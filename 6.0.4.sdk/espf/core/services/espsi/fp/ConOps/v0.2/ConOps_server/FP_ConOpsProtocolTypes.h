/*!
********************************************************************************************
* @file FP_ConOpsProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface ConOps v0.2
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

#ifndef __FP_CONOPSPROTOCOLTYPES_H__
#define __FP_CONOPSPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_CONOPS ((uint16_t) (0x00000010))

#define CONOPS_SENDNEWEVENT_FUNC_ID ((funcIdType_t) 0x00000001)
#define CONOPS_GETOPMODE_FUNC_ID ((funcIdType_t) 0x00000002)
#define CONOPS_SETTHRESHVAL_FUNC_ID ((funcIdType_t) 0x00000003)
#define CONOPS_GETTHRESHVAL_FUNC_ID ((funcIdType_t) 0x00000004)
#define CONOPS_SETALLTHRESHVAL_FUNC_ID ((funcIdType_t) 0x00000005)
#define CONOPS_GETALLTHRESHVAL_FUNC_ID ((funcIdType_t) 0x00000006)
#define CONOPS_ADDNEWSCHEDULERECORD_FUNC_ID ((funcIdType_t) 0x00000007)
#define CONOPS_CLEARSCHEDULERECORDS_FUNC_ID ((funcIdType_t) 0x00000008)
#define CONOPS_SETENABLESUNTRACKINGFLAG_FUNC_ID ((funcIdType_t) 0x00000009)
#define CONOPS_GETENABLESUNTRACKINGFLAG_FUNC_ID ((funcIdType_t) 0x0000000A)
#define CONOPS_SENDNEWEVENT_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define CONOPS_GETOPMODE_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define CONOPS_SETTHRESHVAL_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define CONOPS_GETTHRESHVAL_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define CONOPS_SETALLTHRESHVAL_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define CONOPS_GETALLTHRESHVAL_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define CONOPS_ADDNEWSCHEDULERECORD_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define CONOPS_CLEARSCHEDULERECORDS_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define CONOPS_SETENABLESUNTRACKINGFLAG_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define CONOPS_GETENABLESUNTRACKINGFLAG_FUNCRESP_ID ((funcIdType_t) 0x0000000A)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Standard result enumeration which can be used in most situations as a return code
*/
#define CONOPS_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define CONOPS_STANDARDRESULT_ERROR ((uint8_t) 1)
#define CONOPS_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define CONOPS_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define CONOPS_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t CONOPS_StandardResult_t;

/*
    Increased-Hamming-distance-version of the regular boolean type. Used to represent regular boolean values.
*/
#define CONOPS_SAFEBOOL_SAFE_FALSE ((uint8_t) 0)
#define CONOPS_SAFEBOOL_SAFE_TRUE ((uint8_t) 255)
#define CONOPS_SAFEBOOL_MAX_CNT  ((uint8_t) 256)
typedef uint8_t CONOPS_SafeBool_t;

/*
    The enumeration defines the different threshold types configurable for the ConOps feature
*/
#define CONOPS_THRESHOLDVALUETYPES_DEFAULT ((uint8_t) 0)
#define CONOPS_THRESHOLDVALUETYPES_CBATT_SAFE ((uint8_t) 1)
#define CONOPS_THRESHOLDVALUETYPES_S_SAFE ((uint8_t) 2)
#define CONOPS_THRESHOLDVALUETYPES_S_DET ((uint8_t) 3)
#define CONOPS_THRESHOLDVALUETYPES_S_PAY ((uint8_t) 4)
#define CONOPS_THRESHOLDVALUETYPES_ANGVEL_MAX ((uint8_t) 5)
#define CONOPS_THRESHOLDVALUETYPES_ANGVEL_MIN ((uint8_t) 6)
#define CONOPS_THRESHOLDVALUETYPES_ANGVEL_RANGE ((uint8_t) 7)
#define CONOPS_THRESHOLDVALUETYPES_MAX_CNT  ((uint8_t) 8)
typedef uint8_t CONOPS_ThresholdValueTypes_t;

/*
    Contains the threshold settings for the ConOps
*/
typedef struct {
    int32_t i32CBattSafe;
    int32_t i32SSafe;
    int32_t i32SDet;
    int32_t ai32SPay[10];
    int32_t i32AngVelMax;
    int32_t i32AngVelLow;
    int32_t ai32AngVelRange[2];
} PACKED_STRUCT CONOPS_ThresholdValues_t;

/*
    Defines the set of supported ConOps modes in the system
*/
#define CONOPS_OPMODES_STATE_SAFE ((uint8_t) 1)
#define CONOPS_OPMODES_STATE_IDLE ((uint8_t) 2)
#define CONOPS_OPMODES_STATE_DETUMBLING ((uint8_t) 3)
#define CONOPS_OPMODES_STATE_PAYLOAD ((uint8_t) 4)
#define CONOPS_OPMODES_STATE_MAX ((uint8_t) 5)
#define CONOPS_OPMODES_MAX_CNT  ((uint8_t) 6)
typedef uint8_t CONOPS_OpModes_t;

/*
    Defines the set of supported ConOps state machine events
*/
#define CONOPS_EVENTS_RESET ((uint8_t) 0)
#define CONOPS_EVENTS_PERIODIC ((uint8_t) 1)
#define CONOPS_EVENTS_IDLE ((uint8_t) 3)
#define CONOPS_EVENTS_PAYLOAD_START ((uint8_t) 4)
#define CONOPS_EVENTS_PAYLOAD_STOP ((uint8_t) 5)
#define CONOPS_EVENTS_EVENT_MAX ((uint8_t) 6)
#define CONOPS_EVENTS_MAX_CNT  ((uint8_t) 7)
typedef uint8_t CONOPS_Events_t;

/*
    Time/date structure
*/
typedef struct {
    int32_t i32Year;
    int32_t i32Month;
    int32_t i32Day;
    int32_t i32Hour;
    int32_t i32Min;
    int32_t i32Sec;
} PACKED_STRUCT CONOPS_Time_t;

/*
    Geographic coordinates structure
*/
typedef struct {
    float fLon;
    float fLat;
    float fAlt;
} PACKED_STRUCT CONOPS_GeoCoord_t;

/*
    The structure defines the type of parameters used for desribing payload arguments
*/
typedef struct {
    uint8_t u8Flags;
    uint8_t au8Args[16];
} PACKED_STRUCT CONOPS_PayloadArgs_t;

/*
    The structure defines the parameters used for the ADCS pointing control for the payloads
*/
typedef struct {
    uint16_t u16AdcsPrepTime;
    uint8_t u8AdcsMode;
    CONOPS_GeoCoord_t sAdcsTargetRef;
} PACKED_STRUCT CONOPS_SchelAdcsCfg_t;

/*
    Payload control parameters description
*/
typedef struct {
    uint8_t u8PayId;
    CONOPS_SchelAdcsCfg_t sAdcsCfg;
    CONOPS_PayloadArgs_t sArgs;
} PACKED_STRUCT CONOPS_PayCfg_t;


typedef struct {
    CONOPS_Events_t eEventType;
    CONOPS_PayCfg_t sEventPayCfg;
} PACKED_STRUCT ConOpssendNewEventRequestData_t;

typedef struct {
    int32_t i32ThreshValue;
    uint8_t u8PayloadNum;
    CONOPS_ThresholdValueTypes_t eThresholdType;
} PACKED_STRUCT ConOpssetThreshValRequestData_t;

typedef struct {
    uint8_t u8PayloadNum;
    CONOPS_ThresholdValueTypes_t eThresholdType;
} PACKED_STRUCT ConOpsgetThreshValRequestData_t;

typedef struct {
    CONOPS_ThresholdValues_t sThreshVals;
} PACKED_STRUCT ConOpssetAllThreshValRequestData_t;

typedef struct {
    CONOPS_Time_t sTime;
    uint8_t u8PayloadID;
    uint16_t u16Duration;
    CONOPS_SchelAdcsCfg_t sAdcsCfg;
    CONOPS_PayloadArgs_t sPayArgs;
} PACKED_STRUCT ConOpsaddNewScheduleRecordRequestData_t;

typedef struct {
    CONOPS_SafeBool_t eEnFlag;
} PACKED_STRUCT ConOpssetEnableSunTrackingFlagRequestData_t;


typedef struct {
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpssendNewEventResponseData_t;

typedef struct {
    CONOPS_OpModes_t eOpModeNum;
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpsgetOpModeResponseData_t;

typedef struct {
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpssetThreshValResponseData_t;

typedef struct {
    int32_t i32ThreshValue;
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpsgetThreshValResponseData_t;

typedef struct {
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpssetAllThreshValResponseData_t;

typedef struct {
    CONOPS_ThresholdValues_t sThreshVals;
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpsgetAllThreshValResponseData_t;

typedef struct {
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpsaddNewScheduleRecordResponseData_t;

typedef struct {
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpsclearScheduleRecordsResponseData_t;

typedef struct {
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpssetEnableSunTrackingFlagResponseData_t;

typedef struct {
    CONOPS_SafeBool_t eEnFlag;
    CONOPS_StandardResult_t eOpResult;
} PACKED_STRUCT ConOpsgetEnableSunTrackingFlagResponseData_t;


#endif  // #ifndef __FP_CONOPSPROTOCOLTYPES_H__

