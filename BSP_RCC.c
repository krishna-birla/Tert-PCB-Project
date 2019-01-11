/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_RCC.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_RCC.h"

void Start_All_Clocks()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_TIM1_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_TIM15_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_I2C2_CLK_ENABLE();
}

void ChangeMSI()
{
	RCC->CR |= 0x00000001;
	RCC->CR |= 0x00000008;
	RCC->CR |= 0x00000060;
	RCC->ICSCR &= 0xFFFF00FF;
	FLASH->ACR &= 0xFFFFFFF0;
	RCC->CR &= 0xFEFFFFFF;
	RCC->PLLCFGR = 0x38202801;
	RCC->CR |= 0x01000000;
	RCC->PLLCFGR |= 0x01000000;
	SystemCoreClock = HAL_RCC_GetSysClockFreq() >> AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE) >> POSITION_VAL(RCC_CFGR_HPRE)];
	FLASH->ACR |= 0x00000004;
	RCC->CFGR &= 0xFFFFFF0F;
	RCC->CFGR |= 0x00000003;
	RCC->CFGR &= 0xFFFFC0FF;
	SystemCoreClock = HAL_RCC_GetSysClockFreq() >> AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE) >> POSITION_VAL(RCC_CFGR_HPRE)];
}

void SystemClock_Config_80MHz(RCC_OscInitTypeDef* RCC_Osc_Init_Struct,
	 						  RCC_ClkInitTypeDef* RCC_Clk_Init_Struct)
{
	RCC_Osc_Init_Struct->OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_Osc_Init_Struct->MSIState = RCC_MSI_ON;
	RCC_Osc_Init_Struct->MSIClockRange = RCC_MSIRANGE_6;
	RCC_Osc_Init_Struct->MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_Osc_Init_Struct->PLL.PLLState = RCC_PLL_ON;
	RCC_Osc_Init_Struct->PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_Osc_Init_Struct->PLL.PLLM = PLLM_80MHz;
	RCC_Osc_Init_Struct->PLL.PLLN = PLLN_80MHz;
	RCC_Osc_Init_Struct->PLL.PLLR = PLLR_80MHz;
	RCC_Osc_Init_Struct->PLL.PLLP = PLLP_80MHz;
	RCC_Osc_Init_Struct->PLL.PLLQ = PLLQ_80MHz;

	HAL_RCC_OscConfig(RCC_Osc_Init_Struct);

	RCC_Clk_Init_Struct->ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_Clk_Init_Struct->SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_Clk_Init_Struct->AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_Clk_Init_Struct->APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_Clk_Init_Struct->APB2CLKDivider = RCC_HCLK_DIV1;
	
	HAL_RCC_ClockConfig(RCC_Clk_Init_Struct, FLASH_LATENCY_4);
}

uint32_t Get_PCLK1_Frequency()
{
	return(HAL_RCC_GetPCLK1Freq());
}

uint32_t Get_PCLK2_Frequency()
{
	return(HAL_RCC_GetPCLK2Freq());
}

uint32_t Get_HCLK_Frequency()
{
	return(HAL_RCC_GetHCLKFreq());
}

uint32_t Get_SYSCLK_Frequency()
{
	return(HAL_RCC_GetSysClockFreq());
}

uint32_t Get_TIM1_Frequency()
{
	return((uint32_t)(((double)Get_PCLK2_Frequency()) / ((((double)TIM_Handle_TIM1.Init.Prescaler) + 1) * (((double)TIM_Handle_TIM1.Init.Period) + 1) * (((double)TIM_Handle_TIM1.Init.RepetitionCounter) + 1))));
}

uint32_t Get_TIM2_Frequency()
{
	return((uint32_t)(((double)Get_PCLK1_Frequency()) / ((((double)TIM_Handle_TIM2.Init.Prescaler) + 1) * (((double)TIM_Handle_TIM2.Init.Period) + 1) * (((double)TIM_Handle_TIM2.Init.RepetitionCounter) + 1))));
}

uint32_t Get_TIM15_Frequency()
{
	return((uint32_t)(((double)Get_PCLK2_Frequency()) /  ((((double)TIM_Handle_TIM15.Init.Prescaler) + 1) * (((double)TIM_Handle_TIM15.Init.Period) + 1) * (((double)TIM_Handle_TIM15.Init.RepetitionCounter) + 1))));
}

uint32_t Get_TIM16_Frequency()
{
	return((uint32_t)(((double)Get_PCLK2_Frequency()) /  ((((double)TIM_Handle_TIM16.Init.Prescaler) + 1) * (((double)TIM_Handle_TIM16.Init.Period) + 1) * (((double)TIM_Handle_TIM16.Init.RepetitionCounter) + 1))));
}
