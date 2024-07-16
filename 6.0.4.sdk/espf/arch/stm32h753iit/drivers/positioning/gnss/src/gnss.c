/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 * Provide an interface for the GNSS communication
 *
 * @file gnss.c
 *
 * @brief GNSS driver
 *
 * @}
 * @}
 */

#include "es_cdef.h"
#include "gnss.h"
#include "gnss_resp.h"
#include "gnss_uart.h"
#include "gnss_power.h"
#include "gnss_defs.h"
#include "timer.h"
#include "cmsis_os2.h"
#include "TaskMonitor.h"
#include "trace.h"
#include "assertions.h"
#include <string.h>

#define GNSS_TRACE_ENABLED (0)

#if GNSS_TRACE_ENABLED
#  define FS_GNSS_TRACE(fmt, ...) ES_TRACE_DEBUG(fmt OPT_VA_ARGS(__VA_ARGS__))
#else
#  define FS_GNSS_TRACE(fmt, ...)
#endif



/** @brief must be implemented by the user */
extern void gnss_config_pv_callback(const gnss_xyz_t* pv);

/** @brief must be implemented by the user */
extern void gnss_config_tm_callback(const gnss_time_t* t);



if_sys_mod_t gnss_module_configuration =
{
    .init   = gnss_init,
    .run    = gnss_run,
    .stop   = gnss_stop,
    .deinit = gnss_deinit,
};



/** @brief mutex that ensures thread safety of operations */
static osMutexId_t fs_lock = NULL;

/** @brief used for reading raw messages from the low level driver */
static gnss_uart_resp_t fs_gnss_raw_resp  = { 0 };

/** @brief init task handle */
static osThreadId_t fs_h_init_task = NULL;

/** @brief response task handle */
static osThreadId_t fs_h_resp_task = NULL;

/** @brief software timer used to mark the time since last successfully received bestxyz log */
static timer_handle_t fs_h_bestxyz_tim;

/** @brief software timer used to mark the time since last successfully received time log */
static timer_handle_t fs_h_time_tim;

/** @brief flag used to keep track of whether the user has instructed us to remain powered off */
static bool fs_external_stop = false;

/** @brief flag used to prevent consecutive power on */
static bool fs_already_on = false;



static mod_op_status_id_t fs_start(const bool external_req);
static mod_op_status_id_t fs_stop(const bool external_req);
static void fs_resp_task_data_rdy_callback(void);
static void fs_init_task(void* args);
static void fs_resp_task(void* args);



mod_op_status_id_t gnss_init(sys_init_level_id_t level)
{
    (void)level;

    mod_op_status_id_t ret = STATUS_OK;

    if (NULL == fs_lock)
    {
        osMutexAttr_t attr =
        {
            .name      = NULL,
            .attr_bits = osMutexRecursive | osMutexPrioInherit,
            .cb_mem    = NULL,
            .cb_size   = 0U
        };

        fs_lock = osMutexNew(&attr);

        if (NULL == fs_lock)
        {
            ret = STATUS_FAILED;
        }
    }

    if ((true == ret) && (NULL == fs_h_init_task))
    {
        osThreadAttr_t attr =
        {
            .attr_bits  = osThreadDetached,
            .name       = "gnss1",
            .priority   = osPriorityNormal,
            .cb_mem     = NULL,
            .cb_size    = 0U,
            .stack_mem  = NULL,
            .stack_size = 2048,
            .tz_module  = 0U,
            .reserved   = 0U
        };

        fs_h_init_task = osThreadNew(fs_init_task, NULL, &attr);

        if (NULL == fs_h_init_task)
        {
            ret = STATUS_FAILED;
        }
    }

    if ((true == ret) && (NULL == fs_h_resp_task))
    {
        osThreadAttr_t attr =
        {
            .attr_bits  = osThreadDetached,
            .name       = "gnss2",
            .priority   = osPriorityNormal,
            .cb_mem     = NULL,
            .cb_size    = 0U,
            .stack_mem  = NULL,
            .stack_size = 2048,
            .tz_module  = 0U,
            .reserved   = 0U
        };

        fs_h_resp_task = osThreadNew(fs_resp_task, NULL, &attr);

        if (NULL == fs_h_resp_task)
        {
            ret = STATUS_FAILED;
        }
    }

    return ret;
}


mod_op_status_id_t gnss_deinit(sys_init_level_id_t level)
{
    (void)level;

    mod_op_status_id_t ret = STATUS_OK;

    task_mon_set_task_policy(TASK_MONITOR_GNSS_INIT, TASK_MON_POLICY_DONT_CARE);
    task_mon_set_task_policy(TASK_MONITOR_GNSS_LISTEN, TASK_MON_POLICY_DONT_CARE);

    return ret;
}


mod_op_status_id_t gnss_run(void)
{
    return fs_start(true);
}


mod_op_status_id_t gnss_stop(void)
{
    return fs_stop(true);
}


bool gnss_is_on(void)
{
    bool res = false;

    if ((NULL != fs_lock) && (osOK == osMutexAcquire(fs_lock, osWaitForever)))
    {
        res = gnss_power_is_on();
        (void)osMutexRelease(fs_lock);
    }

    return res;
}


bool gnss_is_tm_valid(const gnss_time_t* tim)
{
    bool res = false;

    if ((NULL != tim) &&
        // this is a basic check taken from oem719 user manual
        (0 != tim->utc_status) &&
        (0 != tim->utc_month) &&
        (0 != tim->utc_day) &&
        (60000 > tim->utc_ms))
    {
        res = true;
    }

    return res;
}


/**
 * @brief Start GNSS
 *
 * @param[in] external_req If true - request is outside the driver (higher priority)
 *
 * @retVal STATUS_NOT_SUPPORTED
 * @retVal STATUS_FAILED
 * @retVal STATUS_OK
 */
static mod_op_status_id_t fs_start(const bool external_req)
{
    mod_op_status_id_t res = STATUS_NOT_SUPPORTED;

    if ((NULL != fs_h_init_task) && (NULL != fs_lock))
    {
        res = STATUS_FAILED;

        if (osOK == osMutexAcquire(fs_lock, osWaitForever))
        {
            // always turn on if the request is from outside the driver
            // otherwise we 1st check if the user has instructed to remain stopped
            // in such case the device won't be turned on since external requests are
            // with higher priority
            if ((true == external_req) || (false == fs_external_stop))
            {
                // if the GNSS is already on there is no need to start it again
                if (false == fs_already_on)
                {
                    (void)osThreadFlagsSet(fs_h_init_task, GNSS_START_FLAG);
                    gnss_power_on();
                    fs_already_on = true;
                    fs_external_stop = false;
                }

                res = STATUS_OK;
            }

            (void)osMutexRelease(fs_lock);
        }
    }

    return res;
}


/**
 * @brief Stop GNSS
 *
 * @param[in] external_req If true - request is outside the driver (higher priority)
 *
 * @retVal STATUS_NOT_SUPPORTED
 * @retVal STATUS_FAILED
 * @retVal STATUS_OK
 */
static mod_op_status_id_t fs_stop(const bool external_req)
{
    mod_op_status_id_t res = STATUS_NOT_SUPPORTED;

    if (NULL != fs_lock)
    {
        res = STATUS_FAILED;

        if (osOK == osMutexAcquire(fs_lock, osWaitForever))
        {
            // cut the power
            gnss_power_off();

            if (true == external_req)
            {
                fs_external_stop = external_req;
            }

            fs_already_on = false;

            (void)osMutexRelease(fs_lock);

            res = STATUS_OK;
        }
    }

    return res;
}


/**
 * @brief Notifies the thread about received data from the low level driver
 */
static void fs_resp_task_data_rdy_callback(void)
{
    CRIT_ASSERT(NULL != fs_h_resp_task);

    if (NULL != fs_h_resp_task)
    {
        (void)osThreadFlagsSet(fs_h_resp_task, GNSS_DATA_FLAG);
    }
}


/**
 * @brief Safely reset timer
 *
 * @param[in] p_handle Timer handle
 */
static void fs_response_timer_reset(timer_handle_t* const p_handle)
{
    if (osOK == osMutexAcquire(fs_lock, osWaitForever))
    {
        timer_start(p_handle);
        (void)osMutexRelease(fs_lock);
    }
}


/**
 * @brief Check if timer is elapsed
 *
 * @param[in] p_handle Timer handle
 *
 * @retVal true  Timer is elapsed
 * @retVal false Timer is not elapsed
 */
static bool fs_response_timer_elapsed(timer_handle_t* const p_handle)
{
    bool res = false;

    if (osOK == osMutexAcquire(fs_lock, osWaitForever))
    {
        res = timer_is_elapsed(p_handle, GNSS_NO_RESPONSE_TIMEOUT_MS);
        (void)osMutexRelease(fs_lock);
    }

    return res;
}


/**
 * @brief Performs full device power cycle
 */
static void fs_power_cycle(void)
{
    // stop communication on OBC side
    (void)gnss_uart_deinit();

    // shutdown gnss
    (void)fs_stop(false);

    // give time to gnss to shutdown properly
    osDelay(1000);

    // start gnss
    // this will only succeed if the user has not forced a shutdown
    (void)fs_start(false);
}


/**
 * @brief Task that prepares GNSS/OBC for timed logging
 *
 * @param[in] args Not used
 */
NO_RETURN static void fs_init_task(void* args)
{
    (void)args;

    TaskMonitor_TaskInitialized(TASK_MONITOR_GNSS_INIT);

    task_mon_set_task_policy(TASK_MONITOR_GNSS_INIT, TASK_MON_POLICY_MONITOR);

    while (1)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_GNSS_INIT);

        uint32_t flags = osThreadFlagsWait(GNSS_START_FLAG, osFlagsWaitAny, 10000);

        // execute only if START has been requested
        if (GNSS_START_FLAG == flags)
        {
            // restart the response timers
            // prevents expiration while we are initialising the GNSS
            fs_response_timer_reset(&fs_h_bestxyz_tim);
            fs_response_timer_reset(&fs_h_time_tim);

            // stop communication on OBC side
            (void)gnss_uart_deinit();

            // wait for boot ready
            osDelay(GNSS_BOOT_TIMEOUT_MS);

            bool status = gnss_uart_init(GNSS_DEFAULT_BAUDRATE);
            osDelay(100);

            if (true == status)
            {
                // stop this log
                (void)gnss_uart_tx((const uint8_t*)GNSS_CMD_UNLOG_RXSTATUSEVENTA, GNSS_STATIC_STRLEN(GNSS_CMD_UNLOG_RXSTATUSEVENTA));
                osDelay(100);
            }

            if (true == status)
            {
                // changing baudrate
                (void)gnss_uart_tx((const uint8_t*)GNSS_CMD_SERIALCONFIG, GNSS_STATIC_STRLEN(GNSS_CMD_SERIALCONFIG));
                osDelay(100);
            }

            if (true == status)
            {
                // stop communication on OBC side
                status = gnss_uart_deinit();
                osDelay(100);
            }

            if (true == status)
            {
                // start communication on OBC side with new baudrate
                status = gnss_uart_init(GNSS_DESIRED_BAUDRATE);
                osDelay(100);
            }

            if (true == status)
            {
                // register BESTXYZ periodic log. send command and wait for response
                (void)gnss_uart_tx((const uint8_t*)GNSS_CMD_LOG_BESTXYZA, GNSS_STATIC_STRLEN(GNSS_CMD_LOG_BESTXYZA));
                osDelay(100);
            }

            if (true == status)
            {
                // register TIME periodic log. send command and wait for response
                (void)gnss_uart_tx((const uint8_t*)GNSS_CMD_LOG_TIMEA, GNSS_STATIC_STRLEN(GNSS_CMD_LOG_TIMEA));
                osDelay(100);
            }

            if (true == status)
            {
                // stop communication on OBC side
                status = gnss_uart_deinit();
                osDelay(100);
            }

            if (true == status)
            {
                // switch to the callback that notifies the handler thread for gnss responses
                status = gnss_uart_reg(fs_resp_task_data_rdy_callback);
            }

            if (true == status)
            {
                // start communication on OBC side with the last selected baudrate
                status = gnss_uart_init(GNSS_DESIRED_BAUDRATE);
                osDelay(100);
            }

            // something failed during startup. restart the device
            if (false == status)
            {
                fs_power_cycle();
            }
        }

        vApplicationLowStackCheck(TASK_MONITOR_GNSS_INIT);
    }
}


/**
 * @brief Task that handles GNSS timed log responses
 *
 * @param[in] args Not used
 */
NO_RETURN static void fs_resp_task(void* args)
{
    (void)args;

    uint32_t flags;
    gnss_ascii_resp_info_t resp_info;
    gnss_time_t gnss_time = { 0 };
    gnss_xyz_t  gnss_xyz = { 0 };

    TaskMonitor_TaskInitialized(TASK_MONITOR_GNSS_LISTEN);
    task_mon_set_task_policy(TASK_MONITOR_GNSS_LISTEN, TASK_MON_POLICY_MONITOR);

    fs_response_timer_reset(&fs_h_bestxyz_tim);
    fs_response_timer_reset(&fs_h_time_tim);

    while (1)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_GNSS_LISTEN);

        flags = osThreadFlagsWait(GNSS_DATA_FLAG, osFlagsWaitAny, 1000);

        // execute when data is received
        if ((0 == (osFlagsError & flags)) &&
            (0 != (GNSS_DATA_FLAG & flags)))
        {
            while ((true == gnss_uart_rx(&fs_gnss_raw_resp)) &&
                   (true == gnss_resp_is_ascii((const char*)fs_gnss_raw_resp.data, fs_gnss_raw_resp.data_sz)) &&
                   (true == gnss_resp_get_ascii_info((const char*)fs_gnss_raw_resp.data, fs_gnss_raw_resp.data_sz, &resp_info)) &&
                   (true == gnss_resp_is_ascii_crc_valid(&resp_info)))
            {
                FS_GNSS_TRACE("%.*s\r\n", resp_info.header_size, resp_info.header_start);

                // is this BESTXYZ log
                if (NULL != strnstr(resp_info.header_start, GNSS_RESP_LOG_BESTXYZA_HDR, resp_info.header_size))
                {
                    // parse ascii response to binary
                    if (true == gnss_resp_parse_ascii_pv(&resp_info, &gnss_xyz))
                    {
                        // invoking user callback
                        gnss_config_pv_callback(&gnss_xyz);

                        // reset response timer
                        fs_response_timer_reset(&fs_h_bestxyz_tim);
                    }
                }
                // is this TIME log
                else if (NULL != strnstr(resp_info.header_start, GNSS_RESP_LOG_TIMEA_HDR, resp_info.header_size))
                {
                    // parse ascii response to binary
                    if (true == gnss_resp_parse_ascii_tm(&resp_info, &gnss_time))
                    {
                        // invoking user callback
                        gnss_config_tm_callback(&gnss_time);

                        // reset response timer
                        fs_response_timer_reset(&fs_h_time_tim);
                    }
                }
                else
                {
                    // we don't expect any other logs
                }
            }
        }

        // if any of the logs has not been received for more than
        // the specified timeout - restart the device.
        if ((true == fs_response_timer_elapsed(&fs_h_bestxyz_tim)) ||
            (true == fs_response_timer_elapsed(&fs_h_time_tim)))
        {
            fs_response_timer_reset(&fs_h_bestxyz_tim);
            fs_response_timer_reset(&fs_h_time_tim);
            fs_power_cycle();
        }

        vApplicationLowStackCheck(TASK_MONITOR_GNSS_LISTEN);
    }
}


