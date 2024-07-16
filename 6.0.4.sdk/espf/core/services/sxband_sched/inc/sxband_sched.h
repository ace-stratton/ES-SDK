/*
 * Copyright (c) 2022-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __SXBAND_SCHED_H__
#define __SXBAND_SCHED_H__

/**
 * @addtogroup Services
 * @{
 *
* @defgroup service_sxband_sched SXBand Command Scheduler
 * @{
 *
 * The SXBand command scheduler is responsible for:
 *     - Managing the sequential execution of a series of SXBand commands uploaded to OBC as a file.
 *     - Storing the result of commands execution for later inspection.
 *
 * @file sxband_sched.h
 *
 * @brief SXBand Scheduler service public interface
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

/**
 * @brief SXBand scheduler operation status values
 */
typedef enum
{
	SXBAND_SCHED_STATUS_OK = 0U,
	SXBAND_SCHED_STATUS_FAILED,
	SXBAND_SCHED_STATUS_INTERRUPTED,
	SXBAND_SCHED_STATUS_IN_PROGRESS,
	SXBAND_SCHED_STATUS_MAX
} sxband_sched_status_t;

/** @brief Status notification callback type called by the sxband scheduler to inform about the outcome of
 *         sequence execution
 *  @param[in] status overall status of the sequence execution
 *  @param[in] p_summary_fname name of the file containing a detailed summary of the execution
 */
typedef void (*sxband_sched_notif_t)(const sxband_sched_status_t status, const char * const p_summary_fname);

/** @brief Initializes the SXBand scheduling service and prepares it for operation. */
void sxband_sched_init(void);

/** @brief Deinitializes the SXBand scheduling service */
void sxband_sched_deinit(void);

/** @brief Activates the scheduler OS task and prepares it for operation */
void sxband_sched_start(void);

/**
 * @brief Triggers the immediate execution of a commands sequence from a file
 *
 * @param[in] p_fname a pointer to the file name where the list of commands is stored
 * @param[in] fname_size size of the data pointed to by the @ref p_fname parameter
 * @param[in] p_sched_notif user-provided callback function to notify when the sequence execution is over;
 *            could be NULL to disable notifications
 * @return Indicates whether the trigger request is accepted or not
 */
sxband_sched_status_t sxband_sched_start_file_seq(const char * const p_fname, const uint8_t fname_size, sxband_sched_notif_t p_sched_notif);

/**
 * @brief The operation stops execution of the current command sequence (if active).
 */
void sxband_sched_stop_file_seq(void);

/**
 * @brief Reports whether a command sequence is being executed at the moment.
 * @return true - command sequence is in progress, false - otherwise
 */
bool sxband_sched_is_file_seq_active(void);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef __SXBAND_SCHED_H__
