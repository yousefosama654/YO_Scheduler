 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.c
 *
 * Description:  Det stores the development errors reported by other modules.
 *               This source file is a STUB for the Det Module
 *
 * Author: Yousef Osama
 ******************************************************************************/
#include "Det.h"

uint16 Det_ModuleId = 0;
uint8 Det_InstanceId = 0;
uint8 Det_ApiId = 0;
uint8 Det_ErrorId = 0;

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                     uint8 ErrorId)
{
    Det_ModuleId = ModuleId;
    Det_InstanceId = InstanceId;
    Det_ApiId = ApiId;
    Det_ErrorId = ErrorId;
    return E_OK;
}
