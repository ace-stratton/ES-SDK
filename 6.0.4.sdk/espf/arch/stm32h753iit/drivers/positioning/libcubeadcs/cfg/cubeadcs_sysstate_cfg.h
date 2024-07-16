/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CUBEADCS_SYSSTATE_CFG_H_
#define CUBEADCS_SYSSTATE_CFG_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_sysstate_cfg.h
 * @brief    Configuration and types of the ADCS system state.
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/

#include "../inc/cubeadcs_tc_tlm_descr.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/


/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

/*------------------------------------------------------------------------------ */
/*-------------------------- CUBEADCS CONFIGURATION USE CASES------------------- */
/*------------------------------------------------------------------------------ */


typedef enum tag_eCubeADCS_Cfg
{
    eCUBEADCS_CFGTYPE_PWR_UP,
    eCUBEADCS_CFGTYPE_NORMAL_DETUMBLING,
	eCUBEADCS_CFGTYPE_Y_THOMSON,
	eCUBEADCS_CFGTYPE_Y_THOMSON_MEMS_RATE,
	eCUBEADCS_CFGTYPE_FAST_DETUMBLING,
	eCUBEADCS_CFGTYPE_VERY_FAST_DETUMBLING,
    eCUBEADCS_CFGTYPE_Y_MOMENTUM,
	eCUBEADCS_CFGTYPE_Y_MOMENTUM_FULL_STATE_EKF,
	eCUBEADCS_CFGTYPE_3AXIS,

    eCUBEADCS_CFGTYPE_SUN_TRACKING,
    eCUBEADCS_CFGTYPE_TARGET_TRACKING,

    eCUBEADCS_CFGTYPE_NO_CONTROL,
    eCUBEADCS_CFGTYPE_ATTITUDE_CHANGE,
    eCUBEADCS_CFGTYPE_ORBITAL_CHANGE,

	eCUBEADCS_CFGTYPE_GEO_TARGET_TRACKING,

    eCUBEADCS_CFGTYPE_NUMBER

} eCubeADCS_CfgType;

typedef union tag_uCubeADCS_CfgNodePwrMask
{
    struct {
        uint8_t CubeControl_Signal  : 1;
        uint8_t CubeControl_Motor   : 1;
        uint8_t CubeSense1          : 1;
        uint8_t CubeSense2          : 1;
        uint8_t CubeStar            : 1;
        uint8_t CubeWheel1          : 1;
        uint8_t CubeWheel2          : 1;
        uint8_t CubeWheel3          : 1;
        uint8_t MotorPwr            : 1;
        uint8_t GPSPwr              : 1;
        uint8_t Res                 : 6;
    };
    uint16_t raw;

} __attribute__((__packed__)) uCubeADCS_CfgNodwPwrMask_t;

typedef struct tag_CubeADCS_Cfg
{
    eCubeADCS_CfgType           		eCfgType;
    uCubeADCS_CfgNodwPwrMask_t  		uNodePwrMask;
    eCUBE_ADCS_TC_13_CONTROL_MODE_t 	eCntrlMask;
    eCUBE_ADCS_TC_14_ESTIMATION_MODE_t	eEstMode;
    eCUBE_ADCS_TC_10_RUNMODE_t   		eRunMask;
    uint8_t                             uAdditionalLogic;


} __attribute__((__packed__)) CubeADCS_Cfg_t;

typedef enum tag_eCubeADCS_AngVelValid
{
    eANGVEL_VALID_NONE = 0,
    eANGVEL_VALID_EST  = 1,
    eANGVEL_VALID_RATE = 2,
    eANGVEL_VALID_BOTH = 3,

} eCubeADCS_AngVelValid_t;


typedef enum tag_eCubeADCS_SysStateCfgStatus {
    eSYSSTATECFGSTATUS_OK          = 0,
    eSYSSTATECFGSTATUS_NEW_REQ     = 1,
    eSYSSTATECFGSTATUS_RUN_0       = 2,
    eSYSSTATECFGSTATUS_RUN_1       = 3,
    eSYSSTATECFGSTATUS_RUN_2       = 4,
    eSYSSTATECFGSTATUS_RUN_3       = 5,
    eSYSSTATECFGSTATUS_RUN_4       = 6,
    eSYSSTATECFGSTATUS_ERR         = 7,
    eSYSSTATECFGSTATUS_IN_PROGRESS = 8,

} eCubeADCS_SysStateCfgStatus_t;

typedef struct CubeADCS_SysSCfg_t {
    eCubeADCS_CfgType eReqCfg;
    eCubeADCS_SysStateCfgStatus_t eReqCfgStatus;

} __attribute__((__packed__))CubeADCS_SysSCfg_t;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/

/** @brief CubeADCS system states description array */
extern CubeADCS_Cfg_t asCubeADCS_SysStates[eCUBEADCS_CFGTYPE_NUMBER];


/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/
#endif    /* CUBEADCS_SYSSTATE_CFG_H_ */
/* ******************************************************************************************* */
