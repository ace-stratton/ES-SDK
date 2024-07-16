/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_COMMON_TYPES_H_
#define CUBEADCS_COMMON_TYPES_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_common_types.h
 * @brief    Commonly used types throughout the cubeadcs code base
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "cubeadcs_driver.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/

typedef enum tag_eCubeADCS_Commissioning
{
    eCUBEADCS_STEP_00_NONE,
    eCUBEADCS_STEP_01_INITIAL_ANG_RATE_EST,
    eCUBEADCS_STEP_02_DETUMBLING,
    eCUBEADCS_STEP_03_MAG_DEPLOYMENT,
    eCUBEADCS_STEP_04_MAG_CALIBRATION,
    eCUBEADCS_STEP_05_ANG_RATE_AND_PITCH_RATE_EST,
    eCUBEADCS_STEP_06_Y_WHEEL_RAMP_UP_TEST,
    eCUBEADCS_STEP_07_Y_MOMENTUM_MODE_COMMISSIONING,
    eCUBEADCS_STEP_08_SUN_NADIR_COMMISSIONING,
    eCUBEADCS_STEP_09_CUBESTAR_COMMISSIONING,
    eCUBEADCS_STEP_10_WHEELS_COMMISSIONING,
    eCUBEADCS_STEP_11_SUN_TRACKING,
    eCUBEADCS_STEP_12_GROUND_TRACKING,
    eCUBEADCS_STEP_NUMBER,

} eCubeADCS_Commissioning_t;

typedef union tag_CubeADCS_NodeStatus
{
    struct {
            uint8_t  Signal     :1;
            uint8_t  Motor      :1;
            uint8_t  Sense1     :1;
            uint8_t  Sense2     :1;
            uint8_t  CubeStar   :1;
            uint8_t  Wheel1     :1;
            uint8_t  Wheel2     :1;
            uint8_t  Wheel3     :1;
        } Node;
        uint8_t u8RawData;
} __attribute__((__packed__)) CubeADCS_NodeStatus_t;

typedef union tag_CubeADCS_RunTimeErr
{
    struct {
        uint16_t NodeRecoveryErr :1;
        uint16_t RangeErr        :1;
        uint16_t RateSensFailure :1;
        uint16_t MagnetometerErr :1;
        uint16_t OrbitParamsErr  :1;
        uint16_t ConfigInvalid   :1;
        uint16_t CntrlModeChgErr :1;
        uint16_t EstModeChgErr   :1;
        uint16_t SysStateChgErr  :1;
        uint16_t Res             :7;
    } Err;
    uint16_t u16RawData;
} __attribute__((__packed__)) CubeADCS_RunTimeErr_t;

typedef struct tag_CubeADCS_HCheckCommStatus_t
{
    eCubeADCS_Comm_Status_t TLM128;
    eCubeADCS_Comm_Status_t TLM130;
    eCubeADCS_Comm_Status_t TLM132;
    eCubeADCS_Comm_Status_t TLM135;
    eCubeADCS_Comm_Status_t TLM224;
    eCubeADCS_Comm_Status_t TLM197;
    eCubeADCS_Comm_Status_t TLM129;

} __attribute__((__packed__)) CubeADCS_HCheckCommStatus_t;

typedef struct tag_CubeADCS_Status
{
    eCubeADCS_Commissioning_t   Commissioning;
    CubeADCS_NodeStatus_t       NodeStatus;
    CubeADCS_RunTimeErr_t       RunTimeLatchedErrors;
    CubeADCS_HCheckCommStatus_t CommStatus;

} __attribute__((__packed__)) CubeADCS_Status_t;
/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_COMMON_TYPES_H_ */
