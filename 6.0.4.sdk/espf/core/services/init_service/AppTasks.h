/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef APPTASKS_H
#define APPTASKS_H

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "main.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/
#define SERVICE_TASK_PERIOD (1000) /**< Period for the services tasks */

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/

/**
 * @brief Initialization of the services task
 *
 */
void ServicesTask_Init(void);

/**
 * @brief Initialization of the application task
 *
 */
void AppTask_Init(void);

/**
 * @brief Getter for the time in seconds in which the system has been active since last reset
 *
 * @return Time in seconds since last reset
 */
uint32_t get_uptime_seconds(void);

/**
 * @brief Getter for the time in seconds in which the services task has been active
 *
 * @return Time in seconds during which the services task has been active
 */
uint32_t ServicesTask_UptimeSeconds(void);

#endif /* APPTASKS_H */
/********************************************************************************************* */
