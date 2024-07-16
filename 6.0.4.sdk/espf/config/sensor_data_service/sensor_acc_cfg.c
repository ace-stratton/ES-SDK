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
 * @brief    Accelerometer integration with the SDS source
 *
 * @}
*/

#include "ais328dq_driver.h"
#include "MCU_Init.h"

#include "sensor_acc_cfg.h"
#include "sensor_data_dbg.h"

#include "es_exeh.h"
#include "assertions.h"

#include "CommandsApi.h"

/** @brief Accelerometer "constant" - given as 0.98 mg/digit typical */
#define AIS328_CONST  ((double)(0.98))

/** @brief Accelerometer error code - no Accelerometer error reported */
#define SDS_ACC_ERR_CODE_NO_ERR (0)

/** @brief Accelerometer error code - a Accelerometer error during read has occurred */
#define SDS_ACC_ERR_CODE_ERR    (1)

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief Cache status of the primary accelerometer  */
static sds_sensor_status_t prim_acc_sens_status;

/** @brief Cache error code of the primary accelerometer */
static uint8_t prim_acc_err_code;

/** @brief Cache status of the secondary accelerometer  */
static sds_sensor_status_t sec_acc_sens_status;

/** @brief Cache error code of the secondary accelerometer */
static uint8_t sec_acc_err_code;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
STATIC sds_op_status_t sensor_acc_prim_get_data_in_mg(sds_acc_data_t * const p_data_dst);
STATIC sds_op_status_t sensor_acc_sec_get_data_in_mg(sds_acc_data_t * const p_data_dst);
STATIC sds_op_status_t sensor_acc_conv_raw_data_to_mg(AxesRaw_t const * p_raw_data, sds_acc_data_t * const p_data_dst);

STATIC sds_op_status_t sensor_acc_prim_init(void);
STATIC sds_op_status_t sensor_acc_prim_deinit(void);
STATIC sds_sensor_status_t sensor_acc_prim_get_state(void);
STATIC uint8_t sensor_acc_prim_get_last_error(void);

STATIC sds_op_status_t sensor_acc_sec_init(void);
STATIC sds_op_status_t sensor_acc_sec_deinit(void);
STATIC sds_sensor_status_t sensor_acc_sec_get_state(void);
STATIC uint8_t sensor_acc_sec_get_last_error(void);

STATIC sds_op_status_t sensor_acc_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value);
STATIC sds_op_status_t sensor_acc_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value);

/**********************************************************************
 *
 * External type definitions
 *
 **********************************************************************/
sds_acc_data_if_t acc_data_prim_if = {
		.get_acc_data = sensor_acc_prim_get_data_in_mg,
};

sds_acc_data_if_t acc_data_sec_if = {
		.get_acc_data = sensor_acc_sec_get_data_in_mg,
};

sds_if_t prim_acc_base_if = {
		.init = sensor_acc_prim_init,
		.deinit = sensor_acc_prim_deinit,
		.get_state = sensor_acc_prim_get_state,
		.get_last_error = sensor_acc_prim_get_last_error,
		.set_reg = sensor_acc_set_register,
		.get_reg = sensor_acc_get_register
};

sds_if_t sec_acc_base_if = {
		.init = sensor_acc_sec_init,
		.deinit = sensor_acc_sec_deinit,
		.get_state = sensor_acc_sec_get_state,
		.get_last_error = sensor_acc_sec_get_last_error,
		.set_reg = sensor_acc_set_register,
		.get_reg = sensor_acc_get_register
};

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Gets the data from the primary accelerometer and converts it to mg
 *  @param[out] sds_acc_data_t * const p_data_dst
 *  @return     sds_op_status_t */
STATIC sds_op_status_t sensor_acc_prim_get_data_in_mg(sds_acc_data_t * const p_data_dst)
{
	CRIT_ASSERT(p_data_dst != NULL);

	AxesRaw_t axesValues = {
			.AXIS_X = 0,
			.AXIS_Y = 0,
			.AXIS_Z = 0
	};

	if ( SEN_SUCCESS != AIS328DQ_GetAccAxesRaw(AIS328DQ_1_MEMS_I2C_ADDRESS, &axesValues) )
	{
		prim_acc_sens_status = SDS_SENSOR_STATUS_ERR;

		prim_acc_err_code = SDS_ACC_ERR_CODE_ERR;

		return SDS_OP_STATUS_FAIL;
	}

	return sensor_acc_conv_raw_data_to_mg(&axesValues, p_data_dst);
}

/** @brief Gets the data from the secondary accelerometer and converts it to mg
 *  @param[out] sds_acc_data_t * const p_data_dst
 *  @return     sds_op_status_t */
STATIC sds_op_status_t sensor_acc_sec_get_data_in_mg(sds_acc_data_t * const p_data_dst)
{
	CRIT_ASSERT(p_data_dst != NULL);

	AxesRaw_t axesValues = {
			.AXIS_X = 0,
			.AXIS_Y = 0,
			.AXIS_Z = 0
	};

	if ( SEN_SUCCESS != AIS328DQ_GetAccAxesRaw(AIS328DQ_2_MEMS_I2C_ADDRESS, &axesValues) )
	{
		prim_acc_sens_status = SDS_SENSOR_STATUS_ERR;

		prim_acc_err_code = SDS_ACC_ERR_CODE_ERR;

		return SDS_OP_STATUS_FAIL;
	}

	return sensor_acc_conv_raw_data_to_mg(&axesValues, p_data_dst);
}

/** @brief Gets the data from the accelerometer and converts it in mg
 *  @param[in]  AxesRaw_t      * const p_raw_data
 *  @param[out] sds_mag_data_t * const p_data_dst
 *  @return     sds_op_status_t */
STATIC sds_op_status_t sensor_acc_conv_raw_data_to_mg(AxesRaw_t const * p_raw_data, sds_acc_data_t * const p_data_dst)
{
	CRIT_ASSERT(NULL != p_raw_data);
	CRIT_ASSERT(NULL != p_data_dst);

	sds_acc_data_t acc_data_mg;

	SDS_TRACE_DBG("%s ACC RAW DATA---X:%d, Y:%d, Z:%d\r", SDS_DBG_HEAD, p_raw_data->AXIS_X, p_raw_data->AXIS_Y, p_raw_data->AXIS_Z);

	/* Convert to mg */
	acc_data_mg.acc_x_mg = (int32_t)( ( p_raw_data->AXIS_X * AIS328_CONST ) );
	acc_data_mg.acc_y_mg = (int32_t)( ( p_raw_data->AXIS_Y * AIS328_CONST ) );
	acc_data_mg.acc_z_mg = (int32_t)( ( p_raw_data->AXIS_Z * AIS328_CONST ) );

	SDS_TRACE_DBG("%s ACC CONV DATA---X:%d, Y:%d, Z:%d\r", SDS_DBG_HEAD, acc_data_mg.acc_x_mg, acc_data_mg.acc_y_mg, acc_data_mg.acc_z_mg);

	/* Copy to destination buffer */
	*p_data_dst = acc_data_mg;

	return SDS_OP_STATUS_OK;
}

/** @brief Initialise the primary accelerometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_acc_prim_init(void)
{
	TODO("This initialises both accelerometers, but we need to initialise only the primary")

	MCU_AccelerometersInit();

	prim_acc_sens_status = SDS_SENSOR_STATUS_INIT;

	prim_acc_err_code = SDS_ACC_ERR_CODE_NO_ERR;

	return SDS_OP_STATUS_OK;
}

/** @brief Deinitialise the primary accelerometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_acc_prim_deinit(void)
{
	TODO("This de-initialises both accelerometers, but we need to de-initialise only the primary")

	MCU_AccelerometersDeInit();

	prim_acc_sens_status = SDS_SENSOR_STATUS_DEINIT;

	return SDS_OP_STATUS_OK;
}

/** @brief Get the primary accelerometer status
 *  @return sds_sensor_status_t */
STATIC sds_sensor_status_t sensor_acc_prim_get_state(void)
{
	return prim_acc_sens_status;
}

/** @brief Get the last primary accelerometer reported error
 *  @return uint8_t */
STATIC uint8_t sensor_acc_prim_get_last_error(void)
{
	return prim_acc_err_code;
}

/** @brief Initialise the secondary accelerometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_acc_sec_init(void)
{
	TODO("This initialises both accelerometers, but we need to initialise only the primary")
	MCU_AccelerometersInit();

	sec_acc_sens_status = SDS_SENSOR_STATUS_INIT;

	sec_acc_err_code = SDS_ACC_ERR_CODE_NO_ERR;

	return SDS_OP_STATUS_OK;
}

/** @brief Deinitialise the secondary accelerometer
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_acc_sec_deinit(void)
{
	TODO("This de-initialises both accelerometers, but we need to de-initialise only the primary")

	MCU_AccelerometersDeInit();

	sec_acc_sens_status = SDS_SENSOR_STATUS_DEINIT;

	return SDS_OP_STATUS_OK;
}

/** @brief Get the secondary accelerometer status
 *  @return sds_sensor_status_t */
STATIC sds_sensor_status_t sensor_acc_sec_get_state(void)
{
	return sec_acc_sens_status;
}

/** @brief Get the last secondary accelerometer reported error
 *  @return uint8_t */
STATIC uint8_t sensor_acc_sec_get_last_error(void)
{
	return sec_acc_err_code;
}

/** @brief Get a register from the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t *reg_value - pointer to memory to populate with the read register value
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_acc_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value)
{
	CRIT_ASSERT(sens_id < SDS_ACC_NUM);
	CRIT_ASSERT(NULL != reg_value);

	sds_op_status_t op_res = SDS_OP_STATUS_OK;

	(void)sens_axis;

	uint8_t i2c_addr = ( sens_id == SDS_ACC_ENUM_PRIM ? AIS328DQ_1_MEMS_I2C_ADDRESS : AIS328DQ_2_MEMS_I2C_ADDRESS );

	if ( SEN_SUCCESS != AIS328DQ_ReadReg(i2c_addr, (uint8_t)reg_address, (uint8_t *) reg_value) )
	{
		op_res = SDS_OP_STATUS_FAIL;
	}

	return op_res;
}

/** @brief Set a register of the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t reg_value - the register value to be written
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_acc_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value)
{
	CRIT_ASSERT(sens_id < SDS_ACC_NUM);

	sds_op_status_t op_res = SDS_OP_STATUS_OK;

	(void)sens_axis;

	uint8_t i2c_addr = ( sens_id == SDS_ACC_ENUM_PRIM ? AIS328DQ_1_MEMS_I2C_ADDRESS : AIS328DQ_2_MEMS_I2C_ADDRESS );

	uint8_t reg_new_val = (uint8_t)(reg_value & 0xFFU);

	if ( SEN_SUCCESS != AIS328DQ_WriteReg(i2c_addr, (uint8_t)reg_address, reg_new_val) )
	{
		op_res = SDS_OP_STATUS_FAIL;
	}

	return op_res;
}
/* ******************************************************************************************* */
