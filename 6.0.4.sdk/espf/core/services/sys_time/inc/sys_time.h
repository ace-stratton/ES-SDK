/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef SYS_TIME_H_
#define SYS_TIME_H_

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup services_sys_time Time
 * @{
 *
 * The main features of this service are:
 * - Provision and maintenance of the system date/time (usually based on internal or external RTC module).
 * - Date/time synchronization support.
 * - RTC calibration support (if supported by the HW).
 *
 * @file sys_time.h
 *
 * @brief Basic calendar services interface
 *
 * @}
 * @}
 */

#include "datetime.h"
#include "fp/time/v0.1/time_server/FP_timeProtocolTypes.h"

typedef datetime_time_t  sys_time_t;
typedef datetime_date_t  sys_date_t;

typedef struct
{
    uint16_t calm;
    TIME_calp_pulses_t calp;
} sys_time_rtc_calib_settings_t;

typedef enum
{
    SYS_TIME_OSC_NONE,
    SYS_TIME_OSC_LSE,
    SYS_TIME_OSC_LSI,
    SYS_TIME_OSC_HSE,
    SYS_TIME_OSC_UNKNOWN
} sys_time_osc_t;

typedef struct
{
    bool enabled;
    sys_time_osc_t source_osc;
    uint8_t hse_division_factor;
    uint8_t rtc_asynchronous_prescaler;
    uint16_t rtc_synchronous_prescaler;
} sys_time_rtc_clock_info_t;

/**
 * @brief      Initializes the time service (uses RTC if applicable)
 * @note       Must be performed only once in the program life cycle
 *             The value of the calendare registers is retained on reset,
 *             even after power-off as long as Vbat is adequately supplied.
 *             Calendar will be reset to 2000-01-01 00:00:00 if the MCU is
 *             completely cutoff from power (including Vbat), although old value
 *             may be retained if cutoff is no more than a few seconds. This is not
 *             guaranteed however.
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_init(void);

/**
 * @brief      Applies the configured RTC calibration values to the RTC peripheral.
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_apply_rtc_calib(void);

/**
 * @brief     Retrieves the stored NVM settings for the RTC calibration.
 * @param[in] p_calib_settings RTC calibration settings to update from NVM
 * @return    `true` on success, `false` otherwise
 */
bool sys_time_retrieve_rtc_calib_settings(sys_time_rtc_calib_settings_t * const p_calib_settings);

/**
 * @brief     Updates the stored NVM settings for the RTC calibration.
 * @param[in] p_calib_settings RTC calibration settings to update in NVM
 * @return    `true` on success, `false` otherwise
 */
bool sys_time_update_rtc_calib_settings(const sys_time_rtc_calib_settings_t * const p_calib_settings);

/**
 * @brief      Activates the RTC calibration output with a predefined frequency of 1Hz (if applicable).
 * @note       Has effect only once throughout the program life cycle. Check the MCU reference for information
 *             on which pin the calibration signal will be output.
 * @param[in]  mode Pin output frequency @ref TIME_cal_freq_t
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_en_calib_out(TIME_cal_freq_t mode);

/**
 * @brief      Returns the current time
 * @note       The the `.us` value in p_time should be taken with a grain of salt as the finest
 *             granularity achieved on the current hardware is ~30 microseconds
 * @param[out] p_time Current time
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_get(sys_time_t* const p_time);

/**
 * @brief      Sets the current time
 * @param[in]  p_time New time specified by caller
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_set(const sys_time_t* const p_time);

/**
 * @brief      Gets the current date
 * @param[out] date Current date
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_get_date(sys_date_t* const p_date);

/**
 * @brief      Sets the current date
 * @param[in]  date New date specified by caller
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_set_date(const sys_date_t* const p_date);

/**
 * @brief      Returns the current date and time with ~30 microsecond precision
 * @note       The the `.us` value in p_time should be taken with a grain of salt as the finest
 *             granularity achieved on the current hardware is ~30 microseconds
 * @param[out] p_date Pointer to sys_date_t structure to be filled with the current date
 * @param[out] p_time Pointer to sys_time_t structure to be filled with the current time
 * @return     `true` on success, `false` on error (may be due to timeout)
 *              On error, structure values are unchanged
 */
bool sys_time_get_stamp(sys_date_t* const p_date, sys_time_t* const p_time);

/**
 * @brief      Sets the current date and time with up to ~30 microseconds precision
 * @note       The the `.us` value in p_time should be taken with a grain of salt as the finest
 *             granularity achieved on the current hardware is ~30 microseconds
 * @param[in]  p_date Pointer to sys_date_t structure with the new date to be set
 * @param[in]  p_time Pointer to sys_time_t structure with the new time to be set
 * @param[in]  timeout mutex lock timeout in ms.
 *             0 - exit with false immediately resource is not available
 *             osWaitForever - wait forever, osWaitForever is a constant defined in <cmsis_os2.h>
 * @return     `true` on success, `false` on error (may be due to timeout)
 *             On error, current datetime is not changed
 */
bool sys_time_set_stamp(const sys_date_t* const p_date, const sys_time_t* const p_time, uint32_t timeout);

/**
 * @brief       Get the current oscillator source for the RTC clock
 * @param[out]  info Pointer to a structure to be filled with the info.
 * @return     `true` on success, `false` otherwise
 */
bool sys_time_get_rtc_clock_source(sys_time_rtc_clock_info_t* info);

#endif /* SYS_TIME_H_ */
