/*!
********************************************************************************************
* @file FP_OBC_CUBEADCSProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_OBC_CUBEADCSPROTOCOLSERVER_H__
#define __FP_OBC_CUBEADCSPROTOCOLSERVER_H__

#include "FP_OBC_CUBEADCSProtocolTypes.h"

typedef void (*pfOBC_CUBEADCS_getCommissioningStatusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_setCommissioningStatusRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSsetCommissioningStatusRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getGenericTLMRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSgetGenericTLMRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_sendGenericTCRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSsendGenericTCRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getOpStatusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_resetRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSresetRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_clrErrFlagsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_startFileTransferRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSstartFileTransferRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_pollFileTransferStatusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_clearFaultyNodeStatusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_startFileListDownloadRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_pollFileListDownloadStatusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_getADCSSysStateRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_setADCSSysStateRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSsetADCSSysStateRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getADCSUnixTimeRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_updateADCSUnixTimeRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_setEnableErrHandlLogicRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSsetEnableErrHandlLogicRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getEnableErrHandlLogicRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_setStablePointingThresholdsRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSsetStablePointingThresholdsRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getStablePointingThresholdsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_setSimulationModeRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSsetSimulationModeRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getSimulationModeValueRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_getOBCCommAndErrCountersRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSclrOBCCommAndErrCountersRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getFDIRCounersRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_clrFDIRCountersRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSclrFDIRCountersRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_stopFileTransferRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_getRunTimeLatchedErrsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_getFaultyNodeStatusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_setSystemStateCfgRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCSsetSystemStateCfgRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_getSystemStateCfgRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfOBC_CUBEADCS_getCommissioningStatusRequestHandler_t OBC_CUBEADCS_getCommissioningStatusRequestHandler;
    pfOBC_CUBEADCS_setCommissioningStatusRequestHandler_t OBC_CUBEADCS_setCommissioningStatusRequestHandler;
    pfOBC_CUBEADCS_getGenericTLMRequestHandler_t OBC_CUBEADCS_getGenericTLMRequestHandler;
    pfOBC_CUBEADCS_sendGenericTCRequestHandler_t OBC_CUBEADCS_sendGenericTCRequestHandler;
    pfOBC_CUBEADCS_getOpStatusRequestHandler_t OBC_CUBEADCS_getOpStatusRequestHandler;
    pfOBC_CUBEADCS_resetRequestHandler_t OBC_CUBEADCS_resetRequestHandler;
    pfOBC_CUBEADCS_clrErrFlagsRequestHandler_t OBC_CUBEADCS_clrErrFlagsRequestHandler;
    pfOBC_CUBEADCS_startFileTransferRequestHandler_t OBC_CUBEADCS_startFileTransferRequestHandler;
    pfOBC_CUBEADCS_pollFileTransferStatusRequestHandler_t OBC_CUBEADCS_pollFileTransferStatusRequestHandler;
    pfOBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandler_t OBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandler;
    pfOBC_CUBEADCS_clearFaultyNodeStatusRequestHandler_t OBC_CUBEADCS_clearFaultyNodeStatusRequestHandler;
    pfOBC_CUBEADCS_startFileListDownloadRequestHandler_t OBC_CUBEADCS_startFileListDownloadRequestHandler;
    pfOBC_CUBEADCS_pollFileListDownloadStatusRequestHandler_t OBC_CUBEADCS_pollFileListDownloadStatusRequestHandler;
    pfOBC_CUBEADCS_getADCSSysStateRequestHandler_t OBC_CUBEADCS_getADCSSysStateRequestHandler;
    pfOBC_CUBEADCS_setADCSSysStateRequestHandler_t OBC_CUBEADCS_setADCSSysStateRequestHandler;
    pfOBC_CUBEADCS_getADCSUnixTimeRequestHandler_t OBC_CUBEADCS_getADCSUnixTimeRequestHandler;
    pfOBC_CUBEADCS_updateADCSUnixTimeRequestHandler_t OBC_CUBEADCS_updateADCSUnixTimeRequestHandler;
    pfOBC_CUBEADCS_setEnableErrHandlLogicRequestHandler_t OBC_CUBEADCS_setEnableErrHandlLogicRequestHandler;
    pfOBC_CUBEADCS_getEnableErrHandlLogicRequestHandler_t OBC_CUBEADCS_getEnableErrHandlLogicRequestHandler;
    pfOBC_CUBEADCS_setStablePointingThresholdsRequestHandler_t OBC_CUBEADCS_setStablePointingThresholdsRequestHandler;
    pfOBC_CUBEADCS_getStablePointingThresholdsRequestHandler_t OBC_CUBEADCS_getStablePointingThresholdsRequestHandler;
    pfOBC_CUBEADCS_setSimulationModeRequestHandler_t OBC_CUBEADCS_setSimulationModeRequestHandler;
    pfOBC_CUBEADCS_getSimulationModeValueRequestHandler_t OBC_CUBEADCS_getSimulationModeValueRequestHandler;
    pfOBC_CUBEADCS_getOBCCommAndErrCountersRequestHandler_t OBC_CUBEADCS_getOBCCommAndErrCountersRequestHandler;
    pfOBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandler_t OBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandler;
    pfOBC_CUBEADCS_getFDIRCounersRequestHandler_t OBC_CUBEADCS_getFDIRCounersRequestHandler;
    pfOBC_CUBEADCS_clrFDIRCountersRequestHandler_t OBC_CUBEADCS_clrFDIRCountersRequestHandler;
    pfOBC_CUBEADCS_stopFileTransferRequestHandler_t OBC_CUBEADCS_stopFileTransferRequestHandler;
    pfOBC_CUBEADCS_getRunTimeLatchedErrsRequestHandler_t OBC_CUBEADCS_getRunTimeLatchedErrsRequestHandler;
    pfOBC_CUBEADCS_getFaultyNodeStatusRequestHandler_t OBC_CUBEADCS_getFaultyNodeStatusRequestHandler;
    pfOBC_CUBEADCS_setSystemStateCfgRequestHandler_t OBC_CUBEADCS_setSystemStateCfgRequestHandler;
    pfOBC_CUBEADCS_getSystemStateCfgRequestHandler_t OBC_CUBEADCS_getSystemStateCfgRequestHandler;
} OBC_CUBEADCS_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_CUBEADCSProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void OBC_CUBEADCS_registerServerApi(OBC_CUBEADCS_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_OBC_CUBEADCSProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t OBC_CUBEADCS_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes OBC_CUBEADCS_getCommissioningStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_CommissioningStatus_t eStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_setCommissioningStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getGenericTLMResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_TLMReqReply_t * const sTLMReq_Reply,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_sendGenericTCResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_TCReqReply_t * const sTCReq_Reply,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getOpStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_OpStatus_t * const sOpStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_resetResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_clrErrFlagsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_startFileTransferResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_pollFileTransferStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_FTransfStatus_t eStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_clearRunTimeLatchedErrsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_clearFaultyNodeStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_startFileListDownloadResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_pollFileListDownloadStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_FTransfStatus_t eStatus,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getADCSSysStateResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_ADCSSysStates_t eSysState,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_setADCSSysStateResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getADCSUnixTimeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_UnixTime_t * const sUnixTime,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_updateADCSUnixTimeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_setEnableErrHandlLogicResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getEnableErrHandlLogicResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_SafeBool_t eEnFlag,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_setStablePointingThresholdsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getStablePointingThresholdsResp(
                RespContext_t* ctx,
                const double dStablePointingThresholdAngle,
                const double dStablePointingThresholdAngleRate,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_setSimulationModeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getSimulationModeValueResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_SafeBool_t eEn_sim_mode,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getOBCCommAndErrCountersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_ErrCounters_t * const sCounters,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_clrOBCCommAndErrCountersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getFDIRCounersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_FDIRCounters_t * const sCounters,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_clrFDIRCountersResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_stopFileTransferResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

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
);

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
);

ESSATMAC_ErrCodes OBC_CUBEADCS_setSystemStateCfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_getSystemStateCfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_CubeADCS_Cfg_t * const asCubeADCS_sys_state_cfg
);


#endif  // #ifndef __FP_OBC_CUBEADCSPROTOCOLSERVER_H__
