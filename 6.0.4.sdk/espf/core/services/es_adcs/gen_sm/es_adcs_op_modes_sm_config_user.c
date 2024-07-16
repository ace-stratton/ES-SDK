#include "libhsm.h"
#include "es_adcs_op_modes_sm_config_user.h"

// USER_CODE_START::@main@

#include "es_adcs.h"
#include "actuator_control_service.h"
#include "nvm.h"

// USER_CODE_END::@main@

// Entry/Exit functions






// Guard condition functions

// Action handlers
// GEN_OBJ_START::es_adcs_op_modes_sm_action_prepare_idle_mode
void es_adcs_op_modes_sm_action_prepare_idle_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_prepare_idle_mode

	/* Read sensor data service configuration from nvm, disable fast sampling, write back to nvm */
	sds_sens_read_freq_t sds_chan_freq_cfgs;

	Nvm_GetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sds_chan_freq_cfgs);
	sds_chan_freq_cfgs.enable = SAFE_FALSE;
	Nvm_SetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sds_chan_freq_cfgs, NVMSETBLOCK_STORE_IMMEDIATELY);

	/* Stop the magnetorquer control service since the ADCS is transitioning to IDLE mode */
	actuator_control_service_stop();

    // USER_CODE_END::action_prepare_idle_mode
}
// GEN_OBJ_END::es_adcs_op_modes_sm_action_prepare_idle_mode

// GEN_OBJ_START::es_adcs_op_modes_sm_action_prepare_trigger_mode
void es_adcs_op_modes_sm_action_prepare_trigger_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_prepare_trigger_mode

	/* Read sensor data service configuration from nvm, enable fast sampling, write back to nvm */
	sds_sens_read_freq_t sds_chan_freq_cfgs;

	Nvm_GetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sds_chan_freq_cfgs);
	sds_chan_freq_cfgs.enable = SAFE_TRUE;
	Nvm_SetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sds_chan_freq_cfgs, NVMSETBLOCK_STORE_IMMEDIATELY);

	/* Force the ADCS to skip a control loop in order to accumulate enough high rate sensor data */
	es_adcs_set_skip_loop();

	/* Start the magnetorquer control service since the ADCS is transitioning to an active mode */
	actuator_control_service_start();

    // USER_CODE_END::action_prepare_trigger_mode
}
// GEN_OBJ_END::es_adcs_op_modes_sm_action_prepare_trigger_mode

// GEN_OBJ_START::es_adcs_op_modes_sm_action_prepare_run_mode
void es_adcs_op_modes_sm_action_prepare_run_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_prepare_run_mode

	/* Read sensor data service configuration from nvm, enable fast sampling, write back to nvm */
	sds_sens_read_freq_t sds_chan_freq_cfgs;

	Nvm_GetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sds_chan_freq_cfgs);
	sds_chan_freq_cfgs.enable = SAFE_TRUE;
	Nvm_SetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sds_chan_freq_cfgs, NVMSETBLOCK_STORE_IMMEDIATELY);

	/* Force the ADCS to skip a control loop in order to accumulate enough high rate sensor data */
	es_adcs_set_skip_loop();

	/* Start the magnetorquer control service since the ADCS is transitioning to an active mode */
	actuator_control_service_start();

    // USER_CODE_END::action_prepare_run_mode
}
// GEN_OBJ_END::es_adcs_op_modes_sm_action_prepare_run_mode
