 /******************************************************************************
 *
 * Driver: Led
 *
 * File Name: Led.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller Led
 *
 * Author: Yousef Osama
 ******************************************************************************/
#ifndef HAL_LED_H_
#define HAL_LED_H_

#include "Dio.h"

/* Positive Logic Led */
#define LED_ON      STD_ON
#define LED_OFF     STD_OFF

#define LED_CHANNEL_ID_INDEX        (uint8)0x00

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Turn ON the Led */
void Led_ON(void);

/* Turn OFF the Led */
void Led_OFF(void);

/* Toggle the Led */
void Led_Toggle(void);

/* Read  Led Value and write it to the Led again */
void Led_Refresh(void);

#endif /* HAL_LED_H_ */
