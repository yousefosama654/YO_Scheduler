 /******************************************************************************
 *
 * Driver: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller Led
 *
 * Author: Yousef Osama
 ******************************************************************************/
#include "Led.h"

/* Turn ON the Led */
void Led_ON(void)
{
    Dio_WriteChannel(LED_CHANNEL_ID_INDEX, LED_ON);
}

/* Turn OFF the Led */
void Led_OFF(void)
{
    Dio_WriteChannel(LED_CHANNEL_ID_INDEX, LED_OFF);
}

/* Toggle the Led */
void Led_Toggle(void)
{
    Dio_FlipChannel(LED_CHANNEL_ID_INDEX);
}

/* Read  Led Value and write it to the Led again */
void Led_Refresh(void)
{
    uint8 LedValue=Dio_ReadChannel(LED_CHANNEL_ID_INDEX);
    Dio_WriteChannel(LED_CHANNEL_ID_INDEX, LedValue);
}
