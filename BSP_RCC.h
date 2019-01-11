/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_RCC.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_RCC_H
#define TERTPCB_BSP_RCC_H

#include "BSP_GENERAL.h"
#include "BSP_TIMER.h"
#include "BSP_GLOBAL.h"

#define PLLM_80MHz (uint8_t)0x01
#define PLLN_80MHz (uint8_t)0x28
#define PLLR_80MHz (uint8_t)0x02
#define PLLP_80MHz (uint8_t)0x07
#define PLLQ_80MHz (uint8_t)0x04

RCC_ClkInitTypeDef RCC_Clk_Init_Struct;
RCC_OscInitTypeDef RCC_Osc_Init_Struct;

void ChangeMSI();
void Start_All_Clocks();
void SystemClock_Config_80MHz(RCC_OscInitTypeDef* RCC_Osc_Init_Struct,
							  RCC_ClkInitTypeDef* RCC_Clk_Init_Struct);
uint32_t HAL_TIM_ReadCapturedValueN(TIM_HandleTypeDef* TIM_Handle,
									uint32_t Channel);
uint32_t Get_PCLK1_Frequency();
uint32_t Get_PCLK2_Frequency();
uint32_t Get_HCLK_Frequency();
uint32_t Get_SYSCLK_Frequency();
uint32_t Get_TIM1_Frequency();
uint32_t Get_TIM2_Frequency();
uint32_t Get_TIM15_Frequency();

#endif /* TERTPCB_BSP_I2C_MSP_H */
