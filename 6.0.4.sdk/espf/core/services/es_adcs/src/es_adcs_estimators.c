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
 * @file     es_adcs_estimators.c
 * @brief    EnduroSat ADCS estimator submodule source file
 *
 * @}
*/

#include "datacache.h"
#include "es_exeh.h"
#include "trace.h"
#include "nvm.h"
#include "es_adcs_math.h"
#include "es_adcs_estimators.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID  (eEXEHModuleID_ES_ADCS)

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/

/** @brief Estimator detailed status variable */
static es_adcs_estimator_status_t estimatorStatus;

/** @brief Data cache structs */
static DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t   mag_measurements_primary;
static DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t mag_measurements_secondary;
static DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t       bdot_estimates;

/** @brief Data cache error variable */
static dc_data_status_t data_cache_error_estimator;

/**********************************************************************
 *
 * Static function declarations
 *
 **********************************************************************/
static es_adcs_result_t                fs_es_adcs_estimator_detumbling_bdot_init(void);
static es_adcs_estimator_algo_status_t fs_es_adcs_estimator_detumbling_bdot(es_adcs_used_magnetometer_t usedMagnetometer);

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
es_adcs_result_t es_adcs_estimate_init(void)
{
    /* Execution result variable */
    es_adcs_result_t result = ES_ADCS_RESULT_FAIL;

    /* No general estimator inits so far, but could be present when more estimators are added */

    /* Init the first estimator - detumbling bdot */
    result = fs_es_adcs_estimator_detumbling_bdot_init();

    /* Send result back to caller */
    return result;
}

es_adcs_result_t es_adcs_estimate(es_adcs_estimator_config_t estimConfig, es_adcs_used_magnetometer_t activeMagnetometer)
{
    /* 0. catch if both estimators are the same? also, if both are NONE, then we can proceed
     * 1. extract number of algorithms to run from estimator config
     * 2. extract which algorithms to run from estimator config
     * 3. run algorithms
     * 4. report if there are errors in the return type
     */

    /* Execution result variable */
    es_adcs_result_t result = ES_ADCS_RESULT_FAIL;

    /* Set up the initial conditions for this loop */
    estimatorStatus.lastWarningGeneral = ES_ADCS_ESTIMATOR_WARN_NONE;
    estimatorStatus.lastErrorGeneral   = ES_ADCS_ESTIMATOR_ERROR_GENERAL;

    /* If the desired estimators are not NONE and they are both the same */
    if ( (ES_ADCS_ESTIMATOR_ALGO_NONE      != estimConfig.eActiveEstimators[0]) &&
         (estimConfig.eActiveEstimators[0] == estimConfig.eActiveEstimators[1])   )
    {
            /* Two identical estimator algorithms selected - raise an error */
            estimatorStatus.lastErrorGeneral = ES_ADCS_ESTIMATOR_ERROR_ALGO_IDENTICAL;

            /* Report through es_exeh */
            EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_ESTIMATOR_ALGO_IDENTICAL);
    }
    else
    {
        /* Execute all active estimators */
        for (uint8_t i = 0; i < ES_ADCS_ACTIVE_ESTIMATORS_MAX; i++)
        {
            switch( estimConfig.eActiveEstimators[i] )
            {
                case ES_ADCS_ESTIMATOR_ALGO_NONE:
                {
                    /* No estimation performed */
                    break;
                }

                case ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG:
                {
                    /* Perform Bdot estimation */
                    estimatorStatus.algoStatus[i] = fs_es_adcs_estimator_detumbling_bdot(activeMagnetometer);
                    break;
                }

                default:
                {
                    /* Invalid estimator algorithm chosen - raise an error */
                    estimatorStatus.lastErrorGeneral = ES_ADCS_ESTIMATOR_ERROR_INVALID_ALGO;

                    /* Report through es_exeh */
                    EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_ESTIMATOR_INVALID_TYPE);
                    break;
                }
            }
        }
    }

    /* If both estimators are active */
    if ( (ES_ADCS_ESTIMATOR_ALGO_NONE != estimConfig.eActiveEstimators[0]) &&
         (ES_ADCS_ESTIMATOR_ALGO_NONE != estimConfig.eActiveEstimators[1])   )
    {
        /* Check that all estimator algorithms have completed successfully */
        /* If the code reached this place and no errors have been reported, everything is ok */
        if ( (ES_ADCS_ESTIMATOR_ERROR_GENERAL == estimatorStatus.lastErrorGeneral)            &&
             (ES_ADCS_ESTIMATOR_ERROR_NONE    == estimatorStatus.algoStatus[0].lastErrorAlgo) &&
             (ES_ADCS_ESTIMATOR_ERROR_NONE    == estimatorStatus.algoStatus[1].lastErrorAlgo)   )
        {
            estimatorStatus.lastErrorGeneral = ES_ADCS_ESTIMATOR_ERROR_NONE;
            result = ES_ADCS_RESULT_OK;
        }
    }
    /* If only the first estimator is activated */
    else if ( (ES_ADCS_ESTIMATOR_ALGO_NONE != estimConfig.eActiveEstimators[0]) &&
              (ES_ADCS_ESTIMATOR_ALGO_NONE == estimConfig.eActiveEstimators[1])   )
    {
        /* Check that only the first estimator algorithm has completed successfully */
        /* If the code reached this place and no errors have been reported, everything is ok */
        if ( (ES_ADCS_ESTIMATOR_ERROR_GENERAL == estimatorStatus.lastErrorGeneral)            &&
             (ES_ADCS_ESTIMATOR_ERROR_NONE    == estimatorStatus.algoStatus[0].lastErrorAlgo)   )
        {
            estimatorStatus.lastErrorGeneral = ES_ADCS_ESTIMATOR_ERROR_NONE;
            result = ES_ADCS_RESULT_OK;
        }
    }
    /* If only the second estimator is activated */
    else if ( (ES_ADCS_ESTIMATOR_ALGO_NONE == estimConfig.eActiveEstimators[0]) &&
              (ES_ADCS_ESTIMATOR_ALGO_NONE != estimConfig.eActiveEstimators[1])   )
    {
        /* Check that only the second estimator algorithm has completed successfully */
        /* If the code reached this place and no errors have been reported, everything is ok */
        if ( (ES_ADCS_ESTIMATOR_ERROR_GENERAL == estimatorStatus.lastErrorGeneral)            &&
             (ES_ADCS_ESTIMATOR_ERROR_NONE    == estimatorStatus.algoStatus[1].lastErrorAlgo)   )
        {
            estimatorStatus.lastErrorGeneral = ES_ADCS_ESTIMATOR_ERROR_NONE;
            result = ES_ADCS_RESULT_OK;
        }
    }
    /* If no estimator algorithms are active */
    else
    {
        /* If the code reached this place and no errors have been reported, everything is ok */
        if (ES_ADCS_ESTIMATOR_ERROR_GENERAL == estimatorStatus.lastErrorGeneral)
        {
            estimatorStatus.lastErrorGeneral = ES_ADCS_ESTIMATOR_ERROR_NONE;
            result = ES_ADCS_RESULT_OK;
        }
    }

    return result;
}

es_adcs_estimator_status_t es_adcs_estimator_get_status(void)
{
    return estimatorStatus;
}

/**********************************************************************
 *
 * Static function definitions
 *
 **********************************************************************/
/** @brief Detumbling B-dot estimator init function
 *  @return es_adcs_result_t - has this passed successfully or not */
static es_adcs_result_t fs_es_adcs_estimator_detumbling_bdot_init(void)
{
    /* Execution result variable */
    es_adcs_result_t result = ES_ADCS_RESULT_FAIL;

    /* The first estimator - detumbling bdot - has no parameters to be initialized at this moment,
     * but it could be extended with further development
     */

    result = ES_ADCS_RESULT_OK;
    return result;
}

/** @brief Detumbling B-dot estimator
 *  @param[in] es_adcs_estimator_magnetometer_used_t usedMagnetometer - which magnetometer to use data from
 *  @return    es_adcs_estimator_algo_status_t                        - contains warnings and errors generated during algorithm execution */
static es_adcs_estimator_algo_status_t fs_es_adcs_estimator_detumbling_bdot(es_adcs_used_magnetometer_t usedMagnetometer)
{
    /* 0. magnetorquer stop time shall be handled outside the estimator (in the task, preferably)
     * outline:
     * 1. retrieve sensor data from DataCache (config flag determines primary or secondary)
     * 2. calculate derivative of magnetic field in each axis
     * 3. return calculated data to DataCache
     */

    es_adcs_estimator_algo_status_t algoStatus;
    algoStatus.lastWarningAlgo = ES_ADCS_ESTIMATOR_WARN_NONE;
    algoStatus.lastErrorAlgo   = ES_ADCS_ESTIMATOR_ERROR_GENERAL;

    REAL x_current;
    REAL x_previous;
    REAL y_current;
    REAL y_previous;
    REAL z_current;
    REAL z_previous;
    REAL vectorMagnitude;

    /* Dodge MISRA-C:2004 10.4 */
    REAL temp_deriv_x_uT;
    REAL temp_deriv_y_uT;
    REAL temp_deriv_z_uT;

    /* Read sensor data service configuration from nvm */
    sds_sens_read_freq_t sds_chan_freq_cfgs;
    Nvm_GetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sds_chan_freq_cfgs);

    /* Extract magnetometer sampling rate in Hz */
    uint16_t sampling_rate_mag = sds_chan_freq_cfgs.sens_cfg[0].freq_cfg;

    /* Transform Hz to seconds */
    REAL sampling_time = 1 / (REAL)sampling_rate_mag;

    /* Local vectors to enable use of vector math */
    es_adcs_vec_3d_t magMeasureCurrent;
    es_adcs_vec_3d_t magMeasurePrevious;
    es_adcs_vec_3d_t magMeasureAverage;
    es_adcs_vec_3d_t magMeasureDerivative;

    /* Check if primary magnetometer is being used */
    if (ES_ADCS_USED_MAGNETOMETER_PRIMARY == usedMagnetometer)
    {
        /* Retrieve latest measurements from primary magnetometer */
        data_cache_error_estimator = dc_get_es_adcs_sensor_mag_primary_data(&mag_measurements_primary);

        /* Catch any DataCache read failure */
        if (DC_DATA_STATUS_OK != data_cache_error_estimator)
        {
            /* DataCache readout failed - raise an error */
            algoStatus.lastErrorAlgo = ES_ADCS_ESTIMATOR_ERROR_DATA_CACHE_GET;

            /* Report through es_exeh */
            EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_ESTIMATOR_BDOT_DC_READ_FAIL);
            return algoStatus;
        }

        /* Measurements come in microT, convert to T */
        x_current  = (REAL)mag_measurements_primary.i32MAG_X_CURRENT  * ES_ADCS_uT_TO_T;
        x_previous = (REAL)mag_measurements_primary.i32MAG_X_PREVIOUS * ES_ADCS_uT_TO_T;

        y_current  = (REAL)mag_measurements_primary.i32MAG_Y_CURRENT  * ES_ADCS_uT_TO_T;
        y_previous = (REAL)mag_measurements_primary.i32MAG_Y_PREVIOUS * ES_ADCS_uT_TO_T;

        z_current  = (REAL)mag_measurements_primary.i32MAG_Z_CURRENT  * ES_ADCS_uT_TO_T;
        z_previous = (REAL)mag_measurements_primary.i32MAG_Z_PREVIOUS * ES_ADCS_uT_TO_T;
    }
    /* Check if secondary magnetometer is being used */
    else if (ES_ADCS_USED_MAGNETOMETER_SECONDARY == usedMagnetometer)
    {
        /* Retrieve latest measurements from secondary magnetometer */
        data_cache_error_estimator = dc_get_es_adcs_sensor_mag_secondary_data(&mag_measurements_secondary);

        /* Catch any DataCache read failure */
        if (DC_DATA_STATUS_OK != data_cache_error_estimator)
        {
            /* DataCache readout failed - raise an error */
            algoStatus.lastErrorAlgo = ES_ADCS_ESTIMATOR_ERROR_DATA_CACHE_GET;

            /* Report through es_exeh */
            EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_ESTIMATOR_BDOT_DC_READ_FAIL);
            return algoStatus;
        }

        /* Measurements come in microT, convert to T */
        x_current  = (REAL)mag_measurements_secondary.i32MAG_X_CURRENT  * ES_ADCS_uT_TO_T;
        x_previous = (REAL)mag_measurements_secondary.i32MAG_X_PREVIOUS * ES_ADCS_uT_TO_T;

        y_current  = (REAL)mag_measurements_secondary.i32MAG_Y_CURRENT  * ES_ADCS_uT_TO_T;
        y_previous = (REAL)mag_measurements_secondary.i32MAG_Y_PREVIOUS * ES_ADCS_uT_TO_T;

        z_current  = (REAL)mag_measurements_secondary.i32MAG_Z_CURRENT  * ES_ADCS_uT_TO_T;
        z_previous = (REAL)mag_measurements_secondary.i32MAG_Z_PREVIOUS * ES_ADCS_uT_TO_T;
    }
    else
    {
        /* Magnetometer config is flawed - raise an error */
        algoStatus.lastErrorAlgo = ES_ADCS_ESTIMATOR_ERROR_MAGNETOMETER_INVALID;

        /* Report through es_exeh */
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_ES_ADCS_ESTIMATOR_INVALID_MAG_CONFIG);
        return algoStatus;
    }

    ES_TRACE_DEBUG("\r");
    ES_TRACE_DEBUG("[es_adcs_estimator] mag measurement current : %f, %f, %f [Tesla]\r", x_current, y_current, z_current);
    ES_TRACE_DEBUG("[es_adcs_estimator] mag measurement previous: %f, %f, %f [Tesla]\r", x_previous, y_previous, z_previous);

    /* Set measurements as vector components */
    magMeasureCurrent  = es_adcs_math_VecSet(x_current , y_current , z_current);
    magMeasurePrevious = es_adcs_math_VecSet(x_previous, y_previous, z_previous);

    /* Find the average of the magnetic field vector */
    /* Scaling by 0.5 is equivalent to dividing by 2 */
    magMeasureAverage = es_adcs_math_VecScale( es_adcs_math_VecAdd(magMeasureCurrent, magMeasurePrevious), 0.5f);

    /* Find the magnitude of the average magnetic field vector */
    vectorMagnitude = es_adcs_math_VecNorm(magMeasureAverage);

    /* Find the derivative of the magnetic field vector */
    magMeasureDerivative = es_adcs_math_VecScale(
                                                 es_adcs_math_VecSub(magMeasureCurrent, magMeasurePrevious),
                                                 es_adcs_math_InverseOf(vectorMagnitude * sampling_time)
                                                 );
    ES_TRACE_DEBUG("[es_adcs_estimator] mag deriv: %.10f, %.10f, %.10f [rad/s]\r", magMeasureDerivative.X, magMeasureDerivative.Y, magMeasureDerivative.Z);

    /* The result is in rad/s */
    /* Convert to desired microrad/s unit */
    temp_deriv_x_uT = magMeasureDerivative.X * ES_ADCS_RADS_TO_uRADS;
    temp_deriv_y_uT = magMeasureDerivative.Y * ES_ADCS_RADS_TO_uRADS;
    temp_deriv_z_uT = magMeasureDerivative.Z * ES_ADCS_RADS_TO_uRADS;

    bdot_estimates.i32MAG_FIELD_DERIV_X = (int32_t)temp_deriv_x_uT;
    bdot_estimates.i32MAG_FIELD_DERIV_Y = (int32_t)temp_deriv_y_uT;
    bdot_estimates.i32MAG_FIELD_DERIV_Z = (int32_t)temp_deriv_z_uT;

    ES_TRACE_DEBUG("[es_adcs_estimator] mag deriv to DataCache: %d, %d, %d [microrad/s]\r", bdot_estimates.i32MAG_FIELD_DERIV_X, bdot_estimates.i32MAG_FIELD_DERIV_Y, bdot_estimates.i32MAG_FIELD_DERIV_Z);

    /* Send estimates to data cache */
    dc_set_es_adcs_estimates_bdot_data(&bdot_estimates);


    /* If the code reached this place and no errors have been reported, everything is ok */
    if (ES_ADCS_ESTIMATOR_ERROR_GENERAL == algoStatus.lastErrorAlgo)
    {
        algoStatus.lastErrorAlgo = ES_ADCS_ESTIMATOR_ERROR_NONE;
    }

    return algoStatus;
}

/* ******************************************************************************************* */
