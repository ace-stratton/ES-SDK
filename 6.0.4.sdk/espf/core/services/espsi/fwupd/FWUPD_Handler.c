/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup fwupd
 * @{
 *
 * @file    FWUPD_Handler.c
 * @brief   FWUPD handler definitions
 *
 * @}
 */

#include <esps_drv_def.h>
#include <string.h>
#include "FWUPD_Handler.h"
#include "CircularFlatBuffer.h"
#include "ESTL_LayersLocalConf.h"
#include "cmsis_os2.h"
#include "es_exeh.h"
#include "FWUPD_Persistor.h"
#include "SdMngr.h"
#include "MACCRC32_Classic_Impl.h"
#include "FWUPD_Handler_Cfg.h"
#include "TaskMonitor.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_FWUPD_HANDLER)
#define TASK_PERIOD_MS              (20U)
#define WD_KICK_PERIOD              (2000U)

// Exception IDs
#define EXC_UNEXPECTED_ENUM_VALUE           ((int32_t) 0)
#define EXC_RECEPTION_INTERRUPTED           ((int32_t) 1)
#define EXC_PACKET_ID_NULL                  ((int32_t) 2)
#define EXC_OS_MESSAGE_QUEUE_NEW_FAILED     ((int32_t) 3)
#define EXC_CANNOT_POST_EVENT               ((int32_t) 4)
#define EXC_IMAGE_VERIFY_FAILED             ((int32_t) 5)
#define EXC_UNHANDLED_TRANSFER_IMAGE        ((int32_t) 6)

// size of event elements in the FW UPD state machine queue
#define SM_EVENT_QUEUE_ELEMENT_SIZE         ((uint32_t) 1)

static osThreadId_t FwUpd_TaskHandle = NULL;

typedef enum
{
    FWUPDSMEVENT_NEW_TRANSFER_REQ,
    FWUPDSMEVENT_NEW_CHUNK_RECEIVED,
    FWUPDSMEVENT_CHECK_FWBUNDLE,
    FWUPDSMEVENT_GO_FW_UPDATE,
    FWUPDSMEVENT_MAX
} eFwUpdSmEvent_t;

typedef enum
{
    FWUPDSTATE_IDLE,
    FWUPDSTATE_RXINPROGRESS,
    FWUPDSTATE_RXFINISHED,
    FWUPDSTATE_MAX
} eFwUpdState_t;

typedef struct
{
    // file I/O result for last transfer info load operation
    eFwUpdPersistorResult lastTransferInfoRes;
    // structure containing information for the update received on the first data chunk from TL
    sTransferInfo_t lastTransferInfo;
    // indicates if this is the first chunk of data received from TL
    bool bIsFirstChunk;
    // indicates if this is the first chunk after system reset
    bool bFirstChunkAfterReset;
    // flat circular buffer management context
    CircularBufCtx_t cbufCtx;
    // current operating state of the FW update
    eFwUpdState_t state;
    // number of bytes written to storage since start of FW update Rx
    uint32_t u32CommittedBytesSinceStart;
    // unique identifier of the active transfer;
    // N.B. in IDLE state, the value of this attribute shall not be used since it gets initialised on
    //      the first OnESFWUPD_OnNewChunk() call
    uint64_t u64ActiveTransferId;
    // handle of the OS queue used to receive state machine events from the asynchronous TP layer callbacks
    osMessageQueueId_t smEvtQueueHandle;
    // event queue configuration attributes
    osMessageQueueAttr_t smEvtQueueAttr;
} sfwUpdContext_t;

// circular buffer to hold incoming FW update chunks
static uint8_t bundleChunkBuf[MAX_NUMBER_OF_TL_BUF_PACKETS * ESTL_MIN_PAYLOAD_SIZE];
static uint8_t auxChunkBuf[STORAGE_COMMIT_BUF_SIZE];
static uint8_t smEvtQueueBuf[SM_EVENT_QUEUE_SIZE * SM_EVENT_QUEUE_ELEMENT_SIZE];
static StaticQueue_t evtQueueCb;

static sfwUpdContext_t fwUpdCtx =
{
    .lastTransferInfoRes = EFWUPDPERSISTORRESULT_ERROR,
    .bFirstChunkAfterReset = true,
    .bIsFirstChunk = true,
    .state = FWUPDSTATE_IDLE,
    .u32CommittedBytesSinceStart = 0U,
    .u64ActiveTransferId = 0U,
    .smEvtQueueHandle = NULL,
};

// OS-task responsible to drive the FWUpd state machine and write data to SD card
static const osThreadAttr_t FWUpd_Task_attributes =
{
    .name = "FwUpdateTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 2500
};

static void fs_vInitSm(void);
static void fs_vFWUPD_Handler_Task(void *argument);
static uint8_t fs_vOnESFWUPD_OnNewChunk(uint8_t* pChunk, uint16_t nReceivedSize, uint64_t* pPacketNumber);
static uint8_t fs_vOnESFWUPD_CheckFirmwareBundle(uint32_t nPktSize);
static void fs_vOnESFWUPD_GoFirmwareUpdate(uint32_t nPktSize);
static osStatus_t fs_vPostSmEvent(eFwUpdSmEvent_t evt);
static void fs_vTriggerSmEvent(eFwUpdSmEvent_t evt);
static void fs_vPersistPendingData(bool bUseFullSizedCommits);

static ESFWUPD_CB_ReqCallbackRet_t reqCbResult =
{
   .OnNewChunk = fs_vOnESFWUPD_OnNewChunk,
   .nPartialReceivedSize = 0U
};

static SESFWUPD_CB_HandlerIntf updIntf;

// this OS task is responsible to drive the SD card write state machine in case of coming FW updates
static void fs_vFWUPD_Handler_Task(void *argument)
{
    osStatus_t status;
    eFwUpdSmEvent_t rcvdEvt;
    uint8_t aliveCntr = 0U;

    (void) argument;

    while (true)
    {
        status = osMessageQueueGet(fwUpdCtx.smEvtQueueHandle, &rcvdEvt, NULL, TASK_PERIOD_MS);

        if (status == osOK)
        {
            fs_vTriggerSmEvent(rcvdEvt);
        }

        aliveCntr++;

        if ((aliveCntr * TASK_PERIOD_MS) >= WD_KICK_PERIOD)
        {
            aliveCntr = 0U;
            TaskMonitor_IamAlive(TASK_FWUPD_HANDLER);
            vApplicationLowStackCheck(TASK_FWUPD_HANDLER);
        }
    }
}

static void fs_vInitSm(void)
{
    eCircBufOpResult res;

    fwUpdCtx.state = FWUPDSTATE_IDLE;
    fwUpdCtx.u32CommittedBytesSinceStart = 0U;
    fwUpdCtx.lastTransferInfo.u64TransferId = 0U;
    (void) memset(&fwUpdCtx.lastTransferInfo, 0U, sizeof(sTransferInfo_t));
    fwUpdCtx.u64ActiveTransferId = 0U;
    fwUpdCtx.bIsFirstChunk = true;

    res = CircularBuf_Init(&fwUpdCtx.cbufCtx,
                           bundleChunkBuf,
                           sizeof(bundleChunkBuf),
                           STORAGE_COMMIT_BUF_SIZE,
                           auxChunkBuf,
                           sizeof(auxChunkBuf));

    if (res != ECIRCBUFOPRESULT_OK)
        EXEH_HANDLE(eEXEHSeverity_Fatal, EXC_OS_MESSAGE_QUEUE_NEW_FAILED);

    if (fwUpdCtx.smEvtQueueHandle == NULL)
    {
        fwUpdCtx.smEvtQueueAttr.name = NULL;
        fwUpdCtx.smEvtQueueAttr.attr_bits = 0;
        fwUpdCtx.smEvtQueueAttr.mq_mem = smEvtQueueBuf;
        fwUpdCtx.smEvtQueueAttr.mq_size = sizeof(smEvtQueueBuf);
        fwUpdCtx.smEvtQueueAttr.cb_mem = &evtQueueCb;
        fwUpdCtx.smEvtQueueAttr.cb_size = sizeof(evtQueueCb);

        fwUpdCtx.smEvtQueueHandle = osMessageQueueNew(SM_EVENT_QUEUE_SIZE,
                                                      SM_EVENT_QUEUE_ELEMENT_SIZE,
                                                      &fwUpdCtx.smEvtQueueAttr);
    }
    else
    {
        (void) osMessageQueueReset(fwUpdCtx.smEvtQueueHandle);
    }

    if (fwUpdCtx.smEvtQueueHandle == NULL)
        EXEH_HANDLE(eEXEHSeverity_Fatal, EXC_OS_MESSAGE_QUEUE_NEW_FAILED);
}

static osStatus_t fs_vPostSmEvent(eFwUpdSmEvent_t evt)
{
    osStatus_t res = osMessageQueuePut(fwUpdCtx.smEvtQueueHandle, (const void *) &evt, 0U, 0U);

    if (res != osOK)
    {
        EXEH_HANDLE(eEXEHSeverity_Error, EXC_CANNOT_POST_EVENT);
        FWUPD_DBG_PRINT("osMessageQueuePut(%d)\r\n", res);
    }

    return res;
}

static void fs_vPersistPendingData(bool bUseFullSizedCommits)
{
    uint32_t u32DataBytesPending;
    uint32_t u32BytesRequested = STORAGE_COMMIT_BUF_SIZE;
    uint32_t u32BytesPersisted = 0U;
    bool bBuffersPending;
    const uint8_t *pData = NULL;
    eFwUpdPersistorResult res;

    bBuffersPending = true;

    while (bBuffersPending)
    {
        // write next available commit buffer to storage
        pData = (true == bUseFullSizedCommits) ?
            (CircularBuf_ReadNextCommitBuffer(&fwUpdCtx.cbufCtx, &u32DataBytesPending)) :
            (CircularBuf_GetNextBufferPtr(&fwUpdCtx.cbufCtx, u32BytesRequested, &u32DataBytesPending));

        if (pData != NULL)
        {
            res = FWUPD_Persistor_CommitBuffer(fwUpdCtx.u32CommittedBytesSinceStart, pData, u32BytesRequested, &u32BytesPersisted);

            if (res == EFWUPDPERSISTORRESULT_OK)
            {
                fwUpdCtx.u32CommittedBytesSinceStart += u32BytesPersisted;
            }
            else
            {
                FWUPD_DBG_PRINT("FWUPD_Persistor_CommitBuffer(%ld)\r\n", fwUpdCtx.u32CommittedBytesSinceStart);
            }

            CircularBuf_ReleaseLastBufferPtr(&fwUpdCtx.cbufCtx, res == EFWUPDPERSISTORRESULT_OK);

            // is this last transfer?
            if ((!bUseFullSizedCommits) && (u32BytesRequested == u32DataBytesPending))
            {
                bBuffersPending = false;
            }
        }
        else
        {
            if (true == bUseFullSizedCommits)
            {
                bBuffersPending = false;
            }
            else
            {
                // request remaining bytes for the last chunk since there are not enough bytes to fill a
                // commit buffer
                u32BytesRequested = u32DataBytesPending;
            }
        }
    }
}

static void fs_vTriggerSmEvent(eFwUpdSmEvent_t evt)
{
    eFwUpdState_t nextState = fwUpdCtx.state;
    eFwUpdPersistorResult res = EFWUPDPERSISTORRESULT_ERROR;

    // next-state decision logic and onExit() transition functions implementation
    switch (fwUpdCtx.state)
    {
        case FWUPDSTATE_IDLE:
        {
            switch (evt)
            {
                case FWUPDSMEVENT_NEW_TRANSFER_REQ:
                // this case happens when a File IO error occurred during RXINPROGRESS and the transfer was temporarily stopped on
                // GS side; later, when continued, we just go back to RXINPROGRESS state
                case FWUPDSMEVENT_NEW_CHUNK_RECEIVED:
                case FWUPDSMEVENT_CHECK_FWBUNDLE:
                {
                    nextState = FWUPDSTATE_RXINPROGRESS;
                    break;
                }

                case FWUPDSMEVENT_GO_FW_UPDATE:
                {
                    // for some reason, last download may have succeeded and we receive a GO_FW_UPDATE command from GS after we previously
                    // entered IDLE state
                    nextState = FWUPDSTATE_RXFINISHED;
                    break;
                }

                default:
                {
                    break;
                }
            }

            // repost event to avoid changing the state in other places apart from this function
            (void) fs_vPostSmEvent(evt);

            break;
        }

        case FWUPDSTATE_RXINPROGRESS:
        {
            switch (evt)
            {
                case FWUPDSMEVENT_NEW_CHUNK_RECEIVED:
                {
                    fs_vPersistPendingData(true);
                    break;
                }

                case FWUPDSMEVENT_NEW_TRANSFER_REQ:
                {
                    FWUPD_Persistor_DiscardPendingUpdate();
                    fwUpdCtx.lastTransferInfo.u64TransferId = fwUpdCtx.u64ActiveTransferId;

                    res = FWUPD_Persistor_StartNewTransfer(&fwUpdCtx.lastTransferInfo, &fwUpdCtx.u32CommittedBytesSinceStart);

                    if (res != EFWUPDPERSISTORRESULT_OK)
                    {
                        nextState = FWUPDSTATE_IDLE;
                    }
                    else
                    {
                        FWUPD_DBG_PRINT("FWUPD_Persistor_StartNewTransfer(%d)\r\n", res);
                    }

                    break;
                }

                case FWUPDSMEVENT_CHECK_FWBUNDLE:
                {
                    fs_vPersistPendingData(false);

                    if (FWUPD_Persistor_VerifyImage() == EFWUPDPERSISTORRESULT_OK)
                    {
                        nextState = FWUPDSTATE_RXFINISHED;
                    }
                    else
                    {
                        EXEH_HANDLE(eEXEHSeverity_Warning, EXC_IMAGE_VERIFY_FAILED);
                        nextState = FWUPDSTATE_IDLE;
                        FWUPD_DBG_PRINT("EXC_IMAGE_VERIFY_FAILED\r\n");
                    }

                    break;
                }
                case FWUPDSMEVENT_GO_FW_UPDATE:
                default:
                break;
            }
        }

        case FWUPDSTATE_RXFINISHED:
        {
            switch (evt)
            {
                case FWUPDSMEVENT_GO_FW_UPDATE:
                {
                    if (false == FWUPD_Handler_Cfg_HandleTransferComplete(&fwUpdCtx.lastTransferInfo,
                                                                          fwUpdCtx.u64ActiveTransferId,
                                                                          FWUPD_Persistor_GetDownloadedImageFileName()))
                    {
                        EXEH_HANDLE(eEXEHSeverity_Warning, EXC_UNHANDLED_TRANSFER_IMAGE);
                        FWUPD_DBG_PRINT("EXC_UNHANDLED_TRANSFER_IMAGE\r\n");
                    }

                    nextState = FWUPDSTATE_IDLE;
                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        case FWUPDSMEVENT_GO_FW_UPDATE:
        default:
        {
            EXEH_HANDLE(eEXEHSeverity_Warning, EXC_UNEXPECTED_ENUM_VALUE);

            fs_vInitSm();

            break;
        }
    }

    // on-entry transition functions implementation
    if (fwUpdCtx.state != nextState)
    {
        fwUpdCtx.state = nextState;
    }
}

static ESFWUPD_CB_ReqCallbackRet_t OnESFWUPD_RequestBundleBuffer(uint64_t* pPacketNumber)
{
    fwUpdCtx.u32CommittedBytesSinceStart = 0U;

    (void) CircularBuf_Init(&fwUpdCtx.cbufCtx,
                            bundleChunkBuf,
                            sizeof(bundleChunkBuf),
                            STORAGE_COMMIT_BUF_SIZE,
                            auxChunkBuf,
                            sizeof(auxChunkBuf));

    // load pending transfer information (if any...)
    fwUpdCtx.lastTransferInfoRes = FWUPD_Persistor_GetPartialTransferInfo(&fwUpdCtx.lastTransferInfo, &fwUpdCtx.u32CommittedBytesSinceStart);

    reqCbResult.OnNewChunk = fs_vOnESFWUPD_OnNewChunk;
    reqCbResult.nPartialReceivedSize = (uint64_t) 0U;

    if (pPacketNumber != NULL)
    {
        fwUpdCtx.u64ActiveTransferId = *pPacketNumber;

        if ((fwUpdCtx.lastTransferInfo.u64TransferId == fwUpdCtx.u64ActiveTransferId) &&
            (fwUpdCtx.lastTransferInfoRes == EFWUPDPERSISTORRESULT_OK))
        {
            fwUpdCtx.bIsFirstChunk = (fwUpdCtx.u32CommittedBytesSinceStart <= sizeof(SESSoftwareUPD_Bundle));
            reqCbResult.nPartialReceivedSize = (uint64_t) fwUpdCtx.u32CommittedBytesSinceStart;

            // correct initial size because those are used as file position offsets during commit
            if (fwUpdCtx.u32CommittedBytesSinceStart >= sizeof(SESSoftwareUPD_Bundle))
            {
                fwUpdCtx.u32CommittedBytesSinceStart -= sizeof(SESSoftwareUPD_Bundle);
            }

            FWUPD_DBG_PRINT("offset = %ld, tid = %lld\r\n", fwUpdCtx.u32CommittedBytesSinceStart, fwUpdCtx.u64ActiveTransferId);
        }
        else
        {
            // discard partial transfer
            fwUpdCtx.u32CommittedBytesSinceStart = 0U;
            fwUpdCtx.bIsFirstChunk = true;

            (void) fs_vPostSmEvent(FWUPDSMEVENT_NEW_TRANSFER_REQ);
            FWUPD_DBG_PRINT("new transfer [%lld]\r\n", fwUpdCtx.u64ActiveTransferId);
        }
    }
    else
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, EXC_PACKET_ID_NULL);
    }

    return reqCbResult;
}

static bool fs_bIsUpdateHeaderValid(SESSoftwareUPD_Bundle * const pUpdHeader)
{
    bool res = false;

    if (pUpdHeader != NULL)
    {
        // currently no other conditions are checked for validity
        // TODO: Extend with more conditions when we have a better idea how to handle FW updates for OBC.
        // e.g. check major/minor SW version and disallow downgrades, etc.
        res = (pUpdHeader->nModuleType == FW_OBC_MODULE_TYPE1) ||
              (pUpdHeader->nModuleType == FW_OBC_MODULE_TYPE2);
    }

    return res;
}

static uint8_t fs_vOnESFWUPD_OnNewChunk(uint8_t* pChunk, uint16_t nReceivedSize, uint64_t* pPacketNumber)
{
    eCircBufOpResult res;
    uint8_t u8OnNewChunkRes = EESTL_SFERR_CANNOT_LOAD_UPD_BUNDLE;
    const uint8_t * pDataStart = pChunk;
    uint16_t u16BytesToCopy = nReceivedSize;
    osStatus_t postEvtResult = osError;
    bool bUpdHeaderValid = true;

    (void) pPacketNumber;

    if (true == fwUpdCtx.bIsFirstChunk)
    {
        if (nReceivedSize >= sizeof(SESSoftwareUPD_Bundle))
        {
        FWUPD_DBG_PRINT("First chunk received\r\n");
            fwUpdCtx.bIsFirstChunk = false;

            // copy update header
            (void) memcpy(&fwUpdCtx.lastTransferInfo.header, pChunk, sizeof(SESSoftwareUPD_Bundle));

            bUpdHeaderValid = fs_bIsUpdateHeaderValid(&fwUpdCtx.lastTransferInfo.header);

            if (bUpdHeaderValid)
            {
                // jump over header in first received chunk of data
                pDataStart = pChunk + sizeof(SESSoftwareUPD_Bundle);
                u16BytesToCopy = nReceivedSize - sizeof(SESSoftwareUPD_Bundle);

                FWUPD_DBG_PRINT("Update header valid\r\n");
                (void) fs_vPostSmEvent(FWUPDSMEVENT_NEW_TRANSFER_REQ);
            }
            else
            {
                FWUPD_DBG_PRINT("Update header invalid!\r\n");
            }
        }
        else
        {
            // bad update header
            u8OnNewChunkRes = EESTL_SFERR_SIZE_MISMATCH;
        FWUPD_DBG_PRINT("Incomplete update header received!\r\n");
        }
    }

    if (bUpdHeaderValid)
        {
            postEvtResult = fs_vPostSmEvent(FWUPDSMEVENT_NEW_CHUNK_RECEIVED);

            if (postEvtResult == osOK)
            {
                res = CircularBuf_Append(&fwUpdCtx.cbufCtx, (uint8_t * const) pDataStart, u16BytesToCopy);

                if (res == ECIRCBUFOPRESULT_BUFFER_FULL)
                {
                    u8OnNewChunkRes = EESTL_SFERR_BUFFER_BUSY;
                    FWUPD_DBG_PRINT("CircularBuf_Append(ECIRCBUFOPRESULT_BUFFER_FULL)\r\n");
                }
                else
                    if (res == ECIRCBUFOPRESULT_OK)
                    {
                        u8OnNewChunkRes = EESTL_SFERR_SUCCESS;
                    }
                    else
                    {
                        FWUPD_DBG_PRINT("CircularBuf_Append(%d)\r\n", res);
                    }
            }
            else
            {
                u8OnNewChunkRes = EESTL_SFERR_BUFFER_BUSY;
                FWUPD_DBG_PRINT("fs_vPostSmEvent(%d)\r\n", postEvtResult);
            }
        }
        else
        {
            EXEH_HANDLE(eEXEHSeverity_Warning, EXC_RECEPTION_INTERRUPTED);
            FWUPD_DBG_PRINT("restart transfer: active transfer #: %lld [%lld]\r\n", fwUpdCtx.u64ActiveTransferId, (*((uint64_t*) pPacketNumber)));

            u8OnNewChunkRes = EESTL_SFERR_BAD_PARAMS;
        }

        fwUpdCtx.bFirstChunkAfterReset = false;

    if (u8OnNewChunkRes != EESTL_SFERR_SUCCESS)
    {
        FWUPD_DBG_PRINT("u8OnNewChunkRes(%d)\r\n", u8OnNewChunkRes);
    }

    return u8OnNewChunkRes;
}

static uint8_t fs_vOnESFWUPD_CheckFirmwareBundle(uint32_t nPktSize)
{
    (void) nPktSize;
    (void) fs_vPostSmEvent(FWUPDSMEVENT_CHECK_FWBUNDLE);
    FWUPD_DBG_PRINT("%s\r\n", __func__);

    return 0;
}

static void fs_vOnESFWUPD_GoFirmwareUpdate(uint32_t nPktSize)
{
    (void) nPktSize;
    (void) fs_vPostSmEvent(FWUPDSMEVENT_GO_FW_UPDATE);

    FWUPD_DBG_PRINT("%s\r\n", __func__);
}

void FWUPD_Handler_Init(void)
{
    fs_vInitSm();

    // Initialise the Firmware Update Protocol
    updIntf.OnRequestBundleCallback = OnESFWUPD_RequestBundleBuffer;
    updIntf.OnCheckFirmwareBundle = fs_vOnESFWUPD_CheckFirmwareBundle;
    updIntf.OnGoFirmwareUpdate = fs_vOnESFWUPD_GoFirmwareUpdate;

    ESFWUPD_ModDrv_Init(&updIntf, true);

    FwUpd_TaskHandle = osThreadNew(fs_vFWUPD_Handler_Task, NULL, &FWUpd_Task_attributes);
    CRIT_ASSERT(FwUpd_TaskHandle);

    TaskMonitor_TaskInitialized(TASK_FWUPD_HANDLER);
}
