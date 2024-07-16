/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __AOCS_PM_TYPES_H__
#define __AOCS_PM_TYPES_H__

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_cntrl_types.c
 * @brief    AOCS control common types
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "aocs_pm_cfg.h"
#include "aocs_pm.h"
#include "es_cdef.h"
#include "aocs_cntrl_types.h"

/** @brief Size of the circular buffer  */
#define SIZE_OF_CIRC_BUF 				2048U

typedef enum
{
	ABOVE 	= 2,
	BETWEEN = 1,
	BELOW 	= 0
}aocs_pm_state_of_threshold;

typedef enum
{
	AOCS_PM_VALUE_1 = 0,
	AOCS_PM_VALUE_2 = 1,
	AOCS_PM_VALUE_3 = 2
}aocs_pm_value_id_t;

typedef struct aocs_pm_threshold_values_tag
{
	/* Tolerance for performance */
	float f_tolerance;
	/* Safety factor is basically the tolerance of the tolerance */
	float f_safety_factor;
}aocs_pm_threshold_values_t;


typedef struct aocs_pm_output_tag
{
	/* Stability assessment in percentage */
	uint8_t u8_stability_measure;
	/* Encoded stability history as an uint16_t */
	uint16_t u16_encoded_history;
}aocs_pm_output_t;

typedef struct aocs_pm_ctx_tag
{
	/* Offset */
	float f_offset;
	/* Previous offset */
	float f_old_offset;
	/* ID to search easier trough instances */
	aocs_pm_value_id_t id;
	/* Upper threshold value */
	float f_upper_threshold;
	/* Lower threshold value */
	float f_lower_threshold;
	/* Data being assessed */
	float data;
	/* Structure that contains the threshold values for each slot for assessment */
	aocs_pm_threshold_values_t s_threshold_values;
	/* Counter based on which we divide the whole orbit to 16 equal parts */
	uint32_t u32_cnt_long_term_window;
	/* Value to hold the sum of the buffer */
	uint16_t u16_buffer_sum;
	/* Compute the uninterrupted stability time - This is the short term measure, which
	 * needs to become > T_CONTACT to count towards the long term stability estimate */
	uint32_t u32_cnt_uninterrupted_time;
	/* Handle of the circular buffer */
	tQueue s_circ_buf;
	/* Circular buffer */
	tQueueData a_circ_buf[SIZE_OF_CIRC_BUF];
	/* Output of the algorithm */
	aocs_pm_output_t s_output;
	/* Keeps the state of the threshold to know which set of thresholds to choose */
	aocs_pm_state_of_threshold e_state_of_threshold;
	/* Remember data from last time to extrapolate */
	uint8_t u8_last_data;
	/* Counter for how many times we entered the algorithm */
	uint32_t u32_number_of_samples_passed;
}aocs_pm_ctx_t;

typedef struct aocs_pm_parameters_tag
{
	/* How much time we should log when we want to */
	uint32_t u32_max_time_for_auto_log;
	/* Update interval it is uint8 because of requirements */
	uint8_t u8_update_interval;
	/* Data for assessment */
	aocs_log_data_types_t data_type;
	/* Number of samples to skip when we do a maneuver */
	uint16_t u16_samples_to_skip;
}aocs_pm_parameters_t;

typedef struct aocs_pm_counters_tag
{
	/* Variable to hold the time for logging in seconds */
	uint32_t u32_time_for_logging_in_sec;
	/* Counter for measuring how much time we were logging*/
	uint32_t u32_time_passed_since_logging_sec;
	/* Counting the time since we started logging to see if we reached the maxed logging time */
	uint32_t u32_counter_for_max_logging;
	/* Number of samples to skip when we do a maneuver */
	uint16_t u16_skiped_samples;
	/* Flag for when we reach max time for auto logging*/
	bool b_max_autolog_reached;
	/* Flag for auto logging */
	bool b_auto_logging_enabled;
	/* Last value of the sysTick timer */
	uint32_t d_t_last;
	/* Difference from the last sysTick and the current one in miliseconds */
	uint32_t d_t;
	/* Difference from the last sysTick and the current one in seconds */
	float d_t_in_sec;
}aocs_pm_counters_t;



#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __AOCS_PM_TYPES_H__
