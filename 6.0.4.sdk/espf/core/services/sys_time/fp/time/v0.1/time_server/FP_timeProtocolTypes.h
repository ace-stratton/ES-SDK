/*!
********************************************************************************************
* @file FP_timeProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface time v0.1
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

#ifndef __FP_TIMEPROTOCOLTYPES_H__
#define __FP_TIMEPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_TIME ((uint16_t) (0x00000018))

#define TIME_SET_DATE_FUNC_ID ((funcIdType_t) 0x00000001)
#define TIME_GET_DATE_FUNC_ID ((funcIdType_t) 0x00000002)
#define TIME_SET_TIME_FUNC_ID ((funcIdType_t) 0x00000003)
#define TIME_GET_TIME_FUNC_ID ((funcIdType_t) 0x00000004)
#define TIME_ENABLE_CALIBRATION_OUTPUT_FUNC_ID ((funcIdType_t) 0x00000005)
#define TIME_CONFIGURE_RTC_CALIBRATION_PARAMETERS_FUNC_ID ((funcIdType_t) 0x00000006)
#define TIME_RETRIEVE_RTC_CALIBRATION_PARAMETERS_FUNC_ID ((funcIdType_t) 0x00000007)
#define TIME_GET_RTC_CLOCK_SOURCE_FUNC_ID ((funcIdType_t) 0x00000008)
#define TIME_SET_DATE_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define TIME_GET_DATE_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define TIME_SET_TIME_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define TIME_GET_TIME_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define TIME_ENABLE_CALIBRATION_OUTPUT_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define TIME_CONFIGURE_RTC_CALIBRATION_PARAMETERS_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define TIME_RETRIEVE_RTC_CALIBRATION_PARAMETERS_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define TIME_GET_RTC_CLOCK_SOURCE_FUNCRESP_ID ((funcIdType_t) 0x00000008)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Operation status
*/
#define TIME_OP_STATUS_ERROR ((uint8_t) 0)
#define TIME_OP_STATUS_OK ((uint8_t) 1)
#define TIME_OP_STATUS_MAX_CNT  ((uint8_t) 2)
typedef uint8_t TIME_op_status_t;

/*
    Week day
*/
#define TIME_WEEK_DAY_INVALID ((uint8_t) 0)
#define TIME_WEEK_DAY_MONDAY ((uint8_t) 1)
#define TIME_WEEK_DAY_TUESDAY ((uint8_t) 2)
#define TIME_WEEK_DAY_WEDNESDAY ((uint8_t) 3)
#define TIME_WEEK_DAY_THURSDAY ((uint8_t) 4)
#define TIME_WEEK_DAY_FRIDAY ((uint8_t) 5)
#define TIME_WEEK_DAY_SATURDAY ((uint8_t) 6)
#define TIME_WEEK_DAY_SUNDAY ((uint8_t) 7)
#define TIME_WEEK_DAY_MAX_CNT  ((uint8_t) 8)
typedef uint8_t TIME_week_day_t;

/*
    Date
*/
typedef struct {
    uint16_t u16Year;
    uint8_t u8Mon;
    uint8_t u8Day;
    TIME_week_day_t eWday;
} PACKED_STRUCT TIME_sdate_t;

/*
    Time
*/
typedef struct {
    uint8_t u8Hour;
    uint8_t u8Min;
    uint8_t u8Sec;
    uint16_t u16Ms;
    uint16_t u16Us;
} PACKED_STRUCT TIME_stime_t;

/*
    Calibration output frequency.
*/
#define TIME_CAL_FREQ_F001HZ ((uint8_t) 0)
#define TIME_CAL_FREQ_F512HZ ((uint8_t) 1)
#define TIME_CAL_FREQ_MAX_CNT  ((uint8_t) 2)
typedef uint8_t TIME_cal_freq_t;

/*
    CALR[CALP] value
*/
#define TIME_CALP_PULSES_RESET ((uint8_t) 0)
#define TIME_CALP_PULSES_SET ((uint8_t) 1)
#define TIME_CALP_PULSES_MAX_CNT  ((uint8_t) 2)
typedef uint8_t TIME_calp_pulses_t;

/*
    RTC source oscillator
*/
#define TIME_RTC_SOURCE_RTC_OSC_NONE ((uint8_t) 0)
#define TIME_RTC_SOURCE_RTC_OSC_LSE ((uint8_t) 1)
#define TIME_RTC_SOURCE_RTC_OSC_LSI ((uint8_t) 2)
#define TIME_RTC_SOURCE_RTC_OSC_HSE ((uint8_t) 3)
#define TIME_RTC_SOURCE_RTC_OSC_UNKNOWN ((uint8_t) 4)
#define TIME_RTC_SOURCE_MAX_CNT  ((uint8_t) 5)
typedef uint8_t TIME_rtc_source_t;

/*
    RTC source type
*/
typedef struct {
    bool bEnabled;
    TIME_rtc_source_t eSource;
    uint8_t u8Rtc_asynchronous_prescaler;
    uint16_t u16Rtc_synchronous_prescaler;
    uint8_t u8Hse_division_factor;
} PACKED_STRUCT TIME_s_rtc_info_t;


typedef struct {
    TIME_sdate_t sDate;
} PACKED_STRUCT timeset_dateRequestData_t;

typedef struct {
    TIME_stime_t sTime;
} PACKED_STRUCT timeset_timeRequestData_t;

typedef struct {
    TIME_cal_freq_t eF;
} PACKED_STRUCT timeenable_calibration_outputRequestData_t;

typedef struct {
    TIME_calp_pulses_t eCalp;
    uint16_t u16Calm;
} PACKED_STRUCT timeconfigure_rtc_calibration_parametersRequestData_t;


typedef struct {
    TIME_op_status_t eStatus;
} PACKED_STRUCT timeset_dateResponseData_t;

typedef struct {
    TIME_op_status_t eStatus;
    TIME_sdate_t sDate;
} PACKED_STRUCT timeget_dateResponseData_t;

typedef struct {
    TIME_op_status_t eStatus;
} PACKED_STRUCT timeset_timeResponseData_t;

typedef struct {
    TIME_op_status_t eStatus;
    TIME_stime_t sTime;
} PACKED_STRUCT timeget_timeResponseData_t;

typedef struct {
    TIME_op_status_t eStatus;
} PACKED_STRUCT timeenable_calibration_outputResponseData_t;

typedef struct {
    TIME_op_status_t eStatus;
} PACKED_STRUCT timeconfigure_rtc_calibration_parametersResponseData_t;

typedef struct {
    TIME_calp_pulses_t eCalp;
    uint16_t u16Calm;
} PACKED_STRUCT timeretrieve_rtc_calibration_parametersResponseData_t;

typedef struct {
    TIME_op_status_t eStatus;
    TIME_s_rtc_info_t sInfo;
} PACKED_STRUCT timeget_rtc_clock_sourceResponseData_t;


#endif  // #ifndef __FP_TIMEPROTOCOLTYPES_H__

