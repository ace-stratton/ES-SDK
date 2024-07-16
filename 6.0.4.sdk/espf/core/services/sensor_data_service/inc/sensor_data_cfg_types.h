/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __IF_SENSOR_DATA_CFG_TYPES_H__
#define __IF_SENSOR_DATA_CFG_TYPES_H__

/**
 * @addtogroup sds
 * @{
 *
 * @file     sensor_data_cfg_types.h
 * @brief    Sensor data configuration types. These types are to be used by the implementation that has to deal with user configuration
 *
 * @}
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "if_sensor_data_service.h"

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @typedef sensor_base_cfg_t
    @brief Sensor basic configuration */
typedef struct
{
	const uint8_t sensor_id;						/**< The sensor ID as defined in the configurable section */
	const uint16_t dc_did_id_SI_sens_frame;			/**< The Data Cache enum ID that needs to be updated with the sensor data, converted in SI units */
	const uint32_t dc_did_id_SI_sens_frame_size;	/**< The Data Cache enum ID size */
	const uint16_t dc_did_id_SI_sat_frame;			/**< The Data Cache enum ID that needs to be updated with the sensor data, converted in SI units and transformed in the satellite coordinate frame */
	const uint32_t dc_did_id_SI_sat_frame_size;		/**< The Data Cache enum ID size */
	const sds_if_t * const sens_if;					/**< The sensor ID as defined in the configurable section */
	const uint8_t freq_cfg_id;						/**< The frequency configuration relating to this sensor  */

} sensor_base_cfg_t;

/** @typedef sensor_mag_data_cfg_t
    @brief Magnetometer sensor data configuration */
typedef struct
{
	const sds_mag_data_if_t * const sens_mag_data_if;		 	/**< Pointer to magnetometer sensor data interface */

} sensor_mag_data_cfg_t;

/** @typedef sensor_gyro_data_cfg_t
    @brief Gyroscope sensor data configuration */
typedef struct
{
	const sds_gyro_data_if_t * const sens_gyro_data_if;		 	/**< Pointer to gyro sensor data interface */

} sensor_gyro_data_cfg_t;

/** @typedef sensor_css_data_cfg_t
    @brief CSS sensor data configuration */
typedef struct
{
	const sds_css_data_if_t * const sens_css_data_if;		 	/**< Pointer to css sensor data interface */

} sensor_css_data_cfg_t;

/** @typedef sensor_acc_data_cfg_t
    @brief Accelerometer sensor data configuration */
typedef struct
{
	const sds_acc_data_if_t * const sens_acc_data_if;		 	/**< Pointer to acc sensor data interface */

} sensor_acc_data_cfg_t;

/** @typedef sensor_panel_temp_data_cfg_t
    @brief Panel temperature sensors sensor data configuration */
typedef struct
{
	const sds_panel_temp_data_if_t * const sens_panel_temp_data_if;		 	/**< Pointer to panel temp sensor data interface */

} sensor_panel_temp_data_cfg_t;

/** @typedef sensor_gyro_temp_data_cfg_t
    @brief Gyroscopes temperature sensors sensor data configuration */
typedef struct
{
	const sds_gyro_temp_data_if_t * const sens_gyro_temp_data_if;		 	/**< Pointer to gyro temp sensor data interface */

} sensor_gyro_temp_data_cfg_t;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SENSOR_DATA_CFG_TYPES_H__

