/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: app.c
 * TYPE: APPLICATION (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "app.h"

void Code_Life_Start_Init()
{
//	SystemClock_Config_80MHz(&RCC_Osc_Init_Struct, &RCC_Clk_Init_Struct);
	ChangeMSI();
	Start_All_Clocks();
	InitializeGPIO();
	InitializeOCPC();
	InitializeTIMx();
	InitializePWM();
	InitializeI2C1();
	InitializeI2C2();
	InitializeGlobals();
	InitializeGPIOExtender();
}

uint8_t All_Systems_Online()
{
	return(1);
}

void Eat_Sleep_Code_Repeat()
{
	if(MOTORFEED[MOTOR_1].RPMValid == 1)
	{
		GPIO_Extender_Write(GPIO_Extender_Pin_3, (MOTORFEED[MOTOR_1].RPMRequired < 0.0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		GeneratePWMM1((MOTORFEED[MOTOR_1].RPMRequired < 0.0) ? (-1 * MOTORFEED[MOTOR_1].RPMRequired) : MOTORFEED[MOTOR_1].RPMRequired);
		MOTORFEED[MOTOR_1].RPMValid = 0;
	}
	if(MOTORFEED[MOTOR_2].RPMValid == 1)
	{
		GPIO_Extender_Write(GPIO_Extender_Pin_4, (MOTORFEED[MOTOR_2].RPMRequired < 0.0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		GeneratePWMM2((MOTORFEED[MOTOR_2].RPMRequired < 0.0) ? (-1 * MOTORFEED[MOTOR_2].RPMRequired) : MOTORFEED[MOTOR_2].RPMRequired);
		MOTORFEED[MOTOR_2].RPMValid = 0;
	}
	if(MOTORFEED[MOTOR_3].RPMValid == 1)
	{
		GPIO_Extender_Write(GPIO_Extender_Pin_5, (MOTORFEED[MOTOR_3].RPMRequired < 0.0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		GeneratePWMM3((MOTORFEED[MOTOR_3].RPMRequired < 0.0) ? (-1 * MOTORFEED[MOTOR_3].RPMRequired) : MOTORFEED[MOTOR_3].RPMRequired);
		MOTORFEED[MOTOR_3].RPMValid = 0;
	}
}

void Check_For_Rotor_Lock()
{
	MOTORFEED[MOTOR_1].RotorLock = GPIO_Extender_Read(GPIO_Extender_Pin_0);
	MOTORFEED[MOTOR_2].RotorLock = GPIO_Extender_Read(GPIO_Extender_Pin_1);
	MOTORFEED[MOTOR_3].RotorLock = GPIO_Extender_Read(GPIO_Extender_Pin_2);
}

int main()
{
	Code_Life_Start_Init();

	while(All_Systems_Online())
	{
		Eat_Sleep_Code_Repeat();
		UpdateOCPCFlags();
		Check_For_Rotor_Lock();
	}
}
