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
 * @file     sensor_temp_cfg.c
 * @brief    Panel temperature sensors integration with the SDS source
 *
 * @}
*/

#include "MCU_Init.h"
#include "panels.h"

#include "sensor_css_cfg.h"
#include "sensor_data_dbg.h"

#include "es_exeh.h"
#include "assertions.h"

/** @brief CSS error code - no CSS error reported */
#define SDS_CSS_ERR_CODE_NO_ERR (0)

/** @brief CSS error code - a CSS error during read has occurred */
#define SDS_CSS_ERR_CODE_ERR    (1)

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief Cache status of the CSS  */
static sds_sensor_status_t css_sens_status;

/** @brief Cache error code of the CSS */
static uint8_t css_err_code;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
STATIC sds_op_status_t sensor_css_get_data_raw(sds_css_data_t * const p_data_dst);
STATIC sds_op_status_t sensor_css_init(void);
STATIC sds_op_status_t sensor_css_deinit(void);
STATIC sds_sensor_status_t sensor_css_get_state(void);
STATIC uint8_t sensor_css_get_last_error(void);
STATIC sds_op_status_t sensor_css_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value);
STATIC sds_op_status_t sensor_css_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value);

/**********************************************************************
 *
 * External type definitions
 *
 **********************************************************************/
sds_css_data_if_t css_data_if = {
		.get_css_data = sensor_css_get_data_raw,
};

sds_if_t css_base_if = {
		.init = sensor_css_init,
		.deinit = sensor_css_deinit,
		.get_state = sensor_css_get_state,
		.get_last_error = sensor_css_get_last_error,
		.set_reg = sensor_css_set_register,
		.get_reg = sensor_css_get_register
};

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Get raw data from the CSS sensors
 *  @param[out] sds_css_data_t * const p_data_dst
 *  @return     sds_op_status_t
 *  @note The so far used Panel_GetPhotodiodesLum() function stores the read data in a global and has no return status.
 *  Therefore we reimplement the same logic here */
STATIC sds_op_status_t sensor_css_get_data_raw(sds_css_data_t * const p_data_dst)
{
	CRIT_ASSERT(NULL != p_data_dst);

	uint16_t css_raw_data[MAX_PAN] = { 0, 0, 0, 0, 0, 0 };

	for (uint8_t i = 0; i < MAX_PAN; i++)
	{
		if ( Pan_PD_ADC_Measure(i, &(css_raw_data[i])) != SEN_SUCCESS )
		{
			css_err_code = SDS_CSS_ERR_CODE_ERR;
		}
	}

	p_data_dst->css_1_adc = css_raw_data[0];
	p_data_dst->css_2_adc = css_raw_data[1];
	p_data_dst->css_3_adc = css_raw_data[2];
	p_data_dst->css_4_adc = css_raw_data[3];
	p_data_dst->css_5_adc = css_raw_data[4];
	p_data_dst->css_6_adc = css_raw_data[5];

	SDS_TRACE_DBG("%s CSS RAW DATA---1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d\r", SDS_DBG_HEAD,
			p_data_dst->css_1_adc, p_data_dst->css_2_adc, p_data_dst->css_3_adc,
			p_data_dst->css_4_adc, p_data_dst->css_5_adc, p_data_dst->css_6_adc);

	return SDS_OP_STATUS_OK;
}

/** @brief Initialise the coarse sun sensors
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_css_init(void)
{
	MCU_SunSensInit();

	css_sens_status = SDS_SENSOR_STATUS_INIT;

	css_err_code = SDS_CSS_ERR_CODE_NO_ERR;

	return SDS_OP_STATUS_OK;
}

/** @brief Deinitialise the coarse sun sensors
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_css_deinit(void)
{
	MCU_SunSensDeInit();

	css_sens_status = SDS_SENSOR_STATUS_DEINIT;

	return SDS_OP_STATUS_OK;
}

/** @brief Get the coarse sun sensors status
 *  @return sds_sensor_status_t */
STATIC sds_sensor_status_t sensor_css_get_state(void)
{
	return css_sens_status;
}

/** @brief Get the last coarse sun sensors reported error
 *  @return uint8_t */
STATIC uint8_t sensor_css_get_last_error(void)
{
	return css_err_code;
}

/** @brief Get a register from the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t *reg_value - pointer to memory to populate with the read register value
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_css_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value)
{
	CRIT_ASSERT(sens_axis < SDS_SENS_AXIS_NUM);
	CRIT_ASSERT(NULL != reg_value);

	(void)sens_id;
	(void)sens_axis;
	(void)reg_address;
	(void)reg_value;

	// Nothing to implement here

	return SDS_OP_STATUS_FAIL;
}

/** @brief Set a register of the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t reg_value - the register value to be written
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_css_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value)
{
	CRIT_ASSERT(sens_axis < SDS_SENS_AXIS_NUM);

	(void)sens_id;
	(void)sens_axis;
	(void)reg_address;
	(void)reg_value;

	// Nothing to implement here

	return SDS_OP_STATUS_FAIL;
}

/* ******************************************************************************************* */
