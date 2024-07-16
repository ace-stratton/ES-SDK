#ifndef ES_ADCS_OP_MODES_SM_CONFIG_USER_H
#define ES_ADCS_OP_MODES_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
// USER_CODE_END::@main@

// Entry/Exit functions

// Guard condition functions

// Action handlers
void es_adcs_op_modes_sm_action_prepare_idle_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void es_adcs_op_modes_sm_action_prepare_trigger_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void es_adcs_op_modes_sm_action_prepare_run_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef ES_ADCS_OP_MODES_SM_CONFIG_USER_H