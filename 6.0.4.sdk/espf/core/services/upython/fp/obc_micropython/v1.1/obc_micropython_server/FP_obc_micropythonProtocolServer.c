/*!
********************************************************************************************
* @file FP_obc_micropythonProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface obc_micropython v1.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#include "FP_obc_micropythonProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define obc_micropython_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define obc_micropython_PROTOCOL_VERSION_MINOR   ((uint8_t) 1)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_micropythonRequestScriptExecutionRequestData_t data;
} PACKED_STRUCT obc_micropythonRequestScriptExecutionProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_micropythonRequestScriptExecutionResponseData_t data;
} PACKED_STRUCT obc_micropythonRequestScriptExecutionProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_micropythonGetScriptExecStatusRequestData_t data;
} PACKED_STRUCT obc_micropythonGetScriptExecStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_micropythonGetScriptExecStatusResponseData_t data;
} PACKED_STRUCT obc_micropythonGetScriptExecStatusProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_RequestScriptExecutionReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetScriptExecStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_obc_micropythonProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_MICROPYTHON,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static obc_micropython_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_MICROPYTHON_REQUESTSCRIPTEXECUTION_FUNC_ID, fs_RequestScriptExecutionReq },
    { OBC_MICROPYTHON_GETSCRIPTEXECSTATUS_FUNC_ID, fs_GetScriptExecStatusReq }
};

/**********************************************************************
 *
 *  Static methods implementation
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    ESSA_Stack_FP_MsgHdr_t *pHdr = NULL;
    bool bIsFuncSupported = false;
    uint8_t i;

    // Basic header validity check
    if ((fp_DataInfo == NULL) ||
        (fp_DataInfo->u16DataSize < sizeof(ESSA_Stack_FP_MsgHdr_t)) ||
        (fp_DataInfo->pu8Data == NULL))
    {
        return false;
    }

    pHdr = (ESSA_Stack_FP_MsgHdr_t *) fp_DataInfo->pu8Data;

    if (IS_REQUEST(*pHdr))
    {
        for (i = 0; i < COUNT_OF(fs_aFuncArray); i++)
        {
            if (fs_aFuncArray[i].funcId == pHdr->funcId)
            {
                if (fs_aFuncArray[i].pfFunc != NULL)
                {
                    bIsFuncSupported = true;
                    fs_aFuncArray[i].pfFunc(fp_DataInfo);
                }

                break;
            }
        }

        if (!bIsFuncSupported)
            (void) ProtocolSendErrorResp(fp_DataInfo, (uint8_t) ESSA_FP_ERRCODE_FUNC_NOT_SUPPORTED);
    }

    return bIsFuncSupported;
}

static void fs_RequestScriptExecutionReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    obc_micropythonRequestScriptExecutionProtocolRequestData_t *fullrequest = (obc_micropythonRequestScriptExecutionProtocolRequestData_t *) fp_DataInfo->pu8Data;
    obc_micropythonRequestScriptExecutionRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(obc_micropythonRequestScriptExecutionProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (obc_micropythonRequestScriptExecutionRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->obc_micropython_RequestScriptExecutionRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->obc_micropython_RequestScriptExecutionRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GetScriptExecStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    obc_micropythonGetScriptExecStatusProtocolRequestData_t *fullrequest = (obc_micropythonGetScriptExecStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    obc_micropythonGetScriptExecStatusRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(obc_micropythonGetScriptExecStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (obc_micropythonGetScriptExecStatusRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->obc_micropython_GetScriptExecStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->obc_micropython_GetScriptExecStatusRequestHandler(&requestCtx,
                                        requestPayload);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void obc_micropython_registerServerApi(obc_micropython_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t obc_micropython_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_obc_micropythonProtocolServerInfo;
}

ESSATMAC_ErrCodes obc_micropython_RequestScriptExecutionResp(
                RespContext_t* ctx,
                const uint8_t u8Script_id,
                const OBC_MICROPYTHON_Result_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    obc_micropythonRequestScriptExecutionProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(obc_micropythonRequestScriptExecutionProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(obc_micropythonRequestScriptExecutionProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_MICROPYTHON;
        responseParams.hdr.funcId  = OBC_MICROPYTHON_REQUESTSCRIPTEXECUTION_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u8Script_id = u8Script_id;
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(obc_micropythonRequestScriptExecutionProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes obc_micropython_GetScriptExecStatusResp(
                RespContext_t* ctx,
                char * const strScript_full_name,
                const uint8_t u8Script_full_nameSize,
                const OBC_MICROPYTHON_Result_t eOp_result,
                const OBC_MICROPYTHON_stime_t * const sRequested_time,
                const OBC_MICROPYTHON_stime_t * const sTime_started,
                const uint32_t u32Duration_ms
)
{
#ifndef BIG_ENDIAN_PLATFORM
    obc_micropythonGetScriptExecStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(obc_micropythonGetScriptExecStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(obc_micropythonGetScriptExecStatusProtocolResponseData_t);

    if ((ctx != NULL) && (strScript_full_name != NULL) && (sRequested_time != NULL) && (sTime_started != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_MICROPYTHON;
        responseParams.hdr.funcId  = OBC_MICROPYTHON_GETSCRIPTEXECSTATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (strScript_full_name != NULL)
        {
            if (u8Script_full_nameSize > 0U)
            {
                // zero-out complete message buffer before copying user data to avoid confusion if
                // buffer is only partially filled-in by user
                (void) memset((void *) responseParams.data.strScript_full_name,
                              0U,
                              sizeof(responseParams.data.strScript_full_name));
                (void) memcpy((void *) responseParams.data.strScript_full_name,
                              (const void *) strScript_full_name,
                              MIN(u8Script_full_nameSize, sizeof(responseParams.data.strScript_full_name)));
            
                // add NULLZ termination for string types
                if (u8Script_full_nameSize < sizeof(responseParams.data.strScript_full_name))
                    responseParams.data.strScript_full_name[u8Script_full_nameSize] = '\0';
                else
                    responseParams.data.strScript_full_name[sizeof(responseParams.data.strScript_full_name) - 1] = '\0';
            }
            
            responseParams.data.u8Script_full_nameSize = MIN(u8Script_full_nameSize, sizeof(responseParams.data.strScript_full_name));
        }
        else
        {
            (void) memset((void *) responseParams.data.strScript_full_name,
                          0U,
                          sizeof(responseParams.data.strScript_full_name));
            responseParams.data.u8Script_full_nameSize = 0U;
        }
        responseParams.data.eOp_result = eOp_result;
        if (sRequested_time != NULL)
        {
            responseParams.data.sRequested_time = *(sRequested_time);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sRequested_time,
                          0U,
                          sizeof(responseParams.data.sRequested_time));
        }
        if (sTime_started != NULL)
        {
            responseParams.data.sTime_started = *(sTime_started);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sTime_started,
                          0U,
                          sizeof(responseParams.data.sTime_started));
        }
        responseParams.data.u32Duration_ms = u32Duration_ms;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(obc_micropythonGetScriptExecStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


