/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_I2C_ARM.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_I2C_ARM_H
#define TERTPCB_BSP_I2C_ARM_H

#include "BSP_GENERAL.h"
#include "BSP_I2C.h"
#include "BSP_GPIO.h"
#include "BSP_OCPC.h"
#include "BSP_GLOBAL.h"

I2C_InitTypeDef I2C1_Struct;
I2C_HandleTypeDef I2C1_Handle;

void InitializeI2C1();
void HAL_I2C1_ListenCpltCallback(I2C_HandleTypeDef *I2C_Handle,
								 uint8_t RW);

#endif /* TERTPCB_BSP_I2C_ARM_H */
