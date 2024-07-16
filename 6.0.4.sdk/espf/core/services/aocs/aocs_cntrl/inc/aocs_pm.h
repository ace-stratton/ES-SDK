/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ESPF_CORE_SERVICES_AOCS_AOCS_CNTRL_INC_AOCS_PM_H_
#define ESPF_CORE_SERVICES_AOCS_AOCS_CNTRL_INC_AOCS_PM_H_

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_pm.h
 * @brief	 AOCS performance monitor interface
 *
 * @}
 */

#include "aocs_pm_cfg.h"
#include "datetime.h"
#include "datacache.h"
#include "CircularFlatBuffer.h"
#include "libqueue.h"
#include "aocs_cntrl_types.h"
#include "aocs_pm_types.h"
#include "nvm_app_block_ids.h"
#include "nvm.h"
#include "if_aocs_cntrl.h"

#if TEST_ENABLED
uint8_t fs_aocs_pm_assess_stability(aocs_pm_ctx_t* context);
void 	fs_aocs_pm_manage_offset(aocs_cntrl_offset_t* offset,aocs_cntrl_res_t aocs_data_status);
void 	fs_aocs_update_att_buff(aocs_pm_ctx_t* context, int32_t input_data, aocs_cntrl_res_t data_status);
#endif

/** @brief Initialize the performance monitor */
extern void aocs_pm_init(void);

/** @brief Reset the algorithm */
extern void aocs_pm_reset(void);
/** @brief
 *  @param[in] aocs_cntrl_log_data_t* get_data_to_pass_to_pm_algorythm pointer to a struct with data for the pm
 *  @param[in] aocs_cntrl_offset_t* aocs_pm_detect_offset_change pointer to a struct with data for the offset
 *  @param[in] aocs_cntrl_res_t data_status - status of the data cache read, this is important because
 *  if the data is invalid the algorithm is extrapolating */
extern void aocs_pm_calc_performance(aocs_cntrl_log_data_t* get_data_to_pass_to_pm_algorythm, aocs_cntrl_offset_t* aocs_pm_detect_offset_change, aocs_cntrl_res_t data_status );

/** @brief Get how much time to log automatically
 *  @return uint32_t current time for auto logging */
extern uint32_t aocs_pm_get_max_time_for_auto_logging(void);

/** @brief Set how much time to log automatically
 *  @param[in] uint32_t u32_time - how much time to log in seconds
 *  @return uint8_t 0: ok
 *  @return uint8_t 1: value not set */
extern uint8_t aocs_pm_set_max_time_for_auto_logging(uint32_t time);

/** @brief Start automatic logging to file */
extern void aocs_pm_start_auto_logging(void);

/** @brief Stop automatic logging to file  by setting to 0 both flags associated with auto logging*/
extern void aocs_pm_stop_auto_logging(void);


/** @brief Start logging to file
 *  @param[in] uint32_t u32_time - how much time to log in seconds */
extern void aocs_pm_start_logging(uint32_t u32_time);

/** @brief Get data type for assessment
 *  @return aocs_log_data_types_t data type that is currently assessing */
extern aocs_log_data_types_t aocs_pm_get_data_type_for_assessment(void);

/** @brief Set data type for assessment
 *  @param[in] aocs_log_data_types_t data - data type
 *  @return uint8_t 0: ok
 *  @return uint8_t 1: value not set */
extern uint8_t aocs_pm_set_data_type_for_assessment(aocs_log_data_types_t data);

/** @brief Get update interval for the algorithm
 *  @return uint8_t update value */
extern uint8_t aocs_pm_get_update_interval(void);

/** @brief Set update interval for the algorithm
 *  @param[in] uint8_t data - data type
 *  @return uint8_t 0: ok
 *  @return uint8_t 1: value not set */
extern uint8_t aocs_pm_set_update_interval(uint8_t data);

/** @brief Set how many samples to skip when change in offset is detected
 *  @return uint16_t samples to skip */
extern uint16_t aocs_pm_get_samples_to_skip(void);

/** @brief Set how many samples to skip when change in offset is detected
 *  @param[out] aocs_pm_parameters_t* config - pointer to a structure with the new parameters
 *  @return uint8_t 0: ok
 *  @return uint8_t 1: value not set */
extern uint8_t aocs_pm_set_samples_to_skip(uint16_t data);

/** @brief Get new configuration parameters from the nvm
 *  @param[out] aocs_pm_parameters_t* config - pointer to a structure to store parameters */
extern void aocs_pm_get_config_form_nvm(aocs_pm_parameters_t* config);

/** @brief Set new configuration parameters to the nvm
 *  @param[out] aocs_pm_parameters_t* config - pointer to a structure with the new parameters
 *  @return uint8_t 0: ok
 *  @return uint8_t 1: value not set */
extern uint8_t aocs_pm_set_config_to_nvm(aocs_pm_parameters_t* config);

/** @brief Get thresholds
 *  @param[out] aocs_pm_threshold_values_t* values - pointer to a structure for the read values
 *  @param[in] uint8_t id  which element of the array to get */
extern void aocs_pm_get_threshold(aocs_pm_threshold_values_t* values, aocs_pm_value_id_t id);

/** @brief Get thresholds from the nvm
 *  @param[out] aocs_pm_threshold_values_t* values - pointer to a structure for the values from the nvm
 *  @param[in] uint8_t id  which element of the array to get */
extern void aocs_pm_get_threshold_from_nvm(aocs_pm_threshold_values_t* f_values, aocs_pm_value_id_t id);

/** @brief Set new thresholds to the nvm
 *  @param[out] aocs_pm_threshold_values_t* values - pointer for a structure with values for the new threshold
 *  @param[in] uint8_t id  which element of the array to get
 *  @return uint8_t 0: ok
 *  @return uint8_t 1: value not set */
extern uint8_t aocs_pm_set_thresholds_to_nvm(aocs_pm_threshold_values_t* values, aocs_pm_value_id_t id);

/** @brief Get output of the algorithm
 *  @param[out] aocs_pm_output_t* output - pointer to an array of the type aocs_pm_output_t
 *  @param[in] uint8_t id  which element of the array to get */
extern void aocs_pm_get_output(aocs_pm_output_t* output, uint8_t id);

#endif /* ESPF_CORE_SERVICES_AOCS_AOCS_CNTRL_INC_AOCS_PM_H_ */
