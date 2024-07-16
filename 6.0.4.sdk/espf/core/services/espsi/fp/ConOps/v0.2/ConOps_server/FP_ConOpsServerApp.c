/*!
********************************************************************************************
* @file FP_ConOpsServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface ConOps v0.2
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

#include "FP_ConOpsProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include <time.h>


#include "conops.h"
#include "payload_scheduler.h"
#include "nvm/inc/nvm.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void ConOps_sendNewEventRequestHandlerImpl(ReqContext_t* pReqCtx,
            const ConOpssendNewEventRequestData_t* pRequestData);

static void ConOps_getOpModeRequestHandlerImpl(ReqContext_t* pReqCtx);

static void ConOps_setThreshValRequestHandlerImpl(ReqContext_t* pReqCtx,
            const ConOpssetThreshValRequestData_t* pRequestData);

static void ConOps_getThreshValRequestHandlerImpl(ReqContext_t* pReqCtx,
            const ConOpsgetThreshValRequestData_t* pRequestData);

static void ConOps_setAllThreshValRequestHandlerImpl(ReqContext_t* pReqCtx,
            const ConOpssetAllThreshValRequestData_t* pRequestData);

static void ConOps_getAllThreshValRequestHandlerImpl(ReqContext_t* pReqCtx);

static void ConOps_addNewScheduleRecordRequestHandlerImpl(ReqContext_t* pReqCtx,
            const ConOpsaddNewScheduleRecordRequestData_t* pRequestData);

static void ConOps_clearScheduleRecordsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void ConOps_setEnableSunTrackingFlagRequestHandlerImpl(ReqContext_t* pReqCtx,
            const ConOpssetEnableSunTrackingFlagRequestData_t* pRequestData);

static void ConOps_getEnableSunTrackingFlagRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static ConOps_ServerApi_t ConOpsServerApiCtx =
{
  .ConOps_sendNewEventRequestHandler = (pfConOps_sendNewEventRequestHandler_t) ConOps_sendNewEventRequestHandlerImpl,
  .ConOps_getOpModeRequestHandler = (pfConOps_getOpModeRequestHandler_t) ConOps_getOpModeRequestHandlerImpl,
  .ConOps_setThreshValRequestHandler = (pfConOps_setThreshValRequestHandler_t) ConOps_setThreshValRequestHandlerImpl,
  .ConOps_getThreshValRequestHandler = (pfConOps_getThreshValRequestHandler_t) ConOps_getThreshValRequestHandlerImpl,
  .ConOps_setAllThreshValRequestHandler = (pfConOps_setAllThreshValRequestHandler_t) ConOps_setAllThreshValRequestHandlerImpl,
  .ConOps_getAllThreshValRequestHandler = (pfConOps_getAllThreshValRequestHandler_t) ConOps_getAllThreshValRequestHandlerImpl,
  .ConOps_addNewScheduleRecordRequestHandler = (pfConOps_addNewScheduleRecordRequestHandler_t) ConOps_addNewScheduleRecordRequestHandlerImpl,
  .ConOps_clearScheduleRecordsRequestHandler = (pfConOps_clearScheduleRecordsRequestHandler_t) ConOps_clearScheduleRecordsRequestHandlerImpl,
  .ConOps_setEnableSunTrackingFlagRequestHandler = (pfConOps_setEnableSunTrackingFlagRequestHandler_t) ConOps_setEnableSunTrackingFlagRequestHandlerImpl,
  .ConOps_getEnableSunTrackingFlagRequestHandler = (pfConOps_getEnableSunTrackingFlagRequestHandler_t) ConOps_getEnableSunTrackingFlagRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method ConOps::sendNewEvent (ID = 0x00000001)
static void ConOps_sendNewEventRequestHandlerImpl(ReqContext_t *pReqCtx,
            const ConOpssendNewEventRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::sendNewEvent@
#if defined(OPMODES_ENABLED)
    sConOps_pay_cfg_t sNewPayCfg;
#endif /* OPMODES_ENABLED */
    // @USER_VAR_SECTION_END@ConOps::sendNewEvent@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::sendNewEvent@

#if defined(OPMODES_ENABLED)

        if ( (pRequestData->sEventPayCfg.u8PayId < PAYLOAD_COUNT)
          && (pRequestData->eEventType < CONOPS_EVENTS_MAX_CNT))
        {
        	sNewPayCfg.payload_id = pRequestData->sEventPayCfg.u8PayId;
        	memcpy(&sNewPayCfg.pointing_cfg, &pRequestData->sEventPayCfg.sAdcsCfg, sizeof(record_adcs_t));
        	memcpy(&sNewPayCfg.payload_args, &pRequestData->sEventPayCfg.sArgs, sizeof(pl_args_t));

			conops_trigger_hsm(pRequestData->eEventType, &sNewPayCfg);

			eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
        }
        else
        {
        	eOpResult = CONOPS_STANDARDRESULT_INVALID_ARGS;
        }
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */

        // @USER_CODE_SECTION_END@ConOps::sendNewEvent@

        respResult = ConOps_sendNewEventResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_SENDNEWEVENT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::sendNewEvent (ID = 0x00000001)

// @START@ Request handler for method ConOps::getOpMode (ID = 0x00000002)
static void ConOps_getOpModeRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_OpModes_t eOpModeNum;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::getOpMode@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@ConOps::getOpMode@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::getOpMode@

#if defined(OPMODES_ENABLED)
        conops_get_hsm_active_state(&eOpModeNum);

        eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */


        // @USER_CODE_SECTION_END@ConOps::getOpMode@

        respResult = ConOps_getOpModeResp(
                        &respCtx,
                        eOpModeNum,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_GETOPMODE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::getOpMode (ID = 0x00000002)

// @START@ Request handler for method ConOps::setThreshVal (ID = 0x00000003)
static void ConOps_setThreshValRequestHandlerImpl(ReqContext_t *pReqCtx,
            const ConOpssetThreshValRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::setThreshVal@
#if defined(OPMODES_ENABLED)
    int32_t i32NewThreshVal;
#endif /* OPMODES_ENABLED */
    // @USER_VAR_SECTION_END@ConOps::setThreshVal@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::setThreshVal@

#if defined(OPMODES_ENABLED)
        i32NewThreshVal = pRequestData->i32ThreshValue;
        if (true == conops_set_thresh_val(&i32NewThreshVal, pRequestData->u8PayloadNum, pRequestData->eThresholdType) )
        	eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
        else
        	eOpResult = CONOPS_STANDARDRESULT_ERROR;
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */

        // @USER_CODE_SECTION_END@ConOps::setThreshVal@

        respResult = ConOps_setThreshValResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_SETTHRESHVAL_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::setThreshVal (ID = 0x00000003)

// @START@ Request handler for method ConOps::getThreshVal (ID = 0x00000004)
static void ConOps_getThreshValRequestHandlerImpl(ReqContext_t *pReqCtx,
            const ConOpsgetThreshValRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    int32_t i32ThreshValue;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::getThreshVal@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@ConOps::getThreshVal@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::getThreshVal@

#if defined(OPMODES_ENABLED)
        if (true == conops_get_thresh_val((void *)&i32ThreshValue, pRequestData->u8PayloadNum, pRequestData->eThresholdType) )
        	eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
        else
        	eOpResult = CONOPS_STANDARDRESULT_ERROR;
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */

        // @USER_CODE_SECTION_END@ConOps::getThreshVal@

        respResult = ConOps_getThreshValResp(
                        &respCtx,
                        i32ThreshValue,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_GETTHRESHVAL_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::getThreshVal (ID = 0x00000004)

// @START@ Request handler for method ConOps::setAllThreshVal (ID = 0x00000005)
static void ConOps_setAllThreshValRequestHandlerImpl(ReqContext_t *pReqCtx,
            const ConOpssetAllThreshValRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::setAllThreshVal@
    // @USER_VAR_SECTION_END@ConOps::setAllThreshVal@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::setAllThreshVal@

#if defined(OPMODES_ENABLED)
        if (true == conops_set_all_thresh_val(&pRequestData->sThreshVals))
        {
           eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
        }
        else
        {
           eOpResult = CONOPS_STANDARDRESULT_ERROR;
        }
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */

        // @USER_CODE_SECTION_END@ConOps::setAllThreshVal@

        respResult = ConOps_setAllThreshValResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_SETALLTHRESHVAL_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::setAllThreshVal (ID = 0x00000005)

// @START@ Request handler for method ConOps::getAllThreshVal (ID = 0x00000006)
static void ConOps_getAllThreshValRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_ThresholdValues_t sThreshVals;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::getAllThreshVal@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@ConOps::getAllThreshVal@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::getAllThreshVal@

#if defined(OPMODES_ENABLED)
        if (true == conops_get_all_thresh_val(&sThreshVals))
        {
            eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
        }
         else
        {
            eOpResult = CONOPS_STANDARDRESULT_ERROR;
        }
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */

        // @USER_CODE_SECTION_END@ConOps::getAllThreshVal@

        respResult = ConOps_getAllThreshValResp(
                        &respCtx,
                        &sThreshVals,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_GETALLTHRESHVAL_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::getAllThreshVal (ID = 0x00000006)

// @START@ Request handler for method ConOps::addNewScheduleRecord (ID = 0x00000007)
static void ConOps_addNewScheduleRecordRequestHandlerImpl(ReqContext_t *pReqCtx,
            const ConOpsaddNewScheduleRecordRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::addNewScheduleRecord@
#if defined(OPMODES_ENABLED)
    record_adcs_t sAdcs_cfg;
    struct tm tm;
    uint32_t ret;
#endif /* OPMODES_ENABLED */
    // @USER_VAR_SECTION_END@ConOps::addNewScheduleRecord@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::addNewScheduleRecord@
#if defined(OPMODES_ENABLED)

        memcpy(&sAdcs_cfg, &pRequestData->sAdcsCfg, sizeof(record_adcs_t));

        tm.tm_year = pRequestData->sTime.i32Year + 100;
        tm.tm_mon = pRequestData->sTime.i32Month - 1;
        tm.tm_mday = pRequestData->sTime.i32Day;
        tm.tm_hour = pRequestData->sTime.i32Hour;
        tm.tm_min = pRequestData->sTime.i32Min;
        tm.tm_sec = pRequestData->sTime.i32Sec;

        ret = mktime(&tm);

        if ( true == PayloadScheduler_addRecord(pRequestData->u8PayloadID, (record_time_t)ret, pRequestData->u16Duration, (record_adcs_t *)&pRequestData->sAdcsCfg, pRequestData->sPayArgs.u8Flags, &pRequestData->sPayArgs.au8Args[0]) )
        	eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
        else
        	eOpResult = CONOPS_STANDARDRESULT_ERROR;

#else
	eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */

        // @USER_CODE_SECTION_END@ConOps::addNewScheduleRecord@

        respResult = ConOps_addNewScheduleRecordResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_ADDNEWSCHEDULERECORD_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::addNewScheduleRecord (ID = 0x00000007)

// @START@ Request handler for method ConOps::clearScheduleRecords (ID = 0x00000008)
static void ConOps_clearScheduleRecordsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::clearScheduleRecords@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@ConOps::clearScheduleRecords@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::clearScheduleRecords@

#if defined(OPMODES_ENABLED)
        PayloadScheduler_clearRecords();

        eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */

        // @USER_CODE_SECTION_END@ConOps::clearScheduleRecords@

        respResult = ConOps_clearScheduleRecordsResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_CLEARSCHEDULERECORDS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::clearScheduleRecords (ID = 0x00000008)

// @START@ Request handler for method ConOps::setEnableSunTrackingFlag (ID = 0x00000009)
static void ConOps_setEnableSunTrackingFlagRequestHandlerImpl(ReqContext_t *pReqCtx,
            const ConOpssetEnableSunTrackingFlagRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::setEnableSunTrackingFlag@
#if defined(OPMODES_ENABLED)
    safe_bool_t bRes;
#endif /* OPMODES_ENABLED */
    // @USER_VAR_SECTION_END@ConOps::setEnableSunTrackingFlag@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::setEnableSunTrackingFlag@
#if defined(OPMODES_ENABLED)

        bRes = conops_set_enable_sun_tracking_flag(pRequestData->eEnFlag);

        if ( IS_TRUE(bRes) )
        	eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
        else
        	eOpResult = CONOPS_STANDARDRESULT_ERROR;
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */


        // @USER_CODE_SECTION_END@ConOps::setEnableSunTrackingFlag@

        respResult = ConOps_setEnableSunTrackingFlagResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_SETENABLESUNTRACKINGFLAG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::setEnableSunTrackingFlag (ID = 0x00000009)

// @START@ Request handler for method ConOps::getEnableSunTrackingFlag (ID = 0x0000000A)
static void ConOps_getEnableSunTrackingFlagRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CONOPS_SafeBool_t eEnFlag;
    CONOPS_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@ConOps::getEnableSunTrackingFlag@
#if defined(OPMODES_ENABLED)
    conops_idle_pointreq_cfg_t sTmpData;
#endif /* OPMODES_ENABLED */
    // @USER_VAR_SECTION_END@ConOps::getEnableSunTrackingFlag@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ConOps::getEnableSunTrackingFlag@
#if defined(OPMODES_ENABLED)
        Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_IDLE_CONFIG, &sTmpData);

        eEnFlag = sTmpData.en_sun_tracking;

        eOpResult = CONOPS_STANDARDRESULT_SUCCESS;
#else
        eOpResult = CONOPS_STANDARDRESULT_NOT_SUPPORTED;
#endif /* OPMODES_ENABLED */
        // @USER_CODE_SECTION_END@ConOps::getEnableSunTrackingFlag@

        respResult = ConOps_getEnableSunTrackingFlagResp(
                        &respCtx,
                        eEnFlag,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CONOPS, CONOPS_GETENABLESUNTRACKINGFLAG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ConOps::getEnableSunTrackingFlag (ID = 0x0000000A)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void ConOpsServerAppInit(void)
{
    ConOps_registerServerApi(&ConOpsServerApiCtx);
}
