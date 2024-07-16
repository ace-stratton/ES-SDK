/*!
********************************************************************************************
* @file FP_TelemetryProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface Telemetry v0.1
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

#ifndef __FP_TELEMETRYPROTOCOLTYPES_H__
#define __FP_TELEMETRYPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_TELEMETRY ((uint16_t) (0x00000102))

#define TELEMETRY_GETTELEMETRYGENERALCONFIG_FUNC_ID ((funcIdType_t) 0x00000000)
#define TELEMETRY_SETTELEMETRYGENERALCONFIG_FUNC_ID ((funcIdType_t) 0x00000001)
#define TELEMETRY_GETTELEMETRYPRESETCONFIG_FUNC_ID ((funcIdType_t) 0x00000002)
#define TELEMETRY_SETTELEMETRYPRESETCONFIG_FUNC_ID ((funcIdType_t) 0x00000003)
#define TELEMETRY_SETACTIVEPRESET_FUNC_ID ((funcIdType_t) 0x00000004)
#define TELEMETRY_GETACTIVEPRESET_FUNC_ID ((funcIdType_t) 0x00000005)
#define TELEMETRY_RESTOREACTIVEPRESET_FUNC_ID ((funcIdType_t) 0x00000006)
#define TELEMETRY_GETTELEMETRYFILESINKCONFIG_FUNC_ID ((funcIdType_t) 0x00000007)
#define TELEMETRY_SETTELEMETRYFILESZLIMITCONFIG_FUNC_ID ((funcIdType_t) 0x00000008)
#define TELEMETRY_SETTELEMETRYFILETMLIMITCONFIG_FUNC_ID ((funcIdType_t) 0x00000009)
#define TELEMETRY_RESUMEFILETELEMETRY_FUNC_ID ((funcIdType_t) 0x0000000A)
#define TELEMETRY_PAUSEFILETELEMETRY_FUNC_ID ((funcIdType_t) 0x0000000B)
#define TELEMETRY_CLEANTELEMETRYFILES_FUNC_ID ((funcIdType_t) 0x0000000C)
#define TELEMETRY_GETTELEMETRYOPERATIONSTATS_FUNC_ID ((funcIdType_t) 0x0000000D)
#define TELEMETRY_GETTELEMETRYGENERALCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define TELEMETRY_SETTELEMETRYGENERALCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define TELEMETRY_GETTELEMETRYPRESETCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define TELEMETRY_SETTELEMETRYPRESETCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define TELEMETRY_SETACTIVEPRESET_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define TELEMETRY_GETACTIVEPRESET_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define TELEMETRY_RESTOREACTIVEPRESET_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define TELEMETRY_GETTELEMETRYFILESINKCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define TELEMETRY_SETTELEMETRYFILESZLIMITCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define TELEMETRY_SETTELEMETRYFILETMLIMITCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define TELEMETRY_RESUMEFILETELEMETRY_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define TELEMETRY_PAUSEFILETELEMETRY_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define TELEMETRY_CLEANTELEMETRYFILES_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define TELEMETRY_GETTELEMETRYOPERATIONSTATS_FUNCRESP_ID ((funcIdType_t) 0x0000000D)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Standard result enumeration which can be used in most situations as a return code
*/
#define TELEMETRY_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define TELEMETRY_STANDARDRESULT_ERROR ((uint8_t) 1)
#define TELEMETRY_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define TELEMETRY_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define TELEMETRY_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t TELEMETRY_StandardResult_t;

/*
    Increased-Hamming-distance-version of the regular boolean
*/
#define TELEMETRY_SAFE_BOOL_SAFE_FALSE ((uint8_t) 0)
#define TELEMETRY_SAFE_BOOL_SAFE_TRUE ((uint8_t) 255)
#define TELEMETRY_SAFE_BOOL_MAX_CNT  ((uint8_t) 256)
typedef uint8_t TELEMETRY_safe_bool_t;

/*
    Settings for the telemetry service stored in the nvm
*/
typedef struct {
    uint16_t u16Data_id;
    bool bActive;
    uint16_t u16Acq_period;
} PACKED_STRUCT TELEMETRY_tlm_preset_cfg_t;

/*
    Structure containing the values for the telemetry size limits
*/
typedef struct {
    uint32_t u32Size_limit_kb;
    uint16_t u16Max_log_files_cnt;
} PACKED_STRUCT TELEMETRY_tlm_file_size_limit_cfg_t;

/*
    Structure containing the values for the telemetry time limits
*/
typedef struct {
    uint32_t u32Time_limit_sec;
    uint16_t u16File_size_limit_kb;
} PACKED_STRUCT TELEMETRY_tlm_file_time_limit_cfg_t;

/*
    How to keep the logging files, time based or size based
*/
#define TELEMETRY_TLM_FILE_LOGGING_TYPE_SIZE_LIMIT ((uint8_t) 0)
#define TELEMETRY_TLM_FILE_LOGGING_TYPE_TIME_LIMIT ((uint8_t) 1)
#define TELEMETRY_TLM_FILE_LOGGING_TYPE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t TELEMETRY_tlm_file_logging_type_t;

/*
    Active configuration for the telemetry service
*/
typedef struct {
    TELEMETRY_safe_bool_t eTelemetry_en;
    TELEMETRY_safe_bool_t eFile_telemetry_en;
} PACKED_STRUCT TELEMETRY_tlm_general_cfg_t;

/*
    Counters of relevant events from the telemetry service
*/
typedef struct {
    uint32_t u32Msg_pushed_cnt;
    uint32_t u32Msg_popped_cnt;
    uint32_t u32Free_bytes_min;
    uint32_t u32Discarded_messages_cnt;
    uint32_t u32Max_number_of_batch_msg;
    uint32_t u32Active_slot_id;
} PACKED_STRUCT TELEMETRY_tlm_stats_t;


typedef struct {
    TELEMETRY_tlm_general_cfg_t sCfg;
} PACKED_STRUCT TelemetrysetTelemetryGeneralConfigRequestData_t;

typedef struct {
    TELEMETRY_tlm_preset_cfg_t asTelemetry_preset_cfg[40];
} PACKED_STRUCT TelemetrysetTelemetryPresetConfigRequestData_t;

typedef struct {
    uint8_t u8Req_active_preset;
} PACKED_STRUCT TelemetrysetActivePresetRequestData_t;

typedef struct {
    TELEMETRY_tlm_file_size_limit_cfg_t sSize_limit_cfg;
} PACKED_STRUCT TelemetrysetTelemetryFileSzLimitConfigRequestData_t;

typedef struct {
    TELEMETRY_tlm_file_time_limit_cfg_t sTime_limit_cfg;
} PACKED_STRUCT TelemetrysetTelemetryFileTmLimitConfigRequestData_t;

typedef struct {
    uint16_t u16Seconds_before_resume;
} PACKED_STRUCT TelemetrypauseFileTelemetryRequestData_t;


typedef struct {
    TELEMETRY_tlm_general_cfg_t sCfg;
} PACKED_STRUCT TelemetrygetTelemetryGeneralConfigResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetrysetTelemetryGeneralConfigResponseData_t;

typedef struct {
    uint8_t u8Slot_preset_cnt;
    uint8_t u8Max_tlm_msg_cnt;
    TELEMETRY_tlm_preset_cfg_t asTelemetry_preset_cfg[40];
} PACKED_STRUCT TelemetrygetTelemetryPresetConfigResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetrysetTelemetryPresetConfigResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
    uint8_t u8Avail_presets_cnt;
} PACKED_STRUCT TelemetrysetActivePresetResponseData_t;

typedef struct {
    uint8_t u8Active_preset_id;
} PACKED_STRUCT TelemetrygetActivePresetResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetryrestoreActivePresetResponseData_t;

typedef struct {
    TELEMETRY_tlm_file_logging_type_t eActive_file_cfg_type;
    TELEMETRY_tlm_file_size_limit_cfg_t sSize_limit_cfg;
    TELEMETRY_tlm_file_time_limit_cfg_t sTime_limit_cfg;
} PACKED_STRUCT TelemetrygetTelemetryFileSinkConfigResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetrysetTelemetryFileSzLimitConfigResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetrysetTelemetryFileTmLimitConfigResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetryresumeFileTelemetryResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetrypauseFileTelemetryResponseData_t;

typedef struct {
    TELEMETRY_StandardResult_t eRes;
} PACKED_STRUCT TelemetrycleanTelemetryFilesResponseData_t;

typedef struct {
    TELEMETRY_tlm_stats_t sTelemetry_stats;
} PACKED_STRUCT TelemetrygetTelemetryOperationStatsResponseData_t;


#endif  // #ifndef __FP_TELEMETRYPROTOCOLTYPES_H__

