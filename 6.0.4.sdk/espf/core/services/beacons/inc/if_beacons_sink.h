/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/** @addtogroup service_beacons
  * @{
  * @file if_beacons_sink.h
  *
  * @brief Beacons sink public interface
  *
  * The interface is intended to be implemented by beacon sink adapters who take care of beacon data processing.
  * The beacon service uses that interface to feed beacon data to the sink but it remains ignorant of what happens to the
  * data in the end. It is the responsibility of the adapter to handle how the data is actually processed.
  *
  * @}
  */

#ifndef __IF_BEACONS_SINK_H__
#define __IF_BEACONS_SINK_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

/** @brief Sink adapter standard commands enumeration */
typedef enum
{
	BEACONS_SINK_ADAPTER_CMD_INIT,
	BEACONS_SINK_ADAPTER_CMD_START,
	BEACONS_SINK_ADAPTER_CMD_STOP,
	BEACONS_SINK_ADAPTER_CMD_MAX,
} beacons_sink_adapter_cmd_t;

/** @brief Public control interface which shall be implemented by each beacons sink adapter */
typedef void (*p_beacons_sink_adapter_cmd)(const beacons_sink_adapter_cmd_t cmd);

/** @brief Public data send interface which shall be implemented by each beacons sink adapter
 *
 *	@param data pointer to the data buffer to send
 *	@param size	size of the data to send
 *	@param p_id a user-provided buffer where to store send id in case of asynchronous confirmation
 *
 *	@return send confirmation status (if false, then confirmation will be sent later via a callback)
*/
typedef bool (*p_beacons_sink_adapter_send)(uint8_t * const data, const uint8_t size, uint8_t * const p_id);

/** @brief A callback used by the sink adapters implementation to confirm beacon transmission status
 *
 *  @param id internally generated id by the sink adapter used to match beacon frame status
 *  @param is_successful_send indicates whether the sending of the beacon with the given id is successful or not
*/
void beacons_confirm_sink_send(const uint8_t id, const bool is_successful_send);

/** @brief Beacons sink interface structure */
typedef struct
{
	p_beacons_sink_adapter_cmd cmd;
	p_beacons_sink_adapter_send send;
} beacons_sink_if_t;

/** @brief Singleton beacons sink interface pointer */
extern const beacons_sink_if_t beacons_sink;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __IF_BEACONS_SINK_H__
/**
 * @}
 * @}
 *
 */