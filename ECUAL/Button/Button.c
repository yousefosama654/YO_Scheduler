 /******************************************************************************
 *
 * Driver: Button
 *
 * File Name: Button.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller SW Button
 *
 * Author: Yousef Osama
 ******************************************************************************/
#include "Button.h"

/* checks the Button state every 20ms */
uint8 Button_GetState()
{
    STATIC uint8 Pressed_Counts = 0;
    STATIC uint8 Released_Counts = 0;
    if(Dio_ReadChannel(SW1_CHANNEL_ID_INDEX)==BUTTON_Pressed)
    {
        Pressed_Counts++;
        Released_Counts = 0;
    }
    else
    {
        Pressed_Counts=0;
        Released_Counts++;
    }
    if(Pressed_Counts==3)
    {
        Pressed_Counts = 0;
        Released_Counts = 0;
        return BUTTON_Pressed;
    }
    else if(Released_Counts==3)
    {
        Pressed_Counts = 0;
        Released_Counts = 0;
        return BUTTON_Released;
    }
    else
    {
        return BUTTON_Released;
    }
}
