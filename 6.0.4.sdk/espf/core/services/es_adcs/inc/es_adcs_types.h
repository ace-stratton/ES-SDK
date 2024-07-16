/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ES_ADCS_TYPES_H
#define ES_ADCS_TYPES_H

/**
 * @addtogroup es_adcs
 * @{
 *
 * @file     es_adcs_types.h
 * @brief    EnduroSat ADCS types file
 *
 * @}
*/

#include "es_adcs_math.h"

/** @brief The full sampling time of the ADCS system */
#define ES_ADCS_SAMPLING_TIME_MS             (1000 - ES_ADCS_MAGNETORQUER_WAIT_TIME_MS)

/** @brief The time to wait for magnetorquers' turn off before starting estimation and control */
#define ES_ADCS_MAGNETORQUER_WAIT_TIME_MS      250

/** @brief Convert microtesla to tesla */
#define ES_ADCS_uT_TO_T                       1e-6

/** @brief Convert radians to microradians */
#define ES_ADCS_RADS_TO_uRADS                  1e6

/** @brief Maximum amount of concurrent estimators */
#define ES_ADCS_ACTIVE_ESTIMATORS_MAX            2

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @brief General ADCS result enum */
typedef enum
{
    ES_ADCS_RESULT_OK,           /**< Operation was successful */
//    ES_ADCS_RESULT_OK_WARNING, /* This can be used to signal that execution has completed, but warnings were present */
    ES_ADCS_RESULT_INIT_FAIL,    /**< ADCS initialization failed */
    ES_ADCS_RESULT_FAIL          /**< Operation has failed */
    // extend when needed
} es_adcs_result_t;

/** @brief ADCS Estimators enum */
typedef enum
{
    ES_ADCS_ESTIMATOR_ALGO_NONE,        /**< No estimator algorithm executed */
    ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG,    /**< Estimator B-dot executed */
//    ES_ADCS_ESTIMATOR_ALGO_BDOT_GYRO,  /* to be implemented */
//    ES_ADCS_ESTIMATOR_ALGO_TRIAD,      /* to be implemented */
//    ES_ADCS_ESTIMATOR_ALGO_RKF_MAG,    /* to be implemented */
//    ES_ADCS_ESTIMATOR_ALGO_EKF,        /* to be implemented */
    ES_ADCS_ESTIMATOR_ALGO_COUNT
    // extend when needed
} es_adcs_estimator_t;

/** @brief ADCS Controllers enum */
typedef enum
{
    ES_ADCS_CONTROLLER_ALGO_NONE,        /**< No controller algorithm executed */
    ES_ADCS_CONTROLLER_ALGO_BDOT_MAG,    /**< Controller B-dot executed */
//    ES_ADCS_CONTROLLER_ALGO_BDOT_GYRO, /* to be implemented */
//    ES_ADCS_CONTROLLER_ALGO_P,         /* to be implemented */
//    ES_ADCS_CONTROLLER_ALGO_PD,        /* to be implemented */
    ES_ADCS_CONTROLLER_ALGO_COUNT
    // extend when needed
} es_adcs_controller_t;

/** @brief ADCS Magnetometers enum */
typedef enum
{
    ES_ADCS_USED_MAGNETOMETER_PRIMARY,
    ES_ADCS_USED_MAGNETOMETER_SECONDARY,
    ES_ADCS_USED_MAGNETOMETER_COUNT
    // extend when needed
} es_adcs_used_magnetometer_t;

/** @brief ADCS B-Dot controller configuration */
typedef struct
{
	REAL bdot_coefficient_X;    /**< B-dot coefficient for X axis */
	REAL bdot_coefficient_Y;    /**< B-dot coefficient for Y axis */
	REAL bdot_coefficient_Z;    /**< B-dot coefficient for Z axis */
    // extend when needed
} es_adcs_controller_bdot_config_t;

/** @brief ADCS General estimator configuration */
typedef struct
{
    es_adcs_estimator_t eActiveEstimators[ES_ADCS_ACTIVE_ESTIMATORS_MAX];    /**< Array with executed estimators */
    // extend when needed
} es_adcs_estimator_config_t;

/** @brief ADCS General controller configuration */
typedef struct
{
    es_adcs_controller_t eActiveController;          /**< Executed controller */
    es_adcs_controller_bdot_config_t sBdotConfig;    /**< B-dot specific configuration */
    // extend when needed
} es_adcs_controller_config_t;

/** @brief ADCS General configuration */
typedef struct
{
    es_adcs_estimator_config_t sEstimatorConfig;      /**< Estimator configuration */
    es_adcs_controller_config_t sControllerConfig;    /**< Controller configuration */
    es_adcs_used_magnetometer_t eUsedMagnetometer; /**< The used magnetometer for estimation */
    // extend when needed
    uint32_t u32Crc;
} es_adcs_config_t;

#endif /* ES_ADCS_TYPES_H */
/* ******************************************************************************************* */
