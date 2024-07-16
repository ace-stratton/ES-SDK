/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __SENSOR_DATA_SERVICE_H__
#define __SENSOR_DATA_SERVICE_H__

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup sds Sensor Data Service
 * @{
 * Sensor Data Service module that handles all sensor input and transfers it to DataCache
 *
 * @file     sensor_data_service.h
 * @brief    Sensor Data Service header
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "debug.h"
#include "cmsis_os2.h"
#include "sensor_data_types.h"
#include "sensor_data_cfg.h"

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
/** @brief Initialises the SDS task */
void sds_init(void);

/** @brief Return the sds thread ID
 *  @return osThreadId_t */
osThreadId_t sds_get_thread_id(void);

/** @brief Convert magnetometer data from sensor coordinate frame to satellite coordinate frame
 *  @param[in]  sds_mag_data_t     *p_mag_data
 *  @param[in]  sds_mag_enum_t      mag_id
 *  @param[out] sds_mag_data_sat_t *p_mag_data_sat */
void sds_conv_mag_data_to_sat_frame(sds_mag_data_t const * const p_mag_data, sds_mag_enum_t mag_id, sds_mag_data_sat_t * const p_mag_data_sat);

/** @brief Convert gyro data from sensor coordinate frame to satellite coordinate frame
 *  @param[in]  sds_gyro_data_t     *p_gyro_data
 *  @param[out] sds_gyro_data_sat_t *p_gyro_data_sat */
void sds_conv_gyro_data_to_sat_frame(sds_gyro_data_t const * const p_gyro_data, sds_gyro_data_sat_t * const p_gyro_data_sat);

/** @brief Convert css data from sensor coordinate frame to satellite coordinate frame
 *  @param[in]  sds_css_data_t     *p_css_data
 *  @param[out] sds_css_data_sat_t *p_css_data_sat */
void sds_conv_css_data_to_sat_frame(sds_css_data_t const * const p_css_data, sds_css_data_sat_t * const p_css_data_sat);

/** @brief Convert accelerometer data from sensor coordinate frame to satellite coordinate frame
 *  @param[in]  sds_acc_data_t     *p_acc_data
 *  @param[in]  sds_acc_enum_t      acc_id
 *  @param[out] sds_acc_data_sat_t *p_acc_data_sat */
void sds_conv_acc_data_to_sat_frame(sds_acc_data_t const * const p_acc_data, sds_acc_enum_t acc_id, sds_acc_data_sat_t * const p_acc_data_sat);

/** @brief Convert panel temperature data from sensor coordinate frame to satellite coordinate frame
 *  @param[in]  sds_panel_temp_data_t     *p_panel_temp_data
 *  @param[out] sds_panel_temp_data_sat_t *p_panel_temp_data_sat */
void sds_conv_panel_temp_data_to_sat_frame(sds_panel_temp_data_t const * const p_panel_temp_data, sds_panel_temp_data_sat_t * const p_panel_temp_data_sat);

/** @brief Convert gyro temperature data from sensor coordinate frame to satellite coordinate frame
 *  @param[in]  sds_gyro_temp_data_t     *p_gyro_temp_data
 *  @param[out] sds_gyro_temp_data_sat_t *p_gyro_temp_data_sat */
void sds_conv_gyro_temp_data_to_sat_frame(sds_gyro_temp_data_t const * const p_gyro_temp_data, sds_gyro_temp_data_sat_t * const p_gyro_temp_data_sat);

/** @brief Lock access to a sensor. Logs an error in case of unsuccessful lock.
 *  @param[in]  sensor_data_sensors_t s_type - the sensor type to lock access to
 *  @retval true - on lock success
 *  @retval false - on lock failure
 *  */
bool sds_sens_lock(sensor_data_sensors_t s_type);

/** @brief Unlock access to a sensor. Logs an error in case of unsuccessful unlock.
 *  @param[in]  sensor_data_sensors_t s_type - the sensor type to unlock
 *  @retval true - on unlock success
 *  @retval false - on unlock failure
 *  */
bool sds_sens_release(sensor_data_sensors_t s_type);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __IF_SENSOR_DATA_SERVICE_H__
/* ******************************************************************************************* */
