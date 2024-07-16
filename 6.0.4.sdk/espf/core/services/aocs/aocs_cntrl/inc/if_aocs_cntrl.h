/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __IF_AOCS_CNTRL_H__
#define __IF_AOCS_CNTRL_H__

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     if_aocs_cntrl.c
 * @brief    Integration interface to the AOCS control service. Each specific AOCS subsystem must implement this interface.
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "aocs_cntrl_types.h"

/* @brief AOCS control standard return codes */
typedef enum
{
	AOCS_CNTRL_FAILED,
	AOCS_CNTRL_OK,
	AOCS_CNTRL_MAX

} aocs_cntrl_res_t;

/* @brief Type depicting the functionality: request a change in the AOCS system state
 *
 * @param uint8_t sys_state - the new system state value
 * @param aocs_cntrl_reference_params_t* p_ref_params - reference parameters for some ADCS control modes
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_sys_state_chng_req)(const aocs_cntrl_sys_state_types_t sys_state,
                                                             const aocs_cntrl_reference_params_t* const p_ref_params);

/* @brief Get the state of the system state change request
 *
 * @param[out] uint8_t *p_sys_state - pointer to store the system state currently in use
 * @param[out] aocs_cntrl_sys_state_req_state_t *p_sys_state_req_state - pointer to store the system state request state
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_sys_state_get_req_state)(aocs_cntrl_sys_state_types_t *p_sys_state, aocs_cntrl_sys_state_req_state_t *p_sys_state_req_state);

/* @brief Get the AOCS system reported errors
 *
 * @param[out] aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs - pointer to destination to store the read errors
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_get_aocs_system_errors)(aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs);

/* @brief Get the estimated angular rates and norm in [mrad/s]
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *p_est_ang_rates_dst - pointer to store the angular rates
 * @param[out] aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm_dst - pointer to store the angular rates norm
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_get_est_ang_rates)(aocs_cntrl_est_ang_rate_t *p_est_ang_rates_dst, aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm_dst);

/* @brief Get the estimated attitude angles in [mdeg]
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *aocs_cntrl_est_att_t - pointer to store the attitude angles
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_get_est_att_ang)(aocs_cntrl_est_att_t *p_est_att_ang_dst);

/* @brief Get the measured wheel speed [RPM]
 *
 * @param[out] aocs_cntrl_wheel_speed_t *p_meas_wheel_speed_dst - pointer to location to store measured wheel speed
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_get_meas_wheel_speed)(aocs_cntrl_wheel_speed_t *p_meas_wheel_speed_dst);

/* @brief Get the data for assessment in mili units
 *
 * @param[out] aocs_cntrl_log_data_t *p_log_data - pointer to store the data for assessment
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_get_log_data)(aocs_cntrl_log_data_t *p_log_data, aocs_log_data_types_t data_type, aocs_cntrl_offset_t* p_offset_values);

/* @brief Get the commissioning status of the ADCS
 *
 * @param[out] uint8_t *p_cms_status - pointer to store the commissioning status
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_get_cms_status) (uint8_t * const p_cms_status);

/* @brief Get the presence of running control algorithm
 *
 * @param[out] bool* const p_cntrl_status - pointer to store the control status
 *
 * @return operation request result
 *
 */
typedef aocs_cntrl_res_t (* p_aocs_cntrl_get_cntrl_status) (bool* const p_cntrl_status);

/* @brief Common interface structure to any AOCS system */
typedef struct
{
	p_aocs_cntrl_sys_state_chng_req p_sys_state_chng_req;
	p_aocs_cntrl_sys_state_get_req_state p_sys_state_get_req_state;
	p_aocs_cntrl_get_aocs_system_errors p_get_aocs_system_errors;
	p_aocs_cntrl_get_est_ang_rates p_get_est_ang_rates;
	p_aocs_cntrl_get_est_att_ang p_get_est_att_ang;
	p_aocs_cntrl_get_meas_wheel_speed p_get_meas_wheel_speed;
	p_aocs_cntrl_get_log_data p_get_log_data;
	p_aocs_cntrl_get_cms_status p_get_cms_status;
	p_aocs_cntrl_get_cntrl_status p_get_cntrl_status;

} aocs_cntrl_t;

/* @brief Basic configuration of the AOCS control service
 *
 * @note This is the configuration type
 */
typedef struct
{
	const aocs_cntrl_t * const aocs_if; /**< pointer to the AOCS interface */
} aocs_cntrl_base_cfg_t;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __IF_AOCS_CNTRL_H__
