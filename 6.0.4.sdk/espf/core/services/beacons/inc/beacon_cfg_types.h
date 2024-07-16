/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/** @addtogroup service_beacons
  * @{
  * @file beacon_cfg_types.h
  *
  * @brief Beacons service configuration types
  * @}
  */

#ifndef __BEACON_CFG_TYPES_H__
#define __BEACON_CFG_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"
#include "datacache.h"

typedef dc_data_status_t (*p_dc_getter)(void * const p_data);

/** @typedef beacon_entry_t
 *  @brief Beacon configuration entry descriptor
 */
typedef struct
{
	const uint16_t beacon_type;				/**< type id of the specific beacon used to enable data interpretation later */
	const p_dc_getter p_get_beacon_data;	/**< a pointer to a DataCache getter function to be used for obtaining the data for the beacon */
	const uint32_t data_size;     			/**< beacon data size in bytes */
} beacon_entry_t;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __BEACON_CFG_TYPES_H__
