 /******************************************************************************
 *
 * Module: APP
 *
 * File Name: main.c
 *
 * Description: Start The Application Layer.
 *
 * Author: Yousef Osama
 ******************************************************************************/
#include "Os.h"

int main(void)
{
    /*
     * Start the Os to Init the Peripherals and Start Schdeuling
     */
    Os_Start();
    return 0;
}
