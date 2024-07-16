/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_cntrl_cubeadcs_int.c
 * @brief    Attitude and Orbit Control System CubeADCS integration source
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "cubeadcs.h"

#include "assertions.h"
#include "es_cdef.h"

#include "datacache.h"

#include "aocs_cntrl_cubeadcs_int.h"

#include "aocs_pm_cfg.h"
/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/


/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_sys_state_chng_req(const aocs_cntrl_sys_state_types_t sys_state,
                                                                   const aocs_cntrl_reference_params_t* const p_ref_params);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_sys_state_get_req_state(aocs_cntrl_sys_state_types_t *p_sys_state,
		                                                                aocs_cntrl_sys_state_req_state_t *p_sys_state_req_state);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_aocs_system_errors(aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_est_ang_rates(aocs_cntrl_est_ang_rate_t *p_est_ang_rates,
                                                                  aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_est_att_ang(aocs_cntrl_est_att_t *p_est_att_ang);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_meas_wheel_speed(aocs_cntrl_wheel_speed_t *p_meas_wheel_speed);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_log_data(aocs_cntrl_log_data_t *p_log_data,
                                                             aocs_log_data_types_t data_type,
                                                             aocs_cntrl_offset_t* p_offset_values);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_cms_status(uint8_t * const p_cms_status);
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_cntrl_status(bool * const p_cntrl_status);

aocs_cntrl_t aocs_cntrl_cubeadcs_int =
{
		.p_sys_state_chng_req      = aocs_cntrl_cubeadcs_int_sys_state_chng_req,
		.p_sys_state_get_req_state = aocs_cntrl_cubeadcs_int_sys_state_get_req_state,
		.p_get_aocs_system_errors = aocs_cntrl_cubeadcs_int_get_aocs_system_errors,
		.p_get_est_ang_rates = aocs_cntrl_cubeadcs_int_get_est_ang_rates,
		.p_get_est_att_ang = aocs_cntrl_cubeadcs_int_get_est_att_ang,
		.p_get_meas_wheel_speed = aocs_cntrl_cubeadcs_int_get_meas_wheel_speed,
		.p_get_log_data = aocs_cntrl_cubeadcs_int_get_log_data,
		.p_get_cms_status = aocs_cntrl_cubeadcs_int_get_cms_status,
		.p_get_cntrl_status = aocs_cntrl_cubeadcs_int_get_cntrl_status
};

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

/* @brief Request a new system state change to the CubeADCS
 *
 * @param[in] aocs_cntrl_sys_state_types_t sys_state - the new system state
 * @param[in] aocs_cntrl_reference_params_t p_ref_params - reference parameters for some ADCS control modes
 *
 * @return status after performing the request
 *
 */
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_sys_state_chng_req(const aocs_cntrl_sys_state_types_t sys_state,
                                                                   const aocs_cntrl_reference_params_t* const p_ref_params)
{
	aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

	eCubeADCS_CfgType adcs_sys_state = eCUBEADCS_CFGTYPE_NUMBER;

    cubeadcs_ref_t ref_params = {
            .ref_param_1 = 0,
            .ref_param_2 = 0,
            .ref_param_3 = 0
    };

    if ( (eCUBEADCS_STATE_IDLE == CubeADCS_GetState() ) &&
            (eCUBEADCS_FTRANSF_STATE_IDLE == (CubeADCS_FTransfer_GetTaskState())) )
    {
        switch (sys_state)
        {
        case AOCS_CNTRL_SYS_STATE_NO_CONTROL:
            adcs_sys_state = eCUBEADCS_CFGTYPE_NO_CONTROL;
            break;
        case AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING:
            adcs_sys_state = eCUBEADCS_CFGTYPE_NORMAL_DETUMBLING;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_THOMSON:
            adcs_sys_state = eCUBEADCS_CFGTYPE_Y_THOMSON;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE:
            adcs_sys_state = eCUBEADCS_CFGTYPE_Y_THOMSON_MEMS_RATE;
            break;
        case AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING:
            adcs_sys_state = eCUBEADCS_CFGTYPE_FAST_DETUMBLING;
            break;
        case AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING:
            adcs_sys_state = eCUBEADCS_CFGTYPE_VERY_FAST_DETUMBLING;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_MOMENTUM:
            adcs_sys_state = eCUBEADCS_CFGTYPE_Y_MOMENTUM;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_MOMENTUM_FULL_STATE_EKF:
            adcs_sys_state = eCUBEADCS_CFGTYPE_Y_MOMENTUM_FULL_STATE_EKF;
            break;
        case AOCS_CNTRL_SYS_STATE_3AXIS:
            adcs_sys_state = eCUBEADCS_CFGTYPE_3AXIS;
            break;
        case AOCS_CNTRL_SYS_STATE_SUN_TRACKING:
            adcs_sys_state = eCUBEADCS_CFGTYPE_SUN_TRACKING;
            break;
        case AOCS_CNTRL_SYS_STATE_TARGET_TRACKING:
            adcs_sys_state = eCUBEADCS_CFGTYPE_TARGET_TRACKING;
            break;
        case AOCS_CNTRL_SYS_STATE_USER1:
            adcs_sys_state = eCUBEADCS_CFGTYPE_ATTITUDE_CHANGE;
            break;
        case AOCS_CNTRL_SYS_STATE_USER2:
            adcs_sys_state = eCUBEADCS_CFGTYPE_ORBITAL_CHANGE;
            break;
        case AOCS_CNTRL_SYS_STATE_USER3:
            adcs_sys_state = eCUBEADCS_CFGTYPE_GEO_TARGET_TRACKING;
            break;
        default:
            break;
        }

        ref_params.ref_param_1 = p_ref_params->ref_param_1;
        ref_params.ref_param_2 = p_ref_params->ref_param_2;
        ref_params.ref_param_3 = p_ref_params->ref_param_3;

        if ( false != cubeadcs_set_sys_state_and_ref(&ref_params, adcs_sys_state) )
        {
            op_res = AOCS_CNTRL_OK;
        }
    }

	return op_res;
}

/* @brief Get the last requested system state and its status
 *
 * @param[out] aocs_cntrl_sys_state_types_t *sys_state - pointer to the storage location for the system state
 * @param[out] aocs_cntrl_sys_state_req_state_t *sys_state_req_state - pointer to the storage location for the request state
 *
 * @return status after performing the request
 *
 */
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_sys_state_get_req_state(aocs_cntrl_sys_state_types_t *sys_state,
		aocs_cntrl_sys_state_req_state_t *sys_state_req_state)
{
	CRIT_ASSERT(NULL != sys_state);
	CRIT_ASSERT(NULL != sys_state_req_state);

	CubeADCS_SysSCfg_t cubeadcs_sys_state;

	aocs_cntrl_sys_state_req_state_t aocs_sys_state_req;
	aocs_cntrl_sys_state_types_t aocs_sys_state;

	cubeadcs_get_adcs_state_cfg(&cubeadcs_sys_state);

    switch (cubeadcs_sys_state.eReqCfg)
    {
    case eCUBEADCS_CFGTYPE_NO_CONTROL:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_NO_CONTROL;
        break;
    case eCUBEADCS_CFGTYPE_NORMAL_DETUMBLING:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING;
        break;
    case eCUBEADCS_CFGTYPE_Y_THOMSON:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_Y_THOMSON;
        break;
    case eCUBEADCS_CFGTYPE_Y_THOMSON_MEMS_RATE:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE;
        break;
    case eCUBEADCS_CFGTYPE_FAST_DETUMBLING:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING;
        break;
    case eCUBEADCS_CFGTYPE_VERY_FAST_DETUMBLING:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING;
        break;
    case eCUBEADCS_CFGTYPE_Y_MOMENTUM:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_Y_MOMENTUM;
        break;
    case eCUBEADCS_CFGTYPE_Y_MOMENTUM_FULL_STATE_EKF:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_Y_MOMENTUM_FULL_STATE_EKF;
        break;
    case eCUBEADCS_CFGTYPE_3AXIS:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_3AXIS;
        break;
    case eCUBEADCS_CFGTYPE_SUN_TRACKING:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_SUN_TRACKING;
        break;
    case eCUBEADCS_CFGTYPE_TARGET_TRACKING:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_TARGET_TRACKING;
        break;
    case eCUBEADCS_CFGTYPE_ATTITUDE_CHANGE:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_USER1;
        break;
    case eCUBEADCS_CFGTYPE_ORBITAL_CHANGE:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_USER2;
        break;
    case eCUBEADCS_CFGTYPE_GEO_TARGET_TRACKING:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_USER3;
        break;
    default:
        aocs_sys_state = AOCS_CNTRL_SYS_STATE_EXISTING_CONTROL;
        break;
    }

	switch ( cubeadcs_sys_state.eReqCfgStatus )
	{
	case eSYSSTATECFGSTATUS_OK:
		aocs_sys_state_req = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
		break;
	case eSYSSTATECFGSTATUS_NEW_REQ:
		aocs_sys_state_req = AOCS_CNTRL_SYS_STATE_STATE_REQ_NEW_REQ;
		break;
	case eSYSSTATECFGSTATUS_ERR:
		aocs_sys_state_req = AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED;
		break;
	default:
		aocs_sys_state_req = AOCS_CNTRL_SYS_STATE_STATE_REQ_IN_PROGRESS;
		break;
	}

	*sys_state = aocs_sys_state;
	*sys_state_req_state = aocs_sys_state_req;

	return AOCS_CNTRL_OK;
}

/* @brief Get the CubeADCS reported errors
 *
 * @param[out] aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs - pointer to the storage location for the system errors
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_aocs_system_errors(aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs)
{
	CRIT_ASSERT(NULL != p_aocs_sys_errs);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;
	uint16_t adcs_sys_errs = (uint16_t)0;
	if ( true == cubeadcs_get_latched_err(&adcs_sys_errs) )
	{
	    *p_aocs_sys_errs = (aocs_cntrl_aocs_sys_errs)adcs_sys_errs;
		ret_val = AOCS_CNTRL_OK;
	}

	return ret_val;
}

/* @brief Get the CubeADCS reported estimated angular rates and norm
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *p_est_ang_rates - pointer to the storage location for the estimated angular rates
 * @param[out] aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm - pointer to the storage location for the norm
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_est_ang_rates(aocs_cntrl_est_ang_rate_t *p_est_ang_rates, aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm)
{
	CRIT_ASSERT( NULL != p_est_ang_rates);
	CRIT_ASSERT( NULL != p_est_ang_rate_norm);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;

	CubeADCS_AngRate_Complete_t ang_rate_and_norm;
	if ( (eCUBEADCS_STATE_IDLE == CubeADCS_GetState() ) &&
	     (eCUBEADCS_FTRANSF_STATE_IDLE == CubeADCS_FTransfer_GetTaskState() ) &&
	     ( true == cubeadcs_get_est_ang_rate_complete(&ang_rate_and_norm)) )
	{
        *p_est_ang_rate_norm = ang_rate_and_norm.fAngVelNorm;

        p_est_ang_rates->X = ang_rate_and_norm.sAngVelVec.X;
        p_est_ang_rates->Y = ang_rate_and_norm.sAngVelVec.Y;
        p_est_ang_rates->Z = ang_rate_and_norm.sAngVelVec.Z;

        ret_val = AOCS_CNTRL_OK;
    }
	return ret_val;
}

/* @brief Get the CubeADCS reported estimated attitude angles
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *p_est_att_ang - pointer to the storage location for the estimated attitude angles
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_est_att_ang(aocs_cntrl_est_att_t *p_est_att_ang)
{
	CRIT_ASSERT( NULL != p_est_att_ang);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;

	cubeadcs_est_att_ang_fmt_t att_angles;
	if ( (eCUBEADCS_STATE_IDLE == CubeADCS_GetState() ) &&
	     (eCUBEADCS_FTRANSF_STATE_IDLE == CubeADCS_FTransfer_GetTaskState() ) &&
	     ( true == cubeadcs_get_est_att_angles(&att_angles) ))
	{
        p_est_att_ang->pitch = att_angles.i32Pitch;
        p_est_att_ang->roll = att_angles.i32Roll;
        p_est_att_ang->yaw = att_angles.i32Yaw;

        ret_val = AOCS_CNTRL_OK;
	}

	return ret_val;
}

/* @brief Get the CubeADCS measured wheel speed
 *
 * @param[out] aocs_cntrl_wheel_speed_t *p_meas_wheel_speed - pointer to the storage location for the measured wheel speed
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_meas_wheel_speed(aocs_cntrl_wheel_speed_t *p_meas_wheel_speed)
{
	CRIT_ASSERT( NULL != p_meas_wheel_speed);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;

	uint16_t cmd_resp_len;
	CubeADCS_CmdCfg_t cmd_req;
	cubeadcs_tlm_156_t cmd_resp;

	if ( (eCUBEADCS_STATE_IDLE == CubeADCS_GetState() ) &&
	 (eCUBEADCS_FTRANSF_STATE_IDLE == CubeADCS_FTransfer_GetTaskState() ))
	{
		CubeADCS_PREPCmd(&cmd_req, eCUBEADCS_CMD_ID_156, NULL, 0, (void *)&cmd_resp, CUBEADCS_TLM156_LEN, &cmd_resp_len);

		if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&cmd_req, eCUBEADCS_COMMREQTYPE_FETCH) )
		{
			p_meas_wheel_speed->rwl0_speed = cmd_resp.meas_wheel_speed.X_Wheel;
			p_meas_wheel_speed->rwl1_speed = cmd_resp.meas_wheel_speed.Y_Wheel;
			p_meas_wheel_speed->rwl2_speed = cmd_resp.meas_wheel_speed.Z_Wheel;


			ret_val = AOCS_CNTRL_OK;
		}
	}

	return ret_val;
}

/* @brief Get the corresponding data for logging and offsets. The offset are the commanded
 * angles and it is only for EST_ATT_ANGL, in all other cases they should be 0.
 * @param[out] aocs_cntrl_log_data_t *p_log_data - array of data to be passed to the PM
 * @param[out] aocs_cntrl_offset_t* offset_values - array of offsets to pass to the PM
 * @param[in] aocs_log_data_types_t data_type - what kind of data to get from the datacache
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_log_data(aocs_cntrl_log_data_t *p_log_data, aocs_log_data_types_t data_type, aocs_cntrl_offset_t* p_offset_values)
{
	aocs_cntrl_res_t ret = AOCS_CNTRL_FAILED;
	dc_data_status_t dc_status;
	DATA_CACHE_ADCS_0_t adcs_dc_data_0;
	DATA_CACHE_ADCS_1_t adcs_dc_data_1;
	DATA_CACHE_ADCS_3_t adcs_dc_data_3;
	DATA_CACHE_ADCS_4_t adcs_dc_data_4;

	CRIT_ASSERT(NULL != p_log_data);
	CRIT_ASSERT(NULL != p_offset_values);

	//get the data cache
	switch(data_type)
	{
		case EST_ATT_ANGL:
			dc_status = dc_get_adcs_3_data(&adcs_dc_data_3);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = (int32_t)(adcs_dc_data_3.i16Est_roll_angle * DATA_MULTIPLIER_AOCS_INT);
				p_log_data->value2 = (int32_t)(adcs_dc_data_3.i16Est_pitch_angle  * DATA_MULTIPLIER_AOCS_INT);
				p_log_data->value3 = (int32_t)(adcs_dc_data_3.i16Est_yaw_angle   * DATA_MULTIPLIER_AOCS_INT);
				ret = AOCS_CNTRL_OK;

				dc_status = DC_DATA_STATUS_TOUT;

				dc_status = dc_get_adcs_1_data(&adcs_dc_data_1);

				if(DC_DATA_STATUS_OK == dc_status)
				{
					p_offset_values->offset_value[0] = (int32_t)(adcs_dc_data_1.ai16ControlledAngles[0] * DATA_MULTIPLIER_AOCS_INT);
					p_offset_values->offset_value[1] = (int32_t)(adcs_dc_data_1.ai16ControlledAngles[1] * DATA_MULTIPLIER_AOCS_INT);
					p_offset_values->offset_value[2] = (int32_t)(adcs_dc_data_1.ai16ControlledAngles[2] * DATA_MULTIPLIER_AOCS_INT);
				}
				else if(DC_DATA_STATUS_TOUT == dc_status)
				{
					ret = AOCS_CNTRL_FAILED;
				}
			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}
		break;
		case EST_ANG_RATES:
			dc_status = dc_get_adcs_1_data(&adcs_dc_data_1);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = (int32_t)(adcs_dc_data_1.ai16EstAngRateVec[0] * DATA_MULTIPLIER_AOCS_INT);
				p_log_data->value2 = (int32_t)(adcs_dc_data_1.ai16EstAngRateVec[1] * DATA_MULTIPLIER_AOCS_INT);
				p_log_data->value3 = (int32_t)(adcs_dc_data_1.ai16EstAngRateVec[2] * DATA_MULTIPLIER_AOCS_INT);

				p_offset_values->offset_value[0] = 0;
				p_offset_values->offset_value[1] = 0;
				p_offset_values->offset_value[2] = 0;
				ret = AOCS_CNTRL_OK;
			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}
		break;
		case MEAS_MAG_FIELD_VEC:
			dc_status = dc_get_adcs_0_data(&adcs_dc_data_0);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = (int32_t)(adcs_dc_data_0.ai16MagFieldVec[0] * DATA_MULTIPLIER_AOCS_INT);
				p_log_data->value2 = (int32_t)(adcs_dc_data_0.ai16MagFieldVec[1] * DATA_MULTIPLIER_AOCS_INT);
				p_log_data->value3 = (int32_t)(adcs_dc_data_0.ai16MagFieldVec[2] * DATA_MULTIPLIER_AOCS_INT);

				p_offset_values->offset_value[0] = 0;
				p_offset_values->offset_value[1] = 0;
				p_offset_values->offset_value[2] = 0;

				ret = AOCS_CNTRL_OK;

			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}
		break;
		case EST_INNOVATION_VEC:

			dc_status = dc_get_adcs_3_data(&adcs_dc_data_3);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = (int32_t)(adcs_dc_data_3.i16Innovation_Vec_X );
				p_log_data->value2 = (int32_t)(adcs_dc_data_3.i16Innovation_Vec_Y );
				p_log_data->value3 = (int32_t)(adcs_dc_data_3.i16Innovation_Vec_Z );

				p_offset_values->offset_value[0] = 0;
				p_offset_values->offset_value[1] = 0;
				p_offset_values->offset_value[2] = 0;

				ret = AOCS_CNTRL_OK;
			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}
		break;
		case Q_ERR_VEC:
			dc_status = dc_get_adcs_3_data(&adcs_dc_data_3);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = (int32_t)(adcs_dc_data_3.i16Err_Q1);
				p_log_data->value2 = (int32_t)(adcs_dc_data_3.i16Err_Q2);
				p_log_data->value3 = (int32_t)(adcs_dc_data_3.i16Err_Q3);

				p_offset_values->offset_value[0] = 0;
				p_offset_values->offset_value[1] = 0;
				p_offset_values->offset_value[2] = 0;

				ret = AOCS_CNTRL_OK;

			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}

		break;
		case MAG_MCU_TEMP:
			dc_status = dc_get_adcs_4_data(&adcs_dc_data_4);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = adcs_dc_data_4.i16ADCS_MCU_Temp;
				p_log_data->value2 = (int32_t)(adcs_dc_data_4.i16MTM_Temp * DATA_MULTIPLIER_AOCS_INT);
				p_log_data->value3 = (int32_t)(adcs_dc_data_4.i16RMTM_Temp * DATA_MULTIPLIER_AOCS_INT);

				p_offset_values->offset_value[0] = 0;
				p_offset_values->offset_value[1] = 0;
				p_offset_values->offset_value[2] = 0;
				ret = AOCS_CNTRL_OK;
			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}
		break;
		case RATE_SENS_TEMP:
			dc_status = dc_get_adcs_4_data(&adcs_dc_data_4);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = (int32_t)adcs_dc_data_4.i16X_Rate_Sensor_Temp;
				p_log_data->value2 = (int32_t)adcs_dc_data_4.i16Y_Rate_Sensor_Temp;
				p_log_data->value3 = (int32_t)adcs_dc_data_4.i16Z_Rate_Sensor_Temp;

				p_offset_values->offset_value[0] = 0;
				p_offset_values->offset_value[1] = 0;
				p_offset_values->offset_value[2] = 0;
				ret = AOCS_CNTRL_OK;
			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}
		break;
		case RATE_CONVERGENCE:
			dc_status = dc_get_adcs_1_data(&adcs_dc_data_1);

			if(DC_DATA_STATUS_OK == dc_status)
			{
				p_log_data->value1 = (int32_t)adcs_dc_data_1.ai16RawGyroRates[0] - (int32_t)adcs_dc_data_1.ai16EstAngRateVec[0];
				p_log_data->value2 = (int32_t)adcs_dc_data_1.ai16RawGyroRates[1] - (int32_t)adcs_dc_data_1.ai16EstAngRateVec[1];
				p_log_data->value3 = (int32_t)adcs_dc_data_1.ai16RawGyroRates[2] - (int32_t)adcs_dc_data_1.ai16EstAngRateVec[2];

				p_offset_values->offset_value[0] = 0;
				p_offset_values->offset_value[1] = 0;
				p_offset_values->offset_value[2] = 0;

				ret = AOCS_CNTRL_OK;
			}
			else if(DC_DATA_STATUS_TOUT == dc_status)
			{
				ret = AOCS_CNTRL_FAILED;
			}
		break;
		default:
			ret = AOCS_CNTRL_FAILED;
		break;
	}

	return ret;
}

STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_cms_status(uint8_t * const p_cms_status)
{
    *p_cms_status = (uint8_t)cubeadcs_get_cms_status();
    return AOCS_CNTRL_OK;
}

STATIC aocs_cntrl_res_t aocs_cntrl_cubeadcs_int_get_cntrl_status(bool * const p_cntrl_status)
{
    if ( eCUBE_ADCS_TC_13_CONTROLMODE_NO_CNTRL != CubeADCS_GetCntrlMode() )
    {
        *p_cntrl_status = true;
    }
    else
    {
        *p_cntrl_status = false;
    }

    return AOCS_CNTRL_OK;
}

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/


/*
 *********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
