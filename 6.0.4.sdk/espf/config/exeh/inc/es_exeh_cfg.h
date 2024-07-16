/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup service_exeh
 * @{
 * @file es_exeh_cfg.h
 * @brief Configuration parameters and types for the EXEH service
 * @}
 */
#ifndef ES_EXEH_CFG_H
#define ES_EXEH_CFG_H
#include "es_cdef.h"
#include "stm32h7xx_hal.h"
#include "ffconf.h"

/** @brief Specifies whether module file names are stored as part of the exception log on the SD card */
#define EXEH_CONFIG_STORE_FILENAME_ENABLED  (0)

/** @brief Specifies whether exception timestamps are stored as part of the exception log on the SD card */
#define EXEH_CONFIG_EVENT_TIMESTAMP_ENABLED (1)

/** @brief Specifies the exception persistor task period in milliseconds */
#define TASK_PERSISTOR_PERIOD_MS            (1000U)

/** @brief Number of task periods before attempting to persist the exception trace buffers to the SD card */
#define TASK_PERSISTOR_MAX_TASK_CNT         (10U)

/** @brief Defines the id of the partition used for storing the files for EXEH module.
  */
#define EXEH_DUMP_DIRECTORY_NAME          ("")

/** @brief Defines the position of the index character in the file name template
  * @verbatim
  "exeh_btl.d__"
             ^
             |
  @endverbatim
  */
#define EXEH_DUMP_FN_INDEX_POS              (10U)

/** @brief Defines the position of the marker character in the file name template
  * @verbatim
  "exeh_btl.d__"
              ^
              |
  @endverbatim
  */
#define EXEH_DUMP_FN_MARKER_POS             (11U)

/** @brief A file name ending with this character is the currently active file */
#define EXEH_DUMP_FN_ACTIVE_MARKER          'o'
/** @brief File names ending with this character indicate older reports */
#define EXEH_DUMP_FN_INACTIVE_MARKER        'x'

/** @brief Maximum number of preserved exception files before starting to erase old content */
#define EXEH_DUMP_FN_SLOTS                  10U

#if EXEH_DUMP_FN_SLOTS > 10
#error EXEH_DUMP_FN_SLOTS shall be set a value <= 10!
#endif

#if defined(BOOTLOADER)
/** @brief File name template used for bootloader exception reporting */
#define EXEH_DUMP_FILE_NAME                 "exeh_btl.d__"
#else
/** @brief File name template used for application exception reporting */
#define EXEH_DUMP_FILE_NAME                 "exeh_app.d__"
#endif  // #if defined(BOOTLOADER)

/** @brief Maximum number of exceptions stored per severity level */
#define EXEH_EXCEPTIONS_MAX     (20U)

/** @brief Maximum file name size in bytes when #EXEH_CONFIG_STORE_FILENAME_ENABLED is set to `1`*/
#define FNAME_SIZE              (FF_LFN_BUF)

/** @brief Maximum number of warnings stored for a single module */
#define WARN_SLOTS_COUNT        (2U)

/** @brief Maximum number of errors stored for a single module */
#define ERROR_SLOTS_COUNT       (2U)

/** @brief Maximum number of fatals stored for a single module */
#define FATAL_SLOTS_COUNT       (2U)

/**
 * @brief enumeration with all modules that could store exceptions
 */
typedef enum
{
    // Exceptions from the operating system.
    eEXEHModuleID_OS,                           // not in uses so far !!!
    // Exceptions from MCU init module.
    eEXEHModuleID_MCU_INIT,
    // Exceptions from the EXEH module itself.
    eEXEHModuleID_ES_EXEH,
    // Exceptions from RCC driver.
    eEXEHModuleID_RCC,
    // Exceptions from the UART module.
    eEXEHModuleID_UART,
    // Exceptions from the RS485 module.
    eEXEHModuleID_MAC,
    eEXEHModuleID_MAC_POOL,
    eEXEHModuleID_MAC_RECEIVE_IRQ,
    eEXEHModuleID_MAC_TRANSMIT_IRQ,
    eEXEHModuleID_MAC_QUEUE,
    eEXEHModuleID_MAC_DISPATCHER,
    eEXEHModuleID_MAC_TIM,
    eEXEHModuleID_MAC_RNG,
    // Exceptions for the MAC TL module.
    eEXEHModuleID_CP_HANDLER,
    eEXEHModuleID_ESSA_STACK_TP_LAYER,
    eEXEHModuleID_S_X_BAND,
    // Exceptions from EPS communication.
    eEXEHModuleID_EPS_COMM,
    // Exceptions from EPS Control Service
    eEXEHModuleID_EPS_CTRL,
    // Exceptions from EPS communication.
    eEXEHModuleID_UHF_COMM,
    // Exceptions from UHF_ANT communication.
    eEXEHModuleID_UHF_ANT_COMM,
    // Exceptions from ARDU_CAM communication.
    eEXEHModuleID_ARDU_CAM_COMM,
    // Exceptions from CON_OPS.
    eEXEHModuleID_CON_OPS,
    // Exceptions from power manager.
    eEXEHModuleID_PWR_MNG,
    // Exceptions from system status and telemetry.
    eEXEHModuleID_SYS_STAT_AND_TLMTRY,
    // Exceptions from Firmware Update
    eEXEHModuleID_FWUPD_HANDLER,
    eEXEHModuleID_FWUPD_HANDLER_CFG,
    // Exceptions from the Endurosat ADCS module
    eEXEHModuleID_ES_ADCS,
	// Exceptions from the AOCS performance monitor module
	eEXEHModuleID_AOCS_PM,
    // Exceptions from Beacons module
    eEXEHModuleID_BEACONS,
    // Exceptions from UHF keep alive module
    eEXEHModuleID_UHF_KEEP_ALIVE,
    // Exceptions from the CubeADCS module
    eEXEHModuleID_CUBEADCS,
    eEXEHModuleID_CUBEADCS_FHANDL,
    // Exceptions from the Sd card manager (SdMngr) module
    eEXEHModuleID_SDMNGR,
    // Exceptions from file logging module
    eEXEHModuleID_FILE_LOGS,
    eEXEHModuleID_TASK_MONITOR,
    // Exceptions from Payload Controller
    eEXEHModuleID_PAYLOAD_CTRL,
    eEXEHModuleID_TELEMETRY_FILESINK,
    // Exceptions from the sensor data service
    eEXEHModuleID_SDS,
    // Exceptions from the actuator control service
    eEXEHModuleID_ACTUATOR_CONTROL_SERVICE,
    eEXEHModuleID_SXBAND_SCHED,
    eEXEHModuleID_CRYPTO,
    eEXEHModuleID_UPYTHON,
    eEXEHModuleID_CUBEADCS_GEN2,
    eEXEHModuleID_COUNT
} eEXEHModuleID_t;



//////////////////////////////////////////////////////////////////////
//        List of all Exception ID according the Module ID          //
//     Keep these arranged systematically for easy documentation    //
// can be use from external applications (GUI, Ground Station etc)  //
//////////////////////////////////////////////////////////////////////

//enumeration for DTC type eEXEHModuleID_MCU_INIT
typedef enum
{
    eEXEH_MCU_INIT_EXCEPTION_ID_I2C_RST,
    eEXEH_MCU_INIT_EXCEPTION_ID_MANITO_INIT,
    eEXEH_MCU_INIT_EXCEPTION_ID_ACCEL_INIT,
    eEXEH_MCU_INIT_EXCEPTION_ID_GYRO_INIT,
    eEXEH_MCU_INIT_EXCEPTION_ID_COUNT
}eEXEH_MCU_INIT_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_MCU_INIT
typedef enum
{
    eEXEH_S_X_BAND_EXCEPTION_ID_AUTO_BAUD_RATE_NOT_FOUND,
    eEXEH_S_X_BAND_EXCEPTION_ID_COUNT
}eEXEH_S_X_BAND_ExceptionID_t;

//enumeration for DTC type eEXEHModuleID_EPS_COMM
typedef enum
{
    eEXEH_EPS_EXCEPTION_ID_COMM_ERROR,
    eEXEH_EPS_EXCEPTION_ID_MAC_COMM_PARAMS_ERROR,
    eEXEH_EPS_EXCEPTION_ID_COMM_INVALID_PARAMS_ERROR,
    eEXEH_EPS_EXCEPTION_ID_COMM_MAC_TIMEOUT_ERROR,
    eEXEH_EPS_EXCEPTION_ID_COMM_MAC_WRITE_SEMAPHOR_ERR_ERROR,
    eEXEH_EPS_EXCEPTION_ID_COMM_MAC_READ_SEMAPHOR_ERR_ERROR,
    eEXEH_EPS_EXCEPTION_ID_COMM_MAC_WRITE_MUTEX_ERR_ERROR,
    eEXEH_EPS_EXCEPTION_ID_COMM_MAC_READ_MUTEX_ERR_ERROR,
    eEXEH_EPS_EXCEPTION_ID_COUNT
}eEXEH_EPS_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_EPS_COMM

//enumeration for DTC type eEXEHModuleID_EPS_CTRL
typedef enum
{
    eEXEH_EPS_CTRL_QUEUE_FULL,      /**> The request queue is full */
    eEXEH_EPS_CTRL_OS_ERROR,        /**> Error with some OS initialization */
    eEXEH_EPS_CTRL_COUNT
} eEXEH_EPS_CTRL_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_EPS_CTRL

//enumeration for DTC type eEXEHModuleID_UHF_COMM
typedef enum
{
    eEXEH_UHF_EXCEPTION_ID_COMM_I2C_ERROR,
    eEXEH_UHF_EXCEPTION_ID_MAC_COMM_PARAMS_ERROR,
    eEXEH_UHF_EXCEPTION_ID_COMM_MAC_TIMEOUT_ERROR,
    eEXEH_UHF_EXCEPTION_ID_COMM_INVALID_PARAMS_ERROR,
    eEXEH_UHF_EXCEPTION_ID_COMM_MAC_WRITE_SEMAPHOR_ERR_ERROR,
    eEXEH_UHF_EXCEPTION_ID_COMM_MAC_READ_SEMAPHOR_ERR_ERROR,
    eEXEH_UHF_EXCEPTION_ID_COMM_MAC_WRITE_MUTEX_ERR_ERROR,
    eEXEH_UHF_EXCEPTION_ID_COMM_MAC_READ_MUTEX_ERR_ERROR,
    eEXEH_UHF_EXCEPTION_ID_COUNT
}eEXEH_UHF_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_UHF_COMM

//enumeration for DTC type eEXEHModuleID_UHF_ANT_COMM
typedef enum
{
    eEXEH_UHF_ANT_EXCEPTION_ID_COMM_ERROR,
    eEXEH_UHF_ANT_EXCEPTION_ID_VBAT_RX_ERROR,
    eEXEH_UHF_ANT_EXCEPTION_ID_COUNT
}eEXEH_UHF_ANT_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_UHF_ANT_COMM

//enumeration for DTC type eEXEHModuleID_ARDU_CAM_COMM
typedef enum
{
    eEXEH_ARDU_CAM_EXCEPTION_ID_COMM_ERROR,
    eEXEH_ARDU_CAM_EXCEPTION_ID_COUNT
}eEXEH_ARDU_CAM_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_ARDU_CAM_COMM

//enumeration for DTC type eEXEHModuleID_CON_OPS
typedef enum
{
    eEXEH_CON_OPS_EXCEPTION_TASK_INIT_FAILURE,
    eEXEH_CON_OPS_EXCEPTION_ID_COUNT
}eEXEH_CON_OPS_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_ARDU_CAM_COMM

//enumeration for DTC type eEXEHModuleID_PWR_MNG
typedef enum
{
    eEXEH_PWR_MNG_EXCEPTION_SET_WAKEUP_TIME_FAIL,
    eEXEH_PWR_MNG_EXCEPTION_ID_COUNT
}eEXEH_PWR_MNG_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_ARDU_CAM_COMM

//enumeration for DTC type eEXEHModuleID_SYS_STAT_AND_TLMTRY
typedef enum
{
    eEXEH_SYS_STAT_TLMTRY_EXCEPTION_EPS_READ_ERROR,
    eEXEH_SYS_STAT_TLMTRY_EXCEPTION_UHF_READ_ERROR,
    eEXEH_SYS_STAT_TLMTRY_EXCEPTION_UHF_ANT_READ_ERROR,
    eEXEH_SYS_STAT_TLMTRY_EXCEPTION_ACCELL_READ_ERROR,
    eEXEH_SYS_STAT_TLMTRY_EXCEPTION_MAGNITOM_READ_ERROR,
    eEXEH_SYS_STAT_TLMTRY_EXCEPTION_CUBE_ADCS_READ_ERROR,
    eEXEH_SYS_STAT_TLMTRY_EXCEPTION_ID_COUNT
}eEXEH_SYS_STAT_AND_TLMTRY_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_SYS_STAT_AND_TLMTRY

//enumeration for DTC type eEXEHModuleID_ES_ADCS
typedef enum
{
    eEXEH_ES_ADCS_INIT_FAIL,
    eEXEH_ES_ADCS_OP_MODE_SWITCH_INVALID,
    eEXEH_ES_ADCS_OP_MODE_INVALID,
    eEXEH_ES_ADCS_ESTIMATOR_INVALID_TYPE,
    eEXEH_ES_ADCS_ESTIMATOR_ALGO_IDENTICAL,
    eEXEH_ES_ADCS_ESTIMATOR_BDOT_DC_READ_FAIL,
    eEXEH_ES_ADCS_ESTIMATOR_INVALID_MAG_CONFIG,
    eEXEH_ES_ADCS_CONTROLLER_INVALID_TYPE,
    eEXEH_ES_ADCS_CONTROLLER_BDOT_DC_READ_FAIL,
    eEXEH_ES_ADCS_ID_COUNT
} eEXEH_ES_ADCS_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_ES_ADCS

//enumeration for DTC type eEXEHModuleID_AOCS_PM
typedef enum
{
    eEXEH_AOCS_PM_RECEIVED_BAD_DATA,
	eEXEH_AOCS_PM_FAILED_TO_OPEN_FILE,
	eEXEH_AOCS_PM_FAILED_TO_WRITE_TO_FILE,
	eEXEH_AOCS_PM_FAILED_TO_GET_TIME_STAMP,
	eEXEH_AOCS_PM_LONG_TERM_MEASURE_TOO_BIG,
    eEXEH_AOCS_PM_ID_COUNT
} eEXEH_AOCS_PM_ExceptionID_t;
//end of enumeration for DTC type 	eEXEHModuleID_AOCS_PM

//enumeration for DTC type eEXEHModuleID_BEACONS
typedef enum
{
    eEXEH_BEACONS_EXCEPTION_EPS_READ_ERROR,
    eEXEH_BEACONS_EXCEPTION_UHF_READ_ERROR,
    eEXEH_BEACONS_EXCEPTION_UHF_ANT_READ_ERROR,
    eEXEH_BEACONS_EXCEPTION_ADCS_READ_ERROR,
    eEXEH_BEACONS_EXCEPTION_ID_COUNT
}eEXEH_BEACONS_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_BEACONS

//enumeration for DTC type eEXEHModuleID_UHF_KEEP_ALIVE
typedef enum
{
    eEXEH_UHF_KEEP_ALIVE_EXCEPTION_CMD_ERROR,
    eEXEH_UHF_KEEP_ALIVE_EXCEPTION_CMD_TIMEOUT,
    eEXEH_UHF_KEEP_ALIVE_EXCEPTION_GS_TIMEOUT,
    eEXEH_UHF_KEEP_ALIVE_EXCEPTION_ALL_UHF_DISSCONNECTED,
    eEXEH_UHF_KEEP_ALIVE_EXCEPTION_EPS_M_CMD_ERROR,
    eEXEH_UHF_KEEP_ALIVE_EXCEPTION_ID_COUNT
}eEXEH_UHF_KEEP_ALIVE_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_UHF_KEEP_ALIVE

//enumeration for DTC type eEXEHModuleID_CUBEADCS
typedef enum
{
    eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR,
    eEXEH_CUBEADCS_EXCEPTION_OS_ERROR,
    eEXEH_CUBEADCS_EXCEPTION_USAGE_ERROR,
    eEXEH_CUBEADCS_EXCEPTION_COMM_COMM_ERROR,
    eEXEH_CUBEADCS_EXCEPTION_ID_COUNT
} eEXEH_CUBEADCS_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_CUBEADCS

//enumeration for SdMngr type eEXEHModuleID_SDMNGR
typedef enum
{
    eEXEH_SDMNGR_EXCEPTION_FR_DISK_ERR = 1, // This mirrors the error types from ff.h:FRESULT where 0 is FR_OK.
    eEXEH_SDMNGR_EXCEPTION_FR_INT_ERR,
    eEXEH_SDMNGR_EXCEPTION_FR_NOT_READY,
    eEXEH_SDMNGR_EXCEPTION_FR_NO_FILE,
    eEXEH_SDMNGR_EXCEPTION_FR_NO_PATH,
    eEXEH_SDMNGR_EXCEPTION_FR_INVALID_NAME,
    eEXEH_SDMNGR_EXCEPTION_FR_DENIED,
    eEXEH_SDMNGR_EXCEPTION_FR_EXIST,
    eEXEH_SDMNGR_EXCEPTION_FR_INVALID_OBJECT,
    eEXEH_SDMNGR_EXCEPTION_FR_WRITE_PROTECTED,
    eEXEH_SDMNGR_EXCEPTION_FR_INVALID_DRIVE,
    eEXEH_SDMNGR_EXCEPTION_FR_NOT_ENABLED,
    eEXEH_SDMNGR_EXCEPTION_FR_NO_FILESYSTEM,
    eEXEH_SDMNGR_EXCEPTION_FR_MKFS_ABORTED,
    eEXEH_SDMNGR_EXCEPTION_FR_TIMEOUT,
    eEXEH_SDMNGR_EXCEPTION_FR_LOCKED,
    eEXEH_SDMNGR_EXCEPTION_FR_NOT_ENOUGH_CORE,
    eEXEH_SDMNGR_EXCEPTION_FR_TOO_MANY_OPEN_FILES,
    eEXEH_SDMNGR_EXCEPTION_FR_INVALID_PARAMETER,
    eEXEH_SDMNGR_EXCEPTION_INIT_FAILED,
    eEXEH_SDMNGR_EXCEPTION_FORMAT_FAILED,
    eEXEH_SDMNGR_EXCEPTION_RECTED_OPPERATION,
    eEXEH_SDMNGR_EXCEPTION_ID_COUNT
} eEXEH_SDMNGR_ExceptionID_t;
//end of enumeration for SdMngr type eEXEHModuleID_SDMNGR

//enumeration for FileLogs type eEXEHModuleID_SDMNGR
typedef enum
{
    eEXEH_FILE_LOGS_EXCEPTION_WRITE_FAIL,
    eEXEH_FILE_LOGS_EXCEPTION_CREATE_FILE,
    eEXEH_FILE_LOGS_EXCEPTION_PREPARE_FILE,
    eEXEH_FILE_LOGS_EXCEPTION_ID_COUNT
} eEXEH_FILE_LOGS_ExceptionID_t;
//end of enumeration for FileLogs type eEXEHModuleID_FILE_LOGS

typedef enum
{
    eEXEH_TASK_MONITOR_TASK_TIMEOUT,
    eEXEH_TASK_MONITOR_TASK_STACK_WARN,
    eEXEH_TASK_MONITOR_TASK_COUNT
} eEXEH_TASK_MON_ExceptionID_t;

//enumeration for DTC type eEXEHModuleID_ACTUATOR_CONTROL_SERVICE
typedef enum
{
    eEXEH_ACTUATOR_CONTROL_SERVICE_INVALID_STATE,
    eEXEH_ACTUATOR_CONTROL_SERVICE_MTQ_DC_READ_FAIL,
    eEXEH_ACTUATOR_CONTROL_SERVICE_MTQ_COORD_SYS_FAIL,
    eEXEH_ACTUATOR_CONTROL_SERVICE_COUNT,
}eEXEH_ACTUATOR_CONTROL_SERVICE_ExceptionID_t;
//end of enumeration for DTC type eEXEHModuleID_ACTUATOR_CONTROL_SERVICE

typedef enum
{
    EXEH_SXB_SCHED_CANT_SPAWN_TASK,
    EXEH_SXB_SCHED_REPORT_CANT_OPEN_FILE,
    EXEH_SXB_SCHED_REPORT_CANT_WRITE_FILE,
    EXEH_SXB_SCHED_REPORT_SXB_LOG_OPEN_ERR,
    EXEH_SXB_SCHED_REPORT_SXB_LOG_READ_ERR,
    EXEH_SXB_SCHED_REPORT_SXB_LOG_RENAME_ERR,
} exeh_sxband_sched_error_codes_t;

typedef enum
{
    EXEH_CRYPTO_CANT_SPAWN_TASK,
    EXEH_CRYPTO_CANT_OPEN_FILE,
    EXEH_CRYPTO_CANT_WRITE_FILE,
} exeh_crypto_error_codes_t;


typedef enum
{
    EXEH_UPYTHON_SDCARD_NOT_READY,
    EXEH_UPYTHON_CANT_FIND_SCRIPT_CONTEXT,
    EXEH_UPYTHON_CANT_OPEN_FILE,
    EXEH_UPYTHON_CANT_WRITE_FILE,
    EXEH_UPYTHON_CANT_GET_MUTEX,
    EXEH_UPYTHON_NO_VALID_MUTEX,
    EXEH_UPYTHON_CANT_CREATE_QUEUE,
    EXEH_UPYTHON_CANT_CREATE_TASK,
    EXEH_UPYTHON_ERROR
} exeh_upy_error_codes_t;

typedef enum
{
    EXEH_CUBEADCS_GEN2_TASK_SPAWN_ERROR,
    EXEH_CUBEADCS_GEN2_OS_OBJ_ERR,
    EXEH_CUBEADCS_GEN2_SYS_STATE_CHANGE_FAILED,
    EXEH_CUBEADCS_GEN2_INVALID_SYS_STATE,
    EXEH_CUBEADCS_GEN2_PERIODIC_HEALTH_CHECK_FAILDED,
	EXEH_CUBEADCS_GEN2_INVALID_SYS_STATE_EXIT,
    EXEH_CUBEADCS_GEN2_ERROR_ID_COUNT
} exeh_cubeadcs_gen2_error_codes_t;

/**
 * @brief Project specific EXEH warning handler.
 */
void EXEH_vHandleWarning(void);

/**
 * @brief Project specific EXEH error handler.
 */
void EXEH_vHandleError(void);

/**
 * @brief Project specific EXEH fatal handler.
 *
 * Could be used to implement global handling in case of fatal error occurrences, e.g.
 * to perform a soft reset of the system.
 */
void EXEH_vHandleFatal(void);

#define getSystemTickCount()    HAL_GetTick()

#endif //ES_EXEH_CFG_H
