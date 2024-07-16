/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __AOCS_CNTRL_H__
#define __AOCS_CNTRL_H__

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup aocs_cntrl AOCS
 * @{
 * Attitude and Orbit Control System (AOCS) control and telemetry service
 * - Provides basic control over the integrated AOCS subsystems
 * - Provides basic telemetry from the integrated AOCS subsystem
 *
 * ## Integrating a new AOCS subsystem
 *
 * The integration of a new subsystem boils down to adding the necessary changes in aocs_cntrl_cfg.c and aocs_cntrl_cfg.h.
 *
 * First, extend the enumeration located in **aocs_cntrl_cfg.h**:
 *
 * @code {.c}
 * typedef enum
 * {
 * 	 AOCS_CNTRL_TYPE_CUBEADCS,
 * 	 AOCS_CNTRL_TYPE_NEW_AOCS, // The new entry
 * 	 AOCS_CNTRL_TYPE_MAX,
 *
 * } aocs_cntrl_types_t;
 * @endcode
 *
 * and add the new interface in aocs_cntrl_cfg.c:
 *
 * @code {.c}
 *  * const aocs_cntrl_base_cfg_t aocs_cntrl_cfg[AOCS_CNTRL_MAX] =
 * {
 * 		{.aocs_if = &aocs_cntrl_cubeadcs_int},
 * 		{.aocs_if = &new_aocs_cntrl_int},			// The new AOCS interface
 * };
 * @endcode
 *
 * The actual interface implementation can be located anywhere, just add the relevant header include.
 *
 * ## Extending the AOCS control service
 *
 * The service can be extended by adding the new interfaces and logic in the core part of the services located in:
 * - aocs_cntrl.c
 * - if_aocs_cntrl.h
 *
 * @file     aocs_cntrl.h
 * @brief    Attitude and Orbit Control System Interface
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#include "aocs_cntrl_types.h"
/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
/**
 *  @brief Initialise the AOCS control task
 */
void aocs_cntrl_task_init(void);

/**
 * @brief Deinitialise (stop monitoring) the AOCS control task
 */
void aocs_cntrl_task_deinit(void);

/**
 * @brief Request a change in the AOCS state (control and estimation modes)
 *
 * @param[in]: aocs_cntrl_sys_state_types_t sys_state - the requested AOCS state
 * @param[in]: aocs_cntrl_reference_params_t * p_ref_params - reference parameters (e.g. angles, geo coordinates) for some AOCS control modes
 *
 * @retval AOCS_CNTRL_ERR_OK: Request for state change has been accepted by the AOCS service
 * @retval AOCS_CNTRL_ERR_BUSY: Request has been rejected because the previous request has not been fully processed yet
 */
aocs_cntrl_err_status aocs_cntrl_request_aocs_state(const aocs_cntrl_sys_state_types_t sys_state, const aocs_cntrl_reference_params_t * const p_ref_params);

/**
 * @brief Get the current requested AOCS state (control and estimation modes)
 *
 * @param[out]: aocs_cntrl_sys_state_types_t * p_aocs_state - target storage for the AOCS state
 * @param[out]: aocs_cntrl_sys_state_req_state_t * p_aocs_req_state - target storage for the state of the request
 *
 * @retval AOCS_CNTRL_ERR_OK: AOCS state and request status have been retrieved successfully
 * @retval AOCS_CNTRL_ERR_FAILED: An error has occurred while reading AOCS state and request status. Retrieved values are not to be trusted
 */
aocs_cntrl_err_status aocs_cntrl_get_aocs_state(aocs_cntrl_sys_state_types_t * const p_aocs_state,
                               aocs_cntrl_sys_state_req_state_t * const p_aocs_req_state);

/**
 * @brief Get the commissioning status of the underlying ADCS
 *
 * @param[out]:  aocs_cms_status_t * p_status - Storage location for the read status
 *
 * @retval true: Commissioning status successfully read
 * @retval false: Error reading commissioning status
 */
bool aocs_cntrl_get_cms_status(aocs_cms_status_t * const p_status);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __AOCS_CNTRL_H__
