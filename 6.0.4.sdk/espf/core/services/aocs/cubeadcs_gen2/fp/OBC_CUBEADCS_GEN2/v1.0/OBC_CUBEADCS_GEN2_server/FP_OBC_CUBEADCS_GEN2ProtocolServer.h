/*!
********************************************************************************************
* @file FP_OBC_CUBEADCS_GEN2ProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_OBC_CUBEADCS_GEN2PROTOCOLSERVER_H__
#define __FP_OBC_CUBEADCS_GEN2PROTOCOLSERVER_H__

#include "FP_OBC_CUBEADCS_GEN2ProtocolTypes.h"

typedef void (*pfOBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2reqStateMachineStateChangeRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_getStateMachineStateRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_getOpStatusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2reqSoftResetAndModeRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_download_evtRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2download_evtRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_download_evt_statusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_download_tlmRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2download_tlmRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_download_tlm_statusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_download_img_storedRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2download_img_storedRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_get_fdir_statsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2set_commissioning_statusRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2set_tlm_cfgRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2get_nvm_system_states_cfgRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2set_nvm_system_states_cfgRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2fw_update_cube_computerRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandler_t)(ReqContext_t *ctx, OBC_CUBEADCS_GEN2fw_update_cube_nodeRequestData_t *pRequestData);
typedef void (*pfOBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfOBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandler_t OBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandler;
    pfOBC_CUBEADCS_GEN2_getStateMachineStateRequestHandler_t OBC_CUBEADCS_GEN2_getStateMachineStateRequestHandler;
    pfOBC_CUBEADCS_GEN2_getOpStatusRequestHandler_t OBC_CUBEADCS_GEN2_getOpStatusRequestHandler;
    pfOBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandler_t OBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandler;
    pfOBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandler_t OBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandler;
    pfOBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandler_t OBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandler;
    pfOBC_CUBEADCS_GEN2_download_evtRequestHandler_t OBC_CUBEADCS_GEN2_download_evtRequestHandler;
    pfOBC_CUBEADCS_GEN2_download_evt_statusRequestHandler_t OBC_CUBEADCS_GEN2_download_evt_statusRequestHandler;
    pfOBC_CUBEADCS_GEN2_download_tlmRequestHandler_t OBC_CUBEADCS_GEN2_download_tlmRequestHandler;
    pfOBC_CUBEADCS_GEN2_download_tlm_statusRequestHandler_t OBC_CUBEADCS_GEN2_download_tlm_statusRequestHandler;
    pfOBC_CUBEADCS_GEN2_download_img_storedRequestHandler_t OBC_CUBEADCS_GEN2_download_img_storedRequestHandler;
    pfOBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandler_t OBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandler;
    pfOBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandler_t OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandler;
    pfOBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandler_t OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandler;
    pfOBC_CUBEADCS_GEN2_get_fdir_statsRequestHandler_t OBC_CUBEADCS_GEN2_get_fdir_statsRequestHandler;
    pfOBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandler_t OBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandler;
    pfOBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandler_t OBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandler;
    pfOBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandler_t OBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandler;
    pfOBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandler_t OBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandler;
    pfOBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandler_t OBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandler;
    pfOBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandler_t OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandler;
    pfOBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandler_t OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandler;
    pfOBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandler_t OBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandler;
    pfOBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandler_t OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandler;
    pfOBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandler_t OBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandler;
    pfOBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandler_t OBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandler;
} OBC_CUBEADCS_GEN2_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_CUBEADCS_GEN2ProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void OBC_CUBEADCS_GEN2_registerServerApi(OBC_CUBEADCS_GEN2_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_OBC_CUBEADCS_GEN2ProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t OBC_CUBEADCS_GEN2_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_reqStateMachineStateChangeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_getStateMachineStateResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StateMachineStates_t eSm_state,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_getOpStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_OpStatusCommon_t * const sOp_status_common,
                const OBC_CUBEADCS_GEN2_OpStatusApp_t * const sOp_status_app,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_reqSoftResetAndModeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_events_since_last_power_upResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_events_t * const sAll_events,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_clear_events_since_last_power_upResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_evtResp(
                RespContext_t* ctx,
                const uint32_t u32Err
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_evt_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_download_event_status_t * const sStatus
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_tlmResp(
                RespContext_t* ctx,
                const uint32_t u32Err
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_tlm_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_download_telemetry_status_t * const sStatus
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_img_storedResp(
                RespContext_t* ctx,
                const uint32_t u32Err
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_img_stored_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_download_image_stored_status_t * const sStatus
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsResp(
                RespContext_t* ctx,
                const uint32_t u32Errors,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_fdir_statsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_fdir_stat_t * const asFdir_logic,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_clear_fdir_statsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_commissioning_statusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_CommissioningStatus_t eStatus,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_set_commissioning_statusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_tlm_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_telemetry_mask_0_t * const sMask_0,
                const OBC_CUBEADCS_GEN2_telemetry_mask_1_t * const sMask_1,
                const OBC_CUBEADCS_GEN2_telemetry_mask_2_t * const sMask_2,
                const OBC_CUBEADCS_GEN2_telemetry_mask_3_t * const sMask_3,
                const OBC_CUBEADCS_GEN2_telemetry_mask_4_t * const sMask_4,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_set_tlm_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_state_change_core_args_t * const sSys_states_cfg,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_computerResp(
                RespContext_t* ctx,
                const uint32_t u32Err
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_cube_computer_fw_update_status_t * const sStatus
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_nodeResp(
                RespContext_t* ctx,
                const uint32_t u32Err
);

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_node_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_cube_node_fw_update_status_t * const sStatus
);


#endif  // #ifndef __FP_OBC_CUBEADCS_GEN2PROTOCOLSERVER_H__
