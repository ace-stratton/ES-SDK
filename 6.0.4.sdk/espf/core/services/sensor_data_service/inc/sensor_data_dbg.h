/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __SENSOR_DATA_DBG_H__
#define __SENSOR_DATA_DBG_H__

/**
 * @addtogroup sds
 * @{
 *
 * @file     sensor_data_dbg.h
 * @brief    Sensor data debug header. Contains tracing facilities
 *
 * @}
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "trace.h"

/** @brief Debug message head */
#define SDS_DBG_HEAD "[SDS_DBG]"

#if defined(DEBUG_TRACE_SDS_ENABLED)
#define SDS_TRACE_INFO(msg, ...)       ES_TRACE_INFO(msg OPT_VA_ARGS(__VA_ARGS__))
#define SDS_TRACE_DBG(msg, ...)        ES_TRACE_DEBUG(msg OPT_VA_ARGS(__VA_ARGS__))
#else
#define SDS_TRACE_INFO(msg, ...)
#define SDS_TRACE_DBG(msg, ...)
#endif

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SENSOR_DATA_DBG_H__
