/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ACTUATOR_CONTROL_SERVICE
#define ACTUATOR_CONTROL_SERVICE

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup actuator_cntrl_service Actuator Control Service
 * @{
 * Service that applies calculated control values to the physical hardware
 *
 * @file     actuator_control_service.h
 * @brief    Actuator Control Service header file
 *
 * @}
 * @}
 *
*/

#include <stdint.h>

/** @brief The sampling time of the actuator control service */
#define ACTUATOR_CONTROL_SERVICE_SAMPLING_TIME_MS    20

/** @brief Total amount of magnetorquers */
#define MAGNETORQUER_QUANTITY    3

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @brief Actuator control service states */
typedef enum
{
    ACTUATOR_CONTROL_SERVICE_STATE_ACTIVE,     /**< All actuators are updated with values from datacache based on @ref ACTUATOR_CONTROL_SERVICE_SAMPLING_TIME_MS */
    ACTUATOR_CONTROL_SERVICE_STATE_INACTIVE    /**< All actuators are deinitialized and not updated */
    // extend when needed
} actuator_control_service_state_t;

/** @brief Actuator control service error codes */
typedef enum
{
    ACTUATOR_CONTROL_SERVICE_ERROR_NONE,                   /**< No errors have occured during normal execution */
    ACTUATOR_CONTROL_SERVICE_ERROR_DATA_CACHE_GET,         /**< An error occured while reading data from the data cache */
    ACTUATOR_CONTROL_SERVICE_ERROR_COORD_SYS_TRANSFORM,    /**< An error occured while data was being transformed between coordinate frames  */
    ACTUATOR_CONTROL_SERVICE_ERROR_GENERAL                 /**< Actuator control service did not fully finish executing */
    // extend when needed
} actuator_control_service_error_t;

/** @brief Actuator control service status struct */
typedef struct
{
    actuator_control_service_state_t state;        /**< State of the actuator control service */
    actuator_control_service_error_t lastError;    /**< Last caught error that occured in the service */
    // extend when needed
} actuator_control_service_status_t;

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
/** @brief Initialization routine for the ES actuator control service component. */
extern void actuator_control_service_init(void);

/** @brief Starts the ES actuator control service. */
extern void actuator_control_service_start(void);

/** @brief Stops the ES actuator control service. */
extern void actuator_control_service_stop(void);

/** @brief Retrieve the actuator control service status
 *  @return actuator_control_service_status_t - current status of the actuator control service */
extern actuator_control_service_status_t actuator_control_service_get_status(void);

/** @brief Retrieve the last executed control values to the magnetorquers
 *  @param[out] lastMtqControlValues pointer to array with the last magnetorquer values sent to the physical hardware */
extern void actuator_control_service_get_last_mtq_control(int8_t *lastMtqControlValues);

#endif /* ACTUATOR_CONTROL_SERVICE */
/* ******************************************************************************************* */
