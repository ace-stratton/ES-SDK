/*!
********************************************************************************************
* @file FP_EPSII_BP_1ProtocolClient.c
* @brief ESSA Stack client-side implementation
********************************************************************************************
* @version           interface EPSII_BP_1 v3.0
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

#include "FP_EPSII_BP_1ProtocolClient.h"

#define EPSII_BP_1_PROTOCOL_VERSION_MAJOR   ((uint8_t) 3)
#define EPSII_BP_1_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetDeviceInfoProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetDeviceInfoResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetDeviceInfoProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetRAWSensorsRequestData_t data;
} PACKED_STRUCT EPSII_BP_1GetRAWSensorsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetRAWSensorsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetRAWSensorsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetBatteryInfoProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBatteryInfoResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBatteryInfoProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetDeviceHealthInfoProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetDeviceHealthInfoResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetDeviceHealthInfoProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetBatHeaterSettingsRequestData_t data;
} PACKED_STRUCT EPSII_BP_1SetBatHeaterSettingsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetBatHeaterSettingsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1SetBatHeaterSettingsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetBatHeaterSettingsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBatHeaterSettingsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBatHeaterSettingsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetBasicSettingsRequestData_t data;
} PACKED_STRUCT EPSII_BP_1SetBasicSettingsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetBasicSettingsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1SetBasicSettingsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetBasicSettingsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBasicSettingsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBasicSettingsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetBasicAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBasicAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBasicAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetBasicAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBasicAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBasicAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetMainAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetMainAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetMainAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetMainAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetMainAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetMainAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetMainAppErrCounters2ProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetMainAppErrCounters2ResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetMainAppErrCounters2ProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1OnESCP_ResetMainAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1OnESCP_ResetMainAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1OnESCP_ResetBasicAppErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1OnESCP_ResetBasicAppExceptionsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBalancerStatusRequestData_t data;
} PACKED_STRUCT EPSII_BP_1GetBalancerStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBalancerStatusResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBalancerStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1ResetDeviceProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1ResetDeviceResponseData_t data;
} PACKED_STRUCT EPSII_BP_1ResetDeviceProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1ForceInstallMainAppProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1ForceInstallMainAppResponseData_t data;
} PACKED_STRUCT EPSII_BP_1ForceInstallMainAppProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1ForceInstallBasicAppProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1ForceInstallBasicAppResponseData_t data;
} PACKED_STRUCT EPSII_BP_1ForceInstallBasicAppProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetBootLoaderErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBootLoaderErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBootLoaderErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1ResetBootLdrErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1ResetBootLdrErrCountersResponseData_t data;
} PACKED_STRUCT EPSII_BP_1ResetBootLdrErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetChargerSettingsRequestData_t data;
} PACKED_STRUCT EPSII_BP_1SetChargerSettingsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetChargerSettingsResponseData_t data;
} PACKED_STRUCT EPSII_BP_1SetChargerSettingsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetRTCRequestData_t data;
} PACKED_STRUCT EPSII_BP_1SetRTCProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1SetRTCResponseData_t data;
} PACKED_STRUCT EPSII_BP_1SetRTCProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetRTCProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetRTCResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetRTCProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1LeaveNoHibModeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1LeaveNoHibModeResponseData_t data;
} PACKED_STRUCT EPSII_BP_1LeaveNoHibModeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1RequestPowerDownProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1RequestPowerDownResponseData_t data;
} PACKED_STRUCT EPSII_BP_1RequestPowerDownProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT EPSII_BP_1GetBpModeSmRollingTraceProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    EPSII_BP_1GetBpModeSmRollingTraceResponseData_t data;
} PACKED_STRUCT EPSII_BP_1GetBpModeSmRollingTraceProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetDeviceInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetRAWSensorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBatteryInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetDeviceHealthInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetBatHeaterSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBatHeaterSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetMainAppErrCounters2Resp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_OnESCP_ResetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBalancerStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ResetDeviceResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ForceInstallMainAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ForceInstallBasicAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBootLoaderErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ResetBootLdrErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetChargerSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetRTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetRTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_LeaveNoHibModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_RequestPowerDownResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBpModeSmRollingTraceResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_EPSII_BP_1ProtocolClientInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static EPSII_BP_1_ClientApi_t *pCliApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { EPSII_BP_1_GETDEVICEINFO_FUNCRESP_ID, fs_GetDeviceInfoResp },
    { EPSII_BP_1_GETRAWSENSORS_FUNCRESP_ID, fs_GetRAWSensorsResp },
    { EPSII_BP_1_GETBATTERYINFO_FUNCRESP_ID, fs_GetBatteryInfoResp },
    { EPSII_BP_1_GETDEVICEHEALTHINFO_FUNCRESP_ID, fs_GetDeviceHealthInfoResp },
    { EPSII_BP_1_SETBATHEATERSETTINGS_FUNCRESP_ID, fs_SetBatHeaterSettingsResp },
    { EPSII_BP_1_GETBATHEATERSETTINGS_FUNCRESP_ID, fs_GetBatHeaterSettingsResp },
    { EPSII_BP_1_SETBASICSETTINGS_FUNCRESP_ID, fs_SetBasicSettingsResp },
    { EPSII_BP_1_GETBASICSETTINGS_FUNCRESP_ID, fs_GetBasicSettingsResp },
    { EPSII_BP_1_GETBASICAPPEXCEPTIONS_FUNCRESP_ID, fs_GetBasicAppExceptionsResp },
    { EPSII_BP_1_GETBASICAPPERRCOUNTERS_FUNCRESP_ID, fs_GetBasicAppErrCountersResp },
    { EPSII_BP_1_GETMAINAPPEXCEPTIONS_FUNCRESP_ID, fs_GetMainAppExceptionsResp },
    { EPSII_BP_1_GETMAINAPPERRCOUNTERS_FUNCRESP_ID, fs_GetMainAppErrCountersResp },
    { EPSII_BP_1_GETMAINAPPERRCOUNTERS2_FUNCRESP_ID, fs_GetMainAppErrCounters2Resp },
    { EPSII_BP_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNCRESP_ID, fs_OnESCP_ResetMainAppErrCountersResp },
    { EPSII_BP_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNCRESP_ID, fs_OnESCP_ResetMainAppExceptionsResp },
    { EPSII_BP_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNCRESP_ID, fs_OnESCP_ResetBasicAppErrCountersResp },
    { EPSII_BP_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNCRESP_ID, fs_OnESCP_ResetBasicAppExceptionsResp },
    { EPSII_BP_1_GETBALANCERSTATUS_FUNCRESP_ID, fs_GetBalancerStatusResp },
    { EPSII_BP_1_RESETDEVICE_FUNCRESP_ID, fs_ResetDeviceResp },
    { EPSII_BP_1_FORCEINSTALLMAINAPP_FUNCRESP_ID, fs_ForceInstallMainAppResp },
    { EPSII_BP_1_FORCEINSTALLBASICAPP_FUNCRESP_ID, fs_ForceInstallBasicAppResp },
    { EPSII_BP_1_GETBOOTLOADERERRCOUNTERS_FUNCRESP_ID, fs_GetBootLoaderErrCountersResp },
    { EPSII_BP_1_RESETBOOTLDRERRCOUNTERS_FUNCRESP_ID, fs_ResetBootLdrErrCountersResp },
    { EPSII_BP_1_SETCHARGERSETTINGS_FUNCRESP_ID, fs_SetChargerSettingsResp },
    { EPSII_BP_1_SETRTC_FUNCRESP_ID, fs_SetRTCResp },
    { EPSII_BP_1_GETRTC_FUNCRESP_ID, fs_GetRTCResp },
    { EPSII_BP_1_LEAVENOHIBMODE_FUNCRESP_ID, fs_LeaveNoHibModeResp },
    { EPSII_BP_1_REQUESTPOWERDOWN_FUNCRESP_ID, fs_RequestPowerDownResp },
    { EPSII_BP_1_GETBPMODESMROLLINGTRACE_FUNCRESP_ID, fs_GetBpModeSmRollingTraceResp }
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
    EPSII_BP_1GetDeviceInfoProtocolResponseData_t *fullresponse = (EPSII_BP_1GetDeviceInfoProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetDeviceInfoResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetDeviceInfoProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetDeviceInfoResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetDeviceInfoResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetDeviceInfoResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetRAWSensorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetRAWSensorsProtocolResponseData_t *fullresponse = (EPSII_BP_1GetRAWSensorsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetRAWSensorsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetRAWSensorsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetRAWSensorsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetRAWSensorsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetRAWSensorsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBatteryInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBatteryInfoProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBatteryInfoProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBatteryInfoResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBatteryInfoProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBatteryInfoResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBatteryInfoResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBatteryInfoResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetDeviceHealthInfoResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetDeviceHealthInfoProtocolResponseData_t *fullresponse = (EPSII_BP_1GetDeviceHealthInfoProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetDeviceHealthInfoResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetDeviceHealthInfoProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetDeviceHealthInfoResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetDeviceHealthInfoResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetDeviceHealthInfoResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetBatHeaterSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1SetBatHeaterSettingsProtocolResponseData_t *fullresponse = (EPSII_BP_1SetBatHeaterSettingsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1SetBatHeaterSettingsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetBatHeaterSettingsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1SetBatHeaterSettingsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_SetBatHeaterSettingsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_SetBatHeaterSettingsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBatHeaterSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBatHeaterSettingsProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBatHeaterSettingsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBatHeaterSettingsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBatHeaterSettingsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBatHeaterSettingsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBatHeaterSettingsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBatHeaterSettingsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1SetBasicSettingsProtocolResponseData_t *fullresponse = (EPSII_BP_1SetBasicSettingsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1SetBasicSettingsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetBasicSettingsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1SetBasicSettingsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_SetBasicSettingsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_SetBasicSettingsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBasicSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBasicSettingsProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBasicSettingsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBasicSettingsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBasicSettingsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBasicSettingsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBasicSettingsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBasicSettingsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBasicAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBasicAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBasicAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBasicAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBasicAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBasicAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBasicAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBasicAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBasicAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBasicAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBasicAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBasicAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBasicAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBasicAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetMainAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_BP_1GetMainAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetMainAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetMainAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetMainAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetMainAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetMainAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetMainAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_BP_1GetMainAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetMainAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetMainAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetMainAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetMainAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetMainAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetMainAppErrCounters2Resp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetMainAppErrCounters2ProtocolResponseData_t *fullresponse = (EPSII_BP_1GetMainAppErrCounters2ProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetMainAppErrCounters2ResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetMainAppErrCounters2ProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetMainAppErrCounters2ResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetMainAppErrCounters2ResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetMainAppErrCounters2ResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetMainAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1OnESCP_ResetMainAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1OnESCP_ResetMainAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetMainAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1OnESCP_ResetMainAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1OnESCP_ResetMainAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetBasicAppErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t *fullresponse = (EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1OnESCP_ResetBasicAppErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1OnESCP_ResetBasicAppErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_OnESCP_ResetBasicAppExceptionsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t *fullresponse = (EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1OnESCP_ResetBasicAppExceptionsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1OnESCP_ResetBasicAppExceptionsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBalancerStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBalancerStatusProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBalancerStatusProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBalancerStatusResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBalancerStatusProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBalancerStatusResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBalancerStatusResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBalancerStatusResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ResetDeviceResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1ResetDeviceProtocolResponseData_t *fullresponse = (EPSII_BP_1ResetDeviceProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1ResetDeviceResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ResetDeviceProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1ResetDeviceResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_ResetDeviceResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_ResetDeviceResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ForceInstallMainAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1ForceInstallMainAppProtocolResponseData_t *fullresponse = (EPSII_BP_1ForceInstallMainAppProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1ForceInstallMainAppResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ForceInstallMainAppProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1ForceInstallMainAppResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_ForceInstallMainAppResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_ForceInstallMainAppResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ForceInstallBasicAppResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1ForceInstallBasicAppProtocolResponseData_t *fullresponse = (EPSII_BP_1ForceInstallBasicAppProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1ForceInstallBasicAppResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ForceInstallBasicAppProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1ForceInstallBasicAppResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_ForceInstallBasicAppResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_ForceInstallBasicAppResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBootLoaderErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBootLoaderErrCountersProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBootLoaderErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBootLoaderErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBootLoaderErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBootLoaderErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBootLoaderErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBootLoaderErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ResetBootLdrErrCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1ResetBootLdrErrCountersProtocolResponseData_t *fullresponse = (EPSII_BP_1ResetBootLdrErrCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1ResetBootLdrErrCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ResetBootLdrErrCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1ResetBootLdrErrCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_ResetBootLdrErrCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_ResetBootLdrErrCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetChargerSettingsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1SetChargerSettingsProtocolResponseData_t *fullresponse = (EPSII_BP_1SetChargerSettingsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1SetChargerSettingsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetChargerSettingsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1SetChargerSettingsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_SetChargerSettingsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_SetChargerSettingsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetRTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1SetRTCProtocolResponseData_t *fullresponse = (EPSII_BP_1SetRTCProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1SetRTCResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetRTCProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1SetRTCResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_SetRTCResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_SetRTCResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetRTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetRTCProtocolResponseData_t *fullresponse = (EPSII_BP_1GetRTCProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetRTCResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetRTCProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetRTCResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetRTCResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetRTCResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_LeaveNoHibModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1LeaveNoHibModeProtocolResponseData_t *fullresponse = (EPSII_BP_1LeaveNoHibModeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1LeaveNoHibModeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1LeaveNoHibModeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1LeaveNoHibModeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_LeaveNoHibModeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_LeaveNoHibModeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_RequestPowerDownResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1RequestPowerDownProtocolResponseData_t *fullresponse = (EPSII_BP_1RequestPowerDownProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1RequestPowerDownResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1RequestPowerDownProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1RequestPowerDownResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_RequestPowerDownResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_RequestPowerDownResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBpModeSmRollingTraceResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    EPSII_BP_1GetBpModeSmRollingTraceProtocolResponseData_t *fullresponse = (EPSII_BP_1GetBpModeSmRollingTraceProtocolResponseData_t *) fp_DataInfo->pu8Data;
    EPSII_BP_1GetBpModeSmRollingTraceResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBpModeSmRollingTraceProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (EPSII_BP_1GetBpModeSmRollingTraceResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->EPSII_BP_1_GetBpModeSmRollingTraceResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->EPSII_BP_1_GetBpModeSmRollingTraceResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void EPSII_BP_1_registerClientApi(EPSII_BP_1_ClientApi_t *pCliApiHandlers)
{
    pCliApiHnd = pCliApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t EPSII_BP_1_getClientProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_EPSII_BP_1ProtocolClientInfo;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetDeviceInfoReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetDeviceInfoProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetDeviceInfoProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetDeviceInfoProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETDEVICEINFO_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetDeviceInfoProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetRAWSensorsReq(
                ReqContext_t* ctx,
                const uint32_t u32PktIDReq,
                const EPSII_BP_1_EPSIIT_SensorIDs_t * const aeSensorsIDs
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetRAWSensorsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetRAWSensorsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetRAWSensorsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETRAWSENSORS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetRAWSensorsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBatteryInfoReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBatteryInfoProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBatteryInfoProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBatteryInfoProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBATTERYINFO_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetBatteryInfoProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetDeviceHealthInfoReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetDeviceHealthInfoProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetDeviceHealthInfoProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetDeviceHealthInfoProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETDEVICEHEALTHINFO_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetDeviceHealthInfoProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_SetBatHeaterSettingsReq(
                ReqContext_t* ctx,
                const EPSII_BP_1_SBH_EnableBitmask_t eEnableBitmask,
                const int32_t i32NormalModeSetPointTemp,
                const int32_t i32HibModeSetPointTemp,
                const uint32_t u32PID_KP,
                const uint32_t u32PID_KI,
                const uint32_t u32PID_KD
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1SetBatHeaterSettingsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1SetBatHeaterSettingsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetBatHeaterSettingsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_SETBATHEATERSETTINGS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eEnableBitmask = eEnableBitmask;
        requestParams.data.i32NormalModeSetPointTemp = i32NormalModeSetPointTemp;
        requestParams.data.i32HibModeSetPointTemp = i32HibModeSetPointTemp;
        requestParams.data.u32PID_KP = u32PID_KP;
        requestParams.data.u32PID_KI = u32PID_KI;
        requestParams.data.u32PID_KD = u32PID_KD;
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
                                            sizeof(EPSII_BP_1SetBatHeaterSettingsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBatHeaterSettingsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBatHeaterSettingsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBatHeaterSettingsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBatHeaterSettingsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBATHEATERSETTINGS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetBatHeaterSettingsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_SetBasicSettingsReq(
                ReqContext_t* ctx,
                const EPSII_BP_1_SBasicSettings_t * const sBasicSettings
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1SetBasicSettingsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1SetBasicSettingsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetBasicSettingsProtocolRequestData_t);

    if ((ctx != NULL) && (sBasicSettings != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_SETBASICSETTINGS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1SetBasicSettingsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBasicSettingsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBasicSettingsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBasicSettingsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBasicSettingsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBASICSETTINGS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetBasicSettingsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBasicAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBasicAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBasicAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBasicAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBASICAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetBasicAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBasicAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBasicAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBasicAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBasicAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBASICAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetBasicAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetMainAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetMainAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetMainAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetMainAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETMAINAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetMainAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetMainAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetMainAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetMainAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetMainAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETMAINAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetMainAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetMainAppErrCounters2Req(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetMainAppErrCounters2ProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetMainAppErrCounters2ProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetMainAppErrCounters2ProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETMAINAPPERRCOUNTERS2_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetMainAppErrCounters2ProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetMainAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1OnESCP_ResetMainAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetMainAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1OnESCP_ResetMainAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetBasicAppErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1OnESCP_ResetBasicAppErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetBasicAppExceptionsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1OnESCP_ResetBasicAppExceptionsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBalancerStatusReq(
                ReqContext_t* ctx,
                const uint8_t u8RequestSpecificRegNumber
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBalancerStatusProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBalancerStatusProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBalancerStatusProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBALANCERSTATUS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8RequestSpecificRegNumber = u8RequestSpecificRegNumber;
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
                                            sizeof(EPSII_BP_1GetBalancerStatusProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_ResetDeviceReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1ResetDeviceProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1ResetDeviceProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ResetDeviceProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_RESETDEVICE_FUNC_ID;
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
                                            sizeof(EPSII_BP_1ResetDeviceProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_ForceInstallMainAppReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1ForceInstallMainAppProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1ForceInstallMainAppProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ForceInstallMainAppProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_FORCEINSTALLMAINAPP_FUNC_ID;
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
                                            sizeof(EPSII_BP_1ForceInstallMainAppProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_ForceInstallBasicAppReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1ForceInstallBasicAppProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1ForceInstallBasicAppProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ForceInstallBasicAppProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_FORCEINSTALLBASICAPP_FUNC_ID;
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
                                            sizeof(EPSII_BP_1ForceInstallBasicAppProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBootLoaderErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBootLoaderErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBootLoaderErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBootLoaderErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBOOTLOADERERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetBootLoaderErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_ResetBootLdrErrCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1ResetBootLdrErrCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1ResetBootLdrErrCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1ResetBootLdrErrCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_RESETBOOTLDRERRCOUNTERS_FUNC_ID;
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
                                            sizeof(EPSII_BP_1ResetBootLdrErrCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_SetChargerSettingsReq(
                ReqContext_t* ctx,
                const EPSII_BP_1_ChargerSettings_t * const aeInChargers
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1SetChargerSettingsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1SetChargerSettingsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetChargerSettingsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_SETCHARGERSETTINGS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (aeInChargers != NULL)
        {
            (void) memcpy((void *) requestParams.data.aeInChargers,
                          (const void *) aeInChargers,
                          sizeof(requestParams.data.aeInChargers));
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
                                            sizeof(EPSII_BP_1SetChargerSettingsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_SetRTCReq(
                ReqContext_t* ctx,
                const uint8_t u8In_hours,
                const uint8_t u8In_minutes,
                const uint8_t u8In_seconds,
                const uint8_t u8In_date,
                const uint8_t u8In_month,
                const uint16_t u16In_year
)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1SetRTCProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1SetRTCProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1SetRTCProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_SETRTC_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8In_hours = u8In_hours;
        requestParams.data.u8In_minutes = u8In_minutes;
        requestParams.data.u8In_seconds = u8In_seconds;
        requestParams.data.u8In_date = u8In_date;
        requestParams.data.u8In_month = u8In_month;
        requestParams.data.u16In_year = u16In_year;
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
                                            sizeof(EPSII_BP_1SetRTCProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetRTCReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetRTCProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetRTCProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetRTCProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETRTC_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetRTCProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_LeaveNoHibModeReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1LeaveNoHibModeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1LeaveNoHibModeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1LeaveNoHibModeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_LEAVENOHIBMODE_FUNC_ID;
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
                                            sizeof(EPSII_BP_1LeaveNoHibModeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_RequestPowerDownReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1RequestPowerDownProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1RequestPowerDownProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1RequestPowerDownProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_REQUESTPOWERDOWN_FUNC_ID;
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
                                            sizeof(EPSII_BP_1RequestPowerDownProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes EPSII_BP_1_GetBpModeSmRollingTraceReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    EPSII_BP_1GetBpModeSmRollingTraceProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(EPSII_BP_1GetBpModeSmRollingTraceProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(EPSII_BP_1GetBpModeSmRollingTraceProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1;
        requestParams.hdr.funcId  = EPSII_BP_1_GETBPMODESMROLLINGTRACE_FUNC_ID;
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
                                            sizeof(EPSII_BP_1GetBpModeSmRollingTraceProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


