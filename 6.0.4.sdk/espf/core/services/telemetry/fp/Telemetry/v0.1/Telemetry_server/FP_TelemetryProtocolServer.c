/*!
********************************************************************************************
* @file FP_TelemetryProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface Telemetry v0.1
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

#include "FP_TelemetryProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define Telemetry_PROTOCOL_VERSION_MAJOR   ((uint8_t) 0)
#define Telemetry_PROTOCOL_VERSION_MINOR   ((uint8_t) 1)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetrygetTelemetryGeneralConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrygetTelemetryGeneralConfigResponseData_t data;
} PACKED_STRUCT TelemetrygetTelemetryGeneralConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryGeneralConfigRequestData_t data;
} PACKED_STRUCT TelemetrysetTelemetryGeneralConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryGeneralConfigResponseData_t data;
} PACKED_STRUCT TelemetrysetTelemetryGeneralConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetrygetTelemetryPresetConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrygetTelemetryPresetConfigResponseData_t data;
} PACKED_STRUCT TelemetrygetTelemetryPresetConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryPresetConfigRequestData_t data;
} PACKED_STRUCT TelemetrysetTelemetryPresetConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryPresetConfigResponseData_t data;
} PACKED_STRUCT TelemetrysetTelemetryPresetConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetActivePresetRequestData_t data;
} PACKED_STRUCT TelemetrysetActivePresetProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetActivePresetResponseData_t data;
} PACKED_STRUCT TelemetrysetActivePresetProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetrygetActivePresetProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrygetActivePresetResponseData_t data;
} PACKED_STRUCT TelemetrygetActivePresetProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetryrestoreActivePresetProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetryrestoreActivePresetResponseData_t data;
} PACKED_STRUCT TelemetryrestoreActivePresetProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetrygetTelemetryFileSinkConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrygetTelemetryFileSinkConfigResponseData_t data;
} PACKED_STRUCT TelemetrygetTelemetryFileSinkConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryFileSzLimitConfigRequestData_t data;
} PACKED_STRUCT TelemetrysetTelemetryFileSzLimitConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryFileSzLimitConfigResponseData_t data;
} PACKED_STRUCT TelemetrysetTelemetryFileSzLimitConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryFileTmLimitConfigRequestData_t data;
} PACKED_STRUCT TelemetrysetTelemetryFileTmLimitConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrysetTelemetryFileTmLimitConfigResponseData_t data;
} PACKED_STRUCT TelemetrysetTelemetryFileTmLimitConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetryresumeFileTelemetryProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetryresumeFileTelemetryResponseData_t data;
} PACKED_STRUCT TelemetryresumeFileTelemetryProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrypauseFileTelemetryRequestData_t data;
} PACKED_STRUCT TelemetrypauseFileTelemetryProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrypauseFileTelemetryResponseData_t data;
} PACKED_STRUCT TelemetrypauseFileTelemetryProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetrycleanTelemetryFilesProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrycleanTelemetryFilesResponseData_t data;
} PACKED_STRUCT TelemetrycleanTelemetryFilesProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT TelemetrygetTelemetryOperationStatsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    TelemetrygetTelemetryOperationStatsResponseData_t data;
} PACKED_STRUCT TelemetrygetTelemetryOperationStatsProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getTelemetryGeneralConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setTelemetryGeneralConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getTelemetryPresetConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setTelemetryPresetConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setActivePresetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getActivePresetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_restoreActivePresetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getTelemetryFileSinkConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setTelemetryFileSzLimitConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setTelemetryFileTmLimitConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_resumeFileTelemetryReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_pauseFileTelemetryReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_cleanTelemetryFilesReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getTelemetryOperationStatsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_TelemetryProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static Telemetry_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { TELEMETRY_GETTELEMETRYGENERALCONFIG_FUNC_ID, fs_getTelemetryGeneralConfigReq },
    { TELEMETRY_SETTELEMETRYGENERALCONFIG_FUNC_ID, fs_setTelemetryGeneralConfigReq },
    { TELEMETRY_GETTELEMETRYPRESETCONFIG_FUNC_ID, fs_getTelemetryPresetConfigReq },
    { TELEMETRY_SETTELEMETRYPRESETCONFIG_FUNC_ID, fs_setTelemetryPresetConfigReq },
    { TELEMETRY_SETACTIVEPRESET_FUNC_ID, fs_setActivePresetReq },
    { TELEMETRY_GETACTIVEPRESET_FUNC_ID, fs_getActivePresetReq },
    { TELEMETRY_RESTOREACTIVEPRESET_FUNC_ID, fs_restoreActivePresetReq },
    { TELEMETRY_GETTELEMETRYFILESINKCONFIG_FUNC_ID, fs_getTelemetryFileSinkConfigReq },
    { TELEMETRY_SETTELEMETRYFILESZLIMITCONFIG_FUNC_ID, fs_setTelemetryFileSzLimitConfigReq },
    { TELEMETRY_SETTELEMETRYFILETMLIMITCONFIG_FUNC_ID, fs_setTelemetryFileTmLimitConfigReq },
    { TELEMETRY_RESUMEFILETELEMETRY_FUNC_ID, fs_resumeFileTelemetryReq },
    { TELEMETRY_PAUSEFILETELEMETRY_FUNC_ID, fs_pauseFileTelemetryReq },
    { TELEMETRY_CLEANTELEMETRYFILES_FUNC_ID, fs_cleanTelemetryFilesReq },
    { TELEMETRY_GETTELEMETRYOPERATIONSTATS_FUNC_ID, fs_getTelemetryOperationStatsReq }
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

static void fs_getTelemetryGeneralConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrygetTelemetryGeneralConfigProtocolRequestData_t *fullrequest = (TelemetrygetTelemetryGeneralConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryGeneralConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_getTelemetryGeneralConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_getTelemetryGeneralConfigRequestHandler(&requestCtx);
    }
}

static void fs_setTelemetryGeneralConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrysetTelemetryGeneralConfigProtocolRequestData_t *fullrequest = (TelemetrysetTelemetryGeneralConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    TelemetrysetTelemetryGeneralConfigRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryGeneralConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (TelemetrysetTelemetryGeneralConfigRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_setTelemetryGeneralConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_setTelemetryGeneralConfigRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getTelemetryPresetConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrygetTelemetryPresetConfigProtocolRequestData_t *fullrequest = (TelemetrygetTelemetryPresetConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryPresetConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_getTelemetryPresetConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_getTelemetryPresetConfigRequestHandler(&requestCtx);
    }
}

static void fs_setTelemetryPresetConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrysetTelemetryPresetConfigProtocolRequestData_t *fullrequest = (TelemetrysetTelemetryPresetConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    TelemetrysetTelemetryPresetConfigRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryPresetConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (TelemetrysetTelemetryPresetConfigRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_setTelemetryPresetConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_setTelemetryPresetConfigRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_setActivePresetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrysetActivePresetProtocolRequestData_t *fullrequest = (TelemetrysetActivePresetProtocolRequestData_t *) fp_DataInfo->pu8Data;
    TelemetrysetActivePresetRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetActivePresetProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (TelemetrysetActivePresetRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_setActivePresetRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_setActivePresetRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getActivePresetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrygetActivePresetProtocolRequestData_t *fullrequest = (TelemetrygetActivePresetProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetActivePresetProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_getActivePresetRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_getActivePresetRequestHandler(&requestCtx);
    }
}

static void fs_restoreActivePresetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetryrestoreActivePresetProtocolRequestData_t *fullrequest = (TelemetryrestoreActivePresetProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetryrestoreActivePresetProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_restoreActivePresetRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_restoreActivePresetRequestHandler(&requestCtx);
    }
}

static void fs_getTelemetryFileSinkConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrygetTelemetryFileSinkConfigProtocolRequestData_t *fullrequest = (TelemetrygetTelemetryFileSinkConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryFileSinkConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_getTelemetryFileSinkConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_getTelemetryFileSinkConfigRequestHandler(&requestCtx);
    }
}

static void fs_setTelemetryFileSzLimitConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrysetTelemetryFileSzLimitConfigProtocolRequestData_t *fullrequest = (TelemetrysetTelemetryFileSzLimitConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    TelemetrysetTelemetryFileSzLimitConfigRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryFileSzLimitConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (TelemetrysetTelemetryFileSzLimitConfigRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_setTelemetryFileSzLimitConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_setTelemetryFileSzLimitConfigRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_setTelemetryFileTmLimitConfigReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrysetTelemetryFileTmLimitConfigProtocolRequestData_t *fullrequest = (TelemetrysetTelemetryFileTmLimitConfigProtocolRequestData_t *) fp_DataInfo->pu8Data;
    TelemetrysetTelemetryFileTmLimitConfigRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryFileTmLimitConfigProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (TelemetrysetTelemetryFileTmLimitConfigRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_setTelemetryFileTmLimitConfigRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_setTelemetryFileTmLimitConfigRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_resumeFileTelemetryReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetryresumeFileTelemetryProtocolRequestData_t *fullrequest = (TelemetryresumeFileTelemetryProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetryresumeFileTelemetryProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_resumeFileTelemetryRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_resumeFileTelemetryRequestHandler(&requestCtx);
    }
}

static void fs_pauseFileTelemetryReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrypauseFileTelemetryProtocolRequestData_t *fullrequest = (TelemetrypauseFileTelemetryProtocolRequestData_t *) fp_DataInfo->pu8Data;
    TelemetrypauseFileTelemetryRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrypauseFileTelemetryProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (TelemetrypauseFileTelemetryRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_pauseFileTelemetryRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_pauseFileTelemetryRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_cleanTelemetryFilesReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrycleanTelemetryFilesProtocolRequestData_t *fullrequest = (TelemetrycleanTelemetryFilesProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrycleanTelemetryFilesProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_cleanTelemetryFilesRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_cleanTelemetryFilesRequestHandler(&requestCtx);
    }
}

static void fs_getTelemetryOperationStatsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    TelemetrygetTelemetryOperationStatsProtocolRequestData_t *fullrequest = (TelemetrygetTelemetryOperationStatsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryOperationStatsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->Telemetry_getTelemetryOperationStatsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->Telemetry_getTelemetryOperationStatsRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void Telemetry_registerServerApi(Telemetry_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t Telemetry_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_TelemetryProtocolServerInfo;
}

ESSATMAC_ErrCodes Telemetry_getTelemetryGeneralConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_tlm_general_cfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrygetTelemetryGeneralConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrygetTelemetryGeneralConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryGeneralConfigProtocolResponseData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_GETTELEMETRYGENERALCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sCfg != NULL)
        {
            responseParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sCfg,
                          0U,
                          sizeof(responseParams.data.sCfg));
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
                                            sizeof(TelemetrygetTelemetryGeneralConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_setTelemetryGeneralConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrysetTelemetryGeneralConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrysetTelemetryGeneralConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryGeneralConfigProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_SETTELEMETRYGENERALCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetrysetTelemetryGeneralConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_getTelemetryPresetConfigResp(
                RespContext_t* ctx,
                const uint8_t u8Slot_preset_cnt,
                const uint8_t u8Max_tlm_msg_cnt,
                const TELEMETRY_tlm_preset_cfg_t * const asTelemetry_preset_cfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrygetTelemetryPresetConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrygetTelemetryPresetConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryPresetConfigProtocolResponseData_t);

    if ((ctx != NULL) && (asTelemetry_preset_cfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_GETTELEMETRYPRESETCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u8Slot_preset_cnt = u8Slot_preset_cnt;
        responseParams.data.u8Max_tlm_msg_cnt = u8Max_tlm_msg_cnt;
        if (asTelemetry_preset_cfg != NULL)
        {
            (void) memcpy((void *) &responseParams.data.asTelemetry_preset_cfg,
                          (const void *) asTelemetry_preset_cfg,
                          sizeof(responseParams.data.asTelemetry_preset_cfg));
        }
        else
        {
            (void) memset((void *) &responseParams.data.asTelemetry_preset_cfg,
                          0U,
                          sizeof(responseParams.data.asTelemetry_preset_cfg));
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
                                            sizeof(TelemetrygetTelemetryPresetConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_setTelemetryPresetConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrysetTelemetryPresetConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrysetTelemetryPresetConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryPresetConfigProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_SETTELEMETRYPRESETCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetrysetTelemetryPresetConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_setActivePresetResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes,
                const uint8_t u8Avail_presets_cnt
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrysetActivePresetProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrysetActivePresetProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetActivePresetProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_SETACTIVEPRESET_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
        responseParams.data.u8Avail_presets_cnt = u8Avail_presets_cnt;
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
                                            sizeof(TelemetrysetActivePresetProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_getActivePresetResp(
                RespContext_t* ctx,
                const uint8_t u8Active_preset_id
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrygetActivePresetProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrygetActivePresetProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetActivePresetProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_GETACTIVEPRESET_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u8Active_preset_id = u8Active_preset_id;
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
                                            sizeof(TelemetrygetActivePresetProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_restoreActivePresetResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetryrestoreActivePresetProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetryrestoreActivePresetProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetryrestoreActivePresetProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_RESTOREACTIVEPRESET_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetryrestoreActivePresetProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_getTelemetryFileSinkConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_tlm_file_logging_type_t eActive_file_cfg_type,
                const TELEMETRY_tlm_file_size_limit_cfg_t * const sSize_limit_cfg,
                const TELEMETRY_tlm_file_time_limit_cfg_t * const sTime_limit_cfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrygetTelemetryFileSinkConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrygetTelemetryFileSinkConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryFileSinkConfigProtocolResponseData_t);

    if ((ctx != NULL) && (sSize_limit_cfg != NULL) && (sTime_limit_cfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_GETTELEMETRYFILESINKCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eActive_file_cfg_type = eActive_file_cfg_type;
        if (sSize_limit_cfg != NULL)
        {
            responseParams.data.sSize_limit_cfg = *(sSize_limit_cfg);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sSize_limit_cfg,
                          0U,
                          sizeof(responseParams.data.sSize_limit_cfg));
        }
        if (sTime_limit_cfg != NULL)
        {
            responseParams.data.sTime_limit_cfg = *(sTime_limit_cfg);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sTime_limit_cfg,
                          0U,
                          sizeof(responseParams.data.sTime_limit_cfg));
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
                                            sizeof(TelemetrygetTelemetryFileSinkConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_setTelemetryFileSzLimitConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrysetTelemetryFileSzLimitConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrysetTelemetryFileSzLimitConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryFileSzLimitConfigProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_SETTELEMETRYFILESZLIMITCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetrysetTelemetryFileSzLimitConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_setTelemetryFileTmLimitConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrysetTelemetryFileTmLimitConfigProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrysetTelemetryFileTmLimitConfigProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrysetTelemetryFileTmLimitConfigProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_SETTELEMETRYFILETMLIMITCONFIG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetrysetTelemetryFileTmLimitConfigProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_resumeFileTelemetryResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetryresumeFileTelemetryProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetryresumeFileTelemetryProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetryresumeFileTelemetryProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_RESUMEFILETELEMETRY_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetryresumeFileTelemetryProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_pauseFileTelemetryResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrypauseFileTelemetryProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrypauseFileTelemetryProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrypauseFileTelemetryProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_PAUSEFILETELEMETRY_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetrypauseFileTelemetryProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_cleanTelemetryFilesResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrycleanTelemetryFilesProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrycleanTelemetryFilesProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrycleanTelemetryFilesProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_CLEANTELEMETRYFILES_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
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
                                            sizeof(TelemetrycleanTelemetryFilesProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes Telemetry_getTelemetryOperationStatsResp(
                RespContext_t* ctx,
                const TELEMETRY_tlm_stats_t * const sTelemetry_stats
)
{
#ifndef BIG_ENDIAN_PLATFORM
    TelemetrygetTelemetryOperationStatsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(TelemetrygetTelemetryOperationStatsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(TelemetrygetTelemetryOperationStatsProtocolResponseData_t);

    if ((ctx != NULL) && (sTelemetry_stats != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY;
        responseParams.hdr.funcId  = TELEMETRY_GETTELEMETRYOPERATIONSTATS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sTelemetry_stats != NULL)
        {
            responseParams.data.sTelemetry_stats = *(sTelemetry_stats);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sTelemetry_stats,
                          0U,
                          sizeof(responseParams.data.sTelemetry_stats));
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
                                            sizeof(TelemetrygetTelemetryOperationStatsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


