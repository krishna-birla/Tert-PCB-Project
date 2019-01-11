/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_PCA.h
 * TYPE: BOARD SUPPORT PACKAGE (HEADER)
 * MCU: STM32F207IG
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_PCA_H
#define TERTPCB_BSP_PCA_H

#include "BSP_GENERAL.h"
#include "BSP_I2C.h"
#include "BSP_I2C_ARM.h"
#include "BSP_I2C_MSP.h"
#include "BSP_GLOBAL.h"

#define PCA_SLAVE_ADDR_WRITE (uint8_t)0x44
#define PCA_SLAVE_ADDR_READ (uint8_t)0x45
#define INPUT_WORD (uint8_t)0x00
#define OUTPUT_WORD (uint8_t)0x01
#define POLARITY_WORD (uint8_t)0x02
#define CONFIGURATION_WORD (uint8_t)0x03
#define PCA_CONFIGURATION_BYTE (uint8_t)0xC7
#define PCA_POLARITY_BYTE (uint8_t)0x07

typedef enum
{
	GPIO_Extender_Pin_0 = (uint8_t)0x00,
	GPIO_Extender_Pin_1 = (uint8_t)0x01,
	GPIO_Extender_Pin_2 = (uint8_t)0x02,
	GPIO_Extender_Pin_3 = (uint8_t)0x03,
	GPIO_Extender_Pin_4 = (uint8_t)0x04,
	GPIO_Extender_Pin_5 = (uint8_t)0x05,
	GPIO_Extender_Pin_6 = (uint8_t)0x06,
	GPIO_Extender_Pin_7 = (uint8_t)0x07
}GPIO_Extender_Pin;

uint8_t CurrentStateOfOutputPort;
uint8_t CurrentStateOfInputPort;

void InitializeGPIOExtender();
GPIO_PinState GPIO_Extender_Read(GPIO_Extender_Pin GPIO_Extender_Pin_x);
void GPIO_Extender_Write(GPIO_Extender_Pin GPIO_Extender_Pin_x,
						 GPIO_PinState PinState);
uint8_t GPIO_Extender_Read_All();
uint8_t GPIO_Extender_Write_All(GPIO_PinState PinState);

#endif /* TERTPCB_BSP_PCA_H */
