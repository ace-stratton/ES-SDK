/*!
********************************************************************************************
* @file FP_OBC_CUBEADCSProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface OBC_CUBEADCS v1.1
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

#include "FP_OBC_CUBEADCSProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define OBC_CUBEADCS_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define OBC_CUBEADCS_PROTOCOL_VERSION_MINOR   ((uint8_t) 1)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetCommissioningStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetCommissioningStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetCommissioningStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetCommissioningStatusRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetCommissioningStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetCommissioningStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetCommissioningStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetGenericTLMRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetGenericTLMProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetGenericTLMResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetGenericTLMProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsendGenericTCRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSsendGenericTCProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsendGenericTCResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSsendGenericTCProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetOpStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetOpStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetOpStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSresetRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSresetProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSresetResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSresetProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSclrErrFlagsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSclrErrFlagsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSclrErrFlagsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSstartFileTransferRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSstartFileTransferProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSstartFileTransferResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSstartFileTransferProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSpollFileTransferStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSpollFileTransferStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSpollFileTransferStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSclearRunTimeLatchedErrsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSclearRunTimeLatchedErrsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSclearRunTimeLatchedErrsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSclearFaultyNodeStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSclearFaultyNodeStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSclearFaultyNodeStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSstartFileListDownloadProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSstartFileListDownloadResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSstartFileListDownloadProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSpollFileListDownloadStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSpollFileListDownloadStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSpollFileListDownloadStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetADCSSysStateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetADCSSysStateResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetADCSSysStateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetADCSSysStateRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetADCSSysStateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetADCSSysStateResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetADCSSysStateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetADCSUnixTimeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetADCSUnixTimeResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetADCSUnixTimeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSupdateADCSUnixTimeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSupdateADCSUnixTimeResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSupdateADCSUnixTimeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetEnableErrHandlLogicRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetEnableErrHandlLogicProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetEnableErrHandlLogicResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetEnableErrHandlLogicProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetEnableErrHandlLogicProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetEnableErrHandlLogicResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetEnableErrHandlLogicProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetStablePointingThresholdsRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetStablePointingThresholdsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetStablePointingThresholdsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetStablePointingThresholdsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetStablePointingThresholdsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetStablePointingThresholdsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetStablePointingThresholdsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetSimulationModeRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetSimulationModeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetSimulationModeResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetSimulationModeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetSimulationModeValueProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetSimulationModeValueResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetSimulationModeValueProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetOBCCommAndErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetOBCCommAndErrCountersResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetOBCCommAndErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSclrOBCCommAndErrCountersRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSclrOBCCommAndErrCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSclrOBCCommAndErrCountersResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSclrOBCCommAndErrCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetFDIRCounersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetFDIRCounersResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetFDIRCounersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSclrFDIRCountersRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSclrFDIRCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSclrFDIRCountersResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSclrFDIRCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSstopFileTransferProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSstopFileTransferResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSstopFileTransferProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetRunTimeLatchedErrsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetRunTimeLatchedErrsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetRunTimeLatchedErrsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetFaultyNodeStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetFaultyNodeStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetFaultyNodeStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetSystemStateCfgRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetSystemStateCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSsetSystemStateCfgResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSsetSystemStateCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCSgetSystemStateCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCSgetSystemStateCfgResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCSgetSystemStateCfgProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getCommissioningStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setCommissioningStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getGenericTLMReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_sendGenericTCReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getOpStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_resetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clrErrFlagsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_startFileTransferReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_pollFileTransferStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clearRunTimeLatchedErrsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clearFaultyNodeStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_startFileListDownloadReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_pollFileListDownloadStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getADCSSysStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setADCSSysStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getADCSUnixTimeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_updateADCSUnixTimeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setEnableErrHandlLogicReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getEnableErrHandlLogicReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setStablePointingThresholdsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getStablePointingThresholdsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setSimulationModeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getSimulationModeValueReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getOBCCommAndErrCountersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clrOBCCommAndErrCountersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getFDIRCounersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clrFDIRCountersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_stopFileTransferReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getRunTimeLatchedErrsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getFaultyNodeStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_setSystemStateCfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getSystemStateCfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_CUBEADCSProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static OBC_CUBEADCS_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_CUBEADCS_GETCOMMISSIONINGSTATUS_FUNC_ID, fs_getCommissioningStatusReq },
    { OBC_CUBEADCS_SETCOMMISSIONINGSTATUS_FUNC_ID, fs_setCommissioningStatusReq },
    { OBC_CUBEADCS_GETGENERICTLM_FUNC_ID, fs_getGenericTLMReq },
    { OBC_CUBEADCS_SENDGENERICTC_FUNC_ID, fs_sendGenericTCReq },
    { OBC_CUBEADCS_GETOPSTATUS_FUNC_ID, fs_getOpStatusReq },
    { OBC_CUBEADCS_RESET_FUNC_ID, fs_resetReq },
    { OBC_CUBEADCS_CLRERRFLAGS_FUNC_ID, fs_clrErrFlagsReq },
    { OBC_CUBEADCS_STARTFILETRANSFER_FUNC_ID, fs_startFileTransferReq },
    { OBC_CUBEADCS_POLLFILETRANSFERSTATUS_FUNC_ID, fs_pollFileTransferStatusReq },
    { OBC_CUBEADCS_CLEARRUNTIMELATCHEDERRS_FUNC_ID, fs_clearRunTimeLatchedErrsReq },
    { OBC_CUBEADCS_CLEARFAULTYNODESTATUS_FUNC_ID, fs_clearFaultyNodeStatusReq },
    { OBC_CUBEADCS_STARTFILELISTDOWNLOAD_FUNC_ID, fs_startFileListDownloadReq },
    { OBC_CUBEADCS_POLLFILELISTDOWNLOADSTATUS_FUNC_ID, fs_pollFileListDownloadStatusReq },
    { OBC_CUBEADCS_GETADCSSYSSTATE_FUNC_ID, fs_getADCSSysStateReq },
    { OBC_CUBEADCS_SETADCSSYSSTATE_FUNC_ID, fs_setADCSSysStateReq },
    { OBC_CUBEADCS_GETADCSUNIXTIME_FUNC_ID, fs_getADCSUnixTimeReq },
    { OBC_CUBEADCS_UPDATEADCSUNIXTIME_FUNC_ID, fs_updateADCSUnixTimeReq },
    { OBC_CUBEADCS_SETENABLEERRHANDLLOGIC_FUNC_ID, fs_setEnableErrHandlLogicReq },
    { OBC_CUBEADCS_GETENABLEERRHANDLLOGIC_FUNC_ID, fs_getEnableErrHandlLogicReq },
    { OBC_CUBEADCS_SETSTABLEPOINTINGTHRESHOLDS_FUNC_ID, fs_setStablePointingThresholdsReq },
    { OBC_CUBEADCS_GETSTABLEPOINTINGTHRESHOLDS_FUNC_ID, fs_getStablePointingThresholdsReq },
    { OBC_CUBEADCS_SETSIMULATIONMODE_FUNC_ID, fs_setSimulationModeReq },
    { OBC_CUBEADCS_GETSIMULATIONMODEVALUE_FUNC_ID, fs_getSimulationModeValueReq },
    { OBC_CUBEADCS_GETOBCCOMMANDERRCOUNTERS_FUNC_ID, fs_getOBCCommAndErrCountersReq },
    { OBC_CUBEADCS_CLROBCCOMMANDERRCOUNTERS_FUNC_ID, fs_clrOBCCommAndErrCountersReq },
    { OBC_CUBEADCS_GETFDIRCOUNERS_FUNC_ID, fs_getFDIRCounersReq },
    { OBC_CUBEADCS_CLRFDIRCOUNTERS_FUNC_ID, fs_clrFDIRCountersReq },
    { OBC_CUBEADCS_STOPFILETRANSFER_FUNC_ID, fs_stopFileTransferReq },
    { OBC_CUBEADCS_GETRUNTIMELATCHEDERRS_FUNC_ID, fs_getRunTimeLatchedErrsReq },
    { OBC_CUBEADCS_GETFAULTYNODESTATUS_FUNC_ID, fs_getFaultyNodeStatusReq },
    { OBC_CUBEADCS_SETSYSTEMSTATECFG_FUNC_ID, fs_setSystemStateCfgReq },
    { OBC_CUBEADCS_GETSYSTEMSTATECFG_FUNC_ID, fs_getSystemStateCfgReq }
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

static void fs_getCommissioningStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetCommissioningStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetCommissioningStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetCommissioningStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getCommissioningStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getCommissioningStatusRequestHandler(&requestCtx);
    }
}

static void fs_setCommissioningStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSsetCommissioningStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCSsetCommissioningStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSsetCommissioningStatusRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetCommissioningStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSsetCommissioningStatusRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_setCommissioningStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_setCommissioningStatusRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getGenericTLMReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetGenericTLMProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetGenericTLMProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSgetGenericTLMRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetGenericTLMProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSgetGenericTLMRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getGenericTLMRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getGenericTLMRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_sendGenericTCReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSsendGenericTCProtocolRequestData_t *fullrequest = (OBC_CUBEADCSsendGenericTCProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSsendGenericTCRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsendGenericTCProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSsendGenericTCRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_sendGenericTCRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_sendGenericTCRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getOpStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetOpStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetOpStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetOpStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getOpStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getOpStatusRequestHandler(&requestCtx);
    }
}

static void fs_resetReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSresetProtocolRequestData_t *fullrequest = (OBC_CUBEADCSresetProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSresetRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSresetProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSresetRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_resetRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_resetRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_clrErrFlagsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSclrErrFlagsProtocolRequestData_t *fullrequest = (OBC_CUBEADCSclrErrFlagsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclrErrFlagsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_clrErrFlagsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_clrErrFlagsRequestHandler(&requestCtx);
    }
}

static void fs_startFileTransferReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSstartFileTransferProtocolRequestData_t *fullrequest = (OBC_CUBEADCSstartFileTransferProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSstartFileTransferRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSstartFileTransferProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSstartFileTransferRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_startFileTransferRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_startFileTransferRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_pollFileTransferStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSpollFileTransferStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCSpollFileTransferStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSpollFileTransferStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_pollFileTransferStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_pollFileTransferStatusRequestHandler(&requestCtx);
    }
}

static void fs_clearRunTimeLatchedErrsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSclearRunTimeLatchedErrsProtocolRequestData_t *fullrequest = (OBC_CUBEADCSclearRunTimeLatchedErrsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclearRunTimeLatchedErrsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandler(&requestCtx);
    }
}

static void fs_clearFaultyNodeStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSclearFaultyNodeStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCSclearFaultyNodeStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclearFaultyNodeStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_clearFaultyNodeStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_clearFaultyNodeStatusRequestHandler(&requestCtx);
    }
}

static void fs_startFileListDownloadReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSstartFileListDownloadProtocolRequestData_t *fullrequest = (OBC_CUBEADCSstartFileListDownloadProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSstartFileListDownloadProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_startFileListDownloadRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_startFileListDownloadRequestHandler(&requestCtx);
    }
}

static void fs_pollFileListDownloadStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSpollFileListDownloadStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCSpollFileListDownloadStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSpollFileListDownloadStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_pollFileListDownloadStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_pollFileListDownloadStatusRequestHandler(&requestCtx);
    }
}

static void fs_getADCSSysStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetADCSSysStateProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetADCSSysStateProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetADCSSysStateProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getADCSSysStateRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getADCSSysStateRequestHandler(&requestCtx);
    }
}

static void fs_setADCSSysStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSsetADCSSysStateProtocolRequestData_t *fullrequest = (OBC_CUBEADCSsetADCSSysStateProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSsetADCSSysStateRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetADCSSysStateProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSsetADCSSysStateRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_setADCSSysStateRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_setADCSSysStateRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getADCSUnixTimeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetADCSUnixTimeProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetADCSUnixTimeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetADCSUnixTimeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getADCSUnixTimeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getADCSUnixTimeRequestHandler(&requestCtx);
    }
}

static void fs_updateADCSUnixTimeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSupdateADCSUnixTimeProtocolRequestData_t *fullrequest = (OBC_CUBEADCSupdateADCSUnixTimeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSupdateADCSUnixTimeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_updateADCSUnixTimeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_updateADCSUnixTimeRequestHandler(&requestCtx);
    }
}

static void fs_setEnableErrHandlLogicReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSsetEnableErrHandlLogicProtocolRequestData_t *fullrequest = (OBC_CUBEADCSsetEnableErrHandlLogicProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSsetEnableErrHandlLogicRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetEnableErrHandlLogicProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSsetEnableErrHandlLogicRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_setEnableErrHandlLogicRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_setEnableErrHandlLogicRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getEnableErrHandlLogicReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetEnableErrHandlLogicProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetEnableErrHandlLogicProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetEnableErrHandlLogicProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getEnableErrHandlLogicRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getEnableErrHandlLogicRequestHandler(&requestCtx);
    }
}

static void fs_setStablePointingThresholdsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSsetStablePointingThresholdsProtocolRequestData_t *fullrequest = (OBC_CUBEADCSsetStablePointingThresholdsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSsetStablePointingThresholdsRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetStablePointingThresholdsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSsetStablePointingThresholdsRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_setStablePointingThresholdsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_setStablePointingThresholdsRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getStablePointingThresholdsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetStablePointingThresholdsProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetStablePointingThresholdsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetStablePointingThresholdsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getStablePointingThresholdsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getStablePointingThresholdsRequestHandler(&requestCtx);
    }
}

static void fs_setSimulationModeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSsetSimulationModeProtocolRequestData_t *fullrequest = (OBC_CUBEADCSsetSimulationModeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSsetSimulationModeRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetSimulationModeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSsetSimulationModeRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_setSimulationModeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_setSimulationModeRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getSimulationModeValueReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetSimulationModeValueProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetSimulationModeValueProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetSimulationModeValueProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getSimulationModeValueRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getSimulationModeValueRequestHandler(&requestCtx);
    }
}

static void fs_getOBCCommAndErrCountersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetOBCCommAndErrCountersProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetOBCCommAndErrCountersProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetOBCCommAndErrCountersProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getOBCCommAndErrCountersRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getOBCCommAndErrCountersRequestHandler(&requestCtx);
    }
}

static void fs_clrOBCCommAndErrCountersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSclrOBCCommAndErrCountersProtocolRequestData_t *fullrequest = (OBC_CUBEADCSclrOBCCommAndErrCountersProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSclrOBCCommAndErrCountersRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclrOBCCommAndErrCountersProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSclrOBCCommAndErrCountersRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getFDIRCounersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetFDIRCounersProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetFDIRCounersProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetFDIRCounersProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getFDIRCounersRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getFDIRCounersRequestHandler(&requestCtx);
    }
}

static void fs_clrFDIRCountersReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSclrFDIRCountersProtocolRequestData_t *fullrequest = (OBC_CUBEADCSclrFDIRCountersProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSclrFDIRCountersRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclrFDIRCountersProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSclrFDIRCountersRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_clrFDIRCountersRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_clrFDIRCountersRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_stopFileTransferReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSstopFileTransferProtocolRequestData_t *fullrequest = (OBC_CUBEADCSstopFileTransferProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSstopFileTransferProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_stopFileTransferRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_stopFileTransferRequestHandler(&requestCtx);
    }
}

static void fs_getRunTimeLatchedErrsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetRunTimeLatchedErrsProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetRunTimeLatchedErrsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetRunTimeLatchedErrsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getRunTimeLatchedErrsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getRunTimeLatchedErrsRequestHandler(&requestCtx);
    }
}

static void fs_getFaultyNodeStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetFaultyNodeStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetFaultyNodeStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetFaultyNodeStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getFaultyNodeStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getFaultyNodeStatusRequestHandler(&requestCtx);
    }
}

static void fs_setSystemStateCfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSsetSystemStateCfgProtocolRequestData_t *fullrequest = (OBC_CUBEADCSsetSystemStateCfgProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCSsetSystemStateCfgRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetSystemStateCfgProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCSsetSystemStateCfgRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_setSystemStateCfgRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_setSystemStateCfgRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getSystemStateCfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCSgetSystemStateCfgProtocolRequestData_t *fullrequest = (OBC_CUBEADCSgetSystemStateCfgProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetSystemStateCfgProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_getSystemStateCfgRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_getSystemStateCfgRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void OBC_CUBEADCS_registerServerApi(OBC_CUBEADCS_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t OBC_CUBEADCS_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_OBC_CUBEADCSProtocolServerInfo;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getCommissioningStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_CommissioningStatus_t eStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetCommissioningStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetCommissioningStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetCommissioningStatusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETCOMMISSIONINGSTATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(OBC_CUBEADCSgetCommissioningStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_setCommissioningStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSsetCommissioningStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSsetCommissioningStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetCommissioningStatusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_SETCOMMISSIONINGSTATUS_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSsetCommissioningStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getGenericTLMResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_TLMReqReply_t * const sTLMReq_Reply,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetGenericTLMProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetGenericTLMProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetGenericTLMProtocolResponseData_t);

    if ((ctx != NULL) && (sTLMReq_Reply != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETGENERICTLM_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sTLMReq_Reply != NULL)
        {
            responseParams.data.sTLMReq_Reply = *(sTLMReq_Reply);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sTLMReq_Reply,
                          0U,
                          sizeof(responseParams.data.sTLMReq_Reply));
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
                                            sizeof(OBC_CUBEADCSgetGenericTLMProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_sendGenericTCResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_TCReqReply_t * const sTCReq_Reply,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSsendGenericTCProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSsendGenericTCProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsendGenericTCProtocolResponseData_t);

    if ((ctx != NULL) && (sTCReq_Reply != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_SENDGENERICTC_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sTCReq_Reply != NULL)
        {
            responseParams.data.sTCReq_Reply = *(sTCReq_Reply);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sTCReq_Reply,
                          0U,
                          sizeof(responseParams.data.sTCReq_Reply));
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
                                            sizeof(OBC_CUBEADCSsendGenericTCProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getOpStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_OpStatus_t * const sOpStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetOpStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetOpStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetOpStatusProtocolResponseData_t);

    if ((ctx != NULL) && (sOpStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETOPSTATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOpStatus != NULL)
        {
            responseParams.data.sOpStatus = *(sOpStatus);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOpStatus,
                          0U,
                          sizeof(responseParams.data.sOpStatus));
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
                                            sizeof(OBC_CUBEADCSgetOpStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_resetResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSresetProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSresetProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSresetProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_RESET_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSresetProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_clrErrFlagsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSclrErrFlagsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSclrErrFlagsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclrErrFlagsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_CLRERRFLAGS_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSclrErrFlagsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_startFileTransferResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSstartFileTransferProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSstartFileTransferProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSstartFileTransferProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_STARTFILETRANSFER_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSstartFileTransferProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_pollFileTransferStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_FTransfStatus_t eStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSpollFileTransferStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSpollFileTransferStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSpollFileTransferStatusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_POLLFILETRANSFERSTATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(OBC_CUBEADCSpollFileTransferStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_clearRunTimeLatchedErrsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSclearRunTimeLatchedErrsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSclearRunTimeLatchedErrsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclearRunTimeLatchedErrsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_CLEARRUNTIMELATCHEDERRS_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSclearRunTimeLatchedErrsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_clearFaultyNodeStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSclearFaultyNodeStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSclearFaultyNodeStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclearFaultyNodeStatusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_CLEARFAULTYNODESTATUS_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSclearFaultyNodeStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_startFileListDownloadResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSstartFileListDownloadProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSstartFileListDownloadProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSstartFileListDownloadProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_STARTFILELISTDOWNLOAD_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSstartFileListDownloadProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_pollFileListDownloadStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_FTransfStatus_t eStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSpollFileListDownloadStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSpollFileListDownloadStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSpollFileListDownloadStatusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_POLLFILELISTDOWNLOADSTATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(OBC_CUBEADCSpollFileListDownloadStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getADCSSysStateResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_ADCSSysStates_t eSysState,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetADCSSysStateProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetADCSSysStateProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetADCSSysStateProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETADCSSYSSTATE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eSysState = eSysState;
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
                                            sizeof(OBC_CUBEADCSgetADCSSysStateProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_setADCSSysStateResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSsetADCSSysStateProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSsetADCSSysStateProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetADCSSysStateProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_SETADCSSYSSTATE_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSsetADCSSysStateProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getADCSUnixTimeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_UnixTime_t * const sUnixTime,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetADCSUnixTimeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetADCSUnixTimeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetADCSUnixTimeProtocolResponseData_t);

    if ((ctx != NULL) && (sUnixTime != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETADCSUNIXTIME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sUnixTime != NULL)
        {
            responseParams.data.sUnixTime = *(sUnixTime);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sUnixTime,
                          0U,
                          sizeof(responseParams.data.sUnixTime));
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
                                            sizeof(OBC_CUBEADCSgetADCSUnixTimeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_updateADCSUnixTimeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSupdateADCSUnixTimeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSupdateADCSUnixTimeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSupdateADCSUnixTimeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_UPDATEADCSUNIXTIME_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSupdateADCSUnixTimeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_setEnableErrHandlLogicResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSsetEnableErrHandlLogicProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSsetEnableErrHandlLogicProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetEnableErrHandlLogicProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_SETENABLEERRHANDLLOGIC_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSsetEnableErrHandlLogicProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getEnableErrHandlLogicResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_SafeBool_t eEnFlag,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetEnableErrHandlLogicProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetEnableErrHandlLogicProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetEnableErrHandlLogicProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETENABLEERRHANDLLOGIC_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eEnFlag = eEnFlag;
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
                                            sizeof(OBC_CUBEADCSgetEnableErrHandlLogicProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_setStablePointingThresholdsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSsetStablePointingThresholdsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSsetStablePointingThresholdsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetStablePointingThresholdsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_SETSTABLEPOINTINGTHRESHOLDS_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSsetStablePointingThresholdsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getStablePointingThresholdsResp(
                RespContext_t* ctx,
                const double dStablePointingThresholdAngle,
                const double dStablePointingThresholdAngleRate,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetStablePointingThresholdsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetStablePointingThresholdsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetStablePointingThresholdsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETSTABLEPOINTINGTHRESHOLDS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.dStablePointingThresholdAngle = dStablePointingThresholdAngle;
        responseParams.data.dStablePointingThresholdAngleRate = dStablePointingThresholdAngleRate;
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
                                            sizeof(OBC_CUBEADCSgetStablePointingThresholdsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_setSimulationModeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSsetSimulationModeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSsetSimulationModeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetSimulationModeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_SETSIMULATIONMODE_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSsetSimulationModeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getSimulationModeValueResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_SafeBool_t eEn_sim_mode,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetSimulationModeValueProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetSimulationModeValueProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetSimulationModeValueProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETSIMULATIONMODEVALUE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eEn_sim_mode = eEn_sim_mode;
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
                                            sizeof(OBC_CUBEADCSgetSimulationModeValueProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getOBCCommAndErrCountersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_ErrCounters_t * const sCounters,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetOBCCommAndErrCountersProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetOBCCommAndErrCountersProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetOBCCommAndErrCountersProtocolResponseData_t);

    if ((ctx != NULL) && (sCounters != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETOBCCOMMANDERRCOUNTERS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sCounters != NULL)
        {
            responseParams.data.sCounters = *(sCounters);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sCounters,
                          0U,
                          sizeof(responseParams.data.sCounters));
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
                                            sizeof(OBC_CUBEADCSgetOBCCommAndErrCountersProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_clrOBCCommAndErrCountersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSclrOBCCommAndErrCountersProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSclrOBCCommAndErrCountersProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclrOBCCommAndErrCountersProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_CLROBCCOMMANDERRCOUNTERS_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSclrOBCCommAndErrCountersProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getFDIRCounersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_FDIRCounters_t * const sCounters,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetFDIRCounersProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetFDIRCounersProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetFDIRCounersProtocolResponseData_t);

    if ((ctx != NULL) && (sCounters != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETFDIRCOUNERS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sCounters != NULL)
        {
            responseParams.data.sCounters = *(sCounters);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sCounters,
                          0U,
                          sizeof(responseParams.data.sCounters));
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
                                            sizeof(OBC_CUBEADCSgetFDIRCounersProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_clrFDIRCountersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSclrFDIRCountersProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSclrFDIRCountersProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSclrFDIRCountersProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_CLRFDIRCOUNTERS_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSclrFDIRCountersProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_stopFileTransferResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSstopFileTransferProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSstopFileTransferProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSstopFileTransferProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_STOPFILETRANSFER_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSstopFileTransferProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getRunTimeLatchedErrsResp(
                RespContext_t* ctx,
                const bool bNodeRecoveryErr,
                const bool bRangeErr,
                const bool bRateSensFailure,
                const bool bMagnetometerErr,
                const bool bOrbitParamsErr,
                const bool bConfigInvalid,
                const bool bCntrlModeChgErr,
                const bool bEstModeChgErr,
                const bool bSysStateChgErr,
                const uint8_t u8Reserved,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetRunTimeLatchedErrsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetRunTimeLatchedErrsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetRunTimeLatchedErrsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETRUNTIMELATCHEDERRS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.bNodeRecoveryErr = bNodeRecoveryErr;
        responseParams.data.bRangeErr = bRangeErr;
        responseParams.data.bRateSensFailure = bRateSensFailure;
        responseParams.data.bMagnetometerErr = bMagnetometerErr;
        responseParams.data.bOrbitParamsErr = bOrbitParamsErr;
        responseParams.data.bConfigInvalid = bConfigInvalid;
        responseParams.data.bCntrlModeChgErr = bCntrlModeChgErr;
        responseParams.data.bEstModeChgErr = bEstModeChgErr;
        responseParams.data.bSysStateChgErr = bSysStateChgErr;
        responseParams.data.u8Reserved = u8Reserved;
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
                                            sizeof(OBC_CUBEADCSgetRunTimeLatchedErrsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getFaultyNodeStatusResp(
                RespContext_t* ctx,
                const bool bSignalMCU,
                const bool bMotorMCU,
                const bool bCubeSense1,
                const bool bCubeSense2,
                const bool bCubeStar,
                const bool bRWheel1,
                const bool bRWheel2,
                const bool bRWheel3,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetFaultyNodeStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetFaultyNodeStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetFaultyNodeStatusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETFAULTYNODESTATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.bSignalMCU = bSignalMCU;
        responseParams.data.bMotorMCU = bMotorMCU;
        responseParams.data.bCubeSense1 = bCubeSense1;
        responseParams.data.bCubeSense2 = bCubeSense2;
        responseParams.data.bCubeStar = bCubeStar;
        responseParams.data.bRWheel1 = bRWheel1;
        responseParams.data.bRWheel2 = bRWheel2;
        responseParams.data.bRWheel3 = bRWheel3;
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
                                            sizeof(OBC_CUBEADCSgetFaultyNodeStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_setSystemStateCfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSsetSystemStateCfgProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSsetSystemStateCfgProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSsetSystemStateCfgProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_SETSYSTEMSTATECFG_FUNCRESP_ID;
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
                                            sizeof(OBC_CUBEADCSsetSystemStateCfgProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_getSystemStateCfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_CubeADCS_Cfg_t * const asCubeADCS_sys_state_cfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCSgetSystemStateCfgProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCSgetSystemStateCfgProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCSgetSystemStateCfgProtocolResponseData_t);

    if ((ctx != NULL) && (asCubeADCS_sys_state_cfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GETSYSTEMSTATECFG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (asCubeADCS_sys_state_cfg != NULL)
        {
            (void) memcpy((void *) &responseParams.data.asCubeADCS_sys_state_cfg,
                          (const void *) asCubeADCS_sys_state_cfg,
                          sizeof(responseParams.data.asCubeADCS_sys_state_cfg));
        }
        else
        {
            (void) memset((void *) &responseParams.data.asCubeADCS_sys_state_cfg,
                          0U,
                          sizeof(responseParams.data.asCubeADCS_sys_state_cfg));
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
                                            sizeof(OBC_CUBEADCSgetSystemStateCfgProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


