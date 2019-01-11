/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_OC.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_OC.h"

void TIMx_PWM_Reconfigure(TIM_HandleTypeDef* TIM_Handle,
					      uint32_t Channel,
					      uint32_t Pulse,
					      TIM_OC_InitTypeDef* TIM_OC_Struct)
{
	TIM_OC_Struct->Pulse = Pulse;

	HAL_TIM_PWM_ConfigChannel(TIM_Handle, TIM_OC_Struct, Channel);
}

void TIMx_PWM_Configure(TIM_HandleTypeDef* TIM_Handle,
					    uint32_t Channel,
					    uint32_t TIM_OCMode_x,
					    uint32_t Pulse,
					    TIM_OC_InitTypeDef* TIM_OC_Struct)
{
	TIM_OC_Struct->OCMode = TIM_OCMode_x;
	TIM_OC_Struct->Pulse = Pulse;

	HAL_TIM_PWM_ConfigChannel(TIM_Handle, TIM_OC_Struct, Channel);
}

void InitializePWM()
{
	TIMx_PWM_Configure(&TIM_Handle_TIM2, TIM_CHANNEL_2, TIM_OCMODE_PWM2, PULSE_OC, &TIM_OC_Struct_M1);
	TIMx_PWM_Configure(&TIM_Handle_TIM2, TIM_CHANNEL_3, TIM_OCMODE_PWM2, PULSE_OC, &TIM_OC_Struct_M2);
	TIMx_PWM_Configure(&TIM_Handle_TIM2, TIM_CHANNEL_1, TIM_OCMODE_PWM2, PULSE_OC, &TIM_OC_Struct_M3);
}

void GeneratePWMM1(double RPM)
{
	if(RPM == 0.0)
	{
		HAL_TIM_PWM_Stop(&TIM_Handle_TIM2, TIM_CHANNEL_2);
		return;
	}
	uint32_t Pulse = PercentToPulse(RPMToPWM(RPM), TIM_Handle_TIM2.Init.Period);
	TIMx_PWM_Reconfigure(&TIM_Handle_TIM2, TIM_CHANNEL_2, Pulse, &TIM_OC_Struct_M1);
	HAL_TIM_PWM_Start(&TIM_Handle_TIM2, TIM_CHANNEL_2);
}

void GeneratePWMM2(double RPM)
{
	if(RPM == 0.0)
	{
		HAL_TIM_PWM_Stop(&TIM_Handle_TIM2, TIM_CHANNEL_3);
		return;
	}
	uint32_t Pulse = PercentToPulse(RPMToPWM(RPM), TIM_Handle_TIM2.Init.Period);
	TIMx_PWM_Reconfigure(&TIM_Handle_TIM2, TIM_CHANNEL_3, Pulse, &TIM_OC_Struct_M2);
	HAL_TIM_PWM_Start(&TIM_Handle_TIM2, TIM_CHANNEL_3);
}

void GeneratePWMM3(double RPM)
{
	if(RPM == 0.0)
	{
		HAL_TIM_PWM_Stop(&TIM_Handle_TIM2, TIM_CHANNEL_1);
		return;
	}
	uint32_t Pulse = PercentToPulse(RPMToPWM(RPM), TIM_Handle_TIM2.Init.Period);
	TIMx_PWM_Reconfigure(&TIM_Handle_TIM2, TIM_CHANNEL_1, Pulse, &TIM_OC_Struct_M3);
	HAL_TIM_PWM_Start(&TIM_Handle_TIM2, TIM_CHANNEL_1);
}
