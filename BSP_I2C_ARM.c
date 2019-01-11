/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_I2C_ARM.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_I2C_ARM.h"

void InitializeI2C1()
{
	int i;
	for(i = 0;i < INCOMING_SIZE_BUS1;i++)
	{
		pBuf_RX_I2C1[i] = 0;
	}
	for(i = 0;i < OUTGOING_SIZE_BUS1;i++)
	{
		pBuf_TX_I2C1[i] = 0;
	}
	InitializeI2Cx(I2C1, &I2C1_Struct, &I2C1_Handle, I2C_ADDRESSINGMODE_7BIT, I2C_DUALADDRESS_DISABLE, OWN_ADDRESS_1_WRITE, OWN_ADDRESS_2, I2C_GENERALCALL_DISABLE, I2C_NOSTRETCH_ENABLE, TIMING);

	Enable_NVIC_I2C(&I2C1_Handle, I2C1_EV_IRQn, I2C1_PREEMPT_PRIORITY, I2C1_SUB_PRIORITY);
}

void HAL_I2C1_ListenCpltCallback(I2C_HandleTypeDef* I2C_Handle,
								 uint8_t RW)
{
	if(RW == 0)
	{
		int i = 0;
		for(i = 0;i < (3 * sizeof(double));i++)
		{
			DBL.i[i % 8] = pBuf_RX_I2C1[i];
			if(i % 8 == 7)
			{
				if(DBL.d != MOTORFEED[i / 8].RPMRequired)
				{
					MOTORFEED[i / 8].RPMRequired = DBL.d;
					MOTORFEED[i / 8].RPMValid = 1;
				}
			}
		}
		i = (3 * sizeof(double));
		for(i = (3 * sizeof(double));i < INCOMING_SIZE_BUS1;i++)
		{
			pBuf_TX_I2C2[i - (3 * sizeof(double))] = pBuf_RX_I2C1[i];
		}
		pBuf_TX_I2C2[INCOMING_SIZE_BUS1 - (3 * sizeof(double))] = OCPCONStatus;
		pBuf_TX_I2C2[INCOMING_SIZE_BUS1 - (3 * sizeof(double)) + 1] = OCPCFaultStatus;
	}
	else
	{
		//Do something.
	}
}

void I2C1_EV_IRQHandler()
{
	Clear_Pending_NVIC(I2C1_EV_IRQn);
	Disable_NVIC_I2C(&I2C1_Handle, I2C1_EV_IRQn);

	uint8_t RW = I2Cx_Run_ARM(&I2C1_Handle, pBuf_RX_I2C1, pBuf_TX_I2C1);

	while(!((I2C1_Handle.Instance->ISR) & 0x00000020));

	I2C1_Handle.Instance->CR1 &= 0xFFFFFFFE;
	if((I2C1_Handle.Instance->CR1 & 0x00000001) == 0x00000000)
	{
		I2C1_Handle.Instance->CR1 |= 0x00000001;
	}

	Enable_NVIC_I2C(&I2C1_Handle, I2C1_EV_IRQn, I2C1_PREEMPT_PRIORITY, I2C1_SUB_PRIORITY);
	Clear_Pending_NVIC(I2C1_EV_IRQn);

	HAL_I2C1_ListenCpltCallback(&I2C1_Handle, RW);
}
