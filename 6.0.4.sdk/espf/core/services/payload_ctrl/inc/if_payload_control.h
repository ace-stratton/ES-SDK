/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __IF_PAYLOAD_CONTROL_H__
/**
 * @addtogroup payload_ctrl
 * @{
 *
 * @file if_payload_control.h
 * @brief Payload Control Interface Header. This interface shall be implemented by all
 *        payload configured in the system to enable uniform control and query operation from
 *        ConOps mechanisms.
 *
 * @}
*/

#define __IF_PAYLOAD_CONTROL_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/

/** @typedef pl_op_status_t
    @brief These values describe the possible outcomes of a payload operation
*/
typedef enum
{
   PL_OP_STATUS_REJECT,         /**< used to indicate that the payload operation is rejected */
   PL_OP_STATUS_FAILURE,        /**< used to indicate that the payload operation failed */
   PL_OP_STATUS_OK              /**< used to indicate that the payload operation succeeded */
} pl_op_status_t;

/** @typedef pl_op_stop_mode_t
    @brief These values describe the possible stop modes of the payloads.
*/
typedef enum
{
    PL_OP_STOP_MODE_NORMAL = 0x00,     /**< standard stop mode sequence executed */
    PL_OP_STOP_MODE_EMERGENCY = 0xFF   /**< immediate power cut of the payload */
} pl_op_stop_mode_t;

/** @typedef pl_state_t
    @brief Enumeration of states used by the Payload Controller to handle the common payload behavior
*/
typedef enum
{
    PL_STATE_NOT_INIT,          /**< payload state indicating the init operation is not started */
    PL_STATE_STOPPED,           /**< payload state indicating the init operation is executed successfully but the payload is not yet started */
    PL_STATE_STARTED,           /**< payload state indicating the start operation is confirmed */
    PL_STATE_STARTING,          /**< payload state indicating that the payload is in the process of starting up */
    PL_STATE_STOPPING,          /**< payload state indicating that the payload is in the process of stopping */
    PL_STATE_ERROR,             /**< error state which can be entered from any other state if the payload reports an issue */
	PL_STATE_ADCS_TIMEOUT,		/**< payload controller state indicating that the payload request was not started due to ADCS timeout **/
	PL_STATE_ADCS_ERROR,		/**< payload controller state indicating that the payload request was not started due to ADCS error */
	PL_STATE_MAX				/**< used for range checking */
} pl_state_t;

/** @typedef pl_config_t
    @brief Payload configuration structure
*/
typedef struct
{
    void *p_config_data;        /**< a pointer to the payload-specific configuration data */
    const uint32_t size;        /**< size of the data pointed to by p_config_data */
} pl_config_t;

/** @typedef pl_instance_id_t
 *  @brief Payload instance type used to represent instances internally in the payload managers
 *  	   which implement the interface described in this file.
 */
typedef uint8_t pl_instance_id_t;

/** @typedef p_pl_event_notify_t
    @brief Notification sent by the payload manager when a state change occurs

    @param instance_id payload instance identifier (0 - if single instance);
    @param to_state payload state which was just reached
*/
typedef void (*p_pl_event_notify_t)(const pl_instance_id_t instance_id, pl_state_t to_state);

/** @typedef p_pl_init_t
    @brief Initializes the payload interfaces and puts the payload in stop mode;
    @param instance_id payload instance identifier (0 - if single instance);
    @param p_init_cfg a pointer to a payload-specific configuration structure used for initialization (if NULL, default configuration is used)
    @param p_event_notify_cb asynchronous notification function provided by the user (can be NULL if polling is used to check the payload state)

    \return operation status result (see \ref pl_op_status_t values for details)
*/
typedef pl_op_status_t (*p_pl_init_t)(const pl_instance_id_t instance_id,
                                      pl_config_t * const p_init_cfg,
                                      const p_pl_event_notify_t p_event_notify_cb);

/** @typedef p_pl_deinit_t
    @brief Performs a deinitialization and disabling of related clocks and peripherals required by the payload. After this call
           the system can be put safely to power down mode.
    @param instance_id payload instance identifier (0 - if single instance);

    \return operation status result (see \ref pl_op_status_t values for details)
*/
typedef pl_op_status_t (*p_pl_deinit_t)(const pl_instance_id_t instance_id);

/** @typedef p_pl_start_t
    @brief Triggers the payload start-up sequence.
    @param instance_id payload instance identifier (0 - if single instance);
    @param p_start_cfg a pointer to a payload-specific data used to configure the particular start operation

    \return operation status result (see \ref pl_op_status_t values for details)
*/
typedef pl_op_status_t (*p_pl_start_t)(const pl_instance_id_t instance_id, pl_config_t * const p_start_cfg);

/** @typedef p_pl_stop_t
    @brief Triggers the payload shutdown sequence.
    @param instance_id payload instance identifier (0 - if single instance);
    @param stop_mode specifies how the payload shall be stopped

    \return operation status result (see \ref pl_op_status_t values for details)
*/
typedef pl_op_status_t (*p_pl_stop_t)(const pl_instance_id_t instance_id, const pl_op_stop_mode_t stop_mode);

/** @typedef p_pl_get_active_state
    @brief Queries the payload manager for the currently active operational state of the payload.
           Shall return the same information as provided by \ref p_pl_event_notify_t.
    @param instance_id payload instance identifier (0 - if single instance);

    \return active state of the payload
*/
typedef pl_state_t (*p_pl_get_active_state)(const pl_instance_id_t instance_id);

/** @typedef p_pl_get_last_error
    @brief Provides a payload-specific error code which triggered the last entry to the ERROR state (if any).
    @param instance_id payload instance identifier (0 - if single instance);

    \return 0 - if no error; error code detected.
*/
typedef uint32_t (*p_pl_get_last_error)(const pl_instance_id_t instance_id);

/** @typedef pl_control_if_t
    @brief Payload control interface structure to be implemented by each payload in the system.
           This interface is to be used by the Payload Controller implementation.
*/
typedef struct
{
    p_pl_init_t init;
    p_pl_deinit_t deinit;
    p_pl_start_t start;
    p_pl_stop_t stop;
    p_pl_get_active_state get_state;
    p_pl_get_last_error get_last_error;
} pl_control_if_t;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef __IF_PAYLOAD_CONTROL_H__
