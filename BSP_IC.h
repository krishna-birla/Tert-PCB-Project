/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_IC.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_IC_H
#define TERTPCB_BSP_IC_H

#include "BSP_GENERAL.h"
#include "BSP_GPIO.h"
#include "BSP_TIMER.h"
#include "BSP_RCC.h"
#include "BSP_GLOBAL.h"

TIM_IC_InitTypeDef TIM_IC_Struct_M1, TIM_IC_Struct_M2, TIM_IC_Struct_M3;

void TIMx_IC_Configure(TIM_HandleTypeDef* TIM_Handle,
					   uint32_t Channel,
					   uint32_t TIM_ICPolarity_x,
					   uint32_t TIM_ICSelection_x,
					   uint32_t TIM_ICPrescaler_x,
					   uint32_t TIM_ICFilter_x,
					   TIM_IC_InitTypeDef* TIM_IC_Struct);
void InitializeIC();
double GetMotor1RPM();
double GetMotor2RPM();
double GetMotor3RPM();

#endif /* TERTPCB_BSP_IC_H */
