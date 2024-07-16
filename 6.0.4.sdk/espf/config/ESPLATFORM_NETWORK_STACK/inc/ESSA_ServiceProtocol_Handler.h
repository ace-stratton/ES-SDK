/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __ESSA_SERVICEPROTOCOL_HANDLER_H__
#define __ESSA_SERVICEPROTOCOL_HANDLER_H__

/**
 * @addtogroup ESPS_I
 * @{
 *
 * @file    ESSA_ServiceProtocol_Handler.h
 * @brief   ESPS stack Service Protocol declarations
 *
 * @}
 */

#include "es_cdef.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_ServiceProtocol_Types.h"

// Data type which defines the respective ServiceProtocol NVM configuration data
typedef struct
{
    uint16_t nModuleType;                               // or DevName. From ESPLATFORM_COMMON\ESSAT_ModuleTypes.h
    uint16_t nModuleHWConfig;                           // Device specific, use 0 if not used
    uint16_t nModuleHWRevision;                         // Device specific, use 0 if not used
    char szModuleSerial[ESSASP_DEV_SERIAL_MAX_SIZE];
} sESSA_SP_Config_t;

// Put before stack initialization!
void ESSA_SP_Init(bool bAfterReset);
void ESSA_SP_Task();
void ESSA_SP_Exit();

#endif // #ifndef __ESSA_SERVICEPROTOCOL_HANDLER_H__
