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
 * @brief    Panel temperature sensors (PTS) integration with the SDS
 *
 * @}
*/

#include "MCU_Init.h"
#include "panels.h"

#include "sensor_temp_cfg.h"
#include "sensor_data_dbg.h"

#include "es_exeh.h"
#include "assertions.h"

/** @brief Panel temperature sensors error code - no error reported */
#define SDS_PANEL_TEMP_ERR_CODE_NO_ERR (0)

/** @brief Panel temperature sensors error code - read error has occurred */
#define SDS_PANEL_TEMP_ERR_CODE_ERR    (1)

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief Cache status of the PTS  */
static sds_sensor_status_t panel_temp_sens_status;

/** @brief Cache error code of the PTS */
static uint8_t panel_temp_err_code;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
STATIC sds_op_status_t sensor_panel_temp_get_data_in_deg_c(sds_panel_temp_data_t * const p_data_dst);
STATIC sds_op_status_t sensor_panel_temp_init(void);
STATIC sds_op_status_t sensor_panel_temp_deinit(void);
STATIC sds_sensor_status_t sensor_panel_temp_get_state(void);
STATIC uint8_t sensor_panel_temp_get_last_error(void);
STATIC sds_op_status_t sensor_panel_temp_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value);
STATIC sds_op_status_t sensor_panel_temp_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value);

/**********************************************************************
 *
 * External type definitions
 *
 **********************************************************************/
sds_panel_temp_data_if_t panel_temp_data_if = {
		.get_panel_temp_data = sensor_panel_temp_get_data_in_deg_c,
};

sds_if_t panel_temp_base_if = {
		.init = sensor_panel_temp_init,
		.deinit = sensor_panel_temp_deinit,
		.get_state = sensor_panel_temp_get_state,
		.get_last_error = sensor_panel_temp_get_last_error,
		.get_reg = sensor_panel_temp_get_register,
		.set_reg = sensor_panel_temp_set_register
};

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Get panel temperature sensors data in degC
 *  @param[out] sds_panel_temp_data_t * const p_data_dst
 *  @return     sds_op_status_t
 *  @note
 *  */
STATIC sds_op_status_t sensor_panel_temp_get_data_in_deg_c(sds_panel_temp_data_t * const p_data_dst)
{
	CRIT_ASSERT(NULL != p_data_dst);

	int16_t panel_temp_data_raw[MAX_PAN] = {0, 0, 0, 0, 0, 0};

	for ( uint8_t i = 0; i < MAX_PAN; i++ )
	{
		if ( SEN_SUCCESS != TMP122_GetTemperatureFromPanel(i, &panel_temp_data_raw[i]) )
		{
			panel_temp_err_code = SDS_PANEL_TEMP_ERR_CODE_ERR;
		}
		else
		{
			panel_temp_data_raw[i] = TMP122_getTemperatureInDegC(panel_temp_data_raw[i]);
		}
	}

	p_data_dst->pan_temp_1_deg_c = panel_temp_data_raw[0];
	p_data_dst->pan_temp_2_deg_c = panel_temp_data_raw[1];
	p_data_dst->pan_temp_3_deg_c = panel_temp_data_raw[2];
	p_data_dst->pan_temp_4_deg_c = panel_temp_data_raw[3];
	p_data_dst->pan_temp_5_deg_c = panel_temp_data_raw[4];
	p_data_dst->pan_temp_6_deg_c = panel_temp_data_raw[5];

	SDS_TRACE_DBG("%s PANEL TEMP DATA IN DEG C---1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d\r", SDS_DBG_HEAD,
			p_data_dst->pan_temp_1_deg_c, p_data_dst->pan_temp_2_deg_c, p_data_dst->pan_temp_3_deg_c,
			p_data_dst->pan_temp_4_deg_c, p_data_dst->pan_temp_5_deg_c, p_data_dst->pan_temp_6_deg_c);

	return SDS_OP_STATUS_OK;
}

/** @brief Initialise the PTS
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_panel_temp_init(void)
{
	MCU_TemprInit();

	panel_temp_sens_status = SDS_SENSOR_STATUS_INIT;

	panel_temp_err_code = SDS_PANEL_TEMP_ERR_CODE_NO_ERR;

	return SDS_OP_STATUS_OK;
}

/** @brief Deinitialise the PTS
 *  @return sds_op_status_t */
STATIC sds_op_status_t sensor_panel_temp_deinit(void)
{
	MCU_TemprDeInit();

	panel_temp_sens_status = SDS_SENSOR_STATUS_DEINIT;

	return SDS_OP_STATUS_OK;
}

/** @brief Get the PTS status
 *  @return sds_sensor_status_t */
STATIC sds_sensor_status_t sensor_panel_temp_get_state(void)
{
	return panel_temp_sens_status;
}

/** @brief Get the last PTS reported error
 *  @return uint8_t */
STATIC uint8_t sensor_panel_temp_get_last_error(void)
{
	return panel_temp_err_code;
}

/** @brief Get a register from the sensor
 *  @param[in] uint8_t sens_id - sensor id. This field is used when a redundant sensor is available
 *  @param[in] sds_axis_enum_t sens_axis - sensor axis. This field is used when single axis sensors are used
 *  @param[in] uint32_t reg_address - the register address to be read
 *  @param[in] uint32_t *reg_value - pointer to memory to populate with the read register value
 *  @return sds_op_status_t - operation result */
STATIC sds_op_status_t sensor_panel_temp_get_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t const *reg_value)
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
STATIC sds_op_status_t sensor_panel_temp_set_register(uint8_t sens_id, sds_axis_enum_t sens_axis, uint32_t reg_address, uint32_t reg_value)
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
