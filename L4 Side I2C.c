/*
#include "stm32l4xx.h"
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_rcc.h"
#include "stm32l4xx_hal_tim.h"
#include "stm32l4xx_hal_dma.h"
#include "stm32l4xx_hal_tim_ex.h"
#include "stm32l4xx_hal_i2c.h"
#include "stdlib.h"

#define OWN_ADDRESS_1_WRITE 0xD0
#define OWN_ADDRESS_1_READ 0xD1

GPIO_InitTypeDef GPIO_Struct;
I2C_InitTypeDef I2C_Struct;
I2C_HandleTypeDef I2C_Handle;

uint8_t pBuf_RX[127] = {0};
uint8_t pBuf_TX[127] = {0};
uint8_t pBuf_RX1[127] = {0};
uint8_t pBuf_RX2[127] = {0};
uint8_t pBuf_RX3[127] = {0};
uint8_t pBuf_TX1[127] = {0};
uint8_t pBuf_TX2[127] = {0};
uint8_t pBuf_TX3[127] = {0};

uint8_t marker = 0;
uint8_t multipleWrite = 0;
uint8_t EnetredI2C1_EV_IRQHandler = 0;

void CopyArray(uint8_t *pBuf_TX,uint8_t *pBuf_RX,uint8_t count)
{
	int i=0;
	for(i=0;i<count;i++)
	{
		pBuf_TX[i] = pBuf_RX[i];
	}
}

void InitializeI2Cx(I2C_TypeDef* I2Cx,
					I2C_InitTypeDef *I2C_Struct,
					I2C_HandleTypeDef *I2C_Handle,
					uint32_t I2C_ADDRESSINGMODE_x,
					uint32_t I2C_DUALADDRESS_x,
					uint32_t OWN_ADDRESS_1,
					uint32_t OWN_ADDRESS_2,
					uint32_t I2C_GENERALCALL_x,
					uint32_t I2C_NOSTRETCH_x,
					uint32_t Timing)
{
	I2C_Struct->AddressingMode = I2C_ADDRESSINGMODE_x;
	I2C_Struct->DualAddressMode = I2C_DUALADDRESS_x;
	I2C_Struct->OwnAddress1 = OWN_ADDRESS_1;
	I2C_Struct->OwnAddress2 = OWN_ADDRESS_2;
	I2C_Struct->GeneralCallMode = I2C_GENERALCALL_x;
	I2C_Struct->NoStretchMode = I2C_NOSTRETCH_x;
	I2C_Struct->Timing = Timing;

	I2C_Handle->Instance = I2Cx;
	I2C_Handle->Init = *I2C_Struct;
	HAL_I2C_Init(I2C_Handle);
}

void EnableNVICI2C(I2C_HandleTypeDef *I2C_Handle)
{
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
	HAL_NVIC_SetPriority(I2C1_EV_IRQn,0,0);
	HAL_I2C_EnableListen_IT(I2C_Handle);
}

void DisableNVICI2C(I2C_HandleTypeDef *I2C_Handle)
{
	HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
	HAL_I2C_DisableListen_IT(I2C_Handle);
}

void I2C1_Run(I2C_HandleTypeDef *I2C_Handle,uint8_t *pBuf_RX,uint8_t *pBuf_TX)
{
	while(!((I2C_Handle->Instance->ISR)&0x00000004));
	uint8_t Head = I2C_Handle->Instance->RXDR;
	uint8_t RW = (uint8_t)(Head>>7);
	uint8_t count = (uint8_t)((uint8_t)(Head<<1)>>1);

	if(RW == 0)
	{
		int index=0;
		while(count--)
		{
			while(!((I2C_Handle->Instance->ISR)&0x00000004));
			pBuf_RX[index++] = I2C_Handle->Instance->RXDR;
		}
	}
	else
	{
		CopyArray(pBuf_TX,pBuf_RX,count);
		int index=0;
		while(count--)
		{
			while(!((I2C_Handle->Instance->ISR) & 0x00000001));
			I2C_Handle->Instance->TXDR = pBuf_TX[index++];
		}
	}
}

int main(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();

	GPIO_Struct.Mode = GPIO_MODE_AF_OD;
	GPIO_Struct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_Struct.Pull = GPIO_PULLUP;
	GPIO_Struct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_Struct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOA,&GPIO_Struct);

	InitializeI2Cx(I2C1,&I2C_Struct,&I2C_Handle,I2C_ADDRESSINGMODE_7BIT,I2C_DUALADDRESS_DISABLE,OWN_ADDRESS_1_WRITE,0x00,I2C_GENERALCALL_DISABLE,I2C_NOSTRETCH_ENABLE,0x00E14);

	EnableNVICI2C(&I2C_Handle);

	while(1)
	{
		//Do nothing.
	}
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *I2C_Handle)
{
	marker = 1;
}

//For single command testing.
void I2C1_EV_IRQHandler()
{
	EnetredI2C1_EV_IRQHandler += 1;

	HAL_NVIC_ClearPendingIRQ(I2C1_EV_IRQn);
	DisableNVICI2C(&I2C_Handle);

	I2C1_Run(&I2C_Handle,pBuf_RX,pBuf_TX);

	while(!((I2C_Handle.Instance->ISR)&0x00000020));

	I2C_Handle.Instance->CR1 &= 0xFFFFFFFE;
	if((I2C_Handle.Instance->CR1 & 0x00000001) == 0x00000000)
	{
		I2C_Handle.Instance->CR1 |= 0x00000001;
	}

	EnableNVICI2C(&I2C_Handle);
	HAL_NVIC_ClearPendingIRQ(I2C1_EV_IRQn);

	HAL_I2C_ListenCpltCallback(&I2C_Handle);
}

//For multiple command testing.
void I2C1_EV_IRQHandler()
{
	EnetredI2C1_EV_IRQHandler += 1;

	HAL_NVIC_ClearPendingIRQ(I2C1_EV_IRQn);
	DisableNVICI2C(&I2C_Handle);

	switch(multipleWrite)
	{
		case 0:{
			I2C1_Run(&I2C_Handle,pBuf_RX1,pBuf_TX1);
			multipleWrite = (multipleWrite+1)%6;
			break;
		}
		case 1:{
			I2C1_Run(&I2C_Handle,pBuf_RX1,pBuf_TX1);
			multipleWrite = (multipleWrite+1)%6;
			break;
		}
		case 2:{
			I2C1_Run(&I2C_Handle,pBuf_RX2,pBuf_TX2);
			multipleWrite = (multipleWrite+1)%6;
			break;
		}
		case 3:{
			I2C1_Run(&I2C_Handle,pBuf_RX2,pBuf_TX2);
			multipleWrite = (multipleWrite+1)%6;
			break;
		}
		case 4:{
			I2C1_Run(&I2C_Handle,pBuf_RX3,pBuf_TX3);
			multipleWrite = (multipleWrite+1)%6;
			break;
		}
		case 5:{
			I2C1_Run(&I2C_Handle,pBuf_RX3,pBuf_TX3);
			multipleWrite = (multipleWrite+1)%6;
			break;
		}
		default:{
			break;
		}
	}

	while(!((I2C_Handle.Instance->ISR)&0x00000020));

	I2C_Handle.Instance->CR1 &= 0xFFFFFFFE;
	if((I2C_Handle.Instance->CR1 & 0x00000001) == 0x00000000)
	{
		I2C_Handle.Instance->CR1 |= 0x00000001;
	}

	EnableNVICI2C(&I2C_Handle);
	HAL_NVIC_ClearPendingIRQ(I2C1_EV_IRQn);

	HAL_I2C_ListenCpltCallback(&I2C_Handle);
}
*/
