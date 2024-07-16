/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup services_sys_time
 * @{
 *
 * @file sys_time.c
 * @brief Main implementation of the Time service
 *
 * @}
 */

#include "sys_time.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_rtc.h"
#include "stm32h7xx_ll_rtc.h"
#include "stm32h7xx_ll_rcc.h"
#include "cmsis_os2.h"
#include "TaskMonitor.h"
#include "trace.h"
#include "drv_led.h"
#include "nvm.h"
#include "assertions.h"


#define FS_YEAR_OFFSET   (2000U)
#define FS_FORMAT        (RTC_FORMAT_BIN)
#define FS_LOCK_TIME     (osWaitForever)

/**
 * The value of 1000 for both MAX_LOOP_RSF and MAX_LOOP_SHPF have been chosen empirically.
 * The worst case scenario according to documentation(RM0433 46.3.8) is 4 RTCCLK cycles, where
 * the usual RTCCLK frequency is 32678Hz, so 1 cycle is ~1/32768s, ie ~30.5us.
 * The HAL_GetTick() granularity is 1 millisecond which is way too rough for our needs.
 * The timeout for the loops is longest right after update (call to sys_time_set_stamp()).
 * An empirical test of 100000 (hundred thousand) repetitions has been made
 * and the count of loops required for RSF to clear right after a call to sys_time_set_stamp()
 * mostly varies between 300 and 720, but most of the times it is around 700.
 * Not once in the test have the loops been more than 800.
 * Considering that the timeout should not be longer according documentation, a limit of 1000
 * should be more than enough.
 * The same test has been made for SHPF and its value is around 600, but otherwise the case is the same.
 * IMPORTANT! This value should be adjusted if a different frequency than 32768Hz is used for RTCCLK
 * or the cpu core frequency is changed as this would affect the looping speed.
 */
#define MAX_LOOP_RSF    (1000)
#define MAX_LOOP_SHPF   (1000)

/**
 * In STM32H753 the maximum value for the Asynchronous Presalar (PREDIV_A) is the maximum of a 7-bit binary value.
 * In STM32H753 the maximum value for the Synchronous Presalar (PREDIV_S) is the maximum of a 15-bit binary value.
 * With the current hardware settings the RTCCLK uses LSE as source with frequency is 32768Hz.
 * In order to have correct counting, (1+PREDIV_A)*(1+PREDIV_S) must equal RTCCLK, ie 32768 with current configuration.
 * See RM0433 46.3.4 and 46.6.5
 */
#define MAX_PREDIV_A_VALUE    (0x7F)    /* 127 */
#define MAX_PREDIV_S_VALUE    (0x7FFF)  /* 32767 */
#define CONFIG_PREDIV_A_VALUE (0)
#define CONFIG_PREDIV_S_VALUE (0x7FFF)  /* 32767 */
#if (CONFIG_PREDIV_A_VALUE > MAX_PREDIV_A_VALUE) || (CONFIG_PREDIV_A_VALUE < 0)
# error message("CONFIG_PREDIV_A_VALUE should not be greater than MAX_PREDIV_A_VALUE")
#endif
#if (CONFIG_PREDIV_S_VALUE > MAX_PREDIV_S_VALUE) || (CONFIG_PREDIV_S_VALUE < 0)
# error message("CONFIG_PREDIV_S_VALUE should not be greater than MAX_PREDIV_S_VALUE")
#endif

/**
 * buffer_time and buffer_date are used to provide date and time quickly when the RTC calendar registers are not immediately available.
 * This happens up to 4*RTCCLK cycles after an update (call to sys_time_set_stamp()) or one RTCCLK cycle after a read (sys_time_get_stamp()).
 * The eventual drift when getting time quickly after an update with the current settings to PREDIV_S (32767)
 * is up to 122us (or a bit more due to rounding of the update value).
 * For quick reads one after the other the drift which is up to 30.5us which is practically the expected granularity,
 * which means no precision is lost, but with no waiting for the RSF/SHPF for the calling thread.
 * The buffers are initialized in sys_time_init().
 */
static sys_time_t buffer_time = {0, 0, 0, 0, 0};
static sys_date_t buffer_date = {0, 0, 0, DATETIME_DOW_INVALID};

static RTC_HandleTypeDef fs_hrtc;
static osMutexId_t fs_lock = NULL;


static bool sys_time_set_stamp_raw(const sys_date_t* const p_date, const sys_time_t* const p_time);
static bool sys_time_get_stamp_check_isr_flags(sys_date_t* const p_date, sys_time_t* const p_time);


bool sys_time_retrieve_rtc_calib_settings(sys_time_rtc_calib_settings_t* const p_calib_settings)
{
    bool res = false;

    if (NULL != p_calib_settings)
    {
        rtc_calib_data_t nvm_calib_settings;

        Nvm_GetBlockById(NVM_BLOCK_RTC_CALIB_DATA, &nvm_calib_settings);
        p_calib_settings->calm = nvm_calib_settings.calm;
        p_calib_settings->calp = nvm_calib_settings.calp;

        res = true;
    }

    return res;
}


bool sys_time_update_rtc_calib_settings(const sys_time_rtc_calib_settings_t * const p_calib_settings)
{
    bool res = false;

    if (NULL != p_calib_settings)
    {
        rtc_calib_data_t nvm_calib_settings =
        {
            .calm = p_calib_settings->calm,
            .calp = p_calib_settings->calp
        };

        Nvm_SetBlockById(NVM_BLOCK_RTC_CALIB_DATA, &nvm_calib_settings, NVMSETBLOCK_STORE_IMMEDIATELY);

        res = true;
    }

    return res;
}


bool sys_time_apply_rtc_calib(void)
{
    rtc_calib_data_t rtc_calib_data;
    bool res = false;

    Nvm_GetBlockById(NVM_BLOCK_RTC_CALIB_DATA, &rtc_calib_data);

    if ((NULL != fs_lock) &&
        (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIME)))
    {
        if (HAL_OK == HAL_RTCEx_SetSmoothCalib(
                &fs_hrtc,
                RTC_SMOOTHCALIB_PERIOD_32SEC,
                (rtc_calib_data.calp == TIME_CALP_PULSES_SET ?
                        RTC_SMOOTHCALIB_PLUSPULSES_SET :
                        RTC_SMOOTHCALIB_PLUSPULSES_RESET),
                rtc_calib_data.calm))
        {
            res = true;
        }
        else
        {
            ES_TRACE_DEBUG("[TIME] failed RTC calibration\r\n");
        }

        (void)osMutexRelease(fs_lock);
    }

    return res;
}


/**
 * Initialize sys_time module.
 * Serious consideration should be taken when changing any of the code in this function.
 * Read RM0433 8. and 46.
 * Read STM32H753xI Errata sheet.
 */
bool sys_time_init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    fs_hrtc.Instance            = RTC;
    fs_hrtc.Init.HourFormat     = RTC_HOURFORMAT_24;
    fs_hrtc.Init.AsynchPrediv   = CONFIG_PREDIV_A_VALUE;
    fs_hrtc.Init.SynchPrediv    = CONFIG_PREDIV_S_VALUE;
    fs_hrtc.Init.OutPut         = RTC_OUTPUT_DISABLE;
    fs_hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    fs_hrtc.Init.OutPutType     = RTC_OUTPUT_TYPE_OPENDRAIN;
    fs_hrtc.Init.OutPutRemap    = RTC_OUTPUT_REMAP_POS1;

    if (HAL_OK != HAL_RTC_Init(&fs_hrtc))
    {
        ES_TRACE_DEBUG("[TIME] failed rtc init\r\n");
        return false;
    }

    // Additional initializations that are not covered in HAL_RTC_INIT()
    __HAL_RTC_WRITEPROTECTION_DISABLE(&fs_hrtc);
    if (HAL_OK != RTC_EnterInitMode(&fs_hrtc))
    {
        __HAL_RTC_WRITEPROTECTION_ENABLE(&fs_hrtc);
        ES_TRACE_DEBUG("[TIME] failed rtc init\r\n");
        return false;
    }

    // Clear BYPSHAD bit. There is no need to read the calendar registers directly,
    // as APB frequency is high enough. With shadow registers enabled, reading is much faster.
    // Synchronization timeout is mitigated by a software calendar buffer, that is updated
    // after each successful read from the RTC calendar registers.
    LL_RTC_DisableShadowRegBypass(fs_hrtc.Instance);

    // Clear REFCKON bit. If this bit is set, it is not possible to update SSR.
    // See RM0433 46.3.11, the second "Caution:" note at the end.
    LL_RTC_DisableRefClock(fs_hrtc.Instance);

    if (HAL_OK != RTC_ExitInitMode(&fs_hrtc))
    {
        __HAL_RTC_WRITEPROTECTION_ENABLE(&fs_hrtc);
        ES_TRACE_DEBUG("[TIME] failed rtc init\r\n");
        return false;
    }

    __HAL_RTC_WRITEPROTECTION_ENABLE(&fs_hrtc);

    osMutexAttr_t lock_attr =
    {
        .name      = "sys_time_loc",
        .attr_bits = osMutexRecursive | osMutexPrioInherit,
        .cb_mem    = NULL,
        .cb_size   = 0U
    };

    fs_lock = osMutexNew(&lock_attr);
    if (NULL == fs_lock)
    {
        ES_TRACE_DEBUG("[TIME] failed creating mutex\r\n");
        return false;
    }

    // Initialize buffer date and time
    if (false == sys_time_get_stamp(&buffer_date, &buffer_time))
    {
        ES_TRACE_DEBUG("[TIME] could not initialize time buffer\r\n");
    }

    (void)sys_time_apply_rtc_calib();

    return true;
}


bool sys_time_en_calib_out(TIME_cal_freq_t mode)
{
    bool res = false;
    HAL_StatusTypeDef ret_code = HAL_OK;
    GPIO_InitTypeDef gpio = {0};

    if ((NULL != fs_lock) &&
        (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIME)))
    {
        drv_led_deinit();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        gpio.Pin       = GPIO_PIN_2;
        gpio.Mode      = GPIO_MODE_AF_PP;
        gpio.Pull      = GPIO_NOPULL;
        gpio.Speed     = GPIO_SPEED_FREQ_LOW;
        gpio.Alternate = GPIO_AF0_RTC_50Hz;
        HAL_GPIO_Init(GPIOB, &gpio);

        switch (mode)
        {
            case TIME_CAL_FREQ_F001HZ:
            {
                ret_code = HAL_RTCEx_SetCalibrationOutPut(&fs_hrtc, RTC_CALIBOUTPUT_1HZ);
            } break;
            case TIME_CAL_FREQ_F512HZ:
            default:
            {
                ret_code = HAL_RTCEx_SetCalibrationOutPut(&fs_hrtc, RTC_CALIBOUTPUT_512HZ);
            } break;
        }

        if (HAL_OK == ret_code)
        {
            res = true;
        }
        else
        {
            ES_TRACE_DEBUG("[TIME] failed rtc init calibration output\r\n");
        }

        (void)osMutexRelease(fs_lock);
    }

    return res;
}


bool sys_time_get(sys_time_t* const p_time)
{
    sys_date_t ignore_date;
    return sys_time_get_stamp(&ignore_date, p_time);
}


bool sys_time_set(const sys_time_t* const p_new_time)
{
    bool res;
    sys_time_t ignore_time;
    sys_date_t current_date = {2000, 1, 1, DATETIME_DOW_INVALID};

    sys_time_get_stamp(&current_date, &ignore_time);

    res = sys_time_set_stamp(&current_date, p_new_time, FS_LOCK_TIME);

    return res;
}


bool sys_time_get_date(sys_date_t* const p_date)
{
    sys_time_t ignore_time;
    return sys_time_get_stamp(p_date, &ignore_time);
}


bool sys_time_set_date(const sys_date_t* const p_new_date)
{
    bool res;
    sys_time_t current_time = {0,0,0,0,0};
    sys_date_t ignore_date;

    sys_time_get_stamp(&ignore_date, &current_time);

    res = sys_time_set_stamp(p_new_date, &current_time, FS_LOCK_TIME);

    return res;
}


/**
 * @brief Internal function. Read the TR,DR and SSR registers and stores them in p_date and p_time.
 *        To be called only after  sanity checks have been made for the input parameters
 *        and the hardware conditions required for proper reading of the registers.
 *        p_date and p_time are updated only after successful reading.
 *
 * @param[out] p_date Pointer to a date structure to be filled by the data in the DR register
 * @param[out] p_time Pointer to a time structure to be filled by the data in the TR and SSR registers
 *
 * @return `true` on success, `false` otherwise
 */
static bool sys_time_get_stamp_raw(sys_date_t* const p_date, sys_time_t* const p_time)
{
    RTC_TimeTypeDef temp_rtc_time;
    RTC_DateTypeDef temp_rtc_date;
    sys_time_t temp_time;
    sys_date_t temp_date;

    // Reading of the calendar registers must start with SSR which is done in HAL_RTC_GetTime
    if (HAL_OK != HAL_RTC_GetTime(&fs_hrtc, &temp_rtc_time, FS_FORMAT))
    {
        return false;
    }

    if (HAL_OK != HAL_RTC_GetDate(&fs_hrtc, &temp_rtc_date, FS_FORMAT))
    {
        return false;
    }

    // According to RM0433 46.3.9 (third paragraph), the RSF bit must be cleared by software
    // in case of quick successive readings of the calendar registers (DR,TR and SSR).
    // We cannot exclude that this won't be the case, ase this function is called from many threads
    // and close successive calls are inevitable at times.
    LL_RTC_DisableWriteProtection(fs_hrtc.Instance);
    LL_RTC_ClearFlag_RS(fs_hrtc.Instance);
    LL_RTC_EnableWriteProtection(fs_hrtc.Instance);

    temp_date.year = temp_rtc_date.Year + FS_YEAR_OFFSET;
    temp_date.mon  = temp_rtc_date.Month;
    temp_date.day  = temp_rtc_date.Date;
    temp_date.wday = temp_rtc_date.WeekDay;

    temp_time.hour = temp_rtc_time.Hours;
    temp_time.min  = temp_rtc_time.Minutes;
    temp_time.sec  = temp_rtc_time.Seconds;


    // The .SubSeconds value is equal to SSR register.
    // .SubSeconds is normally less or equal to .SecondFraction
    // unless an update to the SSR has been recently done recently.
    // Than it can be equal up to 2*PREDIV_S, otherwise something weird is happening.
    // See sys_time_set_stamp_raw() for details.
    if (temp_rtc_time.SecondFraction < temp_rtc_time.SubSeconds)
    {
        temp_rtc_time.SubSeconds -= temp_rtc_time.SecondFraction;

        if (temp_rtc_time.SecondFraction < temp_rtc_time.SubSeconds)
        {
            ES_TRACE_DEBUG("[TIME] Unexpected value for .SecondFraction(SSR), greater than 2*PREDIV_S\r\n");
            return false;
        }

        temp_time.ms = 0;
        temp_time.us = 0;
        if (false == datetime_decrement_timestamp(&temp_date, &temp_time))
        {
            return false;
        }
    }

    double us;
    us = (1e6*(temp_rtc_time.SecondFraction - temp_rtc_time.SubSeconds))/(double)(temp_rtc_time.SecondFraction + 1);
    temp_time.ms = (uint16_t)(us * .001);
    temp_time.us = (uint16_t)(((uint32_t)us) % 1000);

    if ((false == datetime_is_valid_date(&temp_date)) ||
        (false == datetime_is_valid_time(&temp_time)))
    {
        return false;
    }

    // Update calendar buffers, so time can be read without RSF timeout
    buffer_time = temp_time;
    buffer_date = temp_date;

    // We guarantee that the input structures won't be changed in case of error
    *p_time = temp_time;
    *p_date = temp_date;

    return true;
}


bool sys_time_get_stamp(sys_date_t* const p_date, sys_time_t* const p_time)
{
    bool res = false;

    if ((NULL != p_date) &&
        (NULL != p_time) &&
        (NULL != fs_lock) &&
        (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIME)))
    {
        res = sys_time_get_stamp_check_isr_flags(p_date, p_time);

        (void)osMutexRelease(fs_lock);
    }

    return res;
}


bool sys_time_set_stamp(const sys_date_t* const p_date, const sys_time_t* const p_time, uint32_t timeout)
{
    bool res = false;

    if ((NULL != p_date) &&
        (NULL != p_time) &&
        (NULL != fs_lock) &&
        (true == datetime_is_valid_time(p_time)) &&
        (true == datetime_is_valid_date(p_date)) &&
        (osOK == osMutexAcquire(fs_lock, timeout)))
    {
        res = sys_time_set_stamp_raw(p_date, p_time);

        (void)osMutexRelease(fs_lock);
    }

    return res;
}


/**
 * @brief Internal function. It is intermediate and should be called only by sys_time_get_stamp()
 *        after sanity checks and the mutex guard.
 *        This function checks for the status flags in ISR (RTC) to indicate that
 *        calendar registers are ready for reading.
 *        If the synchronization flag or the pending shift flag are not ready, the last successful read is returned.
 *
 * @param[out] p_date Pointer to a date structure to be filled by the data in the DR register
 * @param[out] p_time Pointer to a time structure to be filled by the data in the TR and SSR registers
 *
 * @return `true` on success, `false` otherwise
 */
static bool sys_time_get_stamp_check_isr_flags(sys_date_t* const p_date, sys_time_t* const p_time)
{
    bool ret = false;

    if ((false == LL_RTC_IsActiveFlag_RS(fs_hrtc.Instance)) ||
        (true == LL_RTC_IsActiveFlag_SHP(fs_hrtc.Instance)))
    {
        if ((true == datetime_is_valid_date(&buffer_date)) &&
            (true == datetime_is_valid_time(&buffer_time)))
        {
            *p_date = buffer_date;
            *p_time = buffer_time;

            ret = true;
        }
    }
    else
    {
        ret = sys_time_get_stamp_raw(p_date, p_time);
    }

    return ret;
}


/**
 * @brief Waits for a number of loops for the RSF to get set by hardware.
 *        See explanation above declaration of MAX_LOOP_RSF.
 *        See RM0433 46.3.8, 46.3.9 and 46.6.4(ISR).
 *        Optimizations are turned off to avoid any compiler optimizations.
 *
 * @return `true` on success, `false` otherwise
 */
__attribute__((optimize(0)))
static bool sys_time_wait_rsf(void)
{
    for (uint32_t loop = 0; MAX_LOOP_RSF > loop; loop++)
    {
        if (true == LL_RTC_IsActiveFlag_RS(fs_hrtc.Instance))
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Sets calendar time in the RTC registers. This function is without mutex guards or sanity checks.
 *        It should be called only internally by sys_time_set_stamp() which makes all the sanity checks
 *        and uses a mutex guard
 *
 * @param[in] p_date The new date to be set in the DR register
 * @param[in] p_time The new time of day to be set in the TR and SSR registers
 *
 * @return `true` on success, `false` otherwise
 */
static bool sys_time_set_stamp_raw(const sys_date_t* const p_date, const sys_time_t* const p_time)
{
    bool res = false;
    uint32_t fraction;
    uint32_t shift;

    CRIT_ASSERT(NULL != p_date);
    CRIT_ASSERT(NULL != p_time);

    fraction = LL_RTC_GetSynchPrescaler(fs_hrtc.Instance);
    CRIT_ASSERT(CONFIG_PREDIV_S_VALUE == fraction);

    shift = fraction - (uint32_t)((p_time->ms*1e3 + p_time->us)*(double)(fraction + 1)/1e6);
    CRIT_ASSERT(fraction >= shift);

    LL_RTC_DisableWriteProtection(fs_hrtc.Instance);

    // Entering init mode stops updating of the calendar registers from hardware, so they can be written to
    if (ERROR != LL_RTC_EnterInitMode(fs_hrtc.Instance))
    {
        // When TR is written, SSR is internally reset to a value equal to PREDIV_S
        // Any writing to SHIFTR will make SSR greater than PREDIV_S
        // Thus any calculation made when SSR is greater than PREDIV_S should subtract
        // PREDIV_S from SSR and decrement the value read from TR by 1 second (and DR in case of underflow)
        // For more detail see RM0433, sections 46.3.8-11 and 46.6.1-5,10,11

        // Write TR
        LL_RTC_TIME_Config(
                fs_hrtc.Instance,
                LL_RTC_TIME_FORMAT_AM_OR_24,
                __LL_RTC_CONVERT_BIN2BCD(p_time->hour),
                __LL_RTC_CONVERT_BIN2BCD(p_time->min),
                __LL_RTC_CONVERT_BIN2BCD(p_time->sec));

        // Write DR
        LL_RTC_DATE_Config(
                fs_hrtc.Instance, datetime_wday(p_date),
                __LL_RTC_CONVERT_BIN2BCD(p_date->day),
                __LL_RTC_CONVERT_BIN2BCD(p_date->mon),
                __LL_RTC_CONVERT_BIN2BCD(p_date->year - FS_YEAR_OFFSET));

        // Write SHIFTR, which in turn increments ("moves back" in time) the SSR
        LL_RTC_TIME_Synchronize(fs_hrtc.Instance, LL_RTC_SHIFT_SECOND_ADVANCE, shift);
        LL_RTC_ExitInitMode(fs_hrtc.Instance);

        // Update the calendar buffers, which allows reading without timeout for RSF bit
        buffer_time = *p_time;
        buffer_date = *p_date;

        // Synchronization after init. See STM32H753xI Errata sheet, 2.19.3
        sys_time_wait_rsf();
        res = true;
    }

    LL_RTC_EnableWriteProtection(fs_hrtc.Instance);

    return res;
}


/**
 * @brief RTC hardware init. Overrides HAL function.
 */
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
    RCC_PeriphCLKInitTypeDef periph_clk = { 0 };
    RCC_OscInitTypeDef rcc_clk = { 0 };

    if ((RTC == fs_hrtc.Instance) && (RTC == hrtc->Instance))
    {
        HAL_RCC_GetOscConfig(&rcc_clk);

        periph_clk.PeriphClockSelection = RCC_PERIPHCLK_RTC;

        if ((RCC_LSE_ON == rcc_clk.LSEState) &&
            (0U != __HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY)))
        {
            ES_TRACE_DEBUG("RTC clock setting = [LSE]\r");
            periph_clk.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
        }
        else if ((RCC_LSI_ON == rcc_clk.LSIState) &&
                 (0U != __HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY)))
        {
            ES_TRACE_DEBUG("RTC clock setting = [LSI]\r");
            periph_clk.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
        }
        else
        {
            ES_TRACE_DEBUG("RTC clock setting = [???]\r");
            return;
        }

        if (HAL_OK != HAL_RCCEx_PeriphCLKConfig(&periph_clk))
        {
            ES_TRACE_DEBUG(
                "!!! RTC LSE config failure... "
                "switching over to RTC LSI (internal oscillator)... !!!\r");

            periph_clk.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;

            if (HAL_OK != HAL_RCCEx_PeriphCLKConfig(&periph_clk))
            {
                ES_TRACE_DEBUG("!!! RTC clock setting failure !!!\r");
                Error_Handler();
            }
            else
            {
                ES_TRACE_DEBUG("RTC clock setting = [LSI]\r");
            }
        }

        __HAL_RCC_RTC_ENABLE();
    }
}


/**
 * @brief RTC hardware deinit. Overrides HAL function.
 */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
    if ((RTC == fs_hrtc.Instance) && (RTC == hrtc->Instance))
    {
        __HAL_RCC_RTC_DISABLE();
    }
}

bool sys_time_get_rtc_clock_source(sys_time_rtc_clock_info_t* info)
{
    bool ret = false;
    if (NULL != info)
    {
        info->enabled = (0 != LL_RCC_IsEnabledRTC());

        uint32_t rtc_clock_source = LL_RCC_GetRTCClockSource();
        if (LL_RCC_RTC_CLKSOURCE_NONE == rtc_clock_source)
        {
            info->source_osc = SYS_TIME_OSC_NONE;
        }
        else if (LL_RCC_RTC_CLKSOURCE_LSE == rtc_clock_source)
        {
            info->source_osc = SYS_TIME_OSC_LSE;
        }
        else if (LL_RCC_RTC_CLKSOURCE_LSI == rtc_clock_source)
        {
            info->source_osc = SYS_TIME_OSC_LSI;
        }
        else if (LL_RCC_RTC_CLKSOURCE_HSE == rtc_clock_source)
        {
            info->source_osc = SYS_TIME_OSC_HSE;
        }
        else
        {
            info->source_osc = SYS_TIME_OSC_UNKNOWN;
        }

        info->rtc_asynchronous_prescaler = (uint8_t)LL_RTC_GetAsynchPrescaler(fs_hrtc.Instance);
        info->rtc_synchronous_prescaler = (uint16_t)LL_RTC_GetSynchPrescaler(fs_hrtc.Instance);
        info->hse_division_factor = (uint8_t)(LL_RCC_GetRTC_HSEPrescaler()>>RCC_CFGR_RTCPRE_Pos);

        ret = true;
    }
    return ret;
}
