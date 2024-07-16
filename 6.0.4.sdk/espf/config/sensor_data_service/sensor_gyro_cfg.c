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
 * @file     sensor_gyro_cfg.c
 * @brief    Gyroscopes integration with the SDS source
 *
 * @}
*/

#include "sensor_gyro_cfg.h"
#include "sensor_data_dbg.h"

#include "MCU_Init.h"
#include "panels.h"
#include "adis16265_driver.h"

#include "es_exeh.h"
#include "assertions.h"

/** @brief Gyroscope angular rate conversion constants: ADIS16260/16265 rate in deg/sec per 1 LSB */
#define SDS_GYRO_ANG_RATE_LSB          ((double)0.07326)

/** @brief This is what the 0 measurement of an ADIS16265 gyroscope is interpreted as inside an int32 variable */
#define SDS_GYRO_ZERO_VALUE            (16384)

/** @brief Gyroscope rad/s to urad/s conversion multiplier */
#define SDS_GYRO_URAD_MULT             (10e5)

/** @brief Gyroscope error code - no gyroscope error reported */
#define SDS_GYRO_ERR_CODE_GYRO_NO_ERR  (0)

/** @brief Gyroscope error code - a gyroscope error during read has occurred */
#define SDS_GYRO_ERR_CODE_GYRO_ERR     (1)

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief Cache status of the gyroscopes sensors */
static sds_sensor_status_t gyro_sens_status;

/** @brief Cache error code of the gyroscope */
static uint8_t gyro_err_code;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
STATIC sds_op_status_t sensor_gyro_init(void);
STATIC sds_op_status_t sensor_gyro_deinit(void);
STATIC sds_sensor_status_t sensor_gyro_get_state(void);
STATIC uint8_t sensor_gyro_get_last_error(void);
STATIC sds_op_status_t sensor_gyro_get_data_in_urad_per_s(sds_gyro_data_t * const p_data_dst);
STATIC int32_t sensor_gyro_conv_gyro_raw_axis_data_to_urad_s(int16_t raw_axis_data);
STATIC sds_op_status_t sensor_gyro_get_temp_data_in_deg_c(sds_gyro_temp_data_t * const p_data_dst);
STATIC sds_op_status_t sensor_gyro_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value);
STATIC sds_op_status_t sensor_gyro_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value);


/**********************************************************************
 *
 * External type definitions
 *
 **********************************************************************/
sds_if_t gyro_base_if = {
		.init = sensor_gyro_init,
		.deinit = sensor_gyro_deinit,
		.get_state = sensor_gyro_get_state,
		.get_last_error = sensor_gyro_get_last_error,
		.set_reg = sensor_gyro_set_register,
		.get_reg = sensor_gyro_get_register
};

sds_gyro_data_if_t gyro_data_if = {
		.get_gyro_data = sensor_gyro_get_data_in_urad_per_s,
};

sds_if_t gyro_temp_base_if = {
		.init = sensor_gyro_init,
		.deinit = sensor_gyro_deinit,
		.get_state = sensor_gyro_get_state,
		.get_last_error = sensor_gyro_get_last_error,
		.set_reg = sensor_gyro_set_register,
		.get_reg = sensor_gyro_get_register
};

sds_gyro_temp_data_if_t gyro_temp_data_if = {
		.get_gyro_temp_data = sensor_gyro_get_temp_data_in_deg_c,
};

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Gets the data for the gyroscopes
 *  @param[in] sds_gyro_data_t * const p_data_dst
 *  @return    sds_op_status_t */
STATIC sds_op_status_t sensor_gyro_get_data_in_urad_per_s(sds_gyro_data_t * const p_data_dst)
{
	CRIT_ASSERT(p_data_dst != NULL);

	AxesRaw_t raw_gyro_data;

	sds_op_status_t ret_res = SDS_OP_STATUS_FAIL;

	/* Get rate data from all gyroscopes */
	if ( GYRO_SUCCESS == ADIS16265_GetAxesRate(PANLE_GYROS_AXIS_ALL, &raw_gyro_data) )
	{
		SDS_TRACE_DBG("%s GYRO RAW ANG RATE---X:%d, Y:%d, Z:%d\r", SDS_DBG_HEAD, raw_gyro_data.AXIS_X, raw_gyro_data.AXIS_Y, raw_gyro_data.AXIS_Z);

		p_data_dst->gyro_1_urads = sensor_gyro_conv_gyro_raw_axis_data_to_urad_s(raw_gyro_data.AXIS_X);
		p_data_dst->gyro_2_urads = sensor_gyro_conv_gyro_raw_axis_data_to_urad_s(raw_gyro_data.AXIS_Y);
		p_data_dst->gyro_3_urads = sensor_gyro_conv_gyro_raw_axis_data_to_urad_s(raw_gyro_data.AXIS_Z);

		SDS_TRACE_DBG("%s GYRO CONV ANG RATE---X:%d, Y:%d, Z:%d\r", SDS_DBG_HEAD, p_data_dst->gyro_1_urads, p_data_dst->gyro_2_urads, p_data_dst->gyro_3_urads);

		gyro_sens_status = SDS_SENSOR_STATUS_INIT;
		gyro_err_code = SDS_GYRO_ERR_CODE_GYRO_NO_ERR;
		ret_res = SDS_OP_STATUS_OK;
	}
	else
	{
		gyro_sens_status = SDS_SENSOR_STATUS_ERR;
		gyro_err_code = SDS_GYRO_ERR_CODE_GYRO_ERR;

		SDS_TRACE_DBG("%s Gyroscopes read failed, please check last error\r", SDS_DBG_HEAD);
	}

	return ret_res;
}

/** @brief Gets the temperature data for the gyroscopes
 *  @param[in] sds_gyro_data_t * const p_data_dst
 *  @return    sds_op_status_t */
STATIC sds_op_status_t sensor_gyro_get_temp_data_in_deg_c(sds_gyro_temp_data_t * const p_data_dst)
{
	CRIT_ASSERT(p_data_dst != NULL);

	Temperature_t gyro_temp_data;

	sds_op_status_t ret_res = SDS_OP_STATUS_FAIL;

	if ( GYRO_SUCCESS == ADIS16265_GetTemperature(&gyro_temp_data) )
	{
		p_data_dst->gyro_1_deg_c = gyro_temp_data.Temp_X;
		p_data_dst->gyro_2_deg_c = gyro_temp_data.Temp_Y;
		p_data_dst->gyro_3_deg_c = gyro_temp_data.Temp_Z;

		SDS_TRACE_DBG("%s GYRO TEMP DEG C --- 1:%d, 2:%d, 3:%d\r", SDS_DBG_HEAD, p_data_dst->gyro_1_deg_c, p_data_dst->gyro_2_deg_c, p_data_dst->gyro_3_deg_c);

		gyro_sens_status = SDS_SENSOR_STATUS_INIT;
		gyro_err_code = SDS_GYRO_ERR_CODE_GYRO_NO_ERR;
		ret_res = SDS_OP_STATUS_OK;
	}
	else
	{
		gyro_sens_status = SDS_SENSOR_STATUS_ERR;
		gyro_err_code = SDS_GYRO_ERR_CODE_GYRO_ERR;

		SDS_TRACE_DBG("%s Gyroscopes read failed, please check last error\r", SDS_DBG_HEAD);
	}

	return ret_res;
}



/** @brief Initialise the gyroscope
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_gyro_init(void)
{
	MCU_GyrosInit();

	gyro_sens_status = SDS_SENSOR_STATUS_INIT;

	gyro_err_code = SDS_GYRO_ERR_CODE_GYRO_NO_ERR;

	return SDS_OP_STATUS_OK;
}

/** @brief Deinitialise the gyroscope
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_gyro_deinit(void)
{
	MCU_GyrosDeInit();

	gyro_sens_status = SDS_SENSOR_STATUS_DEINIT;

	return SDS_OP_STATUS_OK;
}

/** @brief Get the gyroscope status
 *  @return sds_sensor_status_t */
STATIC sds_sensor_status_t sensor_gyro_get_state(void)
{
	return gyro_sens_status;
}

/** @brief Get the last gyroscope reported error
 *  @return uint8_t */
STATIC uint8_t sensor_gyro_get_last_error(void)
{
	return gyro_err_code;
}

/** @brief Convert a single gyro axis raw rate data to urad/s
 *  @param[in] int16_t raw_axis_data - raw axis data
 *  @return    int32_t               - axis data in urad/s */
STATIC int32_t sensor_gyro_conv_gyro_raw_axis_data_to_urad_s(int16_t raw_axis_data)
{
	return (raw_axis_data <= ADIS16265_GYRO_OUT_POS_MAX_VAL) ?
			(int32_t)(((                       raw_axis_data  * + SDS_GYRO_ANG_RATE_LSB) * (M_PI / 180.0F)) * SDS_GYRO_URAD_MULT) :
			(int32_t)((((SDS_GYRO_ZERO_VALUE - raw_axis_data) * - SDS_GYRO_ANG_RATE_LSB) * (M_PI / 180.0F)) * SDS_GYRO_URAD_MULT);
}

/** @brief Get a register from the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t *reg_value - pointer to memory to populate with the read register value
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_gyro_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value)
{
	CRIT_ASSERT(sens_axis < SDS_SENS_AXIS_NUM);
	CRIT_ASSERT(NULL != reg_value);

	(void)sens_id;

	sds_op_status_t ret_val = SDS_OP_STATUS_OK;

	gyroscope_t *gyroscope_to_read_reg_from;

	gyroscope_t gyro_x;
	gyroscope_t gyro_y;
	gyroscope_t gyro_z;

	ADIS16265_get_full_gyro_info(&gyro_x, &gyro_y, &gyro_z);

	if ( sens_axis == SDS_SENS_AXIS_X )
	{
		gyroscope_to_read_reg_from = &gyro_x;
	}
	else if ( sens_axis == SDS_SENS_AXIS_Y)
	{
		gyroscope_to_read_reg_from = &gyro_y;
	}
	else
	{
		gyroscope_to_read_reg_from = &gyro_z;
	}

	if ( GYRO_SUCCESS != ADIS16265_ReadReg16(gyroscope_to_read_reg_from, (uint8_t)reg_address, (uint16_t *)reg_value) )
	{
		ret_val = SDS_OP_STATUS_FAIL;
	}

	return ret_val;
}

/** @brief Set a register of the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t reg_value - the register value to be written
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_gyro_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value)
{
	CRIT_ASSERT(sens_axis < SDS_SENS_AXIS_NUM);

	(void)sens_id;

	sds_op_status_t ret_val = SDS_OP_STATUS_OK;

	gyroscope_t *gyroscope_to_write_reg_to;

	gyroscope_t gyro_x;
	gyroscope_t gyro_y;
	gyroscope_t gyro_z;

	ADIS16265_get_full_gyro_info(&gyro_x, &gyro_y, &gyro_z);

	if ( sens_axis == SDS_SENS_AXIS_X )
	{
		gyroscope_to_write_reg_to = &gyro_x;
	}
	else if ( sens_axis == SDS_SENS_AXIS_Y)
	{
		gyroscope_to_write_reg_to = &gyro_y;
	}
	else
	{
		gyroscope_to_write_reg_to = &gyro_z;
	}

	if ( GYRO_SUCCESS != ADIS16265_WriteReg16(gyroscope_to_write_reg_to, (uint8_t)reg_address, (uint16_t)reg_value) )
	{
		ret_val = SDS_OP_STATUS_FAIL;
	}

	return ret_val;
}

/* ******************************************************************************************* */
