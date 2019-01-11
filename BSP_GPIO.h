/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_GPIO.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_GPIO_H
#define TERTPCB_BSP_GPIO_H

#include "BSP_GENERAL.h"
#include "BSP_GLOBAL.h"

GPIO_InitTypeDef GPIO_CMTMOD_Struct_M13, GPIO_CMTMOD_Struct_M2;
GPIO_InitTypeDef GPIO_BRKMOD_Struct_M1, GPIO_BRKMOD_Struct_M23;
GPIO_InitTypeDef GPIO_I2C1_Struct;
GPIO_InitTypeDef GPIO_I2C2_Struct;
GPIO_InitTypeDef GPIO_IC_Struct_M1, GPIO_IC_Struct_M2, GPIO_IC_Struct_M3;
GPIO_InitTypeDef GPIO_OC_Struct_M13, GPIO_OC_Struct_M2;
GPIO_InitTypeDef GPIO_OCPC_Struct_ON1, GPIO_OCPC_Struct_ON2345, GPIO_OCPC_Struct_ON6;
GPIO_InitTypeDef GPIO_OCPC_Struct_FAULT14, GPIO_OCPC_Struct_FAULT2356;

void GPIOx_Configure(uint32_t GPIO_Pin_x,
					 uint32_t GPIO_Mode_x,
					 uint32_t GPIO_Speed_x,
					 uint32_t GPIO_Pull_x,
					 uint32_t GPIO_AFx_x,
					 GPIO_TypeDef* GPIOx,
					 GPIO_InitTypeDef* GPIO_Struct);
void GPIO_Toggle(GPIO_TypeDef* GPIOx,
			   	 uint32_t GPIO_Pin_x);
void GPIO_Write(GPIO_TypeDef* GPIOx,
			   	uint32_t GPIO_Pin_x,
			   	GPIO_PinState PinState);
GPIO_PinState GPIO_Read(GPIO_TypeDef* GPIOx,
			   			uint32_t GPIO_Pin_x);
void InitializeGPIO();

#endif /* TERTPCB_BSP_GPIO_H */
