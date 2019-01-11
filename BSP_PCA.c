/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_PCA.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32F207IG
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_PCA.h"

void InitializeGPIOExtender()
{
	uint8_t TempBuf[2] = {0x00};
	TempBuf[0] = CONFIGURATION_WORD;
	TempBuf[1] = PCA_CONFIGURATION_BYTE;
	I2Cx_Write_Master(&I2C1_Handle, PCA_SLAVE_ADDR_WRITE, TempBuf, 0x02);
	TempBuf[0] = POLARITY_WORD;
	TempBuf[1] = PCA_POLARITY_BYTE;
	I2Cx_Write_Master(&I2C1_Handle, PCA_SLAVE_ADDR_WRITE, TempBuf, 0x02);
	CurrentStateOfOutputPort = GPIO_Extender_Write_All(0x00);
	CurrentStateOfInputPort = GPIO_Extender_Read_All();
}

GPIO_PinState GPIO_Extender_Read(GPIO_Extender_Pin GPIO_Extender_Pin_x)
{
	GPIO_PinState PinState;
	uint8_t TempBuf[2] = {0x00};
	TempBuf[0] = INPUT_WORD;
	I2Cx_Write_Master(&I2C1_Handle, PCA_SLAVE_ADDR_WRITE, &TempBuf[0], 0x01);
	I2Cx_Read_Master(&I2C1_Handle, PCA_SLAVE_ADDR_READ, &TempBuf[1], 0x01);
	CurrentStateOfInputPort = TempBuf[1];
	PinState = (TempBuf[1] & (0x01 << GPIO_Extender_Pin_x)) >> GPIO_Extender_Pin_x;
	return(PinState);
}

void GPIO_Extender_Write(GPIO_Extender_Pin GPIO_Extender_Pin_x,
						 GPIO_PinState PinState)
{
	uint8_t NewStateOfOutputPort = (PinState == GPIO_PIN_SET) ? (CurrentStateOfOutputPort | (0x01 << GPIO_Extender_Pin_x)) : (CurrentStateOfOutputPort & !(0x01 << GPIO_Extender_Pin_x));
	uint8_t TempBuf[2] = {0x00};
	TempBuf[0] = OUTPUT_WORD;
	TempBuf[1] = NewStateOfOutputPort;
	I2Cx_Write_Master(&I2C1_Handle, PCA_SLAVE_ADDR_WRITE, TempBuf, 0x02);
	CurrentStateOfOutputPort = NewStateOfOutputPort;
}

uint8_t GPIO_Extender_Read_All()
{
	GPIO_PinState PinState;
	uint8_t TempBuf[2] = {0x00};
	TempBuf[0] = INPUT_WORD;
	I2Cx_Write_Master(&I2C1_Handle, PCA_SLAVE_ADDR_WRITE, &TempBuf[0], 0x01);
	I2Cx_Read_Master(&I2C1_Handle, PCA_SLAVE_ADDR_READ, &TempBuf[1], 0x01);
	PinState = TempBuf[1];
	return(PinState);
}

uint8_t GPIO_Extender_Write_All(GPIO_PinState PinState)
{
	uint8_t TempBuf[2] = {0x00};
	TempBuf[0] = OUTPUT_WORD;
	TempBuf[1] = PinState;
	I2Cx_Write_Master(&I2C1_Handle, PCA_SLAVE_ADDR_WRITE, TempBuf, 0x02);
	return(PinState);
}
