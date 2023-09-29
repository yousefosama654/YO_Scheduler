 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Yousef Osama
 ******************************************************************************/
#include "Port.h"

/* PB structure used with Port_Init API */
const Port_ConfigType  Port_ConfigType_PB={
                                           PORT_PortA , PORT_Pin0, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortA , PORT_Pin1, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortA , PORT_Pin2, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortA , PORT_Pin3, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortA , PORT_Pin4, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortA , PORT_Pin5, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortA , PORT_Pin6, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortA , PORT_Pin7, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,

                                           PORT_PortB , PORT_Pin0, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortB , PORT_Pin1, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortB , PORT_Pin2, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortB , PORT_Pin3, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortB , PORT_Pin4, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortB , PORT_Pin5, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortB , PORT_Pin6, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortB , PORT_Pin7, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,

                                           PORT_PortC , PORT_Pin0, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortC , PORT_Pin1, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortC , PORT_Pin2, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortC , PORT_Pin3, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortC , PORT_Pin4, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortC , PORT_Pin5, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortC , PORT_Pin6, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortC , PORT_Pin7, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,

                                           PORT_PortD , PORT_Pin0, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortD , PORT_Pin1, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortD , PORT_Pin2, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortD , PORT_Pin3, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortD , PORT_Pin4, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortD , PORT_Pin5, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortD , PORT_Pin6, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortD , PORT_Pin7, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,

                                           PORT_PortE , PORT_Pin0, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortE , PORT_Pin1, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortE , PORT_Pin2, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortE , PORT_Pin3, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortE , PORT_Pin4, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortE , PORT_Pin5, PIN_IN, OFF, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,

                                           PORT_PortF , PORT_Pin0, PIN_IN, PULL_UP, PIN_LEVEL_LOW , PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortF , PORT_Pin1, PIN_OUT, OFF, PIN_LEVEL_LOW, PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortF , PORT_Pin2, PIN_IN, OFF, PIN_LEVEL_LOW, PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortF , PORT_Pin3, PIN_IN, OFF, PIN_LEVEL_LOW, PIN_MODE_DIO , STD_ON, STD_ON,
                                           PORT_PortF , PORT_Pin4, PIN_IN, PULL_UP, PIN_LEVEL_LOW,  PIN_MODE_DIO , STD_ON, STD_ON

};
