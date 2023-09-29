#include "Std_Types.h"

#ifndef MCAL_GPT_SYSTICK_H_
#define MCAL_GPT_SYSTICK_H_


/*******************************************************************************
 *                              Systick NVIC Macros                            *
 *******************************************************************************/
#define SYSTICK_PRIORITY_MASK 0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY 3
#define SYSTICK_PRIORITY_BITS_POS 29


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Systick interrupt Handler */
void Systick_Handler(void);

/* Enable the SystTick Timer and Count time in milli second */
void SysTick_Init(uint8 ticks_In_Millis);

/* Disable the SysTick Timer */
void SysTick_DeInit(void);

/* Set the call back function used in Systick interrupt Handler */
void Systick_SetCallback(void (*ptr)(void));

#endif /* MCAL_GPT_SYSTICK_H_ */
