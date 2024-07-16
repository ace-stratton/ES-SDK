/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __BEACONS_H__
#define __BEACONS_H__

/** @addtogroup Services
  * @{
  *
  * @defgroup service_beacons Beacons
  * @{
  *
  * The beacon service takes responsibility of:
  * 	- periodic collection of beacon messages directly from the DataCache;
  * 	- assembly of message frames (up to a pre-configured length) and forwarding to a data sink adapter
  * 	  (e.g. transmission to radio, sending over to a serial connection or storage to a file, etc.);
  *
  * @file beacons.h
  *
  * @brief Beacons service public interface
  *
  * @}
  * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

/** @brief Initializes the beacon service and prepares it for operation. */
void beacons_init(void);

/** @brief Starts regular beacon transmission */
void beacons_start(void);

/** @brief Ceases regular beacon transmission */
void beacons_stop(void);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __BEACONS_H__
