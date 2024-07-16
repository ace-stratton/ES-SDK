/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup actuator_cntrl_service
 * @{
 *
 * @file     actuator_control_service.c
 * @brief    Actuator Control Service source file
 *
 * @}
 */

#include <string.h>
#include <stdlib.h>
#include "datacache.h"
#include "es_exeh.h"
#include "TaskMonitor.h"
#include "panels.h"

#include "actuator_control_service.h"
#include "es_coordsys.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID (eEXEHModuleID_ACTUATOR_CONTROL_SERVICE)

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief DataCache magnetorquer block */
static DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t mtq_control_values_sat_frame_DC;

/** @brief Data cache error variable */
static dc_data_status_t data_cache_error_actuators;

/** @brief Store the control values and their direction in the satellite and magnetorquer frame */
static int8_t  mtq_control_values_sat_frame[MAGNETORQUER_QUANTITY];
static int8_t  mtq_control_values_mtq_frame[MAGNETORQUER_QUANTITY];
static uint8_t mtq_control_values_directions[MAGNETORQUER_QUANTITY];

/** @brief Actuator control service mode (state) */
static actuator_control_service_state_t activeState = ACTUATOR_CONTROL_SERVICE_STATE_INACTIVE;

/** @brief Holds the latest error found in the service execution */
static actuator_control_service_error_t lastError;

/** @brief Holds essential information about the actuator control service */
static actuator_control_service_status_t status;

/** @brief Actuator control service FreeRTOS Task related variables */
static osThreadId_t actuator_control_service_Task_TaskHandle;
static const osThreadAttr_t actuator_control_service_Task_attributes =
{
        .name = "actuator_control_service_Task",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 128 * 8
};

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
static void fs_actuator_control_service_Task(void *arg);
static void fs_actuator_control_service_update_status(void);
static void fs_magnetorquers_actuate(void);
static void fs_magnetorquers_stop(void);
static void fs_get_magnetorquers_direction(const int8_t *inputData, uint8_t *outputDirections);

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
void actuator_control_service_init(void)
{
    EXEH_INIT_MODULE_FILENAME();

    /* Make sure the task logic doesn't run until told to by the ADCS */
    activeState = ACTUATOR_CONTROL_SERVICE_STATE_INACTIVE;

    /* Spawn the task */
    actuator_control_service_Task_TaskHandle = osThreadNew(fs_actuator_control_service_Task, NULL, &actuator_control_service_Task_attributes);
    CRIT_ASSERT( actuator_control_service_Task_TaskHandle );

    /* Notify task monitor that the actuator control service task is initialized */
    TaskMonitor_TaskInitialized (TASK_ACTUATOR_CONTROL_SERVICE);
    task_mon_set_task_policy(TASK_ACTUATOR_CONTROL_SERVICE, TASK_MON_POLICY_MONITOR);
}

void actuator_control_service_start(void)
{
    /*
     * (this is to be called when ADCS switches from IDLE to any mode)
     */

    if (ACTUATOR_CONTROL_SERVICE_STATE_ACTIVE != activeState)
    {
        /* Reactivate the task logic */
        activeState = ACTUATOR_CONTROL_SERVICE_STATE_ACTIVE;

        /* Initialize physical magnetorquer hardware */
        MCU_MagnetorqersInit();
    }
}

void actuator_control_service_stop(void)
{
    /*
     * (this is to be called when ADCS switches from any mode to IDLE)
     * stop function should also force all actuators to 0 (or turn off)
     */

    if (ACTUATOR_CONTROL_SERVICE_STATE_INACTIVE != activeState)
    {
        /* Make the task dormant */
        activeState = ACTUATOR_CONTROL_SERVICE_STATE_INACTIVE;

        /* Clear magnetorquer outputs */
        fs_magnetorquers_stop();

        /* Deinitialize physical magnetorquer hardware */
        MCU_MagnetorqersDeInit();
    }
}

actuator_control_service_status_t actuator_control_service_get_status(void)
{
    return status;
}

void actuator_control_service_get_last_mtq_control(int8_t *lastMtqControlValues)
{
    memcpy(lastMtqControlValues, mtq_control_values_mtq_frame, sizeof(mtq_control_values_mtq_frame));
}

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief The FreeRTOS task responsible for actuator control service logic
 *  @param[in] void *arg - task arguments */
static void fs_actuator_control_service_Task(void *arg)
{
    /*
     * this should only call each different type of actuator handler
     * the rest is done inside the handler itself, keep it clean
     */

    for (;;)
    {
        TaskMonitor_IamAlive(TASK_ACTUATOR_CONTROL_SERVICE);

        switch (activeState)
        {
            case ACTUATOR_CONTROL_SERVICE_STATE_ACTIVE:
            {
                /* Actuate magnetorquers */
                fs_magnetorquers_actuate();

                /* Add any future actuators here */

                break;
            }
            case ACTUATOR_CONTROL_SERVICE_STATE_INACTIVE:
            {
                /* Remain dormant until changed by ADCS mode switch or satellite operator (through FP) */
                break;
            }
            default:
            {
                /* State out of bounds - report through es_exeh */
                EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ACTUATOR_CONTROL_SERVICE_INVALID_STATE);
                break;
            }
        }

        /* Update service-wide status variable */
        fs_actuator_control_service_update_status();

        /* The task sleeps for the rest of the sampling period */
        vApplicationLowStackCheck(TASK_ACTUATOR_CONTROL_SERVICE);
        osDelay(ACTUATOR_CONTROL_SERVICE_SAMPLING_TIME_MS);
    }
}

/** @brief Actuator control service update status function, responsible for updating the status variable */
static void fs_actuator_control_service_update_status(void)
{
    status.state     = activeState;
    status.lastError = lastError;
}

/** @brief Actuate magnetorquers */
static void fs_magnetorquers_actuate(void)
{
    /*
     * 1. read datacache
     * 2. use es_coordsys transform
     * 3. determine directions
     * 4. scale (if necessary) to appropriate control units
     * 5. send to actuator
     */

    lastError = ACTUATOR_CONTROL_SERVICE_ERROR_NONE;

    /* Retrieve control values from DataCache */
    data_cache_error_actuators = dc_get_es_adcs_control_values_mtq_data(&mtq_control_values_sat_frame_DC);

    /* Catch any DataCache read failure */
    if (DC_DATA_STATUS_OK != data_cache_error_actuators)
    {
        /* DataCache readout failed - raise an error */
        lastError = ACTUATOR_CONTROL_SERVICE_ERROR_DATA_CACHE_GET;

        /* Report through es_exeh */
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ACTUATOR_CONTROL_SERVICE_MTQ_DC_READ_FAIL);
        return;
    }

    /* Use es_coordsys to transform from satellite frame to actuator frame */
    memcpy(mtq_control_values_sat_frame, &mtq_control_values_sat_frame_DC, sizeof(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t));

    if (!coordSys_transformMtq(mtq_control_values_sat_frame, mtq_control_values_mtq_frame))
    {
        /* Coordinate frame transform failed - report through es_exeh */
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ACTUATOR_CONTROL_SERVICE_MTQ_COORD_SYS_FAIL);
        lastError = ACTUATOR_CONTROL_SERVICE_ERROR_COORD_SYS_TRANSFORM;
        return;
    }

    /* Determine direction of magnetorquer action */
    fs_get_magnetorquers_direction(mtq_control_values_mtq_frame, mtq_control_values_directions);

    /* No scaling needed - driver functions work with 0-100 range and direction 0-1 */

    /* Call driver function for magnetorquer */
    /*                       PAN1 PAN2 PAN3 PAN4 PAN5 PAN6 */
    /* Satellite frame:       Y-   X-   Z-   Z+   Y+   X+  */
    SetMagnetorque(PAN_X_M, (uint8_t)(abs(mtq_control_values_mtq_frame[0])), mtq_control_values_directions[0]);    /* PAN4 */
    SetMagnetorque(PAN_Y_M, (uint8_t)(abs(mtq_control_values_mtq_frame[1])), mtq_control_values_directions[1]);    /* PAN5 */
    SetMagnetorque(PAN_Z_M, (uint8_t)(abs(mtq_control_values_mtq_frame[2])), mtq_control_values_directions[2]);    /* PAN6 */
    /* Accessing elements of the array like this is very ugly, but probably faster than a for */

    /* AA TODO: the enum (1st parameter) of SetMagnetorque is very, very confusing */
    /* It should really be redesigned when given the chance */
}

/** @brief Stop magnetorquers */
static void fs_magnetorquers_stop(void)
{
    /*
     * 1. zero out all control values (or whatever represents a turned off actuator)
     * 2. send to actuator
     */
    /* AA TODO: Check if we really need to zero out the values or just pass temporary zeroes to the driver function */
    for (uint8_t i = 0; i < MAGNETORQUER_QUANTITY; i++)
    {
        mtq_control_values_mtq_frame[i] = 0;
    }

    /* Accessing elements of the array like this is very ugly, but probably faster than a for */
    SetMagnetorque(PAN_X_M, (uint8_t)(abs(mtq_control_values_mtq_frame[0])), mtq_control_values_directions[0]);    /* PAN4 */
    SetMagnetorque(PAN_Y_M, (uint8_t)(abs(mtq_control_values_mtq_frame[1])), mtq_control_values_directions[1]);    /* PAN5 */
    SetMagnetorque(PAN_Z_M, (uint8_t)(abs(mtq_control_values_mtq_frame[2])), mtq_control_values_directions[2]);    /* PAN6 */
}

/** @brief Derive magnetorquer directions based on control values
 *  @param[in]  inputData pointer to array with the input magnetorquer control values transformed to actuator frame
 *	@param[out] outputDirections pointer to array with directions of magnetorquer action */
static void fs_get_magnetorquers_direction(const int8_t *inputData, uint8_t *outputDirections)
{
    /* 3 magnetorquers for now */
    for (uint8_t i = 0; i < MAGNETORQUER_QUANTITY; i++)
    {
        if (inputData[i] >= 0)
        {
            outputDirections[i] = 1;
        }
        else
        {
            outputDirections[i] = 0;
        }
    }
}

/* ******************************************************************************************* */
