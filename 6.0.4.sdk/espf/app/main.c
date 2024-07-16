/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup app_main
 * @{
 *
 * @file main.c
 * @brief Initialization sequence and start the OS
 *
 * @}
 *
 */

#include "main.h"
#include "MCU_Init.h"
#include "AppTasks.h"
#include "TaskMonitor.h"
#include <errno.h>
#include <sys/unistd.h>
#include <stdarg.h>
#include "cubeadcs_driver.h"
#include "cubeadcs.h"
#include <es_crc32.h>
#include <MX_I2C.h>
#include <es_exeh.h>
#include <eps_i.h>
#include <FileManager.h>
#include <SdMngr.h>
#include "cubeadcs.h"
#include "drv_fram.h"
#include "datacache.h"
#include "payload_scheduler.h"
#include "nvm.h"
#include "assertions.h"
#include "timer.h"
#include "payload_ctrl.h"
#include "adcs_tlm.h"
#include "conops.h"
#include "eps_ctrl.h"
#include "aocs_cntrl.h"
#include "drv_mcu_temperature.h"
#include "FreeRTOS.h"

#if defined(MICROPYTHON_SERVICE_ENABLED)
#include "upy.h"
#endif

#include "if_sys_conf.h"
#include "if_sys_instancer.h"

#if defined(TELEMETRY_SERVICE_ENABLED)
#include "telemetry.h"
#endif

#if defined(SXBAND_SCHEDULER_ENABLED)
#include "sxband_sched.h"
#endif

#include "rng.h"
#if defined(CRYPTO_SERVICE_ENABLED)
#include "crypto.h"
#endif

#if defined(EXTMODULES_SBAND_TMTC_ENABLED)
#include "sband_tmtc.h"
#endif

#include "S_X_Band_Trnsm.h"

#include "trace.h"
#include "sys_time.h"
#include "drv_led.h"
#include "drv_iwdg.h"
#include "nvm_resetcounters.h"
#include "CommandsApi.h"
#include "es_coordsys.h"

#include "stm32h753xx.h"
#include "can.h"

#if defined(CSP_SUPPORT_ENABLED)
#include "csp_service.h"
#endif

#if defined(LWIP_SUPPORT_ENABLED)
#include "netw.h"
#endif

#if defined(GNSS_ENABLED)
#include "gnss.h"
#endif

#include "arm_fault_handler.h"
#include "nvm_resetcounters.h"
#include "fault_persistor.h"
#include <stdatomic.h>

/**
 * @brief MAIN - First executed method after boot/startup. General initialisation,
 *              followed by running the RTOS kernel
 */
NO_RETURN int main(void)
{
#ifdef DEBUG_ENABLED
    vRamTest_StackFill();
#endif

    // this initialization must be performed before any other call to memory allocation by
    // the RTOS
    freertos_user_init();

#ifdef DEBUG_ENABLED
    //Enable debug mode in sleep and stop modes
    HAL_DBGMCU_EnableDBGSleepMode();
    HAL_DBGMCU_EnableDBGStopMode();
#endif

    drv_led_init(); //Init Both LEDs at the beginning in order to see the LEDs On on any fold during initialization of the OBC

    CommandsApi_GPIO_Init();

    // Get and verify the runtime configuration from the flash
    sys_conf_init();

    // PVD and Brownout reset init
    PVD_BrownoutReset_Init();

    SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk);    // Enable All fault handlers

    // basic initialization of the exception storage facility...
    EXEH_bInit();

#ifdef DEBUG_ENABLED
#  if defined(DEBUG_MODE_WD_ENABLED)
    drv_iwdg_init(drv_iwdg_get_max_timeout());
#  endif
#else
    drv_iwdg_init(drv_iwdg_get_max_timeout());
#endif

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    rng_init();

    timer_init();

    /* Configure the system clock */
    SystemClock_IdleConfig();

    // this call muse be after SystemClock_IdleConfig() so that Backup RAM
    // clocks are turned on
    arm_fault_handler_init();

    fault_persistor_init();

    /* Initialize all configured peripherals */
    MX_AllPeripheryAndGpio_DeInit();

    /* Init scheduler */
    osKernelInitialize();

    trace_init();

    TaskMonitor_Init();

    dc_init();

    EXEH_bStartPersistorTask();

    Nvm_Init();
    Nvm_Load();
    Nvm_TaskStart();

#if 0
    // TODO: Currently commented because store takes place in the exception handler due to issues in noinit-ram
    fault_persistor_store();
#endif

#if defined(LWIP_SUPPORT_ENABLED)
    netw_init();
#endif

    // make sure these calls take place after the NVM init...
    NvmResetCounters_Update(NVMUPDATE_CLEAR_RESET_REASON);
    MCU_Init_I2cPullUps_Nvm();

    SdMngr_InitTask();
    fileManager_Init();

    PayloadScheduler_Init();
    payload_ctrl_init();

#if defined(TELEMETRY_SERVICE_ENABLED)
    telemetry_init();
    telemetry_start();
#endif

#if defined(CRYPTO_SERVICE_ENABLED)
    crypto_init();
    crypto_start();
#endif

    (void)drv_mcu_temp_init();

    MX_ADC1_Init();
    sys_time_init();
    MX_I2C_Init();

    AppTask_Init();

#if defined(MICROPYTHON_SERVICE_ENABLED)
    upy_init();
#endif

    // ESPS is initialised from the service task
    //  once the OS is running
    ServicesTask_Init();

    /* Coordinate frame initialization */
    coordSys_init();

    // Deinitialize all the modules by default
    if(! sys_inst_deinit(INIT_MEM))
        Error_Handler();
    if(! sys_inst_deinit(INIT_HW))
        Error_Handler();
    if (! sys_inst_deinit(INIT_OS))
        Error_Handler();

    // Deinit the dependent components by default
    eps_ctrl_deinit();
    ADCS_TLM_TaskDeInit();
    aocs_cntrl_task_deinit();

    // If the configuration is not valid, not even try to initialise the modules
    if (sys_conf_is_valid())
    {
        // MEMORY Initialization
        if(! sys_inst_init(INIT_MEM))
            Error_Handler();

        // HW (peripherals) Initialization
        if(! sys_inst_init(INIT_HW))
            Error_Handler();

        // OS Initialization
        if (! sys_inst_init(INIT_OS))
            Error_Handler();

        // TODO Move this as part of the init instancer interface
        if (sys_conf_is_module_active(SYS_MODULE_ID_EPS_I)
         || sys_conf_is_module_active(SYS_MODULE_ID_EPS_II)
         || sys_conf_is_module_active(SYS_MODULE_ID_EPS_M))
        {
            if (false == eps_ctrl_init())
            {
                CRIT_ASSERT(false);
            }
        }

        // TODO Move this as part of the init instancer interface
        if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS)
         || sys_conf_is_module_active(SYS_MODULE_ID_ES_ADCS))
        {
            ADCS_TLM_TaskInit();
            aocs_cntrl_task_init();
        }
#if defined(CUBEADCS_GEN2_ENABLED)
        else if ( sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2) )
        {
            aocs_cntrl_task_init();
        }
#endif

#if defined(GNSS_ENABLED)
        if (true == sys_conf_is_module_active(SYS_MODULE_ID_GNSS))
        {
            gnss_run();
        }
#endif
    }

#ifdef EXTMODULES_SBAND_TMTC_ENABLED
    sband_tmtc_init();
#endif

#if defined(SXBAND_SCHEDULER_ENABLED)
    if (sys_conf_is_module_active(SYS_MODULE_ID_SX_BAND))
    {
        sxband_sched_init();
        sxband_sched_start();
    }
    else
    {
        sxband_sched_deinit();
    }
#endif

/* Conops application initialised last due to services dependencies */
#if defined(OPMODES_ENABLED)
    conops_init();
#endif

    if ((false == can_rxq_init(CAN_ID_STANDARD, 5)) || // with default size
        (false == can_rxq_init(CAN_ID_EXTENDED, 100)) || // with default size
        (false == can_txq_init(100)) ||                  // with default size
        (false == can_init()))
    {
        Error_Handler();
    }

#if defined(CSP_SUPPORT_ENABLED)
    if (false == csp_service_init())
    {
        Error_Handler();
    }
#endif

#ifdef DEBUG_ENABLED
    vRamTest_StackUsageCheck();
#endif

    osKernelStart();

    while (true)
    {
        __NOP();
    }
}

void Error_Handler(void)
{
    static atomic_bool in_error_handler = false;

    // this check is needed to avoid recursive calls if the
    // fault_persistor_store() function fails with a call to Error_Handler()
    if (!in_error_handler)
    {
        in_error_handler = true;

        drv_led_set(DRV_LED_ID_GREEN, DRV_LED_STATE_ON);
        drv_led_set(DRV_LED_ID_AMBER, DRV_LED_STATE_ON);

        // TODO: Remove when problem with noinit-ram is resolved!
        fault_persistor_store();

        TaskMonitor_ImmediateReset(TASK_MONITOR_FAULT_RESET);
    }
}

/**
 * @brief This function is called in case of heap memory allocation failure upon calling malloc().
 */
void vApplicationMallocFailedHook(void)
{
    const char msg[] = "malloc failed";
    arm_fault_handler_generic((uint8_t *) msg, sizeof(msg));

    Error_Handler();
}

/**
 * @brief This function is executed in case of insufficient stack memory for the Operation system.
 *  The stack of the OS (configTOTAL_HEAP_SIZE) must be increased.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    const char msg[] = "STKOVFL";
    char buf[configMAX_TASK_NAME_LEN + sizeof(msg)] = { '\0' };
    snprintf(buf, sizeof(buf), "%s:%s", msg, pcTaskName);
    arm_fault_handler_generic((uint8_t *) buf, strlen(buf));

    Error_Handler();
}
