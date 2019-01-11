/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: BSP_I2C_MSP.c
 * TYPE: BOARD SUPPORT PACKAGE (SOURCE)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#include "BSP_I2C_MSP.h"

void InitializeI2C2()
{
	int i;
	for(i = 0;i < INCOMING_SIZE_BUS2;i++)
	{
		pBuf_RX_I2C2[i] = 0;
	}
	for(i = 0;i < OUTGOING_SIZE_BUS2;i++)
	{
		pBuf_TX_I2C2[i] = 0;
	}
	InitializeI2Cx(I2C2, &I2C2_Struct, &I2C2_Handle, I2C_ADDRESSINGMODE_7BIT, I2C_DUALADDRESS_DISABLE, OWN_ADDRESS_1_WRITE, OWN_ADDRESS_2, I2C_GENERALCALL_DISABLE, I2C_NOSTRETCH_ENABLE, TIMING);

	Enable_NVIC_I2C(&I2C2_Handle, I2C2_EV_IRQn, I2C2_PREEMPT_PRIORITY, I2C2_SUB_PRIORITY);
}

void HAL_I2C2_ListenCpltCallback(I2C_HandleTypeDef* I2C_Handle,
								 uint8_t RW)
{
	if(RW == 0)
	{
		int i = 0;
		for(i = 0;i < 3;i++)
		{
			pBuf_TX_I2C1[i] = MOTORFEED[i].RotorLock;
		}
		i = 0;
		for(i = 0;i < 3;i++)
		{
			DBL.d = MOTORSTATE[i].RPM;
			int j = 0;
			for(j = 0;j < sizeof(double);j++)
			{
				pBuf_TX_I2C1[(i * 8) + j + 3] = DBL.i[j];
			}
		}
		i = 0;
		for(i = 0;i < INCOMING_SIZE_BUS2;i++)
		{
			pBuf_TX_I2C1[i + 3 + (3 * sizeof(double))] = pBuf_RX_I2C2[i];
		}
	}
	else
	{
		//Do something.
	}
}

void I2C2_EV_IRQHandler()
{
	Clear_Pending_NVIC(I2C2_EV_IRQn);
	Disable_NVIC_I2C(&I2C2_Handle, I2C2_EV_IRQn);

	uint8_t RW = I2Cx_Run_MSP(&I2C2_Handle, pBuf_RX_I2C2, pBuf_TX_I2C2);

	while(!((I2C2_Handle.Instance->ISR) & 0x00000020));

	I2C2_Handle.Instance->CR1 &= 0xFFFFFFFE;
	if((I2C2_Handle.Instance->CR1 & 0x00000001) == 0x00000000)
	{
		I2C2_Handle.Instance->CR1 |= 0x00000001;
	}

	Enable_NVIC_I2C(&I2C2_Handle, I2C2_EV_IRQn, I2C2_PREEMPT_PRIORITY, I2C2_SUB_PRIORITY);
	Clear_Pending_NVIC(I2C2_EV_IRQn);

	HAL_I2C2_ListenCpltCallback(&I2C2_Handle, RW);
}
