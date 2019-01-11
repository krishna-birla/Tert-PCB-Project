/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_GLOBAL.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_GLOBAL_H
#define TERTPCB_BSP_GLOBAL_H

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_rcc.h"
#include "stm32l4xx_hal_tim.h"
#include "stm32l4xx_hal_i2c.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#define POLEPAIRS (uint8_t)0x02
#define FACTOR_ONE_PER_CYCLE (uint8_t)0x3C
#define MAXRPM (uint16_t)0x14D5 //Confirm Later
#define PASS (uint8_t)0x01
#define FAIL (uint8_t)0x00

typedef enum
{
	MOTOR_1 = (uint8_t)0x00,
	MOTOR_2 = (uint8_t)0x01,
	MOTOR_3 = (uint8_t)0x02,
	NUM_MOTOR = (uint8_t)0x03
}MOTOR_Device;

union Mydouble
{
	double d;
	uint8_t i[sizeof(double)];
}DBL;

struct Inputcompare
{
	uint32_t ICValue1;
	uint32_t ICValue2;
	uint32_t ICDifference;
	uint16_t CaptureIndex;
	volatile uint32_t Counter;
	double RPM;
}MOTORSTATE[NUM_MOTOR];

struct Motorparams
{
	uint8_t RPMValid;
	uint8_t RotorLock;
	double RPMRequired;
}MOTORFEED[NUM_MOTOR];

void InitializeGlobals();

#endif /* TERTPCB_BSP_GLOBAL_H */
