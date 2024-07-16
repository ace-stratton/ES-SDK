/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup app_conops
 * @{
 *
 * @file conops_periodic_ev_task.c
 * @brief Periodic Event Task for the ConOps SM
 *
 * @}
 *
 */

#if defined(OPMODES_ENABLED)

#include "conops.h"
#include "conops_periodic_ev_task.h"

#include "libhsm.h"

#include "es_cdef.h"
#include "TaskMonitor.h"
#include "es_exeh.h"
#include "if_sys_conf.h"

#include "datacache.h"
#include "aocs_cntrl.h"
#include "cubeadcs.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_CON_OPS

/** @brief RPY check OK value */
#define CONOPS_RPY_CHECK_OK	(3U)

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/** @brief Sun Tracking Transition states
 *
 *	todo:
 *	- Refactor to be more general and to cover different ADCS
 *	- Add detumbling state (for ADCS which have no Y_Thomson modes
 */
typedef enum {
	STT_None,
	STT_Y_Thomson,
	STT_Y_Momentum_Initial,
	STT_3Axis,
	STT_Sun_Tracking,
	STT_Completed,

	STT_Max,

} eSTT_states_t;

/** @brief RPY values in the data arrays
 *
 */
enum {
	Roll 	= 0,
	Pitch 	= 1,
	Yaw 	= 2
};

/** @brief XYZ axis values in the data arrays
 *
 */
enum {
	X = 0,
	Y = 1,
	Z = 2
};

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
static       osThreadId_t   conops_p_ev_task_taskHandle;
static const osThreadAttr_t conops_p_ev_task_attributes = {
  .name = "fs_ConOps_P_EV_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 16
};

#ifdef DEBUG_TRACE_OP_MODES_ENABLED
static const char *stt_state_strings[STT_Max] = {
		"STT_None",
		"STT_Y_Thomson",
		"STT_Y_Momentum_Initial",
		"STT_3Axis",
		"STT_Sun_Tracking",
		"STT_Completed"
};
#endif // DEBUG_TRACE_OP_MODES_ENABLED

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
STATIC void fs_conops_p_ev_task(void *arg);
STATIC void fs_conops_p_ev_sun_track_sequence(void);
STATIC void fs_conops_p_ev_track_emergency_shutdown(void);
STATIC bool fs_conops_p_ev_is_y_momentum_rdy(void);
STATIC bool fs_conops_p_ev_is_3axis_cntrl_rdy(void);

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void conops_p_ev_init(void)
{
	EXEH_INIT_MODULE_FILENAME();

	conops_p_ev_task_taskHandle = osThreadNew(fs_conops_p_ev_task, NULL, &conops_p_ev_task_attributes);

	if ( NULL == conops_p_ev_task_taskHandle )
	{
		EXEH_HANDLE(eEXEHSeverity_Fatal, eEXEH_CON_OPS_EXCEPTION_TASK_INIT_FAILURE);
	}
	else
	{
		TaskMonitor_TaskInitialized(TASK_CONOPS_PERIODIC_EV);
	}
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/**
 * @brief The conops periodic task
 *
 * @param[in] void *arg - task arguments
 *
 * @note Refreshed the runtime copies of the relevant nvm entries
 *  	 Triggers the periodic check of the ConOps StateMachine
 *  	 Shutdown and sun tracking services
 */
STATIC void fs_conops_p_ev_task(void *arg)
{
    for(;;)
    {
    	conops_refresh_runtime_nvm_copies();

    	conops_trigger_hsm(eHSM_StdEvent_Periodic, NULL);

    	fs_conops_p_ev_track_emergency_shutdown();

    	fs_conops_p_ev_sun_track_sequence();

        TaskMonitor_IamAlive(TASK_CONOPS_PERIODIC_EV);
        vApplicationLowStackCheck(TASK_CONOPS_PERIODIC_EV);

        osDelay(CONOPS_PER_EV_TASK_PERIOD);
    }
}

/**
 * @brief Automatic sun-tracking sequence logic
 *
 * @param[in] void *arg - task arguments
 *
 * @note MUST be called after conops_trigger_hsm()
 */
STATIC void fs_conops_p_ev_sun_track_sequence(void)
{
    static eSTT_states_t eTState = STT_None;

    uint8_t eOpModeNum;
    aocs_cntrl_sys_state_types_t aocs_state;
    aocs_cntrl_sys_state_req_state_t aocs_state_req_state;

    conops_get_hsm_active_state(&eOpModeNum);

    if ( (false != conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state)) &&
         (AOCS_CNTRL_SYS_STATE_UNDEFINED != aocs_state) &&
         (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == aocs_state_req_state) )
    {
        if ( STATE_SAFE == eOpModeNum )
        {
            /* This check assumes that we have completed detumbling in the context of Detumbling Mode */
            if ( AOCS_CNTRL_SYS_STATE_Y_THOMSON == aocs_state ) {
                eTState = STT_Y_Thomson;

                CONOPS_TRACE_INFO("%s: STT Y-Thomson Started: Last STT: %s\r", CONOPS_SM_STT_DBG, stt_state_strings[eTState]);
            }

            if ( AOCS_CNTRL_SYS_STATE_NO_CONTROL == aocs_state ) {
                eTState = STT_None;

                CONOPS_TRACE_INFO("%s: NEW STT Started: Last STT: %s\r", CONOPS_SM_STT_DBG, stt_state_strings[eTState]);
            }
        }

        CONOPS_TRACE_INFO("%s: OpMode: %d ---- STT_State: %s\r", CONOPS_SM_STT_DBG, eOpModeNum, stt_state_strings[eTState]);

        aocs_cms_status_t eCmsStatus;

        if ( (STATE_SAFE == eOpModeNum) && aocs_cntrl_get_cms_status(&eCmsStatus) )
        {
            switch ( eTState )
            {
            case STT_None:
            {
                if ( CMS_COMPLETE == eCmsStatus ) {
                    conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING, NULL);

                    eTState = STT_Y_Thomson;
                }

                break;
            }

            case STT_Y_Thomson:
            {
                if ( CMS_COMPLETE == eCmsStatus ) {
                    conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_Y_MOMENTUM, NULL);

                    eTState = STT_Y_Momentum_Initial;
                }

                break;
            }

            case STT_Y_Momentum_Initial:
            {
                if ( true == conops_get_enable_sun_tracking_flag() ) {
                    if ( true == fs_conops_p_ev_is_y_momentum_rdy() ) {
                        if ( CMS_COMPLETE == eCmsStatus ) {
                            const aocs_cntrl_reference_params_t rpy_params = {0.0f, 0.0f, 0.0f};
                            conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_3AXIS, &rpy_params);

                            eTState = STT_3Axis;
                        }
                    }
                }

                break;
            }

            case STT_3Axis:
            {
                if ( true == conops_get_enable_sun_tracking_flag() ) {
                    if ( true == fs_conops_p_ev_is_3axis_cntrl_rdy() ) {
                        if ( CMS_COMPLETE == eCmsStatus ) {
                            conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_SUN_TRACKING, NULL);

                            eTState = STT_Sun_Tracking;
                        }
                    }
                }

                break;
            }

            case STT_Sun_Tracking:
            {
                eTState = STT_Completed;

                break;
            }

            default:
                break;
            }

            CONOPS_TRACE_INFO("%s: OpMode: %d ---- NEW STT_State: %s\r", CONOPS_SM_STT_DBG, eOpModeNum, stt_state_strings[eTState]);
        }
    }
}


/**
 * @brief Track for an approaching emergency shutdowns
 *
 * @note In case of critical battery drop the EPS subsystem may choose to cut power to the ADCS and/or
 * 		 other subsystems. Actions such as stopping file transfers, etc. can be performed here.
 */
STATIC void fs_conops_p_ev_track_emergency_shutdown(void)
{
	return;
}

/**
 * @brief Check if steady Y-Momentum state has been achieved
 *
 * @return bool
 */
STATIC bool fs_conops_p_ev_is_y_momentum_rdy(void)
{
	bool bRes;

	DATA_CACHE_AOCS_CNTRL_TLM_t sAdcsData;
	uint8_t u8Chk = 0;

	bRes = false;

	if ( DC_DATA_STATUS_OK == dc_get_aocs_cntrl_tlm_data(&sAdcsData) )
	{
		if ( (CONOPS_RPY_MDEG_THRESH > sAdcsData.ai32EstAttAngles[Roll]) && (-CONOPS_RPY_MDEG_THRESH < sAdcsData.ai32EstAttAngles[Roll]) )
		{
			++u8Chk;
		}

		if ( (CONOPS_RPY_MDEG_THRESH > sAdcsData.ai32EstAttAngles[Pitch]) && (-CONOPS_RPY_MDEG_THRESH < sAdcsData.ai32EstAttAngles[Pitch]) )
		{
			++u8Chk;
		}

		if ( (CONOPS_RPY_MDEG_THRESH > sAdcsData.ai32EstAttAngles[Yaw]) && (-CONOPS_RPY_MDEG_THRESH < sAdcsData.ai32EstAttAngles[Yaw]) )
		{
			++u8Chk;
		}

		if ( CONOPS_RPY_CHECK_OK == u8Chk)
		{
			bRes = true;
		}
	}

	return bRes;
}

/**
 * @brief Check if stable 3-Axis state has been achieved
 *
 * @note Waits until the Y-Wheel momentum has been dumped
 *
 * @return bool
 */
STATIC bool fs_conops_p_ev_is_3axis_cntrl_rdy(void)
{
	bool bRes;

	bRes = true;

	DATA_CACHE_AOCS_CNTRL_TLM_t sAdcsData;

	if ( DC_DATA_STATUS_OK == dc_get_aocs_cntrl_tlm_data(&sAdcsData) )
	{
	    for (uint32_t idx = 0; idx < CDEF_ELEMENT_COUNT(sAdcsData.ai16MeasWheelSpeed); idx++)
	    {
	        if ( (CONOPS_Y_WHEEL_RPM_THRESH <= sAdcsData.ai16MeasWheelSpeed[idx]) &&
                 (-CONOPS_Y_WHEEL_RPM_THRESH >= sAdcsData.ai16MeasWheelSpeed[idx]) )
            {
                bRes = false;
                break;
            }
	    }
	}

	return bRes;
}

#endif /* OPMODES_ENABLED */
/* ******************************************************************************************* */
