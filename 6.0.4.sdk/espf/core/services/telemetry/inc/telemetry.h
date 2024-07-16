/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup service_tlm Telemetry
 * @{
 *
 * The telemetry service takes responsibility of:
 *     - periodic collection of data directly from the DataCache;
 *     - assembly of telemetry frames and forwarding to a data sink adapter
 *       (e.g. sending over to a serial connection or storage to a file, etc.);
 *
 * @file telemetry.h
 *
 * @brief Telemetry service public interface
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

/** @brief Initializes the telemetry service and prepares it for operation. */
void telemetry_init(void);

/** @brief Starts telemetry collection */
void telemetry_start(void);

/** @brief Stops telemetry collection */
void telemetry_stop(void);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef __TELEMETRY_H__
