/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __BEACON_CFG_USER_H__
#define __BEACON_CFG_USER_H__

/**
 * @addtogroup service_beacons
 * @{
 *
 * @file beacons_cfg_user.h
 *
 * @brief Beacons service user configurations header
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "beacon_cfg_types.h"

/** the beacon message can contain up to 72 bytes of data which comprise the individual beacon messages */
#define BEACON_FRAME_DATA_SIZE_BYTES		(70U)

/** maximum number of bytes in a single beacon message; the limitation comes from the beacon message header which defines the size field as a 1-byte entry */
#define BEACON_MSG_MAX_SIZE_BYTES			(255U)

/** beacon send period in milliseconds */
#define BEACON_SEND_PERIOD_MS				(5000U)

/** beacon sink adapter confirmation timeout in milliseconds */
#define BEACON_SINK_CONFIRM_TIMEOUT_MS		(2000U)

/** period of the beacon service task in milliseconds */
#define BEACON_TASK_PERIOD_MS				(250U)

/** NVM configuration reload time in milliseconds taken into account only in Stopped mode to
detect possible reactivation of the beacon service */
#define BCN_RELOAD_CFG_TIME_STOP_MODE_MS	(1000U)

/** ESPS address of the UHF sink device */
#define BEACONS_UHF_SINK_ESPS_ADDRESS		(0x11U)

/** @brief Determines the active beacon preset id to use for the selection of beacon messages
 *
 * 	The beacon configuration provides a set of beacon preset identifiers which are coupled with a set of
 * 	beacon messages to transmit. In this case, the preset id is determined from the OBC operational mode.
 *
 *  @return ID of the active beacon preset
 */
uint8_t beacons_cfg_get_active_preset(void);

/** @brief The function is used to simulate a change in the active beacon preset. Its effect will remain
 * 		   until next reboot or until the @ref beacons_cfg_restore_active_preset is gets called.
 *
 *  @param preset_id Active preset id to be used by the beacon service for subsequent beacon bursts
 *
 *  @return `true` if configuration was applied successfully, otherwise - `false`
 */
bool beacons_cfg_set_active_preset(uint8_t preset_id);

/** @brief The function removes the effect of the @ref beacons_cfg_set_active_preset request.
 *
 */
void beacons_cfg_restore_active_preset(void);

/** @brief Provides the current state of the ConOps
 *  @return Active state ID of the beacons service SM
*/
uint8_t beacons_get_op_mode(void);

#ifdef __cplusplus
}

#endif  // #ifdef __cplusplus
#endif  // #ifndef __BEACON_CFG_USER_H__
