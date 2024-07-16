/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TASKMONITOR_H
#define TASKMONITOR_H

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup taskmon Task Monitor
 * @{
 *
 * The module takes care of the following task supervision activities:
 *  - Periodic monitoring of the tasks
 *  - Task stack size monitoring
 *  - Heap size monitoring
 * Problematic situations detected by Task Monitor service (such as stack and heap usage under a certain
 *  predefined limit or lack of activity reporting from a supervised task) do lead to an immediate system
 *  reset in an attempt to recover normal operation of the system.
 *
 *  ### Example of use
 *  1. Extend the `TASK_MONITOR_TasksEnum` enumerator with your new task
 *  ```C
 *     typedef enum {
 *         // ...
 *         TASK_CRITICAL_TASK_FOO
 *         // ...
 *         TASK_MONITOR_TASKS_NUMBER
 *     } TASK_MONITOR_TasksEnum;
 *  ```
 *  2. Instrument your task function to report certain events to Task Monitor
 *  ```C
 *  #include "TaskMonitor.h"
 *
 *  static void critical_task_foo(void *argument)
 *  {
 *      TaskMonitor_TaskInitialized(TASK_CRITICAL_TASK_FOO);
 *
 *      while (true)
 *      {
 *          // do your task processing here...
 *
 *          // signal TaskMonitor that the task is still operational...
 *          TaskMonitor_IamAlive(TASK_CRITICAL_TASK_FOO);
 *
 *          // this call is optional but recommended to enable stack size limit checking in TaskMonitor for your task
 *          vApplicationLowStackCheck(TASK_CRITICAL_TASK_FOO);
 *      }
 *  }
 *  ```
 *
 * @file    TaskMonitor.h
 * @brief   Header of TaskMonitor.c
 *
 * @}
 * @}
 *
 */

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "main.h"
#include "cmsis_os.h"
#include "taskmon_cfg.h"

/**
 * @brief Init routine for the TaskMonitor component
 */
void TaskMonitor_Init(void);

/**
 * @brief Task routine of the Task monitor
 * @param argument: not used
 */
void TaskMonitor_Task(void * argument);

/**
 * @brief Calling that function from all task listed in TASK_MONITOR_TasksEnum will prevent from watchdog reset
 * @param task: the number of the task according to the TASK_MONITOR_TasksEnum
 */
void TaskMonitor_IamAlive(TASK_MONITOR_TasksEnum task);

/**
 * @brief Set flag that the current task is initialised and ready
 * @param task: the number of the task according to the TASK_MONITOR_TasksEnum
 */
void TaskMonitor_TaskInitialized(TASK_MONITOR_TasksEnum task);

/**
 * @brief Called from the if_sys_mod to start or stop monitoring a task
 * @param task: the number of the task according to the TASK_MONITOR_TasksEnum
 * @param policy: the new task_mon_policy_t to apply
 */
void task_mon_set_task_policy(TASK_MONITOR_TasksEnum task, task_mon_policy_t policy);

/**
 * @brief Check if all tasks are initialised
 * @retval 1: all task are ready
 * @retval 0: at least one task is not ready
 */
uint8_t TaskMonitor_CheckTasksInit(void);

/**
 * @brief Calling that function clauses immediate reset
 * @param ResetType:
 *                  - TASK_MONITOR_SW_RESET: Software reset
 *                  - TASK_MONITOR_WD_RESET: Watchdog reset
 */
void TaskMonitor_ImmediateReset(TASK_MONITOR_resetEnum ResetType);

/**
 * @brief This function is called to check the unused stack for the task it is called from
 */
void vApplicationLowStackCheck(TASK_MONITOR_TasksEnum taskNumber);

/**
 * @brief This function is called to check the unused total heap
 */
void vApplicationLowTotalHeapCheck(void);

/**
 * @brief The function triggers a CPU reset after a specified number of milliseconds
 * @param u32WaitMs: milliseconds to wait before performing a reset
 */
void TaskMonitor_TriggerDelayedReset(const uint32_t u32WaitMs);

#ifdef DEBUG_ENABLED
/**
 * @brief This function will fill up the memory (stack and heap) almost up to the limit. It can be
 *       used to force the reset and recovery of the OBC SDK
 *
 * @note: Only for debug purposes, it is not available in the release version of the SDK
 */
void vRamTest_StackFill(void);

/**
 * @brief Verify that there is still memory available. If not, it calls Error_Handler()
 *
 * @note: Only for debug purposes, it is not available in the release version of the SDK
 */
void vRamTest_StackUsageCheck(void);
#endif

#endif    /* TASKMONITOR_H */
