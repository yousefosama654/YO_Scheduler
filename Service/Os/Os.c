/******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.c
 *
 * Description: Source file for Os Scheduler Based on Time Trigger - Service Layer
 *
 * Author: Yousef Osama
 *
 ******************************************************************************/

#include "Os.h"

volatile static uint8 ticks = 0;
volatile static boolean Os_Flag = FALSE;

/* count the Os ticks based on Systick IRQ every 20 ms*/
void Os_CountTicks(void)
{
    ticks += Os_TICK_BASE;
    Os_Flag = TRUE;
}

/* MCU Modules Init (Port-Dio-Systick) to start the system */
void Os_Init(void)
{
    Enable_Exceptions();
    Port_Init(&Port_ConfigType_PB);
    Dio_Init(&Dio_Configuration);
    Systick_SetCallback(Os_CountTicks);
}

/* Start the Os in the app layer */
void Os_Start(void)
{
    Os_Init();
    Os_Schedule();
}

/* Start the Os in the app layer */
void Os_Schedule(void)
{
    SysTick_Init(Os_TICK_BASE);
    while (1)
    {
        while (Os_Flag==FALSE);
        Os_Flag = FALSE;
        switch (ticks)
        {
        case 100:
        case 20:
            Button_Task();
            break;
        case 80:
        case 40:
            Button_Task();
            Led_Task();
            break;
        case 60:
            Button_Task();
            break;
        case 120:
            ticks = 0;
            Led_Task();
            Button_Task();
            break;
        }
    }
}

void Button_Task(void)
{
    STATIC uint8 PrevState = BUTTON_Released;
    uint8 CurrState = Button_GetState();
    if (CurrState == BUTTON_Pressed && PrevState == BUTTON_Released)
    {
        Led_Toggle();
        PrevState = BUTTON_Pressed;
    }
    else if (CurrState == BUTTON_Released && PrevState == BUTTON_Pressed)
    {
        PrevState = BUTTON_Released;
    }
    else
    {
        /* Do Nothing */
    }
}
void Led_Task(void)
{
    Led_Refresh();
}
