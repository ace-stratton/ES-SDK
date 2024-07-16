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
 * @file     es_adcs_controllers.c
 * @brief    EnduroSat ADCS controller submodule source file
 *
 * @}
*/

#include "datacache.h"
#include "es_exeh.h"
#include "trace.h"
#include "es_adcs_controllers.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID  (eEXEHModuleID_ES_ADCS)

/** @brief Upper limit of acceptable Bdot control signal */
#define BDOT_SATURATION_UPPER 100

/** @brief Lower limit of acceptable Bdot control signal */
#define BDOT_SATURATION_LOWER -100

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
/** @brief Controller detailed status variable */
static es_adcs_controller_status_t controllerStatus;

/** @brief Data cache structs */
static DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t     bdot_estimates_controller;
static DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t bdot_control_values;

/** @brief Data cache error variable */
static dc_data_status_t data_cache_error_controller;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
static es_adcs_result_t                 fs_es_adcs_controller_detumbling_bdot_init(void);
static es_adcs_controller_algo_status_t fs_es_adcs_controller_detumbling_bdot(es_adcs_controller_bdot_config_t activeBdotConfig);

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
es_adcs_result_t es_adcs_control_init(void)
{
    /* Execution result variable */
    es_adcs_result_t result = ES_ADCS_RESULT_FAIL;

    /* No general controller inits so far, but could be present when more controllers are added */

    /* Init the first controller - detumbling bdot */
    result = fs_es_adcs_controller_detumbling_bdot_init();

    /* Send result back to caller */
    return result;
}

es_adcs_result_t es_adcs_control(es_adcs_controller_config_t controlConfig)
{
    /* 1. extract which algorithm to run from es_adcs_controller_config_t
     * 2. run algorithm
     * 3. report if there are errors in the return type
     */

    /* Execution result variable */
    es_adcs_result_t result = ES_ADCS_RESULT_FAIL;

    /* Set up the initial conditions for this loop */
    controllerStatus.lastWarningGeneral = ES_ADCS_CONTROLLER_WARN_NONE;
    controllerStatus.lastErrorGeneral   = ES_ADCS_CONTROLLER_ERROR_GENERAL;

    /* Execute controllers */
    switch( controlConfig.eActiveController )
    {
        case ES_ADCS_CONTROLLER_ALGO_NONE:
        {
            /* No control performed */
            break;
        }

        case ES_ADCS_CONTROLLER_ALGO_BDOT_MAG:
        {
            /* Perform Bdot control */
            controllerStatus.algoStatus = fs_es_adcs_controller_detumbling_bdot(controlConfig.sBdotConfig);
            break;
        }

        default:
        {
            /* Invalid controller algorithm chosen - raise an error */
            controllerStatus.lastErrorGeneral = ES_ADCS_CONTROLLER_ERROR_INVALID_ALGO;

            /* Report through es_exeh */
            EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_CONTROLLER_INVALID_TYPE);
            break;
        }
    }

    /* If the code reached this place and no errors have been reported, everything is ok */
    if ( (ES_ADCS_CONTROLLER_ERROR_GENERAL == controllerStatus.lastErrorGeneral)         &&
         (ES_ADCS_CONTROLLER_ERROR_NONE    == controllerStatus.algoStatus.lastErrorAlgo)   )
    {
        controllerStatus.lastErrorGeneral = ES_ADCS_CONTROLLER_ERROR_NONE;
        result = ES_ADCS_RESULT_OK;
    }

    return result;
}

es_adcs_controller_status_t es_adcs_controller_get_status(void)
{
    return controllerStatus;
}

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Detumbling B-dot controller init function
 *  @return es_adcs_result_t - has this passed successfully or not */
static es_adcs_result_t fs_es_adcs_controller_detumbling_bdot_init(void)
{
    /* Execution result variable */
    es_adcs_result_t result = ES_ADCS_RESULT_FAIL;

    /* The first controller - detumbling bdot - has no parameters to be initialized at this moment,
     * but it could be extended with further development
     */

    result = ES_ADCS_RESULT_OK;
    return result;
}

/** @brief Detumbling B-dot controller
 *  @param[in] es_adcs_controller_bdot_config_t - contains b-dot specific parameters
 *  @return    es_adcs_controller_algo_status_t - contains warnings and errors generated during algorithm execution */
static es_adcs_controller_algo_status_t fs_es_adcs_controller_detumbling_bdot(es_adcs_controller_bdot_config_t activeBdotConfig)
{
    /*
     * 0. magnetorquer starting shall be handled outside the controller (separate OBC task, preferably)
     * outline:
     * 1. retrieve estimated data from DataCache
     * 2. calculate magnetorquer drive strength (from -100 to +100) in each axis
     * 3. return calculated data to DataCache
     */

    es_adcs_controller_algo_status_t algoStatus;
    algoStatus.lastWarningAlgo = ES_ADCS_CONTROLLER_WARN_NONE;
    algoStatus.lastErrorAlgo   = ES_ADCS_CONTROLLER_ERROR_GENERAL;

    REAL estimated_magfield_deriv_x;
    REAL estimated_magfield_deriv_y;
    REAL estimated_magfield_deriv_z;

    REAL control_value_x;
    REAL control_value_y;
    REAL control_value_z;

    /* Get data from the estimator */
    data_cache_error_controller = dc_get_es_adcs_estimates_bdot_data(&bdot_estimates_controller);

    /* Catch any DataCache read failure */
    if (DC_DATA_STATUS_OK != data_cache_error_controller)
    {
        /* DataCache readout failed - raise an error */
        algoStatus.lastErrorAlgo = ES_ADCS_CONTROLLER_ERROR_DATA_CACHE_GET;

        /* Report through es_exeh */
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_CONTROLLER_BDOT_DC_READ_FAIL);
    }
    else
    {
        /* Measurements come in microT/s */
        estimated_magfield_deriv_x = (REAL)bdot_estimates_controller.i32MAG_FIELD_DERIV_X * ES_ADCS_uT_TO_T;
        estimated_magfield_deriv_y = (REAL)bdot_estimates_controller.i32MAG_FIELD_DERIV_Y * ES_ADCS_uT_TO_T;
        estimated_magfield_deriv_z = (REAL)bdot_estimates_controller.i32MAG_FIELD_DERIV_Z * ES_ADCS_uT_TO_T;

        /* Apply B-dot control law => out = - Gain * est_mag_field_deriv */
        control_value_x = - activeBdotConfig.bdot_coefficient_X * estimated_magfield_deriv_x;
        control_value_y = - activeBdotConfig.bdot_coefficient_Y * estimated_magfield_deriv_y;
        control_value_z = - activeBdotConfig.bdot_coefficient_Z * estimated_magfield_deriv_z;

        ES_TRACE_DEBUG("[es_adcs_controller] MTQ values pre-saturation: %.2f, %.2f, %.2f [%%]\r", control_value_x, control_value_y, control_value_z);

        /* Saturate the X signal */
        if (control_value_x > BDOT_SATURATION_UPPER)
        {
            control_value_x = BDOT_SATURATION_UPPER;
            algoStatus.lastWarningAlgo = ES_ADCS_CONTROLLER_WARN_SATURATION_UPPER;
        }
        if (control_value_x < BDOT_SATURATION_LOWER)
        {
            control_value_x = BDOT_SATURATION_LOWER;
            algoStatus.lastWarningAlgo = ES_ADCS_CONTROLLER_WARN_SATURATION_LOWER;
        }

        /* Saturate the Y signal */
        if (control_value_y > BDOT_SATURATION_UPPER)
        {
            control_value_y = BDOT_SATURATION_UPPER;
            algoStatus.lastWarningAlgo = ES_ADCS_CONTROLLER_WARN_SATURATION_UPPER;
        }
        if (control_value_y < BDOT_SATURATION_LOWER)
        {
            control_value_y = BDOT_SATURATION_LOWER;
            algoStatus.lastWarningAlgo = ES_ADCS_CONTROLLER_WARN_SATURATION_LOWER;
        }

        /* Saturate the Z signal */
        if (control_value_z > BDOT_SATURATION_UPPER)
        {
            control_value_z = BDOT_SATURATION_UPPER;
            algoStatus.lastWarningAlgo = ES_ADCS_CONTROLLER_WARN_SATURATION_UPPER;
        }
        if (control_value_z < BDOT_SATURATION_LOWER)
        {
            control_value_z = BDOT_SATURATION_LOWER;
            algoStatus.lastWarningAlgo = ES_ADCS_CONTROLLER_WARN_SATURATION_LOWER;
        }

        /* Convert to desired unit for DataCache */
        bdot_control_values.i8MAGTORQUE_VALUE_X = (int8_t)control_value_x;
        bdot_control_values.i8MAGTORQUE_VALUE_Y = (int8_t)control_value_y;
        bdot_control_values.i8MAGTORQUE_VALUE_Z = (int8_t)control_value_z;

        ES_TRACE_DEBUG("[es_adcs_controller] MTQ values to DataCache:   %d,    %d,    %d [%%]\r", bdot_control_values.i8MAGTORQUE_VALUE_X, bdot_control_values.i8MAGTORQUE_VALUE_Y, bdot_control_values.i8MAGTORQUE_VALUE_Z);

        /* Send calculated control values to data cache */
        dc_set_es_adcs_control_values_mtq_data(&bdot_control_values);
    }

    /* If the code reached this place and no errors have been reported, everything is ok */
    if (ES_ADCS_CONTROLLER_ERROR_GENERAL == algoStatus.lastErrorAlgo)
    {
        algoStatus.lastErrorAlgo = ES_ADCS_CONTROLLER_ERROR_NONE;
    }

    return algoStatus;
}

/* ******************************************************************************************* */
