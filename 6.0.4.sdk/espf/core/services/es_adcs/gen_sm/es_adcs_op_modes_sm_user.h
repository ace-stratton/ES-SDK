#ifndef ES_ADCS_OP_MODES_SM_USER_H
#define ES_ADCS_OP_MODES_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum es_adcs_op_modes_sm_states
{
    STATE_ROOT,
    STATE_ADCS_RUN,
    STATE_ADCS_TRIGGER,
    STATE_ADCS_IDLE,
    STATE_ADCS_NOT_INIT,
    STATE_MAX
};

// User state machine events
enum es_adcs_op_modes_sm_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_es_adcs_op_modes_sm_run_to_idle,
    ev_es_adcs_op_modes_sm_run_to_trigger,
    ev_es_adcs_op_modes_sm_trigger_to_idle,
    ev_es_adcs_op_modes_sm_idle_to_run,
    ev_es_adcs_op_modes_sm_idle_to_trigger,
    ev_es_adcs_op_modes_sm_start,
    evMAX
};

// State machine root object
extern sCompositeState_t state_es_adcs_op_modes_sm;

// Use this macro to access the SM instance instead of a direct reference to
// state_es_adcs_op_modes_sm variable
#define es_adcs_op_modes_sm_instance  HSM_UPCAST_STATE(&state_es_adcs_op_modes_sm)

#ifdef __cplusplus
};
#endif

#endif  // #ifndef ES_ADCS_OP_MODES_SM_USER_H