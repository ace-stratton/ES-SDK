/*!
********************************************************************************************
* @file FP_gnssProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface gnss v1.0
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

#include "FP_gnssProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define gnss_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define gnss_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    gnssset_powerRequestData_t data;
} PACKED_STRUCT gnssset_powerProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    gnssset_powerResponseData_t data;
} PACKED_STRUCT gnssset_powerProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT gnssget_powerProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    gnssget_powerResponseData_t data;
} PACKED_STRUCT gnssget_powerProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_powerReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_powerReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_gnssProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_GNSS,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static gnss_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { GNSS_SET_POWER_FUNC_ID, fs_set_powerReq },
    { GNSS_GET_POWER_FUNC_ID, fs_get_powerReq }
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

static void fs_set_powerReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    gnssset_powerProtocolRequestData_t *fullrequest = (gnssset_powerProtocolRequestData_t *) fp_DataInfo->pu8Data;
    gnssset_powerRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(gnssset_powerProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (gnssset_powerRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->gnss_set_powerRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->gnss_set_powerRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_powerReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    gnssget_powerProtocolRequestData_t *fullrequest = (gnssget_powerProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(gnssget_powerProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->gnss_get_powerRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->gnss_get_powerRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void gnss_registerServerApi(gnss_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t gnss_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_gnssProtocolServerInfo;
}

ESSATMAC_ErrCodes gnss_set_powerResp(
                RespContext_t* ctx,
                const GNSS_operation_t eOp_status
)
{
#ifndef BIG_ENDIAN_PLATFORM
    gnssset_powerProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(gnssset_powerProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(gnssset_powerProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_GNSS;
        responseParams.hdr.funcId  = GNSS_SET_POWER_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_status = eOp_status;
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
                                            sizeof(gnssset_powerProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes gnss_get_powerResp(
                RespContext_t* ctx,
                const GNSS_operation_t eOp_status,
                const GNSS_power_t ePwr_status
)
{
#ifndef BIG_ENDIAN_PLATFORM
    gnssget_powerProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(gnssget_powerProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(gnssget_powerProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_GNSS;
        responseParams.hdr.funcId  = GNSS_GET_POWER_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_status = eOp_status;
        responseParams.data.ePwr_status = ePwr_status;
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
                                            sizeof(gnssget_powerProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


