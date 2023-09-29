 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Yousef Osama
 ******************************************************************************/
#ifndef PORT_PORT_H_
#define PORT_PORT_H_


/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID                 (1000U)

/* Port Module Id */
#define PORT_MODULE_ID                 (124U)

/* Instance Id */
#define PORT_INSTANCE_ID               (0U)

/* Module Version 1.0.0 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.0.3 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)


/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Det Modules */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
 || (PORT_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
 || (PORT_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Initialization */
#define PORT_INIT_SID                     (uint8)0x00

/* Service ID for PORT SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID        (uint8)0x01

/* Service ID for PORT Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID   (uint8)0x02

/* Service ID for PORT Get Version Information */
#define PORT_GET_VERSION_INFO_SID         (uint8)0x03

/* Service ID for PORT Set Pin Mode */
 #define PORT_SET_PIN_MODE_SID             (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                    (uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE       (uint8)0x0B

/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                 (uint8)0x0C

/* API Port_SetPinMode service called when Port Pin Mode passed not valid */
#define PORT_E_PARAM_INVALID_MODE           (uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE            (uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT                       (uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Macros for Port Status */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)
#define MAGIC_COMMIT_REG_VAL            (0x4C4F434B)

#define PTR_TO_REG(X) (*((volatile unsigned long *)X))

/* Description: Data type for the symbolic number of a port pin */
typedef uint8 Port_PinType;

/* Description: Different port pin modes */
typedef uint8 Port_PinModeType;

/* Description: Possible directions of a Port Pin */
typedef enum
{
    PIN_IN,
    PIN_OUT
}Port_PinDirectionType;

/* Description: Possible Resistance Connections of a Port Pin */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN,
}Port_InternalResistor;

typedef enum
{
    PIN_LEVEL_LOW,
    PIN_LEVEL_HIGH,
}Port_PinLevelValue;

/* Port Pin Mode from Mode list for use with Port_Init() function */
typedef enum
{
    PIN_MODE_ADC,
    PIN_MODE_ALT1,
    PIN_MODE_ALT2,
    PIN_MODE_ALT3,
    PIN_MODE_ALT4,
    PIN_MODE_ALT5,
    PIN_MODE_ALT6,
    PIN_MODE_ALT7,
    PIN_MODE_ALT8,
    PIN_MODE_ALT9,
    PIN_MODE_ALT10,
    PIN_MODE_ALT11,
    PIN_MODE_ALT12,
    PIN_MODE_ALT13,
    PIN_MODE_ALT14,
    PIN_MODE_ALT15,
    PIN_MODE_DIO,
} Port_PinInitialMode;

typedef struct
{
    uint8 Port_Num;                     /* PortA, PortB, PortC, ..                  */
    uint8 Pin_Num;                      /* PA0, PA1, ... , PF3, PF4                 */
    Port_PinDirectionType Pin_Direction;    /* PORT_PIN_IN, PORT_PIN_OUT                */
    Port_InternalResistor Pin_Resistor;     /* OFF,PULL_UP,PULL_DOWN                    */
    Port_PinLevelValue Pin_InitialValue;   /* PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH   */
    Port_PinInitialMode Pin_InitialMode;   /* e.g. PORT_PIN_MODE_DIO                   */
    uint8 Pin_DirectionChangeable;           /* STD_ON,STD_OFF                           */
    uint8 Pin_ModeChangeable;          /* STD_ON,STD_OFF                           */
}Port_ConfigPin;
typedef struct
{
    Port_ConfigPin Board_Pins[PORT_CONFIGURED_PINS];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for Initializes the Port Driver module*/
void Port_Init( const Port_ConfigType* ConfigPtr );

/* Function for Sets the port pin direction*/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/* Function for Refreshes port direction*/
void Port_RefreshPortDirection( void );

/* Function for Returns the version information of this module*/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

/* Function for Sets the port pin mode*/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
#include "Port_PBcfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBcfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_PBcfg.h does not match the expected version"
#endif


#endif /* PORT_PORT_H_ */



