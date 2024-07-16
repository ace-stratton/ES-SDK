/*!
********************************************************************************************
* @file sds_events_types.h
* @brief Sensor Data Service events types header
********************************************************************************************
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
********************************************************************************************
*/

#ifndef __SENSOR_DATA_SERVICE_EVENTS_TYPES_H__
#define __SENSOR_DATA_SERVICE_EVENTS_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "es_cdef.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/
/** @brief Maximum number of sensors */
#define SDS_SENSTYPE_MAX_CNT	(0x08)

/** @brief Flags to be set by events logic when the primary magnetometer period arrives */
#define SDS_THREAD_FLAGS_MTM_PRIM 	(0x01)
/** @brief Flags to be set by events logic when the secondary magnetometer period arrives */
#define SDS_THREAD_FLAGS_MTM_SEC 	(0x02)
/** @brief Flags to be set by events logic when the magnetometer read period arrives */
#define SDS_THREAD_FLAGS_MTM 		(SDS_THREAD_FLAGS_MTM_PRIM | SDS_THREAD_FLAGS_MTM_SEC)
/** @brief Flags to be set by events logic when the gyroscope read period arrives */
#define SDS_THREAD_FLAGS_GYRO 		(0x04)
/** @brief Flags to be set by events logic when the CSS read period arrives */
#define SDS_THREAD_FLAGS_CSS		(0x08)
/** @brief Flags to be set by events logic when the primary accelerometer read period arrives */
#define SDS_THREAD_FLAGS_ACC_PRIM	(0x10)
/** @brief Flags to be set by events logic when the secondary accelerometer read period arrives */
#define SDS_THREAD_FLAGS_ACC_SEC	(0x20)
/** @brief Flags to be set by events logic when the accelerometers read period arrives */
#define SDS_THREAD_FLAGS_ACC		(SDS_THREAD_FLAGS_ACC_PRIM | SDS_THREAD_FLAGS_ACC_SEC)
/** @brief Flags to be set by events logic when the temperature sensors read period arrives */
#define SDS_THREAD_FLAGS_TEMP		(0x40)
/** @brief Flags to be set by events logic when the gyroscope temperature read period arrives */
#define SDS_THREAD_FLAGS_GYRO_TEMP	(0x80)
/** @brief Flags to be set by events logic when the RESERVED sensors read period arrives */
#define SDS_THREAD_FLAGS_RES_1		(0x100)
/** @brief Flags to be set by events logic when the RESERVED sensors read period arrives */
#define SDS_THREAD_FLAGS_RES_2		(0x200)

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

typedef struct {
	uint16_t freq_cfg;
	uint16_t event_cfg;

} sds_events_cfg_t;

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

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SENSOR_DATA_SERVICE_EVENTS_TYPES_H__
/* ******************************************************************************************* */
