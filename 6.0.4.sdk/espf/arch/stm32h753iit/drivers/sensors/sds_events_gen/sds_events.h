/*!
********************************************************************************************
* @file sds_events.h
* @brief Sensor Data Service events header
********************************************************************************************
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
********************************************************************************************
*/

#ifndef __SENSOR_DATA_SERVICE_EVENTS_H__
#define __SENSOR_DATA_SERVICE_EVENTS_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "es_cdef.h"
#include "sds_events_types.h"
#include "nvm/inc/nvm.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/
/** @brief The Sensor Data Service events generator timer
 *
 *  @param[in] sds_sens_read_freq_t *sds_events_cfg - frequency and event configuration
 *
 */
void sds_init_events_timer(const sds_sens_read_freq_t *sds_events_cfg);

/** @brief De-initialise the events generation timer */
void sds_deinit_events_timer(void);


#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SENSOR_DATA_SERVICE_EVENTS_H__
/* ******************************************************************************************* */
