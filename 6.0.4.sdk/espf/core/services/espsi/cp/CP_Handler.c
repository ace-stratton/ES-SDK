/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup cp
 * @{
 *
 * @file    CP_Handler.c
 * @brief   Command Protocol handler
 *
 * @}
 */

#include "CP_Handler.h"
#include "stm32h7xx_hal.h"
#include "ESPLATFORM_NETWORK_STACK/ES_CP/ESCCP_ModDrv.h"
#include "ESPLATFORM_NETWORK_STACK/ES_CP/ESCP_ModDrv.h"
#include "es_exeh.h"
#include "ESSA_Stack_TP_Layer.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_CP_HANDLER)

// Exception codes for this module
#define EXC_UNSUPPORTED_COMMAND_ID_RCVD     (0U)

#define ESTL_CP_HANDLER_BEGIN_COMMAND_MAP()                                         \
static pfCPCmdHandler GetCommandHandler(uint32_t nCommandID) {                      \
    switch (nCommandID) {

#define ESTL_CP_HANDLER_REGISTER_COMMAND(commandID, handlerFunc)                    \
    case commandID: return handlerFunc;

#define ESTL_CP_HANDLER_END_COMMAND_MAP()                                           \
    } return (pfCPCmdHandler) NULL; }

#define __ESTL_CP_MOD_DRV_C__
#define __CP_HANDLER_C__
#include "ESCP_CommandsLocalConf.h"

static uint8_t IN_CMDBuffer[ESCP_MAX_IN_PACKET_SIZE];
static uint8_t OUT_CMDBuffer[ESCP_MAX_OUT_PACKET_SIZE];

static ESCP_ModDrvConfig modDrvConfig =
{
	.pCommands = ESTL_CP_GET_CMDENTRIES(),
	.nCommandsCount = ESTL_CP_GET_CMDENTRIESCOUNT(),
	.pIN_CMDBuffer = IN_CMDBuffer,
	.IN_CMDBufferSize = ESCP_MAX_IN_PACKET_SIZE,
	.pOUT_CMDBuffer = OUT_CMDBuffer,
	.OUT_CMDBufferSize = ESCP_MAX_OUT_PACKET_SIZE
};

//---------------------------------------------------------------------------------------------------------------------------
// Types
typedef enum
{
    ESMTS_NONE,
    ESMTS_WAIT_CMD_PROCESS
} ESMTState;

//---------------------------------------------------------------------------------------------------------------------------
static ESMTState eCmdState;
static uint32_t u32StateTimer;
static uint64_t u64CurrentCmdId;

//---------------------------------------------------------------------------------------------------------------------------
// ESCP_SCommandHandlerItem interface
void OnESCP_CommandReceived(uint64_t nCmdID, uint32_t nCmdType, uint8_t *pCMDPkt, uint32_t nCMDPktSize)
{
    eCmdState = ESMTS_WAIT_CMD_PROCESS;
    u32StateTimer = HAL_GetTick();

    u64CurrentCmdId = nCmdID;
}

void OnESCP_CmdCancelRequest(uint64_t nCmdID, uint32_t nCmdType)
{
    if ((u64CurrentCmdId == nCmdID) &&
        ((nCmdType == CP_CMD_SXBAND_GWSEND) ||
         (nCmdType == CP_CMD_MACFP_GWSEND) ||
         (nCmdType == CP_CMD_CUBEADCS_GWSEND)
         ))
        ESSA_Stack_TP_Layer_ReleaseThreadWait();

    // Cancel all activity, related to this command
    // Then call :
    ESCP_ModDrv_PrepareSimpleResult(EESTL_SFERR_CMD_CANCELLED);

    eCmdState = ESMTS_NONE;
}

//---------------------------------------------------------------------------------------------------------------------------
// Module interface

void CP_Handler_Init()
{
    // Initialise the Command Protocol
    ESCP_ModDrv_Init(true, &modDrvConfig);
    ESCCP_ModDrv_Init(true);
    cp_cmd_handler_init();

    eCmdState = ESMTS_NONE;
    u32StateTimer = 0;
    u64CurrentCmdId = 0;
}

void CP_Handler_Task()
{
    sCPDispatchContext_t sDispCtx;
    uint64_t u64CmdId = 0U;
    pfCPCmdHandler pfCmdHandler = (pfCPCmdHandler) NULL;
    uint32_t u32ResBufSize = 0U;
    uint32_t u32CmdType = 0U;
    uint32_t u32CmdDataBufSize = 0;
    eCPDispatchResult_t eCmdDispatchRes;
    uint8_t *pu8CmdDataBuf = (uint8_t *) NULL;
    uint8_t *pu8ResBuf = (uint8_t *) NULL;

    switch (eCmdState)
    {
        case ESMTS_WAIT_CMD_PROCESS :
        {
            ESCP_ModDrv_GetPendingCommand(&u64CmdId, &u32CmdType, &pu8CmdDataBuf, &u32CmdDataBufSize);

            // nCmdType actually represents the command ID while nCmdID is a sequence ID which is incremented with
            // each new command received
            pfCmdHandler = GetCommandHandler(u32CmdType);

            // try to obtain a response buffer for the command data
            pu8ResBuf = ESCP_ModDrv_GetResultBuffer(&u32ResBufSize);

            if (pfCmdHandler != NULL)
            {
            	memset(&sDispCtx, 0, sizeof(sCPDispatchContext_t));
                sDispCtx.u32CmdType = u32CmdType;
                sDispCtx.pu8CmdData = pu8CmdDataBuf;
                sDispCtx.u32CmdDataSize = u32CmdDataBufSize;
                sDispCtx.pu8ResponseBuf = pu8ResBuf;
                sDispCtx.u32ResponseBufSize = u32ResBufSize;
                sDispCtx.u32ResponseActualSize = 0U;
                sDispCtx.u8TLError = EESTL_SFERR_OUT_OF_MEM;
                sDispCtx.pChunkRequestCbk = (OnESCP_RequestCommandChunk_t) NULL;

                eCmdDispatchRes = (*pfCmdHandler)(&sDispCtx);

                switch (eCmdDispatchRes)
                {
                    case ECPDISPATCHRESULT_SIMPLERESULT_OK:
                        ESCP_ModDrv_PrepareSimpleResult(sDispCtx.u8TLError);
                    break;

                    case ECPDISPATCHRESULT_RESULT_OK:
                        ESCP_ModDrv_PrepareResult(sDispCtx.u32ResponseActualSize, sDispCtx.u8TLError);
                    break;

                    case ECPDISPATCHRESULT_RESULT_BY_CHUNKS:
                        ESCP_ModDrv_PrepareResultOnChunks(sDispCtx.u32ResponseActualSize, sDispCtx.u8TLError, sDispCtx.pChunkRequestCbk);
                    break;

                    // It is responsibility of the handler to complete the transfer when the data is present
                    case ECPDISPATCHRESULT_RESULT_POSTPONED:
                    case ECPDISPATCHRESULT_ERROR:
                    default:
                        ESCP_ModDrv_PrepareSimpleResult(EESTL_SFERR_BAD_CMD_PARAMS);
                    break;
                }

                eCmdState = ESMTS_NONE;
            }
            else
                EXEH_HANDLE(eEXEHSeverity_Warning, EXC_UNSUPPORTED_COMMAND_ID_RCVD);

            break;
        }

        case ESMTS_NONE:
        default:
        break;
    }
}

bool CPCmdHandler_IsDispContextValid(sCPDispatchContext_t * const psDispCtx, const uint32_t u32CmdId)
{
    bool res = false;

    if (psDispCtx != NULL)
    {
        res = ((psDispCtx->u32CmdType == u32CmdId) &&
               (psDispCtx->pu8CmdData != NULL) &&
               (psDispCtx->pu8ResponseBuf != NULL) &&
               (psDispCtx->u32ResponseBufSize > 0U));
    }

    return res;
}
