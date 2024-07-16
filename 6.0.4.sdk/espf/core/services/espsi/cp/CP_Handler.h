/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TPLAYER_CP_HANDLER_H_
#define TPLAYER_CP_HANDLER_H_

/**
 * @addtogroup Services
 * @{
 *
 * @addtogroup ESPS_I
 * @{
 *
 * @defgroup cp Command Protocol
 * @{
 *
 * Service to handle the CP Layer from the ESPS I Stack
 *
 * @file CP_Handler.h
 * @brief Command Protocol handler configuration
 *
 * @}
 * @}
 * @}
 *
 */

#include "ESPLATFORM_NETWORK_STACK/ES_CP/ESCP_ModDrv.h"
#include "ESPLATFORM_NETWORK_STACK/ES_CP/ESCCP_ModDrv.h"

//-----------------------------------------------------------------------------------------
// Module interface

typedef enum
{
    ECPDISPATCHRESULT_SIMPLERESULT_OK, /**< response with TL error code received */
    ECPDISPATCHRESULT_RESULT_OK, /**< indicates a response with buffer */
    ECPDISPATCHRESULT_RESULT_POSTPONED, /**< postponed because the data is not currently available */
    ECPDISPATCHRESULT_RESULT_BY_CHUNKS, /**< the result needs to be transferred by chunks */
    ECPDISPATCHRESULT_ERROR, /**< any error not matching standard responses */
    ECPDISPATCHRESULT_MAX
} eCPDispatchResult_t;

typedef struct
{
    uint32_t u32CmdType; /**< GS command ID */
    const uint8_t *pu8CmdData; /**< pointer to the command data payload */
    uint32_t u32CmdDataSize; /**< size of the command data payload buffer */
    uint8_t *pu8ResponseBuf; /**< response to the received command */
    uint32_t u32ResponseBufSize; /**< maximum size of the response buffer pu8ResponseBuf */
    uint32_t u32ResponseActualSize; /**< actual size of the payload written in pu8ResponseBuf */
    uint8_t u8TLError; /**< GS error code provided by the CP handler function to be returned to GS */
    OnESCP_RequestCommandChunk_t pChunkRequestCbk; /**< callback for a chunk-based transfer */
} sCPDispatchContext_t;

/** CP command handler prototype */
typedef eCPDispatchResult_t (*pfCPCmdHandler)(sCPDispatchContext_t * const psDispCtx);

/**
 * @brief Initialize the CP relevant functions from the ESPS I Stack
 */
void CP_Handler_Init();

/**
 * @brief Task to process the CP commands. It is called from the main TP Layer task.
 */
void CP_Handler_Task();

/**
 * @brief Verify that the CP dispatcher context is valid for a command ID
 * @param psDispCtx: context for the CP dispatcher
 * @param u32CmdId: CP Command ID
 *
 * @return whether the context is valid
 */
bool CPCmdHandler_IsDispContextValid(sCPDispatchContext_t * const psDispCtx, const uint32_t u32CmdId);

#endif // TPLAYER_CP_HANDLER_H_
