/*
 * PARIKSHIT STUDENT SATELLITE TEAM
 * MANIPAL INSTITUTE OF TECHNOLOGY
 * FILE: app.h
 * TYPE: APPLICATION (HEADER)
 * MCU: STM32L431CC
 * DEVELOPING SUB-SYSTEM: ON-BOARD DATA HANDLING SUB-SYSTEM
 * DEVELOPER: KRISHNA BIRLA
 */

#ifndef TERTPCB_BSP_APP_H
#define TERTPCB_BSP_APP_H

#include "BSP_GENERAL.h"
#include "BSP_GPIO.h"
#include "BSP_TIMER.h"
#include "BSP_RCC.h"
#include "BSP_I2C.h"
#include "BSP_I2C_ARM.h"
#include "BSP_I2C_MSP.h"
#include "BSP_IC.h"
#include "BSP_OC.h"
#include "BSP_OCPC.h"
#include "BSP_PCA.h"
#include "BSP_GLOBAL.h"
#include "BSP_WWDG.h"

void Code_Life_Start_Init();
uint8_t All_Systems_Online();
void Eat_Sleep_Code_Repeat();
void Check_For_Rotor_Lock();

#endif /* TERTPCB_BSP_APP_H */
