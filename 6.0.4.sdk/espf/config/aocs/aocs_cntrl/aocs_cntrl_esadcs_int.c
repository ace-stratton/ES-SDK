/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_cntrl_esadcs_int.c
 * @brief    Attitude and Orbit Control System ES ADCS integration source
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "es_cdef.h"
#include "datacache.h"
#include "es_adcs.h"
#include "aocs_cntrl_esadcs_int.h"
#include "es_adcs_op_modes_sm_user.h"
#include "assertions.h"
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
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_sys_state_chng_req(const aocs_cntrl_sys_state_types_t sys_state,
                                                                 const aocs_cntrl_reference_params_t* const p_ref_params);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_sys_state_get_req_state(aocs_cntrl_sys_state_types_t *p_sys_state,
		                                                              aocs_cntrl_sys_state_req_state_t *p_sys_state_req_state);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_aocs_system_errors(aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_est_ang_rates(aocs_cntrl_est_ang_rate_t *p_est_ang_rates,
                                                                aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_est_att_ang(aocs_cntrl_est_att_t *p_est_att_ang);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_meas_wheel_speed(aocs_cntrl_wheel_speed_t *p_meas_wheel_speed);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_log_data(aocs_cntrl_log_data_t *p_log_data,
                                                           aocs_log_data_types_t data_type,
                                                           aocs_cntrl_offset_t* p_offset_values);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_cms_status(uint8_t * const p_cms_status);
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_cntrl_status(bool * const p_cntrl_status);

aocs_cntrl_t aocs_cntrl_esadcs_int =
{
		.p_sys_state_chng_req      = aocs_cntrl_esadcs_int_sys_state_chng_req,
		.p_sys_state_get_req_state = aocs_cntrl_esadcs_int_sys_state_get_req_state,
		.p_get_aocs_system_errors  = aocs_cntrl_esadcs_int_get_aocs_system_errors,
		.p_get_est_ang_rates       = aocs_cntrl_esadcs_int_get_est_ang_rates,
		.p_get_est_att_ang         = aocs_cntrl_esadcs_int_get_est_att_ang,
		.p_get_meas_wheel_speed    = aocs_cntrl_esadcs_int_get_meas_wheel_speed,
		.p_get_log_data            = aocs_cntrl_esadcs_int_get_log_data,
		.p_get_cms_status          = aocs_cntrl_esadcs_int_get_cms_status,
		.p_get_cntrl_status        = aocs_cntrl_esadcs_int_get_cntrl_status
};

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

/* @brief Request a new system state change to the ES ADCS
 *
 * @param[in] aocs_cntrl_sys_state_types_t sys_state - the new system state
 *
 * @return status after performing the request
 *
 */
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_sys_state_chng_req(const aocs_cntrl_sys_state_types_t sys_state,
                                                                 const aocs_cntrl_reference_params_t* const p_ref_params)
{
	/* AA TODO: When ES ADCS gets more development, describing system states with separate estimator/controller combination should become possible */

	CRIT_ASSERT(sys_state < AOCS_CNTRL_SYS_NUMBER);

	aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

	/* Flag to hold result from cubeadcs <-> ES adcs state mapping */
	safe_bool_t state_found = SAFE_TRUE;

	/* AA TODO: In terms of precaution, sys states (= configurations) should only be changed when in IDLE mode. Is this a correct assumption? */
	/* Move to IDLE mode */
	es_adcs_set_op_mode(STATE_ADCS_IDLE);

	/* Only if in IDLE mode */
	if (STATE_ADCS_IDLE == es_adcs_get_op_mode())
	{
		/* Check which state is desired */
		switch ( sys_state )
		{
			case AOCS_CNTRL_SYS_STATE_NO_CONTROL:
			{
				/* This replicates an idle satellite */
				es_adcs_set_estimator(ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG, ES_ADCS_ESTIMATOR_ALGO_NONE);
				es_adcs_set_controller(ES_ADCS_CONTROLLER_ALGO_NONE);
				break;
			}

			case AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING:
			{
				/* This is a detumbling satellite */
				es_adcs_set_estimator(ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG, ES_ADCS_ESTIMATOR_ALGO_NONE);
				es_adcs_set_controller(ES_ADCS_CONTROLLER_ALGO_BDOT_MAG);
				break;
			}

			case AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING:
			{
				/* This is a detumbling satellite */
				es_adcs_set_estimator(ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG, ES_ADCS_ESTIMATOR_ALGO_NONE);
				es_adcs_set_controller(ES_ADCS_CONTROLLER_ALGO_BDOT_MAG);
				break;
			}

			case AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING:
			{
				/* This is a detumbling satellite */
				es_adcs_set_estimator(ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG, ES_ADCS_ESTIMATOR_ALGO_NONE);
				es_adcs_set_controller(ES_ADCS_CONTROLLER_ALGO_BDOT_MAG);
				break;
			}

			default:
			{
				/* The rest of the system states do not have a direct counterpart in ES ADCS */
				state_found = SAFE_FALSE;
				break;
			}
		}

		/* Only proceed with state change if the desired state could be replicated with ES ADCS combination of estimator/controller */
		if (SAFE_TRUE == state_found)
		{
			/* Move to RUN mode */
			es_adcs_set_op_mode(STATE_ADCS_RUN);
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
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_sys_state_get_req_state(aocs_cntrl_sys_state_types_t *sys_state,
		aocs_cntrl_sys_state_req_state_t *sys_state_req_state)
{
	CRIT_ASSERT(NULL != sys_state);
	CRIT_ASSERT(NULL != sys_state_req_state);

	es_adcs_estimator_t activatedEstimators[ES_ADCS_ACTIVE_ESTIMATORS_MAX];
	es_adcs_controller_t activatedController;

	aocs_cntrl_sys_state_types_t     aocs_cntrl_state;
	aocs_cntrl_sys_state_req_state_t aocs_cntrl_state_req_state;

	/* Attempted mapping between AOCS states and ES ADCS states */
	es_adcs_get_estimator(activatedEstimators);
	activatedController = es_adcs_get_controller();

	/* AA TODO: this will definitely need to be extended or reworked when more estimators/controllers are added to ES ADCS */
	switch ( activatedController )
	{
		case ES_ADCS_CONTROLLER_ALGO_NONE:
		{
			if ((ES_ADCS_ESTIMATOR_ALGO_NONE == activatedEstimators[0]) && (ES_ADCS_ESTIMATOR_ALGO_NONE == activatedEstimators[1]))
			{
				/* Controller is stopped AND both estimators are stopped - this is 'power up' mode */
				aocs_cntrl_state = AOCS_CNTRL_SYS_STATE_NO_CONTROL;
				aocs_cntrl_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
			}
			else
			{
				/* Controller is stopped, but some estimators are working - this is an undefined mode */
				aocs_cntrl_state = AOCS_CNTRL_SYS_STATE_NO_CONTROL;
				aocs_cntrl_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED;
			}

			break;
		}

		case ES_ADCS_CONTROLLER_ALGO_BDOT_MAG:
		{
			if ((ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG == activatedEstimators[0]) && (ES_ADCS_ESTIMATOR_ALGO_NONE == activatedEstimators[1]))
			{
				/* Controller is working, an estimator is working - this is 'detumbling' mode */
				aocs_cntrl_state = AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING;
				aocs_cntrl_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
			}
			else if ((ES_ADCS_ESTIMATOR_ALGO_NONE == activatedEstimators[0]) && (ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG == activatedEstimators[1]))
			{
				/* Second possible case for estimator/controller config that is valid */
				aocs_cntrl_state = AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING;
				aocs_cntrl_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
			}
			else
			{
				/* Controller is working, but no estimators are on - this is an undefined mode */
				aocs_cntrl_state = AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING;
				aocs_cntrl_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED;
			}

			break;
		}

		default:
		{
			/* AA TODO: this default case has ambiguity; find a way to solve */
			aocs_cntrl_state = AOCS_CNTRL_SYS_STATE_NO_CONTROL;
			aocs_cntrl_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED;
			break;
		}
	}

	*sys_state           = aocs_cntrl_state;
	*sys_state_req_state = aocs_cntrl_state_req_state;

	return AOCS_CNTRL_OK;
}

/* @brief Get the ES ADCS reported errors
 *
 * @param[out] aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs - pointer to the storage location for the system errors
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_aocs_system_errors(aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs)
{
	CRIT_ASSERT(NULL != p_aocs_sys_errs);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;

	*p_aocs_sys_errs = (aocs_cntrl_aocs_sys_errs)es_adcs_get_latched_errors();

	ret_val = AOCS_CNTRL_OK;

	return ret_val;
}

/* @brief Get the ES ADCS reported estimated angular rates and norm
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *p_est_ang_rates - pointer to the storage location for the estimated angular rates
 * @param[out] aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm - pointer to the storage location for the norm
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_est_ang_rates(aocs_cntrl_est_ang_rate_t *p_est_ang_rates, aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm)
{
	/* AA TODO: this needs to get the ES ADCS angular velocity estimates; they are actually in the data cache */

	CRIT_ASSERT( NULL != p_est_ang_rates);
	CRIT_ASSERT( NULL != p_est_ang_rate_norm);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;

	DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t ang_rate_estimates;
	dc_data_status_t data_cache_error_controller;

	/* A vector to be used to calculate angular rate norm */
	es_adcs_vec_3d_t normVector;

	/* AA TODO: at one point, these estimates will have to be moved to a singular "estimates" data cache entry, not a bdot-specific one */
    data_cache_error_controller = dc_get_es_adcs_estimates_bdot_data(&ang_rate_estimates);

    /* Catch any DataCache read failure */
    if (DC_DATA_STATUS_OK != data_cache_error_controller)
    {
        /* DataCache readout failed */
    	ret_val = AOCS_CNTRL_FAILED;
    }
    else
    {
        /* Measurements come in microT/s */
    	p_est_ang_rates->X = ang_rate_estimates.i32MAG_FIELD_DERIV_X;
    	p_est_ang_rates->Y = ang_rate_estimates.i32MAG_FIELD_DERIV_Y;
    	p_est_ang_rates->Z = ang_rate_estimates.i32MAG_FIELD_DERIV_Z;

    	normVector.X = (REAL)ang_rate_estimates.i32MAG_FIELD_DERIV_X;
    	normVector.Y = (REAL)ang_rate_estimates.i32MAG_FIELD_DERIV_Y;
    	normVector.Z = (REAL)ang_rate_estimates.i32MAG_FIELD_DERIV_Z;

    	*p_est_ang_rate_norm = (int32_t)es_adcs_math_VecNorm(normVector);

    	ret_val = AOCS_CNTRL_OK;
    }
	return ret_val;
}

/* @brief Get the ES ADCS reported estimated attitude angles
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *p_est_att_ang - pointer to the storage location for the estimated attitude angles
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_est_att_ang(aocs_cntrl_est_att_t *p_est_att_ang)
{
	/* AA TODO: this needs to get the ES ADCS angular position estimates; they are actually not implemented yet (19.04.2023) */

	CRIT_ASSERT( NULL != p_est_att_ang);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;

	return ret_val;
}

/* @brief Get the ES ADCS measured wheel speed
 *
 * @param[out] aocs_cntrl_wheel_speed_t *p_meas_wheel_speed - pointer to the storage location for the measured wheel speed
 *
 * @return status after performing the request
 */
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_meas_wheel_speed(aocs_cntrl_wheel_speed_t *p_meas_wheel_speed)
{
	/* AA TODO: this needs to get the ES ADCS measured wheel speed; they are actually not implemented yet (19.04.2023) */

	CRIT_ASSERT( NULL != p_meas_wheel_speed);

	aocs_cntrl_res_t ret_val = AOCS_CNTRL_FAILED;

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
STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_log_data(aocs_cntrl_log_data_t *p_log_data, aocs_log_data_types_t data_type, aocs_cntrl_offset_t* offset_values)
{
	aocs_cntrl_res_t ret = AOCS_CNTRL_FAILED;

	CRIT_ASSERT(NULL != p_log_data);
	CRIT_ASSERT(NULL != offset_values);

	/* Left as default values until it is decided what exactly this is going to do for ES ADCS */
	p_log_data->value1 = 0;
	p_log_data->value2 = 0;
	p_log_data->value3 = 0;

	offset_values->offset_value[0] = 0;
	offset_values->offset_value[1] = 0;
	offset_values->offset_value[2] = 0;

	ret = AOCS_CNTRL_OK;
	return ret;
}


STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_cms_status(uint8_t * const p_cms_status)
{
    // TODO: Implement
    return AOCS_CNTRL_FAILED;
}

STATIC aocs_cntrl_res_t aocs_cntrl_esadcs_int_get_cntrl_status(bool * const p_cntrl_status)
{
    // TODO: Implement
    return AOCS_CNTRL_FAILED;
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
