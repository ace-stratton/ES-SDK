/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __IF_SENSOR_DATA_SERVICE_H__
#define __IF_SENSOR_DATA_SERVICE_H__

/**
 * @addtogroup sds
 * @{
 *
 * @file     if_sensor_data_service.h
 * @brief    Sensor Data Service Interface Header. This interface shall be implemented by all sensor drivers/managers
 *           in the system to enable uniform data collection and update in the Data Cache
 *
 * @}
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>

#include "sensor_data_types.h"

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @typedef sds_op_status_t
    @brief This is the standard return result used throughout the SDS module */
typedef enum
{
   SDS_OP_STATUS_FAIL,        /**< used to indicate that the requested operation failed 	*/
   SDS_OP_STATUS_OK           /**< used to indicate that the requested operation succeeded 	*/
} sds_op_status_t;

/** @typedef sds_sensor_status_t
    @brief This is the sensor status */
typedef enum
{
	SDS_SENSOR_STATUS_DEINIT,      /**< indicates that the sensor has been de-initialised 	*/
	SDS_SENSOR_STATUS_INIT,        /**< indicates that the sensor has been initialised 	*/
	SDS_SENSOR_STATUS_ERR,		  /**< indicates that an error in the sensor has occurred preventing normal operation 	*/
} sds_sensor_status_t;

/** @typedef p_sds_init_t
    @brief Initialize the sensor
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_init_t)(void);

/** @typedef p_sds_deinit_t
    @brief De-initialize the sensor
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_deinit_t)(void);

/** @typedef p_sds_get_state
    @brief Gets the sensor state
    @return sensor status result (see \ref sds_sensor_status_t values for details) */
typedef sds_sensor_status_t (*p_sds_get_state)(void);

/** @typedef p_sds_get_last_err
    @brief Gets the last reported sensor error
    @return sensor last reported error code */
typedef uint8_t (*p_sds_get_last_err)(void);

/** @typedef p_sds_get_reg_t
    @brief Read a sensor register.
    @param[in] uint8_t sens_id - sensor id (to be interpreted by the integration). Some sensors can be redundant.
    @param[in] sds_axis_enum_t sens_axis - used to indicate which sensor for a set of three single axis sensors should be accessed.
    @param[in] uint32_t reg_address - register address
    @param[out] uint32_t *reg_value - pointer to storage location for register read value
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_get_reg_t)(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value);

/** @typedef p_sds_set_reg_t
    @brief Set a sensor register.
    @param[in] uint8_t sens_id - sensor id (to be interpreted by the integration). Some sensors can be redundant.
    @param[in] sds_axis_enum_t sens_axis - used to indicate which sensor for a set of three single axis sensors should be accessed.
    @param[in] uint32_t reg_address - register address
    @param[out] uint32_t reg_value - register value
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_set_reg_t)(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value);

/** @typedef sds_if_t
    @brief Sensor Data Service interface structure to be implemented by each sensor in the system.
           This interface is to be used by the Sensor Data Service implementation. */
typedef struct
{
    p_sds_init_t init;
    p_sds_deinit_t deinit;
    p_sds_get_state get_state;
    p_sds_get_last_err get_last_error;
    p_sds_get_reg_t get_reg;
    p_sds_set_reg_t set_reg;
} sds_if_t;

/** @typedef p_sds_get_mag_data_t
    @brief Get data from the MAGNETOMETER sensor
    @param p_data_dst pointer to the destination to copy over the sensors data
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_get_mag_data_t)(sds_mag_data_t * const p_data_dst);

/** @typedef p_sds_get_gyro_data_t
    @brief Get data from the GYRO sensors
    @param p_data_dst pointer to the destination to copy over the sensors data
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_get_gyro_data_t)(sds_gyro_data_t * const p_data_dst);

/** @typedef p_sds_get_css_data_t
    @brief Get data from the CSS sensors
    @param p_data_dst pointer to the destination to copy over the sensors data
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_get_css_data_t)(sds_css_data_t * const p_data_dst);

/** @typedef p_sds_get_acc_data_t
    @brief Get data from the Accelerometer sensor
    @param p_data_dst pointer to the destination to copy over the sensors data
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_get_acc_data_t)(sds_acc_data_t * const p_data_dst);

/** @typedef p_sds_get_panel_temp_data_t
    @brief Get data from the Panels temperature sensors
    @param p_data_dst pointer to the destination to copy over the sensors data
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_get_panel_temp_data_t)(sds_panel_temp_data_t * const p_data_dst);

/** @typedef p_sds_get_gyro_temp_data_t
    @brief Get data from the Gyroscopes temperature sensors
    @param p_data_dst pointer to the destination to copy over the sensors data
    @return operation status result (see \ref sds_op_status_t values for details) */
typedef sds_op_status_t (*p_sds_get_gyro_temp_data_t)(sds_gyro_temp_data_t * const p_data_dst);

/** @typedef sds_mag_if_t
    @brief Sensor Data Service interface structure to be implemented by the magnetometer driver */
typedef struct
{
	p_sds_get_mag_data_t get_mag_data;
} sds_mag_data_if_t;

/** @typedef sds_gyro_if_t
    @brief Sensor Data Service interface structure to be implemented by the gyroscopes driver */
typedef struct
{
	p_sds_get_gyro_data_t get_gyro_data;
} sds_gyro_data_if_t;

/** @typedef sds_css_if_t
    @brief Sensor Data Service interface structure to be implemented by the CSS driver */
typedef struct
{
	p_sds_get_css_data_t get_css_data;
} sds_css_data_if_t;

/** @typedef sds_acc_if_t
    @brief Sensor Data Service interface structure to be implemented by the accelerometer driver */
typedef struct
{
	p_sds_get_acc_data_t get_acc_data;
} sds_acc_data_if_t;

/** @typedef sds_panel_temp_if_t
    @brief Sensor Data Service interface structure to be implemented by the panels temperature sensors driver */
typedef struct
{
	p_sds_get_panel_temp_data_t get_panel_temp_data;
} sds_panel_temp_data_if_t;

/** @typedef sds_gyro_temp_if_t
    @brief Sensor Data Service interface structure to be implemented by the gyroscopes temperature sensors driver */
typedef struct
{
	p_sds_get_gyro_temp_data_t get_gyro_temp_data;
} sds_gyro_temp_data_if_t;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __IF_SENSOR_DATA_SERVICE_H__
