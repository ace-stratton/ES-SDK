/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Services
 * @{
 *
 * @defgroup Nvm
 * @{
 *
 * @file NvM.c
 * @brief NVM service core implementation
 *
 * Responsible to handle:
 * - Initial loading of NVM data from the persistent storage.
 * - Block integrity verification.
 * - NVM block access (read/write).
 *
 * @}
 * @}
 */

#include <string.h>
#include <nvm/inc/nvm.h>
#include <nvm_cfg.h>
#include "MACCRC32_Classic_Impl.h"
#include "trace.h"
#include "assertions.h"

#define CRC32_INIT_VALUE    ((uint32_t)0xFFFFFFFF)
#define CRC_PROTECTED       (true)
#define CRC32_SIZE          (sizeof(uint32_t))
#define NVM_TRACE_SIGNATURE (const char *)"[NVM]"

typedef enum
{
    EDPOPSRESULT_OK,
    EDPOPSRESULT_ERROR,
    EDPOPSRESULT_DEFAULTS_RESTORED,
    EDPOPSRESULT_CRC_MISMATCH,
    EDPRESULT_MAX
} eDpOpsResult_t;

static bool
fs_bNvmWriteBlock(const uint32_t u32Address, uint8_t *const pBuf,
                  const uint32_t u32BufSize, const bool bCrcProtected);

static eDpOpsResult_t
fs_eNvmReadBlock(const uint32_t u32Address, uint8_t *const pBuf,
                 const uint32_t u32BufSize, const void *const pBufDefaults,
                 const bool bCrcProtected);

static bool
NvmStoreBlock(const uint16_t u16BlockId, uint8_t *const pBuf);

void
Nvm_Init(void)
{
    uint32_t u32CurrentAddress = START_ADDRESS;

    if (NVM_Cfg_Init())
    {
        for (uint16_t u16Idx = 0U; u16Idx < NVM_BLOCK_MAX_COUNT; u16Idx++)
        {
            CRIT_ASSERT(aBlockConfig[u16Idx].u32Size <=
                       NVM_Cfg_GetMaxPhysBlockSize());

            if ((aBlockConfig[u16Idx].u16ConfigBitfield &
                 BLKCFG_FIXED_ADDRESS) == BLKCFG_FIXED_ADDRESS)
            {
                u32CurrentAddress = aBlockConfig[u16Idx].u32FixedAddress;
            }

            switch (aBlockConfig[u16Idx].eBlockType)
            {
                case EBLOCKTYPE_REDUNDANT:
                    for (uint8_t u8Idx = 0U;
                         u8Idx < CDEF_ELEMENT_COUNT(
                                     aBlockRTData[u16Idx].u32BlockAddress);
                         u8Idx++)
                    {
                        aBlockRTData[u16Idx].u32BlockAddress[u8Idx] =
                            u32CurrentAddress;
                        u32CurrentAddress += aBlockConfig[u16Idx].u32Size;
                    }
                    break;

                default:
                    aBlockRTData[u16Idx].u32BlockAddress[0U] =
                        u32CurrentAddress;
                    u32CurrentAddress += aBlockConfig[u16Idx].u32Size;
                    break;
            }

            aBlockRTData[u16Idx].bDefaultsRestored      = false;
            aBlockRTData[u16Idx].bRamMirrorDirty        = false;
            aBlockRTData[u16Idx].bOverrideForceDefaults = false;
        }
    }
    else
    	ES_TRACE_DEBUG("%s init error\r\n", NVM_TRACE_SIGNATURE);
}

void
Nvm_Load(void)
{
    eDpOpsResult_t res;
    uint8_t        u8Idx;
    bool           bCrcProtected;

    for (uint16_t u16Idx = 0U; u16Idx < NVM_BLOCK_MAX_COUNT; u16Idx++)
    {
    	ES_TRACE_DEBUG("%s loading block %d...\r\n", NVM_TRACE_SIGNATURE, u16Idx);

        if (NULL == aBlockConfig[u16Idx].pBufDefaults)
        {
        	ES_TRACE_DEBUG("FLASH ROM defaults not provided for block id %d!\r\n",
                      u16Idx);
        }

        bCrcProtected = (aBlockConfig[u16Idx].u16ConfigBitfield &
                         BLKCFG_CRC_PROTECTED) == BLKCFG_CRC_PROTECTED;
        switch (aBlockConfig[u16Idx].eBlockType)
        {
            case EBLOCKTYPE_REDUNDANT:
                u8Idx = 0U;

                res = fs_eNvmReadBlock(
                    aBlockRTData[u16Idx].u32BlockAddress[u8Idx],
                    aBlockConfig[u16Idx].pRamMirrorBuf,
                    aBlockConfig[u16Idx].u32Size,
                    aBlockConfig[u16Idx].pBufDefaults, bCrcProtected);

                aBlockRTData[u16Idx].bDefaultsRestored =
                    (res == EDPOPSRESULT_DEFAULTS_RESTORED);
                ES_TRACE_DEBUG("%s  NvmReadBlock result -> [%d]...\r\n",
                          NVM_TRACE_SIGNATURE, res);

                while ((++u8Idx < CDEF_ELEMENT_COUNT(
                                      aBlockRTData[u16Idx].u32BlockAddress)) &&
                       (res != EDPOPSRESULT_OK))
                {
                        res = fs_eNvmReadBlock(
                        aBlockRTData[u16Idx].u32BlockAddress[u8Idx],
                        aBlockConfig[u16Idx].pRamMirrorBuf,
                        aBlockConfig[u16Idx].u32Size,
                        aBlockConfig[u16Idx].pBufDefaults, bCrcProtected);

                    aBlockRTData[u16Idx].bDefaultsRestored =
                        (res == EDPOPSRESULT_DEFAULTS_RESTORED);
                    ES_TRACE_DEBUG(
                        "%s opted for redundant copy due to integrity failure "
                        "[%d] -> [%d]...\r\n",
                        NVM_TRACE_SIGNATURE, u8Idx, res);
                }
                break;

            case EBLOCKTYPE_SINGLE:
            default:
                res = fs_eNvmReadBlock(aBlockRTData[u16Idx].u32BlockAddress[0U],
                                       aBlockConfig[u16Idx].pRamMirrorBuf,
                                       aBlockConfig[u16Idx].u32Size,
                                       aBlockConfig[u16Idx].pBufDefaults,
                                       bCrcProtected);

                aBlockRTData[u16Idx].bDefaultsRestored =
                    (res == EDPOPSRESULT_DEFAULTS_RESTORED);
                ES_TRACE_DEBUG("%s  NvmReadBlock result -> [%d]...\r\n",
                          NVM_TRACE_SIGNATURE, res);
                break;
        }
    }

    // check layout constraints which are project-specific and force defaults if
    // something doesn't quite match
    if (!NVM_Cfg_VerifyLayout())
    {
    	ES_TRACE_DEBUG("%s  Layout verification failed! Forcing defaults...\r\n",
                  NVM_TRACE_SIGNATURE);
        NVM_Cfg_PrepareLayoutUpgrade();
        Nvm_Store(NVMSTORE_FORCEDEFAULTS);
    }
}

void
Nvm_Store(const bool bForceDefaults)
{
    NVM_Cfg_EnterCriticalSection();

    for (uint16_t u16Idx = 0U; u16Idx < NVM_BLOCK_MAX_COUNT; u16Idx++)
    {
        if (( false != aBlockRTData[u16Idx].bRamMirrorDirty) || bForceDefaults)
        {
            if ((bForceDefaults) && (aBlockConfig[u16Idx].pBufDefaults != NULL))
            {
                // apply defaults only if block defaults override switch not set
                if (!aBlockRTData[u16Idx].bOverrideForceDefaults)
                {
                    (void)memcpy(
                        (void *volatile)aBlockConfig[u16Idx].pRamMirrorBuf,
                        (const void *volatile)aBlockConfig[u16Idx].pBufDefaults,
                        aBlockConfig[u16Idx].u32Size);
                }
            }

            ES_TRACE_DEBUG("%s Storing block -> %d...\r\n", NVM_TRACE_SIGNATURE,
                      u16Idx);
            (void)NvmStoreBlock(
                u16Idx, (uint8_t *const)aBlockConfig[u16Idx].pRamMirrorBuf);
        }
    }

    NVM_Cfg_LeaveCriticalSection();
}

void
Nvm_RestoreBlockDefaults(const uint16_t u16BlockId)
{
    CRIT_ASSERT(u16BlockId < NVM_BLOCK_MAX_COUNT);

    if (aBlockConfig[u16BlockId].pBufDefaults != NULL)
    {
        // apply defaults only if block defaults override switch not set
        if (!aBlockRTData[u16BlockId].bOverrideForceDefaults)
        {
            (void)memcpy(
                (void *volatile)aBlockConfig[u16BlockId].pRamMirrorBuf,
                (const void *volatile)aBlockConfig[u16BlockId].pBufDefaults,
                aBlockConfig[u16BlockId].u32Size);
        }
    }

    ES_TRACE_DEBUG("%s Restoring defaults for block -> %d...\r\n",
              NVM_TRACE_SIGNATURE, u16BlockId);
    (void)NvmStoreBlock(u16BlockId,
                        (uint8_t *const)aBlockConfig[u16BlockId].pRamMirrorBuf);
}

void
Nvm_GetBlockById(uint16_t u16BlockId, void *const pBlockBuffer)
{
    if (u16BlockId < NVM_BLOCK_MAX_COUNT)
    {
        NVM_Cfg_EnterCriticalSection();
        (void)memcpy(pBlockBuffer, aBlockConfig[u16BlockId].pRamMirrorBuf,
                     aBlockConfig[u16BlockId].u32Size);
        NVM_Cfg_LeaveCriticalSection();
    }
}

void
Nvm_SetBlockById(uint16_t u16BlockId, void *const pBlockBuffer,
                 const bool bStoreImmediately)
{
    if (u16BlockId < NVM_BLOCK_MAX_COUNT)
    {
        NVM_Cfg_EnterCriticalSection();
        (void)memcpy(aBlockConfig[u16BlockId].pRamMirrorBuf, pBlockBuffer,
                     aBlockConfig[u16BlockId].u32Size);
        aBlockRTData[u16BlockId].bRamMirrorDirty = true;

        if (bStoreImmediately)
        {
        	ES_TRACE_DEBUG(
                "%s NvmSetBlockById() block id %d immediate store "
                "triggered\r\n",
                NVM_TRACE_SIGNATURE, u16BlockId);
            NvmStoreBlock(u16BlockId, pBlockBuffer);
        }
        else
        	ES_TRACE_DEBUG(
                "%s NvmSetBlockById() block id %d scheduled for storage "
                "later\r\n",
                NVM_TRACE_SIGNATURE, u16BlockId);

        NVM_Cfg_LeaveCriticalSection();
    }
    else
    	ES_TRACE_DEBUG("%s NvmSetBlockById() invalid block ID specified -> %d\r\n",
                  NVM_TRACE_SIGNATURE, u16BlockId);
}

static eDpOpsResult_t
fs_eNvmReadBlock(const uint32_t u32Address, uint8_t *const pBuf,
                 const uint32_t u32BufSize, const void *const pBufDefaults,
                 const bool bCrcProtected)
{
    bool           bReadSuccessful;
    eDpOpsResult_t eRes = EDPOPSRESULT_ERROR;

    CRIT_ASSERT(pBuf != NULL);
    CRIT_ASSERT(u32BufSize > 0U);

    bReadSuccessful =
        NVM_Cfg_ReadBlock(u32Address, (uint8_t *)pBuf, u32BufSize);

    if (bReadSuccessful)
    {
        if (bCrcProtected)
        {
            CRIT_ASSERT(u32BufSize > CRC32_SIZE);

            uint32_t u32CalcCrc = MACCRC32_Calc32(pBuf, u32BufSize - CRC32_SIZE,
                                                  CRC32_INIT_VALUE);

            if (u32CalcCrc != *((uint32_t *)&pBuf[u32BufSize - CRC32_SIZE]))
            {
                eRes = EDPOPSRESULT_CRC_MISMATCH;

                // load FLASH defaults if available...
                if (pBufDefaults != NULL)
                {
                    (void)memcpy(pBuf, pBufDefaults, u32BufSize);
                    eRes = EDPOPSRESULT_DEFAULTS_RESTORED;
                }

                ES_TRACE_DEBUG("%s NvmReadBlock(%08x) CRC failed\r\n",
                          NVM_TRACE_SIGNATURE, u32Address);
            }
            else
            {
                eRes = EDPOPSRESULT_OK;
                ES_TRACE_DEBUG("%s NvmReadBlock(%08x) CRC OK!\r\n",
                          NVM_TRACE_SIGNATURE, u32Address);
            }
        }
        else
        	ES_TRACE_DEBUG("%s NvmReadBlock(%08x) CRC check not configured\r\n",
                      NVM_TRACE_SIGNATURE, u32Address);
    }
    else
    {
        // load FLASH defaults if available...
        if (pBufDefaults != NULL)
        {
            (void)memcpy(pBuf, pBufDefaults, u32BufSize);
            eRes = EDPOPSRESULT_DEFAULTS_RESTORED;
        }
    }

    return eRes;
}

static bool
fs_bNvmWriteBlock(const uint32_t u32Address, uint8_t *const pBuf,
                  const uint32_t u32BufSize, const bool bCrcProtected)
{
    CRIT_ASSERT(pBuf != NULL);
    CRIT_ASSERT(u32BufSize > 0U);

    if (bCrcProtected)
    {
        CRIT_ASSERT(u32BufSize > CRC32_SIZE);

        uint32_t u32CalcCrc =
            MACCRC32_Calc32(pBuf, u32BufSize - CRC32_SIZE, CRC32_INIT_VALUE);

        *((uint32_t *)&pBuf[u32BufSize - CRC32_SIZE]) = u32CalcCrc;
    }

    ES_TRACE_DEBUG("%s NvmWriteBlock(%08x) triggered\r\n", NVM_TRACE_SIGNATURE,
              u32Address);
    return NVM_Cfg_WriteBlock(u32Address, (uint8_t *)pBuf, u32BufSize);
}

static bool
NvmStoreBlock(const uint16_t u16BlockId, uint8_t *const pBuf)
{
    bool bWriteSuccessful = false;
    bool bCrcProtected;
    CRIT_ASSERT(u16BlockId < NVM_BLOCK_MAX_COUNT);
    CRIT_ASSERT(pBuf != NULL);

    bCrcProtected = (aBlockConfig[u16BlockId].u16ConfigBitfield &
                     BLKCFG_CRC_PROTECTED) == BLKCFG_CRC_PROTECTED;

    switch (aBlockConfig[u16BlockId].eBlockType)
    {
        case EBLOCKTYPE_REDUNDANT:
            for (uint8_t u8Idx = 0U;
                 u8Idx <
                 CDEF_ELEMENT_COUNT(aBlockRTData[u16BlockId].u32BlockAddress);
                 u8Idx++)
            {
                bWriteSuccessful = fs_bNvmWriteBlock(
                    aBlockRTData[u16BlockId].u32BlockAddress[u8Idx],
                    (uint8_t *const)pBuf, aBlockConfig[u16BlockId].u32Size,
                    bCrcProtected);

                aBlockRTData[u16BlockId].bRamMirrorDirty = !bWriteSuccessful;
            }
            break;

        case EBLOCKTYPE_SINGLE:
        default:
            bWriteSuccessful = fs_bNvmWriteBlock(
                aBlockRTData[u16BlockId].u32BlockAddress[0U],
                (uint8_t *const)pBuf, aBlockConfig[u16BlockId].u32Size,
                bCrcProtected);

            aBlockRTData[u16BlockId].bRamMirrorDirty = !bWriteSuccessful;
            break;
    }

    return bWriteSuccessful;
}
