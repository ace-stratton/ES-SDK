/*!
********************************************************************************************
* @file FP_OBC_ES_COORDSYSProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface OBC_ES_COORDSYS v3.0
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __FP_OBC_ES_COORDSYSPROTOCOLTYPES_H__
#define __FP_OBC_ES_COORDSYSPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS ((uint16_t) (0x00000044))

#define OBC_ES_COORDSYS_SET_GYROSCOPE_FRAME_FUNC_ID ((funcIdType_t) 0x00000001)
#define OBC_ES_COORDSYS_GET_GYROSCOPE_FRAME_FUNC_ID ((funcIdType_t) 0x00000002)
#define OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAME_FUNC_ID ((funcIdType_t) 0x00000003)
#define OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAME_FUNC_ID ((funcIdType_t) 0x00000004)
#define OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAME_FUNC_ID ((funcIdType_t) 0x00000005)
#define OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAME_FUNC_ID ((funcIdType_t) 0x00000006)
#define OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAME_FUNC_ID ((funcIdType_t) 0x00000007)
#define OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAME_FUNC_ID ((funcIdType_t) 0x00000008)
#define OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIG_FUNC_ID ((funcIdType_t) 0x00000009)
#define OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIG_FUNC_ID ((funcIdType_t) 0x0000000A)
#define OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAME_FUNC_ID ((funcIdType_t) 0x0000000B)
#define OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAME_FUNC_ID ((funcIdType_t) 0x0000000C)
#define OBC_ES_COORDSYS_SET_GYROSCOPE_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define OBC_ES_COORDSYS_GET_GYROSCOPE_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAME_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAME_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAME_FUNCRESP_ID ((funcIdType_t) 0x0000000C)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define OBC_ES_COORDSYS_RESULT_OK ((uint8_t) 0)
#define OBC_ES_COORDSYS_RESULT_FAIL ((uint8_t) 1)
#define OBC_ES_COORDSYS_RESULT_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ES_COORDSYS_RESULT_t;

/*
    This corresponds to enum es_coordsys_satellite_axes_t
*/
#define OBC_ES_COORDSYS_SATELLITE_AXIS_X_POSITIVE ((uint8_t) 0)
#define OBC_ES_COORDSYS_SATELLITE_AXIS_Y_POSITIVE ((uint8_t) 1)
#define OBC_ES_COORDSYS_SATELLITE_AXIS_Z_POSITIVE ((uint8_t) 2)
#define OBC_ES_COORDSYS_SATELLITE_AXIS_X_NEGATIVE ((uint8_t) 3)
#define OBC_ES_COORDSYS_SATELLITE_AXIS_Y_NEGATIVE ((uint8_t) 4)
#define OBC_ES_COORDSYS_SATELLITE_AXIS_Z_NEGATIVE ((uint8_t) 5)
#define OBC_ES_COORDSYS_SATELLITE_AXIS_MAX_CNT  ((uint8_t) 6)
typedef uint8_t OBC_ES_COORDSYS_SATELLITE_AXIS_t;

typedef struct {
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eGyroscope1;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eGyroscope2;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eGyroscope3;
} PACKED_STRUCT OBC_ES_COORDSYS_GYROSCOPE_FRAME_t;

typedef struct {
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eMagnetometer_x;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eMagnetometer_y;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eMagnetometer_z;
} PACKED_STRUCT OBC_ES_COORDSYS_MAGNETOMETER_FRAME_t;

typedef struct {
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eMagnetorquer1;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eMagnetorquer2;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eMagnetorquer3;
} PACKED_STRUCT OBC_ES_COORDSYS_MAGNETORQUER_FRAME_t;

typedef struct {
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eCoarseSunSensor1;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eCoarseSunSensor2;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eCoarseSunSensor3;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eCoarseSunSensor4;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eCoarseSunSensor5;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eCoarseSunSensor6;
} PACKED_STRUCT OBC_ES_COORDSYS_COARSE_SUN_SENSOR_FRAME_t;

typedef struct {
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eAccelerometer_x;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eAccelerometer_y;
    OBC_ES_COORDSYS_SATELLITE_AXIS_t eAccelerometer_z;
} PACKED_STRUCT OBC_ES_COORDSYS_ACCELEROMETER_FRAME_t;

typedef struct {
    OBC_ES_COORDSYS_GYROSCOPE_FRAME_t sGyroscopeFrame;
    OBC_ES_COORDSYS_MAGNETOMETER_FRAME_t sMagnetometerFrame;
    OBC_ES_COORDSYS_MAGNETORQUER_FRAME_t sMagnetorquerFrame;
    OBC_ES_COORDSYS_COARSE_SUN_SENSOR_FRAME_t sCoarseSunSensorFrame;
    OBC_ES_COORDSYS_ACCELEROMETER_FRAME_t sAccelerometerFrame;
} PACKED_STRUCT OBC_ES_COORDSYS_FRAMES_t;


typedef struct {
    OBC_ES_COORDSYS_GYROSCOPE_FRAME_t sDesiredGyrFrame;
} PACKED_STRUCT OBC_ES_COORDSYSSET_GYROSCOPE_FRAMERequestData_t;

typedef struct {
    OBC_ES_COORDSYS_MAGNETOMETER_FRAME_t sDesiredMagFrame;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMERequestData_t;

typedef struct {
    OBC_ES_COORDSYS_MAGNETORQUER_FRAME_t sDesiredMtqFrame;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMERequestData_t;

typedef struct {
    OBC_ES_COORDSYS_COARSE_SUN_SENSOR_FRAME_t sDesiredCssFrame;
} PACKED_STRUCT OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMERequestData_t;

typedef struct {
    OBC_ES_COORDSYS_ACCELEROMETER_FRAME_t sDesiredAccFrame;
} PACKED_STRUCT OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMERequestData_t;


typedef struct {
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSSET_GYROSCOPE_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_GYROSCOPE_FRAME_t sActiveGyrFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSGET_GYROSCOPE_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_MAGNETOMETER_FRAME_t sActiveMagFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSGET_MAGNETOMETER_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_MAGNETORQUER_FRAME_t sActiveMtqFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSGET_MAGNETORQUER_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_COARSE_SUN_SENSOR_FRAME_t sActiveCssFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSGET_COARSE_SUN_SENSOR_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSSAVE_COORDSYS_CONFIGResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSLOAD_COORDSYS_CONFIGResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMEResponseData_t;

typedef struct {
    OBC_ES_COORDSYS_ACCELEROMETER_FRAME_t sActiveAccFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_COORDSYSGET_ACCELEROMETER_FRAMEResponseData_t;


#endif  // #ifndef __FP_OBC_ES_COORDSYSPROTOCOLTYPES_H__

