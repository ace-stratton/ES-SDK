/*!
********************************************************************************************
* @file FP_gnssServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface gnss v1.0
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

#include "FP_gnssProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "gnss.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void gnss_set_powerRequestHandlerImpl(ReqContext_t* pReqCtx,
            const gnssset_powerRequestData_t* pRequestData);

static void gnss_get_powerRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static gnss_ServerApi_t gnssServerApiCtx =
{
  .gnss_set_powerRequestHandler = (pfgnss_set_powerRequestHandler_t) gnss_set_powerRequestHandlerImpl,
  .gnss_get_powerRequestHandler = (pfgnss_get_powerRequestHandler_t) gnss_get_powerRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method gnss::set_power (ID = 0x00000001)
static void gnss_set_powerRequestHandlerImpl(ReqContext_t *pReqCtx,
            const gnssset_powerRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    GNSS_operation_t eOp_status;

    // @USER_VAR_SECTION_START@gnss::set_power@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@gnss::set_power@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@gnss::set_power@
        
        eOp_status = GNSS_OPERATION_ERROR;

        if (GNSS_POWER_ON == pRequestData->ePwr_status)
        {
        	if (STATUS_OK == gnss_run())
        	{
        		eOp_status = GNSS_OPERATION_OK;
        	}
        }
        else
        {
        	if (STATUS_OK == gnss_stop())
        	{
        		eOp_status = GNSS_OPERATION_OK;
        	}
        }
        
        // @USER_CODE_SECTION_END@gnss::set_power@

        respResult = gnss_set_powerResp(
                        &respCtx,
                        eOp_status
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_GNSS, GNSS_SET_POWER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method gnss::set_power (ID = 0x00000001)

// @START@ Request handler for method gnss::get_power (ID = 0x00000003)
static void gnss_get_powerRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    GNSS_operation_t eOp_status;
    GNSS_power_t ePwr_status;

    // @USER_VAR_SECTION_START@gnss::get_power@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@gnss::get_power@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@gnss::get_power@
        
        eOp_status = GNSS_OPERATION_OK;
        ePwr_status = GNSS_POWER_OFF;

        if (true == gnss_is_on())
        {
        	ePwr_status = GNSS_POWER_ON;
        }
        
        // @USER_CODE_SECTION_END@gnss::get_power@

        respResult = gnss_get_powerResp(
                        &respCtx,
                        eOp_status,
                        ePwr_status
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_GNSS, GNSS_GET_POWER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method gnss::get_power (ID = 0x00000003)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void gnssServerAppInit(void)
{
    gnss_registerServerApi(&gnssServerApiCtx);
}
