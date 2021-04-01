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

#ifndef __UDMA_CTRL_H_
#define __UDMA_CTRL_H_

//---------------------------------//
//
// Module: UDMA_CTRL
//
//---------------------------------//

#ifndef __IO
#define __IO volatile
#endif

typedef struct {

  // Offset = 0x0000
  union {
    __IO uint32_t REG_CG;
    struct {
      __IO uint32_t  PERIPH_CLK_ENABLE : 32;
    } REG_CG_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t REG_CFG_EVT;
    struct {
      __IO uint32_t  CMP_EVENT0 :  8;
      __IO uint32_t  CMP_EVENT1 :  8;
      __IO uint32_t  CMP_EVENT2 :  8;
      __IO uint32_t  CMP_EVENT3 :  8;
    } REG_CFG_EVT_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t REG_RST;
    struct {
      __IO uint32_t  PERIPH_RESET : 32;
    } REG_RST_b;
  };
} UDMA_CTRL_t;


#define REG_REG_CG                     0x000
#define   REG_REG_CG_PERIPH_CLK_ENABLE_LSB         0
#define   REG_REG_CG_PERIPH_CLK_ENABLE_MASK        0xffffffff
#define REG_REG_CFG_EVT                0x004
#define   REG_REG_CFG_EVT_CMP_EVENT3_LSB           24
#define   REG_REG_CFG_EVT_CMP_EVENT3_MASK          0xff
#define   REG_REG_CFG_EVT_CMP_EVENT2_LSB           16
#define   REG_REG_CFG_EVT_CMP_EVENT2_MASK          0xff
#define   REG_REG_CFG_EVT_CMP_EVENT1_LSB           8
#define   REG_REG_CFG_EVT_CMP_EVENT1_MASK          0xff
#define   REG_REG_CFG_EVT_CMP_EVENT0_LSB           0
#define   REG_REG_CFG_EVT_CMP_EVENT0_MASK          0xff
#define REG_REG_RST                    0x008
#define   REG_REG_RST_PERIPH_RESET_LSB             0
#define   REG_REG_RST_PERIPH_RESET_MASK            0xffffffff

static inline uint32_t regfield_read(uint32_t reg, uint32_t mask, uint32_t lsb) {
  return (reg >> lsb) & mask;
}
static inline uint32_t regfield_write(uint32_t reg, uint32_t mask, uint32_t lsb, uint32_t value) {
  reg &= ~(mask << lsb);
  reg |= (value & mask) << lsb;
  return reg;
}

#endif __UDMA_CTRL_H_

