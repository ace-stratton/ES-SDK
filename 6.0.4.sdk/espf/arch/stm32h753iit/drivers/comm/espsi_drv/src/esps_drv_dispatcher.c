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
 * @file     esps_drv_dispatcher.c
 * @brief    MAC Received Frames Dispatcher implementation
 *
 * @}
 */

// External imports
#include "esps_drv_esps_stack.h"
#include "esps_drv_config.h"

#include "MACCRC32_Classic_Impl.h"
#include "esps_drv_dispatcher.h"
#include "esps_drv.h"
#include "esps_drv_cdef.h"
#include "esps_drv_ct.h"
#include "esps_drv_pool.h"
#include "esps_drv_exeh.h"
#include "esps_drv_debug.h"

/******************************************************************************
 * Local Preprocessor Definitions
 *****************************************************************************/
#define EXEH_CURRENT_MODULE_ID     (eEXEHModuleID_MAC_DISPATCHER)

/******************************************************************************
 * File Local Function Prototypes
 *****************************************************************************/
/**
 * Processes all queued messages.
 *
 * @param fp_psIntf - MAC interface state for which to process the messages.
 */
STATIC void fs_vProcessQueuedMessages(sMACInterfaceState_t * fp_psIntf);

/******************************************************************************
 * Private Function Definitions
 *****************************************************************************/
// Add a message to the dispatch queue.
void MAC_DISP_bDispatchQueueAdd(sMACDispatcher_t * fp_psDisp, sMACRXPoolEntry_t * fp_psEntry)
{
    // This function should be called from ISR only.
    if((fp_psDisp != NULL) && (fp_psEntry != NULL))
    {
        fp_psEntry->psNext = NULL;

        if(fp_psDisp->sQueue.psTail == NULL)
        {
            fp_psDisp->sQueue.psTail = fp_psEntry;
        }
        else
        {
            fp_psDisp->sQueue.psTail->psNext = fp_psEntry;
            fp_psDisp->sQueue.psTail = fp_psEntry;
        }

        if(fp_psDisp->sQueue.psHead == NULL)
        {
            fp_psDisp->sQueue.psHead = fp_psEntry;
        }

        fp_psDisp->u32RxMsgCount++;

        // Notify dispatcher thread about new message
        MAC_DISP_vDispatcherNotif(fp_psDisp->eMACId);

    }
}

// Return the first message from the dispatch queue.
sMACRXPoolEntry_t *MAC_DISP_bDispatchQueueTop(sMACDispatcher_t * fp_psDisp)
{
    sMACRXPoolEntry_t *psEntry = NULL;

    if(fp_psDisp != NULL)
    {
        psEntry = fp_psDisp->sQueue.psHead;
    }

    return psEntry;
}

// Remove the first message from the queue
void MAC_DISP_bDispatchQueuePop(sMACDispatcher_t * fp_psDisp)
{
    if(fp_psDisp != NULL)
    {
        if(fp_psDisp->sQueue.psHead != NULL)
        {
            if(fp_psDisp->sQueue.psHead == fp_psDisp->sQueue.psTail)
            {
                fp_psDisp->sQueue.psTail = NULL;
                fp_psDisp->sQueue.psHead = NULL;
            }
            else
            {
                fp_psDisp->sQueue.psHead = fp_psDisp->sQueue.psHead->psNext;
            }

            if(fp_psDisp->u32RxMsgCount > 0U)
                --fp_psDisp->u32RxMsgCount;

            MACDRV_DBG_PRINT("   -->  RxQ %ld rem cnt: %ld\r\n", (uint32_t) fp_psDisp->eMACId,
                             (uint32_t) fp_psDisp->u32RxMsgCount);
        }
    }
}

// Initialize the dispatcher
void MAC_DISP_vDispatcherInit(sMACInterfaceState_t * fp_psIntf, eMACInterface_t fp_eInterface)
{
    if(fp_psIntf != NULL)
    {
        // Store the interface ID in the dispatcher because
        // it is needed in order to reply on the correct interface.
        fp_psIntf->sDisp.eMACId = fp_eInterface;
        fp_psIntf->sDisp.u32RxMsgCount = 0U;
    }
}

/// Notify whoever is listening that there is a message ready to dispatch
void MAC_DISP_vDispatcherNotif(eMACInterface_t fp_eInterface)
{
    // Implementation done in Mac Configuration
    MacCfg_vDispatcherNotifCallback(fp_eInterface);
}

// Main processing function to processed all the queued messages.
void MAC_DISP_vDispatchMessages(sMACInterfaceState_t * fp_psIntf)
{

    if(fp_psIntf == NULL)
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        MACDRV_DBG_PRINT("Trg RxQ %ld)\r\n", (uint32_t) fp_psIntf->macIfId);

        // Process all messages
        fs_vProcessQueuedMessages(fp_psIntf);
    }
}

/******************************************************************************
 * Local Function Definitions
 *****************************************************************************/
// Process all queued messages.
STATIC void fs_vProcessQueuedMessages(sMACInterfaceState_t * fp_psIntf)
{
    sMACRXPoolEntry_t *psMsg = NULL;

    uint32_t u32CRC;

    bool bProcessed;

    if(fp_psIntf != NULL)
    {
        do
        {
            // New message
            psMsg = MAC_DISP_bDispatchQueueTop(&fp_psIntf->sDisp);

            if(psMsg)
            {
                // Check CRC
                u32CRC =
                    MACCRC32_Calc32((uint8_t *) & psMsg->sMessage, ESSATMAC_HEADER_SIZE + psMsg->sMessage.u8DataSize,
                                    CRC32_INIT_VALUE);

                // LSB network byte order is used, hence we can use the in-memory representation of the CRC to directly compare to
                // the received value on the bus
                if(u32CRC != psMsg->sMessage.u32CRC)
                {
                    MAC_Stats_triggerEvent(fp_psIntf->macStats, eMACStatId_IncorrectCrcMsgCntr);

                    EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_CRCMismatch);
                }
                else
                {
                    bProcessed = MAC_bProtocolProcessMessage(fp_psIntf->sDisp.eMACId, &psMsg->sMessage);
                    if(!bProcessed)
                    {
                        EXEH_HANDLE(eEXEHSeverity_Warning, (int32_t) eMACException_NotProcessed);
                    }
                    else
                        MAC_Stats_triggerEvent(fp_psIntf->macStats, eMACStatId_RxValidFramesCntr);
                }

                // Remove the messages from the queue.
                MAC_DISP_bDispatchQueuePop(&fp_psIntf->sDisp);

                // Release the message.
                MAC_POOL_vPoolRXFree(fp_psIntf, psMsg);
            }
        }
        while(psMsg != NULL);
    }
}
