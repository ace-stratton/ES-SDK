/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _TELEMETRY_FILE_SINK_H_
#define _TELEMETRY_FILE_SINK_H_

/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_file_sink.h
 *
 * @brief A description of the module’s purpose.
 *
 * @}
 *
*/

#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus

#include "es_cdef.h"
#include "if_telemetry_sink.h"

/** @brief The function sends a stop event to the Telemetry HSM and waits a specified number of milliseconds before
 *         going back to Started state automatically.
 *
 *  @param[in] ms_before_resume number of milliseconds before switching restoring telemetry operation;
 *             if 0: automatic restoration will be disabled
 */
void telemetry_file_sink_pause(const uint32_t ms_before_resume);

/** @brief Synchronized version of the clean operation which can be called outside the telemetry HSM safely */
void telemetry_file_sink_syncd_clean(void);

/** @brief Unsynchornized version of the clean operation which can be called internally in the HSM only */
void telemetry_file_sink_clean(void);

/** @brief Used externally to inform about configuration changes which require a restart of the running
 *         telemetry.
 */
void telemetry_file_sink_config_update(void);

extern telemetry_sink_if_t telemetry_file_sink_if;

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif /* _TELEMETRY_FILE_SINK_H_ */
