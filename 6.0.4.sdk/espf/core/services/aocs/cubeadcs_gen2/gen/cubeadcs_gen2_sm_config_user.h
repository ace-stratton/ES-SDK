#ifndef CUBEADCS_GEN2_SM_CONFIG_USER_H
#define CUBEADCS_GEN2_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// USER_CODE_START::@main@
#include "datetime.h"
#include "cubeadcs_gen2.h"
#include "cubeadcs_gen2_sys_states.h"
#include "es_exeh.h"
#include "cubeadcs_gen2_cfg.h"

/** @brief Backoff time as define by CubeSpace. The bootloader needs certain time to boot.*/
#define CUBEADCS_GEN2_SM_BACKOFF_TIME_S (10)
/** @brief Check period in seconds. The OBC querries the ADCS for its status at this period.*/
#define CUABEADCS_GEN2_SM_CHECK_TIME_S (5)
/** @brief Events download period. Events download can take up to 2 seconds.*/
#define CUBEADCS_GEN2_SM_EVENT_DWN_TIME_S (30)

typedef struct {
    unix_time_t backoff_time_mark;
    unix_time_t check_time_mark;
    unix_time_t event_dwn_time_mark;
} cubeadcs_gen2_sm_ctx_t;
// USER_CODE_END::@main@

// Entry/Exit functions
void cubeadcs_gen2_sm_on_entry_Backoff(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void cubeadcs_gen2_sm_on_entry_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void cubeadcs_gen2_sm_on_entry_EventDownload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void cubeadcs_gen2_sm_on_entry_StateChange(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void cubeadcs_gen2_sm_on_exit_StateChange(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

// Guard condition functions
bool cubeadcs_gen2_sm_guard_is_adcs_ready(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool cubeadcs_gen2_sm_guard_is_time_to_check_expired(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool cubeadcs_gen2_sm_guard_is_time_to_event_download_expired(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool cubeadcs_gen2_sm_guard_is_state_change_valid(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);

// Action handlers
void cubeadcs_gen2_sm_action_notify_users(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef CUBEADCS_GEN2_SM_CONFIG_USER_H