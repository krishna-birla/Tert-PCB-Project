/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_OC.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_OC_H
#define TERTPCB_BSP_OC_H

#include "BSP_GENERAL.h"
#include "BSP_GPIO.h"
#include "BSP_TIMER.h"
#include "BSP_RCC.h"
#include "BSP_GLOBAL.h"

TIM_OC_InitTypeDef TIM_OC_Struct_M1, TIM_OC_Struct_M2, TIM_OC_Struct_M3;

void TIMx_PWM_Configure(TIM_HandleTypeDef* TIM_Handle,
					    uint32_t Channel,
					    uint32_t TIM_OCMode_x,
					    uint32_t Pulse,
					    TIM_OC_InitTypeDef* TIM_OC_Struct);
void TIMx_PWM_Reconfigure(TIM_HandleTypeDef* TIM_Handle,
					      uint32_t Channel,
					      uint32_t Pulse,
					      TIM_OC_InitTypeDef* TIM_OC_Struct);
void InitializePWM();
void GeneratePWMM1(double RPM);
void GeneratePWMM2(double RPM);
void GeneratePWMM3(double RPM);

#endif /* TERTPCB_BSP_OC_H */
