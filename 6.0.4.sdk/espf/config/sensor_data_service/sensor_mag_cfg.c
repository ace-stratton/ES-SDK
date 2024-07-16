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
 * @file     sensor_mag_cfg.c
 * @brief    Magnetometer integration with the SDS source
 *
 * @}
*/

#include "LIS3MDL_MAG_driver.h"
#include "MCU_Init.h"

#include "sensor_mag_cfg.h"
#include "sensor_data_dbg.h"

#include "es_exeh.h"
#include "assertions.h"

/** @brief Magnetometer conversion constant */
#define LIS3MDL_4GAUSS_LSB  ((double)(1.00/6842.00))

/** @brief Magnetometer error code - no magnetometer error reported */
#define SDS_MTM_ERR_CODE_NO_ERR (0)

/** @brief Magnetomter error code - a magnetometer error during read has occurred */
#define SDS_MTM_ERR_CODE_ERR    (1)

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief Cache status of the primary magnetometer  */
static sds_sensor_status_t prim_mag_sens_status;

/** @brief Cache error code of the primary magnetometer */
static uint8_t prim_mag_err_code;

/** @brief Cache status of the secondary magnetometer  */
static sds_sensor_status_t sec_mag_sens_status;

/** @brief Cache error code of the secondary magnetometer */
static uint8_t sec_mag_err_code;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
STATIC sds_op_status_t sensor_mag_prim_get_data_in_uT(sds_mag_data_t * const p_data_dst);
STATIC sds_op_status_t sensor_mag_sec_get_data_in_uT(sds_mag_data_t * const p_data_dst);
STATIC sds_op_status_t sensor_mag_conv_raw_data_to_uT(uint8_t const * const p_raw_data, sds_mag_data_t * const p_data_dst);

STATIC sds_op_status_t sensor_mag_prim_init(void);
STATIC sds_op_status_t sensor_mag_prim_deinit(void);
STATIC sds_sensor_status_t sensor_mag_prim_get_state(void);
STATIC uint8_t sensor_mag_prim_get_last_error(void);

STATIC sds_op_status_t sensor_mag_sec_init(void);
STATIC sds_op_status_t sensor_mag_sec_deinit(void);
STATIC sds_sensor_status_t sensor_mag_sec_get_state(void);
STATIC uint8_t sensor_mag_sec_get_last_error(void);

STATIC sds_op_status_t sensor_mag_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value);
STATIC sds_op_status_t sensor_mag_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value);

/**********************************************************************
 *
 * External type definitions
 *
 **********************************************************************/
sds_mag_data_if_t mag_data_prim_if = {
		.get_mag_data = sensor_mag_prim_get_data_in_uT,
};

sds_mag_data_if_t mag_data_sec_if = {
		.get_mag_data = sensor_mag_sec_get_data_in_uT,
};

sds_if_t prim_mag_base_if = {
		.init = sensor_mag_prim_init,
		.deinit = sensor_mag_prim_deinit,
		.get_state = sensor_mag_prim_get_state,
		.get_last_error = sensor_mag_prim_get_last_error,
		.get_reg = sensor_mag_get_register,
		.set_reg = sensor_mag_set_register
};

sds_if_t sec_mag_base_if = {
		.init = sensor_mag_sec_init,
		.deinit = sensor_mag_sec_deinit,
		.get_state = sensor_mag_sec_get_state,
		.get_last_error = sensor_mag_sec_get_last_error,
		.get_reg = sensor_mag_get_register,
		.set_reg = sensor_mag_set_register
};

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Gets the data from the primary magnetometer and converts it in uT
 *  @param[out] sds_mag_data_t * const p_data_dst
 *  @return     sds_op_status_t */
STATIC sds_op_status_t sensor_mag_prim_get_data_in_uT(sds_mag_data_t * const p_data_dst)
{
	CRIT_ASSERT(p_data_dst != NULL);

	uint8_t regValue[6] = {0, 0, 0, 0, 0, 0};

	if ( SEN_SUCCESS != LIS3MDL_MAG_Get_Magnetic(LIS3MDL_MAG_I2C_ADDRESS_LOW, (uint8_t*)regValue ) )
	{
		prim_mag_sens_status = SDS_SENSOR_STATUS_ERR;

		prim_mag_err_code = SDS_MTM_ERR_CODE_ERR;

		return SDS_OP_STATUS_FAIL;
	}

	return sensor_mag_conv_raw_data_to_uT(&regValue[0], p_data_dst);
}

/** @brief Gets the data from the secondary magnetometer and converts it in uT
 *  @param[out] sds_mag_data_t * const p_data_dst
 *  @return     sds_op_status_t */
STATIC sds_op_status_t sensor_mag_sec_get_data_in_uT(sds_mag_data_t * const p_data_dst)
{
	CRIT_ASSERT(p_data_dst != NULL);

	uint8_t regValue[6] = {0, 0, 0, 0, 0, 0};

	if ( SEN_SUCCESS != LIS3MDL_MAG_Get_Magnetic(LIS3MDL_MAG_I2C_ADDRESS_HIGH, (uint8_t*)regValue ) )
	{
		sec_mag_sens_status = SDS_SENSOR_STATUS_ERR;

		sec_mag_err_code = SDS_MTM_ERR_CODE_ERR;

		return SDS_OP_STATUS_FAIL;
	}

	return sensor_mag_conv_raw_data_to_uT(&regValue[0], p_data_dst);
}

/** @brief Gets the data from the magnetometer and converts it in uT
 *  @param[in]  uint8_t        * const p_raw_data
 *  @param[out] sds_mag_data_t * const p_data_dst
 *  @return     sds_op_status_t */
STATIC sds_op_status_t sensor_mag_conv_raw_data_to_uT(uint8_t const * const p_raw_data, sds_mag_data_t * const p_data_dst)
{
	CRIT_ASSERT(NULL != p_raw_data);
	CRIT_ASSERT(NULL != p_data_dst);

	int16_t DataRaw[3];
	uint16_t DataRawTmp[3]; // Necessary to fix MISRA C 2004, 10.5
	sds_mag_data_t mag_data_uT;

	/* Format the data */
	DataRawTmp[0] = (uint16_t)p_raw_data[1]; // Necessary to fix MISRA C 2004, 10.5
	DataRawTmp[1] = (uint16_t)p_raw_data[3];
	DataRawTmp[2] = (uint16_t)p_raw_data[5];

	DataRaw[0] = (int16_t)( ( (uint16_t)(DataRawTmp[0] << 8) ) + p_raw_data[0] );
	DataRaw[1] = (int16_t)( ( (uint16_t)(DataRawTmp[1] << 8) ) + p_raw_data[2] );
	DataRaw[2] = (int16_t)( ( (uint16_t)(DataRawTmp[2] << 8) ) + p_raw_data[4] );

	SDS_TRACE_DBG("%s MTM RAW DATA---X:%d, Y:%d, Z:%d\r", SDS_DBG_HEAD, DataRaw[0], DataRaw[1], DataRaw[2]);

	/* Convert to uT */
	mag_data_uT.mag_x_uT = (int32_t)( ( DataRaw[0] * LIS3MDL_4GAUSS_LSB ) * 100U );
	mag_data_uT.mag_y_uT = (int32_t)( ( DataRaw[1] * LIS3MDL_4GAUSS_LSB ) * 100U );
	mag_data_uT.mag_z_uT = (int32_t)( ( DataRaw[2] * LIS3MDL_4GAUSS_LSB ) * 100U );

	SDS_TRACE_DBG("%s MTM CONV DATA---X:%d, Y:%d, Z:%d\r", SDS_DBG_HEAD, mag_data_uT.mag_x_uT, mag_data_uT.mag_y_uT, mag_data_uT.mag_z_uT);

	/* Copy to destination buffer */
	*p_data_dst = mag_data_uT;

	return SDS_OP_STATUS_OK;
}

/** @brief Initialise the primary magnetometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_mag_prim_init(void)
{
	MCU_MagnetometersInit();

	prim_mag_sens_status = SDS_SENSOR_STATUS_INIT;

	prim_mag_err_code = SDS_MTM_ERR_CODE_NO_ERR;

	return SDS_OP_STATUS_OK;
}

/** @brief Deinitialise the primary magnetometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_mag_prim_deinit(void)
{
	MCU_MagnetometersDeInit();

	prim_mag_sens_status = SDS_SENSOR_STATUS_DEINIT;

	return SDS_OP_STATUS_OK;
}

/** @brief Get the primary magnetometer status
 *  @return sds_sensor_status_t */
STATIC sds_sensor_status_t sensor_mag_prim_get_state(void)
{
	return prim_mag_sens_status;
}

/** @brief Get the last primary magnetometer reported error
 *  @return uint8_t */
STATIC uint8_t sensor_mag_prim_get_last_error(void)
{
	return prim_mag_err_code;
}

/** @brief Initialise the secondary magnetometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_mag_sec_init(void)
{
	MCU_MagnetometersInit();

	sec_mag_sens_status = SDS_SENSOR_STATUS_INIT;

	sec_mag_err_code = SDS_MTM_ERR_CODE_NO_ERR;

	return SDS_OP_STATUS_OK;
}

/** @brief Deinitialise the secondary magnetometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_mag_sec_deinit(void)
{
	MCU_MagnetometersDeInit();

	sec_mag_sens_status = SDS_SENSOR_STATUS_DEINIT;

	return SDS_OP_STATUS_OK;
}

/** @brief Get the secondary magnetometer status
 *  @return sds_sensor_status_t */
STATIC sds_sensor_status_t sensor_mag_sec_get_state(void)
{
	return sec_mag_sens_status;
}

/** @brief Get the last secondary magnetometer reported error
 *  @return uint8_t */
STATIC uint8_t sensor_mag_sec_get_last_error(void)
{
	return sec_mag_err_code;
}

/** @brief Get a register from the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t *reg_value - pointer to memory to populate with the read register value
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_mag_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value)
{
	CRIT_ASSERT(sens_id < SDS_MAG_NUM);
	CRIT_ASSERT(NULL != reg_value);

	(void)sens_axis;

	sds_op_status_t ret_val = SDS_OP_STATUS_OK;

	uint8_t i2c_addr = (sens_id == SDS_MAG_ENUM_PRIM ? LIS3MDL_MAG_I2C_ADDRESS_LOW : LIS3MDL_MAG_I2C_ADDRESS_HIGH);

	if ( SEN_SUCCESS != LIS3MDL_MAG_ReadReg(i2c_addr, (uint8_t)reg_address, (uint8_t *) reg_value) )
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
STATIC sds_op_status_t sensor_mag_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value)
{
	CRIT_ASSERT(sens_id < SDS_MAG_NUM);

	(void)sens_axis;

	sds_op_status_t ret_val = SDS_OP_STATUS_OK;

	uint8_t i2c_addr = (sens_id == SDS_MAG_ENUM_PRIM ? LIS3MDL_MAG_I2C_ADDRESS_LOW : LIS3MDL_MAG_I2C_ADDRESS_HIGH);

	if ( SEN_SUCCESS != LIS3MDL_MAG_WriteReg(i2c_addr, (uint8_t)reg_address, (uint8_t) reg_value) )
	{
		ret_val = SDS_OP_STATUS_FAIL;
	}

	return ret_val;
}

/* ******************************************************************************************* */
