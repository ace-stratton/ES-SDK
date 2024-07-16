/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_dispatcher_thread.c
 * @brief    Message dispatcher thread for the ESPS I MAC Driver
 *
 * @}
 */

#include <cmsis_os2.h>

#include "esps_drv_config.h"
#include "esps_drv_exeh_config.h"
#include "TaskMonitor.h"

#include <esps_drv.h>
#include <esps_drv_dispatcher.h>
#include <esps_drv_debug.h>

extern bool MAC_bProtocolProcessMessage(eMACInterface_t fp_eMACId, ESSATMAC_Message*  fp_psMsg);

/******************************************************************************
 * Local Preprocessor Definitions
 *****************************************************************************/
#define EXEH_CURRENT_MODULE_ID     (eEXEHModuleID_MAC_DISPATCHER)
/// Error mask, returned by osThreadFlagsWait in case there are errors.
#define MAC_DISPATCH_ERROR         (1U << 31U)
/// Flag for stopping the dispatcher.
#define MAC_DISPATCH_STOP_FLAG     (0x02U)
/// Flag for activating the dispatcher.
#define MAC_DISPATCH_ACTIVATE_FLAG (0x01U)
/// All flags the dispatcher is waiting for (with osThreadFlagsWait)
#define MAC_DISPATCH_FLAGS         (MAC_DISPATCH_STOP_FLAG | MAC_DISPATCH_ACTIVATE_FLAG)

typedef struct {
    // ESPS Interface info
    sMACInterfaceState_t *psInterfaceState;
    // FreeRTOS thread
    osThreadId_t pvThread;
} sDispatcherThread_t;

STATIC sDispatcherThread_t fs_sDispatcherThread_main = { .psInterfaceState = NULL, .pvThread = NULL };

/******************************************************************************
 * File Local Function Prototypes
 *****************************************************************************/
/**
 * Dispatcher thread entry function.
 *
 * @param fp_pvArg - Argument for the thread (MAC interface state).
 */
STATIC void fs_vDispatchThread (void * fp_pvArg);

/******************************************************************************
 * Private Function Definitions
 *****************************************************************************/

// Set MAC_DISPATCH_FLAGS as active
void DISP_vActivateDispatcherThread(eMACInterface_t fp_eInterface){
    uint32_t eStatus;
    (void) fp_eInterface;

    if (fs_sDispatcherThread_main.pvThread != NULL)
    {

        eStatus = osThreadFlagsSet(fs_sDispatcherThread_main.pvThread, MAC_DISPATCH_ACTIVATE_FLAG);

        if (eStatus != MAC_DISPATCH_ACTIVATE_FLAG)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_SystemCallFailed);
        }
    }
}

// Initialize the dispatcher.
void DISP_vThreadInit(eMACInterface_t fp_eInterface)
{
    STATIC const osThreadAttr_t sDispAttr =
    {
        //TODO: Make joinable, implement MAC interface stop
        //      join the thread at stop.
        .attr_bits = osThreadDetached,
        .name      = "MAC_DISP",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 3000
    };

    fs_sDispatcherThread_main.psInterfaceState = MacCfg_sGetMacInterfaceById(fp_eInterface);

    if (fs_sDispatcherThread_main.psInterfaceState != NULL)
    {
        // create thread only if not already existing...
        if (fs_sDispatcherThread_main.pvThread == NULL)
        {
            fs_sDispatcherThread_main.pvThread = osThreadNew(fs_vDispatchThread, (void*) &fs_sDispatcherThread_main, &sDispAttr);

            if (fs_sDispatcherThread_main.pvThread == NULL)
            {
                EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_SystemCallFailed);
            }
            else
                TaskMonitor_TaskInitialized(TASK_MACDRV_DISPATCHER);
        }
    }
}

/******************************************************************************
 * Local Function Definitions
 *****************************************************************************/
// Dispathcer thread
// It should call MAC_DISP_vDispatchMessages() from the esps driver
STATIC void fs_vDispatchThread (void * fp_pvArg)
{
    bool                   bRunning = true;
    uint32_t               u32Flags;
    sMACInterfaceState_t*  psInterface = ((sDispatcherThread_t*) fp_pvArg)->psInterfaceState;


    if (psInterface == NULL)
    {
        EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_DispatcherBroken);
    }
    else
    {
        MACDRV_DBG_PRINT("MAC dispatcher thread started (instance: %ld @ 0x%08x)\r\n", (uint32_t) psInterface->macIfId, (uint32_t) fp_pvArg);

        while(bRunning)
        {
            // Wait for activation
            u32Flags = osThreadFlagsWait(MAC_DISPATCH_FLAGS, osFlagsWaitAny, 1000);

            if ((u32Flags & MAC_DISPATCH_ERROR) && (u32Flags != osErrorTimeout))
            {
                EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_SystemCallFailed);
            }
            else
            {
                if (((u32Flags != osErrorTimeout) && (u32Flags & MAC_DISPATCH_ACTIVATE_FLAG)) ||
                     (u32Flags == osErrorTimeout))
                {
                    MACDRV_DBG_PRINT("Trg RxQ %ld [flg: %ld])\r\n", (uint32_t) psInterface->macIfId, (uint32_t) u32Flags);

                    MAC_DISP_vDispatchMessages(psInterface);
                }

                if ((u32Flags != osErrorTimeout) && (u32Flags & MAC_DISPATCH_STOP_FLAG))
                {
                    EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_SystemCallFailed);
                }
            }
            TaskMonitor_IamAlive(TASK_MACDRV_DISPATCHER);
            vApplicationLowStackCheck(TASK_MACDRV_DISPATCHER);
        }
    }

    osThreadExit();
}
