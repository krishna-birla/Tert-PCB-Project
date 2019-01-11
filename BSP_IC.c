/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_IC.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_IC.h"

void InitializeIC()
{
	TIMx_IC_Configure(&TIM_Handle_TIM15, TIM_CHANNEL_2, TIM_ICPOLARITY_RISING, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, FILTER_IC, &TIM_IC_Struct_M1);
	TIMx_IC_Configure(&TIM_Handle_TIM1, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, FILTER_IC, &TIM_IC_Struct_M2);
	TIMx_IC_Configure(&TIM_Handle_TIM16, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, FILTER_IC, &TIM_IC_Struct_M3);
}

void TIMx_IC_Configure(TIM_HandleTypeDef* TIM_Handle,
					   uint32_t Channel,
					   uint32_t TIM_ICPolarity_x,
					   uint32_t TIM_ICSelection_x,
					   uint32_t TIM_ICPrescaler_x,
					   uint32_t TIM_ICFilter_x,
					   TIM_IC_InitTypeDef* TIM_IC_Struct)
{
	TIM_IC_Struct->ICPolarity = TIM_ICPolarity_x;
	TIM_IC_Struct->ICSelection = TIM_ICSelection_x;
	TIM_IC_Struct->ICFilter = TIM_ICFilter_x;
	TIM_IC_Struct->ICPrescaler = TIM_ICPrescaler_x;

	HAL_TIM_IC_ConfigChannel(TIM_Handle, TIM_IC_Struct, Channel);
}

double GetMotor1RPM()
{
	Enable_NVIC(TIM1_BRK_TIM15_IRQn);
	HAL_TIM_IC_Start_IT(&TIM_Handle_TIM15, TIM_CHANNEL_2);
	while(MOTORSTATE[MOTOR_1].Counter < NUM_OF_SAMPLES);
	MOTORSTATE[MOTOR_1].Counter = 0x00000000;
	return(MOTORSTATE[MOTOR_1].RPM);
}

double GetMotor2RPM()
{
	Enable_NVIC(TIM1_CC_IRQn);
	HAL_TIM_IC_Start_IT(&TIM_Handle_TIM1, TIM_CHANNEL_1);
	while(MOTORSTATE[MOTOR_2].Counter < NUM_OF_SAMPLES);
	MOTORSTATE[MOTOR_2].Counter = 0x00000000;
	return(MOTORSTATE[MOTOR_2].RPM);
}

double GetMotor3RPM()
{
	Enable_NVIC(TIM1_UP_TIM16_IRQn);
	HAL_TIM_IC_Start_IT(&TIM_Handle_TIM16, TIM_CHANNEL_1);
	while(MOTORSTATE[MOTOR_3].Counter < NUM_OF_SAMPLES);
	MOTORSTATE[MOTOR_3].Counter = 0x00000000;
	return(MOTORSTATE[MOTOR_3].RPM);
}

void TIM1_BRK_TIM15_IRQHandler()
{
	MOTORSTATE[MOTOR_1].Counter = MOTORSTATE[MOTOR_1].Counter + 1;

	if(MOTORSTATE[MOTOR_1].CaptureIndex == 0)
	{
		MOTORSTATE[MOTOR_1].ICValue1 = HAL_TIM_ReadCapturedValue(&TIM_Handle_TIM15, TIM_CHANNEL_2);
		MOTORSTATE[MOTOR_1].CaptureIndex = 1;
	}
	else if(MOTORSTATE[MOTOR_1].CaptureIndex == 1)
	{
		MOTORSTATE[MOTOR_1].ICValue2 = HAL_TIM_ReadCapturedValue(&TIM_Handle_TIM15, TIM_CHANNEL_2);
		if(MOTORSTATE[MOTOR_1].ICValue2 > MOTORSTATE[MOTOR_1].ICValue1)
		{
			MOTORSTATE[MOTOR_1].ICDifference = MOTORSTATE[MOTOR_1].ICValue2 - MOTORSTATE[MOTOR_1].ICValue1;
		}
		else
		{
			MOTORSTATE[MOTOR_1].ICDifference = MOTORSTATE[MOTOR_1].ICValue2 + 1 + ((TIM_Handle_TIM15.Init.Period + 1) - MOTORSTATE[MOTOR_1].ICValue1);
		}
		MOTORSTATE[MOTOR_1].RPM = ICDifferenceToRPM(MOTORSTATE[MOTOR_1].ICDifference, &TIM_Handle_TIM15);
		MOTORSTATE[MOTOR_1].CaptureIndex = 0;
	}

	__HAL_TIM_CLEAR_FLAG(&TIM_Handle_TIM15, TIM_IT_UPDATE);

	if(MOTORSTATE[MOTOR_1].Counter == NUM_OF_SAMPLES)
	{
		HAL_TIM_IC_Stop_IT(&TIM_Handle_TIM15, TIM_CHANNEL_2);
		Disable_NVIC(TIM1_BRK_TIM15_IRQn);
	}
}

void TIM1_CC_IRQHandler()
{
	MOTORSTATE[MOTOR_2].Counter = MOTORSTATE[MOTOR_2].Counter + 1;

	if(MOTORSTATE[MOTOR_2].CaptureIndex == 1)
	{
		MOTORSTATE[MOTOR_2].ICValue1 = HAL_TIM_ReadCapturedValue(&TIM_Handle_TIM1, TIM_CHANNEL_1);
		MOTORSTATE[MOTOR_2].CaptureIndex = 1;
	}
	else if(MOTORSTATE[MOTOR_2].CaptureIndex == 1)
	{
		MOTORSTATE[MOTOR_2].ICValue2 = HAL_TIM_ReadCapturedValue(&TIM_Handle_TIM1, TIM_CHANNEL_1);
		if(MOTORSTATE[MOTOR_2].ICValue2 > MOTORSTATE[MOTOR_2].ICValue1)
		{
			MOTORSTATE[MOTOR_2].ICDifference = MOTORSTATE[MOTOR_2].ICValue2 - MOTORSTATE[MOTOR_2].ICValue1;
		}
		else
		{
			MOTORSTATE[MOTOR_2].ICDifference = MOTORSTATE[MOTOR_2].ICValue2 + 1 + ((TIM_Handle_TIM1.Init.Period + 1) - MOTORSTATE[MOTOR_2].ICValue1);
		}
		MOTORSTATE[MOTOR_2].RPM = ICDifferenceToRPM(MOTORSTATE[MOTOR_2].ICDifference, &TIM_Handle_TIM1);
		MOTORSTATE[MOTOR_2].CaptureIndex = 1;
	}

	__HAL_TIM_CLEAR_FLAG(&TIM_Handle_TIM1, TIM_IT_UPDATE);

	if(MOTORSTATE[MOTOR_2].Counter == NUM_OF_SAMPLES)
	{
		HAL_TIM_IC_Stop_IT(&TIM_Handle_TIM1, TIM_CHANNEL_1);
		Disable_NVIC(TIM1_CC_IRQn);
	}
}

void TIM1_UP_TIM16_IRQHandler()
{
	MOTORSTATE[MOTOR_3].Counter = MOTORSTATE[MOTOR_3].Counter + 1;

	if(MOTORSTATE[MOTOR_3].CaptureIndex == 0)
	{
		MOTORSTATE[MOTOR_3].ICValue1 = HAL_TIM_ReadCapturedValue(&TIM_Handle_TIM16, TIM_CHANNEL_1);
		MOTORSTATE[MOTOR_3].CaptureIndex = 1;
	}
	else if(MOTORSTATE[MOTOR_3].CaptureIndex == 1)
	{
		MOTORSTATE[MOTOR_3].ICValue2 = HAL_TIM_ReadCapturedValue(&TIM_Handle_TIM16, TIM_CHANNEL_1);
		if(MOTORSTATE[MOTOR_3].ICValue2 > MOTORSTATE[MOTOR_3].ICValue1)
		{
			MOTORSTATE[MOTOR_3].ICDifference = MOTORSTATE[MOTOR_3].ICValue2 - MOTORSTATE[MOTOR_3].ICValue1;
		}
		else
		{
			MOTORSTATE[MOTOR_3].ICDifference = MOTORSTATE[MOTOR_3].ICValue2 + 1 + ((TIM_Handle_TIM16.Init.Period + 1) - MOTORSTATE[MOTOR_3].ICValue1);
		}
		MOTORSTATE[MOTOR_3].RPM = ICDifferenceToRPM(MOTORSTATE[MOTOR_3].ICDifference, &TIM_Handle_TIM16);
		MOTORSTATE[MOTOR_3].CaptureIndex = 0;
	}

	__HAL_TIM_CLEAR_FLAG(&TIM_Handle_TIM16, TIM_IT_UPDATE);

	if(MOTORSTATE[MOTOR_3].Counter == NUM_OF_SAMPLES)
	{
		HAL_TIM_IC_Stop_IT(&TIM_Handle_TIM16, TIM_CHANNEL_1);
		Disable_NVIC(TIM1_UP_TIM16_IRQn);
	}
}
