/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _IF_TELEMETRY_SINK_H_
#define _IF_TELEMETRY_SINK_H_

/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_data_sink.h
 *
 * @brief Telemetry data-sink interface
 *
 * This interface must be provided by all telemetry data sinks.
 *
 * @}
*/


#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus

#include "es_cdef.h"

/** @brief Sink adapter standard commands enumeration */
typedef enum
{
	TELEMETRY_SINK_ADAPTER_CMD_INIT,
	TELEMETRY_SINK_ADAPTER_CMD_START,
	TELEMETRY_SINK_ADAPTER_CMD_STOP,
	TELEMETRY_SINK_ADAPTER_CMD_MAX,
} telemetry_sink_adapter_cmd_t;

/** @brief Public control interface which shall be implemented by each telemetry sink adapter
 *
 *  @param cmd Specific telemetry sink adapter command to execute
 *
*/
typedef void (*p_telemetry_sink_adapter_cmd)(const telemetry_sink_adapter_cmd_t cmd);

/** @brief Telemetry sink interface structure */
typedef struct
{
	p_telemetry_sink_adapter_cmd cmd;
} telemetry_sink_if_t;

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif /* _IF_TELEMETRY_SINK_H_ */
