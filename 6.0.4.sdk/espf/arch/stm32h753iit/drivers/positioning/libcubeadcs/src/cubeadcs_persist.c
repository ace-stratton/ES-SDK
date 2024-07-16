/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_persist.c
 * @brief    Reading and checking data from the NVM.
 *
 * @}
 */

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "cubeadcs_persist.h"

#include "assertions.h"
#include "nvm/inc/nvm.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/



/*
*********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void cubeadcs_persist_get_nvm_stored_status(CubeADCS_Status_t *psDst)
{
	CRIT_ASSERT(NULL != psDst);

	cubeadcs_status_t sTmp_status;

	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_STATUS, &sTmp_status);

	psDst->Commissioning = sTmp_status.commissioning;
	psDst->NodeStatus.u8RawData = sTmp_status.node_status;
	psDst->RunTimeLatchedErrors.u16RawData = sTmp_status.runtime_latched_errors;
}

void cubeadcs_persist_set_nvm_stored_status(CubeADCS_Status_t *psSrc)
{
	CRIT_ASSERT(NULL != psSrc);

	cubeadcs_status_t sTmp_status;

	sTmp_status.commissioning = psSrc->Commissioning;
	sTmp_status.node_status = psSrc->NodeStatus.u8RawData;
	sTmp_status.runtime_latched_errors = psSrc->RunTimeLatchedErrors.u16RawData;

	Nvm_SetBlockById(NVM_BLOCK_CUBEADCS_STATUS, &sTmp_status, NVMSETBLOCK_STORE_IMMEDIATELY);
}

bool cubeadcs_persist_is_err_handl_en(void)
{
	/* Check if error handling is enabled */
	cubeadcs_err_handl_cfg_t is_err_handl_en;

	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_ERR_HANDL_CONFIG, &is_err_handl_en);

	if ( SAFE_TRUE != is_err_handl_en.en_cubeadcs_err_handl )
	{
		return false;
	}
	else
	{
		return true;
	}
}

void cubeadcs_persist_load_sys_state_cfg(CubeADCS_Cfg_t *psDst)
{
	cubeADCS_sys_state_cfg_t sTmp_state_cfg;
	CRIT_ASSERT(NULL != psDst);

	cubeadcs_persist_get_nvm_sys_state_cfg(&sTmp_state_cfg);

	for (uint8_t i = 0; i < eCUBEADCS_CFGTYPE_NUMBER; i ++)
	{
		psDst[i].eCfgType 						 = sTmp_state_cfg.asCubeADCS_SysStates[i].eCfgType;
		psDst[i].eCntrlMask 				 	 = sTmp_state_cfg.asCubeADCS_SysStates[i].eCntrlMask;
		psDst[i].eEstMode 						 = sTmp_state_cfg.asCubeADCS_SysStates[i].eEstMode;
		psDst[i].eRunMask 						 = sTmp_state_cfg.asCubeADCS_SysStates[i].eRunMask;
		psDst[i].uAdditionalLogic 				 = sTmp_state_cfg.asCubeADCS_SysStates[i].uAdditionalLogic;
		psDst[i].uNodePwrMask.CubeControl_Signal = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeControl_Signal;
		psDst[i].uNodePwrMask.CubeControl_Motor  = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeControl_Motor;
		psDst[i].uNodePwrMask.CubeSense1         = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeSense1;
		psDst[i].uNodePwrMask.CubeSense2         = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeSense2;
		psDst[i].uNodePwrMask.CubeStar           = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeStar;
		psDst[i].uNodePwrMask.CubeWheel1         = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel1;
		psDst[i].uNodePwrMask.CubeWheel2         = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel2;
		psDst[i].uNodePwrMask.CubeWheel3         = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel3;
		psDst[i].uNodePwrMask.MotorPwr           = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.MotorPwr;
		psDst[i].uNodePwrMask.GPSPwr             = sTmp_state_cfg.asCubeADCS_SysStates[i].uNodePwrMask.GPSPwr;
	}

}
void cubeadcs_persist_get_nvm_sys_state_cfg(cubeADCS_sys_state_cfg_t *psDst)
{
	CRIT_ASSERT(NULL != psDst);

	cubeADCS_sys_state_cfg_t sTmp_state_cfg;

	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_SYS_STATE_CFG, &sTmp_state_cfg);

	memcpy(psDst, &sTmp_state_cfg, sizeof(cubeADCS_sys_state_cfg_t));
}

bool cubeadcs_persist_set_nvm_sys_state_cfg(cubeADCS_sys_state_cfg_t *psSrc)
{
	bool res = true;
	CRIT_ASSERT(NULL != psSrc);

	cubeADCS_sys_state_cfg_t sTmp_state_cfg;

	memcpy(&sTmp_state_cfg, psSrc, sizeof(cubeADCS_sys_state_cfg_t));

	Nvm_SetBlockById(NVM_BLOCK_CUBEADCS_SYS_STATE_CFG, &sTmp_state_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

	memset(&sTmp_state_cfg, 0x00, sizeof(cubeADCS_sys_state_cfg_t));

	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_SYS_STATE_CFG, &sTmp_state_cfg);

	if(memcmp(&sTmp_state_cfg, psSrc, sizeof(cubeADCS_sys_state_cfg_t)))
	{
		res = true;
	}
	else
	{
		res = false;
	}

	return res;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/* ******************************************************************************************* */
