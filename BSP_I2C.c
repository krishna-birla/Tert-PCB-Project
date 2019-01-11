/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_I2C.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_I2C.h"

uint8_t I2Cx_Run_ARM(I2C_HandleTypeDef* I2C_Handle,
					 uint8_t* pBuf_RX,
					 uint8_t* pBuf_TX)
{
	while(!((I2C_Handle->Instance->ISR) & 0x00000004));
	uint8_t RW = I2C_Handle->Instance->RXDR;

	if(RW == 0)
	{
		uint16_t count = INCOMING_SIZE_BUS1;
		int index = 0;
		while(count--)
		{
			while(!((I2C_Handle->Instance->ISR) & 0x00000004));
			pBuf_RX[index++] = I2C_Handle->Instance->RXDR;
		}
	}
	else
	{
		uint16_t count = OUTGOING_SIZE_BUS1;
		int index = 0;
		while(count--)
		{
			while(!((I2C_Handle->Instance->ISR) & 0x00000001));
			I2C_Handle->Instance->TXDR = pBuf_TX[index++];
		}
	}
	return(RW);
}

uint8_t I2Cx_Run_MSP(I2C_HandleTypeDef* I2C_Handle,
					 uint8_t* pBuf_RX,
					 uint8_t* pBuf_TX)
{
	while(!((I2C_Handle->Instance->ISR) & 0x00000004));
	uint8_t RW = I2C_Handle->Instance->RXDR;

	if(RW == 0)
	{
		uint16_t count = INCOMING_SIZE_BUS2;
		int index = 0;
		while(count--)
		{
			while(!((I2C_Handle->Instance->ISR) & 0x00000004));
			pBuf_RX[index++] = I2C_Handle->Instance->RXDR;
		}
	}
	else
	{
		uint16_t count = OUTGOING_SIZE_BUS2;
		int index = 0;
		while(count--)
		{
			while(!((I2C_Handle->Instance->ISR) & 0x00000001));
			I2C_Handle->Instance->TXDR = pBuf_TX[index++];
		}
	}
	return(RW);
}

void I2Cx_Write_Master(I2C_HandleTypeDef* I2C_Handle,
					   uint8_t SlaveAddr,
					   uint8_t* pBuf_TX,
					   uint32_t BufSize)
{
	while(HAL_I2C_GetState(I2C_Handle) != HAL_I2C_STATE_READY);
	while(HAL_I2C_Master_Transmit(I2C_Handle, SlaveAddr, pBuf_TX, BufSize, TIMEOUT) != HAL_OK);
}

void I2Cx_Read_Master(I2C_HandleTypeDef* I2C_Handle,
					  uint8_t SlaveAddr,
					  uint8_t* pBuf_TX,
					  uint32_t BufSize)
{
	while(HAL_I2C_GetState(I2C_Handle) != HAL_I2C_STATE_READY);
	while(HAL_I2C_Master_Receive(I2C_Handle, SlaveAddr, pBuf_TX, BufSize, TIMEOUT) != HAL_OK);
}

void InitializeI2Cx(I2C_TypeDef* I2Cx,
					I2C_InitTypeDef* I2C_Struct,
					I2C_HandleTypeDef* I2C_Handle,
					uint32_t I2C_ADDRESSINGMODE_x,
					uint32_t I2C_DUALADDRESS_x,
					uint32_t OWN_ADDRESS_1_x,
					uint32_t OWN_ADDRESS_2_x,
					uint32_t I2C_GENERALCALL_x,
					uint32_t I2C_NOSTRETCH_x,
					uint32_t Timing)
{
	I2C_Struct->AddressingMode = I2C_ADDRESSINGMODE_x;
	I2C_Struct->DualAddressMode = I2C_DUALADDRESS_x;
	I2C_Struct->OwnAddress1 = OWN_ADDRESS_1_x;
	I2C_Struct->OwnAddress2 = OWN_ADDRESS_2_x;
	I2C_Struct->GeneralCallMode = I2C_GENERALCALL_x;
	I2C_Struct->NoStretchMode = I2C_NOSTRETCH_x;
	I2C_Struct->Timing = Timing;

	I2C_Handle->Instance = I2Cx;
	I2C_Handle->Init = *I2C_Struct;
	I2C_Handle->Mode = HAL_I2C_MODE_SLAVE;
	
	HAL_I2C_Init(I2C_Handle);
}

void Enable_NVIC_I2C(I2C_HandleTypeDef* I2C_Handle,
					 IRQn_Type IRQn,
					 uint32_t PreemptPriority,
					 uint32_t SubPriority)
{
	Enable_NVIC(IRQn);
	Set_NVIC_Priority(IRQn, PreemptPriority, SubPriority);
	Enable_I2C_IT(I2C_Handle);
}

void Disable_NVIC_I2C(I2C_HandleTypeDef* I2C_Handle,
					  IRQn_Type IRQn)
{
	Disable_NVIC(IRQn);
	Disable_I2C_IT(I2C_Handle);
}
