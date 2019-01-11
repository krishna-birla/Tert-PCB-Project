/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_TIMER.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_TIMER.h"

void TIMx_Base_Configure(uint32_t Prescaler,
					     uint32_t Period,
					     uint32_t CounterMode,
	  				     uint32_t ClockDivision,
		  			     uint32_t RepetitionCounter,
			  		     TIM_TypeDef* TIMx,
				  	     HAL_TIM_ActiveChannel Channel,
					     TIM_HandleTypeDef* TIM_Handle)
{
	TIM_Handle->Init.Prescaler = Prescaler;
	TIM_Handle->Init.Period = Period;
	TIM_Handle->Init.CounterMode = CounterMode;
	TIM_Handle->Init.ClockDivision = ClockDivision;
	TIM_Handle->Init.RepetitionCounter = RepetitionCounter;
	TIM_Handle->Instance = TIMx;
	TIM_Handle->Channel = Channel;

	HAL_TIM_Base_Init(TIM_Handle);
}

void Enable_NVIC_IC(IRQn_Type IRQn,
					uint32_t PreemptPriority,
					uint32_t SubPriority)
{
	Enable_NVIC(IRQn);
	Set_NVIC_Priority(IRQn, PreemptPriority, SubPriority);
}

void InitializeTIMx()
{
	TIMx_Base_Configure(PRESCALER_IC, PERIOD_IC, TIM_COUNTERMODE_UP, TIM_CLOCKDIVISION_DIV1, REPETITION, TIM1, HAL_TIM_ACTIVE_CHANNEL_1, &TIM_Handle_TIM1);
	TIMx_Base_Configure(PRESCALER_OC, PERIOD_OC, TIM_COUNTERMODE_UP, TIM_CLOCKDIVISION_DIV1, REPETITION, TIM2, HAL_TIM_ACTIVE_CHANNEL_1 | HAL_TIM_ACTIVE_CHANNEL_2 | HAL_TIM_ACTIVE_CHANNEL_3, &TIM_Handle_TIM2);
	TIMx_Base_Configure(PRESCALER_IC, PERIOD_IC, TIM_COUNTERMODE_UP, TIM_CLOCKDIVISION_DIV1, REPETITION, TIM15, HAL_TIM_ACTIVE_CHANNEL_2, &TIM_Handle_TIM15);
	TIMx_Base_Configure(PRESCALER_IC, PERIOD_IC, TIM_COUNTERMODE_UP, TIM_CLOCKDIVISION_DIV1, REPETITION, TIM16, HAL_TIM_ACTIVE_CHANNEL_1, &TIM_Handle_TIM16);
}
