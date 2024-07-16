/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup es_adcs
 * @{
 *
 * @file     es_adcs.c
 * @brief    EnduroSat ADCS main source file
 *
 * @}
*/

#include "es_exeh.h"
#include "TaskMonitor.h"
#include "trace.h"
#include "nvm.h"
#include "es_adcs.h"
#include "es_adcs_op_modes_sm_user.h"
#include "assertions.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID  (eEXEHModuleID_ES_ADCS)

/** @brief The ADCS HSM instance */
#define ES_ADCS_SM_INSTANCE	    (es_adcs_op_modes_sm_instance)

/**********************************************************************
 *
 * External type definitions
 *
 **********************************************************************/
if_sys_mod_t adcs_module_configuration = {
    .init = es_adcs_init,
    .run = es_adcs_start,
    .stop = es_adcs_stop,
    .deinit = es_adcs_deinit,
};

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief The active ADCS configuration */
static es_adcs_config_t es_adcs_config_active;

/** @brief Main ADCS status variable */
static es_adcs_status_t es_adcs_status;

/** @brief Number of errors occured. Reset on every initialization */
static uint16_t es_adcs_latched_errors;

/** @brief
 * Estimator execution result, simplified to OK/FAIL. More information can be extracted using specific get estimator status function */
static es_adcs_result_t es_adcs_estimator_result;

/** @brief
 * Controller result, simplified to OK/FAIL. More information can be extracted using specific get controller status function */
static es_adcs_result_t es_adcs_controller_result;

/** @brief This variable is used to skip the first control loop after changing from IDLE to RUN/TRIGGER state.
 * This is done so that the sensors have ample time to build up information in the DataCache with
 * the appropriate sampling rate.
 * This variable will be controlled from the ADCS HSM state transition actions */
static uint8_t es_adcs_skipLoop = 0;

/** @brief ES ADCS FreeRTOS Task related variables */
static osThreadId_t es_adcs_Task_TaskHandle;
static const osThreadAttr_t es_adcs_Task_attributes =
{
        .name = "es_adcs_Task",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 128 * 16
};

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
static void             fs_es_adcs_Task(void *arg);
static void             fs_es_adcs_control_loop(void);
static void             fs_es_adcs_stop_magnetorquers(void);
static void             fs_es_adcs_update_status(void);
static void             fs_es_adcs_trigger_HSM(uint32_t id);
static const sState_t * fs_es_adcs_get_op_mode(void);

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
mod_op_status_id_t es_adcs_init(sys_init_level_id_t level)
{
    mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

    EXEH_INIT_MODULE_FILENAME();

    if (level == INIT_OS)
    {
        /* Load the active config from NVM */
        es_adcs_load_config_from_NVM();

        /* Check if the estimator can be initialized */
        es_adcs_estimator_result  = es_adcs_estimate_init();

        /* Check if the controller can be initialized */
        es_adcs_controller_result = es_adcs_control_init();

        /* Initialization complete, move forward with spawning the task */
        if((ES_ADCS_RESULT_OK == es_adcs_estimator_result) && (ES_ADCS_RESULT_OK == es_adcs_controller_result))
        {
            /* Zero out the latched errors counter */
            es_adcs_latched_errors = 0;

            /* Spawn the task */
            es_adcs_Task_TaskHandle = osThreadNew(fs_es_adcs_Task, NULL, &es_adcs_Task_attributes);
            CRIT_ASSERT( es_adcs_Task_TaskHandle );

            /* Notify task monitor that the es adcs task is initialized */
            TaskMonitor_TaskInitialized (TASK_MONITOR_ES_ADCS);

            /* Make sure task monitor is actively monitoring the task */
            task_mon_set_task_policy(TASK_MONITOR_ES_ADCS, TASK_MON_POLICY_MONITOR);

            /* Print ADCS HSM root state */
            ES_TRACE_DEBUG("[es_adcs_init] ROOT state: %d\r", es_adcs_get_op_mode());

            /* Reset the ADCS HSM and put it in STATE_ADCS_NOT_INIT */
            fs_es_adcs_trigger_HSM(eHSM_StdEvent_Reset);
            ES_TRACE_DEBUG("[es_adcs_init] NOT_INIT state: %d\r", es_adcs_get_op_mode());

            /* Move the ADCS HSM to STATE_ADCS_IDLE */
            fs_es_adcs_trigger_HSM(ev_es_adcs_op_modes_sm_start);
            ES_TRACE_DEBUG("[es_adcs_init] IDLE state: %d\r", es_adcs_get_op_mode());

            ret = STATUS_OK;
        }
        else
        {
            /* Initialization failed, report through console */
            ES_TRACE_DEBUG("[es_adcs_init] ********************** INIT FAILED\r");

            /* ES ADCS initialization failed - report through es_exeh */
            EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_INIT_FAIL);
            es_adcs_latched_errors++;

            /* Update general ADCS status */
            fs_es_adcs_update_status();

            /* Make sure task monitor is no longer monitoring the task */
            task_mon_set_task_policy(TASK_MONITOR_ES_ADCS, TASK_MON_POLICY_DONT_CARE);

            ret = STATUS_FAILED;
        }
    }

    return ret;
}

mod_op_status_id_t es_adcs_start(void)
{
    mod_op_status_id_t ret = STATUS_FAILED;

    /* Move the ADCS HSM to STATE_ADCS_RUN */
    ES_TRACE_DEBUG("[es_adcs_start]");
    es_adcs_set_op_mode(STATE_ADCS_RUN);

    ret = STATUS_OK;

    return ret;
}

mod_op_status_id_t es_adcs_stop(void)
{
    mod_op_status_id_t ret = STATUS_FAILED;

    /* Move the ADCS HSM to STATE_ADCS_IDLE */
    ES_TRACE_DEBUG("[es_adcs_stop]");
    es_adcs_set_op_mode(STATE_ADCS_IDLE);

    ret = STATUS_OK;

    return ret;
}

mod_op_status_id_t es_adcs_deinit(sys_init_level_id_t level)
{
    mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

    /* AA TODO: what else do i put in here? */

    if (level == INIT_OS)
    {
        task_mon_set_task_policy(TASK_MONITOR_ES_ADCS, TASK_MON_POLICY_DONT_CARE);

        ret = STATUS_OK;
    }

    return ret;
}

uint16_t es_adcs_get_latched_errors(void)
{
    return es_adcs_latched_errors;
}

es_adcs_status_t es_adcs_get_status(void)
{
    return es_adcs_status;
}

es_adcs_estimator_status_t es_adcs_get_status_estimator(void)
{
    return es_adcs_estimator_get_status();
}

es_adcs_controller_status_t es_adcs_get_status_controller(void)
{
    return es_adcs_controller_get_status();
}

void es_adcs_set_skip_loop(void)
{
    es_adcs_skipLoop = 1;
}

void es_adcs_set_op_mode(uint8_t desiredOpMode)
{
    uint8_t currentOpMode = es_adcs_get_op_mode();

    switch (desiredOpMode)
    {
        case STATE_ADCS_RUN:
        {
            if (STATE_ADCS_IDLE == currentOpMode)
            {
                /* Valid transition: IDLE to RUN */
                fs_es_adcs_trigger_HSM(ev_es_adcs_op_modes_sm_idle_to_run);
                ES_TRACE_DEBUG(" OP MODE SWITCH: IDLE -> RUN --- executed\r");
            }
            else if (STATE_ADCS_TRIGGER == currentOpMode)
            {
                /* Forbidden transition TRIGGER to RUN */
                ES_TRACE_DEBUG(" OP MODE SWITCH: TRIGGER -> RUN --- FORBIDDEN, DID NOT EXECUTE\r");
            }
            else
            {
                /* Attempted RUN to RUN transition, do nothing */
                ES_TRACE_DEBUG(" OP MODE SWITCH: RUN -> RUN --- No op mode change occured\r", desiredOpMode);
            }
            break;
        }

        case STATE_ADCS_TRIGGER:
        {
            if (STATE_ADCS_IDLE == currentOpMode)
            {
                /* Valid transition: IDLE to TRIGGER */
                fs_es_adcs_trigger_HSM(ev_es_adcs_op_modes_sm_idle_to_trigger);
                ES_TRACE_DEBUG(" OP MODE SWITCH: IDLE -> TRIGGER --- executed\r");
            }
            else if (STATE_ADCS_RUN == currentOpMode)
            {
                /* Valid transition: RUN to TRIGGER */
                fs_es_adcs_trigger_HSM(ev_es_adcs_op_modes_sm_run_to_trigger);
                ES_TRACE_DEBUG(" OP MODE SWITCH: RUN -> TRIGGER --- executed\r");
            }
            else
            {
                /* Attempted TRIGGER to TRIGGER transition, do nothing */
                ES_TRACE_DEBUG(" OP MODE SWITCH: TRIGGER -> TRIGGER --- No op mode change occured\r");
            }
            break;
        }

        case STATE_ADCS_IDLE:
        {
            if (STATE_ADCS_RUN == currentOpMode)
            {
                /* Valid transition: RUN to IDLE */
                fs_es_adcs_trigger_HSM(ev_es_adcs_op_modes_sm_run_to_idle);
                ES_TRACE_DEBUG(" OP MODE SWITCH: RUN -> IDLE --- executed\r");
            }
            else if (STATE_ADCS_TRIGGER == currentOpMode)
            {
                /* Valid transition: TRIGGER to IDLE */
                fs_es_adcs_trigger_HSM(ev_es_adcs_op_modes_sm_trigger_to_idle);
                ES_TRACE_DEBUG(" OP MODE SWITCH: TRIGGER -> IDLE --- executed\r");
            }
            else
            {
                /* Attempted IDLE to IDLE transition, do nothing */
                ES_TRACE_DEBUG(" OP MODE SWITCH: IDLE -> IDLE --- No op mode change occured\r", desiredOpMode);
            }
            break;
        }

        default:
        {
            /* Either state ROOT, state NOT_INIT or a completely invalid state */

            /* Desired state out of bounds - report through console */
            ES_TRACE_DEBUG(" OP MODE SWITCH: FAILED - state_id not valid\r");

            /* Desired state out of bounds - report through es_exeh */
            EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_OP_MODE_SWITCH_INVALID);
            es_adcs_latched_errors++;
            break;
        }
    }
}

uint8_t es_adcs_get_op_mode(void)
{
    return fs_es_adcs_get_op_mode()->state_id;
}

void es_adcs_set_estimator(es_adcs_estimator_t desiredEstimator1, es_adcs_estimator_t desiredEstimator2)
{
    /* AA TODO: this probably needs checks for valid estimator types, even though it is only called from FP functions */
    es_adcs_config_active.sEstimatorConfig.eActiveEstimators[0] = desiredEstimator1;
    es_adcs_config_active.sEstimatorConfig.eActiveEstimators[1] = desiredEstimator2;
}

void es_adcs_get_estimator(es_adcs_estimator_t *currentEstimators)
{
    CRIT_ASSERT(NULL != currentEstimators);

    currentEstimators[0] = es_adcs_config_active.sEstimatorConfig.eActiveEstimators[0];
    currentEstimators[1] = es_adcs_config_active.sEstimatorConfig.eActiveEstimators[1];
}

void es_adcs_set_controller(es_adcs_controller_t desiredController)
{
    /* AA TODO: this probably needs checks for valid controller types, even though it is only called from FP functions */
    es_adcs_config_active.sControllerConfig.eActiveController = desiredController;
}

es_adcs_controller_t es_adcs_get_controller(void)
{
    return es_adcs_config_active.sControllerConfig.eActiveController;
}

void es_adcs_set_controller_bdot_config(es_adcs_controller_bdot_config_t desiredBdotConfig)
{
    /* AA TODO: this probably needs checks for valid bdot controller config parameters, even though it is only called from FP functions */
    es_adcs_config_active.sControllerConfig.sBdotConfig = desiredBdotConfig;
}

es_adcs_controller_bdot_config_t es_adcs_get_controller_bdot_config(void)
{
    return es_adcs_config_active.sControllerConfig.sBdotConfig;
}

void es_adcs_set_used_magnetometer(es_adcs_used_magnetometer_t desiredMagnetometer)
{
    /* AA TODO: this probably needs checks for valid magnetometer types, even though it is only called from FP functions */
    es_adcs_config_active.eUsedMagnetometer = desiredMagnetometer;
}

es_adcs_used_magnetometer_t es_adcs_get_used_magnetometer(void)
{
    return es_adcs_config_active.eUsedMagnetometer;
}

void es_adcs_set_config(es_adcs_config_t desiredConfig)
{
    /* AA TODO: this probably needs an "is input config valid" check, even though it is only called from FP functions */
    es_adcs_config_active = desiredConfig;
}

es_adcs_config_t es_adcs_get_config(void)
{
    return es_adcs_config_active;
}

void es_adcs_save_config_to_NVM(void)
{
    Nvm_SetBlockById(NVM_BLOCK_ES_ADCS_CONFIG, &es_adcs_config_active, NVMSETBLOCK_STORE_IMMEDIATELY);
}

void es_adcs_load_config_from_NVM(void)
{
    es_adcs_config_t loadedConfig;

    /* AA TODO: this probably needs an "is input config valid" check, even though it loads
     * an NVM config that SHOULD HAVE BEEN checked upon saving */
    Nvm_GetBlockById(NVM_BLOCK_ES_ADCS_CONFIG, &loadedConfig);
    es_adcs_config_active = loadedConfig;
}

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief ADCS task, responsible for the ES ADCS functionality
 *  @param[in] void *arg - task arguments */
static void fs_es_adcs_Task(void *arg)
{
    for (;;)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_ES_ADCS);

        /* React differently based on ADCS operational mode */
        switch ( es_adcs_get_op_mode() )
        {
            case STATE_ADCS_IDLE:
            {
                /* Sits idle, doesn't do much for now */
                ES_TRACE_DEBUG("[es_adcs_Task] IDLE loop\r");
                break;
            }

            case STATE_ADCS_RUN:
            {
                /* Is this the first loop after mode switch? */
                if (es_adcs_skipLoop != 0)
                {
                    /* Reset the skipLoop variable */
                    es_adcs_skipLoop = 0;
                    ES_TRACE_DEBUG("[es_adcs_Task] RUN skip for sensors\r");
                }
                else
                {
                    /* Execute estimation and control */
                    fs_es_adcs_control_loop();
                    ES_TRACE_DEBUG("[es_adcs_Task] RUN loop\r");
                }
                break;
            }

            case STATE_ADCS_TRIGGER:
            {
                /* Is this the first loop after mode switch? */
                if (es_adcs_skipLoop != 0)
                {
                    /* Reset the skipLoop variable */
                    es_adcs_skipLoop = 0;
                    ES_TRACE_DEBUG("[es_adcs_Task] TRIGGER skip for sensors\r");
                }
                else
                {
                    /* Execute estimation and control */
                    fs_es_adcs_control_loop();
                    ES_TRACE_DEBUG("[es_adcs_Task] TRIGGER loop\r");

                    /* Move the ADCS HSM to STATE_ADCS_IDLE since trigger mode executes only once */
                    es_adcs_set_op_mode(STATE_ADCS_IDLE);
                }
                break;
            }

            default:
            {
                /* Either state ROOT or a completely invalid state */

                /* Active state out of bounds - report through console */
                ES_TRACE_DEBUG("[es_adcs_Task] STATE MACHINE FAIL. ENTERED -DEFAULT- STATE\r");

                /* Active state out of bounds - report through es_exeh */
                EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_OP_MODE_INVALID);
                es_adcs_latched_errors++;
                break;
            }
        }

        /* Update the ADCS status */
        fs_es_adcs_update_status();

        /* The task sleeps for the remainder of the ADCS Control loop time */
        vApplicationLowStackCheck(TASK_MONITOR_ES_ADCS);
        if (STATE_ADCS_IDLE == es_adcs_get_op_mode())
        {
            /* No estimators/controllers were executed in IDLE, thus the task needs to delay slightly longer */
            /* to account for no magnetorquer turn off time */
            osDelay(ES_ADCS_SAMPLING_TIME_MS + ES_ADCS_MAGNETORQUER_WAIT_TIME_MS);
        }
        else
        {
            /* Estimators and controllers were executed in these states, therefore the task has already */
            /* waited for the predefined magnetorquer turn off time */
            osDelay(ES_ADCS_SAMPLING_TIME_MS);
        }
    }
}

/** @brief ADCS control loop, responsible for the ES ADCS run and trigger modes */
static void fs_es_adcs_control_loop(void)
{
    /*
    * 1. stop magnetoruqers
    * 2. wait a bit - osDelay(magnetorquerWaitTime), 50ms would be good based on current magnetorquer step response
    * 3. call estimator
    * 4. call controller
    */

    /* Stop magnetorquers */
    fs_es_adcs_stop_magnetorquers();

    /* Wait magnetorquer stop time */
    osDelay(ES_ADCS_MAGNETORQUER_WAIT_TIME_MS);

    /* Call estimation */
    es_adcs_estimator_result = es_adcs_estimate(es_adcs_config_active.sEstimatorConfig, es_adcs_config_active.eUsedMagnetometer);

    /* Call controller, but only if estimator passed successfully */
    if (ES_ADCS_RESULT_OK == es_adcs_estimator_result)
    {
        es_adcs_controller_result = es_adcs_control(es_adcs_config_active.sControllerConfig);
    }
}

/** @brief Write turn off values to magnetorquers to prepare for control loop execution
 *  @note This makes use of the DataCache as a data connection between different subsystems */
static void fs_es_adcs_stop_magnetorquers(void)
{
    DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t zero_control_values;

    /* Zero control struct */
    zero_control_values.i8MAGTORQUE_VALUE_X = 0;
    zero_control_values.i8MAGTORQUE_VALUE_Y = 0;
    zero_control_values.i8MAGTORQUE_VALUE_Z = 0;

    /* Send turn off control values to data cache */
    dc_set_es_adcs_control_values_mtq_data(&zero_control_values);
}

/** @brief ADCS update status function, responsible for updating the main status variable */
static void fs_es_adcs_update_status(void)
{
    es_adcs_status.adcs_hsm_state   = es_adcs_get_op_mode();
    es_adcs_status.estimatorResult  = es_adcs_estimator_result;
    es_adcs_status.controllerResult = es_adcs_controller_result;
}

/** @brief Attempt a state machine transition operation
 *  @param[in] uint32_t id - the id of the desired event that triggers a transition, values are from enums es_adcs_op_modes_sm_events */
static void fs_es_adcs_trigger_HSM(uint32_t id)
{
    HSM_TriggerEvent(ES_ADCS_SM_INSTANCE, id);
}

/** @brief Get the current state of the es_adcs operation mode state machine
 *  @return sState_t * - pointer to HSM state struct, which contains the op mode state */
static const sState_t * fs_es_adcs_get_op_mode(void)
{
    return HSM_GetActiveState(ES_ADCS_SM_INSTANCE);
}

/* ******************************************************************************************* */
