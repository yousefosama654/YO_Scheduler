 /******************************************************************************
 *
 * Driver: Button
 *
 * File Name: Button.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller SW Button
 *
 * Author: Yousef Osama
 ******************************************************************************/

#ifndef ECUAL_BUTTON_H_
#define ECUAL_BUTTON_H_


#include "Dio.h"

/* Pull Up Connnection with the Button */
#define BUTTON_Pressed STD_OFF
#define BUTTON_Released STD_ON

#define SW1_CHANNEL_ID_INDEX         (uint8)0x01

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* checks the Button state every 20ms */
uint8 Button_GetState(void);


#endif /* ECUAL_BUTTON_BUTTON_H_ */
