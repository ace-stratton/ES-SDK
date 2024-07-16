/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*
 * datapool_cfg.c
 *
 *  Created on: Jun 29, 2021
 *      Author: Ivan Petrov
 */

#include "es_cdef.h"
#include <nvm_data_types.h>
#include <nvm_cfg.h>
#include "cmsis_gcc.h"
#include "nvm_block_ids.h"
#include "nvm_app_block_ids.h"
#ifdef COMM_RS485_MAC_LAYER_ENABLED
#include <esps_drv_def.h>
#include "ESPLATFORM_COMMON/ESSAT_ModuleTypes.h"
#endif // #ifdef COMM_RS485_MAC_LAYER_ENABLED
#include "TaskMonitor.h"
#include "drv_fram.h"

static osMutexId_t csMutexHandle = (osMutexId_t)NULL;

//
//  Data entries
//

#include "nvm_bootshared_defs.inc"
#include "nvm_app_defs.inc"

const sNvmBlockDescriptor_t aBlockConfig[NVM_BLOCK_MAX_COUNT] = {
#include "nvm_bootshared_blocks_init.inc"
#include "nvm_app_blocks_init.inc"
};

sNvmBlockDescriptorRunTime_t aBlockRTData[NVM_BLOCK_MAX_COUNT];

eCriticalSectionStatus_t
NVM_Cfg_EnterCriticalSection(void)
{
    eCriticalSectionStatus_t res = ECRITICALSECTIONSTATUS_ERROR;
    osStatus_t               mutexAcqStatus;

    if (osKernelGetState() == osKernelRunning)
    {
        // lazy init on first call if not already done
        if (csMutexHandle == NULL)
            csMutexHandle = osMutexNew((const osMutexAttr_t *)NULL);

        mutexAcqStatus = osMutexAcquire(csMutexHandle, CS_TIMEOUT_MS);

        switch (mutexAcqStatus)
        {
            case osOK:
                res = ECRITICALSECTIONSTATUS_OK;
                break;

            case osErrorTimeout:
                res = ECRITICALSECTIONSTATUS_TIMEOUT;
                break;

            default:
                res = ECRITICALSECTIONSTATUS_ERROR;
                break;
        }
    }
    else
    {
        __disable_irq();
        res = ECRITICALSECTIONSTATUS_OK;
    }

    return res;
}

eCriticalSectionStatus_t
NVM_Cfg_LeaveCriticalSection(void)
{
    eCriticalSectionStatus_t res = ECRITICALSECTIONSTATUS_ERROR;
    osStatus_t               mutexRelStatus;

    if (osKernelGetState() == osKernelRunning)
    {
        if (csMutexHandle != NULL)
        {
            mutexRelStatus = osMutexRelease(csMutexHandle);

            switch (mutexRelStatus)
            {
                case osOK:
                    res = ECRITICALSECTIONSTATUS_OK;
                    break;

                default:
                    res = ECRITICALSECTIONSTATUS_ERROR;
                    break;
            }
        }
    }
    else
    {
        __enable_irq();
        res = ECRITICALSECTIONSTATUS_OK;
    }

    return res;
}

bool
NVM_Cfg_Init(void)
{
    FRAM_Init();

    return true;
}

bool
NVM_Cfg_VerifyLayout(void)
{
    // no need to use critical sections here because this function is called
    // only at startup
    return (NvMLayoutVersion.sharedDataLayoutVersion ==
            cu16NvmBlockLayoutVersion);
}

void
NVM_Cfg_PrepareLayoutUpgrade(void)
{
    // this function gets executed before forcing defaults to NVM
    // for blocks which do not have pre-configured defaults, you can update
    // the corresponding RAM mirror structure here and it will get
    // forced-written to NVM
    NvMLayoutVersion.sharedDataLayoutVersion = cu16NvmBlockLayoutVersion;

#ifndef BOOTLOADER
    aBlockRTData[NVM_BLOCK_BOOTLAYOUTVERSION].bOverrideForceDefaults = true;
#endif // #ifndef (BOOTLOADER)

    aBlockRTData[NVM_BLOCK_BOOTDATA].bOverrideForceDefaults = false;
#ifdef COMM_RS485_MAC_LAYER_ENABLED
    aBlockRTData[NVM_BLOCK_MACCONFIG].bOverrideForceDefaults = false;
#endif // #ifdef COMM_RS485_MAC_LAYER_ENABLED
}

void
NVM_Cfg_ReportTaskAlive(void)
{
    TaskMonitor_IamAlive(TASK_NVM);
    vApplicationLowStackCheck(TASK_NVM);
}

bool
NVM_Cfg_WriteBlock(uint32_t u32Address, uint8_t *const pu8BlockData,
                   uint32_t u32BlockSize)
{
    return FRAM_WriteData(u32Address, u32BlockSize, (uint8_t *)pu8BlockData);
}

bool
NVM_Cfg_ReadBlock(uint32_t u32Address, uint8_t *const pu8BlockData,
                  uint32_t u32BlockSize)
{
    return FRAM_ReadData(u32Address, u32BlockSize, (uint8_t *)pu8BlockData);
}

uint32_t
NVM_Cfg_GetMaxPhysBlockSize(void)
{
    return FRAM_RX_BUFF_SIZE;
}
