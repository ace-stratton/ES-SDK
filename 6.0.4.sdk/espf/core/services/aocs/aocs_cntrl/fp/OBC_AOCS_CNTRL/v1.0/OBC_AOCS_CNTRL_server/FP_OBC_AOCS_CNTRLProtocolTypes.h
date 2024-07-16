/*!
********************************************************************************************
* @file FP_OBC_AOCS_CNTRLProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface OBC_AOCS_CNTRL v1.0
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

#ifndef __FP_OBC_AOCS_CNTRLPROTOCOLTYPES_H__
#define __FP_OBC_AOCS_CNTRLPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL ((uint16_t) (0x00000047))

#define OBC_AOCS_CNTRL_RESETAOCSPMBUFF_FUNC_ID ((funcIdType_t) 0x00000000)
#define OBC_AOCS_CNTRL_GETMAXTIMEFORAUTOLOGGING_FUNC_ID ((funcIdType_t) 0x00000001)
#define OBC_AOCS_CNTRL_SETMAXTIMEFORAUTOLOGGING_FUNC_ID ((funcIdType_t) 0x00000002)
#define OBC_AOCS_CNTRL_STARTLOGGING_FUNC_ID ((funcIdType_t) 0x00000003)
#define OBC_AOCS_CNTRL_GETDATATYPEFORASSESSMENT_FUNC_ID ((funcIdType_t) 0x00000004)
#define OBC_AOCS_CNTRL_SETDATATYPEFORASSESSMENT_FUNC_ID ((funcIdType_t) 0x00000005)
#define OBC_AOCS_CNTRL_GETTHRESHOLDLEVELS_FUNC_ID ((funcIdType_t) 0x00000006)
#define OBC_AOCS_CNTRL_SETTHRESHOLDLEVELS_FUNC_ID ((funcIdType_t) 0x00000007)
#define OBC_AOCS_CNTRL_GETPMOUTPUT_FUNC_ID ((funcIdType_t) 0x00000008)
#define OBC_AOCS_CNTRL_GETCONFIG_FUNC_ID ((funcIdType_t) 0x00000009)
#define OBC_AOCS_CNTRL_GETUPDATEINTERVAL_FUNC_ID ((funcIdType_t) 0x0000000A)
#define OBC_AOCS_CNTRL_SETUPDATEINTERVAL_FUNC_ID ((funcIdType_t) 0x0000000B)
#define OBC_AOCS_CNTRL_GETSAMPLESTOSKIP_FUNC_ID ((funcIdType_t) 0x0000000C)
#define OBC_AOCS_CNTRL_SETSAMPLESTOSKIP_FUNC_ID ((funcIdType_t) 0x0000000D)
#define OBC_AOCS_CNTRL_SETAOCSSTATE_FUNC_ID ((funcIdType_t) 0x0000000E)
#define OBC_AOCS_CNTRL_GETAOCSSTATE_FUNC_ID ((funcIdType_t) 0x0000000F)
#define OBC_AOCS_CNTRL_RESETAOCSPMBUFF_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define OBC_AOCS_CNTRL_GETMAXTIMEFORAUTOLOGGING_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define OBC_AOCS_CNTRL_SETMAXTIMEFORAUTOLOGGING_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define OBC_AOCS_CNTRL_STARTLOGGING_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define OBC_AOCS_CNTRL_GETDATATYPEFORASSESSMENT_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define OBC_AOCS_CNTRL_SETDATATYPEFORASSESSMENT_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define OBC_AOCS_CNTRL_GETTHRESHOLDLEVELS_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define OBC_AOCS_CNTRL_SETTHRESHOLDLEVELS_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define OBC_AOCS_CNTRL_GETPMOUTPUT_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define OBC_AOCS_CNTRL_GETCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define OBC_AOCS_CNTRL_GETUPDATEINTERVAL_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define OBC_AOCS_CNTRL_SETUPDATEINTERVAL_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define OBC_AOCS_CNTRL_GETSAMPLESTOSKIP_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define OBC_AOCS_CNTRL_SETSAMPLESTOSKIP_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define OBC_AOCS_CNTRL_SETAOCSSTATE_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define OBC_AOCS_CNTRL_GETAOCSSTATE_FUNCRESP_ID ((funcIdType_t) 0x0000000F)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define OBC_AOCS_CNTRL_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define OBC_AOCS_CNTRL_STANDARDRESULT_ERROR ((uint8_t) 1)
#define OBC_AOCS_CNTRL_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define OBC_AOCS_CNTRL_STANDARDRESULT_NOT_SUPPORTED2 ((uint8_t) 3)
#define OBC_AOCS_CNTRL_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_AOCS_CNTRL_StandardResult_t;

#define OBC_AOCS_CNTRL_AOCSSERVICEERROR_AOCS_ERR_OK ((uint8_t) 0)
#define OBC_AOCS_CNTRL_AOCSSERVICEERROR_AOCS_ERR_BUSY ((uint8_t) 1)
#define OBC_AOCS_CNTRL_AOCSSERVICEERROR_AOCS_ERR_FAILED ((uint8_t) 2)
#define OBC_AOCS_CNTRL_AOCSSERVICEERROR_MAX_CNT  ((uint8_t) 3)
typedef uint8_t OBC_AOCS_CNTRL_AocsServiceError_t;

#define OBC_AOCS_CNTRL_LOGDATATYPES_EST_ATT_ANGL ((uint8_t) 0)
#define OBC_AOCS_CNTRL_LOGDATATYPES_EST_ANG_RATES ((uint8_t) 1)
#define OBC_AOCS_CNTRL_LOGDATATYPES_MEAS_MAG_FIELD_VEC ((uint8_t) 2)
#define OBC_AOCS_CNTRL_LOGDATATYPES_EST_INNOVATION_VEC ((uint8_t) 3)
#define OBC_AOCS_CNTRL_LOGDATATYPES_Q_ERR_VEC ((uint8_t) 4)
#define OBC_AOCS_CNTRL_LOGDATATYPES_MAG_MCU_TEMP ((uint8_t) 5)
#define OBC_AOCS_CNTRL_LOGDATATYPES_RATE_SENS_TEMP ((uint8_t) 6)
#define OBC_AOCS_CNTRL_LOGDATATYPES_RATE_CONVERGENCE ((uint8_t) 7)
#define OBC_AOCS_CNTRL_LOGDATATYPES_MAX_CNT  ((uint8_t) 8)
typedef uint8_t OBC_AOCS_CNTRL_logDataTypes_t;

#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_UNDEFINED ((uint8_t) 0)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_EXISTING_CONTROL ((uint8_t) 1)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_NO_CONTROL ((uint8_t) 2)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_NORMAL_DETUMBLING ((uint8_t) 3)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_Y_THOMSON ((uint8_t) 4)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_Y_THOMSON_MEMS_RATE ((uint8_t) 5)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_FAST_DETUMBLING ((uint8_t) 6)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_VERY_FAST_DETUMBLING ((uint8_t) 7)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_Y_MOMENTUM ((uint8_t) 8)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_Y_MOMENTUM_FULL_STATE_EKF ((uint8_t) 9)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_3AXIS ((uint8_t) 10)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_SUN_TRACKING ((uint8_t) 11)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_TARGET_TRACKING ((uint8_t) 12)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_USER1 ((uint8_t) 13)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_USER2 ((uint8_t) 14)
#define OBC_AOCS_CNTRL_AOCSSTATE_AOCS_STATE_USER3 ((uint8_t) 15)
#define OBC_AOCS_CNTRL_AOCSSTATE_MAX_CNT  ((uint8_t) 16)
typedef uint8_t OBC_AOCS_CNTRL_AocsState_t;

#define OBC_AOCS_CNTRL_AOCSSTATEREQSTATE_AOCS_STATE_REQ_COMPLETED ((uint8_t) 0)
#define OBC_AOCS_CNTRL_AOCSSTATEREQSTATE_AOCS_STATE_REQ_NEW_REQ ((uint8_t) 1)
#define OBC_AOCS_CNTRL_AOCSSTATEREQSTATE_AOCS_REQ_IN_PROGRESS ((uint8_t) 2)
#define OBC_AOCS_CNTRL_AOCSSTATEREQSTATE_AOCS_STATE_REQ_FAILED ((uint8_t) 3)
#define OBC_AOCS_CNTRL_AOCSSTATEREQSTATE_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_AOCS_CNTRL_AocsStateReqState_t;

typedef struct {
    float fTolerance;
    float fSafety_factor;
} PACKED_STRUCT OBC_AOCS_CNTRL_thresholdValues_t;

typedef struct {
    uint8_t u8LongTermMetric;
    uint16_t u16EncodedStability;
} PACKED_STRUCT OBC_AOCS_CNTRL_PMoutput_t;

typedef struct {
    uint32_t u32Max_time_for_logging;
    uint8_t u8Update_interval;
    OBC_AOCS_CNTRL_logDataTypes_t eData_type;
    uint16_t u16Samples_to_skip;
} PACKED_STRUCT OBC_AOCS_CNTRL_Config_t;

typedef struct {
    float fRefParam1;
    float fRefParam2;
    float fRefParam3;
} PACKED_STRUCT OBC_AOCS_CNTRL_AocsRefParams_t;


typedef struct {
    uint32_t u32MaxTimeForAutoLogging;
} PACKED_STRUCT OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingRequestData_t;

typedef struct {
    uint32_t u32TimeWindowForLogging;
} PACKED_STRUCT OBC_AOCS_CNTRLstartLoggingRequestData_t;

typedef struct {
    OBC_AOCS_CNTRL_logDataTypes_t eDataType;
} PACKED_STRUCT OBC_AOCS_CNTRLsetDataTypeForAssessmentRequestData_t;

typedef struct {
    OBC_AOCS_CNTRL_thresholdValues_t asThreshold[3];
} PACKED_STRUCT OBC_AOCS_CNTRLsetThresholdLevelsRequestData_t;

typedef struct {
    uint8_t u8Update_interval;
} PACKED_STRUCT OBC_AOCS_CNTRLsetUpdateIntervalRequestData_t;

typedef struct {
    uint16_t u16Samples_to_skip;
} PACKED_STRUCT OBC_AOCS_CNTRLsetSamplesToSkipRequestData_t;

typedef struct {
    OBC_AOCS_CNTRL_AocsState_t eAocsState;
    OBC_AOCS_CNTRL_AocsRefParams_t sRefParams;
} PACKED_STRUCT OBC_AOCS_CNTRLsetAocsStateRequestData_t;


typedef struct {
    uint32_t u32MaxTimeForAutoLogging;
} PACKED_STRUCT OBC_AOCS_CNTRLgetMaxTimeForAutoLoggingResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;
} PACKED_STRUCT OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_logDataTypes_t eDataType;
} PACKED_STRUCT OBC_AOCS_CNTRLgetDataTypeForAssessmentResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;
} PACKED_STRUCT OBC_AOCS_CNTRLsetDataTypeForAssessmentResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_thresholdValues_t asThreshold[3];
} PACKED_STRUCT OBC_AOCS_CNTRLgetThresholdLevelsResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;
} PACKED_STRUCT OBC_AOCS_CNTRLsetThresholdLevelsResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_PMoutput_t asOutput[3];
} PACKED_STRUCT OBC_AOCS_CNTRLgetPMOutputResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_Config_t sCurrent_config;
} PACKED_STRUCT OBC_AOCS_CNTRLgetConfigResponseData_t;

typedef struct {
    uint8_t u8Update_interval;
} PACKED_STRUCT OBC_AOCS_CNTRLgetUpdateIntervalResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;
} PACKED_STRUCT OBC_AOCS_CNTRLsetUpdateIntervalResponseData_t;

typedef struct {
    uint16_t u16Samples_to_skip;
} PACKED_STRUCT OBC_AOCS_CNTRLgetSamplesToSkipResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;
} PACKED_STRUCT OBC_AOCS_CNTRLsetSamplesToSkipResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_AocsServiceError_t eOpResult;
} PACKED_STRUCT OBC_AOCS_CNTRLsetAocsStateResponseData_t;

typedef struct {
    OBC_AOCS_CNTRL_AocsServiceError_t eOpResult;
    OBC_AOCS_CNTRL_AocsState_t eAocsState;
    OBC_AOCS_CNTRL_AocsStateReqState_t eReqState;
} PACKED_STRUCT OBC_AOCS_CNTRLgetAocsStateResponseData_t;


#endif  // #ifndef __FP_OBC_AOCS_CNTRLPROTOCOLTYPES_H__

