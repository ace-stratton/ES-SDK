/*!
********************************************************************************************
* @file FP_OBC_CUBEADCS_GEN2ServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface OBC_CUBEADCS_GEN2 v1.0
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

#include "FP_OBC_CUBEADCS_GEN2ProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "cubeadcs_gen2_transfer.h"
#include "if_sys_conf.h"
#include "cubeadcs_gen2.h"
#include "cubeadcs_gen2_gw.h"
#include "cubeadcs_gen2_events.h"
#include "cubeadcs_gen2_fdir.h"
#include "nvm_app_types.h"
#include <assert.h>
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void OBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2reqStateMachineStateChangeRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_getStateMachineStateRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_getOpStatusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2reqSoftResetAndModeRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_download_evtRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2download_evtRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_download_evt_statusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_download_tlmRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2download_tlmRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_download_tlm_statusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_download_img_storedRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2download_img_storedRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_get_fdir_statsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2set_commissioning_statusRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2set_tlm_cfgRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2get_nvm_system_states_cfgRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2set_nvm_system_states_cfgRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2fw_update_cube_computerRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCS_GEN2fw_update_cube_nodeRequestData_t* pRequestData);

static void OBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static OBC_CUBEADCS_GEN2_ServerApi_t OBC_CUBEADCS_GEN2ServerApiCtx =
{
  .OBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandler = (pfOBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandler_t) OBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_getStateMachineStateRequestHandler = (pfOBC_CUBEADCS_GEN2_getStateMachineStateRequestHandler_t) OBC_CUBEADCS_GEN2_getStateMachineStateRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_getOpStatusRequestHandler = (pfOBC_CUBEADCS_GEN2_getOpStatusRequestHandler_t) OBC_CUBEADCS_GEN2_getOpStatusRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandler = (pfOBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandler_t) OBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandler = (pfOBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandler_t) OBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandler = (pfOBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandler_t) OBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_download_evtRequestHandler = (pfOBC_CUBEADCS_GEN2_download_evtRequestHandler_t) OBC_CUBEADCS_GEN2_download_evtRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_download_evt_statusRequestHandler = (pfOBC_CUBEADCS_GEN2_download_evt_statusRequestHandler_t) OBC_CUBEADCS_GEN2_download_evt_statusRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_download_tlmRequestHandler = (pfOBC_CUBEADCS_GEN2_download_tlmRequestHandler_t) OBC_CUBEADCS_GEN2_download_tlmRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_download_tlm_statusRequestHandler = (pfOBC_CUBEADCS_GEN2_download_tlm_statusRequestHandler_t) OBC_CUBEADCS_GEN2_download_tlm_statusRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_download_img_storedRequestHandler = (pfOBC_CUBEADCS_GEN2_download_img_storedRequestHandler_t) OBC_CUBEADCS_GEN2_download_img_storedRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandler = (pfOBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandler_t) OBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandler = (pfOBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandler_t) OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandler = (pfOBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandler_t) OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_get_fdir_statsRequestHandler = (pfOBC_CUBEADCS_GEN2_get_fdir_statsRequestHandler_t) OBC_CUBEADCS_GEN2_get_fdir_statsRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandler = (pfOBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandler_t) OBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandler = (pfOBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandler_t) OBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandler = (pfOBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandler_t) OBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandler = (pfOBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandler_t) OBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandler = (pfOBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandler_t) OBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandler = (pfOBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandler_t) OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandler = (pfOBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandler_t) OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandler = (pfOBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandler_t) OBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandler = (pfOBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandler_t) OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandler = (pfOBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandler_t) OBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandlerImpl,
  .OBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandler = (pfOBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandler_t) OBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method OBC_CUBEADCS_GEN2::reqStateMachineStateChange (ID = 0x0000000A)
static void OBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2reqStateMachineStateChangeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::reqStateMachineStateChange@
    sm_event_ctx_t event_ctx;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::reqStateMachineStateChange@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::reqStateMachineStateChange@

        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            event_ctx.sys_state.sys_state_core_cfg.cntrl_mode = pRequestData->sState_change_event_args.sCore_args.eControl_mode;
            event_ctx.sys_state.sys_state_core_cfg.est_mode_main =
                pRequestData->sState_change_event_args.sCore_args.eEstimation_mode_main;
            event_ctx.sys_state.sys_state_core_cfg.est_mode_backup =
                pRequestData->sState_change_event_args.sCore_args.eEstimation_mode_backup;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.rwl0Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eRwl0;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.rwl1Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eRwl1;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.rwl2Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eRwl2;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.rwl3Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eRwl3;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.mag0Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eMag0;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.mag1Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eMag1;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.gyro0Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eGyro0;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.gyro1Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eGyro1;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.fss0Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eFss0;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.fss1Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eFss1;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.fss2Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eFss2;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.fss3Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eFss3;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.hss0Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eHss0;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.hss1Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eHss1;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.str0Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eStr0;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.str1Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eStr1;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.extSensor0Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eExtSensor0;
            event_ctx.sys_state.sys_state_core_cfg.pwr_state.extSensor1Power =
                pRequestData->sState_change_event_args.sCore_args.sNodes_pwr_states.eExtSensor1;
            event_ctx.sys_state.ref_params.ref_param_1 =
                pRequestData->sState_change_event_args.sRef_params.fRef_param1;
            event_ctx.sys_state.ref_params.ref_param_2 =
                pRequestData->sState_change_event_args.sRef_params.fRef_param2;
            event_ctx.sys_state.ref_params.ref_param_3 =
                pRequestData->sState_change_event_args.sRef_params.fRef_param3;
            event_ctx.sys_state.req_state_id = pRequestData->sState_change_event_args.u8Req_state_id;

            if (true == cubeadcs_gen2_trigger_sm((uint32_t)pRequestData->eSm_event, &event_ctx))
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::reqStateMachineStateChange@

        respResult = OBC_CUBEADCS_GEN2_reqStateMachineStateChangeResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_REQSTATEMACHINESTATECHANGE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::reqStateMachineStateChange (ID = 0x0000000A)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::getStateMachineState (ID = 0x0000000B)
static void OBC_CUBEADCS_GEN2_getStateMachineStateRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StateMachineStates_t eSm_state;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::getStateMachineState@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::getStateMachineState@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::getStateMachineState@

        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            eSm_state = cubeadcs_gen2_get_sm_state()->state_id;

            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eSm_state  = OBC_CUBEADCS_GEN2_STATEMACHINESTATES_MAX_CNT;
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::getStateMachineState@

        respResult = OBC_CUBEADCS_GEN2_getStateMachineStateResp(
                        &respCtx,
                        eSm_state,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GETSTATEMACHINESTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::getStateMachineState (ID = 0x0000000B)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::getOpStatus (ID = 0x0000000C)
static void OBC_CUBEADCS_GEN2_getOpStatusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_OpStatusCommon_t sOp_status_common;
    OBC_CUBEADCS_GEN2_OpStatusApp_t sOp_status_app;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::getOpStatus@
    op_status_t op_status = {0};
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::getOpStatus@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::getOpStatus@

        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            cubeadcs_gen2_get_op_status(&op_status);

            // todo ... need a better solution here

            sOp_status_common.sBoot_status.eState 				= (OBC_CUBEADCS_GEN2_BootState_t)op_status.common_tlm.boot_status.state;
            sOp_status_common.sBoot_status.eResetReason 		= (OBC_CUBEADCS_GEN2_BootResetReason_t)op_status.common_tlm.boot_status.resetReason;
            sOp_status_common.sBoot_status.bSharedParamsError   = op_status.common_tlm.boot_status.sharedParamsError;
            sOp_status_common.sBoot_status.bPortValidationError = op_status.common_tlm.boot_status.portValidationError;
            sOp_status_common.sBoot_status.bPortDiscoveryError  = op_status.common_tlm.boot_status.portDiscoveryError;
            sOp_status_common.sBoot_status.bOtpSerialError      = op_status.common_tlm.boot_status.otpSerialError;
            sOp_status_common.sBoot_status.bCfgSerialError      = op_status.common_tlm.boot_status.cfgSerialError;
            sOp_status_common.sBoot_status.bSerialMismatchError = op_status.common_tlm.boot_status.serialMismatchError;
            sOp_status_common.sBoot_status.bConfigInvalidError  = op_status.common_tlm.boot_status.configInvalidError;

            sOp_status_common.sPower_state.eExtSensor0 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.extSensor0Power;
            sOp_status_common.sPower_state.eExtSensor1 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.extSensor1Power;
            sOp_status_common.sPower_state.eFss0 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.fss0Power;
            sOp_status_common.sPower_state.eFss1 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.fss1Power;
            sOp_status_common.sPower_state.eFss2 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.fss2Power;
            sOp_status_common.sPower_state.eFss3 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.fss3Power;
            sOp_status_common.sPower_state.eGyro0 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.gyro0Power;
            sOp_status_common.sPower_state.eGyro1 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.gyro1Power;
            sOp_status_common.sPower_state.eHss0 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.hss0Power;
            sOp_status_common.sPower_state.eHss1 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.hss1Power;
            sOp_status_common.sPower_state.eMag0 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.mag0Power;
            sOp_status_common.sPower_state.eMag1 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.mag1Power;
            sOp_status_common.sPower_state.eRwl0 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.rwl0Power;
            sOp_status_common.sPower_state.eRwl1 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.rwl1Power;
            sOp_status_common.sPower_state.eRwl2 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.rwl2Power;
            sOp_status_common.sPower_state.eRwl3 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.rwl3Power;
            sOp_status_common.sPower_state.eStr0 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.str0Power;
            sOp_status_common.sPower_state.eStr1 =
                (OBC_CUBEADCS_GEN2_NodePowerState_t)op_status.common_tlm.power_state.str1Power;

            sOp_status_common.sComp_err_codes.u32MasterSvc   = op_status.common_tlm.comp_err_codes.masterSvc;
            sOp_status_common.sComp_err_codes.u32FramFsSvc   = op_status.common_tlm.comp_err_codes.framFsSvc;
            sOp_status_common.sComp_err_codes.u32EventLogSvc = op_status.common_tlm.comp_err_codes.eventLogSvc;
            sOp_status_common.sComp_err_codes.u32ImgLogSvc   = op_status.common_tlm.comp_err_codes.imgLogSvc;
            sOp_status_common.sComp_err_codes.u32TlmLogSvc   = op_status.common_tlm.comp_err_codes.tlmLogSvc;
            sOp_status_common.sComp_err_codes.u32ImuSvc      = op_status.common_tlm.comp_err_codes.imuSvc;

            sOp_status_common.bIs_valid = op_status.common_tlm.is_valid;

            sOp_status_app.eRun_mode = (OBC_CUBEADCS_GEN2_AdcsRunMode_t)op_status.app_tlm.run_mode;

            sOp_status_app.sControl_mode.eControl_mode =
                (OBC_CUBEADCS_GEN2_ControlModes_t)op_status.app_tlm.control_mode.controlMode;
            sOp_status_app.sControl_mode.u16Timeout = op_status.app_tlm.control_mode.magConTimeout;

            sOp_status_app.sEstimation_mode.eMain =
                (OBC_CUBEADCS_GEN2_EstimationModes_t)op_status.app_tlm.est_mode.estModeMain;
            sOp_status_app.sEstimation_mode.eBackup =
                (OBC_CUBEADCS_GEN2_EstimationModes_t)op_status.app_tlm.est_mode.estModeBackup;

            sOp_status_app.eOp_state = (OBC_CUBEADCS_GEN2_AdcsOpState_t)op_status.app_tlm.op_state;

            sOp_status_app.bIs_valid = op_status.app_tlm.is_valid;

            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::getOpStatus@

        respResult = OBC_CUBEADCS_GEN2_getOpStatusResp(
                        &respCtx,
                        &sOp_status_common,
                        &sOp_status_app,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GETOPSTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::getOpStatus (ID = 0x0000000C)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::reqSoftResetAndMode (ID = 0x0000000D)
static void OBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2reqSoftResetAndModeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::reqSoftResetAndMode@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::reqSoftResetAndMode@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::reqSoftResetAndMode@
        
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
        	if ( true == cubeadcs_gen2_reset_handler((cubeadcs_gen2_control_program_type_t)pRequestData->eProg_type) )
        	{
        		eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        	}
        	else
        	{
        		eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
        	}
        }
        else
        {
        	eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::reqSoftResetAndMode@

        respResult = OBC_CUBEADCS_GEN2_reqSoftResetAndModeResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_REQSOFTRESETANDMODE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::reqSoftResetAndMode (ID = 0x0000000D)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::get_events_since_last_power_up (ID = 0x0000000E)
static void OBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_events_t sAll_events;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::get_events_since_last_power_up@
    cubeadcs_gen2_events_cnts_t events_cache = {0};
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::get_events_since_last_power_up@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::get_events_since_last_power_up@
        
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            if (true == cubeadcs_gen2_events_get_events_stats(&events_cache) )
            {
                (void)memcpy((void *)&sAll_events, &events_cache.all_read_events, sizeof(uint16_t) * CUBEADCS_GEN2_EVENTS_MAX);

                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::get_events_since_last_power_up@

        respResult = OBC_CUBEADCS_GEN2_get_events_since_last_power_upResp(
                        &respCtx,
                        &sAll_events,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GET_EVENTS_SINCE_LAST_POWER_UP_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::get_events_since_last_power_up (ID = 0x0000000E)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::clear_events_since_last_power_up (ID = 0x0000000F)
static void OBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::clear_events_since_last_power_up@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::clear_events_since_last_power_up@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::clear_events_since_last_power_up@
        
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            if ( true == cubeadcs_gen2_events_clear_event_stats(CUBEADCS_GEN2_EVENTS_CLEAR_ALL_EVENTS) )
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::clear_events_since_last_power_up@

        respResult = OBC_CUBEADCS_GEN2_clear_events_since_last_power_upResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_CLEAR_EVENTS_SINCE_LAST_POWER_UP_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::clear_events_since_last_power_up (ID = 0x0000000F)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::download_evt (ID = 0x00000010)
static void OBC_CUBEADCS_GEN2_download_evtRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2download_evtRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::download_evt@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::download_evt@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::download_evt@
        
        u32Err = cubeadcs_gen2_transfer_evt(
                (const char*)pRequestData->sFile_name.au8Name,
                (const TctlmCubeComputerCommon3_EventLogFilterTransferSetup*)&pRequestData->sSetup);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::download_evt@

        respResult = OBC_CUBEADCS_GEN2_download_evtResp(
                        &respCtx,
                        u32Err
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::download_evt (ID = 0x00000010)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::download_evt_status (ID = 0x00000011)
static void OBC_CUBEADCS_GEN2_download_evt_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_download_event_status_t sStatus;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::download_evt_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::download_evt_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::download_evt_status@
        
        static_assert(sizeof(OBC_CUBEADCS_GEN2_download_event_status_t) ==
                      sizeof(cubeadcs_gen2_transfer_evt_status_t));

        u32Err = cubeadcs_gen2_transfer_evt_status(
                (cubeadcs_gen2_transfer_evt_status_t*)&sStatus);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::download_evt_status@

        respResult = OBC_CUBEADCS_GEN2_download_evt_statusResp(
                        &respCtx,
                        u32Err,
                        &sStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::download_evt_status (ID = 0x00000011)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::download_tlm (ID = 0x00000012)
static void OBC_CUBEADCS_GEN2_download_tlmRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2download_tlmRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::download_tlm@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::download_tlm@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::download_tlm@
        
        static_assert(sizeof(OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TelemetryLogTransferSetup_t) ==
                      sizeof(TctlmCubeComputerCommon3_TelemetryLogTransferSetup));

        u32Err = cubeadcs_gen2_transfer_tlm(
                (const char*)pRequestData->sFile_name.au8Name,
                (const TctlmCubeComputerCommon3_TelemetryLogTransferSetup*)&pRequestData->sSetup);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::download_tlm@

        respResult = OBC_CUBEADCS_GEN2_download_tlmResp(
                        &respCtx,
                        u32Err
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::download_tlm (ID = 0x00000012)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::download_tlm_status (ID = 0x00000013)
static void OBC_CUBEADCS_GEN2_download_tlm_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_download_telemetry_status_t sStatus;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::download_tlm_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::download_tlm_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::download_tlm_status@
        
        static_assert(sizeof(OBC_CUBEADCS_GEN2_download_telemetry_status_t) ==
                      sizeof(cubeadcs_gen2_transfer_tlm_status_t));

        u32Err = cubeadcs_gen2_transfer_tlm_status(
                (cubeadcs_gen2_transfer_tlm_status_t*)&sStatus);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::download_tlm_status@

        respResult = OBC_CUBEADCS_GEN2_download_tlm_statusResp(
                        &respCtx,
                        u32Err,
                        &sStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::download_tlm_status (ID = 0x00000013)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::download_img_stored (ID = 0x00000014)
static void OBC_CUBEADCS_GEN2_download_img_storedRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2download_img_storedRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::download_img_stored@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::download_img_stored@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::download_img_stored@
        
        u32Err = cubeadcs_gen2_transfer_img_stored(
                (const char*)pRequestData->sFile_name.au8Name, pRequestData->u32File_handle);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::download_img_stored@

        respResult = OBC_CUBEADCS_GEN2_download_img_storedResp(
                        &respCtx,
                        u32Err
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::download_img_stored (ID = 0x00000014)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::download_img_stored_status (ID = 0x00000015)
static void OBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_download_image_stored_status_t sStatus;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::download_img_stored_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::download_img_stored_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::download_img_stored_status@
        
        static_assert(sizeof(OBC_CUBEADCS_GEN2_download_image_stored_status_t) ==
                      sizeof(cubeadcs_gen2_transfer_img_stored_status_t));

        u32Err = cubeadcs_gen2_transfer_img_stored_status(
                (cubeadcs_gen2_transfer_img_stored_status_t*)&sStatus);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::download_img_stored_status@

        respResult = OBC_CUBEADCS_GEN2_download_img_stored_statusResp(
                        &respCtx,
                        u32Err,
                        &sStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::download_img_stored_status (ID = 0x00000015)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::get_fdir_unrecovarable_errors (ID = 0x00000018)
static void OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Errors;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::get_fdir_unrecovarable_errors@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::get_fdir_unrecovarable_errors@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::get_fdir_unrecovarable_errors@
        
        cubeadcs_gen2_fdir_errors_t err_cache = 0U;

        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            if ( true == cubeadcs_gen2_fdir_get_errors(&err_cache) )
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }

        u32Errors = err_cache;

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::get_fdir_unrecovarable_errors@

        respResult = OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsResp(
                        &respCtx,
                        u32Errors,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GET_FDIR_UNRECOVARABLE_ERRORS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::get_fdir_unrecovarable_errors (ID = 0x00000018)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::clear_fdir_unrecovarable_errors (ID = 0x00000019)
static void OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::clear_fdir_unrecovarable_errors@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::clear_fdir_unrecovarable_errors@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::clear_fdir_unrecovarable_errors@
        
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            if ( true == cubeadcs_gen2_fdir_clear_errors() )
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::clear_fdir_unrecovarable_errors@

        respResult = OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_CLEAR_FDIR_UNRECOVARABLE_ERRORS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::clear_fdir_unrecovarable_errors (ID = 0x00000019)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::get_fdir_stats (ID = 0x0000001A)
static void OBC_CUBEADCS_GEN2_get_fdir_statsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_fdir_stat_t asFdir_logic[14];
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::get_fdir_stats@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::get_fdir_stats@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::get_fdir_stats@
        
        cubeadcs_gen2_fdir_failure_ctx_t fdir_ctx_cache = {0};

        eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;

        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            if ( true == cubeadcs_gen2_fdir_get_fdir_ctx(&fdir_ctx_cache) )
            {
                for (uint8_t idx = 0; idx < OBC_CUBEADCS_GEN2_EVENTS_ENUM_MAX_CNT; idx++)
                {
                    asFdir_logic[idx].eEvent_type = fdir_ctx_cache.fdir_handlers[idx].failure_event;
                    asFdir_logic[idx].u8Event_fdir_execution_num = fdir_ctx_cache.fdir_handlers[idx].failure_event_handler_exec;

                    for (uint8_t ev_h = 0; ev_h < CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC; ev_h++)
                    {
                        asFdir_logic[idx].abEvent_fdir_execution_res[ev_h] = fdir_ctx_cache.fdir_handlers[idx].failure_event_handler_exec_op_res[ev_h];
                    }
                }

                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::get_fdir_stats@

        respResult = OBC_CUBEADCS_GEN2_get_fdir_statsResp(
                        &respCtx,
                        asFdir_logic,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GET_FDIR_STATS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::get_fdir_stats (ID = 0x0000001A)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::clear_fdir_stats (ID = 0x0000001B)
static void OBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::clear_fdir_stats@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::clear_fdir_stats@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::clear_fdir_stats@
        
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            if ( true == cubeadcs_gen2_fdir_clear_fdir_ctx_handlers() )
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::clear_fdir_stats@

        respResult = OBC_CUBEADCS_GEN2_clear_fdir_statsResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_CLEAR_FDIR_STATS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::clear_fdir_stats (ID = 0x0000001B)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::get_commissioning_status (ID = 0x0000001C)
static void OBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_CommissioningStatus_t eStatus;
    OBC_CUBEADCS_GEN2_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::get_commissioning_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::get_commissioning_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::get_commissioning_status@
        
        if (false != cubeadcs_gen2_get_cms_status(&eStatus))
        {
            eOpResult = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOpResult = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::get_commissioning_status@

        respResult = OBC_CUBEADCS_GEN2_get_commissioning_statusResp(
                        &respCtx,
                        eStatus,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GET_COMMISSIONING_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::get_commissioning_status (ID = 0x0000001C)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::set_commissioning_status (ID = 0x0000001D)
static void OBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2set_commissioning_statusRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::set_commissioning_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::set_commissioning_status@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::set_commissioning_status@
        
        if (false != cubeadcs_gen2_set_cms_status(pRequestData->eStatus))
        {
            eOpResult = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOpResult = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::set_commissioning_status@

        respResult = OBC_CUBEADCS_GEN2_set_commissioning_statusResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_SET_COMMISSIONING_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::set_commissioning_status (ID = 0x0000001D)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::get_tlm_cfg (ID = 0x0000001E)
static void OBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_telemetry_mask_0_t sMask_0;
    OBC_CUBEADCS_GEN2_telemetry_mask_1_t sMask_1;
    OBC_CUBEADCS_GEN2_telemetry_mask_2_t sMask_2;
    OBC_CUBEADCS_GEN2_telemetry_mask_3_t sMask_3;
    OBC_CUBEADCS_GEN2_telemetry_mask_4_t sMask_4;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::get_tlm_cfg@
    cubeadcs_gen2_tlm_cfg_t tlm_cfg;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::get_tlm_cfg@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::get_tlm_cfg@
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_GEN2_TLM_CFG, (void *)&tlm_cfg);

            sMask_0.bEn_get_health_tlm_for_cubenode_pst3s = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_0];
            sMask_0.bEn_get_health_tlm_for_cubemag_magnetometer = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_1];
            sMask_0.bEn_get_health_tlm_for_cubesense_sun = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_2];
            sMask_0.bEn_get_torquer_current_measurements = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_3];
            sMask_0.bEn_get_raw_cubesense_sun_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_4];
            sMask_0.bEn_get_raw_external_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_5];
            sMask_0.bEn_get_controller_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_6];
            sMask_0.bEn_get_backup_estimator_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_7];

            sMask_1.bEn_get_models_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_0];
            sMask_1.bEn_get_calibrated_gnss_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_1];
            sMask_1.bEn_get_calibrated_hss_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_2];
            sMask_1.bEn_get_calibrated_mag_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_3];
            sMask_1.bEn_get_calibrated_fss_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_4];
            sMask_1.bEn_get_raw_cubesense_earth_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_5];
            sMask_1.bEn_get_raw_mag_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_6];
            sMask_1.bEn_get_raw_css_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_7];

            sMask_2.bEn_get_raw_gyr_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_0];
            sMask_2.bEn_get_raw_rwl_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_1];
            sMask_2.bEn_get_calibrated_css_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_2];
            sMask_2.bEn_get_calibrated_gyr_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_3];
            sMask_2.bEn_get_calibrated_str_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_4];
            sMask_2.bEn_get_calibrated_rwl_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_5];
            sMask_2.bEn_get_main_estimator_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_6];
            sMask_2.bEn_get_main_estimator_high_resolution_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_7];

            sMask_3.bEn_get_raw_gnss_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_0];
            sMask_3.bEn_get_raw_pst3s_star_tracker_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_1];
            sMask_3.bEn_get_acp_execution_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_2];
            sMask_3.bEn_get_cubecomputer_health = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_3];
            sMask_3.bEn_get_health_telemetry_for_cubesense_earth = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_4];
            sMask_3.bEn_get_health_telemetry_for_reaction_wheels = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_5];
            sMask_3.bEn_get_health_telemetry_for_cubenode_nssrwl = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_6];
            sMask_3.bEn_get_raw_nssrwl_sensor_telemetry = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_7];

            sMask_4.bEn_get_health_telemetry_for_cubestar = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_0];
            sMask_4.bReserved_0 = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_1];
            sMask_4.bReserved_1 = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_2];
            sMask_4.bReserved_2 = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_3];
            sMask_4.bReserved_3 = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_4];
            sMask_4.bReserved_4 = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_5];
            sMask_4.bReserved_5 = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_6];
            sMask_4.bReserved_6 = tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_7];

            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::get_tlm_cfg@

        respResult = OBC_CUBEADCS_GEN2_get_tlm_cfgResp(
                        &respCtx,
                        &sMask_0,
                        &sMask_1,
                        &sMask_2,
                        &sMask_3,
                        &sMask_4,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GET_TLM_CFG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::get_tlm_cfg (ID = 0x0000001E)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::set_tlm_cfg (ID = 0x0000001F)
static void OBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2set_tlm_cfgRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::set_tlm_cfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::set_tlm_cfg@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::set_tlm_cfg@
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            cubeadcs_gen2_tlm_cfg_t new_tlm_cfg;
            cubeadcs_gen2_tlm_cfg_t tlm_cfg;

            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_0] = pRequestData->sMask_0.bEn_get_health_tlm_for_cubenode_pst3s;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_1] = pRequestData->sMask_0.bEn_get_health_tlm_for_cubemag_magnetometer;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_2] = pRequestData->sMask_0.bEn_get_health_tlm_for_cubesense_sun;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_3] = pRequestData->sMask_0.bEn_get_torquer_current_measurements;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_4] = pRequestData->sMask_0.bEn_get_raw_cubesense_sun_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_5] = pRequestData->sMask_0.bEn_get_raw_external_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_6] = pRequestData->sMask_0.bEn_get_controller_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_0][CUBEADCS_GEN2_TLM_MASK_BYTES_7] = pRequestData->sMask_0.bEn_get_backup_estimator_telemetry;

            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_0] = pRequestData->sMask_1.bEn_get_models_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_1] = pRequestData->sMask_1.bEn_get_calibrated_gnss_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_2] = pRequestData->sMask_1.bEn_get_calibrated_hss_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_3] = pRequestData->sMask_1.bEn_get_calibrated_mag_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_4] = pRequestData->sMask_1.bEn_get_calibrated_fss_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_5] = pRequestData->sMask_1.bEn_get_raw_cubesense_earth_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_6] = pRequestData->sMask_1.bEn_get_raw_mag_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_1][CUBEADCS_GEN2_TLM_MASK_BYTES_7] = pRequestData->sMask_1.bEn_get_raw_css_sensor_telemetry;

            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_0] = pRequestData->sMask_2.bEn_get_raw_gyr_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_1] = pRequestData->sMask_2.bEn_get_raw_rwl_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_2] = pRequestData->sMask_2.bEn_get_calibrated_css_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_3] = pRequestData->sMask_2.bEn_get_calibrated_gyr_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_4] = pRequestData->sMask_2.bEn_get_calibrated_str_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_5] = pRequestData->sMask_2.bEn_get_calibrated_rwl_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_6] = pRequestData->sMask_2.bEn_get_main_estimator_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_2][CUBEADCS_GEN2_TLM_MASK_BYTES_7] = pRequestData->sMask_2.bEn_get_main_estimator_high_resolution_telemetry;

            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_0] = pRequestData->sMask_3.bEn_get_raw_gnss_sensor_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_1] = pRequestData->sMask_3.bEn_get_raw_pst3s_star_tracker_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_2] = pRequestData->sMask_3.bEn_get_acp_execution_telemetry;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_3] = pRequestData->sMask_3.bEn_get_cubecomputer_health;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_4] = pRequestData->sMask_3.bEn_get_health_telemetry_for_cubesense_earth;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_5] = pRequestData->sMask_3.bEn_get_health_telemetry_for_reaction_wheels;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_6] = pRequestData->sMask_3.bEn_get_health_telemetry_for_cubenode_nssrwl;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_3][CUBEADCS_GEN2_TLM_MASK_BYTES_7] = pRequestData->sMask_3.bEn_get_raw_nssrwl_sensor_telemetry;

            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_0] = pRequestData->sMask_4.bEn_get_health_telemetry_for_cubestar;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_1] = pRequestData->sMask_4.bReserved_0;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_2] = pRequestData->sMask_4.bReserved_1;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_3] = pRequestData->sMask_4.bReserved_2;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_4] = pRequestData->sMask_4.bReserved_3;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_5] = pRequestData->sMask_4.bReserved_4;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_6] = pRequestData->sMask_4.bReserved_5;
            new_tlm_cfg.mask[CUBEADCS_GEN2_TLM_MASK_4][CUBEADCS_GEN2_TLM_MASK_BYTES_7] = pRequestData->sMask_4.bReserved_6;

            Nvm_SetBlockById(NVM_BLOCK_CUBEADCS_GEN2_TLM_CFG,(void *)&new_tlm_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

            Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_GEN2_TLM_CFG, (void *)&tlm_cfg);

            if ( 0 == memcmp((const void *)&new_tlm_cfg.mask,(const void *)&tlm_cfg.mask, sizeof(tlm_cfg.mask)) )
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::set_tlm_cfg@

        respResult = OBC_CUBEADCS_GEN2_set_tlm_cfgResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_SET_TLM_CFG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::set_tlm_cfg (ID = 0x0000001F)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::get_nvm_system_states_cfg (ID = 0x00000020)
static void OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2get_nvm_system_states_cfgRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_state_change_core_args_t sSys_states_cfg;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::get_nvm_system_states_cfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::get_nvm_system_states_cfg@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::get_nvm_system_states_cfg@
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            cubeadcs_gen2_sys_states_cfg_t sys_state_nvm_cfg;

            Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_GEN2_SYS_STATE_CFG, (void *)&sys_state_nvm_cfg);

            sSys_states_cfg.eControl_mode = sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_get].cntrl_mode;
            sSys_states_cfg.eEstimation_mode_main = sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_get].est_mode_main;
            sSys_states_cfg.eEstimation_mode_backup = sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_get].est_mode_backup;

            memcpy(&sSys_states_cfg.sNodes_pwr_states, &sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_get].pwr_state, sizeof(sSys_states_cfg.sNodes_pwr_states));

            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::get_nvm_system_states_cfg@

        respResult = OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgResp(
                        &respCtx,
                        &sSys_states_cfg,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_GET_NVM_SYSTEM_STATES_CFG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::get_nvm_system_states_cfg (ID = 0x00000020)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::set_nvm_system_states_cfg (ID = 0x00000021)
static void OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2set_nvm_system_states_cfgRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::set_nvm_system_states_cfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::set_nvm_system_states_cfg@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::set_nvm_system_states_cfg@
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
        {
            cubeadcs_gen2_sys_states_cfg_t sys_state_nvm_cfg;

            Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_GEN2_SYS_STATE_CFG, (void *)&sys_state_nvm_cfg);

            sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_set].cntrl_mode = pRequestData->sSys_states_cfg.eControl_mode;
            sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_set].est_mode_main = pRequestData->sSys_states_cfg.eEstimation_mode_main;
            sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_set].est_mode_backup = pRequestData->sSys_states_cfg.eEstimation_mode_backup;

            static_assert(sizeof(sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_set].pwr_state) == sizeof(pRequestData->sSys_states_cfg.sNodes_pwr_states));
            memcpy(&sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_set].pwr_state, &pRequestData->sSys_states_cfg.sNodes_pwr_states, sizeof(sys_state_nvm_cfg.sys_state_cfg[pRequestData->eSys_state_to_set].pwr_state));

            Nvm_SetBlockById(NVM_BLOCK_CUBEADCS_GEN2_SYS_STATE_CFG, (void *)&sys_state_nvm_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOp_result = OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::set_nvm_system_states_cfg@

        respResult = OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_SET_NVM_SYSTEM_STATES_CFG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::set_nvm_system_states_cfg (ID = 0x00000021)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_computer (ID = 0x00000022)
static void OBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2fw_update_cube_computerRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_computer@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_computer@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_computer@
        
        u32Err = cubeadcs_gen2_transfer_boot_cube_space_file(
                (const char*)pRequestData->sControl_program_file_name.au8Name,
                (const char*)pRequestData->sConfiguration_file_name.au8Name,
                pRequestData->bForce);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_computer@

        respResult = OBC_CUBEADCS_GEN2_fw_update_cube_computerResp(
                        &respCtx,
                        u32Err
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_computer (ID = 0x00000022)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_computer_status (ID = 0x00000023)
static void OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_cube_computer_fw_update_status_t sStatus;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_computer_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_computer_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_computer_status@
        
        static_assert(sizeof(OBC_CUBEADCS_GEN2_cube_computer_fw_update_status_t) ==
                      sizeof(cubeadcs_gen2_transfer_boot_cube_space_file_status_t));

        u32Err = cubeadcs_gen2_transfer_boot_cube_space_file_status(
                (cubeadcs_gen2_transfer_boot_cube_space_file_status_t*)&sStatus);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_computer_status@

        respResult = OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusResp(
                        &respCtx,
                        u32Err,
                        &sStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_computer_status (ID = 0x00000023)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_node (ID = 0x00000024)
static void OBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCS_GEN2fw_update_cube_nodeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_node@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_node@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_node@
        
        u32Err = cubeadcs_gen2_transfer_appl_cube_space_file(
                (const char*)pRequestData->sControl_program_file_name.au8Name,
				(const char*)pRequestData->sConfiguration_file_name.au8Name,
                pRequestData->bForce,
                (TctlmCommonFrameworkEnums_NodeType)pRequestData->eNode_type,
                pRequestData->u32Serial_int);
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_node@

        respResult = OBC_CUBEADCS_GEN2_fw_update_cube_nodeResp(
                        &respCtx,
                        u32Err
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_node (ID = 0x00000024)

// @START@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_node_status (ID = 0x00000025)
static void OBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_cube_node_fw_update_status_t sStatus;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_node_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_node_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS_GEN2::fw_update_cube_node_status@

        static_assert(sizeof(OBC_CUBEADCS_GEN2_cube_node_fw_update_status_t) ==
                      sizeof(cubeadcs_gen2_transfer_appl_cube_space_file_status_t));

        u32Err = cubeadcs_gen2_transfer_appl_cube_space_file_status(
                (cubeadcs_gen2_transfer_appl_cube_space_file_status_t*)&sStatus);

        // @USER_CODE_SECTION_END@OBC_CUBEADCS_GEN2::fw_update_cube_node_status@

        respResult = OBC_CUBEADCS_GEN2_fw_update_cube_node_statusResp(
                        &respCtx,
                        u32Err,
                        &sStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2, OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS_GEN2::fw_update_cube_node_status (ID = 0x00000025)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void OBC_CUBEADCS_GEN2ServerAppInit(void)
{
    OBC_CUBEADCS_GEN2_registerServerApi(&OBC_CUBEADCS_GEN2ServerApiCtx);
}
