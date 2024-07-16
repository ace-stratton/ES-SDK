/*!
********************************************************************************************
* @file FP_SPProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface SP v0.4
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

#ifndef __FP_SPPROTOCOLTYPES_H__
#define __FP_SPPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_SP ((uint16_t) (0x00000012))

#define SP_GETSOFTWAREVERSION_FUNC_ID ((funcIdType_t) 0x00000000)
#define SP_STARTDEPLOYMENT_FUNC_ID ((funcIdType_t) 0x00000001)
#define SP_GETDEPLOYMENTSTATUS_FUNC_ID ((funcIdType_t) 0x00000002)
#define SP_GETUPTIME_FUNC_ID ((funcIdType_t) 0x00000003)
#define SP_GETTELEMETRY_FUNC_ID ((funcIdType_t) 0x00000004)
#define SP_GETMAINGYRODATA_FUNC_ID ((funcIdType_t) 0x00000005)
#define SP_GETEXTGYRODATA_FUNC_ID ((funcIdType_t) 0x00000006)
#define SP_WRITEMAINGYROREGISTER_FUNC_ID ((funcIdType_t) 0x00000007)
#define SP_WRITEEXTGYROREGISTER_FUNC_ID ((funcIdType_t) 0x00000008)
#define SP_GETMAINGYROREGISTER_FUNC_ID ((funcIdType_t) 0x00000009)
#define SP_GETEXTGYROREGISTER_FUNC_ID ((funcIdType_t) 0x0000000A)
#define SP_RESTARTFMW_FUNC_ID ((funcIdType_t) 0x0000000B)
#define SP_WRITEMTQPARAMETERS_FUNC_ID ((funcIdType_t) 0x0000000C)
#define SP_GETMTQPARAMETERS_FUNC_ID ((funcIdType_t) 0x0000000D)
#define SP_GETSOFTWAREVERSION_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define SP_STARTDEPLOYMENT_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define SP_GETDEPLOYMENTSTATUS_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define SP_GETUPTIME_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define SP_GETTELEMETRY_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define SP_GETMAINGYRODATA_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define SP_GETEXTGYRODATA_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define SP_WRITEMAINGYROREGISTER_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define SP_WRITEEXTGYROREGISTER_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define SP_GETMAINGYROREGISTER_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define SP_GETEXTGYROREGISTER_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define SP_RESTARTFMW_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define SP_WRITEMTQPARAMETERS_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define SP_GETMTQPARAMETERS_FUNCRESP_ID ((funcIdType_t) 0x0000000D)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Version variant,
    	  0xFF for development state
    	  0x00 for release candidate
*/
#define SP_VERSIONVARIANT_DevelopmentState ((uint8_t) 255)
#define SP_VERSIONVARIANT_ReleaseCandidate ((uint8_t) 0)
#define SP_VERSIONVARIANT_MAX_CNT  ((uint8_t) 256)
typedef uint8_t SP_VersionVariant_t;

/*
    List of all available deployment algorithms
*/
#define SP_DEPCMD_OFF ((uint8_t) 0)
#define SP_DEPCMD_ALG1 ((uint8_t) 1)
#define SP_DEPCMD_ALG2 ((uint8_t) 2)
#define SP_DEPCMD_ALG3 ((uint8_t) 3)
#define SP_DEPCMD_MAX_CNT  ((uint8_t) 4)
typedef uint8_t SP_DepCMD_t;

/*
    Structure that provides the data from all Sun sensors.
*/
typedef struct {
    uint16_t u16SunDataMain;
    uint16_t u16SunDataExt;
} PACKED_STRUCT SP_SunSensors_t;

/*
    Structure that provides the data from all Temperature sensors.
*/
typedef struct {
    int16_t i16TempDataMain;
    int16_t i16TempDataExt1;
    int16_t i16TempDataExt2;
    int16_t i16TempDataMCU;
} PACKED_STRUCT SP_TempSensors_t;

/*
    Structure that provides the data from Sun and Temperature data.
*/
typedef struct {
    SP_SunSensors_t sSunData;
    SP_TempSensors_t sTempData;
} PACKED_STRUCT SP_AllTelemetry_t;

/*
    Structure that provides the data from the main gyroscope.
*/
typedef struct {
    int16_t i16GyroDataMainRate;
    uint16_t u16GyroDataMainAngle;
    int16_t i16GyroDataMainTmp;
} PACKED_STRUCT SP_GyroMain_t;

/*
    Structure that provides the data from the external gyroscope.
*/
typedef struct {
    int16_t i16GyroDataExtRate;
    uint16_t u16GyroDataExtAngle;
    int16_t i16GyroDataExtTmp;
} PACKED_STRUCT SP_GyroExt_t;

/*
    List of all available Magnetorquer modes
*/
#define SP_MTQ_MODE_CW ((uint8_t) 0)
#define SP_MTQ_MODE_CCW ((uint8_t) 1)
#define SP_MTQ_MODE_OFF ((uint8_t) 2)
#define SP_MTQ_MODE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t SP_MTQ_Mode_t;

/*
    Return status list
*/
#define SP_RETURN_OUT_OF_RANGE ((uint8_t) 0)
#define SP_RETURN_OK ((uint8_t) 1)
#define SP_RETURN_MAX_CNT  ((uint8_t) 2)
typedef uint8_t SP_RETURN_t;


typedef struct {
    SP_DepCMD_t eDeployCommand;
} PACKED_STRUCT SPStartDeploymentRequestData_t;

typedef struct {
    uint8_t u8WriteMainGyroRegisterAddress;
    uint16_t u16WriteMainGyroRegisterValue;
} PACKED_STRUCT SPWriteMainGyroRegisterRequestData_t;

typedef struct {
    uint8_t u8WriteExtGyroRegisterAddress;
    uint16_t u16WriteExtGyroRegisterValue;
} PACKED_STRUCT SPWriteExtGyroRegisterRequestData_t;

typedef struct {
    uint8_t u8ReadMainGyroRegisterAdress;
} PACKED_STRUCT SPGetMainGyroRegisterRequestData_t;

typedef struct {
    uint8_t u8ReadExtGyroRegisterAddress;
} PACKED_STRUCT SPGetExtGyroRegisterRequestData_t;

typedef struct {
    SP_MTQ_Mode_t eMode;
    uint8_t u8WriteMTQDutyCycle;
} PACKED_STRUCT SPWriteMTQParametersRequestData_t;


typedef struct {
    SP_VersionVariant_t eVerVariant;
    int8_t ai8AppVersion[5];
    int8_t ai8Timestamp[14];
} PACKED_STRUCT SPGetSoftwareVersionResponseData_t;

typedef struct {
    uint8_t u8Status;
    uint8_t u8Heaters;
    uint8_t u8Timer;
    uint8_t u8Feedback;
} PACKED_STRUCT SPGetDeploymentStatusResponseData_t;

typedef struct {
    uint32_t u32Uptime;
} PACKED_STRUCT SPGetUptimeResponseData_t;

typedef struct {
    SP_AllTelemetry_t sData;
} PACKED_STRUCT SPGetTelemetryResponseData_t;

typedef struct {
    SP_GyroMain_t sData;
} PACKED_STRUCT SPGetMainGyroDataResponseData_t;

typedef struct {
    SP_GyroExt_t sData;
} PACKED_STRUCT SPGetExtGyroDataResponseData_t;

typedef struct {
    uint16_t u16ReturnMainGyroRegister;
} PACKED_STRUCT SPGetMainGyroRegisterResponseData_t;

typedef struct {
    uint16_t u16ReturnExtGyroRegister;
} PACKED_STRUCT SPGetExtGyroRegisterResponseData_t;

typedef struct {
    SP_RETURN_t eMTQ_Duty_cycle_valid_range;
} PACKED_STRUCT SPWriteMTQParametersResponseData_t;

typedef struct {
    SP_MTQ_Mode_t eMode;
    uint8_t u8GetMTQDutyCycle;
} PACKED_STRUCT SPGetMTQParametersResponseData_t;


#endif  // #ifndef __FP_SPPROTOCOLTYPES_H__

