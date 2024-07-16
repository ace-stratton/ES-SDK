/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ES_ADCS_CONTROLLERS_H
#define ES_ADCS_CONTROLLERS_H

/**
 * @addtogroup es_adcs
 * @{
 *
 * @file     es_adcs_controllers.h
 * @brief    EnduroSat ADCS controller submodule header file
 *
 * @}
*/

#include "es_adcs_types.h"

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @brief Controller warning enum */
typedef enum
{
    ES_ADCS_CONTROLLER_WARN_NONE,                /**< No controller warnings */
    ES_ADCS_CONTROLLER_WARN_SATURATION_UPPER,    /**< Controller has reached upper limit of allowed control values */
    ES_ADCS_CONTROLLER_WARN_SATURATION_LOWER,    /**< Controller has reached lower limit of allowed control values */
    ES_ADCS_CONTROLLER_WARN_GENERAL              /**< Controller general warning */
    // extend when needed
} es_adcs_controller_warning_t;

/** @brief Controller error enum */
typedef enum
{
    ES_ADCS_CONTROLLER_ERROR_NONE,              /**< No controller errors */
    ES_ADCS_CONTROLLER_ERROR_DATA_CACHE_GET,    /**< Controller has failed to retrieve data from the DataCache */
    ES_ADCS_CONTROLLER_ERROR_INVALID_ALGO,      /**< Controller has failed to identify a valid algorithm */
    ES_ADCS_CONTROLLER_ERROR_GENERAL            /**< Controller general error */
    // extend when needed
} es_adcs_controller_error_t;

/** @brief Controller algorithm specific status */
typedef struct
{
    es_adcs_controller_warning_t lastWarningAlgo;    /**< Controller algorithm warning */
    es_adcs_controller_error_t   lastErrorAlgo;      /**< Controller algorithm error */
    // extend when needed
} es_adcs_controller_algo_status_t;

/** @brief Controller status */
typedef struct
{
    es_adcs_controller_warning_t     lastWarningGeneral;    /**< General controller warning */
    es_adcs_controller_error_t       lastErrorGeneral;      /**< General controller error */
    es_adcs_controller_algo_status_t algoStatus;            /**< Status variable for the executed controller */
    // extend when needed
} es_adcs_controller_status_t;

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
/** @brief Control init function for ES ADCS that handles loading general config into local variables
 *  @return es_adcs_result_t - has this passed successfully or not */
extern es_adcs_result_t es_adcs_control_init(void);

/** @brief Control function for ES ADCS that handles which controller is executed
 *  @param[in] es_adcs_controller_config_t - config struct with desired type of controller and specific controller configs
 *  @return    es_adcs_result_t            - has this passed successfully or not */
extern es_adcs_result_t es_adcs_control(es_adcs_controller_config_t controlConfig);

/** @brief Returns the controller submodule current status
 *  @return es_adcs_controller_status_t - the current status of the controller submodule */
extern es_adcs_controller_status_t es_adcs_controller_get_status(void);

#endif /* ES_ADCS_CONTROLLERS_H */
/* ******************************************************************************************* */
