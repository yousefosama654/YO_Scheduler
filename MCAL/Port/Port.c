 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Yousef Osama
 ******************************************************************************/

#include "Port.h"

/* Included the Regsiters of Base Ports and Offsets in Tiva-C */
#include "Port_Regs.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC Port_ConfigPin *PortConfigTypeLocal = NULL_PTR;
STATIC uint8 PortStatusLocal = PORT_NOT_INITIALIZED;

STATIC uint32* Port_GetPortReg(uint8 Port_Num)
{
    uint32 *Port_Ptr = NULL_PTR;
    switch (Port_Num)
    {
    case PORT_PortA:
        Port_Ptr = (uint32*) GPIO_PORTA_BASE_ADDRESS;
        break;
    case PORT_PortB:
        Port_Ptr = (uint32*) GPIO_PORTB_BASE_ADDRESS;
        break;
    case PORT_PortC:
        Port_Ptr = (uint32*) GPIO_PORTC_BASE_ADDRESS;
        break;
    case PORT_PortD:
        Port_Ptr = (uint32*) GPIO_PORTD_BASE_ADDRESS;
        break;
    case PORT_PortE:
        Port_Ptr = (uint32*) GPIO_PORTE_BASE_ADDRESS;
        break;
    case PORT_PortF:
        Port_Ptr = (uint32*) GPIO_PORTF_BASE_ADDRESS;
        break;
    default:
        break;
    }
    return Port_Ptr;
}
STATIC boolean Port_CheckJTAG(Port_PinType Pin)
{
    if ((PortConfigTypeLocal[Pin].Port_Num == PORT_PortC)
            && ((PortConfigTypeLocal[Pin].Pin_Num >= 0)
                    || (PortConfigTypeLocal[Pin].Pin_Num <= 3)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to configuration set
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Port module.
 ************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr)
{
#if ((PORT_DEV_ERROR_DETECT==STD_ON))
    if (ConfigPtr == NULL_PTR)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
        PORT_E_PARAM_CONFIG);
    }
    else
    {
        /* Do Nothing */
    }
#endif

    PortStatusLocal = PORT_INITIALIZED;
    PortConfigTypeLocal = (Port_ConfigPin*) ConfigPtr->Board_Pins;

    for (Port_PinType i = 0; i < PORT_CONFIGURED_PINS; i++)
    {

        volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        volatile uint32 delay = 0;

        /* Get The port Address*/
        PortGpio_Ptr = Port_GetPortReg(PortConfigTypeLocal[i].Port_Num);

        /* Enable The port Clock*/
//        SYSCTL_REGCGC2_REG |= (1<<PortConfigTypeLocal[i].Port_Num);
        SET_BIT(PTR_TO_REG (SYSCTL_REGCGC2_REG_BASE_ADDRESS),
                PortConfigTypeLocal[i].Port_Num);
        delay = SYSCTL_REGCGC2_REG_BASE_ADDRESS;

        if (Port_CheckJTAG(i))
        {
            /*Do Nothing This is the JTAG Pins*/
            continue;
        }

        else if ((PortConfigTypeLocal[i].Port_Num == PORT_PortF
                && PortConfigTypeLocal[i].Pin_Num == 0)
                || (PortConfigTypeLocal[i].Port_Num == PORT_PortD
                        && PortConfigTypeLocal[i].Pin_Num == 7))
        {
            /* Unlock the GPIOCR register */
            PTR_TO_REG (((volatile uint8*)PortGpio_Ptr + PORT_LOCK_REG_OFFSET)) =
                    MAGIC_COMMIT_REG_VAL;
            SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_COMMIT_REG_OFFSET)),
                    PortConfigTypeLocal[i].Pin_Num);
        }
        /*Set The Initial Mode in Pin I*/
        Port_SetPinMode(i, PortConfigTypeLocal[i].Pin_InitialMode);

        if (PortConfigTypeLocal[i].Pin_Direction == PIN_IN)
        {
            CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_DIR_REG_OFFSET)),
                      PortConfigTypeLocal[i].Pin_Num);
            switch (PortConfigTypeLocal[i].Pin_Resistor)
            {
            case OFF:
                /* Do Nothing */
                CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_PULL_UP_REG_OFFSET)),
                          PortConfigTypeLocal[i].Pin_Num);
                CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_PULL_DOWN_REG_OFFSET)),
                          PortConfigTypeLocal[i].Pin_Num);
                break;
            case PULL_UP:
                SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_PULL_UP_REG_OFFSET)),
                        PortConfigTypeLocal[i].Pin_Num);
                CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_PULL_DOWN_REG_OFFSET)),
                          PortConfigTypeLocal[i].Pin_Num);
                break;
            case PULL_DOWN:
                SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_PULL_DOWN_REG_OFFSET)),
                        PortConfigTypeLocal[i].Pin_Num);
                CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_PULL_UP_REG_OFFSET)),
                          PortConfigTypeLocal[i].Pin_Num);
                break;
            default:
                break;
            }
        }
        else
        {
            SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_DIR_REG_OFFSET)),
                    PortConfigTypeLocal[i].Pin_Num);
            if (PortConfigTypeLocal[i].Pin_InitialValue == PIN_LEVEL_LOW)
            {
                CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_DATA_REG_OFFSET)),
                          PortConfigTypeLocal[i].Pin_Num);
            }
            else
            {
                SET_BIT(PTR_TO_REG(((volatile uint8*)PortGpio_Ptr+PORT_DATA_REG_OFFSET)),
                        PortConfigTypeLocal[i].Pin_Num);
            }
        }
    }

}

/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Sets the port pin direction.
 ************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
#if((PORT_DEV_ERROR_DETECT==STD_ON))
    if (Pin >= PORT_CONFIGURED_PINS)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_PARAM_PIN);
    }
    else
    {
        /*Do Nothing*/
    }
    if (PortConfigTypeLocal[Pin].Pin_DirectionChangeable == STD_OFF)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else
    {
        /*Do Nothing*/
    }
    if (PortStatusLocal == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_UNINIT);
    }
    else
    {
        /*Do Nothing*/
    }
#endif
    volatile uint32 *PortGpio_Ptr = Port_GetPortReg(
            PortConfigTypeLocal[Pin].Port_Num);
    if (Port_CheckJTAG(Pin))
    {
        /*Do Nothing This is the JTAG Pins*/
    }
    else
    {
        if (Direction == PIN_IN)
        {
            CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_DIR_REG_OFFSET)),
                      PortConfigTypeLocal[Pin].Pin_Num);
        }
        else
        {
            SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_DIR_REG_OFFSET)),
                    PortConfigTypeLocal[Pin].Pin_Num);
        }
    }

}
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Refreshes port direction.
 ************************************************************************************/
void Port_RefreshPortDirection(void)
{
#if ((PORT_DEV_ERROR_DETECT==STD_ON))
    if (PortStatusLocal == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_REFRESH_PORT_DIRECTION_SID,
                        PORT_E_UNINIT);
    }
#endif
    for (Port_PinType i = 0; i < PORT_CONFIGURED_PINS; i++)
    {
        volatile uint32 *PortGpio_Ptr = Port_GetPortReg(
                PortConfigTypeLocal[i].Port_Num);
        if (Port_CheckJTAG(i))
        {
            /*Do Nothing This is the JTAG Pins*/
            continue;
        }
        else
        {
            if (PortConfigTypeLocal[i].Pin_DirectionChangeable == STD_ON)
            {
                if (PortConfigTypeLocal[i].Pin_Direction == PIN_IN)
                {
                    CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_DIR_REG_OFFSET)),
                              PortConfigTypeLocal[i].Pin_Num);
                }
                else
                {
                    SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_DIR_REG_OFFSET)),
                            PortConfigTypeLocal[i].Pin_Num);
                }
            }
            else
            {
                /*Do Nothing*/
            }
        }
    }
}

/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Returns the version information of this module.
 ************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if ((PORT_DEV_ERROR_DETECT==STD_ON))
    if (versioninfo == NULL_PTR)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_VERSION_INFO_API,
                        PORT_E_PARAM_POINTER);
    }
    else
    {
        /* Do Nothing */
    }
#endif
    versioninfo->vendorID = PORT_VENDOR_ID;
    versioninfo->moduleID = PORT_MODULE_ID;
    versioninfo->sw_major_version = PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PORT_SW_PATCH_VERSION;
}

#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin - Port Pin ID number, Mode - New Port Pin mode to be set on port pin
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode.
 ************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
#if(PORT_DEV_ERROR_DETECT==STD_ON)
    if (Pin >= PORT_CONFIGURED_PINS)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_PIN);
    }
    else
    {
        /*Do Nothing*/
    }
    if (PortConfigTypeLocal[Pin].Pin_ModeChangeable == STD_OFF)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID,
                        PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
        /*Do Nothing*/
    }
    if (PortStatusLocal == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(
        PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID,
                        PORT_E_UNINIT);
    }
    else
    {
        /*Do Nothing*/
    }
    if (Mode > PIN_MODE_DIO)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
        PORT_E_PARAM_INVALID_MODE);
    }
    else
    {
        /*Do Nothing*/
    }
#endif
    if (Port_CheckJTAG(Pin))
    {
        /*Do Nothing This is the JTAG Pins*/
    }
    else
    {

        volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        /* Get The port Address*/
        PortGpio_Ptr = Port_GetPortReg(PortConfigTypeLocal[Pin].Port_Num);



        switch (Mode)
        {
        case PIN_MODE_DIO:

            /*Disable Alternative pin*/
            CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET)),
                      PortConfigTypeLocal[Pin].Pin_Num);

            /* Enable Digital I/O */
            SET_BIT(PTR_TO_REG(((volatile uint8*)PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET)),
                    PortConfigTypeLocal[Pin].Pin_Num);

            /* Disable Analog  */
            CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET)),
                      PortConfigTypeLocal[Pin].Pin_Num);

            /* Clear the PMCx bits for this pin */
            PTR_TO_REG(((volatile uint8*)PortGpio_Ptr+PORT_CTL_REG_OFFSET)) &= ~(0x0000000F
                    << (PortConfigTypeLocal[Pin].Pin_Num * 4));

            break;
        case PIN_MODE_ADC:
            /*Disable Alternative pin*/
            CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET)),
                      PortConfigTypeLocal[Pin].Pin_Num);

            /* Enable Digital I/O */
            CLEAR_BIT(PTR_TO_REG(((volatile uint8*)PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET)),
                      PortConfigTypeLocal[Pin].Pin_Num);

            /* Disable Analog  */
            SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET)),
                    PortConfigTypeLocal[Pin].Pin_Num);

            /* Clear the PMCx bits for this pin */
            PTR_TO_REG(PortGpio_Ptr+PORT_CTL_REG_OFFSET) &= ~(0x0000000F
                    << (PortConfigTypeLocal[Pin].Pin_Num * 4));
            break;
        default:
            /*Disable Alternative pin*/
            SET_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET)),
                    PortConfigTypeLocal[Pin].Pin_Num);

            /* Enable Digital I/O */
            SET_BIT(PTR_TO_REG(((volatile uint8*)PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET)),
                    PortConfigTypeLocal[Pin].Pin_Num);

            /* Disable Analog  */
            CLEAR_BIT(PTR_TO_REG (((volatile uint8*)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET)),
                      PortConfigTypeLocal[Pin].Pin_Num);

            /* Clear the PMCx bits for this pin */
            PTR_TO_REG(((volatile uint8*)PortGpio_Ptr+PORT_CTL_REG_OFFSET)) &= ~(0x0000000F
                    << (PortConfigTypeLocal[Pin].Pin_Num * 4));

            /* Set the PMCx bits for this pin to specifi mode */
            PTR_TO_REG(((volatile uint8*)PortGpio_Ptr+PORT_CTL_REG_OFFSET)) |=
                    (PortConfigTypeLocal[Pin].Pin_InitialMode & 0x0000000F)
                            << (PortConfigTypeLocal[Pin].Pin_Num * 4);
            break;
        }

    }
}
