/*!
********************************************************************************************
* @file FP_TelemetryServerApp.c
* @brief ServerApp implementation template generator
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

// @START_USER@ USER_INCLUDES
#include "nvm/inc/nvm.h"
#include "config/telemetry/telemetry_cfg_user.h"
#include "telemetry_file_sink.h"
#include "telemetry_queue.h"
#include "debug.h"
#include "telemetry_file_sink.h"
#include "telemetry_types.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void Telemetry_getTelemetryGeneralConfigRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Telemetry_setTelemetryGeneralConfigRequestHandlerImpl(ReqContext_t* pReqCtx,
            const TelemetrysetTelemetryGeneralConfigRequestData_t* pRequestData);

static void Telemetry_getTelemetryPresetConfigRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Telemetry_setTelemetryPresetConfigRequestHandlerImpl(ReqContext_t* pReqCtx,
            const TelemetrysetTelemetryPresetConfigRequestData_t* pRequestData);

static void Telemetry_setActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx,
            const TelemetrysetActivePresetRequestData_t* pRequestData);

static void Telemetry_getActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Telemetry_restoreActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Telemetry_getTelemetryFileSinkConfigRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Telemetry_setTelemetryFileSzLimitConfigRequestHandlerImpl(ReqContext_t* pReqCtx,
            const TelemetrysetTelemetryFileSzLimitConfigRequestData_t* pRequestData);

static void Telemetry_setTelemetryFileTmLimitConfigRequestHandlerImpl(ReqContext_t* pReqCtx,
            const TelemetrysetTelemetryFileTmLimitConfigRequestData_t* pRequestData);

static void Telemetry_resumeFileTelemetryRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Telemetry_pauseFileTelemetryRequestHandlerImpl(ReqContext_t* pReqCtx,
            const TelemetrypauseFileTelemetryRequestData_t* pRequestData);

static void Telemetry_cleanTelemetryFilesRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Telemetry_getTelemetryOperationStatsRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static Telemetry_ServerApi_t TelemetryServerApiCtx =
{
  .Telemetry_getTelemetryGeneralConfigRequestHandler = (pfTelemetry_getTelemetryGeneralConfigRequestHandler_t) Telemetry_getTelemetryGeneralConfigRequestHandlerImpl,
  .Telemetry_setTelemetryGeneralConfigRequestHandler = (pfTelemetry_setTelemetryGeneralConfigRequestHandler_t) Telemetry_setTelemetryGeneralConfigRequestHandlerImpl,
  .Telemetry_getTelemetryPresetConfigRequestHandler = (pfTelemetry_getTelemetryPresetConfigRequestHandler_t) Telemetry_getTelemetryPresetConfigRequestHandlerImpl,
  .Telemetry_setTelemetryPresetConfigRequestHandler = (pfTelemetry_setTelemetryPresetConfigRequestHandler_t) Telemetry_setTelemetryPresetConfigRequestHandlerImpl,
  .Telemetry_setActivePresetRequestHandler = (pfTelemetry_setActivePresetRequestHandler_t) Telemetry_setActivePresetRequestHandlerImpl,
  .Telemetry_getActivePresetRequestHandler = (pfTelemetry_getActivePresetRequestHandler_t) Telemetry_getActivePresetRequestHandlerImpl,
  .Telemetry_restoreActivePresetRequestHandler = (pfTelemetry_restoreActivePresetRequestHandler_t) Telemetry_restoreActivePresetRequestHandlerImpl,
  .Telemetry_getTelemetryFileSinkConfigRequestHandler = (pfTelemetry_getTelemetryFileSinkConfigRequestHandler_t) Telemetry_getTelemetryFileSinkConfigRequestHandlerImpl,
  .Telemetry_setTelemetryFileSzLimitConfigRequestHandler = (pfTelemetry_setTelemetryFileSzLimitConfigRequestHandler_t) Telemetry_setTelemetryFileSzLimitConfigRequestHandlerImpl,
  .Telemetry_setTelemetryFileTmLimitConfigRequestHandler = (pfTelemetry_setTelemetryFileTmLimitConfigRequestHandler_t) Telemetry_setTelemetryFileTmLimitConfigRequestHandlerImpl,
  .Telemetry_resumeFileTelemetryRequestHandler = (pfTelemetry_resumeFileTelemetryRequestHandler_t) Telemetry_resumeFileTelemetryRequestHandlerImpl,
  .Telemetry_pauseFileTelemetryRequestHandler = (pfTelemetry_pauseFileTelemetryRequestHandler_t) Telemetry_pauseFileTelemetryRequestHandlerImpl,
  .Telemetry_cleanTelemetryFilesRequestHandler = (pfTelemetry_cleanTelemetryFilesRequestHandler_t) Telemetry_cleanTelemetryFilesRequestHandlerImpl,
  .Telemetry_getTelemetryOperationStatsRequestHandler = (pfTelemetry_getTelemetryOperationStatsRequestHandler_t) Telemetry_getTelemetryOperationStatsRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method Telemetry::getTelemetryGeneralConfig (ID = 0x00000000)
static void Telemetry_getTelemetryGeneralConfigRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_tlm_general_cfg_t sCfg;

    // @USER_VAR_SECTION_START@Telemetry::getTelemetryGeneralConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::getTelemetryGeneralConfig@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::getTelemetryGeneralConfig@
        telemetry_cfg_t tlm_config;

        Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_GENERAL, (void * const) &tlm_config);

        sCfg.eTelemetry_en = tlm_config.telemetry_en;
        sCfg.eFile_telemetry_en = tlm_config.file_telemetry_en;

        // @USER_CODE_SECTION_END@Telemetry::getTelemetryGeneralConfig@

        respResult = Telemetry_getTelemetryGeneralConfigResp(
                        &respCtx,
                        &sCfg
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_GETTELEMETRYGENERALCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::getTelemetryGeneralConfig (ID = 0x00000000)

// @START@ Request handler for method Telemetry::setTelemetryGeneralConfig (ID = 0x00000001)
static void Telemetry_setTelemetryGeneralConfigRequestHandlerImpl(ReqContext_t *pReqCtx,
            const TelemetrysetTelemetryGeneralConfigRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::setTelemetryGeneralConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::setTelemetryGeneralConfig@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::setTelemetryGeneralConfig@

        telemetry_cfg_t tlm_config;

        Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_GENERAL, (void * const) &tlm_config);

        tlm_config.telemetry_en = pRequestData->sCfg.eTelemetry_en;
        tlm_config.file_telemetry_en = pRequestData->sCfg.eFile_telemetry_en;

        Nvm_SetBlockById(NVM_BLOCK_TELEMETRY_GENERAL, (void * const) &tlm_config, NVMSETBLOCK_STORE_IMMEDIATELY);

        eRes = TELEMETRY_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@Telemetry::setTelemetryGeneralConfig@

        respResult = Telemetry_setTelemetryGeneralConfigResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_SETTELEMETRYGENERALCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::setTelemetryGeneralConfig (ID = 0x00000001)

// @START@ Request handler for method Telemetry::getTelemetryPresetConfig (ID = 0x00000002)
static void Telemetry_getTelemetryPresetConfigRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Slot_preset_cnt;
    uint8_t u8Max_tlm_msg_cnt;
    TELEMETRY_tlm_preset_cfg_t asTelemetry_preset_cfg[40];

    // @USER_VAR_SECTION_START@Telemetry::getTelemetryPresetConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::getTelemetryPresetConfig@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::getTelemetryPresetConfig@

        telemetry_preset_cfg_t tlm_preset_cfg;

        (void) memset(asTelemetry_preset_cfg, INVALID_TLM_SLOT_ASSIGNMENT, sizeof(asTelemetry_preset_cfg));

        Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_PRESETS, (void * const) &tlm_preset_cfg);

        (void) memcpy(asTelemetry_preset_cfg,
                      tlm_preset_cfg.tlm_slots_setting,
                      MIN(sizeof(asTelemetry_preset_cfg), sizeof(tlm_preset_cfg.tlm_slots_setting)));

        u8Slot_preset_cnt = TELEMETRY_PRESETS_COUNT;
        u8Max_tlm_msg_cnt = TELEMETRY_MAX_CONFIGURABLE_ENTRIES;

        // @USER_CODE_SECTION_END@Telemetry::getTelemetryPresetConfig@

        respResult = Telemetry_getTelemetryPresetConfigResp(
                        &respCtx,
                        u8Slot_preset_cnt,
                        u8Max_tlm_msg_cnt,
                        asTelemetry_preset_cfg
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_GETTELEMETRYPRESETCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::getTelemetryPresetConfig (ID = 0x00000002)

// @START@ Request handler for method Telemetry::setTelemetryPresetConfig (ID = 0x00000003)
static void Telemetry_setTelemetryPresetConfigRequestHandlerImpl(ReqContext_t *pReqCtx,
            const TelemetrysetTelemetryPresetConfigRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::setTelemetryPresetConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::setTelemetryPresetConfig@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::setTelemetryPresetConfig@

        telemetry_preset_cfg_t tlm_preset_cfg;

        (void) memcpy((void * volatile) tlm_preset_cfg.tlm_slots_setting,
                      (const void * volatile) pRequestData->asTelemetry_preset_cfg,
                      sizeof(tlm_preset_cfg.tlm_slots_setting));

        Nvm_SetBlockById(NVM_BLOCK_TELEMETRY_PRESETS, &tlm_preset_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

        eRes = TELEMETRY_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@Telemetry::setTelemetryPresetConfig@

        respResult = Telemetry_setTelemetryPresetConfigResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_SETTELEMETRYPRESETCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::setTelemetryPresetConfig (ID = 0x00000003)

// @START@ Request handler for method Telemetry::setActivePreset (ID = 0x00000004)
static void Telemetry_setActivePresetRequestHandlerImpl(ReqContext_t *pReqCtx,
            const TelemetrysetActivePresetRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;
    uint8_t u8Avail_presets_cnt;

    // @USER_VAR_SECTION_START@Telemetry::setActivePreset@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::setActivePreset@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::setActivePreset@

        bool valid_cfg = telemetry_cfg_set_active_preset(pRequestData->u8Req_active_preset);

        eRes = (valid_cfg) ? (TELEMETRY_STANDARDRESULT_SUCCESS) : (TELEMETRY_STANDARDRESULT_INVALID_ARGS);
        u8Avail_presets_cnt = TELEMETRY_PRESETS_COUNT;

        // @USER_CODE_SECTION_END@Telemetry::setActivePreset@

        respResult = Telemetry_setActivePresetResp(
                        &respCtx,
                        eRes,
                        u8Avail_presets_cnt
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_SETACTIVEPRESET_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::setActivePreset (ID = 0x00000004)

// @START@ Request handler for method Telemetry::getActivePreset (ID = 0x00000005)
static void Telemetry_getActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Active_preset_id;

    // @USER_VAR_SECTION_START@Telemetry::getActivePreset@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::getActivePreset@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::getActivePreset@

        u8Active_preset_id = telemetry_cfg_get_active_preset();

        // @USER_CODE_SECTION_END@Telemetry::getActivePreset@

        respResult = Telemetry_getActivePresetResp(
                        &respCtx,
                        u8Active_preset_id
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_GETACTIVEPRESET_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::getActivePreset (ID = 0x00000005)

// @START@ Request handler for method Telemetry::restoreActivePreset (ID = 0x00000006)
static void Telemetry_restoreActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::restoreActivePreset@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::restoreActivePreset@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::restoreActivePreset@

        telemetry_cfg_restore_active_preset();
        eRes = TELEMETRY_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@Telemetry::restoreActivePreset@

        respResult = Telemetry_restoreActivePresetResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_RESTOREACTIVEPRESET_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::restoreActivePreset (ID = 0x00000006)

// @START@ Request handler for method Telemetry::getTelemetryFileSinkConfig (ID = 0x00000007)
static void Telemetry_getTelemetryFileSinkConfigRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_tlm_file_logging_type_t eActive_file_cfg_type;
    TELEMETRY_tlm_file_size_limit_cfg_t sSize_limit_cfg;
    TELEMETRY_tlm_file_time_limit_cfg_t sTime_limit_cfg;

    // @USER_VAR_SECTION_START@Telemetry::getTelemetryFileSinkConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::getTelemetryFileSinkConfig@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::getTelemetryFileSinkConfig@

        telemetry_file_cfg_t tlm_file_cfg;

        Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_FILE_CFG, (void * const) &tlm_file_cfg);

        sSize_limit_cfg.u32Size_limit_kb = tlm_file_cfg.size_limit_kb;
        sSize_limit_cfg.u16Max_log_files_cnt = tlm_file_cfg.max_log_files_cnt;

        sTime_limit_cfg.u16File_size_limit_kb = tlm_file_cfg.file_size_limit_kb;
        sTime_limit_cfg.u32Time_limit_sec = tlm_file_cfg.time_limit_sec;

        switch (tlm_file_cfg.cfg_type)
        {
            case TLM_FILE_CFG_TYPE_SIZE_LIMIT:
            {
                eActive_file_cfg_type = TELEMETRY_TLM_FILE_LOGGING_TYPE_SIZE_LIMIT;
                break;
            }

            case TLM_FILE_CFG_TYPE_TIME_LIMIT:
            {
                eActive_file_cfg_type = TELEMETRY_TLM_FILE_LOGGING_TYPE_TIME_LIMIT;
                break;
            }

            default:
            {
                eActive_file_cfg_type = TELEMETRY_TLM_FILE_LOGGING_TYPE_SIZE_LIMIT;
                break;
            }
        }

        // @USER_CODE_SECTION_END@Telemetry::getTelemetryFileSinkConfig@

        respResult = Telemetry_getTelemetryFileSinkConfigResp(
                        &respCtx,
                        eActive_file_cfg_type,
                        &sSize_limit_cfg,
                        &sTime_limit_cfg
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_GETTELEMETRYFILESINKCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::getTelemetryFileSinkConfig (ID = 0x00000007)

// @START@ Request handler for method Telemetry::setTelemetryFileSzLimitConfig (ID = 0x00000008)
static void Telemetry_setTelemetryFileSzLimitConfigRequestHandlerImpl(ReqContext_t *pReqCtx,
            const TelemetrysetTelemetryFileSzLimitConfigRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::setTelemetryFileSzLimitConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::setTelemetryFileSzLimitConfig@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::setTelemetryFileSzLimitConfig@
        telemetry_file_cfg_t tlm_file_cfg;

        eRes = TELEMETRY_STANDARDRESULT_INVALID_ARGS;

        Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_FILE_CFG, (void * const) &tlm_file_cfg);

        if ((tlm_file_cfg.max_log_files_cnt != pRequestData->sSize_limit_cfg.u16Max_log_files_cnt) ||
            (tlm_file_cfg.size_limit_kb != pRequestData->sSize_limit_cfg.u32Size_limit_kb))
        {
            if (pRequestData->sSize_limit_cfg.u16Max_log_files_cnt > 0)
            {
                // the individual file size for the given configuration shall be non-zero after performing a rounding division, e.g. at least 1KB
                if (((pRequestData->sSize_limit_cfg.u32Size_limit_kb * 1024U) / pRequestData->sSize_limit_cfg.u16Max_log_files_cnt) >= TLM_MSG_SIZE_BYTES_LEAST)
                {
                    tlm_file_cfg.size_limit_kb = pRequestData->sSize_limit_cfg.u32Size_limit_kb;
                    tlm_file_cfg.max_log_files_cnt = pRequestData->sSize_limit_cfg.u16Max_log_files_cnt;
                    // set updated configuration as active
                    tlm_file_cfg.cfg_type = TLM_FILE_CFG_TYPE_SIZE_LIMIT;

                    Nvm_SetBlockById(NVM_BLOCK_TELEMETRY_FILE_CFG, &tlm_file_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

                    telemetry_file_sink_config_update();
                    eRes = TELEMETRY_STANDARDRESULT_SUCCESS;
                }
            }
        }
        else
        {
            // no change in configuration, hence the setting is just confirmed without any action
            eRes = TELEMETRY_STANDARDRESULT_SUCCESS;
        }
        // @USER_CODE_SECTION_END@Telemetry::setTelemetryFileSzLimitConfig@

        respResult = Telemetry_setTelemetryFileSzLimitConfigResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_SETTELEMETRYFILESZLIMITCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::setTelemetryFileSzLimitConfig (ID = 0x00000008)

// @START@ Request handler for method Telemetry::setTelemetryFileTmLimitConfig (ID = 0x00000009)
static void Telemetry_setTelemetryFileTmLimitConfigRequestHandlerImpl(ReqContext_t *pReqCtx,
            const TelemetrysetTelemetryFileTmLimitConfigRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::setTelemetryFileTmLimitConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::setTelemetryFileTmLimitConfig@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::setTelemetryFileTmLimitConfig@

        telemetry_file_cfg_t tlm_file_cfg;

        Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_FILE_CFG, (void * const) &tlm_file_cfg);

        if ((tlm_file_cfg.file_size_limit_kb != pRequestData->sTime_limit_cfg.u16File_size_limit_kb) ||
            (tlm_file_cfg.time_limit_sec != pRequestData->sTime_limit_cfg.u32Time_limit_sec))
        {
            if (((pRequestData->sTime_limit_cfg.u16File_size_limit_kb * 1024U) >= TLM_MSG_SIZE_BYTES_LEAST) &&
                (pRequestData->sTime_limit_cfg.u32Time_limit_sec > 0U))
            {
                tlm_file_cfg.file_size_limit_kb = pRequestData->sTime_limit_cfg.u16File_size_limit_kb;
                tlm_file_cfg.time_limit_sec = pRequestData->sTime_limit_cfg.u32Time_limit_sec;

                Nvm_SetBlockById(NVM_BLOCK_TELEMETRY_FILE_CFG, &tlm_file_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

                telemetry_file_sink_config_update();

                eRes = TELEMETRY_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eRes = TELEMETRY_STANDARDRESULT_INVALID_ARGS;
            }
        }

TODO(Do not activate time-limit configuration because it is currently not implemented yet!)
#if 0
        // set updated configuration as active
        tlm_file_cfg.cfg_type = TLM_FILE_CFG_TYPE_TIME_LIMIT;
#endif

TODO(Return TELEMETRY_STANDARDRESULT_NOT_SUPPORTED for now although the actual configuration would be updated in NVM)
        eRes = TELEMETRY_STANDARDRESULT_NOT_SUPPORTED;

        // @USER_CODE_SECTION_END@Telemetry::setTelemetryFileTmLimitConfig@

        respResult = Telemetry_setTelemetryFileTmLimitConfigResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_SETTELEMETRYFILETMLIMITCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::setTelemetryFileTmLimitConfig (ID = 0x00000009)

// @START@ Request handler for method Telemetry::resumeFileTelemetry (ID = 0x0000000A)
static void Telemetry_resumeFileTelemetryRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::resumeFileTelemetry@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::resumeFileTelemetry@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::resumeFileTelemetry@

        telemetry_file_sink_if.cmd(TELEMETRY_SINK_ADAPTER_CMD_START);

        eRes = TELEMETRY_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@Telemetry::resumeFileTelemetry@

        respResult = Telemetry_resumeFileTelemetryResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_RESUMEFILETELEMETRY_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::resumeFileTelemetry (ID = 0x0000000A)

// @START@ Request handler for method Telemetry::pauseFileTelemetry (ID = 0x0000000B)
static void Telemetry_pauseFileTelemetryRequestHandlerImpl(ReqContext_t *pReqCtx,
            const TelemetrypauseFileTelemetryRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::pauseFileTelemetry@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::pauseFileTelemetry@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::pauseFileTelemetry@

        telemetry_file_sink_pause(((uint32_t) pRequestData->u16Seconds_before_resume) * 1000U);

        eRes = TELEMETRY_STANDARDRESULT_SUCCESS;


        // @USER_CODE_SECTION_END@Telemetry::pauseFileTelemetry@

        respResult = Telemetry_pauseFileTelemetryResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_PAUSEFILETELEMETRY_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::pauseFileTelemetry (ID = 0x0000000B)

// @START@ Request handler for method Telemetry::cleanTelemetryFiles (ID = 0x0000000C)
static void Telemetry_cleanTelemetryFilesRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Telemetry::cleanTelemetryFiles@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::cleanTelemetryFiles@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::cleanTelemetryFiles@
        // setup an auto-resume timer just in case the sequence here breaks so that
        // telemetry will not be stopped until next boot....
        telemetry_file_sink_pause(10000U);

        telemetry_file_sink_syncd_clean();

        // start telemetry back as soon as clean-up is finished, even though auto-resume timer may not have
        // elapsed
        telemetry_file_sink_if.cmd(TELEMETRY_SINK_ADAPTER_CMD_START);

        eRes = TELEMETRY_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@Telemetry::cleanTelemetryFiles@

        respResult = Telemetry_cleanTelemetryFilesResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_CLEANTELEMETRYFILES_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::cleanTelemetryFiles (ID = 0x0000000C)

// @START@ Request handler for method Telemetry::getTelemetryOperationStats (ID = 0x0000000D)
static void Telemetry_getTelemetryOperationStatsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TELEMETRY_tlm_stats_t sTelemetry_stats;

    // @USER_VAR_SECTION_START@Telemetry::getTelemetryOperationStats@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Telemetry::getTelemetryOperationStats@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Telemetry::getTelemetryOperationStats@
        tlm_queue_stats_t queue_stats;

        telemetry_queue_get_stats(&queue_stats);

        sTelemetry_stats.u32Discarded_messages_cnt = queue_stats.discarded_messages_cnt;
        sTelemetry_stats.u32Free_bytes_min = queue_stats.free_bytes_min;
        sTelemetry_stats.u32Max_number_of_batch_msg = queue_stats.max_number_of_batch_msg;
        sTelemetry_stats.u32Msg_popped_cnt = queue_stats.msg_popped_cnt;
        sTelemetry_stats.u32Msg_pushed_cnt = queue_stats.msg_pushed_cnt;
        sTelemetry_stats.u32Active_slot_id = queue_stats.active_slot_id;

        // @USER_CODE_SECTION_END@Telemetry::getTelemetryOperationStats@

        respResult = Telemetry_getTelemetryOperationStatsResp(
                        &respCtx,
                        &sTelemetry_stats
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY, TELEMETRY_GETTELEMETRYOPERATIONSTATS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Telemetry::getTelemetryOperationStats (ID = 0x0000000D)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void TelemetryServerAppInit(void)
{
    Telemetry_registerServerApi(&TelemetryServerApiCtx);
}
