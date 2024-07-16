/*!
********************************************************************************************
* @file FP_SDSProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface SDS v0.3
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

#ifndef __FP_SDSPROTOCOLTYPES_H__
#define __FP_SDSPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_SDS ((uint16_t) (0x0000001A))

#define SDS_SETSENSREADFREQ_FUNC_ID ((funcIdType_t) 0x00000001)
#define SDS_GETSENSREADFREQ_FUNC_ID ((funcIdType_t) 0x00000002)
#define SDS_GETSENSSTATE_FUNC_ID ((funcIdType_t) 0x00000003)
#define SDS_GETSENSERR_FUNC_ID ((funcIdType_t) 0x00000004)
#define SDS_GETSENSREG_FUNC_ID ((funcIdType_t) 0x00000005)
#define SDS_SETSENSREG_FUNC_ID ((funcIdType_t) 0x00000006)
#define SDS_SETSENSREADFREQ_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define SDS_GETSENSREADFREQ_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define SDS_GETSENSSTATE_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define SDS_GETSENSERR_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define SDS_GETSENSREG_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define SDS_SETSENSREG_FUNCRESP_ID ((funcIdType_t) 0x00000006)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    General status type used for SW-related communication and/or settings.
*/
#define SDS_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define SDS_STANDARDRESULT_ERROR ((uint8_t) 1)
#define SDS_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define SDS_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define SDS_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t SDS_StandardResult_t;

/*
    Enumeration for SAFE booleans
*/
#define SDS_SAFEBOOL_FALSE ((uint8_t) 0)
#define SDS_SAFEBOOL_TRUE ((uint8_t) 255)
#define SDS_SAFEBOOL_MAX_CNT  ((uint8_t) 256)
typedef uint8_t SDS_SafeBool_t;

/*
    Enumeration describing the different states of a sensor type group
*/
#define SDS_SENSORSTATE_DEINIT ((uint8_t) 0)
#define SDS_SENSORSTATE_INIT ((uint8_t) 1)
#define SDS_SENSORSTATE_ERR ((uint8_t) 2)
#define SDS_SENSORSTATE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t SDS_SensorState_t;

/*
    Sensor types. Data from up to 8 sensor types can be configured to be read by the SDS
*/
#define SDS_SENSTYPECFGNUM_SENS_MTM ((uint8_t) 0)
#define SDS_SENSTYPECFGNUM_SENS_GYRO ((uint8_t) 1)
#define SDS_SENSTYPECFGNUM_SENS_CSS ((uint8_t) 2)
#define SDS_SENSTYPECFGNUM_SENS_ACC ((uint8_t) 3)
#define SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP ((uint8_t) 4)
#define SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP ((uint8_t) 5)
#define SDS_SENSTYPECFGNUM_SENS_RES_0 ((uint8_t) 6)
#define SDS_SENSTYPECFGNUM_SENS_RES_1 ((uint8_t) 7)
#define SDS_SENSTYPECFGNUM_MAX_CNT  ((uint8_t) 8)
typedef uint8_t SDS_SensTypeCfgNum_t;

/*
    Sensor axis
*/
#define SDS_SENSAXIS_X_AXIS ((uint8_t) 0)
#define SDS_SENSAXIS_Y_AXIS ((uint8_t) 1)
#define SDS_SENSAXIS_Z_AXIS ((uint8_t) 2)
#define SDS_SENSAXIS_MAX_CNT  ((uint8_t) 3)
typedef uint8_t SDS_SensAxis_t;

/*
    Sensor number
*/
#define SDS_SENSNUM_PRIMARY ((uint8_t) 0)
#define SDS_SENSNUM_SECONDARY ((uint8_t) 1)
#define SDS_SENSNUM_MAX_CNT  ((uint8_t) 2)
typedef uint8_t SDS_SensNum_t;


typedef struct {
    SDS_SafeBool_t eEnable;
    uint16_t u16SensMTM;
    uint16_t u16SensGyro;
    uint16_t u16SensCSS;
    uint16_t u16SensACC;
    uint16_t u16SensPANEL_TEMP;
    uint16_t u16SensGYRO_TEMP;
    uint16_t u16SensRES_0;
    uint16_t u16SensRES_1;
} PACKED_STRUCT SDSsetSensReadFreqRequestData_t;

typedef struct {
    SDS_SensTypeCfgNum_t eSensTypeId;
} PACKED_STRUCT SDSgetSensStateRequestData_t;

typedef struct {
    SDS_SensTypeCfgNum_t eSensTypeId;
} PACKED_STRUCT SDSgetSensErrRequestData_t;

typedef struct {
    SDS_SensTypeCfgNum_t eSensTypeId;
    SDS_SensAxis_t eSensAxis;
    SDS_SensNum_t eSensNum;
    uint32_t u32Reg_address;
} PACKED_STRUCT SDSgetSensRegRequestData_t;

typedef struct {
    SDS_SensTypeCfgNum_t eSensTypeId;
    SDS_SensAxis_t eSensAxis;
    SDS_SensNum_t eSensNum;
    uint32_t u32Reg_address;
    uint32_t u32Reg_value;
} PACKED_STRUCT SDSsetSensRegRequestData_t;


typedef struct {
    SDS_StandardResult_t eOpResult;
} PACKED_STRUCT SDSsetSensReadFreqResponseData_t;

typedef struct {
    SDS_SafeBool_t eEnable;
    uint16_t u16SensMTM;
    uint16_t u16SensGyro;
    uint16_t u16SensCSS;
    uint16_t u16SensACC;
    uint16_t u16SensPANEL_TEMP;
    uint16_t u16SensGYRO_TEMP;
    uint16_t u16SensRES_0;
    uint16_t u16SensRES_1;
    SDS_StandardResult_t eOpResult;
} PACKED_STRUCT SDSgetSensReadFreqResponseData_t;

typedef struct {
    SDS_SensorState_t eSensState;
    SDS_StandardResult_t eOpResult;
} PACKED_STRUCT SDSgetSensStateResponseData_t;

typedef struct {
    uint8_t u8SensErr;
    uint8_t u8X_AXIS;
    uint8_t u8Y_AXIS;
    uint8_t u8Z_AXIS;
    SDS_StandardResult_t eOpResult;
} PACKED_STRUCT SDSgetSensErrResponseData_t;

typedef struct {
    uint32_t u32RespBytes;
    SDS_StandardResult_t eOpResult;
} PACKED_STRUCT SDSgetSensRegResponseData_t;

typedef struct {
    SDS_StandardResult_t eOpResult;
} PACKED_STRUCT SDSsetSensRegResponseData_t;


#endif  // #ifndef __FP_SDSPROTOCOLTYPES_H__

