/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TELEMETRY_SM_CONFIG_USER_H
#define TELEMETRY_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
#include "nvm/inc/nvm.h"
#include "timer.h"
#include "cmsis_os2.h"
#include "config/telemetry/telemetry_cfg_user.h"

/** @brief Beacon internal error codes reported to EXEH */
void telemetry_load_config(void);

typedef enum
{
    EXEH_TLM_CANNOT_SPAWN_TASK,
} exeh_tlm_error_codes_t;

/** @typedef runtime_context_t
 *  @brief Runtime context information for the telemetry service
 *
*/
typedef struct
{
    osThreadId_t os_task_hnd;                               /**< OS task handle */
    timer_handle_t tlm_timer;                               /**< periodic collection timer handle */
    timer_handle_t reload_config_timer;                     /**< timer used to trigger reloading of NVM config while in stop mode */
    telemetry_cfg_t gen_cfg;                                /**< telemetry configuration loaded from NVM */
    telemetry_preset_cfg_t preset_cfg;                      /**< telemetry preset configuration loaded from NVM */
    uint8_t active_preset_id;                               /**< currently used preset id for the telemetry configuration */
    uint8_t tlm_msg_buffer[TLM_BUF_SIZE];                   /**< runtime telemetry message buffer used to frame messages before forwarding them to the data sink */
    uint8_t tlm_msg_encode_buffer[TLM_ENCODE_BUF_SIZE];     /**< runtime telemetry message buffer used to encode frames before pushing them to the data queue */
    uint8_t rolling_cntr;                                   /**< telemetry frames rolling counter */
    uint16_t tlm_message_acq_counters[TELEMETRY_MAX_CONFIGURABLE_ENTRIES];   /**< acquisition counters for the individual messages */
} tlm_runtime_context_t;

extern tlm_runtime_context_t tlm_rt_context;

// USER_CODE_END::@main@

// Entry/Exit functions
void telemetry_sm_on_entry_Init(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_sm_on_entry_Started(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_sm_on_exit_Started(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_sm_on_entry_Stopped(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

// Guard condition functions
bool telemetry_sm_guard_can_start_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool telemetry_sm_guard_can_stop_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool telemetry_sm_guard_periodic_timer_elapsed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);

// Action handlers
void telemetry_sm_action_prepare_tlm_collection(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_sm_action_reload_config(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_sm_action_collect_telemetry(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TELEMETRY_SM_CONFIG_USER_H
