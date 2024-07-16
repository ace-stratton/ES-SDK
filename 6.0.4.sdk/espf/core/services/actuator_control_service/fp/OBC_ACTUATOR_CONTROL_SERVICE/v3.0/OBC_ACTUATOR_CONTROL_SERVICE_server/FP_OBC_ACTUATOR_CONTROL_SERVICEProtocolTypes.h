/*!
********************************************************************************************
* @file FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface OBC_ACTUATOR_CONTROL_SERVICE v3.0
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

#ifndef __FP_OBC_ACTUATOR_CONTROL_SERVICEPROTOCOLTYPES_H__
#define __FP_OBC_ACTUATOR_CONTROL_SERVICEPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE ((uint16_t) (0x00000046))

#define OBC_ACTUATOR_CONTROL_SERVICE_START_FUNC_ID ((funcIdType_t) 0x00000001)
#define OBC_ACTUATOR_CONTROL_SERVICE_STOP_FUNC_ID ((funcIdType_t) 0x00000002)
#define OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUS_FUNC_ID ((funcIdType_t) 0x00000003)
#define OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROL_FUNC_ID ((funcIdType_t) 0x00000004)
#define OBC_ACTUATOR_CONTROL_SERVICE_START_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define OBC_ACTUATOR_CONTROL_SERVICE_STOP_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROL_FUNCRESP_ID ((funcIdType_t) 0x00000004)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define OBC_ACTUATOR_CONTROL_SERVICE_RESULT_OK ((uint8_t) 0)
#define OBC_ACTUATOR_CONTROL_SERVICE_RESULT_FAIL ((uint8_t) 1)
#define OBC_ACTUATOR_CONTROL_SERVICE_RESULT_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t;

/*
    This corresponds to enum actuator_control_service_state_t
*/
#define OBC_ACTUATOR_CONTROL_SERVICE_STATE_ACTIVE ((uint8_t) 0)
#define OBC_ACTUATOR_CONTROL_SERVICE_STATE_INACTIVE ((uint8_t) 1)
#define OBC_ACTUATOR_CONTROL_SERVICE_STATE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ACTUATOR_CONTROL_SERVICE_STATE_t;

/*
    This corresponds to enum actuator_control_service_error_t
*/
#define OBC_ACTUATOR_CONTROL_SERVICE_ERROR_NONE ((uint8_t) 0)
#define OBC_ACTUATOR_CONTROL_SERVICE_ERROR_DATA_CACHE_GET ((uint8_t) 1)
#define OBC_ACTUATOR_CONTROL_SERVICE_ERROR_COORD_SYS_TRANSFORM ((uint8_t) 2)
#define OBC_ACTUATOR_CONTROL_SERVICE_ERROR_GENERAL ((uint8_t) 3)
#define OBC_ACTUATOR_CONTROL_SERVICE_ERROR_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_ACTUATOR_CONTROL_SERVICE_ERROR_t;

typedef struct {
    OBC_ACTUATOR_CONTROL_SERVICE_STATE_t eActiveState;
    OBC_ACTUATOR_CONTROL_SERVICE_ERROR_t eLastError;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICE_STATUS_t;

typedef struct {
    int8_t i8MTQ_X;
    int8_t i8MTQ_Y;
    int8_t i8MTQ_Z;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICE_LAST_MTQ_DATA_t;



typedef struct {
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICESTARTResponseData_t;

typedef struct {
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICESTOPResponseData_t;

typedef struct {
    OBC_ACTUATOR_CONTROL_SERVICE_STATUS_t sCurrentStatus;
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICEGET_STATUSResponseData_t;

typedef struct {
    OBC_ACTUATOR_CONTROL_SERVICE_LAST_MTQ_DATA_t sLastMagnetorquerValues;
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ACTUATOR_CONTROL_SERVICEGET_LAST_MTQ_CONTROLResponseData_t;


#endif  // #ifndef __FP_OBC_ACTUATOR_CONTROL_SERVICEPROTOCOLTYPES_H__

