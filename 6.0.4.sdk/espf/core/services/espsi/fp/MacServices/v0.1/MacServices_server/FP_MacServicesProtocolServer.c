/*!
********************************************************************************************
* @file FP_MacServicesProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface MacServices v0.1
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

#include "FP_MacServicesProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define MacServices_PROTOCOL_VERSION_MAJOR   ((uint8_t) 0)
#define MacServices_PROTOCOL_VERSION_MINOR   ((uint8_t) 1)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    MacServicesgetMacBusTerminationSettingRequestData_t data;
} PACKED_STRUCT MacServicesgetMacBusTerminationSettingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    MacServicesgetMacBusTerminationSettingResponseData_t data;
} PACKED_STRUCT MacServicesgetMacBusTerminationSettingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    MacServicessetMacBusTerminationSettingRequestData_t data;
} PACKED_STRUCT MacServicessetMacBusTerminationSettingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT MacServicessetMacBusTerminationSettingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    MacServicessetMacAddressRequestData_t data;
} PACKED_STRUCT MacServicessetMacAddressProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    MacServicessetMacAddressResponseData_t data;
} PACKED_STRUCT MacServicessetMacAddressProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getMacBusTerminationSettingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setMacBusTerminationSettingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setMacAddressReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_MacServicesProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static MacServices_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { MACSERVICES_GETMACBUSTERMINATIONSETTING_FUNC_ID, fs_getMacBusTerminationSettingReq },
    { MACSERVICES_SETMACBUSTERMINATIONSETTING_FUNC_ID, fs_setMacBusTerminationSettingReq },
    { MACSERVICES_SETMACADDRESS_FUNC_ID, fs_setMacAddressReq }
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

static void fs_getMacBusTerminationSettingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    MacServicesgetMacBusTerminationSettingProtocolRequestData_t *fullrequest = (MacServicesgetMacBusTerminationSettingProtocolRequestData_t *) fp_DataInfo->pu8Data;
    MacServicesgetMacBusTerminationSettingRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(MacServicesgetMacBusTerminationSettingProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (MacServicesgetMacBusTerminationSettingRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->MacServices_getMacBusTerminationSettingRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->MacServices_getMacBusTerminationSettingRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_setMacBusTerminationSettingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    MacServicessetMacBusTerminationSettingProtocolRequestData_t *fullrequest = (MacServicessetMacBusTerminationSettingProtocolRequestData_t *) fp_DataInfo->pu8Data;
    MacServicessetMacBusTerminationSettingRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(MacServicessetMacBusTerminationSettingProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (MacServicessetMacBusTerminationSettingRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->MacServices_setMacBusTerminationSettingRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->MacServices_setMacBusTerminationSettingRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_setMacAddressReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    MacServicessetMacAddressProtocolRequestData_t *fullrequest = (MacServicessetMacAddressProtocolRequestData_t *) fp_DataInfo->pu8Data;
    MacServicessetMacAddressRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(MacServicessetMacAddressProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (MacServicessetMacAddressRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->MacServices_setMacAddressRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->MacServices_setMacAddressRequestHandler(&requestCtx,
                                        requestPayload);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void MacServices_registerServerApi(MacServices_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t MacServices_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_MacServicesProtocolServerInfo;
}

ESSATMAC_ErrCodes MacServices_getMacBusTerminationSettingResp(
                RespContext_t* ctx,
                const uint8_t u8SupportedInterfacesBitField,
                const uint8_t u8BusTerminationSettingsBitField
)
{
#ifndef BIG_ENDIAN_PLATFORM
    MacServicesgetMacBusTerminationSettingProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(MacServicesgetMacBusTerminationSettingProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(MacServicesgetMacBusTerminationSettingProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES;
        responseParams.hdr.funcId  = MACSERVICES_GETMACBUSTERMINATIONSETTING_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u8SupportedInterfacesBitField = u8SupportedInterfacesBitField;
        responseParams.data.u8BusTerminationSettingsBitField = u8BusTerminationSettingsBitField;
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
                                            sizeof(MacServicesgetMacBusTerminationSettingProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes MacServices_setMacBusTerminationSettingResp(
                RespContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    MacServicessetMacBusTerminationSettingProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(MacServicessetMacBusTerminationSettingProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(MacServicessetMacBusTerminationSettingProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES;
        responseParams.hdr.funcId  = MACSERVICES_SETMACBUSTERMINATIONSETTING_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

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
                                            sizeof(MacServicessetMacBusTerminationSettingProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes MacServices_setMacAddressResp(
                RespContext_t* ctx,
                const uint8_t u8UpdatedMacAddr
)
{
#ifndef BIG_ENDIAN_PLATFORM
    MacServicessetMacAddressProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(MacServicessetMacAddressProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(MacServicessetMacAddressProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES;
        responseParams.hdr.funcId  = MACSERVICES_SETMACADDRESS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u8UpdatedMacAddr = u8UpdatedMacAddr;
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
                                            sizeof(MacServicessetMacAddressProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


