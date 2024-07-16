/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup cubeadcs_gen2_events
 * @{
 *
 * @file     cubeadcs_gen2_events.c
 * @brief    Cubeadcs Gen2 Events handler
 *
 * @}
 */

#include "es_cdef.h"
#include "cmsis_os2.h"
#include "es_exeh.h"
#include "cubeadcs_gen2_events.h"
#include "cubeadcs_gen2_gw.h"
#include "cubeObc_cubeComputer.h"
#include "cubeadcs_gen2_events.h"
#include "cubeadcs_gen2_transfer.h"

#include "SdMngr.h"
#include "assertions.h"

#include <stdlib.h>

/** @brief Events handling logic context */
static cubeadcs_gen2_events_ctx_t events_ctx = {0};
/** @brief Events file name */
const char events_f_name[16] = "LAST_EVENTS.bin";
/** @brief CubeADCS Gen2 events cache lock */
static osMutexId_t cubeadcs_gen2_ev_lock;
/** @brief CubeADCS Gen2 events mutex attributes */
static const osMutexAttr_t cubeadcs_gen2_ev_lock_attr = {
        "cubeadcs_gen2_ev_lock_mutex",
        osMutexRecursive | osMutexPrioInherit,
        NULL,
        0U
};

STATIC bool fs_cubeadcs_gen2_events_parse_events_log(const char * const p_f_name,  const uint32_t ev_cnt);
STATIC void fs_cubeadcs_gen2_events_update_events_cache(const cubeadcs_gen2_event_t * const p_ev);
STATIC bool fs_cubeadcs_gen2_events_lock_ev(void);
STATIC bool fs_cubeadcs_gen2_events_unlock_ev(void);
STATIC bool fs_cubeadcs_gen2_events_get_marker_start(void);
STATIC bool fs_cubeadcs_gen2_events_get_marker_poll(void);
STATIC bool fs_cubeadcs_gen2_events_dwn_new_crit_events_start(void);
STATIC bool fs_cubeadcs_gen2_events_dwn_new_crit_events_poll(void);

void cubeadcs_gen2_events_init_os(void)
{
    cubeadcs_gen2_ev_lock = osMutexNew(&cubeadcs_gen2_ev_lock_attr);

    if ( NULL == cubeadcs_gen2_ev_lock )
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR);
    }
}

bool cubeadcs_gen2_events_get_marker(void)
{
    bool op_res = false;

    static cubeadcs_gen2_event_dwn_progress_t evt_dwn_progress = CUBEADCS_GEN2_EVENT_DWN_IDLE;

    if ( true == fs_cubeadcs_gen2_events_lock_ev() )
    {
        switch (evt_dwn_progress)
        {
            case CUBEADCS_GEN2_EVENT_DWN_IDLE:
                {
                    if (true == fs_cubeadcs_gen2_events_get_marker_start())
                    {
                        evt_dwn_progress = CUBEADCS_GEN2_EVENT_DWN_STARTED;
                    }
                }
                break;

            case CUBEADCS_GEN2_EVENT_DWN_STARTED:
                {
                    cubeadcs_gen2_transfer_evt_status_t get_marker_status;
                    const ErrorCode                     err = cubeadcs_gen2_transfer_evt_status(&get_marker_status);

                    if (CUBEOBC_ERROR_OK == err)
                    {
                        if (CUBEOBC_ERROR_OK == get_marker_status.err_code)
                        {
                            evt_dwn_progress = CUBEADCS_GEN2_EVENT_DWN_POLL;
                        }
                        else
                        {
                            evt_dwn_progress = CUBEADCS_GEN2_EVENT_DWN_IDLE;
                        }
                    }
                }
                break;

            case CUBEADCS_GEN2_EVENT_DWN_POLL:
                {
                    if (true == fs_cubeadcs_gen2_events_get_marker_poll())
                    {
                        evt_dwn_progress = CUBEADCS_GEN2_EVENT_DWN_FINISHED;
                    }
                    else
                    {
                        // Retry the event log download sequence
                        evt_dwn_progress = CUBEADCS_GEN2_EVENT_DWN_IDLE;
                    }
                }
                break;

            case CUBEADCS_GEN2_EVENT_DWN_FINISHED:
                {
                    op_res = true;

                    // Back to vanilla state
                    evt_dwn_progress = CUBEADCS_GEN2_EVENT_DWN_IDLE;
                }
                break;

            default:
                break;
        }

        (void)fs_cubeadcs_gen2_events_unlock_ev();
    }

    return op_res;
}

bool cubeadcs_gen2_events_check_for_new_crit_events(bool * const is_new_crit_events)
{
    CRIT_ASSERT(NULL != is_new_crit_events);

    bool op_res = false;

    TctlmCubeComputerCommon3_EventLogStatus event_log_status;

    if ( (true == fs_cubeadcs_gen2_events_lock_ev()) &&
         (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerCommon3_getEventLogStatusRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &event_log_status, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)))
    {
        // It is possible that the events log gets deleted by the user ...
        if ( (events_ctx.last_major_events_num != event_log_status.numberOfMajorWarningEvents) ||
             (events_ctx.last_crit_events_num != event_log_status.numberOfCriticalEvents)   )
        {
            events_ctx.events_to_download = abs((event_log_status.numberOfMajorWarningEvents - events_ctx.last_major_events_num) +
                                                (event_log_status.numberOfCriticalEvents - events_ctx.last_crit_events_num));

            TODO("TEST how much time it takes to download events and modify the limit accordingly")
            if ( events_ctx.events_to_download > CUBEADCS_GEN2_EVENTS_MAX_EVENTS_TO_DOWNLOAD )
            {
                events_ctx.events_to_download = CUBEADCS_GEN2_EVENTS_MAX_EVENTS_TO_DOWNLOAD;
            }

            events_ctx.last_major_events_num = event_log_status.numberOfMajorWarningEvents;
            events_ctx.last_crit_events_num = event_log_status.numberOfCriticalEvents;

            *is_new_crit_events = true;
        }
        else
        {
            *is_new_crit_events = false;
        }

        (void)fs_cubeadcs_gen2_events_unlock_ev();

        op_res = true;
    }

    return op_res;
}

bool cubeadcs_gen2_events_dwn_new_crit_events(bool * const p_is_crit_evt)
{
    CRIT_ASSERT(NULL != p_is_crit_evt);

    bool op_res = false;

    static bool is_new_crit_event = false;

    static cubeadcs_gen2_event_crit_dwn_states_t dwn_state = CUBEADCS_GEN2_EVENT_CRIT_IDLE;

    if ( true == fs_cubeadcs_gen2_events_lock_ev() )
    {
        switch (dwn_state)
        {
        case CUBEADCS_GEN2_EVENT_CRIT_IDLE:
            if ( true == cubeadcs_gen2_events_check_for_new_crit_events(&is_new_crit_event))
            {
                dwn_state = CUBEADCS_GEN2_EVENT_CRIT_CHECK;
            }
            break;
        case CUBEADCS_GEN2_EVENT_CRIT_CHECK:
            if ( true == is_new_crit_event )
            {
                if ( true == fs_cubeadcs_gen2_events_dwn_new_crit_events_start() )
                {
                    dwn_state = CUBEADCS_GEN2_EVENT_CRIT_START_DWN;
                }
            }
            else
            {
                dwn_state = CUBEADCS_GEN2_EVENT_CRIT_FINISHED;
            }
            break;
        case CUBEADCS_GEN2_EVENT_CRIT_START_DWN:
            if ( true == fs_cubeadcs_gen2_events_dwn_new_crit_events_poll() )
            {
                dwn_state = CUBEADCS_GEN2_EVENT_CRIT_FINISHED;
            }
            break;
        case CUBEADCS_GEN2_EVENT_CRIT_FINISHED:

            *p_is_crit_evt = is_new_crit_event;

            op_res = true;

            // Return to vanilla state
            dwn_state = CUBEADCS_GEN2_EVENT_CRIT_IDLE;
            is_new_crit_event = false;

            break;

        default:
            break;
        }

        (void)fs_cubeadcs_gen2_events_unlock_ev();
    }

    return op_res;
}

bool cubeadcs_gen2_events_get_events_stats(cubeadcs_gen2_events_cnts_t * const p_ev_dst)
{
    CRIT_ASSERT(NULL != p_ev_dst);

    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_events_lock_ev())
    {
        (void)memcpy(p_ev_dst, &events_ctx.read_events, sizeof(cubeadcs_gen2_events_cnts_t));

        (void)fs_cubeadcs_gen2_events_unlock_ev();

        op_res = true;
    }

    return op_res;
}

bool cubeadcs_gen2_events_clear_event_stats(bool clr_all)
{
    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_events_lock_ev())
    {
        if ( true == clr_all)
        {
            (void)memset((void *)&events_ctx.read_events, 0U, sizeof(events_ctx.read_events) );
        }
        else
        {
            (void)memset((void *)&events_ctx.read_events.last_read_events, 0U, sizeof(events_ctx.read_events.last_read_events) );
        }

        (void)fs_cubeadcs_gen2_events_unlock_ev();

        op_res = true;
    }

    return op_res;
}

/** @brief Parse the events log stored in the provided file name updating a file scoped cache and updating the last read event
 * 
 *  @param[in] const char * const p_events_f_name - The name of the file containing the events log
 * 
 *  @retval true     - on success
 *  @retval false    - on failure
 * 
 */
STATIC bool fs_cubeadcs_gen2_events_parse_events_log(const char * const p_f_name, const uint32_t ev_cnt)
{
    CRIT_ASSERT(NULL != p_f_name);

    FIL f_handle;

    bool op_res = false;

    cubeadcs_gen2_event_t event;
    UINT read_bytes;

    if ( (FR_OK == SdMngr_f_open(&f_handle, p_f_name, FA_READ)) &&
         (FR_OK == SdMngr_f_lseek(&f_handle, 0)) &&
         (true == fs_cubeadcs_gen2_events_lock_ev()))
    {
        for (uint32_t ev = 0; ev < ev_cnt; )
        {
            if ( (FR_OK == SdMngr_f_read(&f_handle, (void *)&event, sizeof(cubeadcs_gen2_event_t), &read_bytes)) &&
                 (read_bytes == sizeof(cubeadcs_gen2_event_t)))
            {
                fs_cubeadcs_gen2_events_update_events_cache(&event);
            }
            else
            {
                // We want to get all events and FDIR on them, otherwise just break and try again
                break;
            }

            if ( ++ev == ev_cnt )
            {
                events_ctx.last_read_counter = event.counter;

                for (uint8_t ev_indx = 0; ev_indx < CUBEADCS_GEN2_EVENTS_MAX; ev_indx++)
                {
                    events_ctx.read_events.all_read_events[ev_indx] += events_ctx.read_events.last_read_events[ev_indx];
                }

                op_res = true;
            }
        }

        (void)SdMngr_f_close(&f_handle);
        (void)fs_cubeadcs_gen2_events_unlock_ev();
    }

    return op_res;
}

/** @brief Update the events cache with the provided event
 *
 *  @note Context lock is NOT performed within the function
 *
 *  @param[in] const cubeadcs_gen2_event_t * const p_ev - the event
 */
STATIC void fs_cubeadcs_gen2_events_update_events_cache(const cubeadcs_gen2_event_t * const p_ev)
{
    CRIT_ASSERT(NULL != p_ev);

    if ( (CUBEADCS_GEN2_EVENT_CLASS_CRITICAL == p_ev->identifier.event_class) ||
         (CUBEADCS_GEN2_EVENT_CLASS_MAJOR == p_ev->identifier.event_class))
    {
        switch (p_ev->identifier.event_type)
        {
        case CUBEADCS_GEN2_EVENTS_ADCS_CONFIG_VALIDATION_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_ADCS_CONFIG_VALIDATION_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_NODE_SETUP_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_NODE_SETUP_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_NODE_JUMP_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_NODE_JUMP_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_MAG_DEPLOY_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_MAG_DEPLOY_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_FAILURE_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_FAILURE] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_NODE_FAILURE_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_NODE_FAILURE] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_CONFIG_PERSIST_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_CONFIG_PERSIST_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_WARNING_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_WARNING] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_PORT_VALIDATION_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_PORT_VALIDATION_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_AUTO_DISCOVERY_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_AUTO_DISCOVERY_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_CRITICAL_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_CRITICAL] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_GYRO_VOLTAGE_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_GYRO_VOLTAGE_ERROR] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_GYRO_CRITICAL_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_GYRO_CRITICAL] += 1;
            break;
        case CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_ERROR_ID:
            events_ctx.read_events.last_read_events[CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_ERROR] += 1;
            break;
        default:
            break;
        }
    }
}

/** @brief Lock events caches
 *
 *  @note Mutex lock is set to wait forever
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_events_lock_ev(void)
{
    bool op_res = true;

    if ( osOK != osMutexAcquire(cubeadcs_gen2_ev_lock, osWaitForever) )
    {
        op_res = false;

        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    return op_res;
}

/** @brief Unlock events cache
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_events_unlock_ev(void)
{
    bool op_res = true;

    if ( osOK != osMutexRelease(cubeadcs_gen2_ev_lock) )
    {
        op_res = false;

        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    return op_res;
}

/** @brief Start event download in the context of getting the initial marker
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_events_get_marker_start(void)
{
    bool op_res = false;

    TctlmCubeComputerCommon3_EventLogFilterTransferSetup filter;

    // First include all classes and all sources and then modify to include only the last entry
    (void)memset((uint8_t *)&filter, 0xFF, sizeof(filter));
    filter.filterType = TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_LAST_X;
    filter.numEntries = 1;

    if (CUBEOBC_ERROR_OK == cubeadcs_gen2_transfer_evt((const char *)&events_f_name, &filter))
    {
        op_res = true;
    }

    return op_res;
}

/** @brief Poll event download in the context of getting the initial marker
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_events_get_marker_poll(void)
{
    bool      op_res = false;
    ErrorCode err_code;

    cubeadcs_gen2_transfer_evt_status_t event_dwn_status;

    err_code = cubeadcs_gen2_transfer_evt_status(&event_dwn_status);

    if ((CUBEOBC_ERROR_OK == err_code) &&
        (CUBEOBC_ERROR_OK == event_dwn_status.err_code) &&
        (true == fs_cubeadcs_gen2_events_parse_events_log((const char *const)&events_f_name, 1)) &&
        (true == cubeadcs_gen2_events_clear_event_stats(CUBEADCS_GEN2_EVENTS_CLEAR_ALL_EVENTS)) &&
        (true == fs_cubeadcs_gen2_events_lock_ev()))
    {
        events_ctx.last_major_events_num = event_dwn_status.status.numberOfMajorWarningEvents;
        events_ctx.last_crit_events_num  = event_dwn_status.status.numberOfCriticalEvents;

        (void)fs_cubeadcs_gen2_events_unlock_ev();

        op_res = true;
    }

    return op_res;
}

/** @brief Start event download in the context of getting new critical events
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_events_dwn_new_crit_events_start(void)
{
    bool op_res = false;

    TctlmCubeComputerCommon3_EventLogFilterTransferSetup filter;

    if (true == fs_cubeadcs_gen2_events_lock_ev())
    {
        (void)memset((uint8_t *)&filter, 0xFF, sizeof(filter)); // Include all classes and all sources

        // Get only the last entries of classes critical and major
        filter.filterType               = TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_LAST_X;
        filter.numEntries               = events_ctx.events_to_download;
        filter.includeClassInfo         = false;
        filter.includeClassMinorWarning = false;

        if (CUBEOBC_ERROR_OK == cubeadcs_gen2_transfer_evt((const char *)&events_f_name, &filter))
        {
            op_res = true;
        }

        (void)fs_cubeadcs_gen2_events_unlock_ev();
    }

    return op_res;
}

/** @brief Poll event download in the context of getting the new critical events
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_events_dwn_new_crit_events_poll(void)
{
    bool      op_res = false;
    ErrorCode err_code;

    cubeadcs_gen2_transfer_evt_status_t event_dwn_status;

    err_code = cubeadcs_gen2_transfer_evt_status(&event_dwn_status);

    if ((CUBEOBC_ERROR_OK == err_code) &&
        (true == fs_cubeadcs_gen2_events_lock_ev()) &&
        (true == fs_cubeadcs_gen2_events_parse_events_log((const char *const)&events_f_name, events_ctx.events_to_download)))
    {
        op_res = true;

        (void)fs_cubeadcs_gen2_events_unlock_ev();
    }

    return op_res;
}
