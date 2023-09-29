#include "Systick.h"
#include "tm4c123gh6pm_registers.h"

/*Pointer to call back function used in Systick interrupt Handler */
STATIC void (*callback_ptr)(void) = NULL_PTR;

/* Systick interrupt Handler */
void Systick_Handler(void)
{
    if (callback_ptr != NULL_PTR)
    {
        (*callback_ptr)();
    }
}

/* Enable the SystTick Timer to run using the System Clock and Count time in milli second */
void SysTick_Init(uint8 ticks_In_Millis)
{
    /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_CTRL_REG = 0;
    /* Set the Reload value with number of milli Second */
    SYSTICK_RELOAD_REG  = 15999 * ticks_In_Millis;
    /* Clear the Current Register value */
    SYSTICK_CURRENT_REG = 0;
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;
    /* Assign priority level 3 to the SysTick Interrupt */
    NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
}

/* Disable the SysTick Timer */
void SysTick_DeInit(void)
{
    /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_CTRL_REG = 0;
}

/* Set the call back function used in Systick interrupt Handler */
void Systick_SetCallback(void (*ptr)(void))
{
    callback_ptr = ptr;
}
