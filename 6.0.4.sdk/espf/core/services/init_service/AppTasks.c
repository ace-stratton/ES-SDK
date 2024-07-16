/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "AppTasks.h"
#include "TaskMonitor.h"
#include "datacache.h"
#include "conops.h"
#include "nvm_resetcounters.h"
#include "limits.h"
#include "payload_scheduler.h"
#include "drv_led.h"
#include "if_sys_conf.h"
#include "cmsis_os2.h"
#include "arm_fault_handler.h"
#include "fault_persistor.h"
#include "datetime.h"
#include "SdMngr.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
#define APP_LED_ON_TIME      (5)                      /**< Given time in ms */
#define APP_TASK_CALL_PERIOD (1000 - APP_LED_ON_TIME) /**< Period for the aplication task */
#define UPTIME_RESOLUTION_1S (1000)                   /**< Used to convert kernel ticks to seconds */

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
static osThreadId_t         StartAppTask_TaskHandle;
static const osThreadAttr_t StartAppTask_attributes = {
    .name       = "StartAppTask",
    .priority   = (osPriority_t)osPriorityNormal,
    .stack_size = 2500
};

/**
 * @brief Time in seconds since last reset
 */
static uint32_t uptime_seconds = 0;

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
static void app_task(void *argument);
static void apptask_update_obc_data(void);
static void update_uptime(void);

/*
*********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void AppTask_Init(void)
{
    StartAppTask_TaskHandle =
        osThreadNew(app_task, NULL, &StartAppTask_attributes);
    CRIT_ASSERT(StartAppTask_TaskHandle);
}

uint32_t get_uptime_seconds(void)
{
    return uptime_seconds;
}

/**
 * @brief Task function of the application task
 */
static void app_task(void *argument)
{
    arm_fault_handler_env_t env_data = {
        .rtc_time = 0U,
        .uptime   = 0U
    };

    static bool exceptions_persisted_to_file = false;

    datetime_stamp_t timestamp_now;

    (void)memset(&timestamp_now, 0U, sizeof(datetime_stamp_t));

    TaskMonitor_TaskInitialized(TASK_MONITOR_APP_TASK); /* The task is initialized and is ready */

    for (;;)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_APP_TASK); /* Prevent from WatchDog reset */

        if (false != sys_conf_is_valid())
        {
            /* blink the Green LED for 50ms to indicate the OBC is running */
            drv_led_set(DRV_LED_ID_GREEN, DRV_LED_STATE_ON);
            osDelay(APP_LED_ON_TIME);
            drv_led_set(DRV_LED_ID_GREEN, DRV_LED_STATE_OFF);
        }
        else
        {
            /* blink the amber LED to indicate there is an error in the configuration validation */
            drv_led_set(DRV_LED_ID_AMBER, DRV_LED_STATE_ON);
            osDelay(APP_LED_ON_TIME);
            drv_led_set(DRV_LED_ID_AMBER, DRV_LED_STATE_OFF);
        }

        // update general DataCache entries...
        apptask_update_obc_data();

        // update fault context
        datetime_now(&timestamp_now);

        env_data.uptime   = osKernelGetTickCount();
        env_data.rtc_time = (uint32_t)datetime_to_unix(&timestamp_now);
        arm_fault_handler_set_env(&env_data);

        if ((SdMngr_GetCardState() == SDMNGR_CARD_STATE_READY) && (!exceptions_persisted_to_file))
        {
            fault_persistor_dump_to_file("fault.dmp");
            exceptions_persisted_to_file = true;
        }

        osDelay(APP_TASK_CALL_PERIOD); /* Give processing time for the other tasks */

        update_uptime(); /* this is done after the delay to avoid incrementing the counter to 1 on first execution of the task */

        vApplicationLowStackCheck(TASK_MONITOR_APP_TASK);
    }
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
/**
 * @brief Updates DataCache with some general OBC data
 */
static void apptask_update_obc_data(void)
{
    DATA_CACHE_OBC_0_t obc_data;

    conops_get_hsm_active_state(&obc_data.u8OpMode);
    obc_data.u32UpTime = get_uptime_seconds();

    // to avoid potential unaligned memory access, we use a stack variable to get the value and then assign it
    // to obc_data entry
    uint16_t u16ResetReasonBitField = 0U;
    uint32_t total_reset_count      = NvmResetCounters_GetTotalCount(&u16ResetReasonBitField);
    obc_data.u16ResetReasonBitField = u16ResetReasonBitField;

    obc_data.u16TotalResetCount = (total_reset_count <= UINT16_MAX) ? ((uint16_t)total_reset_count) : (UINT16_MAX);

    obc_data.u16PayloadModesStatus = 0U;

    // TODO: Data Transfer mode still in discussion and no status available at the moment

    dc_set_obc_0_data(&obc_data);
}

/**
 * @brief Calculates the increment of the uptime counter based on task period
 */
static void update_uptime(void)
{
    static uint16_t delayPeriod = 0;

    delayPeriod += SERVICE_TASK_PERIOD;

    while (delayPeriod >= UPTIME_RESOLUTION_1S)
    {
        uptime_seconds++;

        if (delayPeriod >= UPTIME_RESOLUTION_1S)
        {
            delayPeriod -= UPTIME_RESOLUTION_1S; /* - 1 second */
        }
    }
}

/********************************************************************************************* */
