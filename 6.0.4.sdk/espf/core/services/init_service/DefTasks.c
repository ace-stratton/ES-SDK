/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "es_cdef.h"
#include "AppTasks.h"
#include "TaskMonitor.h"
#include "CommandsApi.h"
#include "SdMngr.h"
#include "trace.h"
#include "if_sys_conf.h"
#include "datetime.h"
#include "sensor_data_service.h"

#ifdef COMM_RS485_MAC_LAYER_ENABLED
#include "ESSA_Stack_Facade.h"
#endif

#if defined(BEACONS_ENABLED)
#include "beacons.h"
#endif

#include "actuator_control_service.h"

/*
********************************************************************************************
* INTERNAL DEFINES
********************************************************************************************
*/
#define APP_LED_ON_TIME (50) /* given time in ms */

/*
********************************************************************************************
* INTERNAL TYPES DEFINITION
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
********************************************************************************************
*/

/*
********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
********************************************************************************************
*/
static uint32_t ServicesTask_RTC_StartTime;

static osThreadId_t         ServicesTask_TaskHandle;
static const osThreadAttr_t ServicesTask_attributes = {
    .name       = "ServicesTask",
    .priority   = (osPriority_t)osPriorityNormal,
    .stack_size = 3000U
};

/*
********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
********************************************************************************************
*/
static void InitCompleted(void);
static void ServicesTask(void *argument);

/*
********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
********************************************************************************************
*/
/*!
*********************************************************************************************
* @brief Init routine for the DefTasks component
*********************************************************************************************
* @param[input]      none
* @param[output]     none
* @return            none
* @note              none
*********************************************************************************************
*/
void ServicesTask_Init(void)
{
    ServicesTask_RTC_StartTime = datetime_to_unix_now();

    ServicesTask_TaskHandle = osThreadNew(ServicesTask, NULL, &ServicesTask_attributes);
    CRIT_ASSERT(ServicesTask_TaskHandle);
}

/*!
********************************************************************************************
* @brief Routine utilised by the task, that handles all service operations.
********************************************************************************************
* @param[input]      none
* @param[output]     none
* @return            none
* @note              none
********************************************************************************************
*/
static void ServicesTask(void *argument)
{
    static safe_bool_t esps_started = SAFE_FALSE;

    TaskMonitor_TaskInitialized(TASK_MONITOR_SERVICES); /* The task is initialized and is ready */

    sds_init();

    /* Initialize the service for controlling actuators */
    actuator_control_service_init();

    InitCompleted();

    while (1)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_SERVICES); /* Prevent from WatchDog reset */

        // NOTE:
        // ESPS-related initialization is performed in a task context to ensure the OS is
        // already started when ESPS driver is activated because heavy communication at OBC start
        // could introduce too many interrupts which will prevent the OS to initialize properly
        if (IS_FALSE(esps_started))
        {
            ESSA_Stack_Facade_Init();

#if defined(BEACONS_ENABLED)
            beacons_init();

            beacons_start();
#endif // #if defined(BEACONS_ENABLED)

            esps_started = SAFE_TRUE;
        }

        osDelay(SERVICE_TASK_PERIOD);

        vApplicationLowStackCheck(TASK_MONITOR_SERVICES);
    }
}

void vApplicationIdleHook(void)
{
    // Ram / Rom check
    // Some functions in service task can run here
}

/*
********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
********************************************************************************************
*/
/*!
********************************************************************************************
* @brief Check if all tasks has been initialised and if yes - prints a string once.
********************************************************************************************
* @param[input]      none
* @param[output]     none
* @return            none
* @note              none
********************************************************************************************
*/
static void InitCompleted(void)
{
    static uint8_t complete = 0;

    if ((0 == complete) && (0 != TaskMonitor_CheckTasksInit()))
    {
        ES_TRACE_INFO("OK+OBC initialisation completed\r\n"); /* OBC GUI application needs that string to end or start a operation */
        complete = 1;
    }
}

uint32_t ServicesTask_UptimeSeconds(void)
{
    return (datetime_to_unix_now() - ServicesTask_RTC_StartTime);
}

/* **************************************************************************************** */
