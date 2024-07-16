/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup sband_tmtc
 * @{
 *
 * @file     sband_tmtc.c
 * @brief    Driver for EnduroSat S Band TMTC
 *
 * @}
 */
#include "sband_tmtc.h"
#include "sband_tmtc_cfg.h"
#include "fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCProtocolClient.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "assertions.h"
#include "TaskMonitor.h"

#include <string.h>

#define FS_RECEIVED_FLAG    (1)
#define FS_MUTEX_TIMEOUT    SBAND_TMTC_RESP_TIMEOUT

static bool fs_is_active = false; /**< S Band is responding */
static osMutexId_t fs_lock = NULL;
static osThreadId_t fs_thread_handle = NULL;
static osThreadAttr_t fs_thread_attr = {
        .name = "sband_tmtc",
        .stack_size = 1024,
        .priority = (osPriority_t) osPriorityNormal
};

/** Monitoring task */
static void fs_thread_routine(void *args);

void sband_tmtc_init(void) {
    static bool already_init = false;

    if (!already_init) {
        already_init = true;

        fs_thread_handle = osThreadNew(fs_thread_routine, NULL,
                &fs_thread_attr);
        CRIT_ASSERT(fs_thread_handle);

        fs_lock = osMutexNew(NULL);
        CRIT_ASSERT(fs_lock);
    }
}

bool sband_tmtc_is_active(void) {
    bool res = false;

    CRIT_ASSERT(fs_lock != NULL);

    if (NULL != fs_lock) {
        if (osOK == osMutexAcquire(fs_lock, FS_MUTEX_TIMEOUT)) {
            res = fs_is_active;
            osMutexRelease(fs_lock);
        }
    }

    return res;
}

void sband_tmtc_uptime_response_handler(const RespContext_t *const resp_ctx,
        const SBAND_TMTCReadUpTimeResponseData_t *const response_data) {
    CRIT_ASSERT(NULL != fs_thread_handle);
    CRIT_ASSERT(NULL != resp_ctx);
    CRIT_ASSERT(NULL != response_data);

    (void) resp_ctx;
    (void) response_data;

    if (NULL != fs_thread_handle) {
        osThreadFlagsSet(fs_thread_handle, FS_RECEIVED_FLAG);
    }
}

static void fs_thread_routine(void *args) {
    (void) args;

    ReqContext_t ctx;
    ctx.nInterfaceNumber = ESSASNI_SYS_PRI;
    ctx.nAddr = sband_tmtc_cfg_get_mac_address();
    ctx.netType = ESSASNETT_INTERNAL;
    ctx.seqId = 0;

    TaskMonitor_TaskInitialized(TASK_SBAND_TMTC);

    while (1) {
        osDelay(2000);


        TaskMonitor_IamAlive(TASK_SBAND_TMTC);

        (void) SBAND_TMTC_ReadUpTimeReq(&ctx);

        bool received = false;

        if (FS_RECEIVED_FLAG
                == osThreadFlagsWait(FS_RECEIVED_FLAG, osFlagsWaitAny, 1000)) {
            received = true;
        }

        if (osOK == osMutexAcquire(fs_lock, FS_MUTEX_TIMEOUT)) {
            fs_is_active = received;
            osMutexRelease(fs_lock);
        }

        vApplicationLowStackCheck(TASK_SBAND_TMTC);
    }
}
