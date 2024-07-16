/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_ERR_HANDL_H_
#define CUBEADCS_ERR_HANDL_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_errhandl.h
 * @brief    Interface for the error handling logic. Used internally by the CubeADCS logic if enabled.
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/

#include "cubeadcs.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

/** @brief Bitmask used to extract the errors for TLM_132 when the CubeADCS is in bootloader */
#define CUBEADCS_DIAG_TLM132_BOOT_MASK          ((uint16_t)0x3FF0)
/** @brief Number of potentially reported errors in TLM_132 when the CubeADCS is in bootloader */
#define CUBEADCS_DIAG_TLM132_ERR_BOOT_CNTS_NUM  ((uint8_t)0x0A)
/** @brief Number of potentially reported errors in TLM_132 when the CubeADCS is in ACP */
#define CUBEADCS_DIAG_TLM132_ERR_APP_CNTS_NUM   ((uint8_t)0x18)
/** @brief Number of potentially reported errors in TLM_135 */
#define CUBEADCS_DIAG_TLM135_ERR_CNTS_NUM       ((uint8_t)0x03)
/** @brief Number of potentially reported errors in TLM_224 */
#define CUBEADCS_DIAG_TLM224_ERR_CNTS_NUM       ((uint8_t)0x0F)
/** @brief Number of the different error handling logic cases that can be activated automatically */
#define CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM        ((uint8_t)0x11)

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

/*------------------------------------------------------------------------------ */
/*-------------------------- CUBEADCS DIAG/ERR TYPES---------------------------- */
/*------------------------------------------------------------------------------ */

/** @brief Enumeration of all errors related to the CubeADCS integration that the OBC keeps track of (in volatile manner) */
typedef enum tag_eCubeADCS_Common_Diag_Cnts {
    /* Communication request replies counters */
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_OK                        ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_ERR                       ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_CMD_ERR                   ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_LEN_WRT_ERR               ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_LEN_READ_ERR              ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_RX_TIMEOUT                ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_TX_TIMEOUT                ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_COMM_ERR                  ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_INV_DATA                  ,
    /* TLM 132 - ACP */
    eCUBEADCS_COMMON_DIAG_CNTS_CUBESENSE1_COMM_ERR            ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBESENSE2_COMM_ERR            ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBECONTROL_SIGNAL_COMM_ERR    ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBECONTROL_MOTOR_COMM_ERR     ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBEWHEEL1_COMM_ERR            ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBEWHEEL2_COMM_ERR            ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBEWHEEL3_COMM_ERR            ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBESTAR_COMM_ERR              ,
    eCUBEADCS_COMMON_DIAG_CNTS_MAGMETER_RANGE_ERR             ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM1_SRAM_OVERCURRENT_DET      ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM1_3V3_OVERCURRENT_DET       ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM1_SENSOR_BUSY_ERR           ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM1_SENSOR_DET_ERR            ,
    eCUBEADCS_COMMON_DIAG_CNTS_SUN_SENSOR_RANGE_ERR           ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM2_SRAM_OVERCURRENT_DET      ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM2_3V3_OVERCURRENT_DET       ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM2_SENSOR_BUSY_ERR           ,
    eCUBEADCS_COMMON_DIAG_CNTS_CAM2_SENSOR_DET_ERR            ,
    eCUBEADCS_COMMON_DIAG_CNTS_NADIR_SENSOR_RANGE_ERR         ,
    eCUBEADCS_COMMON_DIAG_CNTS_RATE_SENSOR_RANGE_ERR          ,
    eCUBEADCS_COMMON_DIAG_CNTS_WHEEL_SPEED_RANGE_ERR          ,
    eCUBEADCS_COMMON_DIAG_CNTS_CSS_ERR                        ,
    eCUBEADCS_COMMON_DIAG_CNTS_STARTRACKER_MATCH_ERR          ,
    eCUBEADCS_COMMON_DIAG_CNTS_STARTRACKER_OVERCURRENT_DET    ,
    /* TLM 132 - Bootloader */
    eCUBEADCS_COMMON_DIAG_CNTS_SRAM_LUP_ERR                   ,
    eCUBEADCS_COMMON_DIAG_CNTS_SRAM_LUP_ERR_REC               ,
    eCUBEADCS_COMMON_DIAG_CNTS_SD_CARD_INIT_ERR               ,
    eCUBEADCS_COMMON_DIAG_CNTS_SD_CARD_READ_ERR               ,
    eCUBEADCS_COMMON_DIAG_CNTS_SD_CARD_WRT_ERR                ,
    eCUBEADCS_COMMON_DIAG_CNTS_EXT_FLASH_ERR                  ,
    eCUBEADCS_COMMON_DIAG_CNTS_INT_FLASH_ERR                  ,
    eCUBEADCS_COMMON_DIAG_CNTS_EEPROM_ERR                     ,
    eCUBEADCS_COMMON_DIAG_CNTS_BOOT_REG_ERR                   ,
    eCUBEADCS_COMMON_DIAG_CNTS_COMM_RADIO_ERR                 ,
    /* TLM 135 */
    eCUBEADCS_COMMON_DIAG_CNTS_ADCS_CONFIG_LOAD_ERR           ,
    eCUBEADCS_COMMON_DIAG_CNTS_ORBIT_PARAM_LOAD_ERR           ,
    eCUBEADCS_COMMON_DIAG_CNTS_SYS_CONFIG_LOAD_ERR            ,
    /* TLM 224 */
    eCUBEADCS_COMMON_DIAG_CNTS_ORBIT_PARAM_INVALID_ERR        ,
    eCUBEADCS_COMMON_DIAG_CNTS_CONFIG_INVALID_ERR             ,
    eCUBEADCS_COMMON_DIAG_CNTS_CNTRL_MODE_CHG_INV_ERR         ,
    eCUBEADCS_COMMON_DIAG_CNTS_EST_CHG_INV_ERR                ,
    eCUBEADCS_COMMON_DIAG_CNTS_MAGNETIC_FIELD_DIFF_ERR        ,
    eCUBEADCS_COMMON_DIAG_CNTS_NODE_RECOVERY_ERR              ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBESENSE1_RUNTIME_ERR         ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBESENSE2_RUNTIME_ERR         ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBECONTROL_SIGNAL_RUNTIME_ERR ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBECONTROL_MOTOR_RUNTIME_ERR  ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBEWHEEL1_RUNTIME_ERR         ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBEWHEEL2_RUNTIME_ERR         ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBEWHEEL3_RUNTIME_ERR         ,
    eCUBEADCS_COMMON_DIAG_CNTS_CUBESTAR_RUNTIME_ERR           ,
    eCUBEADCS_COMMON_DIAG_CNTS_MAGNETOMETER_ERR               ,
    eCUBEADCS_COMMON_DIAG_CNTS_RATE_SENSOR_FAILURE_ERR        ,

    eCUBEADCS_COMMON_DIAG_CNTS_NUMBER

} eCubeADCS_Common_Diag_Cnts;

/** @brief Error counter type - counter ID vs counter VALUE */
typedef struct tag_CubeADCS_Diag_ErrCnts {
    uint8_t  u8Id;
    uint16_t u16Value;

} __attribute__((__packed__)) CubeADCS_Diag_ErrCnts_t;

/** @brief Error handling type - used to configure and keep track of the activation of the specific error handling logic */
typedef struct tag_CubeADCS_Diag_ErrHandlCnts {
    eCubeADCS_Common_Diag_Cnts eErrType;
    uint8_t u8ErrHandlActivationCnt;
    uint8_t u8MaxActivationAllowed;
    eCubeADCS_StdRply (*pErrHandlFunc)(uint8_t) ;
} __attribute__((__packed__)) CubeADCS_Diag_ErrHandlCnts_t;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/

/** @brief Storage of the counters, updated by the error handling and counting logic */
extern CubeADCS_Diag_ErrCnts_t CubeADCS_Err_Cnts [ eCUBEADCS_COMMON_DIAG_CNTS_NUMBER ];

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/

/** @brief Handle MODERATE and HIGH severity errors reported by CubeADCS
 *
 *  @note TESTED:eCUBEADCS_COMMON_DIAG_CNTS_NODE_RECOVERY_ERR
 *               eCUBEADCS_COMMON_DIAG_CNTS_MAGMETER_RANGE_ERR
 *               eCUBEADCS_COMMON_DIAG_CNTS_MAGNETOMETER_ERR
 */
void CubeADCS_ErrHandl(void);

/** @brief Activate specific error handling logic
 *
 *  @param[in] u8ErrNum the error number to activate error handling logic for
 *
 *  @retval true on successful activation
 *  @retval false on un-successful activation
 */
bool cubeadcs_errhandl_activate(uint8_t u8ErrNum);

/** @brief Clear a given error handling logic activation count
 *
 *  @param[in] u8ErrHandlCntr error handling logic id
 */
void CubeADCS_ErrHandl_ClrErrHandlCntrActivCnt(uint8_t u8ErrHandlCntr);

/** @brief Get the activation count of an error handling logic
 *
 *  @param[in] u8ErrHandlCntr error handling logic id
 *
 *  @return pointer to the activation count
 */
uint8_t *CubeADCS_ErrHandl_GetErrHandlCntrActivCnt(uint8_t u8ErrHandlCntr);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif    /* CUBEADCS_ERR_HANDL_H_ */
/* ******************************************************************************************* */
