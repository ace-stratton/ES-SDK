#ifndef SXBAND_SCHED_REPORT_H
#define SXBAND_SCHED_REPORT_H

#include "sxband_cmd_iter_types.h"

/**
 * @addtogroup Services
 * @{
 *
 * @addtogroup service_sxband_sched SXBand Command Scheduler
 * @{
 *
 * SXBand command scheduler file reporting interface
 *
 * @file     sxband_sched_report.h
 * @brief    Definition of the SXBand scheduler reporting interface
 *
 * @}
 * @}
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "es_cdef.h"

typedef enum
{
	SXBAND_SCHED_CMD_STATUS_DEFAULT = 0,
	SXBAND_SCHED_CMD_STATUS_TIMEDOUT,
	SXBAND_SCHED_CMD_STATUS_NO_FILES,
	SXBAND_SCHED_CMD_STATUS_MAX
} sxband_sched_cmd_status_id;

/**
 * @brief Opens a command status report for writing
 *
 * @param[in] p_fname name of the report file to create
 */
void sxband_sched_report_open(const char * const p_fname);

/**
 * @brief Appends a new command status entry to the report
 *
 * @param[in] p_cmd a pointer to the command data
 * @param[in] cmd_user_status provides a specific user status to be reported explicitly
 */
void sxband_sched_report_append(const sxband_sched_cmd_t * const p_cmd, const sxband_sched_cmd_status_id cmd_user_status);

/**
 * @brief Appends free form text provided by the user.
 *
 * @param[in] p_text a pointer to the ASCII string to append to the file
 * @param[in] text_size size in bytes of the ASCII string pointed by @ref p_text
 */
void sxband_sched_report_append_free_text(const char * const p_text, const uint16_t text_size);

/**
 * @brief Closes the report
 */
void sxband_sched_report_close(void);

#ifdef __cplusplus
}
#endif

#endif // SXBAND_SCHED_REPORT_H
