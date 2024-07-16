/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup tp
 * @{
 *
 * @file     ESSA_Stack_TP_Layer.c
 * @brief    TP layer handler definitions
 *
 * @}
 */

#include <esps_drv_config.h>
#include <esps_drv_def.h>
#include "cmsis_os2.h"
#include "stm32h7xx_hal.h"
#include "es_exeh.h"
#include "ESSA_Stack_TP_Layer.h"
#include "ESPLATFORM_NETWORK_STACK/ES_TL_LAYER/ESTL_Drv.h"
#include "CP_Handler.h"
#include "FWUPD_Handler.h"
#include "ESSA_CommonUtils.h"
#include "TaskMonitor.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_ESSA_STACK_TP_LAYER)
#define UNBLOCK_TP_THREAD_FLAG      (1U)

static osThreadId_t MACTL_TaskHandle = NULL;
static ESTL_TL_HostIntf tlIntf;
// This flag indicates if the thread wait procedure has been released by calling ESSA_Stack_TP_Layer_ReleaseThreadWait() before the
// ESSA_Stack_TP_Layer_ThreadWaitForEvent() blocking wait call. In this case, we don't need to block at all.
static bool bThreadAlreadyReleased = false;

static const osThreadAttr_t MACTL_Task_attributes =
{
  .name = "MACTLDrvTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 6500
};

static void MACTL_Task(void *argument);
static void OnESTL_Exception(uint16_t nFileID, uint16_t nLine);
static void OnESTL_Notification(uint16_t nFileID, uint16_t nLine);

static void OnESTL_Exception(uint16_t nFileID, uint16_t nLine)
{
    EXEH_vException(eEXEHSeverity_Error, EXEH_CURRENT_MODULE_ID, nFileID, (uint32_t) nLine);
}

static void OnESTL_Notification(uint16_t nFileID, uint16_t nLine)
{
    EXEH_vException(eEXEHSeverity_Warning, EXEH_CURRENT_MODULE_ID, nFileID, (uint32_t) nLine);
}

static void MACTL_Task(void *argument)
{
    #define TASK_PERIOD_MS     (50)
    #define WD_KICK_PERIOD     (2000)
    uint8_t u8AliveCntr = 0U;

    while (true)
    {
        ESTL_Drv_Task();
        ESCP_ModDrv_Task();
        ESCCP_ModDrv_Task();
        ESFWUPD_ModDrv_Task();

        // user-handling of CP commands
        CP_Handler_Task();

        osDelay(TASK_PERIOD_MS);

        u8AliveCntr++;

        if ((u8AliveCntr * TASK_PERIOD_MS) >= WD_KICK_PERIOD)
        {
            u8AliveCntr = 0U;
            TaskMonitor_IamAlive(TASK_MACTL_DISPATCHER);
            vApplicationLowStackCheck(TASK_MACTL_DISPATCHER);
        }
    }
}

osThreadId_t ESSA_Stack_TP_Layer_GetMainThreadHandle(void)
{
    return MACTL_TaskHandle;
}

void ESSA_Stack_TP_Layer_Init(void)
{
    // Initialise the 'Transport Layer'
    tlIntf.nMacAddress = MacCfg_u8GetMacAddress(eMAC_Interface_Primary);
    tlIntf.TickGet16 = ESSA_CommonUtils_getTickU16;
    tlIntf.TickGet32 = HAL_GetTick;
    tlIntf.OnException = OnESTL_Exception;
    tlIntf.OnNotification = OnESTL_Notification;

    ESTL_Drv_Init(&tlIntf, true);

    FWUPD_Handler_Init();

    CP_Handler_Init();

    MACTL_TaskHandle = osThreadNew(MACTL_Task, NULL, &MACTL_Task_attributes);
    CRIT_ASSERT(MACTL_TaskHandle);

    TaskMonitor_TaskInitialized(TASK_MACTL_DISPATCHER);
}

void ESSA_Stack_TP_Layer_PrepareThreadWait(void)
{
    bThreadAlreadyReleased = false;
}

eThreadBlockEvt_t ESSA_Stack_TP_Layer_ThreadWaitForEvent(uint32_t u32TimeoutMs)
{
    uint32_t u32OsThreadFlagsResult = 0U;
    eThreadBlockEvt_t result = THREADBLOCKEVT_ERROR;

    (void) osThreadFlagsClear(UNBLOCK_TP_THREAD_FLAG);

    if (bThreadAlreadyReleased)
        result = THREADBlOCKEVT_WAITFINISHED;
    else
    {
        u32OsThreadFlagsResult = osThreadFlagsWait(UNBLOCK_TP_THREAD_FLAG,
                                                   osFlagsWaitAll,
                                                   u32TimeoutMs);

        if ((u32OsThreadFlagsResult & UNBLOCK_TP_THREAD_FLAG) == (UNBLOCK_TP_THREAD_FLAG))
            result = THREADBlOCKEVT_WAITFINISHED;
        else
            if (u32OsThreadFlagsResult == osErrorTimeout)
                result = THREADBLOCKEVT_WAITTIMEOUT;
    }

    return result;
}

void ESSA_Stack_TP_Layer_ReleaseThreadWait(void)
{
    bThreadAlreadyReleased = true;
    (void) osThreadFlagsSet(MACTL_TaskHandle,
                            UNBLOCK_TP_THREAD_FLAG);
}
