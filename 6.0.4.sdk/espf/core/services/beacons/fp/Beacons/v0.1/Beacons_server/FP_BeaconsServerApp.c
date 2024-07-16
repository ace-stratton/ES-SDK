/*!
********************************************************************************************
* @file FP_BeaconsServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface Beacons v0.1
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

#include "FP_BeaconsProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include <string.h>
#include "nvm/inc/nvm.h"
#include "config/beacons/beacons_cfg_user.h"
#include "assertions.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void Beacons_getBeaconGeneralConfigRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Beacons_setBeaconGeneralConfigRequestHandlerImpl(ReqContext_t* pReqCtx,
            const BeaconssetBeaconGeneralConfigRequestData_t* pRequestData);

static void Beacons_getBeaconPresetConfigRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Beacons_setBeaconPresetConfigRequestHandlerImpl(ReqContext_t* pReqCtx,
            const BeaconssetBeaconPresetConfigRequestData_t* pRequestData);

static void Beacons_setActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx,
            const BeaconssetActivePresetRequestData_t* pRequestData);

static void Beacons_getActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx);

static void Beacons_restoreActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static Beacons_ServerApi_t BeaconsServerApiCtx =
{
  .Beacons_getBeaconGeneralConfigRequestHandler = (pfBeacons_getBeaconGeneralConfigRequestHandler_t) Beacons_getBeaconGeneralConfigRequestHandlerImpl,
  .Beacons_setBeaconGeneralConfigRequestHandler = (pfBeacons_setBeaconGeneralConfigRequestHandler_t) Beacons_setBeaconGeneralConfigRequestHandlerImpl,
  .Beacons_getBeaconPresetConfigRequestHandler = (pfBeacons_getBeaconPresetConfigRequestHandler_t) Beacons_getBeaconPresetConfigRequestHandlerImpl,
  .Beacons_setBeaconPresetConfigRequestHandler = (pfBeacons_setBeaconPresetConfigRequestHandler_t) Beacons_setBeaconPresetConfigRequestHandlerImpl,
  .Beacons_setActivePresetRequestHandler = (pfBeacons_setActivePresetRequestHandler_t) Beacons_setActivePresetRequestHandlerImpl,
  .Beacons_getActivePresetRequestHandler = (pfBeacons_getActivePresetRequestHandler_t) Beacons_getActivePresetRequestHandlerImpl,
  .Beacons_restoreActivePresetRequestHandler = (pfBeacons_restoreActivePresetRequestHandler_t) Beacons_restoreActivePresetRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method Beacons::getBeaconGeneralConfig (ID = 0x00000000)
static void Beacons_getBeaconGeneralConfigRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    BEACONS_bcn_general_cfg_t sCfg;

    // @USER_VAR_SECTION_START@Beacons::getBeaconGeneralConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Beacons::getBeaconGeneralConfig@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Beacons::getBeaconGeneralConfig@

        beacons_cfg_t bcn_config;

        Nvm_GetBlockById(NVM_BLOCK_BEACONS_GENERAL, (void * const) &bcn_config);

        sCfg.eBeacons_en = (BEACONS_safe_bool_t) bcn_config.beacons_en;
        sCfg.eChunk_based_transfer_en = (BEACONS_safe_bool_t) bcn_config.chunk_based_transfer_en;
        sCfg.u32Bcn_inter_frame_period = bcn_config.bcn_inter_frame_period;
        sCfg.u32Bcn_tx_period = bcn_config.bcn_tx_period;

        // @USER_CODE_SECTION_END@Beacons::getBeaconGeneralConfig@

        respResult = Beacons_getBeaconGeneralConfigResp(
                        &respCtx,
                        &sCfg
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_BEACONS, BEACONS_GETBEACONGENERALCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Beacons::getBeaconGeneralConfig (ID = 0x00000000)

// @START@ Request handler for method Beacons::setBeaconGeneralConfig (ID = 0x00000001)
static void Beacons_setBeaconGeneralConfigRequestHandlerImpl(ReqContext_t *pReqCtx,
            const BeaconssetBeaconGeneralConfigRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    BEACONS_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Beacons::setBeaconGeneralConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Beacons::setBeaconGeneralConfig@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Beacons::setBeaconGeneralConfig@

        beacons_cfg_t bcn_config;

        Nvm_GetBlockById(NVM_BLOCK_BEACONS_GENERAL, (void * const) &bcn_config);

        bcn_config.beacons_en = (safe_bool_t) pRequestData->sCfg.eBeacons_en;
        bcn_config.chunk_based_transfer_en = (safe_bool_t) pRequestData->sCfg.eChunk_based_transfer_en;
        bcn_config.bcn_tx_period = pRequestData->sCfg.u32Bcn_tx_period;

        if ((pRequestData->sCfg.u32Bcn_inter_frame_period >= BEACON_TASK_PERIOD_MS) &&
            (pRequestData->sCfg.u32Bcn_inter_frame_period < pRequestData->sCfg.u32Bcn_tx_period))
        {
            bcn_config.bcn_inter_frame_period = pRequestData->sCfg.u32Bcn_inter_frame_period;

            Nvm_SetBlockById(NVM_BLOCK_BEACONS_GENERAL, (void * const) &bcn_config, NVMSETBLOCK_STORE_IMMEDIATELY);

            eRes = BEACONS_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eRes = BEACONS_STANDARDRESULT_INVALID_ARGS;
        }

        // @USER_CODE_SECTION_END@Beacons::setBeaconGeneralConfig@

        respResult = Beacons_setBeaconGeneralConfigResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_BEACONS, BEACONS_SETBEACONGENERALCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Beacons::setBeaconGeneralConfig (ID = 0x00000001)

// @START@ Request handler for method Beacons::getBeaconPresetConfig (ID = 0x00000002)
static void Beacons_getBeaconPresetConfigRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Slot_preset_cnt;
    uint8_t u8Max_bcn_msg_cnt;
    uint16_t au16Beacon_preset_cfg[80];

    // @USER_VAR_SECTION_START@Beacons::getBeaconPresetConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Beacons::getBeaconPresetConfig@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Beacons::getBeaconPresetConfig@
        beacons_presets_cfg_t bcn_preset_cfg;

        (void) memset(au16Beacon_preset_cfg, INVALID_BEACON_SLOT_ASSIGNMENT, sizeof(au16Beacon_preset_cfg));

        Nvm_GetBlockById(NVM_BLOCK_BEACONS_PRESETS, (void * const) &bcn_preset_cfg);

        (void) memcpy(au16Beacon_preset_cfg,
                      bcn_preset_cfg.beacon_slots_setting,
                      MIN(sizeof(au16Beacon_preset_cfg), sizeof(bcn_preset_cfg.beacon_slots_setting)));

        u8Slot_preset_cnt = BEACON_PRESETS_COUNT;
        u8Max_bcn_msg_cnt = MAX_BEACON_MSG_SLOTS;
        // @USER_CODE_SECTION_END@Beacons::getBeaconPresetConfig@

        respResult = Beacons_getBeaconPresetConfigResp(
                        &respCtx,
                        u8Slot_preset_cnt,
                        u8Max_bcn_msg_cnt,
                        au16Beacon_preset_cfg
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_BEACONS, BEACONS_GETBEACONPRESETCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Beacons::getBeaconPresetConfig (ID = 0x00000002)

// @START@ Request handler for method Beacons::setBeaconPresetConfig (ID = 0x00000003)
static void Beacons_setBeaconPresetConfigRequestHandlerImpl(ReqContext_t *pReqCtx,
            const BeaconssetBeaconPresetConfigRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    BEACONS_StandardResult_t eRes;
    uint8_t au8Preset_error_slot_index[4];

    // @USER_VAR_SECTION_START@Beacons::setBeaconPresetConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Beacons::setBeaconPresetConfig@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Beacons::setBeaconPresetConfig@
        CRIT_ASSERT(BEACON_PRESETS_COUNT == sizeof(au8Preset_error_slot_index));

        uint8_t erroneous_preset_cnt = 0U;

        (void) memset(au8Preset_error_slot_index, 0xFFU, sizeof(au8Preset_error_slot_index));

        for (uint8_t preset_idx = 0U; preset_idx < BEACON_PRESETS_COUNT; preset_idx++)
        {
            for (uint8_t slot_idx = 0U; slot_idx < MAX_BEACON_MSG_SLOTS; slot_idx++)
            {
                volatile uint16_t beacon_type = pRequestData->au16Beacon_preset_cfg[preset_idx * MAX_BEACON_MSG_SLOTS + slot_idx];
                dc_did_id did_id = dc_get_index_by_data_id(beacon_type);

                if (did_id < DC_DID_MAX)
                {
                    uint32_t msg_size = dc_get_data_size(did_id);

                    if (msg_size > BEACON_MSG_MAX_SIZE_BYTES)
                    {
                        erroneous_preset_cnt++;
                        au8Preset_error_slot_index[preset_idx] = slot_idx;

                        break;
                    }
                }
                else
                {
                    // stop processing of the current preset configuration and store an error if ID is out of range
                    if (beacon_type != INVALID_BEACON_SLOT_ASSIGNMENT)
                    {
                        erroneous_preset_cnt++;
                        au8Preset_error_slot_index[preset_idx] = slot_idx;
                    }

                    break;
                }
            }
        }

        if (0U == erroneous_preset_cnt)
        {
            beacons_presets_cfg_t bcn_preset_cfg;

            (void) memcpy((void * volatile) bcn_preset_cfg.beacon_slots_setting,
                          (const void * volatile) pRequestData->au16Beacon_preset_cfg,
                          sizeof(bcn_preset_cfg.beacon_slots_setting));

            Nvm_SetBlockById(NVM_BLOCK_BEACONS_PRESETS, &bcn_preset_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

            eRes = BEACONS_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eRes = BEACONS_STANDARDRESULT_ERROR;
        }


        // @USER_CODE_SECTION_END@Beacons::setBeaconPresetConfig@

        respResult = Beacons_setBeaconPresetConfigResp(
                        &respCtx,
                        eRes,
                        au8Preset_error_slot_index
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_BEACONS, BEACONS_SETBEACONPRESETCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Beacons::setBeaconPresetConfig (ID = 0x00000003)

// @START@ Request handler for method Beacons::setActivePreset (ID = 0x00000004)
static void Beacons_setActivePresetRequestHandlerImpl(ReqContext_t *pReqCtx,
            const BeaconssetActivePresetRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    BEACONS_StandardResult_t eRes;
    uint8_t u8Avail_presets_cnt;

    // @USER_VAR_SECTION_START@Beacons::setActivePreset@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Beacons::setActivePreset@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Beacons::setActivePreset@

        bool valid_cfg = beacons_cfg_set_active_preset(pRequestData->u8Req_active_preset);

        eRes = (valid_cfg) ? (BEACONS_STANDARDRESULT_SUCCESS) : (BEACONS_STANDARDRESULT_INVALID_ARGS);
        u8Avail_presets_cnt = BEACON_PRESETS_COUNT;

        // @USER_CODE_SECTION_END@Beacons::setActivePreset@

        respResult = Beacons_setActivePresetResp(
                        &respCtx,
                        eRes,
                        u8Avail_presets_cnt
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_BEACONS, BEACONS_SETACTIVEPRESET_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Beacons::setActivePreset (ID = 0x00000004)

// @START@ Request handler for method Beacons::getActivePreset (ID = 0x00000005)
static void Beacons_getActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Active_preset_id;

    // @USER_VAR_SECTION_START@Beacons::getActivePreset@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Beacons::getActivePreset@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Beacons::getActivePreset@

        u8Active_preset_id = beacons_cfg_get_active_preset();

        // @USER_CODE_SECTION_END@Beacons::getActivePreset@

        respResult = Beacons_getActivePresetResp(
                        &respCtx,
                        u8Active_preset_id
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_BEACONS, BEACONS_GETACTIVEPRESET_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Beacons::getActivePreset (ID = 0x00000005)

// @START@ Request handler for method Beacons::restoreActivePreset (ID = 0x00000006)
static void Beacons_restoreActivePresetRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    BEACONS_StandardResult_t eRes;

    // @USER_VAR_SECTION_START@Beacons::restoreActivePreset@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Beacons::restoreActivePreset@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Beacons::restoreActivePreset@

        beacons_cfg_restore_active_preset();
        eRes = BEACONS_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@Beacons::restoreActivePreset@

        respResult = Beacons_restoreActivePresetResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_BEACONS, BEACONS_RESTOREACTIVEPRESET_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Beacons::restoreActivePreset (ID = 0x00000006)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void BeaconsServerAppInit(void)
{
    Beacons_registerServerApi(&BeaconsServerApiCtx);
}
