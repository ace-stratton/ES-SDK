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
 * @file     cubeadcs_errhandl.c
 * @brief    Implementation of various error handling strategies based on errors reported by the CubeADCS. Use with caution, no fully tested.
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/

#include "../inc/cubeadcs_errhandl.h"
#include "../inc/cubeadcs_persist.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/** @brief Threshold in rad/s for the activation of a specific error handling logic */
#define CUBEADCS_ERR_CONTROL_MODE_ANG_VEL_THRESH ((float)1.745)
/** @brief Macro used get the correct bit shift based on the error handling logic */
#define CUBEADCS_ERRHANDL_ERR_MASK(shift) ((uint16_t)(0x0001 << ((uint16_t)(shift))))

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

enum {
	eERR_BIT_NodeRecoveryErr = 0,
	eERR_BIT_RangeErr	   		,
	eERR_BIT_RateSensFailure	,
	eERR_BIT_MagnetometerErr	,
	eERR_BIT_OrbitParamsErr 	,
	eERR_BIT_ConfigInvalid  	,
	eERR_BIT_CntrlModeChgErr	,
	eERR_BIT_EstModeChgErr  	,
	eERR_BIT_SysStateChgErr 	,
};

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

CubeADCS_Diag_ErrCnts_t CubeADCS_Err_Cnts [ eCUBEADCS_COMMON_DIAG_CNTS_NUMBER ];

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

/*------------------------------------------------------------------------------ */
/*-------------------------- Automatic Error Handling -------------------------- */
/*------------------------------------------------------------------------------ */

static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Mtm(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Cam1(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Cam2(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_CamStar(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Node(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_RateAndWheelRange(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_RateFail(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Orbit(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Config(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_CntrlMode(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_EstMode(uint8_t u8ErrNum);
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_SysStateCghErr(uint8_t u8ErrNum);
static void 			 fs_cubeadcs_errhandl_update_runtime_err(uint16_t u16RawErrData);

/** @brief Array used to configure the different error handling logic types
 *
 *  @note Last state is not an actual CubeADCS reported state, but an internal one. However, logically, it should be part of the error handling logic. Hence the + 1
 *  */
static CubeADCS_Diag_ErrHandlCnts_t  CubeADCS_Err_Handl [ CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM + 1] = {
		{.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_NODE_RECOVERY_ERR           , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 8, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Node },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_MAGMETER_RANGE_ERR          , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Mtm },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CAM1_SRAM_OVERCURRENT_DET   , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Cam1 },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CAM1_3V3_OVERCURRENT_DET    , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Cam1 },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CAM2_SRAM_OVERCURRENT_DET   , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Cam2 },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CAM2_3V3_OVERCURRENT_DET    , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Cam2 },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_STARTRACKER_OVERCURRENT_DET , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_CamStar },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_MAGNETOMETER_ERR            , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Mtm },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CAM1_SENSOR_BUSY_ERR        , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Cam1 },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CAM2_SENSOR_BUSY_ERR        , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 3, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Cam2 },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_RATE_SENSOR_RANGE_ERR       , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 1, .pErrHandlFunc = fs_CubeADCS_ErrHandl_RateAndWheelRange },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_WHEEL_SPEED_RANGE_ERR       , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 1, .pErrHandlFunc = fs_CubeADCS_ErrHandl_RateAndWheelRange },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_RATE_SENSOR_FAILURE_ERR     , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 1, .pErrHandlFunc = fs_CubeADCS_ErrHandl_RateFail },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_ORBIT_PARAM_INVALID_ERR     , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 5, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Orbit },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CONFIG_INVALID_ERR          , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 1, .pErrHandlFunc = fs_CubeADCS_ErrHandl_Config },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_CNTRL_MODE_CHG_INV_ERR      , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 1, .pErrHandlFunc = fs_CubeADCS_ErrHandl_CntrlMode },
        {.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_EST_CHG_INV_ERR             , .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 1, .pErrHandlFunc = fs_CubeADCS_ErrHandl_EstMode },
		{.eErrType = eCUBEADCS_COMMON_DIAG_CNTS_NUMBER             			, .u8ErrHandlActivationCnt = 0, .u8MaxActivationAllowed = 1, .pErrHandlFunc = fs_CubeADCS_ErrHandl_SysStateCghErr }
    };

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void CubeADCS_ErrHandl(void)
{
    if ( false == cubeadcs_persist_is_err_handl_en() )
    {
    	return;
    }

    for (uint8_t u8ErrNum = 0; u8ErrNum < CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM; ++u8ErrNum)
    {
        if ( 0 != CubeADCS_Err_Cnts[ CubeADCS_Err_Handl[u8ErrNum].eErrType ].u16Value )
        {
        	(*CubeADCS_Err_Handl[u8ErrNum].pErrHandlFunc)(u8ErrNum);
        }
    }
}

bool cubeadcs_errhandl_activate(uint8_t u8ErrNum)
{
	bool bRes = false;

	if ( true == cubeadcs_persist_is_err_handl_en() ) {
    	if ( u8ErrNum <= CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM) {
    		(*CubeADCS_Err_Handl[u8ErrNum].pErrHandlFunc)(u8ErrNum);
    		bRes = true;
    	}
    }

	return bRes;
}

void CubeADCS_ErrHandl_ClrErrHandlCntrActivCnt(uint8_t u8ErrHandlCntr)
{
    CubeADCS_Err_Handl[ u8ErrHandlCntr ].u8ErrHandlActivationCnt = 0;
}

uint8_t *CubeADCS_ErrHandl_GetErrHandlCntrActivCnt(uint8_t u8ErrHandlCntr)
{
    return &CubeADCS_Err_Handl[ u8ErrHandlCntr ].u8ErrHandlActivationCnt;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief Automatic Error Handling - Magnetometer
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_MAGMETER_RANGE_ERR
 *        eCUBEADCS_COMMON_DIAG_CNTS_MAGNETOMETER_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Mtm(uint8_t u8ErrNum)
{
	CubeADCS_TLM132_t uTlmData;

	if ( true != cubeadcs_get_op_status_adcs_state(&uTlmData) )
	{
		return eCUBEADCS_STDRPLY_ERR;
	}

	if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
	{
		/* Enable the motor MCU first to preserve control and estimation modes - otherwise they will be set to None */
		if ( !uTlmData.TLM.App.Byte1.Data.CubeControl_Motor_en ) {
			cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBECONTROL_MOTOR, eCUBE_ADCS_TC11_STATE_ON);
            osDelay(50);
        }

        switch ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt )
        {
        case 0:
            /* Power cycle periphery device */
            cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBECONTROL_SIGNAL, eCUBE_ADCS_TC11_STATE_OFF);
            osDelay(50);
            cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBECONTROL_SIGNAL, eCUBE_ADCS_TC11_STATE_ON);
            break;
        case 1:
            /* Initiate sampling of the redundant magnetometer */
            CubeADCS_ChngMtmSampling(eCUBEADCS_TC56_REDUNT_MTM_SIGNAL_MCU);
            break;
        case 2:
            /* Initiate sampling with the motor controller */
            CubeADCS_ChngMtmSampling(eCUBEADCS_TC56_MAIN_MTM_MOTOR_MCU);
            break;
        default:
            break;
        }

        CubeADCS_ClrErrFlags(); /* Clears the magnetometer error */

        if ( ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt == CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
        {
        	fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_MagnetometerErr));
        }
    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - CAM1
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_CAM1_SRAM_OVERCURRENT_DET
 *        eCUBEADCS_COMMON_DIAG_CNTS_CAM1_3V3_OVERCURRENT_DET
 *        eCUBEADCS_COMMON_DIAG_CNTS_CAM1_SENSOR_BUSY_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Cam1(uint8_t u8ErrNum)
{
    /* Power cycle node */
    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBESENSE_1, eCUBE_ADCS_TC11_STATE_OFF);

        osDelay(50);

        cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBESENSE_1, eCUBE_ADCS_TC11_STATE_ON);

        ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;

    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - CAM2
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_CAM2_SRAM_OVERCURRENT_DET
 *        eCUBEADCS_COMMON_DIAG_CNTS_CAM2_3V3_OVERCURRENT_DET
 *        eCUBEADCS_COMMON_DIAG_CNTS_CAM2_SENSOR_BUSY_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Cam2(uint8_t u8ErrNum)
{
    /* Power cycle node */
    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBESENSE_2, eCUBE_ADCS_TC11_STATE_OFF);

        osDelay(50);

        cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBESENSE_2, eCUBE_ADCS_TC11_STATE_ON);

        ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - CAM STAR TRACKER
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_STARTRACKER_OVERCURRENT_DET
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_CamStar(uint8_t u8ErrNum)
{
    /* Power cycle node */
    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBESTAR, eCUBE_ADCS_TC11_STATE_OFF);

        osDelay(50);

        cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBESTAR, eCUBE_ADCS_TC11_STATE_ON);

        ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - Node Recovery Error
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_NODE_RECOVERY_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Node(uint8_t u8ErrNum)
{
    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        uint32_t u32NodeStatus;

        u32NodeStatus = (cubeadcs_get_node_cntrl_status().u32RawData ^ cubeadcs_get_last_pwr_cntrl_tlmtr_data().u32RawData);

        if ( 0 != u32NodeStatus )
        {
            TODO("Check if only ON/OFF state is reported back or PWR state kept the same as well")

            uint32_t u32Mask;
            CubeADCS_Status_t sTmpAdcsStatus;

            // Shift out the command ID
            u32NodeStatus = (u32NodeStatus >> 8) & 0x0000FFFF;

            cubeadcs_persist_get_nvm_stored_status(&sTmpAdcsStatus);

            for (uint8_t u8Node = 0; u8Node < 8; u8Node++ )
            {
            	// Create a single bit set mask which corresponds to TLM197 mapping
                u32Mask = 1 << ((uint8_t)(2 * u8Node));

                // Extract the set bit and then shift it back to align with the NodeStatus
                sTmpAdcsStatus.NodeStatus.u8RawData |= (uint8_t)((u32NodeStatus & u32Mask) >> u8Node);
            }

            cubeadcs_persist_set_nvm_stored_status(&sTmpAdcsStatus);
        }

        CubeADCS_ClrErrFlags();

        fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_NodeRecoveryErr));

        ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - Rate Sensor or Wheel Speed Range Error
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_RATE_SENSOR_RANGE_ERR
 *        eCUBEADCS_COMMON_DIAG_CNTS_WHEEL_SPEED_RANGE_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_RateAndWheelRange(uint8_t u8ErrNum)
{
	CubeADCS_TLM132_t uTlmData;

	if ( true != cubeadcs_get_op_status_adcs_state(&uTlmData) )
	{
		return eCUBEADCS_STDRPLY_ERR;
	}

    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        CubeADCS_AngRateFormatted_t sAngRate;

        /* Stop all wheels */
        CubeADCS_StopRWheels();

        /* Set rate sensor mult to maximum value to try to get the actual body rate */
        CubeADCS_ChngRateSensorMult(eCUBEADCS_TC23_RATESENSORMULT_12);

        /* Get the state of the CubeADCS */
        (void)CubeADCS_SendCmdWithChecks(CubeADCS_GetHCheckCmdDetails(eCUBEADCS_IDLE_STATE_CMD_ID_132), CUBEADCS_DIAG_UPDATE_OK, CUBEADCS_VALIDATE_DATA_TRUE);

        /* Enable the CubeControl Signal MCU */
        if ( !uTlmData.TLM.App.Byte1.Data.CubeControl_Signal_en ) {
            cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBECONTROL_SIGNAL, eCUBE_ADCS_TC11_STATE_ON);
            osDelay(50);
        }

        /* Enable the Motor MCU */
        if ( !uTlmData.TLM.App.Byte1.Data.CubeControl_Motor_en ) {
            cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBECONTROL_MOTOR, eCUBE_ADCS_TC11_STATE_ON);
            osDelay(50);
        }

        /* Set estimation mode to MEMS rate */
        CubeADCS_SetEstimationMode(eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS);

        /* Give some time for the MEMS rate sensor to converge */
        osDelay(500);

        /* Get angular rate and decide if mode 8 or 9 should be entered */
        if ( eCUBEADCS_STDRPLY_OK == CubeADCS_GetAngularRate(&sAngRate, eCUBEADCS_ANGRATETYPE_EST) )
        {
            if ( sqrt((sAngRate.fX * sAngRate.fX) + (sAngRate.fY * sAngRate.fY) + (sAngRate.fZ * sAngRate.fZ)) > CUBEADCS_ERR_CONTROL_MODE_ANG_VEL_THRESH )
            {
                CubeADCS_SetControlMode(eCUBE_ADCS_TC_13_CONTROLMODE_VERY_FAST_SPIN_DETUMB, CUBEADCS_TC_13_NO_TIMEOUT);
            }
            else
            {
                CubeADCS_SetControlMode(eCUBE_ADCS_TC_13_CONTROLMODE_FAST_SPIN_DETUMB, CUBEADCS_TC_13_NO_TIMEOUT);
            }

            fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_RangeErr));

            ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
        }
    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - Rate Sensor Failure
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_RATE_SENSOR_FAILURE_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_RateFail(uint8_t u8ErrNum)
{
	CubeADCS_TLM132_t uTlmData;

	if ( true != cubeadcs_get_op_status_adcs_state(&uTlmData) )
	{
		return eCUBEADCS_STDRPLY_ERR;
	}

	if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
	{
		/* Stop all wheels */
		CubeADCS_StopRWheels();

		/* Enable the signal MCU */
		if ( !uTlmData.TLM.App.Byte1.Data.CubeControl_Signal_en )
		{
			cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC11_NODES_CUBECONTROL_SIGNAL, eCUBE_ADCS_TC11_STATE_ON);
		}

		osDelay(50);

		(void)CubeADCS_SendCmdWithChecks(CubeADCS_GetHCheckCmdDetails(eCUBEADCS_IDLE_STATE_CMD_ID_132), CUBEADCS_DIAG_UPDATE_OK, CUBEADCS_VALIDATE_DATA_TRUE);

		if ( uTlmData.TLM.App.Byte1.Data.CubeControl_Signal_en )
		{
			CubeADCS_SetControlMode(eCUBE_ADCS_TC_13_CONTROLMODE_VERY_FAST_SPIN_DETUMB, CUBEADCS_TC_13_NO_TIMEOUT);
		}
		else
		{
			CubeADCS_SetControlMode(eCUBE_ADCS_TC_13_CONTROLMODE_FAST_SPIN_DETUMB, CUBEADCS_TC_13_NO_TIMEOUT);
		}

		fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_RateSensFailure));

		++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
	}

	return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - Orbital Parameters Invalid
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_ORBIT_PARAM_INVALID_ERR
 *
 *        This one is marked as reserved for future use. It is not expected
 *        to be ever activated.
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Orbit(uint8_t u8ErrNum)
{
    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_OrbitParamsErr));

        ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - Magnetorquer or CSS configuration is Invalid
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_CONFIG_INVALID_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_Config(uint8_t u8ErrNum)
{
    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_ConfigInvalid));

        ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
    }

    return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - Control Mode Change not Allowed
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_CNTRL_MODE_CHG_INV_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_CntrlMode(uint8_t u8ErrNum)
{
    if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
    {
        fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_CntrlModeChgErr));

        ++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
    }

    return eCUBEADCS_STDRPLY_OK;

}

/** @brief Automatic Error Handling - Estimation Mode Change not Allowed
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_EST_CHG_INV_ERR
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_EstMode(uint8_t u8ErrNum)
{
	if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
	{
		fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_EstModeChgErr));

		++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
	}

	return eCUBEADCS_STDRPLY_OK;
}

/** @brief Automatic Error Handling - ADCS System State Change Error
 *
 *  @param[in] u8ErrNum the error id (number)
 *
 *  @return result of performed operation
 *
 *  @note Handles the following errors:
 *        eCUBEADCS_COMMON_DIAG_CNTS_NUMBER
 */
static eCubeADCS_StdRply fs_CubeADCS_ErrHandl_SysStateCghErr(uint8_t u8ErrNum)
{
	if ( CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt < CubeADCS_Err_Handl[u8ErrNum].u8MaxActivationAllowed )
	{
		fs_cubeadcs_errhandl_update_runtime_err(CUBEADCS_ERRHANDL_ERR_MASK(eERR_BIT_SysStateChgErr));

		++CubeADCS_Err_Handl[u8ErrNum].u8ErrHandlActivationCnt;
	}

	return eCUBEADCS_STDRPLY_OK;
}

/** @brief Update nvm runtime latched errors and operational status
 *
 *  @param[in] u16RawErrData error data
 */
static void fs_cubeadcs_errhandl_update_runtime_err(uint16_t u16RawErrData)
{
	uint16_t u16TmpLatchedErr;
	CubeADCS_Status_t sTmpAdcsStatus;

	/* Update operational status */
	(void)cubeadcs_lock_data_access(100U);

	(void)cubeadcs_get_latched_err(&u16TmpLatchedErr);

	u16TmpLatchedErr |= u16RawErrData;

	(void)cubeadcs_set_latched_err(&u16TmpLatchedErr);

	(void)cubeadcs_unlock_data_access();

	/* Update the NVM operational status */
	cubeadcs_persist_get_nvm_stored_status(&sTmpAdcsStatus);

	sTmpAdcsStatus.RunTimeLatchedErrors.u16RawData |= u16RawErrData;

	cubeadcs_persist_set_nvm_stored_status(&sTmpAdcsStatus);
}

/* ******************************************************************************************* */
