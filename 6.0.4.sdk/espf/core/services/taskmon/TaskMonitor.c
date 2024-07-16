/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup taskmon
 * @{
 *
 * @file    TaskMonitor.c
 * @brief   Monitors if all task are running.
 *
 * @}
 *
 */

#include "TaskMonitor.h"          /* Include own header file */
#include "es_exeh.h"
#include "trace.h"
#include "datacache.h"
#include "timer.h"
#include "drv_iwdg.h"
#include "arm_fault_handler.h"
#include "assertions.h"

#define timer_is_running(timer_hnd)          IS_TRUE((timer_hnd).is_running)

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
/* Period in ms at witch the watchdog timer will be refreshed: see hwwdg.Init.Window 7ms min, 10 is with 50% reserve */
#define TASK_MONITOR_REFRESH_WDG_PERIOD          (100)

// WD periodic activity check timeout in milliseconds
#define TASK_MONITOR_TASK_CHECK_PERIOD_MS        (10U * 60U * 1000U)         // 10 min

/** @brief Time interval (in ms) for reporting free RTOS heap size to the trace console */
#define HEAP_FREE_TRACE_INTERVAL_MS              (60000)

#define TASK_MONITOR_LOW_MEMORY_STACK_PER_TASK   (50)
#define TASK_MONITOR_LOW_MEMORY_TOTAL_HEAP       (1024)

#define EXEH_CURRENT_MODULE_ID                   (eEXEHModuleID_TASK_MONITOR)

// number of tasks after which the stack size usage is reported to DataCache
#define DC_TASK_STATS_REPORT_PERIOD_CNTR         (30U)
/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/
// Used instead of a bool to increase the Hamming distance between the Inactive and Active state
// Therefore unexpected bit-flips could not easily go from Inactive to Active state and trigger
// a reset
typedef enum
{
    ECOUNTDOWN_INACTIVE = 0,
    ECOUNTDOWN_ACTIVE = 0xFF
} eResetCountdownActivationFlags_t;

typedef struct
{
    uint32_t u32MsUntilReset;
    eResetCountdownActivationFlags_t eDelayedResetCountdownActive;
} sDelayedResetCtx_t;

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/
/* No External variables definition */

/**
* @brief Variable description
*/


/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
static uint8_t      TaskMonitor_RunCounter[TASK_MONITOR_TASKS_NUMBER];
static uint8_t      TaskMonitor_InitComplete[TASK_MONITOR_TASKS_NUMBER];
static uint16_t     Task_UnusedStackSize[TASK_MONITOR_TASKS_NUMBER];
static uint8_t      task_mon_policy_list[TASK_MONITOR_TASKS_NUMBER];

static sDelayedResetCtx_t sDelayedResetData =
{
    .u32MsUntilReset = 0U,
    .eDelayedResetCountdownActive = ECOUNTDOWN_INACTIVE
};

static osThreadId_t TaskMonitor_TaskHandle;
static const osThreadAttr_t TaskMonitor_attributes = {
    .name = "TaskMonitor_Task",
    .priority = (osPriority_t) osPriorityRealtime,
    .stack_size = 1000
};

static DATA_CACHE_TaskStats_t task_data;
static uint8_t min_task_cnt = 0U;
/** @brief Periodic timer used to trigger task activity checks at runtime.
 */
static timer_handle_t wd_periodic_check_timer_hnd;

/** @brief Periodic timer used to trigger heap free bytes trace */
static timer_handle_t heap_check_timer;

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
static uint8_t TaskMonitor_CheckTasks(void);
static void fs_vManageDelayedReset(const uint32_t u32MsSinceLastCall);
static inline const char * const fs_pcGetResetTypeDesc(const TASK_MONITOR_resetEnum eResetType);

/*
*********************************************************************************************
* EXTERNAL (NON STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
void TaskMonitor_Init(void)
{
    sDelayedResetData.eDelayedResetCountdownActive = ECOUNTDOWN_INACTIVE;
    sDelayedResetData.u32MsUntilReset = 0U;

    for(uint8_t i = 0; i < TASK_MONITOR_TASKS_NUMBER; i ++ )
    {
        TaskMonitor_RunCounter[i] = 0;
        TaskMonitor_InitComplete[i] = 0;
        task_mon_policy_list[i] = TASK_MON_POLICY_MONITOR;
        Task_UnusedStackSize[i] = -1;
    }

#if (defined(DEBUG_ENABLED) && defined(DEBUG_MODE_WD_ENABLED)) || !defined(DEBUG_ENABLED)
    TaskMonitor_TaskHandle = osThreadNew(TaskMonitor_Task, NULL, &TaskMonitor_attributes);
    CRIT_ASSERT( TaskMonitor_TaskHandle );
#endif

    uint8_t elem_cnt = sizeof(task_data.ai16TaskStackMaxUnusedSize) / sizeof(task_data.ai16TaskStackMaxUnusedSize[0]);

    for (uint8_t j = 0; j < elem_cnt; j++)
    {
        task_data.ai16TaskStackMaxUnusedSize[j] = Task_UnusedStackSize[0U];
    }

    // calculate the minimum number of tasks to report in data cache...
    min_task_cnt = (elem_cnt >= TASK_MONITOR_TASKS_NUMBER) ? (TASK_MONITOR_TASKS_NUMBER) : (elem_cnt);

    timer_stop(&wd_periodic_check_timer_hnd);
    timer_stop(&heap_check_timer);

    EXEH_INIT_MODULE_FILENAME();
}

void TaskMonitor_Task(void * argument)
{
    static uint8_t task_period_cntr = 0U;

    timer_start(&wd_periodic_check_timer_hnd);
    timer_start(&heap_check_timer);

    while (true)
    {
        osDelay(TASK_MONITOR_REFRESH_WDG_PERIOD);
        fs_vManageDelayedReset(TASK_MONITOR_REFRESH_WDG_PERIOD);

        if (timer_is_elapsed(&wd_periodic_check_timer_hnd, TASK_MONITOR_TASK_CHECK_PERIOD_MS))
        {
            volatile uint8_t u8LastTaskChecked = TaskMonitor_CheckTasks();

            // sanity check (if timer is not actually running, timer_is_elapsed() will return true right away;
            // this situation should not happen but if it does, we will not be checking task
            // activity because we may end up with a false positive where some tasks didn't have a
            // chance to report aliveness yet; therefore we just restart the timer hoping that next
            // time what caused it to stop, will not happen again
            if (timer_is_running(wd_periodic_check_timer_hnd))
            {
                if (u8LastTaskChecked == TASK_MONITOR_TASKS_NUMBER)
                {
                	drv_iwdg_refresh();

                    // restart timer
                    timer_start(&wd_periodic_check_timer_hnd);
                }
                else
                {
                    const char * const resetTypeDescr = fs_pcGetResetTypeDesc(TASK_MONITOR_TASK_TIMEOUT);
                    (void) resetTypeDescr;

                    ES_TRACE_DEBUG("%s (tid: %d)\r\n", resetTypeDescr, u8LastTaskChecked);
                    TaskMonitor_ImmediateReset(TASK_MONITOR_TASK_TIMEOUT);
                }
            }

            // restart timer
            timer_start(&wd_periodic_check_timer_hnd);
        }
        else
        {
        	drv_iwdg_refresh();
        }

        TaskMonitor_IamAlive(TASK_MONITOR_TASK);
        vApplicationLowStackCheck(TASK_MONITOR_TASK);

        // simple periodic counter is used because the time value between reports is not
        // critical; we just want to avoid reporting too often
        if (task_period_cntr++ == DC_TASK_STATS_REPORT_PERIOD_CNTR)
        {
            for (uint8_t j = 0; j < min_task_cnt; j++)
            {
                task_data.ai16TaskStackMaxUnusedSize[j] = Task_UnusedStackSize[j];
            }

            dc_set_os_task_data(&task_data);

            task_period_cntr = 0U;
        }
#ifdef DEBUG_ENABLED
        vApplicationLowTotalHeapCheck();
#endif
    }
}

void TaskMonitor_IamAlive(TASK_MONITOR_TasksEnum task)
{
    if( task < TASK_MONITOR_TASKS_NUMBER )
    {
        if( TaskMonitor_RunCounter[task] < 0xFE )   /* Prevent from rolling over */
        {
            /* Set the task as alive (run one more time) */
            TaskMonitor_RunCounter[task] ++;
        }
    }
}

void task_mon_set_task_policy(TASK_MONITOR_TasksEnum task, task_mon_policy_t policy)
{
    if( task < TASK_MONITOR_TASKS_NUMBER )
    {
        /* Set the new task policy */
        task_mon_policy_list[task] = policy;
    }
}

void TaskMonitor_TaskInitialized(TASK_MONITOR_TasksEnum task)
{
    if( task < TASK_MONITOR_TASKS_NUMBER )
    {
        TaskMonitor_InitComplete[task] = 1;
    }
}

uint8_t TaskMonitor_CheckTasksInit(void)
{
    uint8_t i;
    uint8_t retVal = 1; /* assume all task has passed at least once */

    for( i = 0; i < TASK_MONITOR_TASKS_NUMBER; i ++ )
    {
        if( TaskMonitor_InitComplete[i] == 0 )
        {
            /* One task is not alive */
            retVal = 0;
            break;
        }
    }

    return retVal;
}

void TaskMonitor_ImmediateReset(TASK_MONITOR_resetEnum ResetType)
{
    (void)ResetType;

    arm_fault_handler_bkpt_if_debug();

    NVIC_SystemReset();
}

void vApplicationLowStackCheck(TASK_MONITOR_TasksEnum taskNumber)
{
    // uxTaskGetStackHighWaterMark returns words, we want bytes (1 word = 4 bytes)
    UBaseType_t uxHighWaterMark_bytes = uxTaskGetStackHighWaterMark( NULL ) * 4;

    if(Task_UnusedStackSize[taskNumber] > (uint16_t)uxHighWaterMark_bytes)
    {
        Task_UnusedStackSize[taskNumber] = (uint16_t)uxHighWaterMark_bytes;
    }

    if(Task_UnusedStackSize[taskNumber] < 2 * TASK_MONITOR_LOW_MEMORY_STACK_PER_TASK)
        EXEH_HANDLE(eEXEHSeverity_Warning, eEXEH_TASK_MONITOR_TASK_STACK_WARN | ((uint32_t) taskNumber << 24U));

    //Minimum stack size over the needed
    if(Task_UnusedStackSize[taskNumber] < TASK_MONITOR_LOW_MEMORY_STACK_PER_TASK)
    {
        Error_Handler();
    }
}

void vApplicationLowTotalHeapCheck(void)
{
    extern uint32_t lnk_freertos_heap_size_bytes;   // linker symbol
    size_t free_heap = xPortGetFreeHeapSize();

    if (timer_is_elapsed(&heap_check_timer, HEAP_FREE_TRACE_INTERVAL_MS))
    {
        ES_TRACE_DEBUG("RTOS heap [free: %lu (%0.2f%%), total: %lu] (bytes)", free_heap, (float) free_heap * 100. / (uint32_t) &lnk_freertos_heap_size_bytes, (uint32_t) &lnk_freertos_heap_size_bytes);
        timer_start(&heap_check_timer);
    }

    BREAK_ASSERT(free_heap >= TASK_MONITOR_LOW_MEMORY_TOTAL_HEAP);
    CRIT_ASSERT(free_heap != 0);
}

void TaskMonitor_TriggerDelayedReset(const uint32_t u32WaitMs)
{
    // order is important since this information is used in the TaskMonitor_Task() and
    // the bDelayedResetCountdownActive flag could be checked before setting the u32MsUntilReset
    // value causing an immediate reset - no protection is needed here since bDelayedResetCountdownActive
    // is read atomically
    sDelayedResetData.u32MsUntilReset = u32WaitMs;
    sDelayedResetData.eDelayedResetCountdownActive = ECOUNTDOWN_ACTIVE;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/**
 * @brief Check if all task are still running, but not stuck
 * @retval 1: All tasks are alive
 * @retval 0: At least one frozen task has been found
 */
static uint8_t TaskMonitor_CheckTasks(void)
{
    uint8_t i;
    uint8_t u8LastTaskChecked = TASK_MONITOR_TASKS_NUMBER; /* assume all task has passed at least once */

    for( i = 0; i < TASK_MONITOR_TASKS_NUMBER; i ++ )
    {
        if(task_mon_policy_list[i] == TASK_MON_POLICY_MONITOR)
        {
            if( TaskMonitor_RunCounter[i] == 0 )
            {
                // report task which was not alive
                u8LastTaskChecked = i;
                break;
            }else{
                TaskMonitor_RunCounter[i] = 0;
            }
        }
    }

    return u8LastTaskChecked;
}

/**
 * @brief Manage the delayed reset mechanism
 * @param u32MsSinceLastCall: milliseconds passed since last call of this function
 *                            in the main task
 */
static void fs_vManageDelayedReset(const uint32_t u32MsSinceLastCall)
{
    if (sDelayedResetData.eDelayedResetCountdownActive == ECOUNTDOWN_ACTIVE)
    {
        if (sDelayedResetData.u32MsUntilReset >= u32MsSinceLastCall)
        {
            sDelayedResetData.u32MsUntilReset -= u32MsSinceLastCall;
        }
        else
            TaskMonitor_ImmediateReset(TASK_MONITOR_USER_DELAYED_RESET);
    }
}
/* **************************************************************************************** */

static inline const char * const fs_pcGetResetTypeDesc(const TASK_MONITOR_resetEnum eResetType)
{
    static const char *cResetTypesDescription[TASK_MONITOR_RESET_NUMBER] =
    {
        "SW_RESET",
        "FAULT_RESET",
        "USER_DELAYED_RESET",
        "TASK_TIMEOUT"
    };

    if (eResetType < TASK_MONITOR_RESET_NUMBER)
        return cResetTypesDescription[(uint8_t) eResetType];
    else
        return "UNKNOWN";
}

#ifdef DEBUG_ENABLED
//
// linker imports
//
extern uint32_t lnk_user_main_stack_size_bytes;		// allocates user stack size
extern uint32_t lnk_user_main_stack_start_addr;		// stack start address
extern uint32_t _estack;							// highest address of user stack

#define USER_STACK_PATTERN 		(0x52)
#define USER_STACK_SIZE 		((uint32_t) &lnk_user_main_stack_size_bytes)
#define USER_STACK_TOP_ADDR 	((uint8_t *) &_estack)
#define USER_STACK_START_ADDR   ((uint8_t *) &lnk_user_main_stack_start_addr)
#define MIN_FREE_SIZE_STACK 	(50)

/** @brief Initializes the main stack buffer with a special value so that the stack growth can be
 *         measured upon startup.
 *
 *  @note The function initializes only the main stack region defined in the linker. RTOS task stacks are
 *        monitored by the RTOS itself.
 *
 *  @warning This function shall be the first to be called in main() so that main stack usage can be
 *           measured. If you call this from a function which must return, the stack will be corrupted!
 */
void vRamTest_StackFill(void)
{
    // memset() not used because this function will be called by the assembly startup code before initializing the C runtime
    for (uint8_t *p_stack_mem_index = USER_STACK_START_ADDR; p_stack_mem_index < USER_STACK_TOP_ADDR; p_stack_mem_index++)
    {
        *p_stack_mem_index = USER_STACK_PATTERN;
    }
}

void vRamTest_StackUsageCheck(void)
{
    const uint8_t * p_stack_mem_index;

    for (p_stack_mem_index = USER_STACK_START_ADDR; p_stack_mem_index < USER_STACK_TOP_ADDR; p_stack_mem_index++)
    {
        if (USER_STACK_PATTERN != *p_stack_mem_index)
        {
            break;
        }
    }

    volatile uint32_t free_stack_bytes = (uint32_t) p_stack_mem_index - (uint32_t) USER_STACK_START_ADDR;

    ES_TRACE_DEBUG("main stack [free: %lu (%0.2f%%)/total: %lu] (bytes)", free_stack_bytes, (float) free_stack_bytes * 100. / USER_STACK_SIZE, USER_STACK_SIZE);

    ES_CDEF_UNUSED(free_stack_bytes);

    BREAK_ASSERT(free_stack_bytes >= MIN_FREE_SIZE_STACK);
    CRIT_ASSERT(0 != free_stack_bytes);
}
#endif
