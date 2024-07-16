/*!
********************************************************************************************
* @file FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface OBC_ACTUATOR_CONTROL_SERVICE v3.0
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

#include "FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define OBC_ACTUATOR_CONTROL_SERVICE_PROTOCOL_VERSION_MAJOR   ((uint8_t) 3)
#define OBC_ACTUATOR_CONTROL_SERVICE_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ACTUATOR_CONTROL_SERVICESTARTResponseData_t data;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ACTUATOR_CONTROL_SERVICESTOPResponseData_t data;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSResponseData_t data;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLResponseData_t data;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_STARTReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_STOPReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_STATUSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_LAST_MTQ_CONTROLReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static OBC_ACTUATOR_CONTROL_SERVICE_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_ACTUATOR_CONTROL_SERVICE_START_FUNC_ID, fs_STARTReq },
    { OBC_ACTUATOR_CONTROL_SERVICE_STOP_FUNC_ID, fs_STOPReq },
    { OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUS_FUNC_ID, fs_GET_STATUSReq },
    { OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROL_FUNC_ID, fs_GET_LAST_MTQ_CONTROLReq }
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

static void fs_STARTReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolRequestData_t *fullrequest = (OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandler(&requestCtx);
    }
}

static void fs_STOPReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolRequestData_t *fullrequest = (OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandler(&requestCtx);
    }
}

static void fs_GET_STATUSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolRequestData_t *fullrequest = (OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandler(&requestCtx);
    }
}

static void fs_GET_LAST_MTQ_CONTROLReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolRequestData_t *fullrequest = (OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void OBC_ACTUATOR_CONTROL_SERVICE_registerServerApi(OBC_ACTUATOR_CONTROL_SERVICE_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t OBC_ACTUATOR_CONTROL_SERVICE_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServerInfo;
}

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_STARTResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE;
        responseParams.hdr.funcId  = OBC_ACTUATOR_CONTROL_SERVICE_START_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
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
                                            sizeof(OBC_ACTUATOR_CONTROL_SERVICESTARTProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_STOPResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE;
        responseParams.hdr.funcId  = OBC_ACTUATOR_CONTROL_SERVICE_STOP_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
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
                                            sizeof(OBC_ACTUATOR_CONTROL_SERVICESTOPProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_STATUS_t * const sCurrentStatus,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolResponseData_t);

    if ((ctx != NULL) && (sCurrentStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE;
        responseParams.hdr.funcId  = OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sCurrentStatus != NULL)
        {
            responseParams.data.sCurrentStatus = *(sCurrentStatus);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sCurrentStatus,
                          0U,
                          sizeof(responseParams.data.sCurrentStatus));
        }
        responseParams.data.eOpResult = eOpResult;
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
                                            sizeof(OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_LAST_MTQ_DATA_t * const sLastMagnetorquerValues,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolResponseData_t);

    if ((ctx != NULL) && (sLastMagnetorquerValues != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE;
        responseParams.hdr.funcId  = OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROL_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sLastMagnetorquerValues != NULL)
        {
            responseParams.data.sLastMagnetorquerValues = *(sLastMagnetorquerValues);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sLastMagnetorquerValues,
                          0U,
                          sizeof(responseParams.data.sLastMagnetorquerValues));
        }
        responseParams.data.eOpResult = eOpResult;
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
                                            sizeof(OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


