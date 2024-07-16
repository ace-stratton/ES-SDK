/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TASKMONITOR_CFG_H
#define TASKMONITOR_CFG_H

/**
 * @addtogroup taskmon
 * @{
 *
 * @file    taskmon_cfg.h
 * @brief   Configuration Header for the Task Monitor service
 *
 * @}
 *
 */

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/
typedef enum {
    TASK_MONITOR_TASK = 0x00,
#if defined(GENERAL_EXEH_PERSIST_ENABLED)
    TASK_MONITOR_EXEH_PERSISTOR,
#endif
    TASK_MONITOR_APP_TASK ,
    TASK_MONITOR_SERVICES ,
    TASK_MONITOR_SD_MANAGER ,
    TASK_MONITOR_S_X_BAND ,
    TASK_MONITOR_CUBEADCS ,
    TASK_MONITOR_CUBEADCS_FHANDL ,
    TASK_PAYLOAD_SCHEDULER  ,
#if defined(TELEMETRY_SERVICE_ENABLED)
    TASK_TELEMETRY,
    TASK_TELEMETRY_FILE_SINK,
#endif
    TASK_MONITOR_SP ,
#if defined(COMM_RS485_MAC_LAYER_ENABLED)
    TASK_MACDRV_DISPATCHER ,
    TASK_MACTL_DISPATCHER ,
    TASK_FWUPD_HANDLER ,
    TASK_ESSA_SP_HANDLER ,
#endif
    TASK_NVM,
    TASK_DATACACHE,
    TASK_ADCS_TLM,
#if defined(OPMODES_ENABLED)
    TASK_CONOPS_PERIODIC_EV,
#endif // #if defined(OPMODES_ENABLED)
    TASK_MONITOR_PAYLOAD_CTRL,
    TASK_BEACONS,
    TASK_EPS_CTRL,
    TASK_EPS_I,
    TASK_EPS_II,
    TASK_MONITOR_ES_ADCS,
    TASK_ACTUATOR_CONTROL_SERVICE,
    TASK_SDS,
    TASK_AOCS_CNTRL,
#if defined(SXBAND_SCHEDULER_ENABLED)
    TASK_SXBAND_SCHED,
#endif // #if defined(SXBAND_SCHEDULER_ENABLED)
#if defined(CRYPTO_SERVICE_ENABLED)
    TASK_CRYPTO_SRV,
#endif    // #if defined(CRYPTO_SERVICE_ENABLED)
#if defined(EXTMODULES_SBAND_TMTC_ENABLED)
    TASK_SBAND_TMTC,
#endif
#if defined(MICROPYTHON_SERVICE_ENABLED)
    TASK_MONITOR_UPYTHON,
#endif
#if defined(LWIP_SUPPORT_ENABLED)
    TASK_ETHERNET,
    TASK_TCPIP,
#endif
#if defined(SLIP_SUPPORT_ENABLED) && defined(LWIP_SUPPORT_ENABLED)
    TASK_SLIP,
#endif
    TASK_CAN_INIT,
    TASK_CAN_TX,
#if defined(CUBEADCS_GEN2_ENABLED)
    TASK_MONITOR_CUBEADCS_GEN2,
    TASK_MONITOR_CUBEADCS_GEN2_COMM,
    TASK_MONITOR_CUBEADCS_GEN2_TRANSFER,
#endif
#if defined(GNSS_ENABLED)
	TASK_MONITOR_GNSS_INIT,
	TASK_MONITOR_GNSS_LISTEN,
#endif
    TASK_MONITOR_TASKS_NUMBER
} TASK_MONITOR_TasksEnum;

typedef enum{
    TASK_MONITOR_SW_RESET,
    TASK_MONITOR_FAULT_RESET,
    TASK_MONITOR_USER_DELAYED_RESET,
    TASK_MONITOR_TASK_TIMEOUT,
    TASK_MONITOR_RESET_NUMBER
} TASK_MONITOR_resetEnum;

typedef enum
{
  TASK_MON_POLICY_MONITOR,    // task monitoring is active as soon as task initializes
  TASK_MON_POLICY_DONT_CARE,  // task monitoring skips this task because it doesn't expect it to be operational
  TASK_MON_POLICY_MAX
} task_mon_policy_t;

#endif    /* TASKMONITOR_CFG_H */
