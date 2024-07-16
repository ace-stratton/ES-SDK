/*!
********************************************************************************************
* @file FP_OBC_AOCS_CNTRLProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface OBC_AOCS_CNTRL v1.0
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

#include "FP_OBC_AOCS_CNTRLProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define OBC_AOCS_CNTRL_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define OBC_AOCS_CNTRL_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLresetAOCSPMbuffProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLresetAOCSPMbuffProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingRequestData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLstartLoggingRequestData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLstartLoggingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLstartLoggingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetDataTypeForAssessmentResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetDataTypeForAssessmentRequestData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetDataTypeForAssessmentResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetThresholdLevelsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetThresholdLevelsResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetThresholdLevelsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetThresholdLevelsRequestData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetThresholdLevelsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetThresholdLevelsResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetThresholdLevelsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetPMOutputProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetPMOutputResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetPMOutputProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetConfigResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetUpdateIntervalProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetUpdateIntervalResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetUpdateIntervalProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetUpdateIntervalRequestData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetUpdateIntervalProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetUpdateIntervalResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetUpdateIntervalProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetSamplesToSkipProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetSamplesToSkipResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetSamplesToSkipProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetSamplesToSkipRequestData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetSamplesToSkipProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetSamplesToSkipResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetSamplesToSkipProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetAocsStateRequestData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetAocsStateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLsetAocsStateResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLsetAocsStateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_AOCS_CNTRLgetAocsStateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_AOCS_CNTRLgetAocsStateResponseData_t data;
} PACKED_STRUCT OBC_AOCS_CNTRLgetAocsStateProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_resetAOCSPMbuffReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getMaxTimeForAutoLoggingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setMaxTimeForAutoLoggingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_startLoggingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getDataTypeForAssessmentReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setDataTypeForAssessmentReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getThresholdLevelsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setThresholdLevelsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getPMOutputReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getUpdateIntervalReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setUpdateIntervalReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getSamplesToSkipReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setSamplesToSkipReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setAocsStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getAocsStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_AOCS_CNTRLProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static OBC_AOCS_CNTRL_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_AOCS_CNTRL_RESETAOCSPMBUFF_FUNC_ID, fs_resetAOCSPMbuffReq },
    { OBC_AOCS_CNTRL_GETMAXTIMEFORAUTOLOGGING_FUNC_ID, fs_getMaxTimeForAutoLoggingReq },
    { OBC_AOCS_CNTRL_SETMAXTIMEFORAUTOLOGGING_FUNC_ID, fs_setMaxTimeForAutoLoggingReq },
    { OBC_AOCS_CNTRL_STARTLOGGING_FUNC_ID, fs_startLoggingReq },
    { OBC_AOCS_CNTRL_GETDATATYPEFORASSESSMENT_FUNC_ID, fs_getDataTypeForAssessmentReq },
    { OBC_AOCS_CNTRL_SETDATATYPEFORASSESSMENT_FUNC_ID, fs_setDataTypeForAssessmentReq },
    { OBC_AOCS_CNTRL_GETTHRESHOLDLEVELS_FUNC_ID, fs_getThresholdLevelsReq },
    { OBC_AOCS_CNTRL_SETTHRESHOLDLEVELS_FUNC_ID, fs_setThresholdLevelsReq },
    { OBC_AOCS_CNTRL_GETPMOUTPUT_FUNC_ID, fs_getPMOutputReq },
    { OBC_AOCS_CNTRL_GETCONFIG_FUNC_ID, fs_getConfigReq },
    { OBC_AOCS_CNTRL_GETUPDATEINTERVAL_FUNC_ID, fs_getUpdateIntervalReq },
    { OBC_AOCS_CNTRL_SETUPDATEINTERVAL_FUNC_ID, fs_setUpdateIntervalReq },
    { OBC_AOCS_CNTRL_GETSAMPLESTOSKIP_FUNC_ID, fs_getSamplesToSkipReq },
    { OBC_AOCS_CNTRL_SETSAMPLESTOSKIP_FUNC_ID, fs_setSamplesToSkipReq },
    { OBC_AOCS_CNTRL_SETAOCSSTATE_FUNC_ID, fs_setAocsStateReq },
    { OBC_AOCS_CNTRL_GETAOCSSTATE_FUNC_ID, fs_getAocsStateReq }
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

static void fs_resetAOCSPMbuffReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLresetAOCSPMbuffProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLresetAOCSPMbuffProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLresetAOCSPMbuffProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandler(&requestCtx);
    }
}

static void fs_getMaxTimeForAutoLoggingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandler(&requestCtx);
    }
}

static void fs_setMaxTimeForAutoLoggingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_startLoggingReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLstartLoggingProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLstartLoggingProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_AOCS_CNTRLstartLoggingRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLstartLoggingProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_AOCS_CNTRLstartLoggingRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_startLoggingRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_startLoggingRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getDataTypeForAssessmentReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandler(&requestCtx);
    }
}

static void fs_setDataTypeForAssessmentReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_AOCS_CNTRLsetDataTypeForAssessmentRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_AOCS_CNTRLsetDataTypeForAssessmentRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getThresholdLevelsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetThresholdLevelsProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetThresholdLevelsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetThresholdLevelsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getThresholdLevelsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getThresholdLevelsRequestHandler(&requestCtx);
    }
}

static void fs_setThresholdLevelsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLsetThresholdLevelsProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLsetThresholdLevelsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_AOCS_CNTRLsetThresholdLevelsRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetThresholdLevelsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_AOCS_CNTRLsetThresholdLevelsRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_setThresholdLevelsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_setThresholdLevelsRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getPMOutputReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetPMOutputProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetPMOutputProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetPMOutputProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getPMOutputRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getPMOutputRequestHandler(&requestCtx);
    }
}

static void fs_getConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetConfigProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getConfigRequestHandler(&requestCtx);
    }
}

static void fs_getUpdateIntervalReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetUpdateIntervalProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetUpdateIntervalProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetUpdateIntervalProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getUpdateIntervalRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getUpdateIntervalRequestHandler(&requestCtx);
    }
}

static void fs_setUpdateIntervalReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLsetUpdateIntervalProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLsetUpdateIntervalProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_AOCS_CNTRLsetUpdateIntervalRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetUpdateIntervalProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_AOCS_CNTRLsetUpdateIntervalRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_setUpdateIntervalRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_setUpdateIntervalRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getSamplesToSkipReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetSamplesToSkipProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetSamplesToSkipProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetSamplesToSkipProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getSamplesToSkipRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getSamplesToSkipRequestHandler(&requestCtx);
    }
}

static void fs_setSamplesToSkipReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLsetSamplesToSkipProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLsetSamplesToSkipProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_AOCS_CNTRLsetSamplesToSkipRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetSamplesToSkipProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_AOCS_CNTRLsetSamplesToSkipRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_setSamplesToSkipRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_setSamplesToSkipRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_setAocsStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLsetAocsStateProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLsetAocsStateProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_AOCS_CNTRLsetAocsStateRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetAocsStateProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_AOCS_CNTRLsetAocsStateRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_setAocsStateRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_setAocsStateRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getAocsStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_AOCS_CNTRLgetAocsStateProtocolRequestData_t *fullrequest = (OBC_AOCS_CNTRLgetAocsStateProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetAocsStateProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_AOCS_CNTRL_getAocsStateRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_AOCS_CNTRL_getAocsStateRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void OBC_AOCS_CNTRL_registerServerApi(OBC_AOCS_CNTRL_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t OBC_AOCS_CNTRL_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_OBC_AOCS_CNTRLProtocolServerInfo;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_resetAOCSPMbuffResp(
                RespContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLresetAOCSPMbuffProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLresetAOCSPMbuffProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLresetAOCSPMbuffProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_RESETAOCSPMBUFF_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLresetAOCSPMbuffProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingResp(
                RespContext_t* ctx,
                const uint32_t u32MaxTimeForAutoLogging
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETMAXTIMEFORAUTOLOGGING_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32MaxTimeForAutoLogging = u32MaxTimeForAutoLogging;
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
                                            sizeof(OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_SETMAXTIMEFORAUTOLOGGING_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_startLoggingResp(
                RespContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLstartLoggingProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLstartLoggingProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLstartLoggingProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_STARTLOGGING_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLstartLoggingProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getDataTypeForAssessmentResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_logDataTypes_t eDataType
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETDATATYPEFORASSESSMENT_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eDataType = eDataType;
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
                                            sizeof(OBC_AOCS_CNTRLgetDataTypeForAssessmentProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setDataTypeForAssessmentResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_SETDATATYPEFORASSESSMENT_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLsetDataTypeForAssessmentProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getThresholdLevelsResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_thresholdValues_t * const asThreshold
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetThresholdLevelsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetThresholdLevelsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetThresholdLevelsProtocolResponseData_t);

    if ((ctx != NULL) && (asThreshold != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETTHRESHOLDLEVELS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (asThreshold != NULL)
        {
            (void) memcpy((void *) &responseParams.data.asThreshold,
                          (const void *) asThreshold,
                          sizeof(responseParams.data.asThreshold));
        }
        else
        {
            (void) memset((void *) &responseParams.data.asThreshold,
                          0U,
                          sizeof(responseParams.data.asThreshold));
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
                                            sizeof(OBC_AOCS_CNTRLgetThresholdLevelsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setThresholdLevelsResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLsetThresholdLevelsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLsetThresholdLevelsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetThresholdLevelsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_SETTHRESHOLDLEVELS_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLsetThresholdLevelsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getPMOutputResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_PMoutput_t * const asOutput
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetPMOutputProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetPMOutputProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetPMOutputProtocolResponseData_t);

    if ((ctx != NULL) && (asOutput != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETPMOUTPUT_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (asOutput != NULL)
        {
            (void) memcpy((void *) &responseParams.data.asOutput,
                          (const void *) asOutput,
                          sizeof(responseParams.data.asOutput));
        }
        else
        {
            (void) memset((void *) &responseParams.data.asOutput,
                          0U,
                          sizeof(responseParams.data.asOutput));
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
                                            sizeof(OBC_AOCS_CNTRLgetPMOutputProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getConfigResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_Config_t * const sCurrent_config
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetConfigProtocolResponseData_t);

    if ((ctx != NULL) && (sCurrent_config != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sCurrent_config != NULL)
        {
            responseParams.data.sCurrent_config = *(sCurrent_config);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sCurrent_config,
                          0U,
                          sizeof(responseParams.data.sCurrent_config));
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
                                            sizeof(OBC_AOCS_CNTRLgetConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getUpdateIntervalResp(
                RespContext_t* ctx,
                const uint8_t u8Update_interval
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetUpdateIntervalProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetUpdateIntervalProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetUpdateIntervalProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETUPDATEINTERVAL_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u8Update_interval = u8Update_interval;
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
                                            sizeof(OBC_AOCS_CNTRLgetUpdateIntervalProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setUpdateIntervalResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLsetUpdateIntervalProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLsetUpdateIntervalProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetUpdateIntervalProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_SETUPDATEINTERVAL_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLsetUpdateIntervalProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getSamplesToSkipResp(
                RespContext_t* ctx,
                const uint16_t u16Samples_to_skip
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetSamplesToSkipProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetSamplesToSkipProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetSamplesToSkipProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETSAMPLESTOSKIP_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u16Samples_to_skip = u16Samples_to_skip;
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
                                            sizeof(OBC_AOCS_CNTRLgetSamplesToSkipProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setSamplesToSkipResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLsetSamplesToSkipProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLsetSamplesToSkipProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetSamplesToSkipProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_SETSAMPLESTOSKIP_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLsetSamplesToSkipProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setAocsStateResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_AocsServiceError_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLsetAocsStateProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLsetAocsStateProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLsetAocsStateProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_SETAOCSSTATE_FUNCRESP_ID;
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
                                            sizeof(OBC_AOCS_CNTRLsetAocsStateProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getAocsStateResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_AocsServiceError_t eOpResult,
                const OBC_AOCS_CNTRL_AocsState_t eAocsState,
                const OBC_AOCS_CNTRL_AocsStateReqState_t eReqState
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_AOCS_CNTRLgetAocsStateProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_AOCS_CNTRLgetAocsStateProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_AOCS_CNTRLgetAocsStateProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL;
        responseParams.hdr.funcId  = OBC_AOCS_CNTRL_GETAOCSSTATE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
        responseParams.data.eAocsState = eAocsState;
        responseParams.data.eReqState = eReqState;
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
                                            sizeof(OBC_AOCS_CNTRLgetAocsStateProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


