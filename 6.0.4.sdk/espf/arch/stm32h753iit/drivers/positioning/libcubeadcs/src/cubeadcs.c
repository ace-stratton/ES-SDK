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
 * @file     cubeadcs.c
 * @brief    The main source file is the place of residence of the initialisation logic,
 * 			 the main task, functions related to getting/setting of the ADCS mode,
 * 			 control mode, estimation mode, etc. (commonly referred here as ADCS system state),
 * 			 functions related to sending commands and so on.
 *
 * @}
 */

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/

#include "AppTasks.h"
#include "TaskMonitor.h"

#include "../inc/cubeadcs.h"
#include "../inc/cubeadcs_errhandl.h"
#include "../inc/cubeadcs_usercmds.h"
#include "../cfg/cubeadcs_cfg.h"
#include "datacache.h"
#include "conops.h"
#include "nvm/inc/nvm.h"

#include "assertions.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
/** @brief Time to wait for the bootloader to load and start the ACP */
#define CUBEADCS_PWR_UP_TO_APP_TIME_S               ((uint8_t)0x0A)
/** @brief ID of the communication counters */
#define CUBEADCS_DIAG_UPDATE_COMM_ID                ((uint8_t)0x00)
/** @brief Retry number when sending a TC */
#define CUBEADCS_RTRY_TC_CNT                        ((uint8_t)5)
/** @brief Conversion multiplier from degrees to radians */
#define CUBEADCS_TO_RAD_CONV                        ((float)(M_PI / 180.0F))
/** @brief Conversion multiplier from radians to degrees */
#define CUBEADCS_TO_DEG_CONV                        ((float)(180.0F / M_PI))
/** @brief Size of the buffer used during the validation check */
#define CUBEADCS_LOCAL_BUFF_OP_STATUS_CHECK			((uint8_t)0x09)


/** @brief System state change check - System state change start value */
#define CUBEADCS_SYS_STATE_CHANGE_START			((uint8_t)0x00)
/** @brief System state change check - CubeADCS run mode is set */
#define CUBEADCS_SYS_STATE_RUN_MODE_SET			((uint8_t)0x01)
/** @brief System state change check - Necessary CubeADCS nodes are enabled */
#define CUBEADCS_SYS_STATE_NODE_PWR_SET			((uint8_t)0x02)
/** @brief System state change check - CubeADCS estimation mode is set */
#define CUBEADCS_SYS_STATE_EST_MODE_SET			((uint8_t)0x04)
/** @brief System state change check - CubeADCS control mode is set */
#define CUBEADCS_SYS_STATE_CNTRL_MODE_SET		((uint8_t)0x08)
/** @brief System state change check - System state change is successful */
#define CUBEADCS_SYS_STATE_CHANGE_SUCCESSFUL	((uint8_t)0x0F)

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

if_sys_mod_t cube_adcs_module_configuration = {
    .init = cube_adcs_init,
    .run = cube_adcs_run,
    .stop = cube_adcs_stop,
    .deinit = cube_adcs_deinit,
};


/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
/** @brief CubeADCS main task handle */
static       osThreadId_t   CubeADCS_Task_TaskHandle;
/** @brief CubeADCS main task attributes */
static const osThreadAttr_t CubeADCS_Task_attributes = {
  .name = "fs_cubeadcs_task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048
};

/** @brief Mutex to control access to the communication channel to CubeADCS */
static osMutexId_t cubeadcs_comm_mutex;
/** @brief Mutex attributes */
static const osMutexAttr_t CubeADCSComm_Mutex_attr = {
  "CubeADCSCommMutex",
  osMutexRecursive | osMutexPrioInherit,
  NULL,
  0U
};

/** @brief Mutex to control access to operational status data from CubeADCS */
static osMutexId_t cubeadcs_data_mutex;
/** @brief Mutex attributes */
static const osMutexAttr_t CubeADCSData_Mutex_attr = {
  "CubeADCSDataMutex",
  osMutexRecursive | osMutexPrioInherit,
  NULL,
  0U
};

/** @brief Local cache for the operational status */
static CubeADCS_Op_Status_t CubeADCS_OpStatus;
/** @brief Local cache for the current main state machine state */
static eCubeADCS_State_t CubeADCS_State;
/** @brief Local cache for node power status */
static CubeADCS_TLM197_t sNodeCntrlStatus;
/** @brief Local cache for TLM128 */
static CubeADCS_TLM128_t sResult_TLM128;
/** @brief Local cache for TLM197 */
static CubeADCS_TLM197_t sResult_TLM197;
/** @brief Local cache for the response size of a command request */
static uint16_t u16LocalCmdRespSize;

/** @brief Array of the commands context used during the INIT state */
static CubeADCS_CmdCfg_t aInitState[ eCUBEADCS_INIT_STATE_CMD_ID_NUM ] =
{
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_128,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&sResult_TLM128,
                .u16CmdResDstSize   =   CUBEADCS_TLM128_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        }
};

/** @brief Array of the commands context used during the IDLE state */
static CubeADCS_CmdCfg_t aHealthCheckState[ eCUBEADCS_IDLE_STATE_CMD_ID_NUM ] =
{
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_128,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&sResult_TLM128,
                .u16CmdResDstSize   =   CUBEADCS_TLM128_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        },
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_129,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&CubeADCS_OpStatus.State.boot_status,
                .u16CmdResDstSize   =   CUBEADCS_TLM129_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        },
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_130,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&CubeADCS_OpStatus.State.prog_status,
                .u16CmdResDstSize   =   CUBEADCS_TLM130_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        },
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_132,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&CubeADCS_OpStatus.State.State_ADCS,
                .u16CmdResDstSize   =   CUBEADCS_TLM132_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        },
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_224,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&CubeADCS_OpStatus.State.State2_ADCS,
                .u16CmdResDstSize   =   CUBEADCS_TLM224_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        },
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_197,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&sResult_TLM197,
                .u16CmdResDstSize   =   CUBEADCS_TLM197_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        },
        {
                .u8CmdID            =   eCUBEADCS_CMD_ID_135,
                .pu8CmdData         =   NULL,
                .u16CmdDataSize     =   0,
                .pvCmdResDst        =   (void *)&CubeADCS_OpStatus.State.State_Err,
                .u16CmdResDstSize   =   CUBEADCS_TLM135_LEN,
                .u16CmdResSize      =   &u16LocalCmdRespSize,
        }
};

/** @brief Local cache to make time based decisions */
static uint32_t u32BaseTime;
/** @brief Local cache of the current ADCS system configuration */
static CubeADCS_SysSCfg_t eADCSCfg;

/** @brief Roll angle that is to be used in the orbital change mode
 *
 *  @note  Unit format is DEGREES * 100 to fit with CubeADCS desired format
 */
static int16_t orbital_change_roll  = 0;
/** @brief Pitch angle that is to be used in the orbital change mode
 *
 *  @note  Unit format is DEGREES * 100 to fit with CubeADCS desired format
 */
static int16_t orbital_change_pitch = 0;
/** @brief Yaw angle that is to be used in the orbital change mode
 *
 *  @note  Unit format is DEGREES * 100 to fit with CubeADCS desired format
 */
static int16_t orbital_change_yaw   = 0;

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

static void                         fs_cubeadcs_init_memory(void);
static void                         fs_cubeadcs_init_hw(void);
static void                         fs_cubeadcs_init_os(void);
static void							fs_cubeadcs_deinit_hw(void);
static void                         fs_cubeadcs_task(void *argument);
static void                         fs_CubeADCS_Init_Diag_Counters(void);
static void                         fs_CubeADCS_Diag_Update_Counters(uint8_t cmdID, eCubeADCS_Comm_Status_t comm_status);
static void                         fs_CubeADCS_SetRWheelsRPM(CubeADCS_RWheels_Speed_t sRPM);
static void                         fs_CubeADCS_SetCommandedAngles(CubeADCS_Command_Angles_t sCommandAngles);
static void                         fs_CubeADCS_UpdateHCheckCommStatuses(uint8_t u8CmdID);
static eCubeADCS_StdRply            fs_CubeADCS_ApplyNewSysStateCfg(eCubeADCS_CfgType eReqCfg);
static void 						fs_cubeadcs_init_op_status(void);
static void 						fs_cubeadcs_set_node_type(eCubeADCS_Mode_t eMode);
static eCubeADCS_Comm_Status_t 		fs_cubeadcs_get_last_comm_status(void);
static bool 						fs_cubeadcs_lock_comm_access(uint32_t u32WaitTimeMS);
static bool 						fs_cubeadcs_unlock_comm_access();
static bool							fs_cubeadcs_is_boot_commanded(void);
static void 						fs_cubeadcs_update_adcs_sys_state_cfg_status(eCubeADCS_SysStateCfgStatus_t eStatus);
static bool 						fs_cubeadcs_set_sm_state(eCubeADCS_State_t eReqState);
static uint8_t                      fs_cubeadcs_execute_custom_logic(eCubeADCS_CfgType eADCSCfgType);
static uint8_t                      fs_cubeadcs_attitude_change_mode_check();
static uint8_t                      fs_cubeadcs_orbital_change_mode_check();
static safe_bool_t                  fs_cubeadcs_get_simulation_mode_en_status(void);

/*
*********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

mod_op_status_id_t cube_adcs_init(sys_init_level_id_t level){
    mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

    // Eventually, to split the initialisation into the different levels
    if(level ==  INIT_MEM)
    {
        fs_cubeadcs_init_memory();
        ret = STATUS_OK;
    }
    else if (level ==  INIT_HW)
    {
        fs_cubeadcs_init_hw();
        ret = STATUS_OK;
    }
    else if (level ==  INIT_OS)
    {
        fs_cubeadcs_init_os();
        task_mon_set_task_policy(TASK_MONITOR_CUBEADCS, TASK_MON_POLICY_MONITOR);
        task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_FHANDL, TASK_MON_POLICY_MONITOR);
        ret = STATUS_OK;
    }
    else
    {
        ret = STATUS_NOT_SUPPORTED;;
    }
    return ret;
}

mod_op_status_id_t cube_adcs_run(){
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}

mod_op_status_id_t cube_adcs_stop(){
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}

mod_op_status_id_t cube_adcs_deinit(sys_init_level_id_t level){
	mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

	switch(level)
	{
	case INIT_MEM:
		ret = STATUS_NOT_SUPPORTED;
		break;
	case INIT_HW:

		fs_cubeadcs_deinit_hw();

		ret = STATUS_OK;

		break;
	case INIT_OS:

		task_mon_set_task_policy(TASK_MONITOR_CUBEADCS, TASK_MON_POLICY_DONT_CARE);
		task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_FHANDL, TASK_MON_POLICY_DONT_CARE);

		ret = STATUS_OK;

		break;
	default:
		ret = STATUS_NOT_SUPPORTED;
		break;
	}

    return ret;
}

void CubeADCS_TaskInit()
{
    /* Create the CubeADCS related TASK */
    CubeADCS_Task_TaskHandle = osThreadNew(fs_cubeadcs_task, NULL, &CubeADCS_Task_attributes);
    CRIT_ASSERT( CubeADCS_Task_TaskHandle );

    TaskMonitor_TaskInitialized(TASK_MONITOR_CUBEADCS);
}

void CubeADCS_DelayTask(uint32_t delay)
{
	uint32_t u32OsWaitRes;

	u32OsWaitRes = osThreadFlagsWait(0x00000001, osFlagsWaitAny, delay);

	(void)u32OsWaitRes;
}

eCubeADCS_Commissioning_t cubeadcs_get_cms_status(void)
{
	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	return op_status.Status.Commissioning;
}

eCubeADCS_StdRply cubeadcs_set_cms_status(const eCubeADCS_Commissioning_t newStatus)
{
	CubeADCS_Status_t sAdcsTmpStatus;

	eCubeADCS_StdRply res = eCUBEADCS_STDRPLY_ERR;

    if (newStatus < eCUBEADCS_STEP_NUMBER)
    {
    	cubeadcs_persist_get_nvm_stored_status(&sAdcsTmpStatus);

    	sAdcsTmpStatus.Commissioning = newStatus;

    	CubeADCS_OpStatus.Status.Commissioning = sAdcsTmpStatus.Commissioning;

    	cubeadcs_persist_set_nvm_stored_status(&sAdcsTmpStatus);

        res = eCUBEADCS_STDRPLY_OK;
    }
    else
        res = eCUBEADCS_STDRPLY_INVALID_ARGS;

    return res;
}

eCubeADCS_State_t CubeADCS_GetState(void)
{
    return CubeADCS_State;
}

void CubeADCS_PREPCmd(CubeADCS_CmdCfg_t *sCmd, uint8_t   u8CmdID, uint8_t  *pu8CmdData, uint16_t  u16CmdDataSize,
                        void     *pvCmdResDst, uint16_t  u16CmdResDstSize, uint16_t *u16CmdResSize)
{
    sCmd->pu8CmdData       = pu8CmdData;
    sCmd->pvCmdResDst      = pvCmdResDst;
    sCmd->u16CmdDataSize   = u16CmdDataSize;
    sCmd->u16CmdResDstSize = u16CmdResDstSize;
    sCmd->u16CmdResSize    = u16CmdResSize;
    sCmd->u8CmdID          = u8CmdID;
}

eCubeADCS_Mode_t CubeADCS_GetNodeType(void)
{
	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	return CubeADCS_OpStatus.Mode;
}

eCUBE_ADCS_TC_13_CONTROL_MODE_t CubeADCS_GetCntrlMode(void)
{
	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	return (eCUBE_ADCS_TC_13_CONTROL_MODE_t)op_status.State.State_ADCS.TLM.App.Byte0.Data.Control_Mode;
}

void CubeADCS_SetControlMode(eCUBE_ADCS_TC_13_CONTROL_MODE_t eCntlMode, uint16_t u16TimeOut)
{
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;
    CubeADCS_TC_13_t sData;

    CubeADCS_CmdCfg_t sCmdStruct;

    sData.ControlMode = eCntlMode;
    sData.u16Timeout  = u16TimeOut;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_13, (uint8_t *)&sData, CUBEADCS_TC_13_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH);
}

eCUBE_ADCS_TC_14_ESTIMATION_MODE_t CubeADCS_GetEstMode(void)
{
	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	return (eCUBE_ADCS_TC_14_ESTIMATION_MODE_t)CubeADCS_OpStatus.State.State_ADCS.TLM.App.Byte0.Data.Att_Est_Mode;
}

void CubeADCS_SetEstimationMode(eCUBE_ADCS_TC_14_ESTIMATION_MODE_t eEstMode)
{
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;
    eCUBE_ADCS_TC_14_ESTIMATION_MODE_t eNewMode;

    CubeADCS_CmdCfg_t sCmdStruct;

    eNewMode = eEstMode;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_14, (uint8_t *)&eNewMode, CUBEADCS_TC_14_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH);
}

eCUBE_ADCS_TC_10_RUNMODE_t CubeADCS_GetADCSRunMode(void)
{
	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	return (eCUBE_ADCS_TC_10_RUNMODE_t)CubeADCS_OpStatus.State.State_ADCS.TLM.App.Byte1.Data.ADCS_Run_Mode;
}

void CubeADCS_SetADCSRunMode(eCUBE_ADCS_TC_10_RUNMODE_t eRunMode)
{
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;
    eCUBE_ADCS_TC_10_RUNMODE_t eNewRunMode;

    CubeADCS_CmdCfg_t sCmdStruct;

    eNewRunMode = eRunMode;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_10, (uint8_t *)&eNewRunMode, CUBEADCS_TC_10_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH);
}

void cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC_11_NODES_t node, eCUBE_ADCS_TC_11_PWR_STATES_t state)
{
    uint8_t  u8Data[CUBEADCS_TC_11_BYTE_LEN] = {0x00, 0x00, 0x00};

    uint16_t u16Resp;
    uint16_t u16RespSize;

    CubeADCS_CmdCfg_t sCmdStruct;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_11, &u8Data[0], CUBEADCS_TC_11_BYTE_LEN, (void *)&u16Resp, CUBEADCS_TC_LEN, &u16RespSize);

    /* Here we clear the two bits responsible for the node and then set them to the requested value (going from right to left)
     * - we clear the two bits corresponding to the node in the 3 bytes responsible for the power control
     * - we logically OR this value with the 0x00AAAAAA pattern, this pattern corresponds to the power control set to no change
     * - we logically OR with the result with the node state bits
     * - ...there may be a better way ...
     * */
    uint32_t u32PwrData = ((uint32_t)state << ((uint32_t)node * 2)) | ( 0x00AAAAAA & ~((uint32_t)0x03 << ((uint32_t)node * 2)) );

    for ( uint8_t u8Indx = 0; u8Indx < CUBEADCS_TC_11_BYTE_LEN; ++u8Indx )
    {
        *(sCmdStruct.pu8CmdData + u8Indx) = *(((uint8_t *)&u32PwrData) + u8Indx); /* Each node occupies 2 bits for the state - see TC 11 */
    }

    /* Update the node control status on success */
    if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH))
    {
        sNodeCntrlStatus.u32RawData = sResult_TLM197.u32RawData | (((uint32_t)state << ((uint32_t)node * 2)) << 8); /* The last shift is needed because the cmdID is part of the structure */
    }
}

eCubeADCS_StdRply CubeADCS_GetAngularRate(CubeADCS_AngRateFormatted_t *sAngRate, eCubeADCS_AngRateType_t eMeasType)
{
	CRIT_ASSERT(sAngRate != NULL);
	CRIT_ASSERT(eMeasType < eCUBEADCS_ANGRATETYPE_NUM);

    eCubeADCS_AngVelValid_t u8CanRead;
    eCUBE_ADCS_TC_56_MTM_MODE_t	eUsedMtmSMode;

    float fWA0;
    float fWB0;

    eCubeADCS_StdRply eRetVal;

    uint16_t u16CmdRspLen;
    CubeADCS_CmdCfg_t sCmdStruct_147;
    CubeADCS_CmdCfg_t sCmdStruct_155;

    CubeADCS_TLM147_t sCmdRsp147;
    CubeADCS_TLM155_t sCmdRsp155;

    fWA0 = 0.0F;
    fWB0 = 0.0F;
    u8CanRead = eANGVEL_VALID_NONE;
    eRetVal = eCUBEADCS_STDRPLY_ERR;

    CubeADCS_PREPCmd(&sCmdStruct_147, eCUBEADCS_CMD_ID_147, NULL, 0, (void *)&sCmdRsp147, CUBEADCS_TLM147_LEN, &u16CmdRspLen);
    CubeADCS_PREPCmd(&sCmdStruct_155, eCUBEADCS_CMD_ID_155, NULL, 0, (void *)&sCmdRsp155, CUBEADCS_TLM155_LEN, &u16CmdRspLen);

    eUsedMtmSMode = CubeADCS_GetMTMSamplingMode();

    /* Check if we can actually read data from the sensors/estimators */
    if ( eCUBEADCS_TC56_MAIN_MTM_MOTOR_MCU == eUsedMtmSMode )
    {
        if ( eCUBE_ADCS_TC11_STATE_ON == CubeADCS_GetADCSNodePwrState(eCUBE_ADCS_TC11_NODES_CUBECONTROL_MOTOR) )
        {
            u8CanRead |= eANGVEL_VALID_RATE;

            if ( eCUBE_ADCS_TC_14_ESTIMATIONMODE_NO_EST != CubeADCS_GetEstMode() )
            	u8CanRead |= eANGVEL_VALID_EST;
        }
    }
    else
    {
    	if ( eCUBE_ADCS_TC11_STATE_ON == CubeADCS_GetADCSNodePwrState(eCUBE_ADCS_TC11_NODES_CUBECONTROL_SIGNAL) )
    		if ( eCUBE_ADCS_TC_14_ESTIMATIONMODE_NO_EST != CubeADCS_GetEstMode() )
    			u8CanRead |= eANGVEL_VALID_EST;

    	if ( eCUBE_ADCS_TC11_STATE_ON == CubeADCS_GetADCSNodePwrState(eCUBE_ADCS_TC11_NODES_CUBECONTROL_MOTOR) )
    		u8CanRead |= eANGVEL_VALID_RATE;
    }

    /* Read data based on the request and sensors / estimation availability */
    switch (eMeasType)
    {
        case eCUBEADCS_ANGRATETYPE_EST:
        {
            if ( eANGVEL_VALID_EST == (u8CanRead & eANGVEL_VALID_EST) ) {
                if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct_147, eCUBEADCS_COMMREQTYPE_FETCH) ) {
                    sAngRate->fX = ( (float)sCmdRsp147.AngRate.i16X * 0.01F ) * CUBEADCS_TO_RAD_CONV;
                    sAngRate->fY = ( (float)sCmdRsp147.AngRate.i16Y * 0.01F ) * CUBEADCS_TO_RAD_CONV;
                    sAngRate->fZ = ( (float)sCmdRsp147.AngRate.i16Z * 0.01F ) * CUBEADCS_TO_RAD_CONV;

                    eRetVal = eCUBEADCS_STDRPLY_OK;
                }
            }

            break;
        }
        case eCUBEADCS_ANGRATETYPE_RATE:
        {
            if ( eANGVEL_VALID_RATE == (u8CanRead & eANGVEL_VALID_RATE) ) {
                if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct_155, eCUBEADCS_COMMREQTYPE_FETCH) ) {
                    sAngRate->fX = ( (float)sCmdRsp155.AngRate.i16X * 0.01F ) * CUBEADCS_TO_RAD_CONV;
                    sAngRate->fY = ( (float)sCmdRsp155.AngRate.i16Y * 0.01F ) * CUBEADCS_TO_RAD_CONV;
                    sAngRate->fZ = ( (float)sCmdRsp155.AngRate.i16Z * 0.01F ) * CUBEADCS_TO_RAD_CONV;

                    eRetVal = eCUBEADCS_STDRPLY_OK;
                }
            }

            break;
        }
        case eCUBEADCS_ANGRATETYPE_WEIGHTED:
        {
            if ( eANGVEL_VALID_EST == (u8CanRead & eANGVEL_VALID_EST) ) {
                if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct_147, eCUBEADCS_COMMREQTYPE_FETCH) )
                {
                    fWA0 = 1.0F;

                    eRetVal = eCUBEADCS_STDRPLY_OK;
                }
            }

            if ( eANGVEL_VALID_RATE == (u8CanRead & eANGVEL_VALID_RATE) ) {
                if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct_155, eCUBEADCS_COMMREQTYPE_FETCH) )
                {
                    if ( eCUBEADCS_STDRPLY_OK == eRetVal ) {
                        fWA0 = 0.8F;
                        fWB0 = 0.2F;
                    }
                    else
                        fWB0 = 1.0F;

                    eRetVal = eCUBEADCS_STDRPLY_OK;
                }
            }

            if ( eCUBEADCS_STDRPLY_OK == eRetVal ) {
                sAngRate->fX = (fWA0 * ((float)sCmdRsp147.AngRate.i16X * 0.01F)) + (fWB0 * ((float)sCmdRsp155.AngRate.i16X * 0.01F));
                sAngRate->fY = (fWA0 * ((float)sCmdRsp147.AngRate.i16Y * 0.01F)) + (fWB0 * ((float)sCmdRsp155.AngRate.i16Y * 0.01F));
                sAngRate->fZ = (fWA0 * ((float)sCmdRsp147.AngRate.i16Z * 0.01F)) + (fWB0 * ((float)sCmdRsp155.AngRate.i16Z * 0.01F));

                sAngRate->fX *= CUBEADCS_TO_RAD_CONV;
                sAngRate->fY *= CUBEADCS_TO_RAD_CONV;
                sAngRate->fZ *= CUBEADCS_TO_RAD_CONV;
            }

            break;
        }
        default:
            EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR, __LINE__);

            eRetVal = eCUBEADCS_STDRPLY_ERR;
            break;
    }

    return eRetVal;
}

bool cubeadcs_get_est_ang_rate(CubeADCS_AngRate_Formatted_t * const psAngRate)
{
	CRIT_ASSERT(psAngRate != NULL);

	bool bRetVal;

	uint16_t u16CmdRspLen;
	CubeADCS_CmdCfg_t sCmdStruct_147;
	CubeADCS_TLM147_t sCmdRsp147;

	CubeADCS_PREPCmd(&sCmdStruct_147, eCUBEADCS_CMD_ID_147, NULL, 0, (void *)&sCmdRsp147, CUBEADCS_TLM147_LEN, &u16CmdRspLen);

	bRetVal = false;
	if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct_147, eCUBEADCS_COMMREQTYPE_FETCH) ) {
		// We lose some accuracy here
		psAngRate->X = (int32_t) ( (( sCmdRsp147.AngRate.i16X * 0.01F ) * CUBEADCS_TO_RAD_CONV) * 1000);
		psAngRate->Y = (int32_t) ( (( sCmdRsp147.AngRate.i16Y * 0.01F ) * CUBEADCS_TO_RAD_CONV) * 1000);
		psAngRate->Z = (int32_t) ( (( sCmdRsp147.AngRate.i16Z * 0.01F ) * CUBEADCS_TO_RAD_CONV) * 1000);

		bRetVal = true;
	}

	return bRetVal;
}

bool cubeadcs_get_est_ang_rate_complete(CubeADCS_AngRate_Complete_t * const psDst)
{
	CRIT_ASSERT(psDst != NULL);

	bool bRetVal;

	CubeADCS_AngRate_Formatted_t sTmpData;

	if ( true == (bRetVal = cubeadcs_get_est_ang_rate(&sTmpData)) )
	{
		// We lose some accuracy here
		psDst->fAngVelNorm = (int32_t)sqrt((sTmpData.X * sTmpData.X) +
								  	  	   (sTmpData.Y * sTmpData.Y) +
										   (sTmpData.Z * sTmpData.Z));

		memcpy((void *)&psDst->sAngVelVec, (void *)&sTmpData, sizeof(CubeADCS_AngRate_Formatted_t));
	}

	return bRetVal;
}

bool cubeadcs_get_op_status(CubeADCS_Op_Status_t *psDst)
{
	CRIT_ASSERT(NULL != psDst);

    bool retVal;

    retVal = true;

	(void)cubeadcs_lock_data_access(0U);

    memcpy(psDst, &CubeADCS_OpStatus, sizeof(CubeADCS_OpStatus));

	(void)cubeadcs_unlock_data_access();

    return retVal;
}

bool cubeadcs_get_op_status_adcs_state(CubeADCS_TLM132_t *psDst)
{
	CRIT_ASSERT(NULL != psDst);

    bool bRet = true;

	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	memcpy(psDst, &op_status.State.State_ADCS, sizeof(CubeADCS_TLM132_t));

    return bRet;
}

void CubeADCS_SetPwrNodeStates(uCubeADCS_CfgNodwPwrMask_t uNodeMask)
{
    uint8_t  u8Data[CUBEADCS_TC_11_BYTE_LEN] = {0x00};

    uint16_t u16Resp;
    uint16_t u16RespSize;

    uint8_t  u8State;
    uint32_t u32PwrData;

    CubeADCS_CmdCfg_t sCmdStruct;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_11, &u8Data[0], CUBEADCS_TC_11_BYTE_LEN, (void *)&u16Resp, CUBEADCS_TC_LEN, &u16RespSize);

    u32PwrData = 0x00000000;

    for (uint8_t u8Node = 0; u8Node < (uint8_t)eCUBE_ADCS_TC11_NODES_NUMBER; ++u8Node )
    {
        u8State = (uNodeMask.raw >> u8Node) & 0x01;

        u32PwrData |= ((uint32_t)u8State << ((uint32_t)u8Node * 2));
    }

    for (uint8_t u8Indx = 0; u8Indx < CUBEADCS_TC_11_BYTE_LEN; ++u8Indx )
    {
    	*(sCmdStruct.pu8CmdData + u8Indx) = *(((uint8_t *)&u32PwrData) + u8Indx); /* Each node occupies 2 bits for the state - see TC 11 */
    }

    /* Update the node control status on success */
    if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    {
    	sNodeCntrlStatus.u32RawData = sResult_TLM197.u32RawData | (u32PwrData << 8); /* The last shift is needed because the cmdID is part of the structure */
    }
}

eCUBE_ADCS_TC_11_PWR_STATES_t CubeADCS_GetADCSNodePwrState(eCUBE_ADCS_TC_11_NODES_t eNode)
{
    eCUBE_ADCS_TC_11_PWR_STATES_t eNodeState;

	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

    switch ( eNode )
    {
    case eCUBE_ADCS_TC11_NODES_CUBECONTROL_SIGNAL:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte1.Data.CubeControl_Signal_en;
        break;
    case eCUBE_ADCS_TC11_NODES_CUBECONTROL_MOTOR:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte1.Data.CubeControl_Motor_en;
        break;
    case eCUBE_ADCS_TC11_NODES_CUBESENSE_1:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte1.Data.CubeSense1_en;
        break;
    case eCUBE_ADCS_TC11_NODES_CUBESENSE_2:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte1.Data.CubeSense2_en;
        break;
    case eCUBE_ADCS_TC11_NODES_CUBESTAR:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte2.Data.CubeStar_en;
        break;
    case eCUBE_ADCS_TC11_NODES_CUBEWHEEL_1:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte2.Data.CubeWheel1_en;
        break;
    case eCUBE_ADCS_TC11_NODES_CUBEWHEEL_2:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte2.Data.CubeWheel2_en;
        break;
    case eCUBE_ADCS_TC11_NODES_CUBEWHEEL_3:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte2.Data.CubeWheel3_en;
        break;
    case eCUBE_ADCS_TC11_NODES_MOTOR:
        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)op_status.State.State_ADCS.TLM.App.Byte2.Data.Motor_drv_en;
        break;
    case eCUBE_ADCS_TC11_NODES_GPS:
    {
    	/* Necessary to fix MISRA C:2004, 10.3, see section 6.10 */
    	uint8_t pwr_state = ((uint8_t)op_status.State.State_ADCS.TLM.App.Byte2.Data.GPS_LNA_en & (uint8_t)op_status.State.State_ADCS.TLM.App.Byte2.Data.GPS_rx_en);

        eNodeState = (eCUBE_ADCS_TC_11_PWR_STATES_t)pwr_state;
        break;
    }
    default:
        eNodeState = eCUBE_ADCS_TC11_STATE_NUMBER;

        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR, __LINE__);

        break;
    }

    return eNodeState;
}

uCubeADCS_CfgNodwPwrMask_t CubeADCS_GetADCSNodesPwrMask(void)
{
    uint8_t  u8Node;
    uCubeADCS_CfgNodwPwrMask_t u16RawMask;
    uint32_t u32RawTLMData;

    u16RawMask.raw = 0x0000;

    u32RawTLMData = (sResult_TLM197.u32RawData & 0x00FFFFFF) >> 8;

    for ( u8Node = 0; u8Node < (uint8_t)eCUBE_ADCS_TC11_NODES_NUMBER; ++u8Node )
    {
        u16RawMask.raw |= (u32RawTLMData & ( 1 << ((uint32_t)u8Node * 2))) >> u8Node;
    }

    return u16RawMask;
}

eCubeADCS_Comm_Status_t CubeADCS_SendCmd(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_CommReqType_t eCommReqType)
{
	eCubeADCS_Comm_Status_t eRetStatus;

	eRetStatus = eCUBEADCS_COMM_ERR;

	if ( true == fs_cubeadcs_lock_comm_access(CUBEADCS_COMM_RX_TIMEOUT) )
	{
		eRetStatus = CubeADCS_Driver_ExecCmdReq(sCmd, eCommReqType, CubeADCS_GetNodeType());

		if ( true != fs_cubeadcs_unlock_comm_access() ) {
			eRetStatus = eCUBEADCS_COMM_ERR;
		}

		fs_CubeADCS_Diag_Update_Counters(CUBEADCS_DIAG_UPDATE_COMM_ID, eRetStatus);
	}

	return eRetStatus;
}

eCubeADCS_Comm_Status_t CubeADCS_SendCmdWithChecks(CubeADCS_CmdCfg_t *sCmd, uint8_t u8Update, uint8_t u8Valid)
{
    eCubeADCS_Comm_Status_t eCommStatus = eCUBEADCS_COMM_COMM_ERR;

    if ( true == fs_cubeadcs_lock_comm_access(CUBEADCS_COMM_RX_TIMEOUT))
    {
        /* Store to a temporary location the OpStatus related TLM messages */
        void   *pvTmpCmdResDst;
        uint8_t u8TmpDataArr[CUBEADCS_LOCAL_BUFF_OP_STATUS_CHECK];

        if ( CUBEADCS_VALIDATE_DATA_TRUE == u8Valid ) {
            pvTmpCmdResDst   = sCmd->pvCmdResDst;
            sCmd->pvCmdResDst = (void *)&u8TmpDataArr[0];
        }

        eCommStatus = CubeADCS_SendCmd(sCmd, eCUBEADCS_COMMREQTYPE_FETCH);

        (void)cubeadcs_lock_data_access(0U);
        CubeADCS_OpStatus.Comm = eCommStatus;
        (void)cubeadcs_unlock_data_access();

        /* Point back the original pointers to the OpStatus TLM message caches */
        if ( CUBEADCS_VALIDATE_DATA_TRUE == u8Valid ) {
            sCmd->pvCmdResDst = pvTmpCmdResDst;
        }

        if ( eCUBEADCS_COMM_OK == CubeADCS_OpStatus.Comm )
        {
            if ( CUBEADCS_DIAG_UPDATE_OK == u8Update )
            {
                fs_CubeADCS_Diag_Update_Counters(sCmd->u8CmdID, CubeADCS_OpStatus.Comm);
            }

            /* Update the OpStatus related TLM messages on successful communication */
            if ( CUBEADCS_VALIDATE_DATA_TRUE == u8Valid )
            {
                memcpy(sCmd->pvCmdResDst, (void *)&u8TmpDataArr, sCmd->u16CmdResDstSize);
            }
        }

        fs_CubeADCS_UpdateHCheckCommStatuses(sCmd->u8CmdID);

        if ( true != fs_cubeadcs_unlock_comm_access() ) {

            EXEH_vException(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_OS_ERROR, __LINE__);
        }
    }

    return eCommStatus;
}

void CubeADCS_StopRWheels(void)
{
    CubeADCS_RWheels_Speed_t sStopRPM;

    sStopRPM.i16RWheel_X = 0;
    sStopRPM.i16RWheel_Y = 0;
    sStopRPM.i16RWheel_Z = 0;

    fs_CubeADCS_SetRWheelsRPM(sStopRPM);
}

void CubeADCS_ChngRateSensorMult(eCUBE_ADCS_TC_23_RATE_SENSOR_MULT_t u8RateSensMult)
{
    uint8_t  u8Data[CUBEADCS_TLM138_LEN];
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmdStruct;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_138, NULL, 0, (void *)&u8Data, CUBEADCS_TLM138_LEN, &u16CmdRspLen);

    if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    {
        /* Set a new multiplier value */
        u8Data[ CUBEADCS_TLM138_LEN - 1 ] = u8RateSensMult;

        CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_23, &u8Data[1], CUBEADCS_TLM138_LEN - 1, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

        (void)CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH);
    }
}

void CubeADCS_ClrErrFlags(void)
{
    uint8_t  u8Data;
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmdStruct;

	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

    if ( eCUBEADCS_MODE_BOOTLOADER == op_status.Mode )
    {
        u8Data = 0x00;

        CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_7, &u8Data, 0, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

        (void)CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH);
    }
    else
    {
        u8Data = 0x03;

        CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_12, &u8Data, 1, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

        (void)CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH);
    }
}

void CubeADCS_ChngMtmSampling(eCUBE_ADCS_TC_56_MTM_MODE_t eMtmMode)
{
    uint8_t  u8Data;
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;
    CubeADCS_CmdCfg_t sCmdStruct;

    u8Data = (uint8_t)eMtmMode;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_56, &u8Data, 1, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    (void)CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH);
}

CubeADCS_TLM197_t cubeadcs_get_node_cntrl_status(void)
{
    return sNodeCntrlStatus;
}

CubeADCS_TLM197_t cubeadcs_get_last_pwr_cntrl_tlmtr_data(void)
{
	return sResult_TLM197;
}

CubeADCS_CmdCfg_t *CubeADCS_GetHCheckCmdDetails(eCubeADCS_IDLE_STATE_CMD_List_t eCmdId)
{
    return &aHealthCheckState[ eCmdId ];
}

osThreadId_t CubeADCS_GetThreadHandle(void)
{
    return CubeADCS_Task_TaskHandle;
}

eCubeADCS_StdRply CubeADCS_GetAvrgAngVel(CubeADCS_AngRateFormatted_t *sAvrgAngVel, eCubeADCS_AngRateType_t eMeasType, uint8_t u8SCntToDecision)
{
    eCubeADCS_StdRply eRetVal;

    CubeADCS_AngRateFormatted_t sAngVelTmp;

    static uint8_t u8SCnt = 0;
    static CubeADCS_AngRateFormatted_t sAngVel;

    eRetVal = eCUBEADCS_STDRPLY_ERR;

    if ( u8SCnt < u8SCntToDecision )
    {
        if ( eCUBEADCS_STDRPLY_OK == CubeADCS_GetAngularRate(&sAngVelTmp, eMeasType) )
        {
            ++u8SCnt;

            sAngVel.fX += sAngVelTmp.fX;
            sAngVel.fY += sAngVelTmp.fY;
            sAngVel.fZ += sAngVelTmp.fZ;

        }
        else
            u8SCnt = 0;
    }
    else
    if ( u8SCnt > u8SCntToDecision )
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR, __LINE__);
    }
    else
    {
        sAvrgAngVel->fX = sAngVel.fX / u8SCntToDecision;
        sAvrgAngVel->fY = sAngVel.fY / u8SCntToDecision;
        sAvrgAngVel->fZ = sAngVel.fZ / u8SCntToDecision;

        eRetVal = eCUBEADCS_STDRPLY_OK;
    }

    return eRetVal;
}

eCubeADCS_StdRply CubeADCS_GetQErrFormatted(CubeADCS_QErrFormatted_t *sQErr)
{
    CRIT_ASSERT(sQErr != NULL);

    eCubeADCS_StdRply eRetVal;

    uint16_t u16CmdRspLen;
    CubeADCS_CmdCfg_t sCmdStruct_163;

    CubeADCS_TLM163_t sCmdRsp163;

    eRetVal = eCUBEADCS_STDRPLY_ERR;

    CubeADCS_PREPCmd(&sCmdStruct_163, eCUBEADCS_CMD_ID_163, NULL, 0, (void *)&sCmdRsp163, CUBEADCS_TLM163_LEN, &u16CmdRspLen);

    if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct_163, eCUBEADCS_COMMREQTYPE_FETCH) ) {
        sQErr->fQ1 = sCmdRsp163.QErr.i16Q1 * 0.0001F;
        sQErr->fQ2 = sCmdRsp163.QErr.i16Q2 * 0.0001F;
        sQErr->fQ3 = sCmdRsp163.QErr.i16Q3 * 0.0001F;

        eRetVal = eCUBEADCS_STDRPLY_OK;
    }

    return eRetVal;
}

bool cubeadcs_set_sys_state_and_ref(cubeadcs_ref_t *p_ref, eCubeADCS_CfgType new_sys_cfg)
{
    CRIT_ASSERT(p_ref != NULL);
    CRIT_ASSERT(new_sys_cfg < eCUBEADCS_CFGTYPE_NUMBER);

    bool bRes = true;

    switch (new_sys_cfg)
    {
    case eCUBEADCS_CFGTYPE_Y_MOMENTUM:
    case eCUBEADCS_CFGTYPE_Y_MOMENTUM_FULL_STATE_EKF:
    case eCUBEADCS_CFGTYPE_3AXIS:
    {
        CubeADCS_Command_Angles_t sAngles = {
                .i16RollAngle = 0,
                .i16PitchAngle = 0,
                .i16YawAngle = 0
        };

        /* Clear offset angles */
        fs_CubeADCS_SetCommandedAngles(sAngles);

        /* Update the system state configuration */
        cubeadcs_set_state_cfg(new_sys_cfg, CUBEADCS_EXEC_STATE_REQ);

        break;
    }
    /* If the new system state configuration is for target tracking, the target should be set before the */
    /* state is changed to target tracking (CubeADCS User Manual, 4.4.3.3) */
    case eCUBEADCS_CFGTYPE_TARGET_TRACKING:
    case eCUBEADCS_CFGTYPE_GEO_TARGET_TRACKING:
    {
        uint16_t u16CmdRsp;
        uint16_t u16CmdRspLen;

        CubeADCS_CmdCfg_t sCmdStruct;

        CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_55, (uint8_t *)p_ref, CUBEADCS_TC_55_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

        if ( eCUBEADCS_COMM_OK != CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
        {
            bRes = false;

            /* Update the system state configuration, don't execute it ... */
            cubeadcs_set_state_cfg(new_sys_cfg, CUBEADCS_DONT_EXEC_STATE_REQ);
            /* ... and then immediately invalidate the request since we don't have the target coordinates set */
            fs_cubeadcs_update_adcs_sys_state_cfg_status(eSYSSTATECFGSTATUS_ERR);
        }
        else
        {
            /* Update the system state configuration */
            cubeadcs_set_state_cfg(new_sys_cfg, CUBEADCS_EXEC_STATE_REQ);
        }

        break;
    }
    case eCUBEADCS_CFGTYPE_ORBITAL_CHANGE:
    {
    	/* Save supplied 3D vector as roll/pitch/yaw angles instead of lon/lat/alt set points */
    	/* Format them as CubeADCS requires */

    	if ( (fabs(p_ref->ref_param_1) > 180.0F) ||
    			(fabs(p_ref->ref_param_2) > 180.0F) ||
				(fabs(p_ref->ref_param_3) > 180.0F) 	)
    	{
    		bRes = false;

    		orbital_change_roll  = 0;
    		orbital_change_pitch = 0;
    		orbital_change_yaw   = 0;

    		/* Update the system state configuration, don't execute it ... */
    		cubeadcs_set_state_cfg(new_sys_cfg, CUBEADCS_DONT_EXEC_STATE_REQ);
    		/* ... and then immediately invalidate the request since the RPY angles are not acceptable */
    		fs_cubeadcs_update_adcs_sys_state_cfg_status(eSYSSTATECFGSTATUS_ERR);
    	}
    	else
    	{
    		/* Update the system state configuration */
    		cubeadcs_set_state_cfg(new_sys_cfg, CUBEADCS_EXEC_STATE_REQ);

    		orbital_change_roll  = (int16_t)(p_ref->ref_param_1 * 100.0F);
    		orbital_change_pitch = (int16_t)(p_ref->ref_param_2 * 100.0F);
    		orbital_change_yaw   = (int16_t)(p_ref->ref_param_3 * 100.0F);
    	}

    	break;
    }
    default:

        /* Update the system state configuration */
        cubeadcs_set_state_cfg(new_sys_cfg, CUBEADCS_EXEC_STATE_REQ);

        break;

    }

    return bRes;
}

void cubeadcs_set_state_cfg(eCubeADCS_CfgType new_sys_cfg, bool exec_state_req)
{
    eADCSCfg.eReqCfg = new_sys_cfg;

    eADCSCfg.eReqCfgStatus = eSYSSTATECFGSTATUS_RUN_0;

    if ( true == exec_state_req )
    {
        osThreadFlagsSet(CubeADCS_GetThreadHandle(), 0x00000001);

        (void)fs_cubeadcs_set_sm_state(eCUBEADCS_STATE_SYSSTATE_CHANGE);
    }
}

void cubeadcs_get_adcs_state_cfg(CubeADCS_SysSCfg_t * const peADCSCfg)
{
	CRIT_ASSERT(NULL != peADCSCfg);

	memcpy(peADCSCfg, &eADCSCfg, sizeof(CubeADCS_SysSCfg_t));
}

eCUBE_ADCS_TC_56_MTM_MODE_t CubeADCS_GetMTMSamplingMode(void)
{
	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	return (eCUBE_ADCS_TC_56_MTM_MODE_t)CubeADCS_OpStatus.State.State2_ADCS.Byte0.Data.MagnetometerSampMode;
}

bool cubeadcs_get_latched_err(uint16_t *u16Dst)
{
	CRIT_ASSERT(u16Dst != NULL);

	bool bRes = true;

	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	*u16Dst = op_status.Status.RunTimeLatchedErrors.u16RawData;

	return bRes;
}

bool cubeadcs_set_latched_err(uint16_t const *p_src)
{
	CRIT_ASSERT(p_src != NULL);

	bool bRes;

	if ( true == ( bRes = cubeadcs_lock_data_access(0U) ) ) {
		CubeADCS_OpStatus.Status.RunTimeLatchedErrors.u16RawData = *p_src;

		(void)cubeadcs_unlock_data_access();
	}

	return bRes;
}

eCubeADCS_StdRply cubeadcs_update_unix_time(CubeADCS_UnixTime_t * const psNewUnixTime)
{
	CRIT_ASSERT(psNewUnixTime != NULL);

	eCubeADCS_StdRply eRply = eCUBEADCS_STDRPLY_OK;

    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmdStruct;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_2, (uint8_t *)psNewUnixTime, CUBEADCS_TC_02_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    if (eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    {
    	CubeADCS_UnixTimeSave_t sUnixTimeSaveCfg;

    	/* Save now */
    	sUnixTimeSaveCfg.uSaveCfg.u8Data = 0x01;
    	sUnixTimeSaveCfg.u8Period = 0x00;

    	CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_9, (uint8_t *)&sUnixTimeSaveCfg, CUBEADCS_TC_09_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    	if (eCUBEADCS_COMM_OK != CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    		eRply = eCUBEADCS_STDRPLY_ERR;
    }
    else
    	eRply = eCUBEADCS_STDRPLY_ERR;

    return eRply;
}

eCubeADCS_StdRply cubeadcs_get_unix_time(CubeADCS_UnixTime_t * const psCurrentUnixTime)
{
	CRIT_ASSERT(psCurrentUnixTime != NULL);

	eCubeADCS_StdRply eRply = eCUBEADCS_STDRPLY_OK;

    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmdStruct;

    CubeADCS_TLM140_t sCmdRsp140;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_140, NULL, 0, (void *)&sCmdRsp140, CUBEADCS_TLM140_LEN, &u16CmdRspLen);

    if (eCUBEADCS_COMM_OK != CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    	eRply = eCUBEADCS_STDRPLY_ERR;

    memcpy(psCurrentUnixTime, &sCmdRsp140.sUnixTime, sizeof(CubeADCS_UnixTime_t));

    return eRply;
}

eCubeADCS_StdRply CubeADCS_SetSGP4OrbitParams(CubeADCS_SGP4_Orbit_Params_t * const psOrbitParams)
{
	CRIT_ASSERT(psOrbitParams != NULL);

	eCubeADCS_StdRply eRply = eCUBEADCS_STDRPLY_OK;

    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmdStruct;

    CubeADCS_PREPCmd(&sCmdStruct, eCubeADCS_CMD_ID_45, (uint8_t *)psOrbitParams, CUBEADCS_TC_45_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    if (eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    {
    	CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_64, NULL, CUBEADCS_TC_64_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    	if (eCUBEADCS_COMM_OK != CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    		eRply = eCUBEADCS_STDRPLY_ERR;
    }
    else
    	eRply = eCUBEADCS_STDRPLY_ERR;

    return eRply;
}

eCubeADCS_StdRply CubeADCS_GetSGP4OrbitParams(CubeADCS_SGP4_Orbit_Params_t * const psOrbitParams)
{
	CRIT_ASSERT(psOrbitParams != NULL);

	eCubeADCS_StdRply eRply = eCUBEADCS_STDRPLY_OK;

    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmdStruct;

    CubeADCS_TLM207_t sCmdRsp207;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_207, NULL, 0, (void *)&sCmdRsp207, CUBEADCS_TLM207_LEN, &u16CmdRspLen);

    if (eCUBEADCS_COMM_OK != CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
    {
    	eRply = eCUBEADCS_STDRPLY_ERR;
    }

    memcpy(psOrbitParams, &sCmdRsp207.sSGP4_Orbit_Params, sizeof(CubeADCS_SGP4_Orbit_Params_t));

    return eRply;
}

bool cubeadcs_lock_data_access(uint32_t u32WaitTimeMS)
{
	bool bRes = true;

	if ( osOK != osMutexAcquire(cubeadcs_data_mutex, u32WaitTimeMS) ) {
		bRes = false;

		EXEH_vException(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_OS_ERROR, __LINE__);
	}

	return bRes;
}

/*!
********************************************************************************************
* @brief Release access to the operational status data
********************************************************************************************
* @param[input]      -
* @param[output]     -
* @return            bool - result of operation
* @note              -
********************************************************************************************
*/
bool cubeadcs_unlock_data_access(void)
{
	bool bRes = true;

	if ( osOK != osMutexRelease(cubeadcs_data_mutex) ) {

		bRes = false;

		EXEH_vException(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_OS_ERROR, __LINE__);
	}

	return bRes;
}

bool cubeadcs_get_est_att_angles(cubeadcs_est_att_ang_fmt_t * const psEstAttAng)
{
	CRIT_ASSERT(psEstAttAng != NULL);

	bool bRetVal;

	uint16_t u16CmdRspLen;
	CubeADCS_CmdCfg_t sCmdStruct_146;
	cubeadcs_tlm_146_t sCmdRsp146;

	CubeADCS_PREPCmd(&sCmdStruct_146, eCUBEADCS_CMD_ID_146, NULL, 0, (void *)&sCmdRsp146, CUBEADCS_TLM146_LEN, &u16CmdRspLen);

	bRetVal = false;
	if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct_146, eCUBEADCS_COMMREQTYPE_FETCH) ) {
		psEstAttAng->i32Roll = (int32_t)sCmdRsp146.sRawAttAng.i16Roll_raw  * 10 ;
		psEstAttAng->i32Pitch = (int32_t)sCmdRsp146.sRawAttAng.i16Pitch_raw * 10 ;
		psEstAttAng->i32Yaw = (int32_t)sCmdRsp146.sRawAttAng.i16Yaw_raw   * 10 ;

		bRetVal = true;
	}

	return bRetVal;
}

bool cubeadcs_reset(eCubeADCS_Mode_t eMode)
{
	bool bRes;
    uint8_t  u8Data;
    uint16_t u16CmdResp;
    uint16_t u16RespSize;

    CubeADCS_CmdCfg_t sCmdStruct;
    eCubeADCS_Comm_Status_t eCommStatus;

    bRes = false;

    /* Reset magic number */
    u8Data = CUBEADCS_TC_01_MAGIC_NUM;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_1, &u8Data, 1, (void *)&u16CmdResp, CUBEADCS_TC_LEN, &u16RespSize);

    /* We expect timeout as this is the default behaviour after reset of the CubeADCS */
    if ( eCUBEADCS_COMM_RX_TIMEOUT == (eCommStatus = CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) ) )
    {
    	if ( eCUBEADCS_MODE_BOOTLOADER == eMode ) {
    		(void)fs_cubeadcs_set_sm_state(eCUBEADCS_STATE_INIT);
    	}
    	else {
    		/* Set a new period to wait before TLM requests */
    		u32BaseTime = get_uptime_seconds();

    		(void)fs_cubeadcs_set_sm_state(eCUBEADCS_STATE_INIT_WAIT);
    	}

    	bRes = true;

    	osThreadFlagsSet(CubeADCS_GetThreadHandle(), 0x00000001);
    }

    return bRes;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief Init routine for the memory level
 *
 *  @note Initialise the used UART, buffers, etc. Gets the commissioning status.
 */
static void fs_cubeadcs_init_memory(void)
{
    /* MEMORY LEVEL INITIALIZATION */
    /* Create the CubeADCS communication channel access mutex */
    cubeadcs_comm_mutex = osMutexNew(&CubeADCSComm_Mutex_attr);

    /* Create the CubeADCS data access mutex */
    cubeadcs_data_mutex = osMutexNew(&CubeADCSData_Mutex_attr);

    /* Initialise the operational status */
    fs_cubeadcs_init_op_status();

    /* Initialise the task state machine entry point */
    CubeADCS_State = eCUBEADCS_STATE_INIT_WAIT;

    /* Initialise the error counters */
    fs_CubeADCS_Init_Diag_Counters();

    /* Get base time for CubeADCS decision */
    u32BaseTime = get_uptime_seconds();

    /* Initialise the driver related memory and buffers */
    cubeadcs_driver_mem_init();

    /* Load the system state configuration from the NVM*/
    cubeadcs_persist_load_sys_state_cfg(asCubeADCS_SysStates);
}

/** @brief Init routine for the hardware level
 *
 *  @note Initialise the driver.
 */
static void fs_cubeadcs_init_hw(void)
{
    /* HW LEVEL INITIALIZATION */
    /* Initialise driver */
    cubeadcs_driver_init();
}

/** @brief Init routine for the os level
 *
 *  @note Initialise the driver.
 */
static void fs_cubeadcs_init_os()
{
    /* OS LEVEL INITIALIZATION */
    /* Create and initialise the main CubeADCS task */
    CubeADCS_TaskInit();

    /* Create and initialise the file transfer handling task */
    CubeADCS_FTransfer_TaskInit();
}

/** @brief De-init routine for the hardware level
 *
 *  @note De-initialises the driver.
 */
static void fs_cubeadcs_deinit_hw()
{
    /* HW LEVEL DE-INITIALIZATION */
    /* De-Initialise driver */
	cubeadcs_driver_deinit();
}

/** @brief The main CubeADCS task
 *
 *  @param[in] task arguments
 */
static void fs_cubeadcs_task(void *arg)
{
    for(;;)
    {
        eCubeADCS_State_t eADCS_NewState;
        eCubeADCS_State_t eADCS_CacheState;

        eADCS_CacheState = CubeADCS_GetState();
        eADCS_NewState = eADCS_CacheState;

        switch ( eADCS_CacheState )
        {
            case eCUBEADCS_STATE_INIT_WAIT:
            {
                CUBEADCS_TRACE_DBG("%s INIT_WAIT_RUNS\r", CUBEADCS_HEAD);

                /* Wait until CubeADCS starts in Application mode */
                if ( get_uptime_seconds() >= (u32BaseTime + CUBEADCS_PWR_UP_TO_APP_TIME_S) )
                {
                	eADCS_NewState = eCUBEADCS_STATE_INIT;
                }
                else
                {
                	CubeADCS_DelayTask(CUBEADCS_TASK_BASE_DELAY_MS);
                }

                break;
            }

            case eCUBEADCS_STATE_INIT:
            {
                CUBEADCS_TRACE_DBG("%s INIT_RUNS\r", CUBEADCS_HEAD);

                if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmdWithChecks(&aInitState[ eCUBEADCS_INIT_STATE_CMD_ID_128 ], CUBEADCS_DIAG_UPDATE_NOK, CUBEADCS_VALIDATE_DATA_TRUE) )
                {
                	fs_cubeadcs_set_node_type((eCubeADCS_Mode_t)sResult_TLM128.NodeType);

                    eADCS_NewState = eCUBEADCS_STATE_HEALTH_CHECK;

                    for (uint8_t u8Indx = 1; u8Indx < eCUBEADCS_INIT_STATE_CMD_ID_NUM; ++u8Indx )
                    {
                        (void)CubeADCS_SendCmdWithChecks(&aInitState[u8Indx], CUBEADCS_DIAG_UPDATE_OK, CUBEADCS_VALIDATE_DATA_TRUE);

                        if ( eCUBEADCS_COMM_OK != fs_cubeadcs_get_last_comm_status() )
                        {
                        	break;
                        }
                    }
                }

                CubeADCS_DelayTask(CUBEADCS_TASK_BASE_DELAY_MS);

                break;
            }

            case eCUBEADCS_STATE_IDLE:
            {
                CUBEADCS_TRACE_DBG("%s IDLE_STARTS\r", CUBEADCS_HEAD);

                /* Retrieve the current system state configuration */
                CubeADCS_SysSCfg_t sCurrentSysStateCfg;
                cubeadcs_get_adcs_state_cfg(&sCurrentSysStateCfg);

                CUBEADCS_TRACE_DBG("%s CUBE_ADCS_eReqCfgStatus: %d\r", CUBEADCS_HEAD, sCurrentSysStateCfg.eReqCfgStatus);
                /* If there is additional logic required by this state configuration */
                /* and it -has not- been completed */
                if ( (0 != asCubeADCS_SysStates[sCurrentSysStateCfg.eReqCfg].uAdditionalLogic) &&
                     (eSYSSTATECFGSTATUS_IN_PROGRESS == sCurrentSysStateCfg.eReqCfgStatus) )
                {
                    uint8_t u8Res = 0;
                    /* Call the additional logic handler */
                    u8Res = fs_cubeadcs_execute_custom_logic(sCurrentSysStateCfg.eReqCfg);

                    /* Catch an error if there is one */
                    if (255 == u8Res)
                    {
                        CubeADCS_ErrHandl(); // error handler maybe?
                    }

                    /* Default task delay if there is logic being executed */
                    CubeADCS_DelayTask(CUBEADCS_TASK_BASE_DELAY_MS);
                    CUBEADCS_TRACE_DBG("%s IDLE_RUNS_CUSTOM_LOGIC\r", CUBEADCS_HEAD);
                }
                else
                {
                    /* IDLE delay if there is no logic being executed */
                    CubeADCS_DelayTask(CUBEADCS_TASK_IDLE_DELAY_MS);
                    CUBEADCS_TRACE_DBG("%s IDLE_RUNS\r", CUBEADCS_HEAD);
                }

                if ( (eCUBEADCS_STATE_IDLE == CubeADCS_GetState()) && ( eCUBEADCS_FTRANSF_STATE_IDLE == CubeADCS_FTransfer_GetTaskState()))
                {
                	eADCS_NewState = eCUBEADCS_STATE_HEALTH_CHECK;
                }

                break;
            }

            case eCUBEADCS_STATE_HEALTH_CHECK:
            {
                CUBEADCS_TRACE_DBG("%s HEALTH_CHECK_RUNS\r", CUBEADCS_HEAD);

                if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmdWithChecks(&aHealthCheckState[ eCUBEADCS_IDLE_STATE_CMD_ID_128 ], CUBEADCS_DIAG_UPDATE_NOK, CUBEADCS_VALIDATE_DATA_TRUE) )
                {
                	fs_cubeadcs_set_node_type((eCubeADCS_Mode_t)sResult_TLM128.NodeType);

                    for ( uint8_t u8Indx = 1; u8Indx < eCUBEADCS_IDLE_STATE_CMD_ID_NUM; ++u8Indx )
                    {
                        (void)CubeADCS_SendCmdWithChecks(&aHealthCheckState[u8Indx], CUBEADCS_DIAG_UPDATE_OK, CUBEADCS_VALIDATE_DATA_TRUE);

                        if ( eCUBEADCS_COMM_OK != fs_cubeadcs_get_last_comm_status() )
                        {
                        	break;
                        }
                    }
                }

                if ( eCUBEADCS_MODE_BOOTLOADER == CubeADCS_GetNodeType() )
                {
                	if ( true == fs_cubeadcs_is_boot_commanded() )
                	{
                		eADCS_NewState = eCUBEADCS_STATE_IDLE;
                	}
                }
                else {
                    CUBEADCS_TRACE_DBG("%s HEALTH_CHECK_ERR_HANDL_RUNS\r", CUBEADCS_HEAD);

                    CubeADCS_ErrHandl();

                    eADCS_NewState = eCUBEADCS_STATE_PREP_DETUMB;
                }
                break;
            }

            case eCUBEADCS_STATE_SYSSTATE_CHANGE:
            {
                CUBEADCS_TRACE_DBG("%s SYS_STATE_CHANGE_ENTRY\r", CUBEADCS_HEAD);

                eCubeADCS_StdRply eExecRetVal;
                CubeADCS_SysSCfg_t sSysStateCfg;
                CubeADCS_SysSCfg_t sUpdatedSysStateCfg;

                /* Retrieve the desired system state configuration */
                cubeadcs_get_adcs_state_cfg(&sSysStateCfg);

                CUBEADCS_TRACE_DBG("%s State Change Attempt: %02d\r", CUBEADCS_HEAD, sSysStateCfg.eReqCfgStatus);

                switch( sSysStateCfg.eReqCfgStatus )
                {
                    case eSYSSTATECFGSTATUS_ERR:
                    {
                    	/* Too many attempts to change state were made, throw an error and fall through to IDLE */
                    	cubeadcs_errhandl_activate(CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM);
                    	CUBEADCS_TRACE_DBG("%s SYS_STATE_CHANGE_ERROR\r", CUBEADCS_HEAD);
                    }

                    case eSYSSTATECFGSTATUS_OK:
                    {
                    	/* Return to IDLE state */
                        eADCS_NewState = eCUBEADCS_STATE_IDLE;

                        /* If it's an actual "OK", not just a fall through from ERR above */
                        if (eSYSSTATECFGSTATUS_OK == sSysStateCfg.eReqCfgStatus)
                        {
                            CUBEADCS_TRACE_DBG("%s SYS_STATE_CHANGE_OK\r", CUBEADCS_HEAD);
                        }

                        break;
                    }

                    case eSYSSTATECFGSTATUS_IN_PROGRESS:
                    {
                        /* Return to IDLE, but keep the state change operation IN_PROGRESS */
                        eADCS_NewState = eCUBEADCS_STATE_IDLE;
                        CUBEADCS_TRACE_DBG("%s SYS_STATE_CHANGE_PROGRESS\r", CUBEADCS_HEAD);
                        break;
                    }

                    default:
                    {
                    	/* Attempt to change the CubeADCS state */
                    	eExecRetVal = fs_CubeADCS_ApplyNewSysStateCfg(sSysStateCfg.eReqCfg);

                    	/* Retrieve the now updated system state configuration */
                    	cubeadcs_get_adcs_state_cfg(&sUpdatedSysStateCfg);

                    	/* Before requesting a new state change load the configuration from the NVM */
                    	if(eSYSSTATECFGSTATUS_NEW_REQ == sUpdatedSysStateCfg.eReqCfgStatus)
                    	{
                    		cubeadcs_persist_load_sys_state_cfg(asCubeADCS_SysStates);
                    	}

                    	/* If the system state configuration successfully changed to the desired one */
                    	if ( (sSysStateCfg.eReqCfgStatus == sUpdatedSysStateCfg.eReqCfgStatus) &&
                    			( sSysStateCfg.eReqCfg == sUpdatedSysStateCfg.eReqCfg)         &&
								( eCUBEADCS_STDRPLY_OK == eExecRetVal ))
                    	{
                    		/* If the system state configuration requires additional logic to be executed */
                    		if (asCubeADCS_SysStates[sSysStateCfg.eReqCfg].uAdditionalLogic)
                    		{
                    			CUBEADCS_TRACE_DBG("%s CUSTOM_STATE_ENTERED: %d\r", CUBEADCS_HEAD, sSysStateCfg.eReqCfg);
                    			/* Move the system state change operation to IN_PROGRESS */
                    			sSysStateCfg.eReqCfgStatus = eSYSSTATECFGSTATUS_IN_PROGRESS;
                    		}
                    		else
                    		{
                    			/* Signal that the system state change operation has completed */
                    			sSysStateCfg.eReqCfgStatus = eSYSSTATECFGSTATUS_OK;
                    		}
                    	}
                    	else
                    	{
                    		/* Increase the attempts counter */
                    		sSysStateCfg.eReqCfgStatus++;
                    	}

                    	/* Update the system state configuration */
                    	fs_cubeadcs_update_adcs_sys_state_cfg_status(sSysStateCfg.eReqCfgStatus);

                    	break;
                    }
                }

                CUBEADCS_TRACE_DBG("%s SYS_STATE_CHANGE_EXIT\r\r", CUBEADCS_HEAD);
                break;
            }

            case eCUBEADCS_STATE_PREP_DETUMB:
            {
                CUBEADCS_TRACE_DBG("%s PREP_DETUMBLING_RUNS\r", CUBEADCS_HEAD);

                eADCS_NewState = eCUBEADCS_STATE_IDLE;

                /* If necessary enable everything needed to assess detumbling needs */
                if ( eCUBEADCS_MODE_APPLICATION == CubeADCS_GetNodeType() )
                {
                	if ( SAFE_TRUE != fs_cubeadcs_get_simulation_mode_en_status() )
                	{
                		if ( eCUBE_ADCS_TC10_RUNMODE_ENABLED != CubeADCS_GetADCSRunMode() )
                		{
                		    cubeadcs_set_state_cfg(eCUBEADCS_CFGTYPE_NO_CONTROL, CUBEADCS_EXEC_STATE_REQ);

                			eADCS_NewState = eCUBEADCS_STATE_SYSSTATE_CHANGE;
                		}
                	}
                }

                break;
            }

            default:
                EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR, __LINE__);

                eADCS_NewState = eCUBEADCS_STATE_IDLE;

                break;
        }

        /* Accept state machine state only if no outside state forcing happened in the meantime */
        if ( eADCS_CacheState == CubeADCS_GetState() )
        {
        	(void)fs_cubeadcs_set_sm_state(eADCS_NewState);
        }

        TaskMonitor_IamAlive(TASK_MONITOR_CUBEADCS);
        vApplicationLowStackCheck(TASK_MONITOR_CUBEADCS);
    }
}

/** @brief Initialise all CubeADCS RAM error counters
 *
 */
static void fs_CubeADCS_Init_Diag_Counters(void)
{
    for (uint8_t indx = 0; indx < eCUBEADCS_COMMON_DIAG_CNTS_NUMBER; ++indx ) {

        CubeADCS_Err_Cnts[indx].u8Id            = indx;
        CubeADCS_Err_Cnts[indx].u16Value        = 0x0000;
    }
}

/** @brief Update diagnostic counters related to CubeADCS operation
 *
 *  @param[in] cmdID the command ID
 *  @param[in] comm_status status of the communication
 *
 *  @note The valid cmd IDs are:
 *        cmdID == 0   - Communication status with CubeADCS
 *        cmdID == 132 - TLM132
 *        cmdID == 135 - TLM135
 *        cmdID == 224 - TLM224
 *
 *        cmdID == 128 - TLM128, it contains no counters, nothing happens
 *        cmdID == 129 - TLM129, it contains no counters, nothing happens
 *        cmdID == 130 - TLM130, it contains no counters, nothing happens
 *        cmdID == 197 - TLM197, it contains no counters, nothing happens
 *
 *        NOTE: Anything else is considered INVALID
 *
 */
static void fs_CubeADCS_Diag_Update_Counters(uint8_t cmdID, eCubeADCS_Comm_Status_t comm_status)
{
	eCubeADCS_Comm_Status_t eCommStatus;
	eCubeADCS_Mode_t        eMode;
	CubeADCS_TLM132_t 		sStateADCS;
	CubeADCS_TLM135_t		sStateErr;
	CubeADCS_TLM224_t		sStateADCS2;

	eCommStatus = comm_status;

	(void)cubeadcs_lock_data_access(0U);
	eMode		= CubeADCS_OpStatus.Mode;
	sStateADCS	= CubeADCS_OpStatus.State.State_ADCS;
	sStateErr	= CubeADCS_OpStatus.State.State_Err;
	sStateADCS2 = CubeADCS_OpStatus.State.State2_ADCS;

	(void)cubeadcs_unlock_data_access();


    switch ( cmdID )
    {
        case 0: /* Communication with CubeADCS */
        {
            if ( (eCubeADCS_Common_Diag_Cnts)eCommStatus <= eCUBEADCS_COMMON_DIAG_CNTS_COMM_COMM_ERR )
            {
            	CubeADCS_Err_Cnts[ (eCubeADCS_Common_Diag_Cnts)eCommStatus ].u16Value++;
            }

            break;
        }
        case eCUBEADCS_CMD_ID_132: /* TLM132 */
        {
            uint8_t u8Indx;
            uint8_t u8Base;

            if ( eCUBEADCS_MODE_BOOTLOADER == eMode )
            {
                uint8_t u8ErrState;

                u8ErrState = (uint8_t)((sStateADCS.TLM.Boot.flags.u16DataBytes & CUBEADCS_DIAG_TLM132_BOOT_MASK) >> 4);
                u8Base     = (uint8_t)eCUBEADCS_COMMON_DIAG_CNTS_SRAM_LUP_ERR;

                for (u8Indx = 0; u8Indx < CUBEADCS_DIAG_TLM132_ERR_BOOT_CNTS_NUM; ++u8Indx)
                {
                    if ( 0 != ( (u8ErrState >> u8Indx) & 0x01 ) )
                    {
                    	CubeADCS_Err_Cnts[(u8Indx + u8Base)].u16Value++;
                    }
                }
            }
            else
            {
                uint32_t u32ErrState;

                u32ErrState = (((uint32_t)sStateADCS.TLM.App.Byte5.u8DataByte << 16) +
                               ((uint32_t)sStateADCS.TLM.App.Byte4.u8DataByte <<  8) +
                               ((uint32_t)sStateADCS.TLM.App.Byte3.u8DataByte      ));

                u8Base      = (uint8_t)eCUBEADCS_COMMON_DIAG_CNTS_CUBESENSE1_COMM_ERR;

                for (u8Indx = 0; u8Indx < CUBEADCS_DIAG_TLM132_ERR_APP_CNTS_NUM; ++u8Indx)
                {
                    if ( 0 != (uint8_t)((u32ErrState >> u8Indx) & 0x01) )
                    {
                    	CubeADCS_Err_Cnts[u8Indx + u8Base].u16Value++;
                    }
                }
            }

            break;
        }
        case eCUBEADCS_CMD_ID_135: /* TLM135 */
        {
            if ( eCUBEADCS_MODE_APPLICATION == eMode )
            {
                uint8_t u8Base;
                uint8_t u8ErrState;

                u8ErrState = sStateErr.ACP_State.u8DataByte;
                u8Base     = (uint8_t)eCUBEADCS_COMMON_DIAG_CNTS_ADCS_CONFIG_LOAD_ERR;

                for (uint8_t u8Indx = 0; u8Indx < CUBEADCS_DIAG_TLM135_ERR_CNTS_NUM; ++u8Indx)
                {
                    if ( 0 != (uint8_t)((u8ErrState >> u8Indx) & 0x01) )
                    {
                    	CubeADCS_Err_Cnts[u8Indx + u8Base].u16Value++;
                    }
                }
            }
            break;
        }
        case eCUBEADCS_CMD_ID_224: /* TLM224 */
        {
            if ( eCUBEADCS_MODE_APPLICATION == eMode )
            {
                uint8_t u8Base;
                uint32_t u32ErrState;

                /* Byte0 contains two mtm status flags - BIT4 and BIT5, which we escape here in order to align with the enums following eCUBEADCS_COMMON_DIAG_CNTS_ORBIT_PARAM_INVALID_ERR  */
                u32ErrState = ((  (uint32_t)sStateADCS2.Byte2.u8DataByte << 16 ) +
                               (  (uint32_t)sStateADCS2.Byte1.u8DataByte <<  8 ) +
                               ((((uint32_t)sStateADCS2.Byte0.u8DataByte << 2) & 0x3C) | (sStateADCS2.Byte0.u8DataByte & 0xC0)) ) >> 2;

                u8Base = (uint8_t)eCUBEADCS_COMMON_DIAG_CNTS_ORBIT_PARAM_INVALID_ERR;

                for (uint8_t u8Indx = 0; u8Indx < CUBEADCS_DIAG_TLM224_ERR_CNTS_NUM; ++u8Indx)
                {
                    if ( 0 != (uint8_t)((u32ErrState >> u8Indx) & 0x01) )
                    {
                    	CubeADCS_Err_Cnts[ u8Indx + u8Base ].u16Value++;
                    }
                }
            }

            break;
        }
        case eCUBEADCS_CMD_ID_128: /* TLM128 */
        case eCUBEADCS_CMD_ID_129: /* TLM129 */
        case eCUBEADCS_CMD_ID_130: /* TLM130 */
        case eCUBEADCS_CMD_ID_197: /* TLM197 */

            /* No DIAG counters related to these TLM messages */
            break;
        default:
            break;
    }
}

/** @brief Set reaction wheels speed to the indicated RPM value
 *
 *  @param[in] sRPM reaction wheels speed
 *
 */
static void fs_CubeADCS_SetRWheelsRPM(CubeADCS_RWheels_Speed_t sRPM)
{
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;
    CubeADCS_TC_17_t sData;

    CubeADCS_CmdCfg_t sCmdStruct;

    sData.RWheelsRPM.i16RWheel_X = sRPM.i16RWheel_X;
    sData.RWheelsRPM.i16RWheel_Y = sRPM.i16RWheel_Y;
    sData.RWheelsRPM.i16RWheel_Z = sRPM.i16RWheel_Z;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_17, (uint8_t *)&sData, CUBEADCS_TC_17_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    for (uint8_t u8Rtry = 0; u8Rtry < CUBEADCS_RTRY_TC_CNT; ++u8Rtry)
    {
        if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) ) {
            break;
        }
    }
}

/** @brief  Set commanded angles value to a given offset from NADIR
 *
 *  @param[in] sCommandAngles desired offset angles
 *
 */
static void fs_CubeADCS_SetCommandedAngles(CubeADCS_Command_Angles_t sCommandAngles)
{
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;
    CubeADCS_TC_15_t sData;

    CubeADCS_CmdCfg_t sCmdStruct;

    sData.CommandedAngles.i16RollAngle  = sCommandAngles.i16RollAngle;
    sData.CommandedAngles.i16PitchAngle = sCommandAngles.i16PitchAngle;
    sData.CommandedAngles.i16YawAngle   = sCommandAngles.i16YawAngle;

    CubeADCS_PREPCmd(&sCmdStruct, eCUBEADCS_CMD_ID_15, (uint8_t *)&sData, CUBEADCS_TC_15_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    for (uint8_t u8Rtry = 0; u8Rtry < CUBEADCS_RTRY_TC_CNT; ++u8Rtry)
    {
        if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) ) {
            break;
        }
    }
}

/** @brief Update the Health Check TLM request communication status
 *
 */
static void fs_CubeADCS_UpdateHCheckCommStatuses(uint8_t u8CmdID)
{
	(void)cubeadcs_lock_data_access(0U);

    switch ( u8CmdID )
    {
        case eCUBEADCS_CMD_ID_128:
            CubeADCS_OpStatus.Status.CommStatus.TLM128 = CubeADCS_OpStatus.Comm;
            break;
        case eCUBEADCS_CMD_ID_129:
        	CubeADCS_OpStatus.Status.CommStatus.TLM129 = CubeADCS_OpStatus.Comm;
        	break;
        case eCUBEADCS_CMD_ID_130:
            CubeADCS_OpStatus.Status.CommStatus.TLM130 = CubeADCS_OpStatus.Comm;
            break;
        case eCUBEADCS_CMD_ID_132:
            CubeADCS_OpStatus.Status.CommStatus.TLM132 = CubeADCS_OpStatus.Comm;
            break;
        case eCUBEADCS_CMD_ID_135:
            CubeADCS_OpStatus.Status.CommStatus.TLM135 = CubeADCS_OpStatus.Comm;
            break;
        case eCUBEADCS_CMD_ID_224:
        	CubeADCS_OpStatus.Status.CommStatus.TLM224 = CubeADCS_OpStatus.Comm;
        	break;
        case eCUBEADCS_CMD_ID_197:
        	CubeADCS_OpStatus.Status.CommStatus.TLM197 = CubeADCS_OpStatus.Comm;
        	break;
        default:
        	break;
    }

    (void)cubeadcs_unlock_data_access();
}

/** @brief Set a new system state configuration for the CubeADCS
 *
 *  @param[in] eReqCfg the new system state configuration
 *
 *  @return operation result
 *
 *  @note Takes ~1100ms to execute. RUN mode MUST be set first.Estimation and control modes
 *        cannot be set until the periphery nodes are booted. Estimation mode MUST be set first
 *        (CubeADCS allows this) followed by the control mode. If the estimation mode requires
 *        some periphery and it is not enabled we will enter error handling through the error
 *        handling logic.
 *
 */
static eCubeADCS_StdRply fs_CubeADCS_ApplyNewSysStateCfg(eCubeADCS_CfgType eReqCfg)
{
    uint8_t u8Status = CUBEADCS_SYS_STATE_CHANGE_START;

    eCubeADCS_StdRply eRetStatus = eCUBEADCS_STDRPLY_ERR;

    CUBEADCS_TRACE_DBG("%s: CHANGE FROM %02d TO %02d, ENTRY\r", CUBEADCS_HEAD, eADCSCfg.eReqCfg, eReqCfg);


    /* NOTE: Enter Error_Handling in Debug Mode on mismatch */
    if ( eReqCfg != asCubeADCS_SysStates[eReqCfg].eCfgType )
    {
    	EXEH_vException(eEXEHSeverity_Fatal, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_USAGE_ERROR, __LINE__);
    }

    /* Update operational status */
    (void)CubeADCS_SendCmdWithChecks(&aHealthCheckState[ eCUBEADCS_IDLE_STATE_CMD_ID_132 ], CUBEADCS_DIAG_UPDATE_OK, CUBEADCS_VALIDATE_DATA_TRUE);

    (void)CubeADCS_SendCmdWithChecks(&aHealthCheckState[ eCUBEADCS_IDLE_STATE_CMD_ID_197 ], CUBEADCS_DIAG_UPDATE_OK, CUBEADCS_VALIDATE_DATA_TRUE);

    if ( SAFE_TRUE != fs_cubeadcs_get_simulation_mode_en_status() )
    {
    	/* Set run mode */
    	if ( asCubeADCS_SysStates[ eReqCfg ].eRunMask == CubeADCS_GetADCSRunMode() )
    	{
    		u8Status |= CUBEADCS_SYS_STATE_RUN_MODE_SET;
    		CUBEADCS_TRACE_DBG("%s: 1/4 RUN MODE ALREADY SET\r", CUBEADCS_HEAD);
    	}
    	else
    	{
    		CubeADCS_SetADCSRunMode(asCubeADCS_SysStates[ eReqCfg ].eRunMask);
    		CUBEADCS_TRACE_DBG("%s: 1/4 RUN MODE SET\r", CUBEADCS_HEAD);
    	}

    	osDelay(200);

    	/* Set CubeADCS nodes power state */
    	if ( asCubeADCS_SysStates[ eReqCfg ].uNodePwrMask.raw != (CubeADCS_GetADCSNodesPwrMask()).raw )
    	{
    		CubeADCS_SetPwrNodeStates(asCubeADCS_SysStates[ eReqCfg ].uNodePwrMask);
    		CUBEADCS_TRACE_DBG("%s: 2/4 NODE POWER STATE SET\r", CUBEADCS_HEAD);
    	}
    	else
    	{
    		u8Status |= CUBEADCS_SYS_STATE_NODE_PWR_SET;
    		CUBEADCS_TRACE_DBG("%s: 2/4 NODE POWER STATE ALREADY SET\r", CUBEADCS_HEAD);
    	}

    	osDelay(400);
    }
    else
    {
    	/* Set run mode and nodes power state when in simulation mode */
    	u8Status |= CUBEADCS_SYS_STATE_RUN_MODE_SET;
    	u8Status |= CUBEADCS_SYS_STATE_NODE_PWR_SET;
    }

    /* Set estimation mode */
    if ( asCubeADCS_SysStates[ eReqCfg ].eEstMode == CubeADCS_GetEstMode() )
    {   u8Status |= CUBEADCS_SYS_STATE_EST_MODE_SET;
        CUBEADCS_TRACE_DBG("%s: 3/4 ESTIM MODE ALREADY SET\r", CUBEADCS_HEAD);
    }
    else
    {   CubeADCS_SetEstimationMode(asCubeADCS_SysStates[ eReqCfg ].eEstMode);
        CUBEADCS_TRACE_DBG("%s: 3/4 ESTIM MODE SET\r", CUBEADCS_HEAD);
    }

    osDelay(200);

    /* Set control mode */
    if ( asCubeADCS_SysStates[ eReqCfg ].eCntrlMask == CubeADCS_GetCntrlMode() )
    {   u8Status |= CUBEADCS_SYS_STATE_CNTRL_MODE_SET;
        CUBEADCS_TRACE_DBG("%s: 4/4 CTRL MODE ALREADY SET\r", CUBEADCS_HEAD);
    }
    else
    {   CubeADCS_SetControlMode(asCubeADCS_SysStates[ eReqCfg ].eCntrlMask, CUBEADCS_TC_13_NO_TIMEOUT);
        CUBEADCS_TRACE_DBG("%s: 4/4 CTRL MODE SET\r", CUBEADCS_HEAD);
    }

    osDelay(200);

    if ( CUBEADCS_SYS_STATE_CHANGE_SUCCESSFUL == u8Status )
    {
    	eRetStatus = eCUBEADCS_STDRPLY_OK;
    }

    CUBEADCS_TRACE_DBG("%s: u8Status [=15?] %02d\r", CUBEADCS_HEAD, u8Status);

    CUBEADCS_TRACE_DBG("%s: CHANGE FROM %02d TO %02d, EXIT\r", CUBEADCS_HEAD, eADCSCfg.eReqCfg, eReqCfg);

    return eRetStatus;
}

/** @brief Initialize the operational status kept by the sw module
 *
 */
static void fs_cubeadcs_init_op_status(void)
{
	CubeADCS_Status_t sTmpStatus;

	cubeadcs_persist_get_nvm_stored_status(&sTmpStatus);

	(void)cubeadcs_lock_data_access(0U);

	/* Get important statuses as stored in the flash */
	CubeADCS_OpStatus.Status.Commissioning = sTmpStatus.Commissioning;

	/* Invalidate the CubeADCS state at startup before first request */
	CubeADCS_OpStatus.Mode = eCUBEADCS_MODE_INVALID;

	(void)cubeadcs_unlock_data_access();
}

/** @brief Set the mode/node type - bootloader or application
 *
 */
static void fs_cubeadcs_set_node_type(eCubeADCS_Mode_t eMode)
{
	(void)cubeadcs_lock_data_access(0U);

	CubeADCS_OpStatus.Mode = eMode;

	(void)cubeadcs_unlock_data_access();
}

/** @brief Get last status from communication with the cubeadcs
 *
 *  @return the last communication status
 *
 */
static eCubeADCS_Comm_Status_t fs_cubeadcs_get_last_comm_status(void)
{
	CubeADCS_Op_Status_t op_status;

	(void)cubeadcs_get_op_status(&op_status);

	return CubeADCS_OpStatus.Comm;
}

/** @brief Lock access to the communication port
 *
 *  @param[in] u32WaitTimeMS time to wait to acquire mutex lock
 *
 *  @retval true: successfully acquired lock
 *  @retval false: failure to acquire lock
 */
static bool fs_cubeadcs_lock_comm_access(uint32_t u32WaitTimeMS)
{
	bool bRes = true;

	if ( osOK != osMutexAcquire(cubeadcs_comm_mutex, u32WaitTimeMS) ) {
		bRes = false;

		EXEH_vException(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_OS_ERROR, __LINE__);
	}

	return bRes;
}

/** @brief Unlock access to the communication port
 *
 *  @param[in] u32WaitTimeMS time to wait to acquire mutex lock
 *
 *  @retval true: successful unlock
 *  @retval false: successful lock
 */
static bool fs_cubeadcs_unlock_comm_access(void)
{
	bool bRes = true;

	if ( osOK != osMutexRelease(cubeadcs_comm_mutex) ) {

		bRes = false;

		EXEH_vException(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS, eEXEH_CUBEADCS_EXCEPTION_OS_ERROR, __LINE__);
	}

	return bRes;
}

/** @brief Check for commanded bootloader mode
 *
 *  @note Check if a reboot into Application is necessary. Typically, this will
 * 		  happen if the CubeComputers undergoes a reset but the OBC doesn't.A TLM128
 * 		  request during the CubeComputer boot procedure may result in the latter
 * 		  remaining in bootloader.
 */
static bool fs_cubeadcs_is_boot_commanded(void)
{
	bool bRes;
	CubeADCS_Op_Status_t op_status;

	bRes = true;

	(void)cubeadcs_get_op_status(&op_status);

	/* Reboot only if no application load errors occurred */
	if ( eCUBEADCS_TLM130_BOOT_SUCCESS == op_status.State.prog_status.eBootStatus )
	{
		/* Start the application if the boot was not commanded */
		if ( eCUBEADCS_TLM129_BOOTCAUSE_COMMANDED != ((op_status.State.boot_status.rst_and_boot >> 4) & 0x0F ) )
		{
			(void)cubeadcs_reset(eCUBEADCS_MODE_APPLICATION);
			bRes = false;
		}
	}

	return bRes;
}

/** @brief Update the ADCS System State Configuration Request status
 *
 *  @param[in] eStatus the update status
 */
static void fs_cubeadcs_update_adcs_sys_state_cfg_status(eCubeADCS_SysStateCfgStatus_t eStatus)
{
    eADCSCfg.eReqCfgStatus = eStatus;
}

/** @brief Change the CubeADCS state machine state
 *
 *  @param[in] eReqState the new state
 *
 *  @note SM change is allowed only if the bootloader or the application is running
 */
static bool fs_cubeadcs_set_sm_state(eCubeADCS_State_t eReqState)
{
	bool bRes;

	eCubeADCS_Mode_t eMode = CubeADCS_GetNodeType();

	/* Handle fist the initial wait period for the ACP boot. During this period the node type will be invalid. */
	if ( (eCUBEADCS_STATE_INIT_WAIT == CubeADCS_GetState()) && (eCUBEADCS_STATE_INIT == eReqState) ) {
		CubeADCS_State = eReqState;

		bRes = true;

	}
	else if ( (eCUBEADCS_MODE_APPLICATION == eMode) || (eCUBEADCS_MODE_BOOTLOADER == eMode) ) {
		CubeADCS_State = eReqState;

		bRes = true;
	}
	else {
		bRes = false;
	}

	return bRes;
}

/** @brief Triggers the state machine that determines which custom logic is to be executed
 *
 *  @param[in] eADCSCfgType the system state config
 *
 *  @retval 1: Success
 *  @retval 0: Failure
 *  @retval 255: Error
 *
 */
static uint8_t fs_cubeadcs_execute_custom_logic(eCubeADCS_CfgType eADCSCfgType) {

    uint8_t u8RetVal;

    /* Retrieve the current system state configuration */
    CubeADCS_SysSCfg_t sCurrentSysStateCfg;
    cubeadcs_get_adcs_state_cfg(&sCurrentSysStateCfg);

    /* If the current system state configuration matches the given configuration */
    if (sCurrentSysStateCfg.eReqCfg == eADCSCfgType)
    {
        CUBEADCS_TRACE_DBG("[AAA]: ----- LOGIC FOR: %d\r", eADCSCfgType);
        /* Trigger different logic based on system state configuration */
        switch (eADCSCfgType)
        {

            case eCUBEADCS_CFGTYPE_ATTITUDE_CHANGE:
            {
                uint8_t u8Res = 0;

                /* Evaluate Y-Thompson conditions */
                u8Res = fs_cubeadcs_attitude_change_mode_check();

                /* Y-Thompson is stable */
                if (true == u8Res)
                {
                    /* Custom logic is completed, switch to NO_CONTROL system state */
                    u8RetVal = 1;
                    cubeadcs_set_state_cfg(eCUBEADCS_CFGTYPE_NO_CONTROL, CUBEADCS_EXEC_STATE_REQ);

                }
                /* Y-Thompson is still not stable */
                else if (false == u8Res)
                {
                    /* Flag custom logic as in progress */
                    u8RetVal = 0;
                }
                /* There was an error evaluating Y-Thompson conditions */
                else
                {
                    u8RetVal = 255;
                }
                break;
            }

            case eCUBEADCS_CFGTYPE_ORBITAL_CHANGE:
            {
                uint8_t u8Res = 0;

                /* Evaluate state transition progress */
                u8Res = fs_cubeadcs_orbital_change_mode_check();

                /* ADCS has transitioned to orbital change mode */
                if (true == u8Res)
                {
                    /* Custom logic is completed, flag state transition as completed */
                    u8RetVal = 1;
                    /* Update the system state configuration to COMPLETE */
                    fs_cubeadcs_update_adcs_sys_state_cfg_status(eSYSSTATECFGSTATUS_OK);

                }
                /* Conditions for orbital change mode have not been met */
                else if (false == u8Res)
                {
                    /* Flag custom logic as in progress */
                    u8RetVal = 0;
                }
                /* There was an error evaluating state transition conditions */
                else
                {
                    u8RetVal = 255;
                }
                break;
            }

            default:
            {
                /* Return an error when there is no implemented custom logic for the chosen system state configuration */
                u8RetVal = 255;
                break;
            }

        }
    }
    else
    {
        /* Return an error if the system state configurations do not match */
        u8RetVal = 255;
    }

    return u8RetVal;
}

/** @brief Function for checking the exit condition of Attitude Change mode
 *
 *  @param[in] eADCSCfgType the system state config
 *
 *  @retval 1: Success
 *  @retval 0: Failure
 *  @retval 255: Error
 *
 */
static uint8_t fs_cubeadcs_attitude_change_mode_check(void) {

    uint8_t u8Res = 0;

    DATA_CACHE_AOCS_CNTRL_TLM_t sADCSData;

    /* Retrieve data cache information for CubeADCS */
    if ( DC_DATA_STATUS_OK != dc_get_aocs_cntrl_tlm_data(&sADCSData) )
    {
    	return 255; // Failed to retrieve data cache information, return error
    }

    /* Retrieve the current system state configuration */
    CubeADCS_SysSCfg_t sCurrentSysStateCfg;
    cubeadcs_get_adcs_state_cfg(&sCurrentSysStateCfg);

    /* Only evaluate Y-Thompson state if the system state configuration is correct */
    if ( eCUBEADCS_CFGTYPE_ATTITUDE_CHANGE == sCurrentSysStateCfg.eReqCfg )
    {
        CUBEADCS_TRACE_DBG("[AAA]: ----- ENTERED_ATTITUDE_CHECK\r");
        CubeADCS_AngRate_Formatted_t sAngRateVecTmp;
        int32_t i32OmegaLowThresh;
        int32_t i32OmegaHighThresh;
        uint8_t u8ChkCnt = 0;

        /* Retrieve estimated angular velocities from the data cache */
        sAngRateVecTmp.X = sADCSData.ai32EstAngRateVec[0];
        sAngRateVecTmp.Y = sADCSData.ai32EstAngRateVec[1];
        sAngRateVecTmp.Z = sADCSData.ai32EstAngRateVec[2];

        /* Get the Y-Axis angular velocity boundaries for Y-Thompson */
        if ( true == conops_get_thresh_val(&i32OmegaLowThresh, 0, CONOPS_THRESHOLDVALUETYPES_ANGVEL_RANGE ) )
        {
            if ( true == conops_get_thresh_val(&i32OmegaHighThresh, 1, CONOPS_THRESHOLDVALUETYPES_ANGVEL_RANGE ) )
            {
                /* If both boundaries are successfully obtained
                   start checking each axis separately */

                /* Is Y-Axis angular velocity within the required boundaries? */
                if ( (i32OmegaHighThresh > sAngRateVecTmp.Y) && (sAngRateVecTmp.Y > i32OmegaLowThresh) )
                {
                	++u8ChkCnt;
                }

                /* Is X-Axis angular velocity within the predefined boundaries? */
                if ( (CUBEADCS_Y_THOMSON_POS_THRESH_MRAD_S > sAngRateVecTmp.X) && (sAngRateVecTmp.X > CUBEADCS_Y_THOMSON_NEG_THRESH_MRAD_S) )
                {
                	++u8ChkCnt;
                }

                /* Is Z-Axis angular velocity within the predefined boundaries? */
                if ( (CUBEADCS_Y_THOMSON_POS_THRESH_MRAD_S > sAngRateVecTmp.Z) && (sAngRateVecTmp.Z > CUBEADCS_Y_THOMSON_NEG_THRESH_MRAD_S) )
                {
                	++u8ChkCnt;
                }

                CUBEADCS_TRACE_DBG("[AAA]: thresholds HIGH: %4d, %4d, %4d\r", CONOPS_ADCS_Y_THOMSON_POS_THRESH_MRAD_S, i32OmegaHighThresh, CONOPS_ADCS_Y_THOMSON_POS_THRESH_MRAD_S);
                CUBEADCS_TRACE_DBG("[AAA]:  current angles: %4d, %4d, %4d\r", sAngRateVecTmp.X, sAngRateVecTmp.Y, sAngRateVecTmp.Z);
                CUBEADCS_TRACE_DBG("[AAA]: thresholds  LOW: %4d, %4d, %4d\r", CONOPS_ADCS_Y_THOMSON_NEG_THRESH_MRAD_S, i32OmegaLowThresh, CONOPS_ADCS_Y_THOMSON_NEG_THRESH_MRAD_S);
                CUBEADCS_TRACE_DBG("[AAA]: conditions met: %d\r", u8ChkCnt);
            }
        }

        /* If all three checks passed, ADCS is in stable Y-Thompson */
        if ( (uint8_t)0x03 == u8ChkCnt)
        {
            u8Res = true; // Y-Thompson completed
        }
        else
        {
            u8Res = false; // Y-Thompson not completed
        }

        CUBEADCS_TRACE_DBG("[AAA]: ----- EXIT_ATTITUDE_CHECK\r");
    }
    else
    {
        u8Res = 255; // Wrong system state configuration, return error
    }

    return u8Res;
}

/** @brief Function for checking the exit condition of Orbital Change mode
 *
 *  @param[in] eADCSCfgType the system state config
 *
 *  @retval 1: Success
 *  @retval 0: Failure
 *  @retval 255: Error
 *
 */
static uint8_t fs_cubeadcs_orbital_change_mode_check(void)
{
    uint8_t u8Res = 0;

	DATA_CACHE_AOCS_CNTRL_TLM_t sADCSData;

    /* Retrieve data cache information for CubeADCS */
    if ( DC_DATA_STATUS_OK != dc_get_aocs_cntrl_tlm_data(&sADCSData) )
        return 255; // Failed to retrieve data cache information, return error

    /* Retrieve stable pointing thresholds from NVM */
    cubeadcs_angle_limits_t sTmp_angle_limits;

    /* These come in millidegrees format, so they have to be reformatted */
    Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_ANGLE_LIMITS, &sTmp_angle_limits);

    /* Retrieve the current system state configuration */
    CubeADCS_SysSCfg_t sCurrentSysStateCfg;
    cubeadcs_get_adcs_state_cfg(&sCurrentSysStateCfg);

    /* Only evaluate the following conditions if the system state configuration is correct */
    if ( eCUBEADCS_CFGTYPE_ORBITAL_CHANGE == sCurrentSysStateCfg.eReqCfg )
    {
        CUBEADCS_TRACE_DBG("[AAA]: ----- ENTERED_ORBITAL_CHECK\r");
        static uint8_t u8ChkCnt = 0;

        /* AA TODO: These can probably be made more compact, but check if the whole thing works first, then optimize */
        double currentRoll;
        double currentRollRate;
        double currentPitch;
        double currentPitchRate;
        double currentYaw;
        double currentYawRate;

        /* Retrieve the angle and angle rate limits from NVM */
        double stablePointingThresholdAngle     = fabs((double)sTmp_angle_limits.stable_pointing_threshold_angle * 0.001F);			// mdeg -> deg
        double stablePointingThresholdAngleRate = fabs((double)sTmp_angle_limits.stable_pointing_threshold_angle_rate * 0.001F);	// mdeg/s -> deg/s

        /* Retrieve absolute value of estimated angular positions from the data cache */
        currentRoll  = fabs(((double)sADCSData.ai32EstAttAngles[0] * 0.001F)); // mdeg -> deg
        currentPitch = fabs(((double)sADCSData.ai32EstAttAngles[1] * 0.001F));
        currentYaw   = fabs(((double)sADCSData.ai32EstAttAngles[2] * 0.001F));

        /* Retrieve absolute value of estimated angular velocities from the data cache */
        currentRollRate  = fabs(((double)sADCSData.ai32EstAngRateVec[0] * 0.001F) * CUBEADCS_TO_DEG_CONV); // mrad/s -> rad/s -> deg/s
        currentPitchRate = fabs(((double)sADCSData.ai32EstAngRateVec[1] * 0.001F) * CUBEADCS_TO_DEG_CONV);
        currentYawRate   = fabs(((double)sADCSData.ai32EstAngRateVec[2] * 0.001F) * CUBEADCS_TO_DEG_CONV);

        if (0 == u8ChkCnt)
        {
        CUBEADCS_TRACE_DBG("[AAA]:           ANGLES: %3.2f, %3.2f, %3.2f\r", ((double)sADCSData.ai32EstAttAngles[0] * 0.001F), ((double)sADCSData.ai32EstAttAngles[1] * 0.001F), ((double)sADCSData.ai32EstAttAngles[2] * 0.001F));
        CUBEADCS_TRACE_DBG("[AAA]:           LIMITS: %3.2f, %3.2f, %3.2f\r", (double)sTmp_angle_limits.stable_pointing_threshold_angle * 0.001F, (double)sTmp_angle_limits.stable_pointing_threshold_angle * 0.001F, (double)sTmp_angle_limits.stable_pointing_threshold_angle * 0.001F);
        CUBEADCS_TRACE_DBG("[AAA]:       ABS_ANGLES: %3.2f, %3.2f, %3.2f\r", currentRoll, currentPitch, currentYaw);
        CUBEADCS_TRACE_DBG("[AAA]: ABS_ANGLE_LIMITS: %3.2f, %3.2f, %3.2f\r\r", stablePointingThresholdAngle, stablePointingThresholdAngle, stablePointingThresholdAngle);

        CUBEADCS_TRACE_DBG("[AAA]:            RATES: %3.2f, %3.2f, %3.2f\r", ((double)sADCSData.ai32EstAngRateVec[0] * 0.001F) * CUBEADCS_TO_DEG_CONV, ((double)sADCSData.ai32EstAngRateVec[1] * 0.001F) * CUBEADCS_TO_DEG_CONV, ((double)sADCSData.ai32EstAngRateVec[2] * 0.001F) * CUBEADCS_TO_DEG_CONV);
        CUBEADCS_TRACE_DBG("[AAA]:           LIMITS: %3.2f, %3.2f, %3.2f\r", (double)sTmp_angle_limits.stable_pointing_threshold_angle_rate * 0.001F, (double)sTmp_angle_limits.stable_pointing_threshold_angle_rate * 0.001F, (double)sTmp_angle_limits.stable_pointing_threshold_angle_rate * 0.001F);
        CUBEADCS_TRACE_DBG("[AAA]:        ABS_RATES: %3.2f, %3.2f, %3.2f\r", currentRollRate, currentPitchRate, currentYawRate);
        CUBEADCS_TRACE_DBG("[AAA]:  ABS_RATE_LIMITS: %3.2f, %3.2f, %3.2f\r", stablePointingThresholdAngleRate, stablePointingThresholdAngleRate, stablePointingThresholdAngleRate);
        }

        /* STEP 1: Stable nadir check */
        /* Are the angles and angle rates within boundaries? */
        if ((currentRoll      < stablePointingThresholdAngle) &&
            (currentPitch     < stablePointingThresholdAngle) &&
            (currentYaw       < stablePointingThresholdAngle) &&
            (currentRollRate  < stablePointingThresholdAngleRate) &&
            (currentPitchRate < stablePointingThresholdAngleRate) &&
            (currentYawRate   < stablePointingThresholdAngleRate))
        {
            /* Stable nadir is complete */
            u8ChkCnt = 1;
            CUBEADCS_TRACE_DBG("[AAA]: ORBITAL_CHECK_COND_1_OK\r");
        }

        /* STEP 2: Apply required offsets only if there is stable nadir */
        if (1 == u8ChkCnt)
        {
            /* Push the desired offsets into the appropriate struct */
            CubeADCS_Command_Angles_t sAngles;

            sAngles.i16RollAngle  = orbital_change_roll;
            sAngles.i16PitchAngle = orbital_change_pitch;
            sAngles.i16YawAngle   = orbital_change_yaw;

            /* Set the desired offsets */
            fs_CubeADCS_SetCommandedAngles(sAngles);

            /* AA TODO: Can do a check if the commanded angles match the desired ones (get version of the set command) */

            /* Offset angles from nadir pointing are set */
            u8ChkCnt = 2;
            CUBEADCS_TRACE_DBG("[AAA]: ORBITAL_CHECK_COND_2_OK\r");
        }

        /* STEP 3: Check how close the satellite is to the desired offsets */
        if (2 == u8ChkCnt)
        {
            double currentRollDiff  = fabs(fabs(((uint32_t)orbital_change_roll  * 10)) - fabs(sADCSData.ai32EstAttAngles[0])) * 0.001F;
            double currentPitchDiff = fabs(fabs(((uint32_t)orbital_change_pitch * 10)) - fabs(sADCSData.ai32EstAttAngles[1])) * 0.001F;
            double currentYawDiff   = fabs(fabs(((uint32_t)orbital_change_yaw   * 10)) - fabs(sADCSData.ai32EstAttAngles[2])) * 0.001F;

            CUBEADCS_TRACE_DBG("[AAA]:  ANGLE_SET_POINT: %3.2f, %3.2f, %3.2f\r", (double)orbital_change_roll  * 0.01F, (double)orbital_change_pitch  * 0.01F, (double)orbital_change_yaw  * 0.01F);
            CUBEADCS_TRACE_DBG("[AAA]:   ABS_ANGLE_DIFF: %3.2f, %3.2f, %3.2f\r", currentRollDiff, currentPitchDiff, currentYawDiff);
            CUBEADCS_TRACE_DBG("[AAA]: ABS_ANGLE_LIMITS: %3.2f, %3.2f, %3.2f\r\r", stablePointingThresholdAngle, stablePointingThresholdAngle, stablePointingThresholdAngle);
            CUBEADCS_TRACE_DBG("[AAA]:         ABS_RATE: %3.2f, %3.2f, %3.2f\r", currentRollRate, currentPitchRate, currentYawRate);
            CUBEADCS_TRACE_DBG("[AAA]:  ABS_RATE_LIMITS: %3.2f, %3.2f, %3.2f\r", stablePointingThresholdAngleRate, stablePointingThresholdAngleRate, stablePointingThresholdAngleRate);
            /* Are the angle and angle rate differences within boundaries? */
            /* Used boundaries are the same as stable-nadir */
            /* 3-AXIS should be capable of equal pointing accuracy at all angles */
            if ( (currentRollDiff     < stablePointingThresholdAngle) &&
                 (currentPitchDiff    < stablePointingThresholdAngle) &&
                 (currentYawDiff      < stablePointingThresholdAngle) &&
                 (currentRollRate     < stablePointingThresholdAngleRate) &&
                 (currentPitchRate    < stablePointingThresholdAngleRate) &&
                 (currentYawRate      < stablePointingThresholdAngleRate))
            {
                /* Offset angles from nadir pointing are reached */
                u8ChkCnt = 3;
                CUBEADCS_TRACE_DBG("[AAA]: ORBITAL_CHECK_COND_3_OK\r");
            }
        }

        CUBEADCS_TRACE_DBG("[AAA]: conditions met: %d\r", u8ChkCnt);

        /* If all three checks passed, ADCS has completed orbital change mode transition */
        if ( 3 == u8ChkCnt)
        {
            u8Res = true; // Satellite has reached the required offset angles
            u8ChkCnt = 0; // Clear conditions and prepare for another payload
        }
        else
        {
            u8Res = false; // Satellite has -not- reached the required offset angles
        }

        CUBEADCS_TRACE_DBG("[AAA]: ----- EXIT_ORBITAL_CHECK\r");
    }
    else
    {
        u8Res = 255; // Wrong system state configuration, return error
    }

    return u8Res;
}

/** @brief Get simulation mode status
 *
 *  @retval 0: False - disabled
 *  @retval 255: True - enalbed
 */
static safe_bool_t fs_cubeadcs_get_simulation_mode_en_status(void)
{
	cubeadcs_sim_mode_t en_sim_mode_status;

	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_SIMULATION_MODE, &en_sim_mode_status);

	return en_sim_mode_status.en_sim_mode;
}

/* ******************************************************************************************* */
