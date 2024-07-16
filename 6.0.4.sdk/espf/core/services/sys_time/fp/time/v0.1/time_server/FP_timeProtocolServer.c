/*!
********************************************************************************************
* @file FP_timeProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface time v0.1
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

#include "FP_timeProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define time_PROTOCOL_VERSION_MAJOR   ((uint8_t) 0)
#define time_PROTOCOL_VERSION_MINOR   ((uint8_t) 1)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeset_dateRequestData_t data;
} PACKED_STRUCT timeset_dateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeset_dateResponseData_t data;
} PACKED_STRUCT timeset_dateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT timeget_dateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeget_dateResponseData_t data;
} PACKED_STRUCT timeget_dateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeset_timeRequestData_t data;
} PACKED_STRUCT timeset_timeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeset_timeResponseData_t data;
} PACKED_STRUCT timeset_timeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT timeget_timeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeget_timeResponseData_t data;
} PACKED_STRUCT timeget_timeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeenable_calibration_outputRequestData_t data;
} PACKED_STRUCT timeenable_calibration_outputProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeenable_calibration_outputResponseData_t data;
} PACKED_STRUCT timeenable_calibration_outputProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeconfigure_rtc_calibration_parametersRequestData_t data;
} PACKED_STRUCT timeconfigure_rtc_calibration_parametersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeconfigure_rtc_calibration_parametersResponseData_t data;
} PACKED_STRUCT timeconfigure_rtc_calibration_parametersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT timeretrieve_rtc_calibration_parametersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeretrieve_rtc_calibration_parametersResponseData_t data;
} PACKED_STRUCT timeretrieve_rtc_calibration_parametersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT timeget_rtc_clock_sourceProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    timeget_rtc_clock_sourceResponseData_t data;
} PACKED_STRUCT timeget_rtc_clock_sourceProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_dateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_dateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_timeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_timeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_enable_calibration_outputReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_configure_rtc_calibration_parametersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_retrieve_rtc_calibration_parametersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_rtc_clock_sourceReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_timeProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_TIME,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static time_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { TIME_SET_DATE_FUNC_ID, fs_set_dateReq },
    { TIME_GET_DATE_FUNC_ID, fs_get_dateReq },
    { TIME_SET_TIME_FUNC_ID, fs_set_timeReq },
    { TIME_GET_TIME_FUNC_ID, fs_get_timeReq },
    { TIME_ENABLE_CALIBRATION_OUTPUT_FUNC_ID, fs_enable_calibration_outputReq },
    { TIME_CONFIGURE_RTC_CALIBRATION_PARAMETERS_FUNC_ID, fs_configure_rtc_calibration_parametersReq },
    { TIME_RETRIEVE_RTC_CALIBRATION_PARAMETERS_FUNC_ID, fs_retrieve_rtc_calibration_parametersReq },
    { TIME_GET_RTC_CLOCK_SOURCE_FUNC_ID, fs_get_rtc_clock_sourceReq }
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

static void fs_set_dateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeset_dateProtocolRequestData_t *fullrequest = (timeset_dateProtocolRequestData_t *) fp_DataInfo->pu8Data;
    timeset_dateRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeset_dateProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (timeset_dateRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_set_dateRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_set_dateRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_dateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeget_dateProtocolRequestData_t *fullrequest = (timeget_dateProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeget_dateProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_get_dateRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_get_dateRequestHandler(&requestCtx);
    }
}

static void fs_set_timeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeset_timeProtocolRequestData_t *fullrequest = (timeset_timeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    timeset_timeRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeset_timeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (timeset_timeRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_set_timeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_set_timeRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_timeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeget_timeProtocolRequestData_t *fullrequest = (timeget_timeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeget_timeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_get_timeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_get_timeRequestHandler(&requestCtx);
    }
}

static void fs_enable_calibration_outputReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeenable_calibration_outputProtocolRequestData_t *fullrequest = (timeenable_calibration_outputProtocolRequestData_t *) fp_DataInfo->pu8Data;
    timeenable_calibration_outputRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeenable_calibration_outputProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (timeenable_calibration_outputRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_enable_calibration_outputRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_enable_calibration_outputRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_configure_rtc_calibration_parametersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeconfigure_rtc_calibration_parametersProtocolRequestData_t *fullrequest = (timeconfigure_rtc_calibration_parametersProtocolRequestData_t *) fp_DataInfo->pu8Data;
    timeconfigure_rtc_calibration_parametersRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeconfigure_rtc_calibration_parametersProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (timeconfigure_rtc_calibration_parametersRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_configure_rtc_calibration_parametersRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_configure_rtc_calibration_parametersRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_retrieve_rtc_calibration_parametersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeretrieve_rtc_calibration_parametersProtocolRequestData_t *fullrequest = (timeretrieve_rtc_calibration_parametersProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeretrieve_rtc_calibration_parametersProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_retrieve_rtc_calibration_parametersRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_retrieve_rtc_calibration_parametersRequestHandler(&requestCtx);
    }
}

static void fs_get_rtc_clock_sourceReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    timeget_rtc_clock_sourceProtocolRequestData_t *fullrequest = (timeget_rtc_clock_sourceProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(timeget_rtc_clock_sourceProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->time_get_rtc_clock_sourceRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->time_get_rtc_clock_sourceRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void time_registerServerApi(time_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t time_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_timeProtocolServerInfo;
}

ESSATMAC_ErrCodes time_set_dateResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeset_dateProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeset_dateProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeset_dateProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_SET_DATE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(timeset_dateProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes time_get_dateResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus,
                const TIME_sdate_t * const sDate
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeget_dateProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeget_dateProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeget_dateProtocolResponseData_t);

    if ((ctx != NULL) && (sDate != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_GET_DATE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
        if (sDate != NULL)
        {
            responseParams.data.sDate = *(sDate);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sDate,
                          0U,
                          sizeof(responseParams.data.sDate));
        }
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
                                            sizeof(timeget_dateProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes time_set_timeResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeset_timeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeset_timeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeset_timeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_SET_TIME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(timeset_timeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes time_get_timeResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus,
                const TIME_stime_t * const sTime
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeget_timeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeget_timeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeget_timeProtocolResponseData_t);

    if ((ctx != NULL) && (sTime != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_GET_TIME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
        if (sTime != NULL)
        {
            responseParams.data.sTime = *(sTime);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sTime,
                          0U,
                          sizeof(responseParams.data.sTime));
        }
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
                                            sizeof(timeget_timeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes time_enable_calibration_outputResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeenable_calibration_outputProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeenable_calibration_outputProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeenable_calibration_outputProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_ENABLE_CALIBRATION_OUTPUT_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(timeenable_calibration_outputProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes time_configure_rtc_calibration_parametersResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeconfigure_rtc_calibration_parametersProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeconfigure_rtc_calibration_parametersProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeconfigure_rtc_calibration_parametersProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_CONFIGURE_RTC_CALIBRATION_PARAMETERS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(timeconfigure_rtc_calibration_parametersProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes time_retrieve_rtc_calibration_parametersResp(
                RespContext_t* ctx,
                const TIME_calp_pulses_t eCalp,
                const uint16_t u16Calm
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeretrieve_rtc_calibration_parametersProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeretrieve_rtc_calibration_parametersProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeretrieve_rtc_calibration_parametersProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_RETRIEVE_RTC_CALIBRATION_PARAMETERS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eCalp = eCalp;
        responseParams.data.u16Calm = u16Calm;
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
                                            sizeof(timeretrieve_rtc_calibration_parametersProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes time_get_rtc_clock_sourceResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus,
                const TIME_s_rtc_info_t * const sInfo
)
{
#ifndef BIG_ENDIAN_PLATFORM
    timeget_rtc_clock_sourceProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(timeget_rtc_clock_sourceProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(timeget_rtc_clock_sourceProtocolResponseData_t);

    if ((ctx != NULL) && (sInfo != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TIME;
        responseParams.hdr.funcId  = TIME_GET_RTC_CLOCK_SOURCE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
        if (sInfo != NULL)
        {
            responseParams.data.sInfo = *(sInfo);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sInfo,
                          0U,
                          sizeof(responseParams.data.sInfo));
        }
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
                                            sizeof(timeget_rtc_clock_sourceProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


