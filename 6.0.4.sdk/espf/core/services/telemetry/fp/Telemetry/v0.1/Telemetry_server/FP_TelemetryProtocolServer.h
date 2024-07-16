/*!
********************************************************************************************
* @file FP_TelemetryProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_TELEMETRYPROTOCOLSERVER_H__
#define __FP_TELEMETRYPROTOCOLSERVER_H__

#include "FP_TelemetryProtocolTypes.h"

typedef void (*pfTelemetry_getTelemetryGeneralConfigRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfTelemetry_setTelemetryGeneralConfigRequestHandler_t)(ReqContext_t *ctx, TelemetrysetTelemetryGeneralConfigRequestData_t *pRequestData);
typedef void (*pfTelemetry_getTelemetryPresetConfigRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfTelemetry_setTelemetryPresetConfigRequestHandler_t)(ReqContext_t *ctx, TelemetrysetTelemetryPresetConfigRequestData_t *pRequestData);
typedef void (*pfTelemetry_setActivePresetRequestHandler_t)(ReqContext_t *ctx, TelemetrysetActivePresetRequestData_t *pRequestData);
typedef void (*pfTelemetry_getActivePresetRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfTelemetry_restoreActivePresetRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfTelemetry_getTelemetryFileSinkConfigRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfTelemetry_setTelemetryFileSzLimitConfigRequestHandler_t)(ReqContext_t *ctx, TelemetrysetTelemetryFileSzLimitConfigRequestData_t *pRequestData);
typedef void (*pfTelemetry_setTelemetryFileTmLimitConfigRequestHandler_t)(ReqContext_t *ctx, TelemetrysetTelemetryFileTmLimitConfigRequestData_t *pRequestData);
typedef void (*pfTelemetry_resumeFileTelemetryRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfTelemetry_pauseFileTelemetryRequestHandler_t)(ReqContext_t *ctx, TelemetrypauseFileTelemetryRequestData_t *pRequestData);
typedef void (*pfTelemetry_cleanTelemetryFilesRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfTelemetry_getTelemetryOperationStatsRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfTelemetry_getTelemetryGeneralConfigRequestHandler_t Telemetry_getTelemetryGeneralConfigRequestHandler;
    pfTelemetry_setTelemetryGeneralConfigRequestHandler_t Telemetry_setTelemetryGeneralConfigRequestHandler;
    pfTelemetry_getTelemetryPresetConfigRequestHandler_t Telemetry_getTelemetryPresetConfigRequestHandler;
    pfTelemetry_setTelemetryPresetConfigRequestHandler_t Telemetry_setTelemetryPresetConfigRequestHandler;
    pfTelemetry_setActivePresetRequestHandler_t Telemetry_setActivePresetRequestHandler;
    pfTelemetry_getActivePresetRequestHandler_t Telemetry_getActivePresetRequestHandler;
    pfTelemetry_restoreActivePresetRequestHandler_t Telemetry_restoreActivePresetRequestHandler;
    pfTelemetry_getTelemetryFileSinkConfigRequestHandler_t Telemetry_getTelemetryFileSinkConfigRequestHandler;
    pfTelemetry_setTelemetryFileSzLimitConfigRequestHandler_t Telemetry_setTelemetryFileSzLimitConfigRequestHandler;
    pfTelemetry_setTelemetryFileTmLimitConfigRequestHandler_t Telemetry_setTelemetryFileTmLimitConfigRequestHandler;
    pfTelemetry_resumeFileTelemetryRequestHandler_t Telemetry_resumeFileTelemetryRequestHandler;
    pfTelemetry_pauseFileTelemetryRequestHandler_t Telemetry_pauseFileTelemetryRequestHandler;
    pfTelemetry_cleanTelemetryFilesRequestHandler_t Telemetry_cleanTelemetryFilesRequestHandler;
    pfTelemetry_getTelemetryOperationStatsRequestHandler_t Telemetry_getTelemetryOperationStatsRequestHandler;
} Telemetry_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_TelemetryProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void Telemetry_registerServerApi(Telemetry_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_TelemetryProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t Telemetry_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes Telemetry_getTelemetryGeneralConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_tlm_general_cfg_t * const sCfg
);

ESSATMAC_ErrCodes Telemetry_setTelemetryGeneralConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_getTelemetryPresetConfigResp(
                RespContext_t* ctx,
                const uint8_t u8Slot_preset_cnt,
                const uint8_t u8Max_tlm_msg_cnt,
                const TELEMETRY_tlm_preset_cfg_t * const asTelemetry_preset_cfg
);

ESSATMAC_ErrCodes Telemetry_setTelemetryPresetConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_setActivePresetResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes,
                const uint8_t u8Avail_presets_cnt
);

ESSATMAC_ErrCodes Telemetry_getActivePresetResp(
                RespContext_t* ctx,
                const uint8_t u8Active_preset_id
);

ESSATMAC_ErrCodes Telemetry_restoreActivePresetResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_getTelemetryFileSinkConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_tlm_file_logging_type_t eActive_file_cfg_type,
                const TELEMETRY_tlm_file_size_limit_cfg_t * const sSize_limit_cfg,
                const TELEMETRY_tlm_file_time_limit_cfg_t * const sTime_limit_cfg
);

ESSATMAC_ErrCodes Telemetry_setTelemetryFileSzLimitConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_setTelemetryFileTmLimitConfigResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_resumeFileTelemetryResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_pauseFileTelemetryResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_cleanTelemetryFilesResp(
                RespContext_t* ctx,
                const TELEMETRY_StandardResult_t eRes
);

ESSATMAC_ErrCodes Telemetry_getTelemetryOperationStatsResp(
                RespContext_t* ctx,
                const TELEMETRY_tlm_stats_t * const sTelemetry_stats
);


#endif  // #ifndef __FP_TELEMETRYPROTOCOLSERVER_H__
