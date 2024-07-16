/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __PAYLOAD_CTRL_H__
/**
 * @addtogroup Services
 * @{
 *
 * @defgroup payload_ctrl Payload Controller
 * @{
 *
 * Responsible for:
 * - individual payload activation/deactivation
 * - payload state tracking and error handling
 * - triggers the configured pointing mode for the payload and waits until confirmed before starting the payload
 *
 * @file payload_ctrl.h
 * @brief Payload Controller public interface
 *
 *
 * @}
 * @}
*/

#define __PAYLOAD_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>
#include "if_payload_control.h"
#include "payload_cfg.h"
#include "payload_shared_types.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/** \typedef payload_ctrl_op_res_t
 * 	@brief Payload Controller operation status codes
 */
typedef enum
{
	PL_CTRL_OP_RES_NOT_INIT,			/**< component not initialized */
	PL_CTRL_OP_RES_INVALID_PL_ID,		/**< invalid payload id provided */
	PL_CTRL_OP_RES_REFUSE_CMD,			/**< command is refused because operating conditions do not allow it */
	PL_CTRL_OP_RES_FAILED,				/**< command execution failed */
	PL_CTRL_OP_RES_OK,					/**< operation successful */
	PL_CTRL_OP_RES_MAX					/**< used for validity checking only */
} payload_ctrl_op_res_t;

/** \typedef payload_ctrl_event_t
 * 	@brief Payload event structure
 */
typedef struct
{
	payload_ctrl_payload_t payload_id;	/**< unique payload instance identifier */
	pl_state_t op_state;				/**< operating state to which a transition occurred */
	uint32_t error_code;				/**< payload error code in case op_state = PL_STATE_ERROR */
} payload_ctrl_event_t;

/** \typedef p_payload_event
 * 	@brief Payload event callback used to signal payload state changes to client components
 *
 * 	@param p_event	state change event data
 */
typedef void (*p_payload_event)(payload_ctrl_event_t *p_event);

/** \typedef payload_ctrl_start_cfg_t
 * 	@brief Payload starting configuration
 *
 */
typedef struct
{
	record_adcs_t pointing_cfg;			/**< ADCS configuration parameters to setup payload pointing mode before start */
	pl_args_t payload_args;				/**< payload-specific buffer passed transparently to the respective payload manager */
} payload_ctrl_start_cfg_t;

/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
/** @brief Initialize all configured payloads
 *
 *	@return PL_CTRL_OP_FAILED - if at least one payload init failed
 *			PL_CTRL_OP_RES_OK - all payloads initialized successfully
 */
payload_ctrl_op_res_t payload_ctrl_init(void);

/** @brief Deinitialize all configured payloads
 *
 *	@return operation status (see \ref payload_ctrl_op_res_t for details)
 */
payload_ctrl_op_res_t payload_ctrl_deinit(void);

/** @brief Start a specified payload instance
 *  @param payload_id unique payload instance identifier
 *  @param p_start_cfg a pointer to the payload start configuration
 *
 *	@return operation status (see \ref payload_ctrl_op_res_t for details)
 */
payload_ctrl_op_res_t payload_ctrl_start(const payload_ctrl_payload_t payload_id,
										 payload_ctrl_start_cfg_t * const p_start_cfg);

/** @brief Stop a specified payload instance
 *  @param payload_id unique payload instance identifier
 *  @param stop_mode specifies how the stop operation shall be performed
 *
 *	@return operation status (see \ref payload_ctrl_op_res_t for details)
 */
payload_ctrl_op_res_t payload_ctrl_stop(const payload_ctrl_payload_t payload_id,
										const pl_op_stop_mode_t stop_mode);

/** @brief Subscribes to payload events
 *  @param p_evt_callback a pointer to an event notification function called when payload state changes;
 *  					  if NULL specified, the subscription is removed
 */
void payload_ctrl_subscribe_events(p_payload_event const p_evt_callback);

/** @brief Queries the state of a specified payload
 *  @param payload_id unique payload instance identifier
 *  @param p_state a pointer to receive the payload state
 *  @param p_error_code only to be used if the p_state is set to PL_STATE_ERROR
 *
 *	@return operation status (see \ref payload_ctrl_op_res_t for details)
 */
payload_ctrl_op_res_t payload_ctrl_get_state(const payload_ctrl_payload_t payload_id,
											 pl_state_t * p_state,
											 uint32_t * const p_error_code);

/** @brief Notification function to be used by the payload_cfg.c implementation to properly
 *            route payload manager notifications from multi-instance payloads to the correct
 *            external payload_id.
 *
 *  @param payload_id external payload id (unique for each payload instance no matter if it is
 *                    of the same kind and managed by the same payload manager
 *  @param to_state target state which was reached by the payload
 */
void payload_ctrl_event_notify(const payload_ctrl_payload_t payload_id, pl_state_t to_state);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef __PAYLOAD_CTRL_H__
