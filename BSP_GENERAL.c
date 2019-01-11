/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_GENERAL.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_GENERAL.h"

void Delay(uint32_t count)
{
	while(count--);
}

void Set_NVIC_PriorityGrouping(uint32_t NVIC_PRIORITYGROUP_x)
{
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_x);
}

void Set_NVIC_Priority(IRQn_Type IRQn,
					   uint32_t PreemptPriority,
					   uint32_t SubPriority)
{
	HAL_NVIC_SetPriority(IRQn, PreemptPriority, SubPriority);
}

void Clear_Pending_NVIC(IRQn_Type IRQn)
{
	HAL_NVIC_ClearPendingIRQ(IRQn);
}

void Enable_NVIC(IRQn_Type IRQn)
{
	HAL_NVIC_EnableIRQ(IRQn);
}

void Disable_NVIC(IRQn_Type IRQn)
{
	HAL_NVIC_DisableIRQ(IRQn);
}

void Enable_I2C_IT(I2C_HandleTypeDef *I2C_Handle)
{
	HAL_I2C_EnableListen_IT(I2C_Handle);
}

void Disable_I2C_IT(I2C_HandleTypeDef *I2C_Handle)
{
	HAL_I2C_DisableListen_IT(I2C_Handle);
}

uint8_t InAcceptableRange(uint32_t MeasuredFrequency,
						  uint32_t Period,
						  uint16_t Prescaler)
{
    uint32_t MyFrequency = (uint32_t)((((double)CLKSRC) / (((double)Period) + 1)) / (((double)Prescaler) + 1));
    return(((uint32_t)(((double)(Abs(MeasuredFrequency - MyFrequency))) / ((double)MyFrequency)) > 10) ? FAIL : PASS);
}

double FrequencyToRPM(uint32_t MeasuredFrequency)
{
	return((double)((((double)MeasuredFrequency) * ((double)FACTOR_ONE_PER_CYCLE)) / ((double)POLEPAIRS)));
}

double ICDifferenceToRPM(uint32_t ICDifference,
						 TIM_HandleTypeDef* TIM_Handle)
{
	return((double)(((double)(((double)((double)(Get_PCLK2_Frequency()) / (double)(TIM_Handle->Init.Prescaler + 1))) / (double)(ICDifference))) * ((double)(((double)FACTOR_ONE_PER_CYCLE) / ((double)POLEPAIRS)))));
}

uint32_t Abs(int32_t a)
{
    return((uint32_t)((a < 0) ? (-a) : a));
}

uint32_t PercentToPulse(double PWMPercent,
						uint32_t Period)
{
	if((double)(((((double)Period) / 100.0) * PWMPercent) - 1) < 0.0)
	{
		return((uint32_t)FAIL);
	}
    return((uint32_t)(((((double)Period) / 100.0) * PWMPercent) - 1));
}

double PulseToPercent(uint32_t Pulse,
					  uint32_t Period)
{
	if((double)(((((double)Pulse) + 1.0) / ((double)Period)) * 100.0) < 0.0)
	{
		return((double)FAIL);
	} 
    return((double)(((((double)Pulse) + 1.0) / ((double)Period)) * 100.0));
}

double RPMToPWM(double RPMValue)
{
	return((double)((((double)RPMValue) / ((double)MAXRPM)) * 100.0));
}

double PWMToRPM(double PWMValue)
{
	return((double)((PWMValue / 100.0) * ((double)MAXRPM)));
}
