/*!
********************************************************************************************
* @file FP_SPProtocolClient.c
* @brief ESSA Stack client-side implementation
********************************************************************************************
* @version           interface SP v0.4
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

#include "FP_SPProtocolClient.h"

#define SP_PROTOCOL_VERSION_MAJOR   ((uint8_t) 0)
#define SP_PROTOCOL_VERSION_MINOR   ((uint8_t) 4)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPGetSoftwareVersionProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetSoftwareVersionResponseData_t data;
} PACKED_STRUCT SPGetSoftwareVersionProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPStartDeploymentRequestData_t data;
} PACKED_STRUCT SPStartDeploymentProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPStartDeploymentProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPGetDeploymentStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetDeploymentStatusResponseData_t data;
} PACKED_STRUCT SPGetDeploymentStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPGetUptimeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetUptimeResponseData_t data;
} PACKED_STRUCT SPGetUptimeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPGetTelemetryProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetTelemetryResponseData_t data;
} PACKED_STRUCT SPGetTelemetryProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPGetMainGyroDataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetMainGyroDataResponseData_t data;
} PACKED_STRUCT SPGetMainGyroDataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPGetExtGyroDataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetExtGyroDataResponseData_t data;
} PACKED_STRUCT SPGetExtGyroDataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPWriteMainGyroRegisterRequestData_t data;
} PACKED_STRUCT SPWriteMainGyroRegisterProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPWriteMainGyroRegisterProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPWriteExtGyroRegisterRequestData_t data;
} PACKED_STRUCT SPWriteExtGyroRegisterProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPWriteExtGyroRegisterProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetMainGyroRegisterRequestData_t data;
} PACKED_STRUCT SPGetMainGyroRegisterProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetMainGyroRegisterResponseData_t data;
} PACKED_STRUCT SPGetMainGyroRegisterProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetExtGyroRegisterRequestData_t data;
} PACKED_STRUCT SPGetExtGyroRegisterProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetExtGyroRegisterResponseData_t data;
} PACKED_STRUCT SPGetExtGyroRegisterProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPRestartFMWProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPRestartFMWProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPWriteMTQParametersRequestData_t data;
} PACKED_STRUCT SPWriteMTQParametersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPWriteMTQParametersResponseData_t data;
} PACKED_STRUCT SPWriteMTQParametersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SPGetMTQParametersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SPGetMTQParametersResponseData_t data;
} PACKED_STRUCT SPGetMTQParametersProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetSoftwareVersionResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_StartDeploymentResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetDeploymentStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetUptimeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetTelemetryResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMainGyroDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetExtGyroDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteMainGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteExtGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMainGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetExtGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_RestartFMWResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteMTQParametersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMTQParametersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_SPProtocolClientInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_SP,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static SP_ClientApi_t *pCliApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { SP_GETSOFTWAREVERSION_FUNCRESP_ID, fs_GetSoftwareVersionResp },
    { SP_STARTDEPLOYMENT_FUNCRESP_ID, fs_StartDeploymentResp },
    { SP_GETDEPLOYMENTSTATUS_FUNCRESP_ID, fs_GetDeploymentStatusResp },
    { SP_GETUPTIME_FUNCRESP_ID, fs_GetUptimeResp },
    { SP_GETTELEMETRY_FUNCRESP_ID, fs_GetTelemetryResp },
    { SP_GETMAINGYRODATA_FUNCRESP_ID, fs_GetMainGyroDataResp },
    { SP_GETEXTGYRODATA_FUNCRESP_ID, fs_GetExtGyroDataResp },
    { SP_WRITEMAINGYROREGISTER_FUNCRESP_ID, fs_WriteMainGyroRegisterResp },
    { SP_WRITEEXTGYROREGISTER_FUNCRESP_ID, fs_WriteExtGyroRegisterResp },
    { SP_GETMAINGYROREGISTER_FUNCRESP_ID, fs_GetMainGyroRegisterResp },
    { SP_GETEXTGYROREGISTER_FUNCRESP_ID, fs_GetExtGyroRegisterResp },
    { SP_RESTARTFMW_FUNCRESP_ID, fs_RestartFMWResp },
    { SP_WRITEMTQPARAMETERS_FUNCRESP_ID, fs_WriteMTQParametersResp },
    { SP_GETMTQPARAMETERS_FUNCRESP_ID, fs_GetMTQParametersResp }
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

    if (IS_RESPONSE(*pHdr))
    {
        pHdr->funcId = GET_FUNC_ID(*pHdr);

        for (i = 0; i < COUNT_OF(fs_aFuncArray); i++)
        {
            if (fs_aFuncArray[i].funcId == pHdr->funcId)
            {
                if (fs_aFuncArray[i].pfFunc != NULL)
                {
                    fs_aFuncArray[i].pfFunc(fp_DataInfo);

                    bIsFuncSupported = true;
                }

                break;
            }
        }
    }

    return bIsFuncSupported;
}

static void fs_GetSoftwareVersionResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetSoftwareVersionProtocolResponseData_t *fullresponse = (SPGetSoftwareVersionProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetSoftwareVersionResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetSoftwareVersionProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetSoftwareVersionResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetSoftwareVersionResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetSoftwareVersionResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_StartDeploymentResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPStartDeploymentProtocolResponseData_t *fullresponse = (SPStartDeploymentProtocolResponseData_t *) fp_DataInfo->pu8Data;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPStartDeploymentProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_StartDeploymentResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_StartDeploymentResponseHandler(&responseCtx);
    }
}

static void fs_GetDeploymentStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetDeploymentStatusProtocolResponseData_t *fullresponse = (SPGetDeploymentStatusProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetDeploymentStatusResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetDeploymentStatusProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetDeploymentStatusResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetDeploymentStatusResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetDeploymentStatusResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetUptimeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetUptimeProtocolResponseData_t *fullresponse = (SPGetUptimeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetUptimeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetUptimeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetUptimeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetUptimeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetUptimeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetTelemetryResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetTelemetryProtocolResponseData_t *fullresponse = (SPGetTelemetryProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetTelemetryResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetTelemetryProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetTelemetryResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetTelemetryResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetTelemetryResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetMainGyroDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetMainGyroDataProtocolResponseData_t *fullresponse = (SPGetMainGyroDataProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetMainGyroDataResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetMainGyroDataProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetMainGyroDataResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetMainGyroDataResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetMainGyroDataResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetExtGyroDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetExtGyroDataProtocolResponseData_t *fullresponse = (SPGetExtGyroDataProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetExtGyroDataResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetExtGyroDataProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetExtGyroDataResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetExtGyroDataResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetExtGyroDataResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteMainGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPWriteMainGyroRegisterProtocolResponseData_t *fullresponse = (SPWriteMainGyroRegisterProtocolResponseData_t *) fp_DataInfo->pu8Data;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPWriteMainGyroRegisterProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_WriteMainGyroRegisterResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_WriteMainGyroRegisterResponseHandler(&responseCtx);
    }
}

static void fs_WriteExtGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPWriteExtGyroRegisterProtocolResponseData_t *fullresponse = (SPWriteExtGyroRegisterProtocolResponseData_t *) fp_DataInfo->pu8Data;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPWriteExtGyroRegisterProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_WriteExtGyroRegisterResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_WriteExtGyroRegisterResponseHandler(&responseCtx);
    }
}

static void fs_GetMainGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetMainGyroRegisterProtocolResponseData_t *fullresponse = (SPGetMainGyroRegisterProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetMainGyroRegisterResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetMainGyroRegisterProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetMainGyroRegisterResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetMainGyroRegisterResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetMainGyroRegisterResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetExtGyroRegisterResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetExtGyroRegisterProtocolResponseData_t *fullresponse = (SPGetExtGyroRegisterProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetExtGyroRegisterResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetExtGyroRegisterProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetExtGyroRegisterResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetExtGyroRegisterResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetExtGyroRegisterResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_RestartFMWResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPRestartFMWProtocolResponseData_t *fullresponse = (SPRestartFMWProtocolResponseData_t *) fp_DataInfo->pu8Data;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPRestartFMWProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_RestartFMWResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_RestartFMWResponseHandler(&responseCtx);
    }
}

static void fs_WriteMTQParametersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPWriteMTQParametersProtocolResponseData_t *fullresponse = (SPWriteMTQParametersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPWriteMTQParametersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPWriteMTQParametersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPWriteMTQParametersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_WriteMTQParametersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_WriteMTQParametersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetMTQParametersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SPGetMTQParametersProtocolResponseData_t *fullresponse = (SPGetMTQParametersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SPGetMTQParametersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SPGetMTQParametersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SPGetMTQParametersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SP_GetMTQParametersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SP_GetMTQParametersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void SP_registerClientApi(SP_ClientApi_t *pCliApiHandlers)
{
    pCliApiHnd = pCliApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t SP_getClientProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_SPProtocolClientInfo;
}

ESSATMAC_ErrCodes SP_GetSoftwareVersionReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetSoftwareVersionProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetSoftwareVersionProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetSoftwareVersionProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETSOFTWAREVERSION_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetSoftwareVersionProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_StartDeploymentReq(
                ReqContext_t* ctx,
                const SP_DepCMD_t eDeployCommand
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPStartDeploymentProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPStartDeploymentProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPStartDeploymentProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_STARTDEPLOYMENT_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eDeployCommand = eDeployCommand;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPStartDeploymentProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetDeploymentStatusReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetDeploymentStatusProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetDeploymentStatusProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetDeploymentStatusProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETDEPLOYMENTSTATUS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetDeploymentStatusProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetUptimeReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetUptimeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetUptimeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetUptimeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETUPTIME_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetUptimeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetTelemetryReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetTelemetryProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetTelemetryProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetTelemetryProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETTELEMETRY_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetTelemetryProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetMainGyroDataReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetMainGyroDataProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetMainGyroDataProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetMainGyroDataProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETMAINGYRODATA_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetMainGyroDataProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetExtGyroDataReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetExtGyroDataProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetExtGyroDataProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetExtGyroDataProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETEXTGYRODATA_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetExtGyroDataProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_WriteMainGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8WriteMainGyroRegisterAddress,
                const uint16_t u16WriteMainGyroRegisterValue
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPWriteMainGyroRegisterProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPWriteMainGyroRegisterProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPWriteMainGyroRegisterProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_WRITEMAINGYROREGISTER_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8WriteMainGyroRegisterAddress = u8WriteMainGyroRegisterAddress;
        requestParams.data.u16WriteMainGyroRegisterValue = u16WriteMainGyroRegisterValue;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPWriteMainGyroRegisterProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_WriteExtGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8WriteExtGyroRegisterAddress,
                const uint16_t u16WriteExtGyroRegisterValue
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPWriteExtGyroRegisterProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPWriteExtGyroRegisterProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPWriteExtGyroRegisterProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_WRITEEXTGYROREGISTER_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8WriteExtGyroRegisterAddress = u8WriteExtGyroRegisterAddress;
        requestParams.data.u16WriteExtGyroRegisterValue = u16WriteExtGyroRegisterValue;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPWriteExtGyroRegisterProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetMainGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8ReadMainGyroRegisterAdress
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetMainGyroRegisterProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetMainGyroRegisterProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetMainGyroRegisterProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETMAINGYROREGISTER_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8ReadMainGyroRegisterAdress = u8ReadMainGyroRegisterAdress;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetMainGyroRegisterProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetExtGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8ReadExtGyroRegisterAddress
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetExtGyroRegisterProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetExtGyroRegisterProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetExtGyroRegisterProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETEXTGYROREGISTER_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8ReadExtGyroRegisterAddress = u8ReadExtGyroRegisterAddress;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetExtGyroRegisterProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_RestartFMWReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPRestartFMWProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPRestartFMWProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPRestartFMWProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_RESTARTFMW_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPRestartFMWProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_WriteMTQParametersReq(
                ReqContext_t* ctx,
                const SP_MTQ_Mode_t eMode,
                const uint8_t u8WriteMTQDutyCycle
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPWriteMTQParametersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPWriteMTQParametersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPWriteMTQParametersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_WRITEMTQPARAMETERS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eMode = eMode;
        requestParams.data.u8WriteMTQDutyCycle = u8WriteMTQDutyCycle;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPWriteMTQParametersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SP_GetMTQParametersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SPGetMTQParametersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SPGetMTQParametersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SPGetMTQParametersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SP;
        requestParams.hdr.funcId  = SP_GETMTQPARAMETERS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(SPGetMTQParametersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


