/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __TELEMETRY_CFG_USER_H__
#define __TELEMETRY_CFG_USER_H__

/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_cfg_user.h
 * @brief Telemetry service configuration header
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/** Telemetry frame delimiter value (for COBS encoding we use 0) */
#define TLM_FRM_DELIMITER            		(0U)

/** telemetry root drive (only one supported at the moment) */
#define TLM_FILE_SINK_ROOT_PATH				""

/** 3-letter file extension used for telemetry files */
#define TLM_FILE_SINK_EXT				    "tlm"

/** maximum size of the telemetry file name */
#define TLM_FILE_SINK_MAX_FN_SIZE			(20U)

/** size of the internal telemetry buffer used to frame messages before forwarding them to the data sink interface */
#define TLM_BUF_SIZE						(300U)

/** 10% over the TLM_BUF_SIZE used for COBS encoding */
#define TLM_ENCODE_BUF_SIZE					(TLM_BUF_SIZE + (TLM_BUF_SIZE / 10U))

/** number of bytes reserved for the Telemetry queue used to buffer messages before they get stored to SD card */
#define TLM_QUEUE_SIZE						(5 * TLM_ENCODE_BUF_SIZE)

/** period of the telemetry service task in milliseconds */
#define TLM_FILE_SINK_TASK_PERIOD_MS		(1500U)

/** number of milliseconds to pause telemetry file sink operation when a TL frame is received on ESPS I bus
(e.g. during ground station communication) */
#define TLM_FILE_SINK_PAUSE_ON_TL_FRAME_MS  (3000U)

/** period of the telemetry service task in milliseconds */
#define TLM_TASK_PERIOD_MS					(500U)

/** NVM configuration reload time in milliseconds taken into account only in Stopped mode to detect possible reactivation of the telemetry service */
#define TLM_RELOAD_CFG_TIME_MS				(1000U)

/** @brief Determines the active beacon preset id to use for the selection of beacon messages
 *
 * 	The beacon configuration provides a set of beacon preset identifiers which are coupled with a set of
 * 	beacon messages to transmit. In this case, the preset id is determined from the OBC operational mode.
 *
 * @return ID of the active telemetry preset
 */
uint8_t telemetry_cfg_get_active_preset(void);

/** @brief The function is used to simulate a change in the active beacon preset. Its effect will remain
 * 		   until next reboot or until the @ref telemetry_cfg_restore_active_preset is gets called.
 *
 *  @param preset_id Active preset id to be used by the beacon service for subsequent beacon bursts
 *
 *  @return `true` if configuration was applied successfully, otherwise - `false`
 */
bool telemetry_cfg_set_active_preset(uint8_t preset_id);

/** @brief The function removes the effect of the @ref telemetry_cfg_set_active_preset request.
 *
 */
void telemetry_cfg_restore_active_preset(void);

/** @brief Provides the current state of the ConOps
 *  @return ID of the active telemetry SM state
*/
uint8_t telemetry_get_op_mode(void);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __TELEMETRY_CFG_USER_H__
