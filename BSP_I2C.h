/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_I2C.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_I2C_H
#define TERTPCB_BSP_I2C_H

#include "BSP_GENERAL.h"
#include "BSP_GLOBAL.h"

#define INCOMING_SIZE_BUS1 (uint8_t)0x0A
#define OUTGOING_SIZE_BUS1 (uint8_t)0x0A
#define INCOMING_SIZE_BUS2 (uint8_t)0x0A
#define OUTGOING_SIZE_BUS2 (uint8_t)0x0A
#define OWN_ADDRESS_1_WRITE (uint8_t)0xD0
#define OWN_ADDRESS_1_READ (uint8_t)0xD1
#define OWN_ADDRESS_2 (uint8_t)0x00
#define TIMING (uint32_t)0x00000E14
#define TIMEOUT (uint32_t)0x00002710
#define I2C1_PREEMPT_PRIORITY (uint8_t)0x03
#define I2C1_SUB_PRIORITY (uint8_t)0x03
#define I2C2_PREEMPT_PRIORITY (uint8_t)0x04
#define I2C2_SUB_PRIORITY (uint8_t)0x04

uint8_t pBuf_RX_I2C1[INCOMING_SIZE_BUS1];
uint8_t pBuf_TX_I2C1[OUTGOING_SIZE_BUS1];
uint8_t pBuf_RX_I2C2[INCOMING_SIZE_BUS2];
uint8_t pBuf_TX_I2C2[OUTGOING_SIZE_BUS2];

void InitializeI2Cx(I2C_TypeDef* I2Cx,
					I2C_InitTypeDef *I2C_Struct,
					I2C_HandleTypeDef *I2C_Handle,
					uint32_t I2C_ADDRESSINGMODE_x,
					uint32_t I2C_DUALADDRESS_x,
					uint32_t OWN_ADDRESS_1_x,
					uint32_t OWN_ADDRESS_2_x,
					uint32_t I2C_GENERALCALL_x,
					uint32_t I2C_NOSTRETCH_x,
					uint32_t Timing);
void Enable_NVIC_I2C(I2C_HandleTypeDef *I2C_Handle,
					 IRQn_Type IRQn,
					 uint32_t PreemptPriority,
					 uint32_t SubPriority);
void Disable_NVIC_I2C(I2C_HandleTypeDef *I2C_Handle,
					  IRQn_Type IRQn);
uint8_t I2Cx_Run_MSP(I2C_HandleTypeDef *I2C_Handle,
					 uint8_t *pBuf_RX,
					 uint8_t *pBuf_TX);
uint8_t I2Cx_Run_ARM(I2C_HandleTypeDef *I2C_Handle,
					 uint8_t *pBuf_RX,
					 uint8_t *pBuf_TX);
void I2Cx_Write_Master(I2C_HandleTypeDef* I2C_Handle,
					   uint8_t SlaveAddr,
					   uint8_t* pBuf_TX,
					   uint32_t BufSize);
void I2Cx_Read_Master(I2C_HandleTypeDef* I2C_Handle,
					  uint8_t SlaveAddr,
					  uint8_t* pBuf_TX,
					  uint32_t BufSize);

#endif /* TERTPCB_BSP_I2C_H */
