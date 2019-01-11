/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_TIMER.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_TIMER_H
#define TERTPCB_BSP_TIMER_H

#include "BSP_GENERAL.h"
#include "BSP_GLOBAL.h"

#define CLKSRC (uint32_t)0x04C4B400
#define REPETITION (uint8_t)0x00
#define PRESCALER_IC (uint16_t)0x03E7
#define PRESCALER_OC (uint16_t)0x0000
#define PERIOD_IC (uint16_t)0xFFFE
#define PERIOD_OC (uint16_t)0x0C7F
#define FILTER_IC (uint32_t)0x00000000
#define PULSE_OC (uint32_t)0x00000000
#define NUM_OF_SAMPLES (uint32_t)0x00000004

TIM_HandleTypeDef  TIM_Handle_TIM1, TIM_Handle_TIM2, TIM_Handle_TIM15, TIM_Handle_TIM16;

void TIMx_Base_Configure(uint32_t Prescaler,
					     uint32_t Period,
					     uint32_t CounterMode,
	  				     uint32_t ClockDivision,
		  			     uint32_t RepetitionCounter,
			  		     TIM_TypeDef* TIMx,
				  	     HAL_TIM_ActiveChannel Channel,
					     TIM_HandleTypeDef* TIM_Handle);
void Enable_NVIC_IC(IRQn_Type IRQn,
					uint32_t PreemptPriority,
					uint32_t SubPriority);
void InitializeTIMx();

#endif /* TERTPCB_BSP_TIMER_H */
