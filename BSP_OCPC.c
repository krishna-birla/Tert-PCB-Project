/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_OCPC.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_OCPC.h"

void InitializeOCPC()
{
	OCPCONStatus = 0;
	OCPCFaultStatus = 0;
	GPIO_Write(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	GPIO_Write(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	GPIO_Write(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	GPIO_Write(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	GPIO_Write(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	GPIO_Write(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void SetOCPCONStatus(OCPC_Device OCPCDevice,
					 GPIO_PinState PinState)
{
	switch(OCPCDevice)
	{
		case OCPC_MOTOR1:{
			GPIO_Write(GPIOA, GPIO_PIN_11, PinState);
			break;
		}
		case OCPC_MOTOR2:{
			GPIO_Write(GPIOB, GPIO_PIN_5, PinState);
			break;
		}
		case OCPC_MOTOR3:{
			GPIO_Write(GPIOB, GPIO_PIN_7, PinState);
			break;
		}
		case OCPC_VCCADC:{
			GPIO_Write(GPIOB, GPIO_PIN_15, PinState);
			break;
		}
		case OCPC_PROXYP:{
			GPIO_Write(GPIOB, GPIO_PIN_11, PinState);
			break;
		}
		case OCPC_M123EN:{
			GPIO_Write(GPIOC, GPIO_PIN_13, PinState);
			break;
		}
		default:{
			//Do nothing.
			break;
		}
	}
}

GPIO_PinState GetOCPCFAULTStatus(OCPC_Device OCPCDevice)
{
	GPIO_PinState PinState = 0x00;
	switch(OCPCDevice)
	{
		case OCPC_MOTOR1:{
			PinState = GPIO_Read(GPIOA, GPIO_PIN_12);
			break;
		}
		case OCPC_MOTOR2:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_6);
			break;
		}
		case OCPC_MOTOR3:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_8);
			break;
		}
		case OCPC_VCCADC:{
			PinState = GPIO_Read(GPIOA, GPIO_PIN_0);
			break;
		}
		case OCPC_PROXYP:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_12);
			break;
		}
		case OCPC_M123EN:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_9);
			break;
		}
		default:{
			//Do nothing.
			break;
		}
	}
	return(PinState);
}

GPIO_PinState GetOCPCONStatus(OCPC_Device OCPCDevice)
{
	GPIO_PinState PinState = 0x00;
	switch(OCPCDevice)
	{
		case OCPC_MOTOR1:{
			PinState = GPIO_Read(GPIOA, GPIO_PIN_11);
			break;
		}
		case OCPC_MOTOR2:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_5);
			break;
		}
		case OCPC_MOTOR3:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_7);
			break;
		}
		case OCPC_VCCADC:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_15);
			break;
		}
		case OCPC_PROXYP:{
			PinState = GPIO_Read(GPIOB, GPIO_PIN_11);
			break;
		}
		case OCPC_M123EN:{
			PinState = GPIO_Read(GPIOC, GPIO_PIN_13);
			break;
		}
		default:{
			//Do nothing.
			break;
		}
	}
	return(PinState);
}

void UpdateOCPCFlags()
{
	OCPCONStatus = 0x00;
	OCPCFaultStatus = 0x00;

	OCPCONStatus = ((GetOCPCONStatus(OCPC_MOTOR1) == GPIO_PIN_SET) ? (OCPCONStatus | (0x01 << (OCPC_MOTOR1 - 1))) : (OCPCONStatus & !(0x01 << (OCPC_MOTOR1 - 1))));
	OCPCONStatus = ((GetOCPCONStatus(OCPC_MOTOR2) == GPIO_PIN_SET) ? (OCPCONStatus | (0x01 << (OCPC_MOTOR2 - 1))) : (OCPCONStatus & !(0x01 << (OCPC_MOTOR2 - 1))));
	OCPCONStatus = ((GetOCPCONStatus(OCPC_MOTOR3) == GPIO_PIN_SET) ? (OCPCONStatus | (0x01 << (OCPC_MOTOR3 - 1))) : (OCPCONStatus & !(0x01 << (OCPC_MOTOR3 - 1))));
	OCPCONStatus = ((GetOCPCONStatus(OCPC_PROXYP) == GPIO_PIN_SET) ? (OCPCONStatus | (0x01 << (OCPC_VCCADC - 1))) : (OCPCONStatus & !(0x01 << (OCPC_VCCADC - 1))));
	OCPCONStatus = ((GetOCPCONStatus(OCPC_VCCADC) == GPIO_PIN_SET) ? (OCPCONStatus | (0x01 << (OCPC_PROXYP - 1))) : (OCPCONStatus & !(0x01 << (OCPC_PROXYP - 1))));
	OCPCONStatus = ((GetOCPCONStatus(OCPC_M123EN) == GPIO_PIN_SET) ? (OCPCONStatus | (0x01 << (OCPC_M123EN - 1))) : (OCPCONStatus & !(0x01 << (OCPC_M123EN - 1))));

	OCPCFaultStatus = ((GetOCPCFAULTStatus(OCPC_MOTOR1) == GPIO_PIN_SET) ? (OCPCFaultStatus | (0x01 << (OCPC_MOTOR1 - 1))) : (OCPCFaultStatus & !(0x01 << (OCPC_MOTOR1 - 1))));
	OCPCFaultStatus = ((GetOCPCFAULTStatus(OCPC_MOTOR2) == GPIO_PIN_SET) ? (OCPCFaultStatus | (0x01 << (OCPC_MOTOR2 - 1))) : (OCPCFaultStatus & !(0x01 << (OCPC_MOTOR2 - 1))));
	OCPCFaultStatus = ((GetOCPCFAULTStatus(OCPC_MOTOR3) == GPIO_PIN_SET) ? (OCPCFaultStatus | (0x01 << (OCPC_MOTOR3 - 1))) : (OCPCFaultStatus & !(0x01 << (OCPC_MOTOR3 - 1))));
	OCPCFaultStatus = ((GetOCPCFAULTStatus(OCPC_PROXYP) == GPIO_PIN_SET) ? (OCPCFaultStatus | (0x01 << (OCPC_VCCADC - 1))) : (OCPCFaultStatus & !(0x01 << (OCPC_VCCADC - 1))));
	OCPCFaultStatus = ((GetOCPCFAULTStatus(OCPC_VCCADC) == GPIO_PIN_SET) ? (OCPCFaultStatus | (0x01 << (OCPC_PROXYP - 1))) : (OCPCFaultStatus & !(0x01 << (OCPC_PROXYP - 1))));
	OCPCFaultStatus = ((GetOCPCFAULTStatus(OCPC_M123EN) == GPIO_PIN_SET) ? (OCPCFaultStatus | (0x01 << (OCPC_M123EN - 1))) : (OCPCFaultStatus & !(0x01 << (OCPC_M123EN - 1))));
}
