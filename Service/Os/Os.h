 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.h
 *
 * Description: Header file for Os Scheduler Based on Time Trigger - Service Layer
 *
 * Author: Yousef Osama
 ******************************************************************************/
#ifndef SERVICE_OS_H_
#define SERVICE_OS_H_


#include "Button.h"
#include "Led.h"
#include "Port.h"
#include "Dio.h"
#include "Systick.h"

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions() __asm(" CPSIE I")

/*LCM of System Tasks Time*/
#define Os_TICK_BASE 20

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* MCU Modules Init (Port-Dio-Systick) to start the system */
void Os_Init(void);

/* Start the Os in the app layer */
void Os_Start(void);

/* Start the Os in the app layer */
void Os_Schedule(void);

/* Button Task supported by the app layer */
void Button_Task(void);

/* Led Task supported by the app layer */
void Led_Task(void);

/* count the Os ticks based on Systick IRQ every 20 ms*/
void Os_CountTicks(void);

#endif /* SERVICE_OS_H_ */
