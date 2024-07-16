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
 * @file     aocs_cntrl.c
 * @brief    Attitude and Orbit Control System source
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "../inc/aocs_cntrl_dbg.h"
#include "../inc/aocs_cntrl.h"
#include "../inc/if_aocs_cntrl_sys.h"
#include "aocs_cntrl_cfg.h"
#include "aocs_pm.h"

#include "AppTasks.h"
#include "TaskMonitor.h"
#include "if_sys_conf.h"

#include "datacache.h"
#include "assertions.h"

#include <string.h>

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
#define AOCS_CNTRL_TASK_PERIOD_MS (1000U)

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
/** @brief Used to calculate the wait time of the AOCS_cntrl task */
static uint32_t fs_wait_time = 0;

/** @brief The AOCS control task handle */
static osThreadId_t   fs_h_aocs_cntrl_task_handle;

/** @brief Flag indicating whether communication with ADCS module has been established. Used
 *  by the AOCS state request interface to reject requests if there is no underlying ADCS
 *  module to service them.
 *
 *  @note This flag doesn't need a mutex, because it is set to true only on initialization
 *  of communication with the ADCS module. If the initialization function is called again
 *  with a not-ready ADCS and there is a request for AOCS state (e.g. by payload controller)
 *  it is possible that the request will be registered in DataCache, but will ultimately fail
 *  if the ADCS module doesn't come online in time.
 */
static bool fs_adcs_initialized = false;

/** @brief The AOCS control task attributes */
static const osThreadAttr_t aocs_cntrl_task_attributes = {
  .name = "fs_aocs_cntrl_task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1500
};

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
STATIC void fs_aocs_cntrl_task(void *arg);
STATIC void fs_aocs_cntrl_init_control_mode(const aocs_cntrl_types_t used_aocs_type);
STATIC void fs_aocs_cntrl_task_main(const aocs_cntrl_types_t used_aocs_type);
STATIC bool fs_aocs_cntrl_is_new_sys_state_req(aocs_cntrl_sys_state_types_t *p_sys_state);
STATIC void fs_aocs_cntrl_set_aocs_dc_data(void);
STATIC void fs_aocs_cntrl_set_aocs_sys_state_dc_data(bool is_last_req_successful);
STATIC void fs_aocs_cntrl_pm(aocs_cntrl_sys_state_types_t sys_state);
STATIC bool fs_aocs_cntrl_is_interface_valid(const aocs_cntrl_t * const p_if);
STATIC bool fs_aocs_cntrl_get_ref_params(aocs_cntrl_reference_params_t * const p_ref_params);
STATIC void fs_aocs_cntrl_set_ref_params(const aocs_cntrl_reference_params_t * const p_ref_params);

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
void aocs_cntrl_task_init(void)
{
    // Check if the interfaces to underlying AOCS modules are properly configured
    bool all_correct = true;
    for (uint32_t i = 0; i < CDEF_ELEMENT_COUNT(aocs_cntrl_cfg); i++)
    {
        all_correct = all_correct && fs_aocs_cntrl_is_interface_valid(aocs_cntrl_cfg[i].aocs_if);
    }

    // Start the AOCS service only if all interfaces are configured
    if (false != all_correct)
    {
        fs_h_aocs_cntrl_task_handle = osThreadNew(fs_aocs_cntrl_task, NULL, &aocs_cntrl_task_attributes);
        CRIT_ASSERT( NULL != fs_h_aocs_cntrl_task_handle );

        TaskMonitor_TaskInitialized(TASK_AOCS_CNTRL);
        task_mon_set_task_policy(TASK_AOCS_CNTRL, TASK_MON_POLICY_MONITOR);
    }
}

void aocs_cntrl_task_deinit(void)
{
    task_mon_set_task_policy(TASK_AOCS_CNTRL, TASK_MON_POLICY_DONT_CARE);
}

aocs_cntrl_err_status aocs_cntrl_request_aocs_state(const aocs_cntrl_sys_state_types_t sys_state, const aocs_cntrl_reference_params_t * const p_ref_params)
{
    aocs_cntrl_err_status op_res = AOCS_CNTRL_ERR_FAILED;

    DATA_CACHE_AOCS_CNTRL_SYS_STATE_t s_aocs_state_data;
    const dc_data_status_t dc_status = dc_get_aocs_cntrl_sys_state_data(&s_aocs_state_data);


    if ( ((DC_NOT_INITIALIZED == dc_status) ||
         (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == s_aocs_state_data.u8AdcsSysStateStatus) ||
         (AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED    == s_aocs_state_data.u8AdcsSysStateStatus)) &&
         (false != fs_adcs_initialized))
    {

        // There is no ongoing change of the AOCS state
        fs_aocs_cntrl_set_ref_params(p_ref_params);

        s_aocs_state_data.u8AdcsSysState = (uint8_t)sys_state;
        s_aocs_state_data.u8AdcsSysStateStatus = AOCS_CNTRL_SYS_STATE_STATE_REQ_NEW_REQ;

        dc_set_aocs_cntrl_sys_state_data(&s_aocs_state_data);
        op_res = AOCS_CNTRL_ERR_OK;
    }
    else
    {
        TODO(There should be a separate result for the case of lacking communication with ADCS module.)
        op_res = AOCS_CNTRL_ERR_BUSY;
    }

    return op_res;
}

aocs_cntrl_err_status aocs_cntrl_get_aocs_state(aocs_cntrl_sys_state_types_t * const p_aocs_state,
                               aocs_cntrl_sys_state_req_state_t * const p_aocs_req_state)
{
    aocs_cntrl_err_status op_res = AOCS_CNTRL_ERR_FAILED;

    if ( (NULL != p_aocs_state) && (NULL != p_aocs_req_state) )
    {
        DATA_CACHE_AOCS_CNTRL_SYS_STATE_t s_adcs_data;
        const dc_data_status_t dc_status = dc_get_aocs_cntrl_sys_state_data(&s_adcs_data);
        if (DC_NOT_INITIALIZED != dc_status)
        {
            op_res = AOCS_CNTRL_ERR_OK;
        }

        // Set the output values with whatever is read from DC. User should check the return code of the function
        *p_aocs_state = s_adcs_data.u8AdcsSysState;
        *p_aocs_req_state = s_adcs_data.u8AdcsSysStateStatus;
    }
    else
    {
        CRIT_ASSERT(false);
    }

    return op_res;
}

bool aocs_cntrl_get_cms_status(aocs_cms_status_t * const p_status)
{
    bool op_res = false;

    if (NULL != p_status)
    {
        uint8_t adcs_status;
        const aocs_cntrl_types_t used_aocs_type = get_enabled_aocs_type();
        if ( AOCS_CNTRL_OK == aocs_cntrl_cfg[used_aocs_type].aocs_if->p_get_cms_status(&adcs_status) )
        {
            *p_status = (aocs_cms_status_t)adcs_status;
            op_res = true;
        }
    }
    else
    {
        CRIT_ASSERT(false);
    }

    return op_res;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
/** @brief The AOCS control task
 *
 *  @param[in] void *args - task arguments
 *
 */
STATIC void fs_aocs_cntrl_task(void *arg)
{
    (void) arg;
	aocs_pm_init();

	for(;;)
	{
		fs_wait_time = osKernelGetTickCount();

	    const aocs_cntrl_types_t used_aocs_type = get_enabled_aocs_type();

	    if (false == fs_adcs_initialized)
	    {
	        // After OBC reset, check if there is an existing control algorithm applied by the ADCS
	        fs_aocs_cntrl_init_control_mode(used_aocs_type);
	    }
	    else
	    {
	        // Perform the regular activities of the AOCS service
            fs_aocs_cntrl_task_main(used_aocs_type);
	    }

		fs_wait_time += AOCS_CNTRL_TASK_PERIOD_MS;

		osDelayUntil(fs_wait_time);

		TaskMonitor_IamAlive(TASK_AOCS_CNTRL);
		vApplicationLowStackCheck(TASK_AOCS_CNTRL);
	}
}

/** @brief Handles the detection of existing ADCS control mode after OBC reset
 *
 *  @param[in] aocs_cntrl_types_t aocs_type - type of the AOCS HW module which the AOCS service works with
 *
 */
STATIC void fs_aocs_cntrl_init_control_mode(const aocs_cntrl_types_t used_aocs_type)
{
    const aocs_cntrl_reference_params_t default_params = {.ref_param_1 = 0.0f,
                                                          .ref_param_2 = 0.0f,
                                                          .ref_param_3 = 0.0f};
    bool cntrl_status = false;
    DATA_CACHE_AOCS_CNTRL_SYS_STATE_t s_aocs_state_data;
    bool adcs_initialized = false;

    if (AOCS_CNTRL_OK == aocs_cntrl_cfg[used_aocs_type].aocs_if->p_get_cntrl_status(&cntrl_status))
    {
        if (false != cntrl_status)
        {
            // The ADCS is already following some control algorithm
            s_aocs_state_data.u8AdcsSysState = (uint8_t)AOCS_CNTRL_SYS_STATE_EXISTING_CONTROL;
            s_aocs_state_data.u8AdcsSysStateStatus = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
            dc_set_aocs_cntrl_sys_state_data(&s_aocs_state_data);
        }
        else
        {
            fs_aocs_cntrl_set_ref_params(&default_params);
            s_aocs_state_data.u8AdcsSysState = (uint8_t)AOCS_CNTRL_SYS_STATE_NO_CONTROL;
            s_aocs_state_data.u8AdcsSysStateStatus = AOCS_CNTRL_SYS_STATE_STATE_REQ_NEW_REQ;
            dc_set_aocs_cntrl_sys_state_data(&s_aocs_state_data);
        }

        adcs_initialized = true;
    }
    else
    {
        // While there is no reliable reading from ADCS the AOCS state shall be reported as UNDEFINED.
        // Do not set the "initialized" flag to true - we want to retry reading the control status for
        // as long as it takes

        s_aocs_state_data.u8AdcsSysState = (uint8_t)AOCS_CNTRL_SYS_STATE_UNDEFINED;
        s_aocs_state_data.u8AdcsSysStateStatus = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
        dc_set_aocs_cntrl_sys_state_data(&s_aocs_state_data);
    }

    fs_adcs_initialized = adcs_initialized;
}

/** @brief The periodic part of the AOCS control algorithm, after initialization
 *
 *  @param[in] aocs_cntrl_types_t used_aocs_type - type of the AOCS HW module which the AOCS service works with
 *
 */
STATIC void fs_aocs_cntrl_task_main(const aocs_cntrl_types_t used_aocs_type)
{
    aocs_cntrl_sys_state_types_t sys_state;
    aocs_cntrl_reference_params_t ref_params;
    bool sys_state_chng_req_status = true;

    if ( fs_aocs_cntrl_is_new_sys_state_req(&sys_state) &&
         fs_aocs_cntrl_get_ref_params(&ref_params) &&
         (used_aocs_type < AOCS_CNTRL_TYPE_MAX) )
    {
        if ( AOCS_CNTRL_OK == aocs_cntrl_cfg[used_aocs_type].aocs_if->p_sys_state_chng_req(sys_state, &ref_params) )
        {
            AOCS_CNTRL_TRACE_DBG("%s: REQ_SENT\r", AOCS_CNTRL_HEAD_DBG);
        }
        else
        {
            sys_state_chng_req_status = false;
        }
    }

    fs_aocs_cntrl_set_aocs_sys_state_dc_data(sys_state_chng_req_status);

    fs_aocs_cntrl_set_aocs_dc_data();

    if (sys_state < AOCS_CNTRL_SYS_NUMBER)
    {
        fs_aocs_cntrl_pm(sys_state);
    }
}

/** @brief Calls and manages the performance monitor
 *
 *	@param[in] aocs_cntrl_sys_state_types_t *p_sys_state - the requested system state
 */
STATIC void fs_aocs_cntrl_pm(aocs_cntrl_sys_state_types_t sys_state)
{
	aocs_cntrl_log_data_t get_data_to_pass_to_pm_algorythm;
	aocs_log_data_types_t data_type_for_assessment;
	aocs_cntrl_offset_t offset;
	aocs_cntrl_res_t pm_data_status;
	aocs_cntrl_types_t used_aocs_type;

	used_aocs_type = get_enabled_aocs_type();

	if( AOCS_CNTRL_SYS_STATE_TARGET_TRACKING == sys_state )
	{
		aocs_pm_start_auto_logging();
	}
	else
	{
		aocs_pm_stop_auto_logging();
	}

	data_type_for_assessment = aocs_pm_get_data_type_for_assessment();

	pm_data_status = (aocs_cntrl_cfg[used_aocs_type].aocs_if->p_get_log_data(&get_data_to_pass_to_pm_algorythm ,data_type_for_assessment, &offset));

	/* this is a constant offset only for AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE and
	 *  AOCS_CNTRL_SYS_STATE_Y_THOMSON and when we are logging angullar rates */
	if(((AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE == sys_state) || (AOCS_CNTRL_SYS_STATE_Y_THOMSON == sys_state)) &&
		(EST_ANG_RATES == data_type_for_assessment))
	{
		offset.offset_value[0] = 0;
		offset.offset_value[1] = CONSTANT_OFFSET_FOR_Y_TOMSON;
		offset.offset_value[2] = 0;
	}

	aocs_pm_calc_performance(&get_data_to_pass_to_pm_algorythm, &offset, pm_data_status);
}
/** @brief Check if a new system state request has been generated
 *
 *	@param[out] aocs_cntrl_sys_state_types_t *p_sys_state - the requested system state
 *  @retval true: new request generated
 *  @retval false: no new request generated
 *
 */
STATIC bool fs_aocs_cntrl_is_new_sys_state_req(aocs_cntrl_sys_state_types_t *p_sys_state)
{
	CRIT_ASSERT(NULL != p_sys_state);

	bool op_res = false;

	DATA_CACHE_AOCS_CNTRL_SYS_STATE_t s_adcs_data;

	if ( DC_DATA_STATUS_OK == dc_get_aocs_cntrl_sys_state_data(&s_adcs_data) )
	{
		*p_sys_state = (aocs_cntrl_sys_state_types_t)s_adcs_data.u8AdcsSysState;

		if ( AOCS_CNTRL_SYS_STATE_STATE_REQ_NEW_REQ == s_adcs_data.u8AdcsSysStateStatus )
		{
			op_res = true;
		}
	}
	else
	{
	    *p_sys_state = AOCS_CNTRL_SYS_NUMBER;
	}

	return op_res;
}

/** @brief Set the AOCS general data cache data
 *
 *	@note This function updates the general AOCS data cache entry
 *
 */
STATIC void fs_aocs_cntrl_set_aocs_dc_data(void)
{
	AOCS_CNTRL_TRACE_DBG("%s: READ AOCS DC DATA\r", AOCS_CNTRL_HEAD_DBG);

	DATA_CACHE_AOCS_CNTRL_TLM_t s_adcs_data;

	aocs_cntrl_aocs_sys_errs aocs_sys_errs = (aocs_cntrl_aocs_sys_errs)0;
	aocs_cntrl_est_ang_rate_t est_ang_rates = { .X = (int32_t)0, .Y = (int32_t)0, .Z = (int32_t)0};
	aocs_cntrl_est_ang_rate_norm est_ang_rate_norm = (aocs_cntrl_est_ang_rate_norm)0;
	aocs_cntrl_est_att_t est_att_angles = {.roll = (int32_t)0, .pitch = (int32_t)0, .yaw = (int32_t)0};
	aocs_cntrl_wheel_speed_t meas_wheel_speed = {.rwl0_speed = (int16_t)0, .rwl1_speed = (int16_t)0,
	                                             .rwl2_speed = (int16_t)0, .rwl3_speed = (int16_t)0};

	aocs_cntrl_types_t used_aocs_type;

	used_aocs_type = get_enabled_aocs_type();

	if ( used_aocs_type < AOCS_CNTRL_TYPE_MAX )
	{
		if ( AOCS_CNTRL_OK != aocs_cntrl_cfg[used_aocs_type].aocs_if->p_get_aocs_system_errors(&aocs_sys_errs) )
		{
			aocs_sys_errs = (aocs_cntrl_aocs_sys_errs)0;
		}

		if ( AOCS_CNTRL_OK != aocs_cntrl_cfg[used_aocs_type].aocs_if->p_get_est_ang_rates(&est_ang_rates, &est_ang_rate_norm) )
		{
			memset(&est_ang_rates, 0, sizeof(est_ang_rates));
			est_ang_rate_norm = (aocs_cntrl_est_ang_rate_norm)0;
		}

		if ( AOCS_CNTRL_OK != aocs_cntrl_cfg[used_aocs_type].aocs_if->p_get_est_att_ang(&est_att_angles) )
		{
			memset(&est_att_angles, 0, sizeof(est_att_angles));
		}

		if ( AOCS_CNTRL_OK != aocs_cntrl_cfg[used_aocs_type].aocs_if->p_get_meas_wheel_speed(&meas_wheel_speed) )
		{
			memset(&meas_wheel_speed, 0, sizeof(meas_wheel_speed));
		}
	}

	s_adcs_data.u32AdcsErrFlags = aocs_sys_errs;
	s_adcs_data.i32EstAngRateNorm = est_ang_rate_norm;

	memcpy(&s_adcs_data.ai32EstAngRateVec, &est_ang_rates, sizeof(s_adcs_data.ai32EstAngRateVec));
	memcpy(&s_adcs_data.ai32EstAttAngles, &est_att_angles, sizeof(s_adcs_data.ai32EstAttAngles));
	memcpy(&s_adcs_data.ai16MeasWheelSpeed, &meas_wheel_speed, sizeof(s_adcs_data.ai16MeasWheelSpeed));

	dc_set_aocs_cntrl_tlm_data(&s_adcs_data);
}

/** @brief Set the AOCS system state data cache entry
 *
 *	@param[in]: bool is_last_req_successful - function behaviour based on last system state update request
 *
 *	@note This function updates the AOCS system state data cache
 *
 */
STATIC void fs_aocs_cntrl_set_aocs_sys_state_dc_data(bool is_last_req_successful)
{
	AOCS_CNTRL_TRACE_DBG("%s: READ AOCS SYS STATE DC DATA\r", AOCS_CNTRL_HEAD_DBG);

	DATA_CACHE_AOCS_CNTRL_SYS_STATE_t s_aocs_sys_data;

	aocs_cntrl_sys_state_types_t sys_state = AOCS_CNTRL_SYS_STATE_UNDEFINED;
	aocs_cntrl_sys_state_req_state_t sys_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;

	aocs_cntrl_types_t used_aocs_type;

	used_aocs_type = get_enabled_aocs_type();

	if ( used_aocs_type < AOCS_CNTRL_TYPE_MAX )
	{
	    dc_get_aocs_cntrl_sys_state_data(&s_aocs_sys_data);

		if ( (true != is_last_req_successful) ||
		     (AOCS_CNTRL_SYS_STATE_EXISTING_CONTROL == s_aocs_sys_data.u8AdcsSysState))
		{
			AOCS_CNTRL_TRACE_DBG("%s: PREV REQ FAILED\r", AOCS_CNTRL_HEAD_DBG);

			sys_state = (aocs_cntrl_sys_state_types_t)s_aocs_sys_data.u8AdcsSysState;
			sys_state_req_state = (aocs_cntrl_sys_state_req_state_t)s_aocs_sys_data.u8AdcsSysStateStatus;
		}
		else if ( AOCS_CNTRL_OK != aocs_cntrl_cfg[used_aocs_type].aocs_if->p_sys_state_get_req_state(&sys_state, &sys_state_req_state) )
		{
		    TODO(This situation must be reconsidered. What shall be the stored state if no reliable feedback comes from the ADCS?)
			sys_state = AOCS_CNTRL_SYS_STATE_UNDEFINED;
			sys_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
		}
		else
		{
		    // Status of the last request has been successfully retrieved from ADCS driver/service
		}
	}

	s_aocs_sys_data.u8AdcsSysState = (uint8_t)sys_state;
	s_aocs_sys_data.u8AdcsSysStateStatus = (uint8_t)sys_state_req_state;

	dc_set_aocs_cntrl_sys_state_data(&s_aocs_sys_data);
}

/** @brief Check if a given instance of an if_aocs_cntrl realization has all of its methods defined.
 *         This is done to avoid runtime checks of function pointers for the interface methods
 *
 *  @param[in]: aocs_cntrl_t* p_if - reference to the interface realization
 *
 *  @return: true if all methods are defined, false otherwise
 */
STATIC bool fs_aocs_cntrl_is_interface_valid(const aocs_cntrl_t * const p_if)
{
    bool res = false;

    if ( (NULL != p_if->p_get_aocs_system_errors) &&
         (NULL != p_if->p_get_est_ang_rates) &&
         (NULL != p_if->p_get_est_att_ang) &&
         (NULL != p_if->p_get_log_data) &&
         (NULL != p_if->p_get_meas_wheel_speed) &&
         (NULL != p_if->p_sys_state_chng_req) &&
         (NULL != p_if->p_sys_state_get_req_state) &&
         (NULL != p_if->p_get_cms_status) &&
         (NULL != p_if->p_get_cntrl_status) )
    {
        res = true;
    }

    return res;
}

/** @brief Retrieve from DataCache reference parameters for some ADCS control modes
 *
 *  @param[out]: aocs_cntrl_reference_params_t* p_ref_params - destination location for the parameters
 *
 *  @return: true if all methods are defined, false otherwise
 */
STATIC bool fs_aocs_cntrl_get_ref_params(aocs_cntrl_reference_params_t * const p_ref_params)
{
    bool res = false;

    if (NULL != p_ref_params)
    {
        DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t params;
        const dc_data_status_t dc_status = dc_get_aocs_cntrl_ref_params_data(&params);
        // Reference parameters are not expected to be written periodically so it is not an issue to
        // get a timeout status for the DC read operation. DC data will still have its last set values.
        if ( (DC_DATA_STATUS_OK == dc_status) || (DC_DATA_STATUS_TOUT == dc_status) )
        {
            p_ref_params->ref_param_1 = params.fRefParam1;
            p_ref_params->ref_param_2 = params.fRefParam2;
            p_ref_params->ref_param_3 = params.fRefParam3;

            res = true;
        }
    }

    return res;
}

/** @brief Write in DataCache reference parameters for some ADCS control modes
 *
 *  @param[in]: aocs_cntrl_reference_params_t* p_ref_params - the parameters to be written
 *
 *  @note: This function must be called only from aocs_cntrl_request_aocs_state!
 */
STATIC void fs_aocs_cntrl_set_ref_params(const aocs_cntrl_reference_params_t * const p_ref_params)
{
    if (NULL != p_ref_params)
    {
        DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t dc_params = {.fRefParam1 = p_ref_params->ref_param_1,
                                                        .fRefParam2 = p_ref_params->ref_param_2,
                                                        .fRefParam3 = p_ref_params->ref_param_3};
        dc_set_aocs_cntrl_ref_params_data(&dc_params);
    }
}

/* ******************************************************************************************* */
