/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_GEN2_TYPES_H
#define CUBEADCS_GEN2_TYPES_H

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_types.h
 * @brief    Cubeadcs Generation 2 types used by the service
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "tctlmCubeComputerControlProgram8.h"
#include <cubeObc/cubeObc_bulkDataTransfer.h>
#include "SdMngr.h"


/** @brief maximum file name size in bytes */
#define CUBEADCS_GEN2_BDT_FILE_NAME_SZ (FF_MAX_LFN)

/** @brief maximum upload/download file size */
#define CUBEADCS_GEN2_FILE_SZ_LIMIT (50 * 1024 * 1024) // 50 MB

/** @brief file transfer context type */
typedef U32 cubeadcs_gen2_ft_ctx_t;

/** @brief bootloader file upload context type */
#define CUBEADCS_GEN2_BDT_CTX_FTP_BL ((cubeadcs_gen2_ft_ctx_t)0)

/** @brief application file upload context type */
#define CUBEADCS_GEN2_BDT_CTX_FTP_AP ((cubeadcs_gen2_ft_ctx_t)1)

/** @brief image file download context type */
#define CUBEADCS_GEN2_BDT_CTX_IMG_CC ((cubeadcs_gen2_ft_ctx_t)2)

/** @brief events file download context typee */
#define CUBEADCS_GEN2_BDT_CTX_EVT_CC ((cubeadcs_gen2_ft_ctx_t)3)

/** @brief telemetry file download context type */
#define CUBEADCS_GEN2_BDT_CTX_TLM_CC ((cubeadcs_gen2_ft_ctx_t)4)

/** @brief file context limit, used only for internal checks */
#define CUBEADCS_GEN2_BDT_CTX_MAX    ((cubeadcs_gen2_ft_ctx_t)5)


typedef struct
{
    cubeadcs_gen2_ft_ctx_t context;                     /**< file transfer context type */
    char file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ + 1]; /**< buffer to store the file name, +1 for null termination */
    FIL file_handle;                                    /**< File pointer */
    U32 file_seek_index;                                /**< File seek index for next frame to extract */
    U16 last_frame_size;                                /**< Size of the last frame requested by the lib */
    U8 frame_buffer[BDT_MAX_FRAME_SIZE];                /**< Buffer for a single frame of data */
} cubeadcs_gen2_file_context_t;


/** @brief System state change states */
typedef enum
{
    CUBEADCS_GEN2_SYS_STATE_CHANGE_SUCCESS,
    CUBEADCS_GEN2_SYS_STATE_CHANGE_ERROR,
    CUBEADCS_GEN2_SYS_STATE_CHANGE_IN_PROGRESS,

    CUBEADCS_GEN2_SYS_STATE_CHANGE_MAX
} cubeadcs_gen2_sys_state_change_status_t;

/** @brief Gen2 control modes groups */
typedef enum
{
    CUBEADCS_GEN2_CONTROL_GROUP_NO_CONTROL,
    CUBEADCS_GEN2_CONTROL_GROUP_DETUMB_AND_SPIN,
    CUBEADCS_GEN2_CONTROL_GROUP_GG,
    CUBEADCS_GEN2_CONTROL_GROUP_Y_MOMENTUM,
    CUBEADCS_GEN2_CONTROL_GROUP_XYZ_WHEEL,
    CUBEADCS_GEN2_CONTROL_GROUP_WHEEL_MANAGEMENET,
    CUBEADCS_GEN2_CONTROL_GROUP_USER,

    CUBEADCS_GEN2_CONTROL_GROUP_MAX

} cubeadcs_gen2_control_group_t;

/** @brief Gen2 estimation modes groups */
typedef enum
{
    CUBEADCS_GEN2_EST_GROUP_NO_EST,
    CUBEADCS_GEN2_EST_GROUP_GYRO,
    CUBEADCS_GEN2_EST_GROUP_MAG,
    CUBEADCS_GEN2_EST_GROUP_MAG_PITCH,
    CUBEADCS_GEN2_EST_GROUP_TRIAD,
    CUBEADCS_GEN2_EST_GROUP_FULL_STATE,
    CUBEADCS_GEN2_EST_GROUP_GYRO_EKF,
    CUBEADCS_GEN2_EST_GROUP_USER,

    CUBEADCS_GEN2_EST_GROUP_MAX

} cubeadcs_gen2_est_group_t;

/** @brief Control program type */
typedef enum
{
    CUBEADCS_GEN2_CONTROL_PROGRAM_TYPE_BOOTLOADER = 0,
    CUBEADCS_GEN2_CONTROL_PROGRAM_TYPE_APPLICATION = 1,

    CUBEADCS_GEN2_CONTROL_PROGRAM_TYPE_MAX = 2

} cubeadcs_gen2_control_program_type_t;

/** @brief Gen2 control modes and groups */
typedef struct
{
    TctlmCubeComputerControlProgram8_ConModeSelect control_mode;
    cubeadcs_gen2_control_group_t control_group;
} cubeadcs_gen2_control_mode_info_t;

/** @brief Gen2 estimation modes and groups */
typedef struct
{
    TctlmCubeComputerControlProgram8_EstModeSelect estimator_type;
    cubeadcs_gen2_est_group_t estimator_group;
} cubeadcs_gen2_estimator_mode_info_t;

/** @brief Reference parameters for some of Gen2's control modes */
typedef struct
{
    float ref_param_1;   /*!< Roll, Latitude or X component of an ECI pointing vector */
    float ref_param_2;   /*!< Pitch, Longitude or Y component of an ECI pointing vector */
    float ref_param_3;   /*!< Yaw, Altitude or Z component of an ECI pointing vector */
} cubeadcs_gen2_ref_params_t;

/** @brief System state core description of Gen2 */
typedef struct
{
    TctlmCubeComputerCommon3_PowerState pwr_state;
    TctlmCubeComputerControlProgram8_ConModeSelect cntrl_mode;
    TctlmCubeComputerControlProgram8_EstModeSelect est_mode_main;
    TctlmCubeComputerControlProgram8_EstModeSelect est_mode_backup;
} cubeadcs_gen2_sys_state_core_t;

/** @brief System state description of Gen2 */
typedef struct
{
    cubeadcs_gen2_sys_state_core_t sys_state_core_cfg;
    cubeadcs_gen2_ref_params_t ref_params;
    uint8_t req_state_id;
} cubeadcs_gen2_sys_state_t;

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif /* CUBEADCS_GEN2_TYPES_H */

/* ******************************************************************************************* */
