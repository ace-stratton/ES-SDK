/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_pool.c
 * @brief    MAC Message pool implementation
 *
 * @}
 */

#include <string.h>

// External imports
#include "esps_drv_esps_stack.h"

#include "esps_drv_pool.h"
#include "esps_drv.h"
#include "esps_drv_exeh.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_MAC_POOL)

/// Find a free transfer pool for the MAC interface
sMACTXPoolEntry_t *MAC_POOL_psPoolTXNew(sMACInterfaceState_t * fp_psMACIntf)
{
    sMACTXPoolEntry_t *psEntry = NULL;

    uint8_t idx;

    bool freePoolFound = false;

    if((fp_psMACIntf == NULL)
       || ((uint8_t *) fp_psMACIntf->sTXCtx.pvMemPool != (uint8_t *) fp_psMACIntf->sTXCtx.aTxPool))
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        MAC_vEnterCriticalSection(fp_psMACIntf);

        for(idx = 0; idx < MAC_TXMEMORYPOOL_COUNT; idx++)
            if(fp_psMACIntf->sTXCtx.aTxPoolFreeMap[idx])
            {
                freePoolFound = true;

                // Mark entry as occupied
                fp_psMACIntf->sTXCtx.aTxPoolFreeMap[idx] = false;

                ++fp_psMACIntf->sTXCtx.txPoolsOccupied;
                MAC_Stats_storeEventMax(fp_psMACIntf->macStats,
                                        eMACStatId_MaxTxSlotsOccupied, fp_psMACIntf->sTXCtx.txPoolsOccupied);

                break;
            }

        if(!freePoolFound)
        {
            EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_SystemCallFailed);
        }
        else
            psEntry = (sMACTXPoolEntry_t *) & fp_psMACIntf->sTXCtx.aTxPool[idx];

        MAC_vLeaveCriticalSection(fp_psMACIntf);
    }

    return psEntry;
}

/// Return a free RX pool if any
sMACRXPoolEntry_t *MAC_POOL_psPoolRXNew(sMACInterfaceState_t * fp_psMACIntf)
{
    sMACRXPoolEntry_t *psEntry = NULL;

    uint8_t idx;

    bool freePoolFound = false;

    if((fp_psMACIntf == NULL)
       || ((uint8_t *) fp_psMACIntf->sRXCtx.pvMemPool != (uint8_t *) fp_psMACIntf->sRXCtx.aRxPool))
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        MAC_vEnterCriticalSection(fp_psMACIntf);

        for(idx = 0; idx < MAC_RXMEMORYPOOL_COUNT; idx++)
            if(fp_psMACIntf->sRXCtx.aRxPoolFreeMap[idx])
            {
                freePoolFound = true;

                // Mark the entry as occupied
                fp_psMACIntf->sRXCtx.aRxPoolFreeMap[idx] = false;
                // Keep track of the amount of pools occupied
                ++fp_psMACIntf->sRXCtx.rxPoolsOccupied;
                MAC_Stats_storeEventMax(fp_psMACIntf->macStats,
                                        eMACStatId_MaxRxSlotsOccupied, fp_psMACIntf->sRXCtx.rxPoolsOccupied);

                break;
            }

        if(!freePoolFound)
        {
            EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_SystemCallFailed);
        }
        else
        {
            // Return the pool
            psEntry = (sMACRXPoolEntry_t *) & fp_psMACIntf->sRXCtx.aRxPool[idx];
        }

        MAC_vLeaveCriticalSection(fp_psMACIntf);
    }

    return psEntry;
}

/// Stop using a TX pool
void MAC_POOL_vPoolTXFree(sMACInterfaceState_t * fp_psMACIntf, sMACTXPoolEntry_t * fp_psEntry)
{
    uint8_t idx;

    bool poolFound = false;

    if((fp_psMACIntf == NULL) || (fp_psEntry == NULL)
       || ((uint8_t *) fp_psMACIntf->sTXCtx.pvMemPool != (uint8_t *) fp_psMACIntf->sTXCtx.aTxPool))
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        MAC_vEnterCriticalSection(fp_psMACIntf);

        for(idx = 0; idx < MAC_TXMEMORYPOOL_COUNT; idx++)
            if((fp_psMACIntf->sTXCtx.aTxPoolFreeMap[idx] == false) &&
               (fp_psEntry == ((sMACTXPoolEntry_t *) & fp_psMACIntf->sTXCtx.aTxPool[idx])))
            {
                fp_psMACIntf->sTXCtx.aTxPoolFreeMap[idx] = true;
                poolFound = true;

                if(fp_psMACIntf->sTXCtx.txPoolsOccupied > 0)
                    --fp_psMACIntf->sTXCtx.txPoolsOccupied;

                break;
            }

        if(!poolFound)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_SystemCallFailed);
        }

        MAC_vLeaveCriticalSection(fp_psMACIntf);
    }
}

/// Stop using a RX pool
void MAC_POOL_vPoolRXFree(sMACInterfaceState_t * fp_psMACIntf, sMACRXPoolEntry_t * fp_psEntry)
{
    uint8_t idx;

    bool poolFound = false;

    if((fp_psMACIntf == NULL) || (fp_psEntry == NULL)
       || ((uint8_t *) fp_psMACIntf->sRXCtx.pvMemPool != (uint8_t *) fp_psMACIntf->sRXCtx.aRxPool))
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        MAC_vEnterCriticalSection(fp_psMACIntf);

        for(idx = 0; idx < MAC_RXMEMORYPOOL_COUNT; idx++)
            if((fp_psMACIntf->sRXCtx.aRxPoolFreeMap[idx] == false) &&
               (fp_psEntry == ((sMACRXPoolEntry_t *) & fp_psMACIntf->sRXCtx.aRxPool[idx])))
            {
                fp_psMACIntf->sRXCtx.aRxPoolFreeMap[idx] = true;
                poolFound = true;

                if(fp_psMACIntf->sRXCtx.rxPoolsOccupied > 0)
                    --fp_psMACIntf->sRXCtx.rxPoolsOccupied;

                break;
            }

        if(!poolFound)
        {
            EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_SystemCallFailed);
        }

        MAC_vLeaveCriticalSection(fp_psMACIntf);
    }
}

/// initialize the transmit and receive pools
bool MAC_POOL_bPoolInit(sMACInterfaceState_t * fp_psMACIntf)
{
    bool bInitOK = false;

    if(fp_psMACIntf == NULL)
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        // Set the values for the Transmit pools as all free
        fp_psMACIntf->sTXCtx.pvMemPool = (sMACTXPoolEntry_t *) fp_psMACIntf->sTXCtx.aTxPool;
        memset(fp_psMACIntf->sTXCtx.aTxPoolFreeMap, true, MAC_TXMEMORYPOOL_COUNT);
        fp_psMACIntf->sTXCtx.txPoolsOccupied = (uint8_t) 0;

        MAC_Stats_storeEventMax(fp_psMACIntf->macStats, eMACStatId_MaxTxSlotsOccupied,
                                fp_psMACIntf->sTXCtx.txPoolsOccupied);

        // Set the values for the Receive pools as all free
        fp_psMACIntf->sRXCtx.pvMemPool = (sMACRXPoolEntry_t *) fp_psMACIntf->sRXCtx.aRxPool;
        memset(fp_psMACIntf->sRXCtx.aRxPoolFreeMap, true, MAC_RXMEMORYPOOL_COUNT);
        fp_psMACIntf->sRXCtx.rxPoolsOccupied = (uint8_t) 0;

        MAC_Stats_storeEventMax(fp_psMACIntf->macStats, eMACStatId_MaxRxSlotsOccupied,
                                fp_psMACIntf->sRXCtx.rxPoolsOccupied);

        bInitOK = true;
    }

    return bInitOK;
}
