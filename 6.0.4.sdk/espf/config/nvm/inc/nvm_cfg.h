/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef NVM_PRIVATE_INC_NVM_CFG_H_
#define NVM_PRIVATE_INC_NVM_CFG_H_

#include "es_cdef.h"
#include "cmsis_os2.h"
#include "nvm_types.h"

#define MAX_STORAGE_SIZE ((uint32_t)(256 * 1024)) // FRAM chip size in bytes

typedef enum
{
   ECRITICALSECTIONSTATUS_OK,
   ECRITICALSECTIONSTATUS_TIMEOUT,
   ECRITICALSECTIONSTATUS_ERROR,
   ECRITICALSECTIONSTATUS_MAX
} eCriticalSectionStatus_t;

extern const sNvmBlockDescriptor_t aBlockConfig[];
extern sNvmBlockDescriptorRunTime_t aBlockRTData[];

bool NVM_Cfg_Init(void);
bool NVM_Cfg_VerifyLayout(void);
void NVM_Cfg_PrepareLayoutUpgrade(void);
void NVM_Cfg_ReportTaskAlive(void);
bool NVM_Cfg_WriteBlock(uint32_t u32Address, uint8_t * const pu8BlockData, uint32_t u32BlockSize);
bool NVM_Cfg_ReadBlock(uint32_t u32Address, uint8_t * const pu8BlockData, uint32_t u32BlockSize);
eCriticalSectionStatus_t NVM_Cfg_EnterCriticalSection(void);
eCriticalSectionStatus_t NVM_Cfg_LeaveCriticalSection(void);
uint32_t NVM_Cfg_GetMaxPhysBlockSize(void);

#endif /* NVM_PRIVATE_INC_NVM_CFG_H_ */
