/*!
********************************************************************************************
* @file FP_OBC_ES_ADCSProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface OBC_ES_ADCS v3.0
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

#include "FP_OBC_ES_ADCSProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define OBC_ES_ADCS_PROTOCOL_VERSION_MAJOR   ((uint8_t) 3)
#define OBC_ES_ADCS_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_OP_MODERequestData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_OP_MODEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_OP_MODEResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_OP_MODEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_OP_MODEProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_OP_MODEResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_OP_MODEProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_ESTIMATORSRequestData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_ESTIMATORSProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_ESTIMATORSResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_ESTIMATORSProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_ESTIMATORSProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_ESTIMATORSResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_ESTIMATORSProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_CONTROLLERRequestData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLERProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_CONTROLLERResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLERProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_CONTROLLERProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_CONTROLLERResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_CONTROLLERProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUSProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_STATUSResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUSProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_STATUS_ESTIMATORSResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_STATUS_CONTROLLERResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGRequestData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_MAGNETOMETERRequestData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_MAGNETOMETERProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_MAGNETOMETERResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_MAGNETOMETERProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_MAGNETOMETERProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_MAGNETOMETERResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_MAGNETOMETERProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_ADCS_CONFIGRequestData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_ADCS_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSET_ADCS_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSSET_ADCS_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSGET_ADCS_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSGET_ADCS_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSGET_ADCS_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSSAVE_ADCS_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_ES_ADCSLOAD_ADCS_CONFIGResponseData_t data;
} PACKED_STRUCT OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_OP_MODEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_OP_MODEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_ESTIMATORSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_ESTIMATORSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_CONTROLLERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_CONTROLLERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_STATUSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_STATUS_ESTIMATORSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_STATUS_CONTROLLERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_CONTROLLER_BDOT_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_CONTROLLER_BDOT_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_MAGNETOMETERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_MAGNETOMETERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SET_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GET_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SAVE_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_LOAD_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_ES_ADCSProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static OBC_ES_ADCS_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_ES_ADCS_SET_OP_MODE_FUNC_ID, fs_SET_OP_MODEReq },
    { OBC_ES_ADCS_GET_OP_MODE_FUNC_ID, fs_GET_OP_MODEReq },
    { OBC_ES_ADCS_SET_ESTIMATORS_FUNC_ID, fs_SET_ESTIMATORSReq },
    { OBC_ES_ADCS_GET_ESTIMATORS_FUNC_ID, fs_GET_ESTIMATORSReq },
    { OBC_ES_ADCS_SET_CONTROLLER_FUNC_ID, fs_SET_CONTROLLERReq },
    { OBC_ES_ADCS_GET_CONTROLLER_FUNC_ID, fs_GET_CONTROLLERReq },
    { OBC_ES_ADCS_GET_STATUS_FUNC_ID, fs_GET_STATUSReq },
    { OBC_ES_ADCS_GET_STATUS_ESTIMATORS_FUNC_ID, fs_GET_STATUS_ESTIMATORSReq },
    { OBC_ES_ADCS_GET_STATUS_CONTROLLER_FUNC_ID, fs_GET_STATUS_CONTROLLERReq },
    { OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIG_FUNC_ID, fs_SET_CONTROLLER_BDOT_CONFIGReq },
    { OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIG_FUNC_ID, fs_GET_CONTROLLER_BDOT_CONFIGReq },
    { OBC_ES_ADCS_SET_MAGNETOMETER_FUNC_ID, fs_SET_MAGNETOMETERReq },
    { OBC_ES_ADCS_GET_MAGNETOMETER_FUNC_ID, fs_GET_MAGNETOMETERReq },
    { OBC_ES_ADCS_SET_ADCS_CONFIG_FUNC_ID, fs_SET_ADCS_CONFIGReq },
    { OBC_ES_ADCS_GET_ADCS_CONFIG_FUNC_ID, fs_GET_ADCS_CONFIGReq },
    { OBC_ES_ADCS_SAVE_ADCS_CONFIG_FUNC_ID, fs_SAVE_ADCS_CONFIGReq },
    { OBC_ES_ADCS_LOAD_ADCS_CONFIG_FUNC_ID, fs_LOAD_ADCS_CONFIGReq }
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

static void fs_SET_OP_MODEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSSET_OP_MODEProtocolRequestData_t *fullrequest = (OBC_ES_ADCSSET_OP_MODEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_ADCSSET_OP_MODERequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_OP_MODEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_ADCSSET_OP_MODERequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_SET_OP_MODERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_SET_OP_MODERequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_OP_MODEReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_OP_MODEProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_OP_MODEProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_OP_MODEProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_OP_MODERequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_OP_MODERequestHandler(&requestCtx);
    }
}

static void fs_SET_ESTIMATORSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSSET_ESTIMATORSProtocolRequestData_t *fullrequest = (OBC_ES_ADCSSET_ESTIMATORSProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_ADCSSET_ESTIMATORSRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_ESTIMATORSProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_ADCSSET_ESTIMATORSRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_SET_ESTIMATORSRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_SET_ESTIMATORSRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_ESTIMATORSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_ESTIMATORSProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_ESTIMATORSProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_ESTIMATORSProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_ESTIMATORSRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_ESTIMATORSRequestHandler(&requestCtx);
    }
}

static void fs_SET_CONTROLLERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSSET_CONTROLLERProtocolRequestData_t *fullrequest = (OBC_ES_ADCSSET_CONTROLLERProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_ADCSSET_CONTROLLERRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_CONTROLLERProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_ADCSSET_CONTROLLERRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_SET_CONTROLLERRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_SET_CONTROLLERRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_CONTROLLERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_CONTROLLERProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_CONTROLLERProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_CONTROLLERProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_CONTROLLERRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_CONTROLLERRequestHandler(&requestCtx);
    }
}

static void fs_GET_STATUSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_STATUSProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_STATUSProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_STATUSProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_STATUSRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_STATUSRequestHandler(&requestCtx);
    }
}

static void fs_GET_STATUS_ESTIMATORSReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandler(&requestCtx);
    }
}

static void fs_GET_STATUS_CONTROLLERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandler(&requestCtx);
    }
}

static void fs_SET_CONTROLLER_BDOT_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_CONTROLLER_BDOT_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandler(&requestCtx);
    }
}

static void fs_SET_MAGNETOMETERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSSET_MAGNETOMETERProtocolRequestData_t *fullrequest = (OBC_ES_ADCSSET_MAGNETOMETERProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_ADCSSET_MAGNETOMETERRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_MAGNETOMETERProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_ADCSSET_MAGNETOMETERRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_SET_MAGNETOMETERRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_SET_MAGNETOMETERRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_MAGNETOMETERReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_MAGNETOMETERProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_MAGNETOMETERProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_MAGNETOMETERProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_MAGNETOMETERRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_MAGNETOMETERRequestHandler(&requestCtx);
    }
}

static void fs_SET_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSSET_ADCS_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_ADCSSET_ADCS_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_ES_ADCSSET_ADCS_CONFIGRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_ADCS_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_ES_ADCSSET_ADCS_CONFIGRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_SET_ADCS_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_SET_ADCS_CONFIGRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_GET_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSGET_ADCS_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_ADCSGET_ADCS_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_ADCS_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_GET_ADCS_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_GET_ADCS_CONFIGRequestHandler(&requestCtx);
    }
}

static void fs_SAVE_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandler(&requestCtx);
    }
}

static void fs_LOAD_ADCS_CONFIGReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolRequestData_t *fullrequest = (OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void OBC_ES_ADCS_registerServerApi(OBC_ES_ADCS_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t OBC_ES_ADCS_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_OBC_ES_ADCSProtocolServerInfo;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_OP_MODEResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSSET_OP_MODEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSSET_OP_MODEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_OP_MODEProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_SET_OP_MODE_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSSET_OP_MODEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_OP_MODEResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_OP_MODES_t eActiveMode,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_OP_MODEProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_OP_MODEProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_OP_MODEProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_OP_MODE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eActiveMode = eActiveMode;
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
                                            sizeof(OBC_ES_ADCSGET_OP_MODEProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_ESTIMATORSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSSET_ESTIMATORSProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSSET_ESTIMATORSProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_ESTIMATORSProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_SET_ESTIMATORS_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSSET_ESTIMATORSProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_ESTIMATORSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator1,
                const OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator2,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_ESTIMATORSProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_ESTIMATORSProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_ESTIMATORSProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_ESTIMATORS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eActiveEstimator1 = eActiveEstimator1;
        responseParams.data.eActiveEstimator2 = eActiveEstimator2;
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
                                            sizeof(OBC_ES_ADCSGET_ESTIMATORSProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_CONTROLLERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSSET_CONTROLLERProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSSET_CONTROLLERProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_CONTROLLERProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_SET_CONTROLLER_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSSET_CONTROLLERProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_CONTROLLERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONTROLLER_t eActiveController,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_CONTROLLERProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_CONTROLLERProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_CONTROLLERProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_CONTROLLER_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eActiveController = eActiveController;
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
                                            sizeof(OBC_ES_ADCSGET_CONTROLLERProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_STATUSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_STATUS_t * const sCurrentStatus,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_STATUSProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_STATUSProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_STATUSProtocolResponseData_t);

    if ((ctx != NULL) && (sCurrentStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_STATUS_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSGET_STATUSProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_STATUS_ESTIMATORSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_ESTIMATOR_STATUS_t * const sCurrentStatusEstimators,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolResponseData_t);

    if ((ctx != NULL) && (sCurrentStatusEstimators != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_STATUS_ESTIMATORS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sCurrentStatusEstimators != NULL)
        {
            responseParams.data.sCurrentStatusEstimators = *(sCurrentStatusEstimators);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sCurrentStatusEstimators,
                          0U,
                          sizeof(responseParams.data.sCurrentStatusEstimators));
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
                                            sizeof(OBC_ES_ADCSGET_STATUS_ESTIMATORSProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_STATUS_CONTROLLERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONTROLLER_STATUS_t * const sCurrentStatusController,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolResponseData_t);

    if ((ctx != NULL) && (sCurrentStatusController != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_STATUS_CONTROLLER_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sCurrentStatusController != NULL)
        {
            responseParams.data.sCurrentStatusController = *(sCurrentStatusController);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sCurrentStatusController,
                          0U,
                          sizeof(responseParams.data.sCurrentStatusController));
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
                                            sizeof(OBC_ES_ADCSGET_STATUS_CONTROLLERProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIG_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONTROLLER_BDOT_CONFIG_t * const sActiveBdotConfig,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t);

    if ((ctx != NULL) && (sActiveBdotConfig != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sActiveBdotConfig != NULL)
        {
            responseParams.data.sActiveBdotConfig = *(sActiveBdotConfig);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sActiveBdotConfig,
                          0U,
                          sizeof(responseParams.data.sActiveBdotConfig));
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
                                            sizeof(OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_MAGNETOMETERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSSET_MAGNETOMETERProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSSET_MAGNETOMETERProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_MAGNETOMETERProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_SET_MAGNETOMETER_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSSET_MAGNETOMETERProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_MAGNETOMETERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_USED_MAGNETOMETER_t eActiveMagnetometer,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_MAGNETOMETERProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_MAGNETOMETERProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_MAGNETOMETERProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_MAGNETOMETER_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eActiveMagnetometer = eActiveMagnetometer;
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
                                            sizeof(OBC_ES_ADCSGET_MAGNETOMETERProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSSET_ADCS_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSSET_ADCS_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSET_ADCS_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_SET_ADCS_CONFIG_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSSET_ADCS_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONFIG_t * const sActiveConfig,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSGET_ADCS_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSGET_ADCS_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSGET_ADCS_CONFIGProtocolResponseData_t);

    if ((ctx != NULL) && (sActiveConfig != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_GET_ADCS_CONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sActiveConfig != NULL)
        {
            responseParams.data.sActiveConfig = *(sActiveConfig);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sActiveConfig,
                          0U,
                          sizeof(responseParams.data.sActiveConfig));
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
                                            sizeof(OBC_ES_ADCSGET_ADCS_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_SAVE_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_SAVE_ADCS_CONFIG_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSSAVE_ADCS_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_ES_ADCS_LOAD_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS;
        responseParams.hdr.funcId  = OBC_ES_ADCS_LOAD_ADCS_CONFIG_FUNCRESP_ID;
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
                                            sizeof(OBC_ES_ADCSLOAD_ADCS_CONFIGProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


