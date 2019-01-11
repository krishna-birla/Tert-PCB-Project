/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_GENERAL.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_GENERAL_H
#define TERTPCB_BSP_GENERAL_H

#include "BSP_GLOBAL.h"
#include "BSP_TIMER.h"

void Delay(uint32_t count);
void Set_NVIC_PriorityGrouping(uint32_t NVIC_PRIORITYGROUP_x);
void Set_NVIC_Priority(IRQn_Type IRQn,
					   uint32_t PreemptPriority,
					   uint32_t SubPriority);
void Enable_NVIC(IRQn_Type IRQn);
void Clear_Pending_NVIC(IRQn_Type IRQn);
void Disable_NVIC(IRQn_Type IRQn);
void Disable_I2C_IT(I2C_HandleTypeDef *I2C_Handle);
void Enable_I2C_IT(I2C_HandleTypeDef *I2C_Handle);
double ICDifferenceToRPM(uint32_t ICDifference,
						 TIM_HandleTypeDef* TIM_Handle);
uint8_t InAcceptableRange(uint32_t MeasuredFrequency,
						  uint32_t Period,
						  uint16_t Prescaler);
double FrequencyToRPM(uint32_t MeasuredFrequency);
uint32_t Abs(int32_t a);
uint32_t PercentToPulse(double PWMPercent,
						uint32_t Period);
double PulseToPercent(uint32_t Pulse,
					  uint32_t Period);
double PWMToRPM(double PWMValue);
double RPMToPWM(double RPMValue);
uint32_t Get_PCLK1_Frequency();
uint32_t Get_PCLK2_Frequency();
uint32_t Get_HCLK_Frequency();
uint32_t Get_SYSCLK_Frequency();
uint32_t Get_TIM1_Frequency();
uint32_t Get_TIM2_Frequency();
uint32_t Get_TIM15_Frequency();

#endif /* TERTPCB_BSP_GENERAL_H */
