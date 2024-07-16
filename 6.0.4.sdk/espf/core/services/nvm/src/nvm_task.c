/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Services
 * @{
 *
 * @defgroup Nvm
 * @{
 *
 * @file Nvm_Task.c
 * @brief NVM service OS tasks implementation
 *
 * @}
 * @}
 */

#include "es_cdef.h"
#include <nvm/inc/nvm.h>
#include "nvm_cfg.h"
#include "cmsis_os2.h"
#include "assertions.h"

static osThreadId_t Nvm_TaskHandle = NULL;

static const osThreadAttr_t Nvm_Task_attributes =
{
    .name = "NvmTask",
    .priority = (osPriority_t) osPriorityAboveNormal,
    .stack_size = 2500
};

static void fs_Nvm_Task(void *param)
{
    (void) param;

    while (true)
    {
        Nvm_Store(NVMSTORE_STANDARD);

        NVM_Cfg_ReportTaskAlive();

        osDelay(NVM_TASK_PERIOD_MS);
    }
}

void Nvm_TaskStart(void)
{
    Nvm_TaskHandle = osThreadNew((osThreadFunc_t) fs_Nvm_Task, NULL, (const osThreadAttr_t *) &Nvm_Task_attributes);
    CRIT_ASSERT(Nvm_TaskHandle);
}
