/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Copyright (C) 2020 ETH Zurich
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 8 spaces!
 */


/*
 * Create implementation of vPortSetupTimerInterrupt() if the CLINT is not
 * available, but make sure the configCLINT_BASE_ADDRESS constant is still
 * defined.
 *
 * Define vPortHandleInterrupt to whatever the interrupt handler is called.  In
 * this case done by defining vPortHandleInterrupt=SystemIrqHandler on the
 * assembler command line as SystemIrqHandler is referenced from both FreeRTOS
 * code and the libraries that come with the Vega board.
 */

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>

/* c stdlib */
#include <stdio.h>

/* PULPissimo includes. */
#include "target/core-v-mcu/include/core-v-mcu-config.h"
#include "target/core-v-mcu/include/core-v-mcu-system.h"
#include "hal/include/hal_timer_irq.h"
#include "hal/include/hal_fll.h"
#include "hal/include/hal_irq.h"
#include "hal/include/hal_gpio.h"

/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting (defined in this file) is used to
 * select between the two.  The simply blinky demo is implemented and described
 * in main_blinky.c.  The more comprehensive test and demo application is
 * implemented and described in main_full.c.
 *
 * This file implements the code that is not demo specific, including the
 * hardware setup and standard FreeRTOS hook functions.
 *
 * ENSURE TO READ THE DOCUMENTATION PAGE FOR THIS PORT AND DEMO APPLICATION ON
 * THE http://www.FreeRTOS.org WEB SITE FOR FULL INFORMATION ON USING THIS DEMO
 * APPLICATION, AND ITS ASSOCIATE FreeRTOS ARCHITECTURE PORT!
 *
 */

/* Set mainCREATE_SIMPLE_BLINKY_DEMO_ONLY to one to run the simple blinky demo,
or 0 to run the more comprehensive test and demo application. */
/* #define mainCREATE_SIMPLE_BLINKY_DEMO_ONLY	0*/

/*
 * main_blinky() is used when mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is set to 1.
 * main_full() is used when mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is set to 0.
 */

	extern void main_blinky( void );

/* Prototypes for the standard FreeRTOS callback/hook functions implemented
within this file.  See https://www.freertos.org/a00016.html */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

/* Prepare hardware to run the demo. */
static void prvSetupHardware( void );



/*-----------------------------------------------------------*/
#include <periph-tasks/include/write_uart_task.h>
#include <app/include/i2c_task.h>
#include <app/include/estruct.h>

#include "libs/cli/include/cli.h"

char* SOFTWARE_VERSION_STR = "cli_test v0.1\n";
extern const struct cli_cmd_entry my_main_menu[];

int main(void)
{
	//apb_timer = ((apb_timer_typedef*) TIMER_START_ADDR);
	//apb_int = ((apb_interrupt_ctl_typedef*) 0x1A109800);
	prvSetupHardware();

	/* The mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting is described at the top
	of this file. */
	xTaskCreate(
		prvWriteUart0Task, /* The function that implements the task. */
		"uart0", /* The text name assigned to the task - for debug only as it is not used by the kernel. */
		configMINIMAL_STACK_SIZE, /* The size of the stack to allocate to the task. */
		NULL, /* The parameter passed to the task - not used in this case. */
		tskIDLE_PRIORITY+3, /* The priority assigned to the task. */
		NULL); /* The task handle is not required, so NULL is passed. */
	xTaskCreate(prvWriteUart1Task,"uart1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL);
	//xTaskCreate (prvI2CTask, "I2C", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
	//xTaskCreate (prvCAMTask, "CAM", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

	CLI_start_task( my_main_menu );

	/* Start the tasks and timer running. */
	vTaskStartScheduler();
	/* If all is well, the scheduler will now be running, and the following
		line will never be reached.  If the following line does execute, then
		there was insufficient FreeRTOS heap memory available for the Idle and/or
		timer tasks to be created.  See the memory management section on the
		FreeRTOS web site for more details on the FreeRTOS heap
		http://www.freertos.org/a00111.html. */

	while(1);
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Init board hardware. */
	system_init();

	/* configure led0 (spim_csn1) as gpio */
	gpio_pin_configure(0x5, GPIO_OUTPUT_LOW);

	/* Set up UART1 (swap TX and RX) */
//	pinmux_pin_set(4, 1);	// IO_4 connected to JB[3] should be RX
//	pinmux_pin_set(3 , 1);	// IO_3 connected to JB[2] should be TX
}
/*-----------------------------------------------------------*/

void vToggleLED( void )
{
	gpio_pin_toggle( 0x5 );
}
/*-----------------------------------------------------------*/


void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
//	printf( "error: application malloc failed\n" );
	__asm volatile( "ebreak" );
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	__asm volatile( "ebreak" );
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* The tests in the full demo expect some interaction with interrupts. */
	#if( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY != 1 )
	{
		extern void vFullDemoTickHook( void );
		vFullDemoTickHook();
	}
	#endif
}
/*-----------------------------------------------------------*/
