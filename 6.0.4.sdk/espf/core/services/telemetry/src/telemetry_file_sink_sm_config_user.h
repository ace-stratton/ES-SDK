#ifndef TELEMETRY_FILE_SINK_SM_CONFIG_USER_H
#define TELEMETRY_FILE_SINK_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"
#include "stdatomic.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
#include "nvm/inc/nvm.h"
#include "config/telemetry/telemetry_cfg_user.h"
#include "timer.h"

typedef enum
{
    EXEH_TLM_FS_CANNOT_SPAWN_TASK,
    EXEH_TLM_FS_FILE_ERROR,
} exeh_tlm_fs_error_codes_t;

/** @brief Operation types which require synchronization with the main file sink task.
 *         The enumeration values serve as indices in tlm_file_sink_rt_ctx_t::main_task_sync_op_flags array.
 */
typedef enum
{
    TLM_FILE_SINK_OP_PAUSE = 0,
    TLM_FILE_SINK_OP_CFG_UPDATE = 1,
    TLM_FILE_SINK_OP_CLEAN = 2,
    TLM_FILE_SINK_OP_MAX = 3
} tlm_file_sink_op_t;

/**
 * @brief Defines the shared data used by the SM implementation and the main file sink
 * implementation.
 */
typedef struct
{
    osThreadId_t os_task_hnd;                               /**< OS task handle */
    telemetry_file_cfg_t cfg;                               /**< NVM configuration of the file sink */
    telemetry_cfg_t gen_cfg;                                /**< telemetry configuration loaded from NVM */
    tlm_file_cfg_type_t prev_cfg_type;                      /**< last used configuration type */
    uint16_t current_idx;                                   /**< current file index to write to */
    uint32_t max_file_size_bytes;                           /**< max individual telemetry file size in bytes */
    char current_file_name[TLM_FILE_SINK_MAX_FN_SIZE];      /**< current file name in use for next write */
    char wildcard[sizeof(TLM_FILE_SINK_EXT) + 2U];          /**< contains the telemetry files wildcard used to enumerate the files */
    uint8_t tlm_msg_buffer[TLM_BUF_SIZE];                   /**< runtime telemetry message buffer used to pop messages from queue temporarily */
    timer_handle_t auto_resume_timer;                       /**< automatic resume timer used to transition between Stopped and Wait_Storage states */
    uint32_t auto_resume_period_ms;                         /**< telemetry operation resume timer period */
    atomic_bool main_task_sync_op_flags[TLM_FILE_SINK_OP_MAX];  /**< flags used to synchronize external operations to main task */
} tlm_file_sink_rt_ctx_t;

/**
 * @brief  Shared data context used to sync the behavior of the SM implementation and the main file sink
 * implementation.
 *
 */
extern tlm_file_sink_rt_ctx_t tlm_filesink_rt_context;

/** @brief Responsible to clean-up all existing telemetry files on the storage.
 *
 */
void telemetry_file_sink_clean(void);

// USER_CODE_END::@main@

// Entry/Exit functions
void telemetry_file_sink_sm_on_entry_Init(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_file_sink_sm_on_entry_Stopped(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

// Guard condition functions
bool telemetry_file_sink_sm_guard_can_start_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool telemetry_file_sink_sm_guard_is_storage_available(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool telemetry_file_sink_sm_guard_can_stop_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool telemetry_file_sink_sm_guard_is_storage_blocked(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool telemetry_file_sink_sm_guard_is_auto_resume_timer_elapsed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);

// Action handlers
void telemetry_file_sink_sm_action_reload_config(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_file_sink_sm_action_perform_file_scan(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_file_sink_sm_action_store_telemetry(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void telemetry_file_sink_sm_action_clean_and_reload_cfg(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TELEMETRY_FILE_SINK_SM_CONFIG_USER_H