/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_OCPC.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_OCPC_H
#define TERTPCB_BSP_OCPC_H

#include "BSP_GENERAL.h"
#include "BSP_GPIO.h"
#include "BSP_GLOBAL.h"

typedef enum
{
	OCPC_MOTOR1 = (uint8_t)0x01,
	OCPC_MOTOR2 = (uint8_t)0x02,
	OCPC_MOTOR3 = (uint8_t)0x03,
	OCPC_VCCADC = (uint8_t)0x04,
	OCPC_PROXYP = (uint8_t)0x05,
	OCPC_M123EN = (uint8_t)0x06
}OCPC_Device;

uint8_t OCPCONStatus, OCPCFaultStatus;

void InitializeOCPC();
void SetOCPCONStatus(OCPC_Device OCPCDevice,
					 GPIO_PinState PinState);
GPIO_PinState GetOCPCFAULTStatus(OCPC_Device OCPCDevice);
GPIO_PinState GetOCPCONStatus(OCPC_Device OCPCDevice);
void UpdateOCPCFlags();

#endif /* TERTPCB_BSP_OCPC_H */
