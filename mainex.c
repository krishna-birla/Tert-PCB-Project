//#include "app.h"
//
//GPIO_InitTypeDef GPIO_I2C1_Ex_Struct;
//I2C_InitTypeDef I2C_Ex_Struct;
//I2C_HandleTypeDef I2C_Ex_Handle;
//
//int main()
//{
//	ChangeMSI();
//
//	__HAL_RCC_GPIOA_CLK_ENABLE();
//	__HAL_RCC_I2C1_CLK_ENABLE();
//
//	GPIOx_Configure(GPIO_PIN_9 | GPIO_PIN_10, GPIO_MODE_AF_OD, GPIO_SPEED_FREQ_HIGH, GPIO_PULLUP, GPIO_AF4_I2C1, GPIOA, &GPIO_I2C1_Ex_Struct);
//
//	I2C_Ex_Struct.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
//	I2C_Ex_Struct.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//	I2C_Ex_Struct.OwnAddress1 = OWN_ADDRESS_1_WRITE;
//	I2C_Ex_Struct.OwnAddress2 = OWN_ADDRESS_2;
//	I2C_Ex_Struct.GeneralCallMode = I2C_GENERALCALL_DISABLE;
//	I2C_Ex_Struct.NoStretchMode = I2C_NOSTRETCH_ENABLE;
//	I2C_Ex_Struct.Timing = TIMING;
//
//	I2C_Ex_Handle.Instance = I2C1;
//	I2C_Ex_Handle.Init = I2C_Ex_Struct;
//	I2C_Ex_Handle.Mode = HAL_I2C_MODE_MASTER;
//
//	HAL_I2C_Init(&I2C_Ex_Handle);
//
//	while(1);
//}
