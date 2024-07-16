/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_fdir.c
 * @brief    Cubeadcs Gen2 dedicated FDIR
 *
 * @}
 */

#include "es_cdef.h"
#include "assertions.h"
#include "cmsis_os2.h"
#include "es_exeh.h"

#include "cubeadcs_gen2_fdir.h"

#include <string.h>

/** @brief CubeADCS Gen2 fdir errors access lock */
static osMutexId_t cubeadcs_gen2_fdir_err_lock;
/** @brief CubeADCS Gen2 fdir lock attributes */
static const osMutexAttr_t cubeadcs_gen2_fdir_err_lock_attr = {
        "cubeadcs_gen2_fdir_err_lock_mutex",
        osMutexRecursive | osMutexPrioInherit,
        NULL,
        0U
};

STATIC bool cubeadcs_gen2_fdir_generic_handler_critical(void);
STATIC bool cubeadcs_gen2_fdir_generic_handler_non_critical(void);
STATIC bool fs_cubeadcs_gen2_fdir_lock_err(void);
STATIC bool fs_cubeadcs_gen2_fdir_unlock_err(void);

STATIC cubeadcs_gen2_fdir_failure_ctx_t fdir_ctx = {
        .unrecoverable_errors = CUBEADCS_GEN2_FDIR_ERRORS_NO_ERRORS,
        .fdir_handlers =
        {
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_ADCS_CONFIG_VALIDATION_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_non_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_NODE_SETUP_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_non_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_NODE_JUMP_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_MAG_DEPLOY_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_non_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_FAILURE,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_non_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_NODE_FAILURE,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_CONFIG_PERSIST_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_non_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_WARNING,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_non_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_PORT_VALIDATION_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_non_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_AUTO_DISCOVERY_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_CRITICAL,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_GYRO_VOLTAGE_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_GYRO_CRITICAL,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                },
                {
                        .failure_event = CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_ERROR,
                        .failure_event_handler = cubeadcs_gen2_fdir_generic_handler_critical,
                        .failure_event_handler_max_exec = CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC,
                        .failure_event_handler_exec = 0,
                        .failure_event_handler_exec_op_res = {false},
                        .failure_event_fdir_error = CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED,
                }
        }
};

void cubeadcs_gen2_fdir_init_os(void)
{
    cubeadcs_gen2_fdir_err_lock = osMutexNew(&cubeadcs_gen2_fdir_err_lock_attr);

    if ( NULL == cubeadcs_gen2_fdir_err_lock )
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR);
    }
}

bool cubeadcs_gen2_fdir_exec(void)
{
    bool op_res = false;

    cubeadcs_gen2_events_cnts_t events;

    if ( (true == cubeadcs_gen2_events_get_events_stats(&events)) &&
            (true == fs_cubeadcs_gen2_fdir_lock_err()))
    {
        // Clear the last events and only then work on the local copy
        if ( true == cubeadcs_gen2_events_clear_event_stats(CUBEADCS_GEN2_EVENTS_CLEAR_LAST_READ_EVENTS) )
        {
            for (uint8_t ev = 0; ev < CUBEADCS_GEN2_EVENTS_MAX; ev++)
            {
                if ( (0 != events.last_read_events[ev]) &&
                        (fdir_ctx.fdir_handlers[ev].failure_event_handler_exec < fdir_ctx.fdir_handlers[ev].failure_event_handler_max_exec) )
                {
                    if (true == fdir_ctx.fdir_handlers[ev].failure_event_handler())
                    {
                        fdir_ctx.fdir_handlers[ev].failure_event_handler_exec_op_res[fdir_ctx.fdir_handlers[ev].failure_event_handler_exec] = true;
                    }
                    else
                    {
                        // If error was not handled or we failed to handle it, update the unrecoverable errors
                        fdir_ctx.unrecoverable_errors |= fdir_ctx.fdir_handlers[ev].failure_event_fdir_error;
                    }

                    fdir_ctx.fdir_handlers[ev].failure_event_handler_exec++;
                }

            }

            op_res = true;
        }

        (void)fs_cubeadcs_gen2_fdir_unlock_err();
    }

    return op_res;
}

bool cubeadcs_gen2_fdir_get_errors(cubeadcs_gen2_fdir_errors_t * const p_dst)
{
    CRIT_ASSERT(NULL != p_dst);

    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_fdir_lock_err() )
    {
        *p_dst = fdir_ctx.unrecoverable_errors;

        (void)fs_cubeadcs_gen2_fdir_unlock_err();

        op_res = true;
    }

    return op_res;
}

bool cubeadcs_gen2_fdir_clear_errors(void)
{
    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_fdir_lock_err() )
    {
        fdir_ctx.unrecoverable_errors = CUBEADCS_GEN2_FDIR_ERRORS_NO_ERRORS;

        (void)fs_cubeadcs_gen2_fdir_unlock_err();

        op_res = true;
    }

    return op_res;
}

bool cubeadcs_gen2_fdir_get_fdir_ctx(cubeadcs_gen2_fdir_failure_ctx_t * const p_dst)
{
    CRIT_ASSERT(NULL != p_dst);

    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_fdir_lock_err() )
    {
        memcpy(p_dst, (void *)&fdir_ctx, sizeof(fdir_ctx));

        (void)fs_cubeadcs_gen2_fdir_unlock_err();

        op_res = true;
    }

    return op_res;
}

bool cubeadcs_gen2_fdir_clear_fdir_ctx_handlers(void)
{
    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_fdir_lock_err() )
    {
        for (uint8_t ev = 0; ev < CUBEADCS_GEN2_EVENTS_MAX; ev++)
        {
            fdir_ctx.fdir_handlers[ev].failure_event_handler_exec = 0;

            for (uint8_t ev_h = 0; ev < fdir_ctx.fdir_handlers[ev].failure_event_handler_max_exec; ev_h++)
            {
                fdir_ctx.fdir_handlers[ev].failure_event_handler_exec_op_res[ev_h] = false;
            }
        }

        (void)fs_cubeadcs_gen2_fdir_unlock_err();

        op_res = true;
    }

    return op_res;
}

/** @brief Generic fdir handler for critical errors
 *
 *  @retval true - On successful recovery from the error
 *  @retval false - On failure to recover from the error
 */
STATIC bool cubeadcs_gen2_fdir_generic_handler_critical(void)
{
    bool op_res = false;

    return op_res;
}

/** @brief Generic fdir handler for non-critical errors
 *
 *  @retval true - On successful recovery from the error
 *  @retval false - On failure to recover from the error
 */
STATIC bool cubeadcs_gen2_fdir_generic_handler_non_critical(void)
{
    bool op_res = false;

    return op_res;
}

/** @brief Lock access to errors stash
 *
 *  @note Mutex lock is set to wait forever
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_fdir_lock_err(void)
{
    bool op_res = true;

    if ( osOK != osMutexAcquire(cubeadcs_gen2_fdir_err_lock, osWaitForever) )
    {
        op_res = false;

        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    return op_res;
}

/** @brief Unlock access to errors stash
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_fdir_unlock_err(void)
{
    bool op_res = true;

    if ( osOK != osMutexRelease(cubeadcs_gen2_fdir_err_lock) )
    {
        op_res = false;

        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    return op_res;
}

