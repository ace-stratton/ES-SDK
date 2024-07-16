/*!
********************************************************************************************
* @file FP_OBC_CUBEADCSServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface OBC_CUBEADCS v1.1
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

#include "FP_OBC_CUBEADCSProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include "nvm/inc/nvm.h"
#include "datetime.h"
#include "cubeadcs_usercmds.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
static inline bool is_bit_set(uint32_t val, uint32_t bit_val){return !!(val & bit_val);}
// @END_USER@ USER_LOCAL_FUNC_DECL
static void OBC_CUBEADCS_getCommissioningStatusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_setCommissioningStatusRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSsetCommissioningStatusRequestData_t* pRequestData);

static void OBC_CUBEADCS_getGenericTLMRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSgetGenericTLMRequestData_t* pRequestData);

static void OBC_CUBEADCS_sendGenericTCRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSsendGenericTCRequestData_t* pRequestData);

static void OBC_CUBEADCS_getOpStatusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_resetRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSresetRequestData_t* pRequestData);

static void OBC_CUBEADCS_clrErrFlagsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_startFileTransferRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSstartFileTransferRequestData_t* pRequestData);

static void OBC_CUBEADCS_pollFileTransferStatusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_clearFaultyNodeStatusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_startFileListDownloadRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_pollFileListDownloadStatusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_getADCSSysStateRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_setADCSSysStateRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSsetADCSSysStateRequestData_t* pRequestData);

static void OBC_CUBEADCS_getADCSUnixTimeRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_updateADCSUnixTimeRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_setEnableErrHandlLogicRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSsetEnableErrHandlLogicRequestData_t* pRequestData);

static void OBC_CUBEADCS_getEnableErrHandlLogicRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_setStablePointingThresholdsRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSsetStablePointingThresholdsRequestData_t* pRequestData);

static void OBC_CUBEADCS_getStablePointingThresholdsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_setSimulationModeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSsetSimulationModeRequestData_t* pRequestData);

static void OBC_CUBEADCS_getSimulationModeValueRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_getOBCCommAndErrCountersRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSclrOBCCommAndErrCountersRequestData_t* pRequestData);

static void OBC_CUBEADCS_getFDIRCounersRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_clrFDIRCountersRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSclrFDIRCountersRequestData_t* pRequestData);

static void OBC_CUBEADCS_stopFileTransferRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_getRunTimeLatchedErrsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_getFaultyNodeStatusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_CUBEADCS_setSystemStateCfgRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_CUBEADCSsetSystemStateCfgRequestData_t* pRequestData);

static void OBC_CUBEADCS_getSystemStateCfgRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static OBC_CUBEADCS_ServerApi_t OBC_CUBEADCSServerApiCtx =
{
  .OBC_CUBEADCS_getCommissioningStatusRequestHandler = (pfOBC_CUBEADCS_getCommissioningStatusRequestHandler_t) OBC_CUBEADCS_getCommissioningStatusRequestHandlerImpl,
  .OBC_CUBEADCS_setCommissioningStatusRequestHandler = (pfOBC_CUBEADCS_setCommissioningStatusRequestHandler_t) OBC_CUBEADCS_setCommissioningStatusRequestHandlerImpl,
  .OBC_CUBEADCS_getGenericTLMRequestHandler = (pfOBC_CUBEADCS_getGenericTLMRequestHandler_t) OBC_CUBEADCS_getGenericTLMRequestHandlerImpl,
  .OBC_CUBEADCS_sendGenericTCRequestHandler = (pfOBC_CUBEADCS_sendGenericTCRequestHandler_t) OBC_CUBEADCS_sendGenericTCRequestHandlerImpl,
  .OBC_CUBEADCS_getOpStatusRequestHandler = (pfOBC_CUBEADCS_getOpStatusRequestHandler_t) OBC_CUBEADCS_getOpStatusRequestHandlerImpl,
  .OBC_CUBEADCS_resetRequestHandler = (pfOBC_CUBEADCS_resetRequestHandler_t) OBC_CUBEADCS_resetRequestHandlerImpl,
  .OBC_CUBEADCS_clrErrFlagsRequestHandler = (pfOBC_CUBEADCS_clrErrFlagsRequestHandler_t) OBC_CUBEADCS_clrErrFlagsRequestHandlerImpl,
  .OBC_CUBEADCS_startFileTransferRequestHandler = (pfOBC_CUBEADCS_startFileTransferRequestHandler_t) OBC_CUBEADCS_startFileTransferRequestHandlerImpl,
  .OBC_CUBEADCS_pollFileTransferStatusRequestHandler = (pfOBC_CUBEADCS_pollFileTransferStatusRequestHandler_t) OBC_CUBEADCS_pollFileTransferStatusRequestHandlerImpl,
  .OBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandler = (pfOBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandler_t) OBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandlerImpl,
  .OBC_CUBEADCS_clearFaultyNodeStatusRequestHandler = (pfOBC_CUBEADCS_clearFaultyNodeStatusRequestHandler_t) OBC_CUBEADCS_clearFaultyNodeStatusRequestHandlerImpl,
  .OBC_CUBEADCS_startFileListDownloadRequestHandler = (pfOBC_CUBEADCS_startFileListDownloadRequestHandler_t) OBC_CUBEADCS_startFileListDownloadRequestHandlerImpl,
  .OBC_CUBEADCS_pollFileListDownloadStatusRequestHandler = (pfOBC_CUBEADCS_pollFileListDownloadStatusRequestHandler_t) OBC_CUBEADCS_pollFileListDownloadStatusRequestHandlerImpl,
  .OBC_CUBEADCS_getADCSSysStateRequestHandler = (pfOBC_CUBEADCS_getADCSSysStateRequestHandler_t) OBC_CUBEADCS_getADCSSysStateRequestHandlerImpl,
  .OBC_CUBEADCS_setADCSSysStateRequestHandler = (pfOBC_CUBEADCS_setADCSSysStateRequestHandler_t) OBC_CUBEADCS_setADCSSysStateRequestHandlerImpl,
  .OBC_CUBEADCS_getADCSUnixTimeRequestHandler = (pfOBC_CUBEADCS_getADCSUnixTimeRequestHandler_t) OBC_CUBEADCS_getADCSUnixTimeRequestHandlerImpl,
  .OBC_CUBEADCS_updateADCSUnixTimeRequestHandler = (pfOBC_CUBEADCS_updateADCSUnixTimeRequestHandler_t) OBC_CUBEADCS_updateADCSUnixTimeRequestHandlerImpl,
  .OBC_CUBEADCS_setEnableErrHandlLogicRequestHandler = (pfOBC_CUBEADCS_setEnableErrHandlLogicRequestHandler_t) OBC_CUBEADCS_setEnableErrHandlLogicRequestHandlerImpl,
  .OBC_CUBEADCS_getEnableErrHandlLogicRequestHandler = (pfOBC_CUBEADCS_getEnableErrHandlLogicRequestHandler_t) OBC_CUBEADCS_getEnableErrHandlLogicRequestHandlerImpl,
  .OBC_CUBEADCS_setStablePointingThresholdsRequestHandler = (pfOBC_CUBEADCS_setStablePointingThresholdsRequestHandler_t) OBC_CUBEADCS_setStablePointingThresholdsRequestHandlerImpl,
  .OBC_CUBEADCS_getStablePointingThresholdsRequestHandler = (pfOBC_CUBEADCS_getStablePointingThresholdsRequestHandler_t) OBC_CUBEADCS_getStablePointingThresholdsRequestHandlerImpl,
  .OBC_CUBEADCS_setSimulationModeRequestHandler = (pfOBC_CUBEADCS_setSimulationModeRequestHandler_t) OBC_CUBEADCS_setSimulationModeRequestHandlerImpl,
  .OBC_CUBEADCS_getSimulationModeValueRequestHandler = (pfOBC_CUBEADCS_getSimulationModeValueRequestHandler_t) OBC_CUBEADCS_getSimulationModeValueRequestHandlerImpl,
  .OBC_CUBEADCS_getOBCCommAndErrCountersRequestHandler = (pfOBC_CUBEADCS_getOBCCommAndErrCountersRequestHandler_t) OBC_CUBEADCS_getOBCCommAndErrCountersRequestHandlerImpl,
  .OBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandler = (pfOBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandler_t) OBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandlerImpl,
  .OBC_CUBEADCS_getFDIRCounersRequestHandler = (pfOBC_CUBEADCS_getFDIRCounersRequestHandler_t) OBC_CUBEADCS_getFDIRCounersRequestHandlerImpl,
  .OBC_CUBEADCS_clrFDIRCountersRequestHandler = (pfOBC_CUBEADCS_clrFDIRCountersRequestHandler_t) OBC_CUBEADCS_clrFDIRCountersRequestHandlerImpl,
  .OBC_CUBEADCS_stopFileTransferRequestHandler = (pfOBC_CUBEADCS_stopFileTransferRequestHandler_t) OBC_CUBEADCS_stopFileTransferRequestHandlerImpl,
  .OBC_CUBEADCS_getRunTimeLatchedErrsRequestHandler = (pfOBC_CUBEADCS_getRunTimeLatchedErrsRequestHandler_t) OBC_CUBEADCS_getRunTimeLatchedErrsRequestHandlerImpl,
  .OBC_CUBEADCS_getFaultyNodeStatusRequestHandler = (pfOBC_CUBEADCS_getFaultyNodeStatusRequestHandler_t) OBC_CUBEADCS_getFaultyNodeStatusRequestHandlerImpl,
  .OBC_CUBEADCS_setSystemStateCfgRequestHandler = (pfOBC_CUBEADCS_setSystemStateCfgRequestHandler_t) OBC_CUBEADCS_setSystemStateCfgRequestHandlerImpl,
  .OBC_CUBEADCS_getSystemStateCfgRequestHandler = (pfOBC_CUBEADCS_getSystemStateCfgRequestHandler_t) OBC_CUBEADCS_getSystemStateCfgRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method OBC_CUBEADCS::getCommissioningStatus (ID = 0x00000003)
static void OBC_CUBEADCS_getCommissioningStatusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_CommissioningStatus_t eStatus;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getCommissioningStatus@
    eCubeADCS_Commissioning_t resStatus;

    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getCommissioningStatus@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getCommissioningStatus@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            resStatus = cubeadcs_get_cms_status();

            switch (resStatus)
            {
                case eCUBEADCS_STEP_00_NONE:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_00_NONE;
                break;

                case eCUBEADCS_STEP_01_INITIAL_ANG_RATE_EST:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_01_INITIAL_ANG_RATE_EST;
                break;

                case eCUBEADCS_STEP_02_DETUMBLING:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_02_DETUMBLING;
                break;

                case eCUBEADCS_STEP_03_MAG_DEPLOYMENT:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_03_MAG_DEPLOYMENT;
                break;

                case eCUBEADCS_STEP_04_MAG_CALIBRATION:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_04_MAG_CALIBRATION;
                break;

                case eCUBEADCS_STEP_05_ANG_RATE_AND_PITCH_RATE_EST:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_05_ANG_RATE_AND_PITCH_RATE_EST;
                break;

                case eCUBEADCS_STEP_06_Y_WHEEL_RAMP_UP_TEST:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_06_Y_WHEEL_RAMP_UP_TEST;
                break;

                case eCUBEADCS_STEP_07_Y_MOMENTUM_MODE_COMMISSIONING:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_07_Y_MOMENTUM_MODE_COMMISSIONING;
                break;

                case eCUBEADCS_STEP_08_SUN_NADIR_COMMISSIONING:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_08_SUN_NADIR_COMMISSIONING;
                break;

                case eCUBEADCS_STEP_09_CUBESTAR_COMMISSIONING:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_09_CUBESTAR_COMMISSIONING;
                break;

                case eCUBEADCS_STEP_10_WHEELS_COMMISSIONING:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_10_WHEELS_COMMISSIONING;
                break;

                case eCUBEADCS_STEP_11_SUN_TRACKING:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_11_SUN_TRACKING;
                break;

                case eCUBEADCS_STEP_12_GROUND_TRACKING:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_STEP_12_GROUND_TRACKING;
                break;

                default:
                    eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_MAX_CNT;
                break;
            }

            eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eStatus = OBC_CUBEADCS_COMMISSIONINGSTATUS_MAX_CNT;
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getCommissioningStatus@

        respResult = OBC_CUBEADCS_getCommissioningStatusResp(
                        &respCtx,
                        eStatus,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETCOMMISSIONINGSTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getCommissioningStatus (ID = 0x00000003)

// @START@ Request handler for method OBC_CUBEADCS::setCommissioningStatus (ID = 0x00000004)
static void OBC_CUBEADCS_setCommissioningStatusRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSsetCommissioningStatusRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::setCommissioningStatus@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::setCommissioningStatus@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::setCommissioningStatus@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            if (eCUBEADCS_STDRPLY_OK == cubeadcs_set_cms_status(pRequestData->eStatus) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::setCommissioningStatus@

        respResult = OBC_CUBEADCS_setCommissioningStatusResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_SETCOMMISSIONINGSTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::setCommissioningStatus (ID = 0x00000004)

// @START@ Request handler for method OBC_CUBEADCS::getGenericTLM (ID = 0x00000005)
static void OBC_CUBEADCS_getGenericTLMRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSgetGenericTLMRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_TLMReqReply_t sTLMReq_Reply;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getGenericTLM@
    uint16_t u16RespSize;
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getGenericTLM@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getGenericTLM@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            u16RespSize             = 0x0000;
            sNewCmd.u8CmdID         = pRequestData->u8TLMID;
            sNewCmd.pu8CmdData      = NULL;
            sNewCmd.u16CmdDataSize  = 0x00;
            sNewCmd.pvCmdResDst     = (void *)&sTLMReq_Reply.sTLM_Rply_Data;
            sNewCmd.u16CmdResDstSize= ((uint16_t)173);
            sNewCmd.u16CmdResSize   = &u16RespSize;

            eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;

            if ( sNewCmd.u8CmdID >= 0x80) {
                if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GENERIC, &sNewCmd, NULL) )
                    eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }

            sTLMReq_Reply.u16TLM_Rply_Len = u16RespSize;
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getGenericTLM@

        respResult = OBC_CUBEADCS_getGenericTLMResp(
                        &respCtx,
                        &sTLMReq_Reply,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETGENERICTLM_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getGenericTLM (ID = 0x00000005)

// @START@ Request handler for method OBC_CUBEADCS::sendGenericTC (ID = 0x00000006)
static void OBC_CUBEADCS_sendGenericTCRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSsendGenericTCRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_TCReqReply_t sTCReq_Reply;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::sendGenericTC@
    uint16_t u16RespSize;
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::sendGenericTC@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::sendGenericTC@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            u16RespSize             = 0x0000;

            sNewCmd.u8CmdID         = pRequestData->sTCReq_Data.u8TC_ID;
            sNewCmd.pu8CmdData      = (uint8_t *)&pRequestData->sTCReq_Data.au8TC_Data[0];
            sNewCmd.u16CmdDataSize  = pRequestData->sTCReq_Data.u16TC_Data_Len;
            sNewCmd.pvCmdResDst     = (void *)&sTCReq_Reply.sTCData;
            sNewCmd.u16CmdResDstSize= ((uint16_t)173);
            sNewCmd.u16CmdResSize   = &u16RespSize;

            eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;

            if ( sNewCmd.u8CmdID < 0x80 ) {
                if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GENERIC, &sNewCmd, NULL) )
                    eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }

            sTCReq_Reply.u16TC_Rply_Len = u16RespSize;
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::sendGenericTC@

        respResult = OBC_CUBEADCS_sendGenericTCResp(
                        &respCtx,
                        &sTCReq_Reply,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_SENDGENERICTC_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::sendGenericTC (ID = 0x00000006)

// @START@ Request handler for method OBC_CUBEADCS::getOpStatus (ID = 0x00000007)
static void OBC_CUBEADCS_getOpStatusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_OpStatus_t sOpStatus;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getOpStatus@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getOpStatus@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getOpStatus@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pvCmdResDst = (void *)&sOpStatus;
            sNewCmd.u16CmdResDstSize = sizeof(sOpStatus);

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GET_OP_STATUS, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getOpStatus@

        respResult = OBC_CUBEADCS_getOpStatusResp(
                        &respCtx,
                        &sOpStatus,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETOPSTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getOpStatus (ID = 0x00000007)

// @START@ Request handler for method OBC_CUBEADCS::reset (ID = 0x00000008)
static void OBC_CUBEADCS_resetRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSresetRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::reset@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::reset@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::reset@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pu8CmdData = (uint8_t *)&pRequestData->eMode;
            sNewCmd.u16CmdDataSize = sizeof(uint8_t);

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_RESET, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::reset@

        respResult = OBC_CUBEADCS_resetResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_RESET_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::reset (ID = 0x00000008)

// @START@ Request handler for method OBC_CUBEADCS::clrErrFlags (ID = 0x00000009)
static void OBC_CUBEADCS_clrErrFlagsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::clrErrFlags@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::clrErrFlags@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::clrErrFlags@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_CLR_LATCHED_ERR_FLAGS, NULL, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::clrErrFlags@

        respResult = OBC_CUBEADCS_clrErrFlagsResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_CLRERRFLAGS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::clrErrFlags (ID = 0x00000009)

// @START@ Request handler for method OBC_CUBEADCS::startFileTransfer (ID = 0x0000000A)
static void OBC_CUBEADCS_startFileTransferRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSstartFileTransferRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::startFileTransfer@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::startFileTransfer@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::startFileTransfer@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pu8CmdData = (uint8_t *)&pRequestData->sFileInfo;
            sNewCmd.u16CmdDataSize = sizeof(CubeADCS_FDwnInfo_t);

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_START_FILE_TRANSFER, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::startFileTransfer@

        respResult = OBC_CUBEADCS_startFileTransferResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_STARTFILETRANSFER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::startFileTransfer (ID = 0x0000000A)

// @START@ Request handler for method OBC_CUBEADCS::pollFileTransferStatus (ID = 0x0000000B)
static void OBC_CUBEADCS_pollFileTransferStatusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_FTransfStatus_t eStatus;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::pollFileTransferStatus@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::pollFileTransferStatus@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::pollFileTransferStatus@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pvCmdResDst = (uint8_t *)&eStatus;

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_POLL_FILE_TRANSFER, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eStatus  = OBC_CUBEADCS_FTRANSFSTATUS_MAX_CNT;
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::pollFileTransferStatus@

        respResult = OBC_CUBEADCS_pollFileTransferStatusResp(
                        &respCtx,
                        eStatus,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_POLLFILETRANSFERSTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::pollFileTransferStatus (ID = 0x0000000B)

// @START@ Request handler for method OBC_CUBEADCS::clearRunTimeLatchedErrs (ID = 0x00000011)
static void OBC_CUBEADCS_clearRunTimeLatchedErrsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::clearRunTimeLatchedErrs@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::clearRunTimeLatchedErrs@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::clearRunTimeLatchedErrs@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_CLR_RUNTIME_LATCHED_ERR, NULL, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::clearRunTimeLatchedErrs@

        respResult = OBC_CUBEADCS_clearRunTimeLatchedErrsResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_CLEARRUNTIMELATCHEDERRS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::clearRunTimeLatchedErrs (ID = 0x00000011)

// @START@ Request handler for method OBC_CUBEADCS::clearFaultyNodeStatus (ID = 0x00000013)
static void OBC_CUBEADCS_clearFaultyNodeStatusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::clearFaultyNodeStatus@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::clearFaultyNodeStatus@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::clearFaultyNodeStatus@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_CLR_FAULTY_NODE, NULL, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::clearFaultyNodeStatus@

        respResult = OBC_CUBEADCS_clearFaultyNodeStatusResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_CLEARFAULTYNODESTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::clearFaultyNodeStatus (ID = 0x00000013)

// @START@ Request handler for method OBC_CUBEADCS::startFileListDownload (ID = 0x00000014)
static void OBC_CUBEADCS_startFileListDownloadRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::startFileListDownload@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::startFileListDownload@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::startFileListDownload@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_START_FILE_LIST_TRANSFER, NULL, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::startFileListDownload@

        respResult = OBC_CUBEADCS_startFileListDownloadResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_STARTFILELISTDOWNLOAD_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::startFileListDownload (ID = 0x00000014)

// @START@ Request handler for method OBC_CUBEADCS::pollFileListDownloadStatus (ID = 0x00000015)
static void OBC_CUBEADCS_pollFileListDownloadStatusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_FTransfStatus_t eStatus;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::pollFileListDownloadStatus@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::pollFileListDownloadStatus@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::pollFileListDownloadStatus@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pvCmdResDst = (uint8_t *)&eStatus;

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_POLL_FILE_LIST_TRANSFER, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eStatus  = OBC_CUBEADCS_FTRANSFSTATUS_MAX_CNT;
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::pollFileListDownloadStatus@

        respResult = OBC_CUBEADCS_pollFileListDownloadStatusResp(
                        &respCtx,
                        eStatus,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_POLLFILELISTDOWNLOADSTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::pollFileListDownloadStatus (ID = 0x00000015)

// @START@ Request handler for method OBC_CUBEADCS::getADCSSysState (ID = 0x00000016)
static void OBC_CUBEADCS_getADCSSysStateRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_ADCSSysStates_t eSysState;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getADCSSysState@
    CubeADCS_CmdCfg_t sNewCmd;
    CubeADCS_SysSCfg_t sNewState;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getADCSSysState@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getADCSSysState@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pvCmdResDst = (uint8_t *)&sNewState;

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GET_SYSSTATE, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }

            eSysState = (OBC_CUBEADCS_ADCSSysStates_t)sNewState.eReqCfg;
        }
        else
        {
            eSysState  = OBC_CUBEADCS_ADCSSYSSTATES_MAX_CNT;
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getADCSSysState@

        respResult = OBC_CUBEADCS_getADCSSysStateResp(
                        &respCtx,
                        eSysState,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETADCSSYSSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getADCSSysState (ID = 0x00000016)

// @START@ Request handler for method OBC_CUBEADCS::setADCSSysState (ID = 0x00000017)
static void OBC_CUBEADCS_setADCSSysStateRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSsetADCSSysStateRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::setADCSSysState@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::setADCSSysState@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::setADCSSysState@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pu8CmdData = (uint8_t *)&pRequestData->eSysState;
            sNewCmd.u16CmdDataSize = sizeof(uint8_t);

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_SET_SYSSTATE, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::setADCSSysState@

        respResult = OBC_CUBEADCS_setADCSSysStateResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_SETADCSSYSSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::setADCSSysState (ID = 0x00000017)

// @START@ Request handler for method OBC_CUBEADCS::getADCSUnixTime (ID = 0x00000018)
static void OBC_CUBEADCS_getADCSUnixTimeRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_UnixTime_t sUnixTime;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getADCSUnixTime@
    CubeADCS_CmdCfg_t sNewCmd;
    CubeADCS_UnixTime_t sNewUnixTime;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getADCSUnixTime@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getADCSUnixTime@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pvCmdResDst = (uint8_t *)&sNewUnixTime;

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GET_UNIXTIME, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }

            sUnixTime.u32CurrentUnixTime = sNewUnixTime.u32CurrentUnixTime;
            sUnixTime.u16Milliseconds = sNewUnixTime.u16Milliseconds;
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getADCSUnixTime@

        respResult = OBC_CUBEADCS_getADCSUnixTimeResp(
                        &respCtx,
                        &sUnixTime,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETADCSUNIXTIME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getADCSUnixTime (ID = 0x00000018)

// @START@ Request handler for method OBC_CUBEADCS::updateADCSUnixTime (ID = 0x00000019)
static void OBC_CUBEADCS_updateADCSUnixTimeRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::updateADCSUnixTime@
    CubeADCS_CmdCfg_t sNewCmd;
    unix_time_t		  tNow;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::updateADCSUnixTime@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::updateADCSUnixTime@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            tNow = datetime_to_unix_now();

            sNewCmd.pu8CmdData = (uint8_t *)&tNow;
            sNewCmd.u16CmdDataSize = sizeof(unix_time_t);

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_SET_UNIXTIME, &sNewCmd, NULL) )
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::updateADCSUnixTime@

        respResult = OBC_CUBEADCS_updateADCSUnixTimeResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_UPDATEADCSUNIXTIME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::updateADCSUnixTime (ID = 0x00000019)

// @START@ Request handler for method OBC_CUBEADCS::setEnableErrHandlLogic (ID = 0x0000001A)
static void OBC_CUBEADCS_setEnableErrHandlLogicRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSsetEnableErrHandlLogicRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::setEnableErrHandlLogic@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::setEnableErrHandlLogic@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::setEnableErrHandlLogic@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            if ( (true == IS_TRUE(pRequestData->eEnFlag)) || (true == IS_FALSE(pRequestData->eEnFlag)) ) {
                Nvm_SetBlockById(NVM_BLOCK_CUBEADCS_ERR_HANDL_CONFIG, (void *)&pRequestData->eEnFlag, NVMSETBLOCK_STORE_IMMEDIATELY);

                eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
                eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::setEnableErrHandlLogic@

        respResult = OBC_CUBEADCS_setEnableErrHandlLogicResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_SETENABLEERRHANDLLOGIC_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::setEnableErrHandlLogic (ID = 0x0000001A)

// @START@ Request handler for method OBC_CUBEADCS::getEnableErrHandlLogic (ID = 0x0000001B)
static void OBC_CUBEADCS_getEnableErrHandlLogicRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_SafeBool_t eEnFlag;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getEnableErrHandlLogic@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getEnableErrHandlLogic@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getEnableErrHandlLogic@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            cubeadcs_err_handl_cfg_t sTmpData;

            Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_ERR_HANDL_CONFIG, &sTmpData);

            eEnFlag = sTmpData.en_cubeadcs_err_handl;

            eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
            eEnFlag = 0x00;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getEnableErrHandlLogic@

        respResult = OBC_CUBEADCS_getEnableErrHandlLogicResp(
                        &respCtx,
                        eEnFlag,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETENABLEERRHANDLLOGIC_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getEnableErrHandlLogic (ID = 0x0000001B)

// @START@ Request handler for method OBC_CUBEADCS::setStablePointingThresholds (ID = 0x0000001C)
static void OBC_CUBEADCS_setStablePointingThresholdsRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSsetStablePointingThresholdsRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::setStablePointingThresholds@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::setStablePointingThresholds@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::setStablePointingThresholds@
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
        	cubeadcs_angle_limits_t sData;
        	cubeadcs_angle_limits_t sDataCheck;

        	/* Values come in degrees, so a multiplication by 1e3 is required to convert to millidegrees */
        	sData.stable_pointing_threshold_angle      = (int32_t)(pRequestData->dStablePointingThresholdAngle     * 1000);
        	sData.stable_pointing_threshold_angle_rate = (int32_t)(pRequestData->dStablePointingThresholdAngleRate * 1000);

        	Nvm_SetBlockById(NVM_BLOCK_CUBEADCS_ANGLE_LIMITS, (void *)&sData, NVMSETBLOCK_STORE_IMMEDIATELY);

        	/* Check if it actually worked */
        	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_ANGLE_LIMITS, &sDataCheck);

        	if ((sData.stable_pointing_threshold_angle      == sDataCheck.stable_pointing_threshold_angle) &&
        			(sData.stable_pointing_threshold_angle_rate == sDataCheck.stable_pointing_threshold_angle_rate))
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        	}
        	else
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
        	}
        }
        else
        {
        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::setStablePointingThresholds@

        respResult = OBC_CUBEADCS_setStablePointingThresholdsResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_SETSTABLEPOINTINGTHRESHOLDS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::setStablePointingThresholds (ID = 0x0000001C)

// @START@ Request handler for method OBC_CUBEADCS::getStablePointingThresholds (ID = 0x0000001D)
static void OBC_CUBEADCS_getStablePointingThresholdsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    double dStablePointingThresholdAngle;
    double dStablePointingThresholdAngleRate;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getStablePointingThresholds@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getStablePointingThresholds@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getStablePointingThresholds@
    	if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
    	{
    		cubeadcs_angle_limits_t sData;

    		/* Retrieve thresholds from NVM */
    		Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_ANGLE_LIMITS, &sData);

    		/* Change from millidegree integers to degrees doubles for the SDE user */
    		dStablePointingThresholdAngle     = (double)sData.stable_pointing_threshold_angle      * 0.001F;
    		dStablePointingThresholdAngleRate = (double)sData.stable_pointing_threshold_angle_rate * 0.001F;

    		eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
    	}
    	else
    	{
    		dStablePointingThresholdAngle = (double)0.0;
    		dStablePointingThresholdAngleRate = (double)0.0;

    		eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
    	}
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getStablePointingThresholds@

        respResult = OBC_CUBEADCS_getStablePointingThresholdsResp(
                        &respCtx,
                        dStablePointingThresholdAngle,
                        dStablePointingThresholdAngleRate,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETSTABLEPOINTINGTHRESHOLDS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getStablePointingThresholds (ID = 0x0000001D)

// @START@ Request handler for method OBC_CUBEADCS::setSimulationMode (ID = 0x0000001E)
static void OBC_CUBEADCS_setSimulationModeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSsetSimulationModeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::setSimulationMode@
    cubeadcs_sim_mode_t en_sim;
    cubeadcs_sim_mode_t en_sim_valid;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::setSimulationMode@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::setSimulationMode@

        if ( sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS) )
        {
        	en_sim.en_sim_mode = pRequestData->eEn_sim_mode;

        	Nvm_SetBlockById(NVM_BLOCK_CUBEADCS_SIMULATION_MODE, (void *)&en_sim, NVMSETBLOCK_STORE_IMMEDIATELY);

        	/* Check result of set operation */
        	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_SIMULATION_MODE, &en_sim_valid);

        	if ( en_sim.en_sim_mode == en_sim_valid.en_sim_mode )
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        	}
        	else
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
        	}
        }
        else
        {
        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::setSimulationMode@

        respResult = OBC_CUBEADCS_setSimulationModeResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_SETSIMULATIONMODE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::setSimulationMode (ID = 0x0000001E)

// @START@ Request handler for method OBC_CUBEADCS::getSimulationModeValue (ID = 0x0000001F)
static void OBC_CUBEADCS_getSimulationModeValueRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_SafeBool_t eEn_sim_mode;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getSimulationModeValue@
    cubeadcs_sim_mode_t en_sim;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getSimulationModeValue@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getSimulationModeValue@
        
        if ( sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS) )
        {
        	Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_SIMULATION_MODE, &en_sim);

        	eEn_sim_mode = en_sim.en_sim_mode;

        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        }
        else
        {
        	eEn_sim_mode = SAFE_FALSE;

        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getSimulationModeValue@

        respResult = OBC_CUBEADCS_getSimulationModeValueResp(
                        &respCtx,
                        eEn_sim_mode,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETSIMULATIONMODEVALUE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getSimulationModeValue (ID = 0x0000001F)

// @START@ Request handler for method OBC_CUBEADCS::getOBCCommAndErrCounters (ID = 0x00000020)
static void OBC_CUBEADCS_getOBCCommAndErrCountersRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_ErrCounters_t sCounters;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getOBCCommAndErrCounters@
    CubeADCS_CmdCfg_t sNewCmd;
    uint16_t err_cnts[62];
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getOBCCommAndErrCounters@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getOBCCommAndErrCounters@

    	if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
    	{
    		sNewCmd.pvCmdResDst = (void *)&err_cnts[0];
    		sNewCmd.u16CmdResDstSize = sizeof(err_cnts);

    		if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GET_OBC_ERR_COUNTERS, &sNewCmd, NULL) )
    		{
    			memcpy((void *)&sCounters, &err_cnts[0], sizeof(err_cnts));

    			eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
    		}
    		else
    		{
    			eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
    		}
    	}
    	else
    	{
    		eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
    	}

        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getOBCCommAndErrCounters@

        respResult = OBC_CUBEADCS_getOBCCommAndErrCountersResp(
                        &respCtx,
                        &sCounters,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETOBCCOMMANDERRCOUNTERS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getOBCCommAndErrCounters (ID = 0x00000020)

// @START@ Request handler for method OBC_CUBEADCS::clrOBCCommAndErrCounters (ID = 0x00000021)
static void OBC_CUBEADCS_clrOBCCommAndErrCountersRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSclrOBCCommAndErrCountersRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::clrOBCCommAndErrCounters@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::clrOBCCommAndErrCounters@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::clrOBCCommAndErrCounters@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
        	sNewCmd.pu8CmdData = (uint8_t *)&pRequestData->sRange;
        	sNewCmd.u16CmdDataSize = sizeof(pRequestData->sRange);

        	if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_CLR_OBC_ERR_COUNTERS, &sNewCmd, NULL) )
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        	}
        	else
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
        	}
        }
        else
        {
        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::clrOBCCommAndErrCounters@

        respResult = OBC_CUBEADCS_clrOBCCommAndErrCountersResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_CLROBCCOMMANDERRCOUNTERS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::clrOBCCommAndErrCounters (ID = 0x00000021)

// @START@ Request handler for method OBC_CUBEADCS::getFDIRCouners (ID = 0x00000022)
static void OBC_CUBEADCS_getFDIRCounersRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_FDIRCounters_t sCounters;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getFDIRCouners@
    CubeADCS_CmdCfg_t sNewCmd;
    uint8_t errHandlCntrs[17];
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getFDIRCouners@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getFDIRCouners@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
        	sNewCmd.pvCmdResDst = (void *)&errHandlCntrs[0];
        	sNewCmd.u16CmdResDstSize = COUNT_OF(errHandlCntrs);

        	if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GET_FLAG_ERR_COUNTERS, &sNewCmd, NULL) )
        	{
        		memcpy((void *)&sCounters, &errHandlCntrs[0], sizeof(errHandlCntrs));

        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        	}
        	else
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
        	}
        }
        else
        {
        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getFDIRCouners@

        respResult = OBC_CUBEADCS_getFDIRCounersResp(
                        &respCtx,
                        &sCounters,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETFDIRCOUNERS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getFDIRCouners (ID = 0x00000022)

// @START@ Request handler for method OBC_CUBEADCS::clrFDIRCounters (ID = 0x00000023)
static void OBC_CUBEADCS_clrFDIRCountersRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSclrFDIRCountersRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::clrFDIRCounters@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::clrFDIRCounters@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::clrFDIRCounters@

        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
        	sNewCmd.pu8CmdData = (uint8_t *)&pRequestData->sRange;
        	sNewCmd.u16CmdDataSize = sizeof(pRequestData->sRange);

        	if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_CLR_FLAG_ERR_COUNTERS, &sNewCmd, NULL) )
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        	}
        	else
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
        	}
        }
        else
        {
        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }

        // @USER_CODE_SECTION_END@OBC_CUBEADCS::clrFDIRCounters@

        respResult = OBC_CUBEADCS_clrFDIRCountersResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_CLRFDIRCOUNTERS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::clrFDIRCounters (ID = 0x00000023)

// @START@ Request handler for method OBC_CUBEADCS::stopFileTransfer (ID = 0x00000024)
static void OBC_CUBEADCS_stopFileTransferRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::stopFileTransfer@
    CubeADCS_CmdCfg_t sNewCmd;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::stopFileTransfer@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::stopFileTransfer@
        
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
        	if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_STOP_FILE_TRANSFER, &sNewCmd, NULL) )
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
        	}
        	else
        	{
        		eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
        	}
        }
        else
        {
        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::stopFileTransfer@

        respResult = OBC_CUBEADCS_stopFileTransferResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_STOPFILETRANSFER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::stopFileTransfer (ID = 0x00000024)

// @START@ Request handler for method OBC_CUBEADCS::getRunTimeLatchedErrs (ID = 0x00000025)
static void OBC_CUBEADCS_getRunTimeLatchedErrsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    bool bNodeRecoveryErr;
    bool bRangeErr;
    bool bRateSensFailure;
    bool bMagnetometerErr;
    bool bOrbitParamsErr;
    bool bConfigInvalid;
    bool bCntrlModeChgErr;
    bool bEstModeChgErr;
    bool bSysStateChgErr;
    uint8_t u8Reserved;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getRunTimeLatchedErrs@
    CubeADCS_CmdCfg_t sNewCmd;
    uint16_t errs;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getRunTimeLatchedErrs@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getRunTimeLatchedErrs@

    	bNodeRecoveryErr = false;
    	bRangeErr = false;
    	bRateSensFailure = false;
    	bMagnetometerErr = false;
    	bOrbitParamsErr = false;
    	bConfigInvalid = false;
    	bCntrlModeChgErr = false;
    	bEstModeChgErr = false;
    	bSysStateChgErr = false;

    	u8Reserved = 0;

        if( sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS) )
        {
            sNewCmd.pvCmdResDst = (void *)&errs;
            sNewCmd.u16CmdResDstSize = sizeof(errs);

            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GET_RUNTIME_LATCHED_ERR, &sNewCmd, NULL) )
            {
            	bNodeRecoveryErr = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_NODERECOVERY_ERR);
            	bRangeErr = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_RANGE_ERR);
            	bRateSensFailure = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_RATESENSORFAILURE_ERR);
				bMagnetometerErr = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_MAGNETOMETER_ERR);
				bOrbitParamsErr = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_ORBITPARAMS_ERR);
				bConfigInvalid = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_CONFIGINVALID_ERR);
				bCntrlModeChgErr = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_CNTRLMODECHG_ERR);
				bEstModeChgErr = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_ESTMODECHG_ERR);
				bSysStateChgErr = is_bit_set(errs, OBC_CUBEADCS_RUNTIMELATCHEDERRFLAGS_SYSSTATE_ERR);

            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
        	eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getRunTimeLatchedErrs@

        respResult = OBC_CUBEADCS_getRunTimeLatchedErrsResp(
                        &respCtx,
                        bNodeRecoveryErr,
                        bRangeErr,
                        bRateSensFailure,
                        bMagnetometerErr,
                        bOrbitParamsErr,
                        bConfigInvalid,
                        bCntrlModeChgErr,
                        bEstModeChgErr,
                        bSysStateChgErr,
                        u8Reserved,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETRUNTIMELATCHEDERRS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getRunTimeLatchedErrs (ID = 0x00000025)

// @START@ Request handler for method OBC_CUBEADCS::getFaultyNodeStatus (ID = 0x00000026)
static void OBC_CUBEADCS_getFaultyNodeStatusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    bool bSignalMCU;
    bool bMotorMCU;
    bool bCubeSense1;
    bool bCubeSense2;
    bool bCubeStar;
    bool bRWheel1;
    bool bRWheel2;
    bool bRWheel3;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getFaultyNodeStatus@
    CubeADCS_CmdCfg_t sNewCmd;
    uint8_t node_status;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getFaultyNodeStatus@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getFaultyNodeStatus@

        bSignalMCU = false;
        bMotorMCU = false;
        bCubeSense1 = false;
        bCubeSense2 = false;
        bCubeStar = false;
        bRWheel1 = false;
        bRWheel2 = false;
        bRWheel3 = false;
        if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
        {
            sNewCmd.pvCmdResDst = (void *)&node_status;
            sNewCmd.u16CmdResDstSize = sizeof(node_status);
            if ( eCUBEADCS_REQCMD_STATUS_SUCCESS == CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GET_FAULTY_NODE, &sNewCmd, NULL) )
            {
            	bSignalMCU = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_SIGNAL_MCU);
            	bMotorMCU = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_MOTOR_MCU);
            	bCubeSense1 = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_CUBESENSE_1);
            	bCubeSense2 = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_CUBESENSE_2);
            	bCubeStar = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_CUBESTAR);
            	bRWheel1 = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_WHEEL_1);
            	bRWheel2 = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_WHEEL_2);
            	bRWheel3 = is_bit_set(node_status, OBC_CUBEADCS_FAULTYNODEFLAGS_WHEEL_3);

            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
            }
            else
            {
            	eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
            }
        }
        else
        {
            eOpResult = OBC_CUBEADCS_STANDARDRESULT_NOT_SUPPORTED;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getFaultyNodeStatus@

        respResult = OBC_CUBEADCS_getFaultyNodeStatusResp(
                        &respCtx,
                        bSignalMCU,
                        bMotorMCU,
                        bCubeSense1,
                        bCubeSense2,
                        bCubeStar,
                        bRWheel1,
                        bRWheel2,
                        bRWheel3,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETFAULTYNODESTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getFaultyNodeStatus (ID = 0x00000026)

// @START@ Request handler for method OBC_CUBEADCS::setSystemStateCfg (ID = 0x00000027)
static void OBC_CUBEADCS_setSystemStateCfgRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_CUBEADCSsetSystemStateCfgRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::setSystemStateCfg@
    cubeADCS_sys_state_cfg_t temp_sys_state;
    bool res = true;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::setSystemStateCfg@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::setSystemStateCfg@
        cubeadcs_persist_get_nvm_sys_state_cfg(&temp_sys_state);

		for(int i = 0; i < eCUBEADCS_CFGTYPE_NUMBER; i++)
		{
			temp_sys_state.asCubeADCS_SysStates[i].eCfgType                        = pRequestData->asCubeADCS_sys_state_cfg[i].eCfgType;
			temp_sys_state.asCubeADCS_SysStates[i].eCntrlMask                      = pRequestData->asCubeADCS_sys_state_cfg[i].eCntrlMask;
			temp_sys_state.asCubeADCS_SysStates[i].eEstMode                        = pRequestData->asCubeADCS_sys_state_cfg[i].eEstMode;
			temp_sys_state.asCubeADCS_SysStates[i].eRunMask                        = pRequestData->asCubeADCS_sys_state_cfg[i].eRunMask;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeControl_Motor  = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeControl_Motor;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeControl_Signal = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeControl_Signal;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeSense1         = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeSense1;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeSense2         = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeSense2;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeStar           = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeStar;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel1         = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeWheel1;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel2         = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeWheel2;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel3         = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeWheel3;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.GPSPwr             = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eGPSPwr;
			temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.MotorPwr           = pRequestData->asCubeADCS_sys_state_cfg[i].sNodePwrMask.eMotorPwr;
			temp_sys_state.asCubeADCS_SysStates[i].uAdditionalLogic                = pRequestData->asCubeADCS_sys_state_cfg[i].u8AdditionalLogic;
		}

		res = cubeadcs_persist_set_nvm_sys_state_cfg(&temp_sys_state);
		if(true == res)
		{
			eOpResult = OBC_CUBEADCS_STANDARDRESULT_ERROR;
		}
		else
		{
			eOpResult = OBC_CUBEADCS_STANDARDRESULT_SUCCESS;
		}
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::setSystemStateCfg@

        respResult = OBC_CUBEADCS_setSystemStateCfgResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_SETSYSTEMSTATECFG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::setSystemStateCfg (ID = 0x00000027)

// @START@ Request handler for method OBC_CUBEADCS::getSystemStateCfg (ID = 0x00000028)
static void OBC_CUBEADCS_getSystemStateCfgRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_CUBEADCS_CubeADCS_Cfg_t asCubeADCS_sys_state_cfg[15];

    // @USER_VAR_SECTION_START@OBC_CUBEADCS::getSystemStateCfg@
    cubeADCS_sys_state_cfg_t temp_sys_state;
    // @USER_VAR_SECTION_END@OBC_CUBEADCS::getSystemStateCfg@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_CUBEADCS::getSystemStateCfg@
        cubeadcs_persist_get_nvm_sys_state_cfg(&temp_sys_state);
        
        for(int i = 0; i < eCUBEADCS_CFGTYPE_NUMBER; i++)
        {
        	 asCubeADCS_sys_state_cfg[i].eCfgType 						  = temp_sys_state.asCubeADCS_SysStates[i].eCfgType;
        	 asCubeADCS_sys_state_cfg[i].eCntrlMask                       = temp_sys_state.asCubeADCS_SysStates[i].eCntrlMask;
        	 asCubeADCS_sys_state_cfg[i].eEstMode                         = temp_sys_state.asCubeADCS_SysStates[i].eEstMode;
        	 asCubeADCS_sys_state_cfg[i].eRunMask                         = temp_sys_state.asCubeADCS_SysStates[i].eRunMask;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeControl_Motor  = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeControl_Motor;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeControl_Signal = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeControl_Signal;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeSense1         = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeSense1;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeSense2         = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeSense2;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeStar           = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeStar;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeWheel1         = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel1;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeWheel2         = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel2;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eCubeWheel3         = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.CubeWheel3;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eGPSPwr             = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.GPSPwr;
        	 asCubeADCS_sys_state_cfg[i].sNodePwrMask.eMotorPwr           = temp_sys_state.asCubeADCS_SysStates[i].uNodePwrMask.MotorPwr;
        	 asCubeADCS_sys_state_cfg[i].u8AdditionalLogic                = temp_sys_state.asCubeADCS_SysStates[i].uAdditionalLogic;
        }
        // @USER_CODE_SECTION_END@OBC_CUBEADCS::getSystemStateCfg@

        respResult = OBC_CUBEADCS_getSystemStateCfgResp(
                        &respCtx,
                        asCubeADCS_sys_state_cfg
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS, OBC_CUBEADCS_GETSYSTEMSTATECFG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_CUBEADCS::getSystemStateCfg (ID = 0x00000028)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void OBC_CUBEADCSServerAppInit(void)
{
    OBC_CUBEADCS_registerServerApi(&OBC_CUBEADCSServerApiCtx);
}
