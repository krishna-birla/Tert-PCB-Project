/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_GLOBAL.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_GLOBAL.h"

void InitializeGlobals()
{
	int i;
	for(i = 0;i < 3;i++)
	{
		MOTORFEED[i].RPMValid = 0;
		MOTORFEED[i].RotorLock = 0;
		MOTORFEED[i].RPMRequired = 0.0;
	}
	for(i = 0;i < 3;i++)
	{
		MOTORSTATE[i].ICValue1 = 0x00000000;
		MOTORSTATE[i].ICValue2 = 0x00000000;
		MOTORSTATE[i].ICDifference = 0x00000000;
		MOTORSTATE[i].CaptureIndex = 0x0000;
		MOTORSTATE[i].Counter = 0x00000000;
		MOTORSTATE[i].RPM = 0.0;
	}
}
