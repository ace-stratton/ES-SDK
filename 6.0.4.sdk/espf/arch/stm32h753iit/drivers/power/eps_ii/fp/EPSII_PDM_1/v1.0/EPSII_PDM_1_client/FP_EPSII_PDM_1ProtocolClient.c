/*!
********************************************************************************************
* @file FP_EPSII_PDM_1ProtocolClient.c
* @brief ESSA Stack client-side implementation
********************************************************************************************
* @version           interface EPSII_PDM_1 v1.0
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

#include "FP_EPSII_PDM_1ProtocolClient.h"

#define EPSII_PDM_1_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define EPSII_PDM_1_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetDeviceInfoProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetDeviceInfoResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetDeviceInfoProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetPowerDistributionInfoProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetPowerDistributionInfoResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetPowerDistributionInfoProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetDeviceHealthInfoProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetDeviceHealthInfoResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetDeviceHealthInfoProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1SetPC104GPIORequestData_t data;
} PACKED_STRUCT EPSII_PDM_1SetPC104GPIOProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1SetPC104GPIOResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1SetPC104GPIOProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetPC104GPIOProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetPC104GPIOResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetPC104GPIOProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetRAWSensorsRequestData_t data;
} PACKED_STRUCT EPSII_PDM_1GetRAWSensorsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetRAWSensorsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetRAWSensorsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1SetPowerOutputsRequestData_t data;
} PACKED_STRUCT EPSII_PDM_1SetPowerOutputsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1SetPowerOutputsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1SetPowerOutputsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetPowerOutputsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetPowerOutputsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetPowerOutputsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1SetBasicSettingsRequestData_t data;
} PACKED_STRUCT EPSII_PDM_1SetBasicSettingsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1SetBasicSettingsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1SetBasicSettingsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetBasicSettingsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetBasicSettingsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetBasicSettingsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetBasicAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetBasicAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetBasicAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetBasicAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetBasicAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetBasicAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetMainAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetMainAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetMainAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetMainAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetMainAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetMainAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1OnESCP_ResetMainAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1OnESCP_ResetMainAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1OnESCP_ResetBasicAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1OnESCP_ResetBasicAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetBulkTelemetryProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetBulkTelemetryResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetBulkTelemetryProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1ResetDeviceProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1ResetDeviceResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1ResetDeviceProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1ForceInstallMainAppProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1ForceInstallMainAppResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1ForceInstallMainAppProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1ForceInstallBasicAppProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1ForceInstallBasicAppResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1ForceInstallBasicAppProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1GetBootLoaderErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1GetBootLoaderErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1GetBootLoaderErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_PDM_1ResetBootLdrErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_PDM_1ResetBootLdrErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_PDM_1ResetBootLdrErrCountersProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetDeviceInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetPowerDistributionInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetDeviceHealthInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetPC104GPIOResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetPC104GPIOResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetRAWSensorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetPowerOutputsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetPowerOutputsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBulkTelemetryResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ResetDeviceResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ForceInstallMainAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ForceInstallBasicAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBootLoaderErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ResetBootLdrErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_EPSII_PDM_1ProtocolClientInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static EPSII_PDM_1_ClientApi_t *pCliApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { EPSII_PDM_1_GETDEVICEINFO_FUNCRESP_ID, fs_GetDeviceInfoResp },
    { EPSII_PDM_1_GETPOWERDISTRIBUTIONINFO_FUNCRESP_ID, fs_GetPowerDistributionInfoResp },
    { EPSII_PDM_1_GETDEVICEHEALTHINFO_FUNCRESP_ID, fs_GetDeviceHealthInfoResp },
    { EPSII_PDM_1_SETPC104GPIO_FUNCRESP_ID, fs_SetPC104GPIOResp },
    { EPSII_PDM_1_GETPC104GPIO_FUNCRESP_ID, fs_GetPC104GPIOResp },
    { EPSII_PDM_1_GETRAWSENSORS_FUNCRESP_ID, fs_GetRAWSensorsResp },
    { EPSII_PDM_1_SETPOWEROUTPUTS_FUNCRESP_ID, fs_SetPowerOutputsResp },
    { EPSII_PDM_1_GETPOWEROUTPUTS_FUNCRESP_ID, fs_GetPowerOutputsResp },
    { EPSII_PDM_1_SETBASICSETTINGS_FUNCRESP_ID, fs_SetBasicSettingsResp },
    { EPSII_PDM_1_GETBASICSETTINGS_FUNCRESP_ID, fs_GetBasicSettingsResp },
    { EPSII_PDM_1_GETBASICAPPEXCEPTIONS_FUNCRESP_ID, fs_GetBasicAppExceptionsResp },
    { EPSII_PDM_1_GETBASICAPPERRCOUNTERS_FUNCRESP_ID, fs_GetBasicAppErrCountersResp },
    { EPSII_PDM_1_GETMAINAPPEXCEPTIONS_FUNCRESP_ID, fs_GetMainAppExceptionsResp },
    { EPSII_PDM_1_GETMAINAPPERRCOUNTERS_FUNCRESP_ID, fs_GetMainAppErrCountersResp },
    { EPSII_PDM_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNCRESP_ID, fs_OnESCP_ResetMainAppErrCountersResp },
    { EPSII_PDM_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNCRESP_ID, fs_OnESCP_ResetMainAppExceptionsResp },
    { EPSII_PDM_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNCRESP_ID, fs_OnESCP_ResetBasicAppErrCountersResp },
    { EPSII_PDM_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNCRESP_ID, fs_OnESCP_ResetBasicAppExceptionsResp },
    { EPSII_PDM_1_GETBULKTELEMETRY_FUNCRESP_ID, fs_GetBulkTelemetryResp },
    { EPSII_PDM_1_RESETDEVICE_FUNCRESP_ID, fs_ResetDeviceResp },
    { EPSII_PDM_1_FORCEINSTALLMAINAPP_FUNCRESP_ID, fs_ForceInstallMainAppResp },
    { EPSII_PDM_1_FORCEINSTALLBASICAPP_FUNCRESP_ID, fs_ForceInstallBasicAppResp },
    { EPSII_PDM_1_GETBOOTLOADERERRCOUNTERS_FUNCRESP_ID, fs_GetBootLoaderErrCountersResp },
    { EPSII_PDM_1_RESETBOOTLDRERRCOUNTERS_FUNCRESP_ID, fs_ResetBootLdrErrCountersResp }
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

static void fs_GetDeviceInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetDeviceInfoProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetDeviceInfoProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetDeviceInfoResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetDeviceInfoProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetDeviceInfoResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetDeviceInfoResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetDeviceInfoResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetPowerDistributionInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetPowerDistributionInfoProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetPowerDistributionInfoProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetPowerDistributionInfoResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetPowerDistributionInfoProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetPowerDistributionInfoResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetPowerDistributionInfoResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetPowerDistributionInfoResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetDeviceHealthInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetDeviceHealthInfoProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetDeviceHealthInfoProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetDeviceHealthInfoResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetDeviceHealthInfoProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetDeviceHealthInfoResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetDeviceHealthInfoResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetDeviceHealthInfoResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetPC104GPIOResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1SetPC104GPIOProtocolResponseData_t *fullresponse = (EPSII_PDM_1SetPC104GPIOProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1SetPC104GPIOResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1SetPC104GPIOProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1SetPC104GPIOResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_SetPC104GPIOResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_SetPC104GPIOResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetPC104GPIOResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetPC104GPIOProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetPC104GPIOProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetPC104GPIOResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetPC104GPIOProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetPC104GPIOResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetPC104GPIOResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetPC104GPIOResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetRAWSensorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetRAWSensorsProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetRAWSensorsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetRAWSensorsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetRAWSensorsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetRAWSensorsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetRAWSensorsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetRAWSensorsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetPowerOutputsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1SetPowerOutputsProtocolResponseData_t *fullresponse = (EPSII_PDM_1SetPowerOutputsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1SetPowerOutputsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1SetPowerOutputsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1SetPowerOutputsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_SetPowerOutputsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_SetPowerOutputsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetPowerOutputsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetPowerOutputsProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetPowerOutputsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetPowerOutputsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetPowerOutputsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetPowerOutputsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetPowerOutputsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetPowerOutputsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1SetBasicSettingsProtocolResponseData_t *fullresponse = (EPSII_PDM_1SetBasicSettingsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1SetBasicSettingsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1SetBasicSettingsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1SetBasicSettingsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_SetBasicSettingsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_SetBasicSettingsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetBasicSettingsProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetBasicSettingsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetBasicSettingsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBasicSettingsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetBasicSettingsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetBasicSettingsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetBasicSettingsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetBasicAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetBasicAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetBasicAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBasicAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetBasicAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetBasicAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetBasicAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetBasicAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetBasicAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetBasicAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBasicAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetBasicAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetBasicAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetBasicAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetMainAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetMainAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetMainAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetMainAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetMainAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetMainAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetMainAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetMainAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetMainAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetMainAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetMainAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetMainAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetMainAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetMainAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1OnESCP_ResetMainAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1OnESCP_ResetMainAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1OnESCP_ResetMainAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1OnESCP_ResetMainAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1OnESCP_ResetBasicAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1OnESCP_ResetBasicAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1OnESCP_ResetBasicAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1OnESCP_ResetBasicAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBulkTelemetryResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetBulkTelemetryProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetBulkTelemetryProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetBulkTelemetryResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBulkTelemetryProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetBulkTelemetryResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetBulkTelemetryResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetBulkTelemetryResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ResetDeviceResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1ResetDeviceProtocolResponseData_t *fullresponse = (EPSII_PDM_1ResetDeviceProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1ResetDeviceResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ResetDeviceProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1ResetDeviceResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_ResetDeviceResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_ResetDeviceResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ForceInstallMainAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1ForceInstallMainAppProtocolResponseData_t *fullresponse = (EPSII_PDM_1ForceInstallMainAppProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1ForceInstallMainAppResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ForceInstallMainAppProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1ForceInstallMainAppResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_ForceInstallMainAppResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_ForceInstallMainAppResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ForceInstallBasicAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1ForceInstallBasicAppProtocolResponseData_t *fullresponse = (EPSII_PDM_1ForceInstallBasicAppProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1ForceInstallBasicAppResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ForceInstallBasicAppProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1ForceInstallBasicAppResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_ForceInstallBasicAppResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_ForceInstallBasicAppResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBootLoaderErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1GetBootLoaderErrCountersProtocolResponseData_t *fullresponse = (EPSII_PDM_1GetBootLoaderErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1GetBootLoaderErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBootLoaderErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1GetBootLoaderErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_GetBootLoaderErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_GetBootLoaderErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ResetBootLdrErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_PDM_1ResetBootLdrErrCountersProtocolResponseData_t *fullresponse = (EPSII_PDM_1ResetBootLdrErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_PDM_1ResetBootLdrErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ResetBootLdrErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_PDM_1ResetBootLdrErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_PDM_1_ResetBootLdrErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_PDM_1_ResetBootLdrErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void EPSII_PDM_1_registerClientApi(EPSII_PDM_1_ClientApi_t *pCliApiHandlers)
{
    pCliApiHnd = pCliApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t EPSII_PDM_1_getClientProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_EPSII_PDM_1ProtocolClientInfo;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetDeviceInfoReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetDeviceInfoProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetDeviceInfoProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetDeviceInfoProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETDEVICEINFO_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetDeviceInfoProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetPowerDistributionInfoReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetPowerDistributionInfoProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetPowerDistributionInfoProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetPowerDistributionInfoProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETPOWERDISTRIBUTIONINFO_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetPowerDistributionInfoProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetDeviceHealthInfoReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetDeviceHealthInfoProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetDeviceHealthInfoProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetDeviceHealthInfoProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETDEVICEHEALTHINFO_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetDeviceHealthInfoProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_SetPC104GPIOReq(
                ReqContext_t* ctx,
                const EPSII_PDM_1_SGGPIO_Bitmask_t eFilterMask,
                const EPSII_PDM_1_SGGPIO_OnOff_mask_t eValuesMaskReq
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1SetPC104GPIOProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1SetPC104GPIOProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1SetPC104GPIOProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_SETPC104GPIO_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eFilterMask = eFilterMask;
        requestParams.data.eValuesMaskReq = eValuesMaskReq;
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
                                            sizeof(EPSII_PDM_1SetPC104GPIOProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetPC104GPIOReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetPC104GPIOProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetPC104GPIOProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetPC104GPIOProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETPC104GPIO_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetPC104GPIOProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetRAWSensorsReq(
                ReqContext_t* ctx,
                const uint32_t u32PktIDReq,
                const EPSII_PDM_1_ESEPSII_PDM_SensorIDs_t * const aeSensorsIDs
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetRAWSensorsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetRAWSensorsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetRAWSensorsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETRAWSENSORS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u32PktIDReq = u32PktIDReq;
        if (aeSensorsIDs != NULL)
        {
            (void) memcpy((void *) requestParams.data.aeSensorsIDs,
                          (const void *) aeSensorsIDs,
                          sizeof(requestParams.data.aeSensorsIDs));
        }
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
                                            sizeof(EPSII_PDM_1GetRAWSensorsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_SetPowerOutputsReq(
                ReqContext_t* ctx,
                const EPSII_PDM_1_SGPO_Bitmask_t eFilterMask,
                const EPSII_PDM_1_SGPO_ON_Off_Bitmask_t eValuesMask
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1SetPowerOutputsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1SetPowerOutputsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1SetPowerOutputsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_SETPOWEROUTPUTS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eFilterMask = eFilterMask;
        requestParams.data.eValuesMask = eValuesMask;
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
                                            sizeof(EPSII_PDM_1SetPowerOutputsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetPowerOutputsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetPowerOutputsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetPowerOutputsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetPowerOutputsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETPOWEROUTPUTS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetPowerOutputsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_SetBasicSettingsReq(
                ReqContext_t* ctx,
                const EPSII_PDM_1_SBasicSettings_t * const sBasicSettings
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1SetBasicSettingsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1SetBasicSettingsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1SetBasicSettingsProtocolRequestData_t);

    if ((ctx != NULL) && (sBasicSettings != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_SETBASICSETTINGS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sBasicSettings != NULL)
        {
            requestParams.data.sBasicSettings = *(sBasicSettings);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sBasicSettings,
                          0U,
                          sizeof(requestParams.data.sBasicSettings));
        }
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
                                            sizeof(EPSII_PDM_1SetBasicSettingsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetBasicSettingsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetBasicSettingsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetBasicSettingsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBasicSettingsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETBASICSETTINGS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetBasicSettingsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetBasicAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetBasicAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetBasicAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBasicAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETBASICAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetBasicAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetBasicAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetBasicAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetBasicAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBasicAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETBASICAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetBasicAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetMainAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetMainAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetMainAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetMainAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETMAINAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetMainAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetMainAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetMainAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetMainAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetMainAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETMAINAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetMainAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetMainAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetMainAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetBulkTelemetryReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetBulkTelemetryProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetBulkTelemetryProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBulkTelemetryProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETBULKTELEMETRY_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetBulkTelemetryProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_ResetDeviceReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1ResetDeviceProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1ResetDeviceProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ResetDeviceProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_RESETDEVICE_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1ResetDeviceProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_ForceInstallMainAppReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1ForceInstallMainAppProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1ForceInstallMainAppProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ForceInstallMainAppProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_FORCEINSTALLMAINAPP_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1ForceInstallMainAppProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_ForceInstallBasicAppReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1ForceInstallBasicAppProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1ForceInstallBasicAppProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ForceInstallBasicAppProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_FORCEINSTALLBASICAPP_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1ForceInstallBasicAppProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_GetBootLoaderErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1GetBootLoaderErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1GetBootLoaderErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1GetBootLoaderErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_GETBOOTLOADERERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1GetBootLoaderErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_PDM_1_ResetBootLdrErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_PDM_1ResetBootLdrErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_PDM_1ResetBootLdrErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_PDM_1ResetBootLdrErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1;
        requestParams.hdr.funcId  = EPSII_PDM_1_RESETBOOTLDRERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_PDM_1ResetBootLdrErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


