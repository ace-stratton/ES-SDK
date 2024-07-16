/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_GEN2_FDIR_H
#define CUBEADCS_GEN2_FDIR_H

/**
 * @addtogroup cubeadcs_gen2_fdir
 * @{
 *
 * @file     cubeadcs_gen2_fdir.h
 * @brief    Cubeadcs Generation 2 FDIR header
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"
#include "cubeadcs_gen2_events.h"

/** @brief No errors */
#define CUBEADCS_GEN2_FDIR_ERRORS_NO_ERRORS (0U)
/** @brief Control authority compromised. Control cannot be achieved */
#define CUBEADCS_GEN2_FDIR_ERRORS_CONTROL_COMPROMISED (1U)
/** @brief FDIR errors mask */
typedef uint32_t cubeadcs_gen2_fdir_errors_t;

/** @brief Maximum number of executions for event handlers */
#define CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC (1)

/** @brief Function pointer type for the specific FDIR */
typedef bool (*p_fdir_handler_t)(void);

/** @brief Failure handler description */
typedef struct
{
    const cubeadcs_gen2_events_types_t failure_event; /** @brief The event linked to this handler  */
    const p_fdir_handler_t failure_event_handler; /** @brief The handler logic/state machine/etc.  */
    const uint8_t failure_event_handler_max_exec; /** @brief The maximum number of allowed executions of the handler logic  */
    uint8_t failure_event_handler_exec; /** @brief The current number (since last reset) of the executions of the handler logic  */
    bool failure_event_handler_exec_op_res[CUBEADCS_GEN2_FDIR_EVENT_HANDLER_MAX_EXEC]; /**@brief Execution results */
    const cubeadcs_gen2_fdir_errors_t failure_event_fdir_error; /**@brief One of the defined FDIR errors which is raised in case the FDIR handler failed */
} cubeadcs_gen2_fdir_failure_handler_t;

/** @brief The FDIR context */
typedef struct
{
    cubeadcs_gen2_fdir_errors_t unrecoverable_errors; /** @brief Errors mask of errors which the FDIR could not recover from */
    cubeadcs_gen2_fdir_failure_handler_t fdir_handlers[CUBEADCS_GEN2_EVENTS_MAX]; /** @brief Failure handler description and stats */

} cubeadcs_gen2_fdir_failure_ctx_t;

/** @brief Inititliase OS objects */
void cubeadcs_gen2_fdir_init_os(void);

/** @brief FDIR state machine
 *
 *  @note Execute the gen2 fdir logic
 *
 *  @retval true - On completed FDIR
 *  @retval false - On failure to complete/execute FDIR
 */
bool cubeadcs_gen2_fdir_exec(void);

/** @brief Get unhandled/unrecoverd errors
 *
 *  @note This function returns the errors which the FDIR logic could not handle or which it has no knowledge of how to handle. Treat these
 *  errors as critical to the control of the satellite!
 *
 *  @param[out] cubeadcs_gen2_fdir_errors * const p_dst - destination to copy the critical errors to
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
bool cubeadcs_gen2_fdir_get_errors(cubeadcs_gen2_fdir_errors_t * const p_dst);

/** @brief Clear the unhandled/uncrecovarable errors
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
bool cubeadcs_gen2_fdir_clear_errors(void);

/** @brief Read the full FDIR context
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
bool cubeadcs_gen2_fdir_get_fdir_ctx(cubeadcs_gen2_fdir_failure_ctx_t * const p_dst);

/** @brief Clear the FDIR handlers - counters and execution results
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
bool cubeadcs_gen2_fdir_clear_fdir_ctx_handlers(void);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_GEN2_FDIR_H */

/* ******************************************************************************************* */
