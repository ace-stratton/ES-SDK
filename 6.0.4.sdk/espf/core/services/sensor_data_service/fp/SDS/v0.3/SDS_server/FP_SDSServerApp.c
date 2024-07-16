/*!
********************************************************************************************
* @file FP_SDSServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface SDS v0.3
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#include "FP_SDSProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include "nvm/inc/nvm.h"
#include "sensor_data_cfg.h"
#include "sensor_data_service.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// @END_USER@ USER_LOCAL_FUNC_DECL
static void SDS_setSensReadFreqRequestHandlerImpl(ReqContext_t* pReqCtx,
            const SDSsetSensReadFreqRequestData_t* pRequestData);

static void SDS_getSensReadFreqRequestHandlerImpl(ReqContext_t* pReqCtx);

static void SDS_getSensStateRequestHandlerImpl(ReqContext_t* pReqCtx,
            const SDSgetSensStateRequestData_t* pRequestData);

static void SDS_getSensErrRequestHandlerImpl(ReqContext_t* pReqCtx,
            const SDSgetSensErrRequestData_t* pRequestData);

static void SDS_getSensRegRequestHandlerImpl(ReqContext_t* pReqCtx,
            const SDSgetSensRegRequestData_t* pRequestData);

static void SDS_setSensRegRequestHandlerImpl(ReqContext_t* pReqCtx,
            const SDSsetSensRegRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static SDS_ServerApi_t SDSServerApiCtx =
{
  .SDS_setSensReadFreqRequestHandler = (pfSDS_setSensReadFreqRequestHandler_t) SDS_setSensReadFreqRequestHandlerImpl,
  .SDS_getSensReadFreqRequestHandler = (pfSDS_getSensReadFreqRequestHandler_t) SDS_getSensReadFreqRequestHandlerImpl,
  .SDS_getSensStateRequestHandler = (pfSDS_getSensStateRequestHandler_t) SDS_getSensStateRequestHandlerImpl,
  .SDS_getSensErrRequestHandler = (pfSDS_getSensErrRequestHandler_t) SDS_getSensErrRequestHandlerImpl,
  .SDS_getSensRegRequestHandler = (pfSDS_getSensRegRequestHandler_t) SDS_getSensRegRequestHandlerImpl,
  .SDS_setSensRegRequestHandler = (pfSDS_setSensRegRequestHandler_t) SDS_setSensRegRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method SDS::setSensReadFreq (ID = 0x00000001)
static void SDS_setSensReadFreqRequestHandlerImpl(ReqContext_t *pReqCtx,
            const SDSsetSensReadFreqRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    SDS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@SDS::setSensReadFreq@
    sds_sens_read_freq_t sens_freq_cfgs;
    // @USER_VAR_SECTION_END@SDS::setSensReadFreq@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@SDS::setSensReadFreq@
        
        Nvm_GetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sens_freq_cfgs);

        sens_freq_cfgs.enable = pRequestData->eEnable;

        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_MTM].freq_cfg = (pRequestData->u16SensMTM > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensMTM;
        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_GYRO].freq_cfg = (pRequestData->u16SensGyro > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensGyro;
        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_CSS].freq_cfg = (pRequestData->u16SensCSS > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensCSS;
        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_ACC].freq_cfg = (pRequestData->u16SensACC > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensACC;
        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP].freq_cfg = (pRequestData->u16SensPANEL_TEMP > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensPANEL_TEMP;
        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP].freq_cfg = (pRequestData->u16SensGYRO_TEMP > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensGYRO_TEMP;
        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_RES_0].freq_cfg = (pRequestData->u16SensRES_0 > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensRES_0;
        sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_RES_1].freq_cfg = (pRequestData->u16SensRES_1 > SDS_MAX_SENSOR_FREQ_HZ) ? SDS_MAX_SENSOR_FREQ_HZ : pRequestData->u16SensRES_1;

        Nvm_SetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, (void *const)&sens_freq_cfgs, NVMSETBLOCK_STORE_IMMEDIATELY);

        eOpResult = SDS_STANDARDRESULT_SUCCESS;

        
        // @USER_CODE_SECTION_END@SDS::setSensReadFreq@

        respResult = SDS_setSensReadFreqResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_SDS, SDS_SETSENSREADFREQ_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method SDS::setSensReadFreq (ID = 0x00000001)

// @START@ Request handler for method SDS::getSensReadFreq (ID = 0x00000002)
static void SDS_getSensReadFreqRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    SDS_SafeBool_t eEnable;
    uint16_t u16SensMTM;
    uint16_t u16SensGyro;
    uint16_t u16SensCSS;
    uint16_t u16SensACC;
    uint16_t u16SensPANEL_TEMP;
    uint16_t u16SensGYRO_TEMP;
    uint16_t u16SensRES_0;
    uint16_t u16SensRES_1;
    SDS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@SDS::getSensReadFreq@
    sds_sens_read_freq_t sens_freq_cfgs;
    // @USER_VAR_SECTION_END@SDS::getSensReadFreq@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@SDS::getSensReadFreq@
        
        Nvm_GetBlockById(NVM_BLOCK_SDS_SENS_READ_FREQ_CFG, &sens_freq_cfgs);

        eEnable = sens_freq_cfgs.enable;
        u16SensMTM = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_MTM].freq_cfg;
        u16SensGyro = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_GYRO].freq_cfg;
        u16SensCSS = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_CSS].freq_cfg;
        u16SensACC = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_ACC].freq_cfg;
        u16SensPANEL_TEMP = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_PANEL_TEMP].freq_cfg;
        u16SensGYRO_TEMP = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_GYRO_TEMP].freq_cfg;
        u16SensRES_0 = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_RES_0].freq_cfg;
        u16SensRES_1 = sens_freq_cfgs.sens_cfg[SDS_SENSTYPECFGNUM_SENS_RES_1].freq_cfg;

        eOpResult = SDS_STANDARDRESULT_SUCCESS;

        
        // @USER_CODE_SECTION_END@SDS::getSensReadFreq@

        respResult = SDS_getSensReadFreqResp(
                        &respCtx,
                        eEnable,
                        u16SensMTM,
                        u16SensGyro,
                        u16SensCSS,
                        u16SensACC,
                        u16SensPANEL_TEMP,
                        u16SensGYRO_TEMP,
                        u16SensRES_0,
                        u16SensRES_1,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_SDS, SDS_GETSENSREADFREQ_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method SDS::getSensReadFreq (ID = 0x00000002)

// @START@ Request handler for method SDS::getSensState (ID = 0x00000003)
static void SDS_getSensStateRequestHandlerImpl(ReqContext_t *pReqCtx,
            const SDSgetSensStateRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    SDS_SensorState_t eSensState;
    SDS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@SDS::getSensState@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SDS::getSensState@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@SDS::getSensState@
        if ( pRequestData->eSensTypeId < SENSOR_COUNT)
        {
        	eSensState = sensor_base_cfg[pRequestData->eSensTypeId].sens_if->get_state();
        }
        else
        {
        	eSensState = SDS_SENSOR_STATUS_DEINIT;
        }

        eOpResult = SDS_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@SDS::getSensState@

        respResult = SDS_getSensStateResp(
                        &respCtx,
                        eSensState,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_SDS, SDS_GETSENSSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method SDS::getSensState (ID = 0x00000003)

// @START@ Request handler for method SDS::getSensErr (ID = 0x00000004)
static void SDS_getSensErrRequestHandlerImpl(ReqContext_t *pReqCtx,
            const SDSgetSensErrRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8SensErr;
    uint8_t u8X_AXIS;
    uint8_t u8Y_AXIS;
    uint8_t u8Z_AXIS;
    SDS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@SDS::getSensErr@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SDS::getSensErr@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@SDS::getSensErr@
        
        u8X_AXIS = 0;
        u8Y_AXIS = 0;
        u8Z_AXIS = 0;

        if ( pRequestData->eSensTypeId < SENSOR_COUNT)
        {
        	u8SensErr = sensor_base_cfg[pRequestData->eSensTypeId].sens_if->get_last_error();

        	if (SENSOR_GYRO == pRequestData->eSensTypeId)
        	{
        		gyroscope_status_bundle_t gyroStatus = ADIS16265_GetStatus();

        		u8X_AXIS = gyroStatus.gyroscope_X_status;
        		u8Y_AXIS = gyroStatus.gyroscope_Y_status;
        		u8Z_AXIS = gyroStatus.gyroscope_Z_status;
        	}
        }
        else
        {
        	u8SensErr = 0xFF;
        }

        eOpResult = SDS_STANDARDRESULT_SUCCESS;
        
        // @USER_CODE_SECTION_END@SDS::getSensErr@

        respResult = SDS_getSensErrResp(
                        &respCtx,
                        u8SensErr,
                        u8X_AXIS,
                        u8Y_AXIS,
                        u8Z_AXIS,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_SDS, SDS_GETSENSERR_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method SDS::getSensErr (ID = 0x00000004)

// @START@ Request handler for method SDS::getSensReg (ID = 0x00000005)
static void SDS_getSensRegRequestHandlerImpl(ReqContext_t *pReqCtx,
            const SDSgetSensRegRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32RespBytes;
    SDS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@SDS::getSensReg@
    sds_sensor_status_t sens_status;
    // @USER_VAR_SECTION_END@SDS::getSensReg@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@SDS::getSensReg@
        
        eOpResult = SDS_STANDARDRESULT_ERROR;
        u32RespBytes = 0U;

        for (uint8_t s_id = 0; s_id < SENSOR_COUNT; s_id++)
        {
        	if ( (pRequestData->eSensTypeId == sensor_base_cfg[ s_id ].freq_cfg_id) &&
        			(true == sds_sens_lock(s_id)) )
        	{
        		sens_status = sensor_base_cfg[ s_id ].sens_if->get_state();

        		if ( SDS_SENSOR_STATUS_INIT != sens_status )
        		{
        			sensor_base_cfg[ s_id ].sens_if->init();
        		}

        		if ( SDS_OP_STATUS_OK == sensor_base_cfg[ s_id ].sens_if->get_reg(pRequestData->eSensNum, pRequestData->eSensAxis, pRequestData->u32Reg_address, &u32RespBytes) )
        		{
        			eOpResult = SDS_STANDARDRESULT_SUCCESS;
        		}

        		if ( SDS_SENSOR_STATUS_INIT != sens_status )
        		{
        			sensor_base_cfg[ s_id ].sens_if->deinit();
        		}

        		(void)sds_sens_release(s_id);

        		break;
        	}
        }

        // @USER_CODE_SECTION_END@SDS::getSensReg@

        respResult = SDS_getSensRegResp(
                        &respCtx,
                        u32RespBytes,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_SDS, SDS_GETSENSREG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method SDS::getSensReg (ID = 0x00000005)

// @START@ Request handler for method SDS::setSensReg (ID = 0x00000006)
static void SDS_setSensRegRequestHandlerImpl(ReqContext_t *pReqCtx,
            const SDSsetSensRegRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    SDS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@SDS::setSensReg@
    sds_sensor_status_t sens_status;
    // @USER_VAR_SECTION_END@SDS::setSensReg@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@SDS::setSensReg@
        
        eOpResult = SDS_STANDARDRESULT_ERROR;

        for (uint8_t s_id = 0; s_id < SENSOR_COUNT; s_id++)
        {
        	if ( (pRequestData->eSensTypeId == sensor_base_cfg[ s_id ].freq_cfg_id ) &&
        			(true == sds_sens_lock(s_id)) )
        	{
        		sens_status = sensor_base_cfg[ s_id ].sens_if->get_state();

        		if ( SDS_SENSOR_STATUS_INIT != sens_status )
        		{
        			sensor_base_cfg[ s_id ].sens_if->init();
        		}

        		if ( SDS_OP_STATUS_OK == sensor_base_cfg[ s_id ].sens_if->set_reg(pRequestData->eSensNum, pRequestData->eSensAxis, pRequestData->u32Reg_address, pRequestData->u32Reg_value) )
        		{
        			eOpResult = SDS_STANDARDRESULT_SUCCESS;
        		}

        		if ( SDS_SENSOR_STATUS_INIT != sens_status )
        		{
        			sensor_base_cfg[ s_id ].sens_if->deinit();
        		}

        		(void)sds_sens_release(s_id);

        		break;
        	}
        }

        // @USER_CODE_SECTION_END@SDS::setSensReg@

        respResult = SDS_setSensRegResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_SDS, SDS_SETSENSREG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method SDS::setSensReg (ID = 0x00000006)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void SDSServerAppInit(void)
{
    SDS_registerServerApi(&SDSServerApiCtx);
}
