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
 * @file     esps_drv_queue.c
 * @brief    MAC Message Queue implementation
 *
 * @}
 */

#include "esps_drv_esps_stack.h"

#include "esps_drv_ct.h"
#include "esps_drv_exeh.h"
#include "esps_drv_dispatcher.h"

/******************************************************************************
 * File Local Preprocessor Definitions
 *****************************************************************************/
#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_MAC_QUEUE)
#define MAC_PRIORITY(A)             (A.u8BasePriority + A.u8Priority)

/******************************************************************************
 * Private Function Definitions
 *****************************************************************************/
/// Add a new entry to the transmission queue.
bool MAC_QUEUE_vTXQueueAdd(sMACInterfaceState_t * fp_psMACIntf, sMACTXPoolEntry_t * fp_psEntry)
{
    bool result = false;

    sMACTXPoolEntry_t *psCurrent = NULL;

    if((fp_psMACIntf == NULL) || (fp_psEntry == NULL))
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        MAC_vEnterCriticalSection(fp_psMACIntf);

        if((fp_psMACIntf->sTXCtx.psQueue == NULL) ||
           (MAC_PRIORITY(fp_psMACIntf->sTXCtx.psQueue->sPrio) >= MAC_PRIORITY(fp_psEntry->sPrio)))
        {
            // Set the entry as the one to be processed next
            fp_psEntry->psNext = fp_psMACIntf->sTXCtx.psQueue;
            fp_psMACIntf->sTXCtx.psQueue = fp_psEntry;
        }
        else
        {
            // Place the entry depending on its priority
            psCurrent = fp_psMACIntf->sTXCtx.psQueue;

            while((psCurrent->psNext != NULL) && (MAC_PRIORITY(psCurrent->sPrio) < MAC_PRIORITY(fp_psEntry->sPrio)))
            {
                psCurrent = psCurrent->psNext;
            }

            fp_psEntry->psNext = psCurrent->psNext;
            psCurrent->psNext = fp_psEntry;
        }

        result = true;

        MAC_vLeaveCriticalSection(fp_psMACIntf);
    }

    if(result)
        fp_psMACIntf->sTXCtx.u32QueueElementsCount++;

    return result;
}

/// Get and remove the first transmission queue entry.
sMACTXPoolEntry_t *MAC_QUEUE_vTXQueuePop(sMACInterfaceState_t * fp_psMACIntf)
{
    MAC_vEnterCriticalSection(fp_psMACIntf);

    sMACTXPoolEntry_t *psEntry = fp_psMACIntf->sTXCtx.psQueue;

    if(fp_psMACIntf->sTXCtx.psQueue)
    {
        fp_psMACIntf->sTXCtx.psQueue = fp_psMACIntf->sTXCtx.psQueue->psNext;

        if(fp_psMACIntf->sTXCtx.u32QueueElementsCount > 0U)
            --fp_psMACIntf->sTXCtx.u32QueueElementsCount;
    }

    MAC_vLeaveCriticalSection(fp_psMACIntf);

    return psEntry;
}

/// Complete a transmission. Unblock the thread waiting for TX.
void MAC_QUEUE_vTXQueueComplete(sMACTXPoolEntry_t * fp_psEntry, bool fp_bSuccess)
{
    ESSATMAC_ErrCodes txResult;

    if(fp_psEntry != NULL)
    {
        if(fp_bSuccess)
        {
            txResult = ESSATMAC_EC_OK;
        }
        else
        {
            txResult = ESSATMAC_EC_RETRY_COUNT_LIMIT;
        }

        // Execute callback to the sender with the result
        if(fp_psEntry->pSendCallback != NULL)
            (*fp_psEntry->pSendCallback) (fp_psEntry->nMsgID, txResult);
    }
}
