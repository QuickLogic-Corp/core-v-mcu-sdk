/*
 * This is a generated file
 * 
 * Copyright 2021 QuickLogic
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __UDMA_UART_H_
#define __UDMA_UART_H_

//---------------------------------//
//
// Module: UDMA_UART
//
//---------------------------------//

#ifndef __IO
#define __IO volatile
#endif

typedef struct {

  // Offset = 0x0000
  union {
    __IO uint32_t RX_SADDR;
    struct {
      __IO uint32_t  SADDR      : 12;
    } RX_SADDR_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t RX_SIZE;
    struct {
      __IO uint32_t  SIZE       : 16;
    } RX_SIZE_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t RX_CFG;
    struct {
      __IO uint32_t  CONTINUOUS :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  EN         :  1;
      __IO uint32_t  PENDING    :  1;
      __IO uint32_t  CLR        :  1;
    } RX_CFG_b;
  };
  __I uint32_t    RESERVED0[1];

  // Offset = 0x0010
  union {
    __IO uint32_t TX_SADDR;
    struct {
      __IO uint32_t  SADDR      : 12;
    } TX_SADDR_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t TX_SIZE;
    struct {
      __IO uint32_t  SIZE       : 16;
    } TX_SIZE_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t TX_CFG;
    struct {
      __IO uint32_t  CONTINUOUS :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  EN         :  1;
      __IO uint32_t  PENDING    :  1;
      __IO uint32_t  CLR        :  1;
    } TX_CFG_b;
  };
  __I uint32_t    RESERVED1[1];

  // Offset = 0x0020
  union {
    __IO uint32_t STATUS;
    struct {
      __IO uint32_t  TX_BUSY    :  1;
      __IO uint32_t  RX_BUSY    :  1;
    } STATUS_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t UART_SETUP;
    struct {
      __IO uint32_t  PARITY_EN  :  1;
      __IO uint32_t  BITS       :  2;
      __IO uint32_t  STOP_BITS  :  1;
      __IO uint32_t  RX_POLLING_EN :  1;
      __IO uint32_t  RX_CLEAN_FIFO :  1;
      __IO uint32_t             :  2;
      __IO uint32_t  EN_TX      :  1;
      __IO uint32_t  EN_RX      :  1;
      __IO uint32_t             :  6;
      __IO uint32_t  DIV        : 16;
    } UART_SETUP_b;
  };

  // Offset = 0x0028
  union {
    __IO uint32_t ERROR;
    struct {
      __IO uint32_t  OVERFLOW_ERR :  1;
      __IO uint32_t  PARITY_ERR :  1;
    } ERROR_b;
  };

  // Offset = 0x002c
  union {
    __IO uint32_t IRQ_EN;
    struct {
      __IO uint32_t  RX_IRQ_EN  :  1;
      __IO uint32_t  ERR_IRQ_EN :  1;
    } IRQ_EN_b;
  };

  // Offset = 0x0030
  union {
    __IO uint32_t VALID;
    struct {
      __IO uint32_t  RX_DATA_VALID :  1;
    } VALID_b;
  };

  // Offset = 0x0034
  union {
    __IO uint32_t DATA;
    struct {
      __IO uint32_t  RX_DATA    :  8;
    } DATA_b;
  };
} UDMA_UART_t;


#define REG_RX_SADDR                   0x00
#define   REG_RX_SADDR_SADDR_LSB                   0
#define   REG_RX_SADDR_SADDR_MASK                  0xfff
#define REG_RX_SIZE                    0x04
#define   REG_RX_SIZE_SIZE_LSB                     0
#define   REG_RX_SIZE_SIZE_MASK                    0xffff
#define REG_RX_CFG                     0x08
#define   REG_RX_CFG_CLR_LSB                       6
#define   REG_RX_CFG_CLR_MASK                      0x1
#define   REG_RX_CFG_PENDING_LSB                   5
#define   REG_RX_CFG_PENDING_MASK                  0x1
#define   REG_RX_CFG_EN_LSB                        4
#define   REG_RX_CFG_EN_MASK                       0x1
#define   REG_RX_CFG_CONTINUOUS_LSB                0
#define   REG_RX_CFG_CONTINUOUS_MASK               0x1
#define REG_TX_SADDR                   0x10
#define   REG_TX_SADDR_SADDR_LSB                   0
#define   REG_TX_SADDR_SADDR_MASK                  0xfff
#define REG_TX_SIZE                    0x14
#define   REG_TX_SIZE_SIZE_LSB                     0
#define   REG_TX_SIZE_SIZE_MASK                    0xffff
#define REG_TX_CFG                     0x18
#define   REG_TX_CFG_CLR_LSB                       6
#define   REG_TX_CFG_CLR_MASK                      0x1
#define   REG_TX_CFG_PENDING_LSB                   5
#define   REG_TX_CFG_PENDING_MASK                  0x1
#define   REG_TX_CFG_EN_LSB                        4
#define   REG_TX_CFG_EN_MASK                       0x1
#define   REG_TX_CFG_CONTINUOUS_LSB                0
#define   REG_TX_CFG_CONTINUOUS_MASK               0x1
#define REG_STATUS                     0x20
#define   REG_STATUS_RX_BUSY_LSB                   1
#define   REG_STATUS_RX_BUSY_MASK                  0x1
#define   REG_STATUS_TX_BUSY_LSB                   0
#define   REG_STATUS_TX_BUSY_MASK                  0x1
#define REG_UART_SETUP                 0x24
#define   REG_UART_SETUP_DIV_LSB                   16
#define   REG_UART_SETUP_DIV_MASK                  0xffff
#define   REG_UART_SETUP_EN_RX_LSB                 9
#define   REG_UART_SETUP_EN_RX_MASK                0x1
#define   REG_UART_SETUP_EN_TX_LSB                 8
#define   REG_UART_SETUP_EN_TX_MASK                0x1
#define   REG_UART_SETUP_RX_CLEAN_FIFO_LSB         5
#define   REG_UART_SETUP_RX_CLEAN_FIFO_MASK        0x1
#define   REG_UART_SETUP_RX_POLLING_EN_LSB         4
#define   REG_UART_SETUP_RX_POLLING_EN_MASK        0x1
#define   REG_UART_SETUP_STOP_BITS_LSB             3
#define   REG_UART_SETUP_STOP_BITS_MASK            0x1
#define   REG_UART_SETUP_BITS_LSB                  1
#define   REG_UART_SETUP_BITS_MASK                 0x3
#define   REG_UART_SETUP_PARITY_EN_LSB             0
#define   REG_UART_SETUP_PARITY_EN_MASK            0x1
#define REG_ERROR                      0x28
#define   REG_ERROR_PARITY_ERR_LSB                 1
#define   REG_ERROR_PARITY_ERR_MASK                0x1
#define   REG_ERROR_OVERFLOW_ERR_LSB               0
#define   REG_ERROR_OVERFLOW_ERR_MASK              0x1
#define REG_IRQ_EN                     0x2C
#define   REG_IRQ_EN_ERR_IRQ_EN_LSB                1
#define   REG_IRQ_EN_ERR_IRQ_EN_MASK               0x1
#define   REG_IRQ_EN_RX_IRQ_EN_LSB                 0
#define   REG_IRQ_EN_RX_IRQ_EN_MASK                0x1
#define REG_VALID                      0x30
#define   REG_VALID_RX_DATA_VALID_LSB              0
#define   REG_VALID_RX_DATA_VALID_MASK             0x1
#define REG_DATA                       0x34
#define   REG_DATA_RX_DATA_LSB                     0
#define   REG_DATA_RX_DATA_MASK                    0xff

#ifndef __REGFIELD_OPS_
#define __REGFIELD_OPS_
static inline uint32_t regfield_read(uint32_t reg, uint32_t mask, uint32_t lsb) {
  return (reg >> lsb) & mask;
}
static inline uint32_t regfield_write(uint32_t reg, uint32_t mask, uint32_t lsb, uint32_t value) {
  reg &= ~(mask << lsb);
  reg |= (value & mask) << lsb;
  return reg;
}
#endif  // __REGFIELD_OPS_

#endif // __UDMA_UART_H_
