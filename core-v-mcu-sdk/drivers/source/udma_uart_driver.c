

#include "target/core-v-mcu/include/core-v-mcu-config.h"
#include <periph-tasks/include/write_uart_task.h>
#include <string.h>
#include "hal/include/hal_fc_event.h"
#include "hal/include/hal_udma_ctrl_reg_defs.h"

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "target/core-v-mcu/include/core-v-mcu-config.h"
#include "periph-tasks/include/write_uart_task.h"
#include "drivers/include/udma_uart_driver.h"

SemaphoreHandle_t  uart_semaphores_rx[N_UART];
SemaphoreHandle_t  uart_semaphores_tx[N_UART];

uint16_t udma_uart_open (uint8_t uart_id, uint32_t xbaudrate) {
	uart_channel_t*					puart;
	volatile UDMA_CTRL_t*		pudma_ctrl = (UDMA_CTRL_t*)UDMA_CH_ADDR_CTRL;

	/* See if already initialized */
	if (uart_semaphores_rx[uart_id] != NULL || uart_semaphores_tx[uart_id] != NULL) {
		return 1;
	}
	/* Enable reset and enable uart clock */
	pudma_ctrl->REG_RST |= (UDMA_CTRL_UART0_CLKEN << uart_id);
	pudma_ctrl->REG_CG |= (UDMA_CTRL_UART0_CLKEN << uart_id);
	/* Set semaphore */
	SemaphoreHandle_t xSemaphoreHandle;
	xSemaphoreHandle = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphoreHandle);
	uart_semaphores_rx[uart_id] = xSemaphoreHandle;
	configASSERT(uart_semaphores_rx[uart_id]);
	xSemaphoreHandle = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphoreHandle);
	uart_semaphores_tx[uart_id] = xSemaphoreHandle;
	configASSERT(uart_semaphores_tx[uart_id]);
	/* Set handlers. */
	pi_fc_event_handler_set(SOC_EVENT_UDMA_UART_RX(uart_id), NULL, uart_semaphores_rx[uart_id]);
	pi_fc_event_handler_set(SOC_EVENT_UDMA_UART_TX(uart_id), NULL, uart_semaphores_tx[uart_id]);
	/* Enable SOC events propagation to FC. */
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_UART_RX(uart_id));
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_UART_TX(uart_id));

	/* configure */
	puart = (uart_channel_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);
	puart->setup = (5000000/xbaudrate) << 16 | // Baud rate divisor
	(3 << 1) | // 8-bits
	(1 << 4) | // use polling on read
	(1 << 8) | // tx enable
	(1 << 9) ; // rx enable
	
	return 0;
}


uint16_t udma_uart_writeraw(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer) {
	uart_channel_t*					puart = (uart_channel_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	SemaphoreHandle_t xSemaphoreHandle = uart_semaphores_tx[uart_id];
	if( xSemaphoreTake( xSemaphoreHandle, 1000000 ) != pdTRUE ) {
			return 1;
		}

	puart->tx_saddr = write_buffer;
	puart->tx_size = write_len;
	puart->tx_cfg = 0x10; //enable the transfer

	return 0;
}
