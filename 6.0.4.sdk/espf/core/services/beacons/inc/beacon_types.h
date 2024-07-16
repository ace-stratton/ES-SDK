/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
  * @addtogroup service_beacons
  * @{
  *
  * @file beacon_types.h
  *
  * @brief Beacons service types header
  * @}
  */

#ifndef __BEACON_TYPES_H__
#define __BEACON_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"
#include "config/beacons/beacons_cfg_user.h"

/** @brief Bit mask values used to update the @ref beacon_frame_hdr_t::flags field */
enum
{
	FRAME_HDR_FLAGS_INIT = 0x00,			/**< initialization value bit mask */
	FRAME_HDR_FLAGS_CONTINUATION = 0x01		/**< continuation bit mask */
};

/** @typedef beacon_frame_hdr_t
 *  @brief Beacon header definition
 */
typedef struct
{
	uint8_t rolling_cntr;	/**< beacon rolling counter used to detect gaps in transmitted beacons */
	uint8_t obc_opmode;		/**< current OBC operational mode at the moment of beacon sending */
	uint8_t flags;			/**< transmission data flags */
} PACKED beacon_frame_hdr_t;

/** @typedef beacon_msg_hdr_t
 *  @brief Beacon message header definition
 */
typedef struct
{
	uint16_t beacon_type;	/**< a unique identifier used to interpret the beacon message data field */
	uint8_t  beacon_data_status;	/**< status of the provided data, e.g. see @ref dc_data_status_t for details on value encoding */
	uint8_t  data_len;		/**< length in bytes of the beacon message data field */
} PACKED beacon_msg_hdr_t;

#define BEACON_FRAME_SIZE_BYTES	(sizeof(beacon_frame_hdr_t) + BEACON_FRAME_DATA_SIZE_BYTES)

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __BEACON_TYPES_H__
