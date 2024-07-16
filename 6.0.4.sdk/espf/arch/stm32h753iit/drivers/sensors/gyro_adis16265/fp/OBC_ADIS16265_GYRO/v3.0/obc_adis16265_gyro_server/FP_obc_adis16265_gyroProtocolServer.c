/*!
********************************************************************************************
* @file FP_obc_adis16265_gyroProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface obc_adis16265_gyro v3.0
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

#include "FP_obc_adis16265_gyroProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define obc_adis16265_gyro_PROTOCOL_VERSION_MAJOR   ((uint8_t) 3)
#define obc_adis16265_gyro_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_adis16265_gyroSET_GYROSCOPE_CONFIGRequestData_t data;
} PACKED_STRUCT obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_adis16265_gyroSET_GYROSCOPE_CONFIGResponseData_t data;
} PACKED_STRUCT obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_adis16265_gyroGET_GYROSCOPE_CONFIGResponseData_t data;
} PACKED_STRUCT obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGResponseData_t data;
} PACKED_STRUCT obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGResponseData_t data;
} PACKED_STRUCT obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_GYROSCOPE_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_GYROSCOPE_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SAVE_GYRO_PANEL_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_LOAD_GYRO_PANEL_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_obc_adis16265_gyroProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static obc_adis16265_gyro_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_ADIS16265_GYRO_SET_GYROSCOPE_CONFIG_FUNC_ID, fs_SET_GYROSCOPE_CONFIGReq },
    { OBC_ADIS16265_GYRO_GET_GYROSCOPE_CONFIG_FUNC_ID, fs_GET_GYROSCOPE_CONFIGReq },
    { OBC_ADIS16265_GYRO_SAVE_GYRO_PANEL_CONFIG_FUNC_ID, fs_SAVE_GYRO_PANEL_CONFIGReq },
    { OBC_ADIS16265_GYRO_LOAD_GYRO_PANEL_CONFIG_FUNC_ID, fs_LOAD_GYRO_PANEL_CONFIGReq }
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

static void fs_SET_GYROSCOPE_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolRequestData_t *fullrequest = (obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    obc_adis16265_gyroSET_GYROSCOPE_CONFIGRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (obc_adis16265_gyroSET_GYROSCOPE_CONFIGRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->obc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->obc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_GYROSCOPE_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolRequestData_t *fullrequest = (obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->obc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->obc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandler(&requestCtx);
    }
}

static void fs_SAVE_GYRO_PANEL_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolRequestData_t *fullrequest = (obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandler(&requestCtx);
    }
}

static void fs_LOAD_GYRO_PANEL_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolRequestData_t *fullrequest = (obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void obc_adis16265_gyro_registerServerApi(obc_adis16265_gyro_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t obc_adis16265_gyro_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_obc_adis16265_gyroProtocolServerInfo;
}

ESSATMAC_ErrCodes obc_adis16265_gyro_SET_GYROSCOPE_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO;
        responseParams.hdr.funcId  = OBC_ADIS16265_GYRO_SET_GYROSCOPE_CONFIG_FUNCRESP_ID;
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
                                            sizeof(obc_adis16265_gyroSET_GYROSCOPE_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes obc_adis16265_gyro_GET_GYROSCOPE_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_PANEL_t eX_AXIS_ACTIVE_PANEL,
                const OBC_ADIS16265_GYRO_PANEL_t eY_AXIS_ACTIVE_PANEL,
                const OBC_ADIS16265_GYRO_PANEL_t eZ_AXIS_ACTIVE_PANEL,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO;
        responseParams.hdr.funcId  = OBC_ADIS16265_GYRO_GET_GYROSCOPE_CONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eX_AXIS_ACTIVE_PANEL = eX_AXIS_ACTIVE_PANEL;
        responseParams.data.eY_AXIS_ACTIVE_PANEL = eY_AXIS_ACTIVE_PANEL;
        responseParams.data.eZ_AXIS_ACTIVE_PANEL = eZ_AXIS_ACTIVE_PANEL;
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
                                            sizeof(obc_adis16265_gyroGET_GYROSCOPE_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO;
        responseParams.hdr.funcId  = OBC_ADIS16265_GYRO_SAVE_GYRO_PANEL_CONFIG_FUNCRESP_ID;
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
                                            sizeof(obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO;
        responseParams.hdr.funcId  = OBC_ADIS16265_GYRO_LOAD_GYRO_PANEL_CONFIG_FUNCRESP_ID;
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
                                            sizeof(obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


