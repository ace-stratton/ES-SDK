/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ES_ADCS_ESTIMATORS_H
#define ES_ADCS_ESTIMATORS_H

/**
 * @addtogroup es_adcs
 * @{
 *
 * @file     es_adcs_estimators.h
 * @brief    EnduroSat ADCS estimator submodule header file
 *
 * @}
*/

#include "es_adcs_types.h"

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @brief Estimator warning enum */
typedef enum
{
    ES_ADCS_ESTIMATOR_WARN_NONE,      /**< No estimator warnings */
    ES_ADCS_ESTIMATOR_WARN_GENERAL    /**< Estimator general warning */
    // extend when needed
} es_adcs_estimator_warning_t;

/** @brief Estimator error enum */
typedef enum
{
    ES_ADCS_ESTIMATOR_ERROR_NONE,                    /**< No estimator errors */
    ES_ADCS_ESTIMATOR_ERROR_DATA_CACHE_GET,          /**< Estimator has failed to retrieve data from the DataCache */
    ES_ADCS_ESTIMATOR_ERROR_MAGNETOMETER_INVALID,    /**< Estimator has failed to identify a valid magnetometer */
    ES_ADCS_ESTIMATOR_ERROR_INVALID_ALGO,            /**< Estimator has failed to identify a valid algorithm */
    ES_ADCS_ESTIMATOR_ERROR_ALGO_IDENTICAL,          /**< Estimator is asked to execute two identical algorithms */
    ES_ADCS_ESTIMATOR_ERROR_GENERAL                  /**< Estimator general error */
    // extend when needed
} es_adcs_estimator_error_t;

/** @brief Estimator algorithm specific status */
typedef struct
{
    es_adcs_estimator_warning_t lastWarningAlgo;    /**< Estimator algorithm warning */
    es_adcs_estimator_error_t   lastErrorAlgo;      /**< Estimator algorithm error */
    // extend when needed
} es_adcs_estimator_algo_status_t;

/** @brief Estimator status */
typedef struct
{
    es_adcs_estimator_warning_t     lastWarningGeneral;                           /**< General estimator warning */
    es_adcs_estimator_error_t       lastErrorGeneral;                             /**< General estimator error */
    es_adcs_estimator_algo_status_t algoStatus[ES_ADCS_ACTIVE_ESTIMATORS_MAX];    /**< Status variable for each executed estimator */
    // extend when needed
} es_adcs_estimator_status_t;

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
/** @brief Estimate init function for ES ADCS that handles loading general config into local variables
 *  @return es_adcs_result_t - has this passed successfully or not */
extern es_adcs_result_t es_adcs_estimate_init(void);

/** @brief Estimate function for ES ADCS that handles which estimator is executed
 *  @param[in] es_adcs_estimator_config_t  - config struct with number of estimators and types of estimators and other parameters
 *  @param[in] es_adcs_used_magnetometer_t - the used magnetometer by the ADCS
 *  @return    es_adcs_result_t            - has this passed successfully or not */
extern es_adcs_result_t es_adcs_estimate(es_adcs_estimator_config_t estimConfig, es_adcs_used_magnetometer_t activeMagnetometer);

/** @brief Returns the estimator submodule current status
 *  @return es_adcs_estimator_status_t - the current status of the estimator submodule */
extern es_adcs_estimator_status_t es_adcs_estimator_get_status(void);

#endif /* ES_ADCS_ESTIMATORS_H */
/* ******************************************************************************************* */
