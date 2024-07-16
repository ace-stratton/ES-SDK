/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup sds
 * @{
 *
 * @file     sensor_data_cfg.c
 * @brief    Sensor Data user configuration source
 *
 * @}
*/

#include <string.h>

#include "sensor_mag_cfg.h"
#include "sensor_gyro_cfg.h"
#include "sensor_css_cfg.h"
#include "sensor_acc_cfg.h"
#include "sensor_temp_cfg.h"

#include "sensor_data_cfg.h"
#include "sensor_data_service.h"

#include "datacache.h"
#include "nvm/inc/nvm.h"

#include "assertions.h"

#include "fp/SDS/v0.3/SDS_server/FP_SDSProtocolTypes.h"

/**********************************************************************
 *
 * External type definitions
 *
 **********************************************************************/
/** @brief Collection of the sensors base configuration
 *
 *  @note .freq_cfg_id is one of the sensor type config enum used to configure the sampling frequency - check sds.fidl for further information
 *  */
const sensor_base_cfg_t sensor_base_cfg[SENSOR_COUNT] =
{
		{
				.sensor_id = SENSOR_MAG_PRIMARY,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_MAG_PRIMARY_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_ES_ADCS_SENSOR_MAG_PRIMARY_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t),
				.sens_if = &prim_mag_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_MTM,
		},
		{
				.sensor_id = SENSOR_MAG_SECONDARY,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_MAG_SECONDARY_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_ES_ADCS_SENSOR_MAG_SECONDARY_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t),
				.sens_if = &sec_mag_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_MTM,
		},
		{
				.sensor_id = SENSOR_GYRO,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_GYRO_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_GYRO_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_ES_ADCS_SENSOR_GYRO_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t),
				.sens_if = &gyro_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_GYRO,
		},
		{
				.sensor_id = SENSOR_CSS,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_COARSE_SUN_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_COARSE_SUN_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_ES_ADCS_SENSOR_CSS_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_ES_ADCS_SENSOR_CSS_t),
				.sens_if = &css_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_CSS,
		},
		{
				.sensor_id = SENSOR_ACC_PRIMARY,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_ACC_PRIMARY_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t),
				.sens_if = &prim_acc_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_ACC,
		},
		{
				.sensor_id = SENSOR_ACC_SECONDARY,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_ACC_SECONDARY_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t),
				.sens_if = &sec_acc_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_ACC,
		},
		{
				.sensor_id = SENSOR_PANEL_TEMP,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_PANEL_TEMP_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_SENSOR_PANEL_TEMP_SAT_FRAME_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t),
				.sens_if = &panel_temp_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP,
		},
		{
				.sensor_id = SENSOR_GYRO_TEMP,
				.dc_did_id_SI_sens_frame = (uint16_t)DC_DID_SENSOR_GYRO_TEMP_DATA,
				.dc_did_id_SI_sens_frame_size = sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_t),
				.dc_did_id_SI_sat_frame = (uint16_t)DC_DID_SENSOR_GYRO_TEMP_SAT_FRAME_DATA,
				.dc_did_id_SI_sat_frame_size = sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t),
				.sens_if = &gyro_temp_base_if,
				.freq_cfg_id = SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP,
		},
};

/** @brief Primary Magnetometer data configuration */
const sensor_mag_data_cfg_t sensor_prim_mag_data_cfg =
{
		.sens_mag_data_if = &mag_data_prim_if,
};

/** @brief Secondary Magnetometer data configuration */
const sensor_mag_data_cfg_t sensor_sec_mag_data_cfg =
{
		.sens_mag_data_if = &mag_data_sec_if,
};

/** @brief Gyroscopes data configuration */
const sensor_gyro_data_cfg_t sensor_gyro_data_cfg =
{
		.sens_gyro_data_if = &gyro_data_if,
};

/** @brief CSS data configuration */
const sensor_css_data_cfg_t sensor_css_data_cfg =
{
		.sens_css_data_if = &css_data_if,
};

/** @brief Primary Accelerometer data configuration */
const sensor_acc_data_cfg_t sensor_prim_acc_data_cfg =
{
		.sens_acc_data_if = &acc_data_prim_if,
};

/** @brief Secondary Accelerometer data configuration */
const sensor_acc_data_cfg_t sensor_sec_acc_data_cfg =
{
		.sens_acc_data_if = &acc_data_sec_if,
};

/** @brief Panel Temperature Sensors data configuration */
const sensor_panel_temp_data_cfg_t sensor_panel_temp_data_cfg =
{
		.sens_panel_temp_data_if = &panel_temp_data_if,
};

/** @brief Gyroscopes Temperature Sensors data configuration */
const sensor_gyro_temp_data_cfg_t sensor_gyro_temp_data_cfg =
{
		.sens_gyro_temp_data_if = &gyro_temp_data_if,
};

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
sds_op_status_t sds_get_sensor_data(sensor_data_sensors_t sens_type, sds_all_sens_data_t * const p_sens_data,
								sds_all_sens_data_sat_step_t * const p_sens_data_sat, const void **p_sens_data_mem,
								const void **p_sens_data_sat_mem)
{
	CRIT_ASSERT(sens_type < SENSOR_COUNT);
	CRIT_ASSERT(p_sens_data != NULL);
	CRIT_ASSERT(p_sens_data_sat != NULL);

	sds_op_status_t op_res;

	switch (sens_type)
	{
	case SENSOR_MAG_PRIMARY:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_prim_mag_data_cfg.sens_mag_data_if->get_mag_data(&p_sens_data->mag_data_prim)) )
		{
			memcpy(&p_sens_data_sat->mag_data_prim.mag_data_prev, &p_sens_data_sat->mag_data_prim.mag_data_curr, sizeof(sds_mag_data_sat_t));

			sds_conv_mag_data_to_sat_frame(&p_sens_data->mag_data_prim, SDS_MAG_ENUM_PRIM, &p_sens_data_sat->mag_data_prim.mag_data_curr);
		}

		*p_sens_data_mem = &p_sens_data->mag_data_prim;
		*p_sens_data_sat_mem = &p_sens_data_sat->mag_data_prim;

		break;
	case SENSOR_MAG_SECONDARY:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_sec_mag_data_cfg.sens_mag_data_if->get_mag_data(&p_sens_data->mag_data_sec)) )
		{
			memcpy(&p_sens_data_sat->mag_data_sec.mag_data_prev, &p_sens_data_sat->mag_data_sec.mag_data_curr, sizeof(sds_mag_data_sat_t));

			sds_conv_mag_data_to_sat_frame(&p_sens_data->mag_data_sec, SDS_MAG_ENUM_SEC, &p_sens_data_sat->mag_data_sec.mag_data_curr);
		}

		*p_sens_data_mem = &p_sens_data->mag_data_sec;
		*p_sens_data_sat_mem = &p_sens_data_sat->mag_data_sec;

		break;
	case SENSOR_GYRO:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_gyro_data_cfg.sens_gyro_data_if->get_gyro_data(&p_sens_data->gyro_data)) )
		{
			memcpy(&p_sens_data_sat->gyro_data.gyro_data_prev, &p_sens_data_sat->gyro_data.gyro_data_curr, sizeof(sds_gyro_data_sat_t));

			sds_conv_gyro_data_to_sat_frame(&p_sens_data->gyro_data, &p_sens_data_sat->gyro_data.gyro_data_curr);
		}

		*p_sens_data_mem = &p_sens_data->gyro_data;
		*p_sens_data_sat_mem = &p_sens_data_sat->gyro_data;

		break;
	case SENSOR_CSS:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_css_data_cfg.sens_css_data_if->get_css_data(&p_sens_data->css_data)) )
		{
			memcpy(&p_sens_data_sat->css_data.css_data_prev, &p_sens_data_sat->css_data.css_data_curr, sizeof(sds_css_data_sat_t));

			sds_conv_css_data_to_sat_frame(&p_sens_data->css_data, &p_sens_data_sat->css_data.css_data_curr);
		}

		*p_sens_data_mem = &p_sens_data->css_data;
		*p_sens_data_sat_mem = &p_sens_data_sat->css_data;

		break;

	case SENSOR_ACC_PRIMARY:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_prim_acc_data_cfg.sens_acc_data_if->get_acc_data(&p_sens_data->acc_data_prim)) )
		{
			memcpy(&p_sens_data_sat->acc_data_prim.acc_data_prev, &p_sens_data_sat->acc_data_prim.acc_data_curr, sizeof(sds_acc_data_sat_t));

			sds_conv_acc_data_to_sat_frame(&p_sens_data->acc_data_prim, SDS_ACC_ENUM_PRIM, &p_sens_data_sat->acc_data_prim.acc_data_curr);
		}

		*p_sens_data_mem = &p_sens_data->acc_data_prim;
		*p_sens_data_sat_mem = &p_sens_data_sat->acc_data_prim;

		break;

	case SENSOR_ACC_SECONDARY:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_sec_acc_data_cfg.sens_acc_data_if->get_acc_data(&p_sens_data->acc_data_sec)) )
		{
			memcpy(&p_sens_data_sat->acc_data_sec.acc_data_prev, &p_sens_data_sat->acc_data_sec.acc_data_curr, sizeof(sds_acc_data_sat_t));

			sds_conv_acc_data_to_sat_frame(&p_sens_data->acc_data_sec, SDS_ACC_ENUM_SEC, &p_sens_data_sat->acc_data_sec.acc_data_curr);
		}

		*p_sens_data_mem = &p_sens_data->acc_data_sec;
		*p_sens_data_sat_mem = &p_sens_data_sat->acc_data_sec;

		break;

	case SENSOR_PANEL_TEMP:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_panel_temp_data_cfg.sens_panel_temp_data_if->get_panel_temp_data(&p_sens_data->panel_temp_data)) )
		{
			sds_conv_panel_temp_data_to_sat_frame(&p_sens_data->panel_temp_data, &p_sens_data_sat->panel_temp_data);
		}

		*p_sens_data_mem = &p_sens_data->panel_temp_data;
		*p_sens_data_sat_mem = &p_sens_data_sat->panel_temp_data;

		break;

	case SENSOR_GYRO_TEMP:
		if ( SDS_OP_STATUS_OK == (op_res = sensor_gyro_temp_data_cfg.sens_gyro_temp_data_if->get_gyro_temp_data(&p_sens_data->gyro_temp_data)) )
		{
			sds_conv_gyro_temp_data_to_sat_frame(&p_sens_data->gyro_temp_data, &p_sens_data_sat->gyro_temp_data);
		}

		*p_sens_data_mem = &p_sens_data->gyro_temp_data;
		*p_sens_data_sat_mem = &p_sens_data_sat->gyro_temp_data;

		break;

	default:

		op_res = SDS_OP_STATUS_FAIL;

		break;
	}

	return op_res;
}
