/*!
********************************************************************************************
* @file FP_nvmServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface nvm v0.1
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

#include "FP_nvmProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include <nvm/inc/nvm.h>
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void nvm_restore_defaultsRequestHandlerImpl(ReqContext_t* pReqCtx,
            const nvmrestore_defaultsRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static nvm_ServerApi_t nvmServerApiCtx =
{
  .nvm_restore_defaultsRequestHandler = (pfnvm_restore_defaultsRequestHandler_t) nvm_restore_defaultsRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method nvm::restore_defaults (ID = 0x00000000)
static void nvm_restore_defaultsRequestHandlerImpl(ReqContext_t *pReqCtx,
            const nvmrestore_defaultsRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    NVM_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@nvm::restore_defaults@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@nvm::restore_defaults@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@nvm::restore_defaults@

        if (pRequestData->eBlock_id < NVM_BLOCK_MAX_COUNT)
        {
            Nvm_RestoreBlockDefaults(pRequestData->eBlock_id);
            eOp_result = NVM_STANDARDRESULT_SUCCESS;
        }
        else
        {
            eOp_result = NVM_STANDARDRESULT_INVALID_ARGS;
        }

        // @USER_CODE_SECTION_END@nvm::restore_defaults@

        respResult = nvm_restore_defaultsResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_NVM, NVM_RESTORE_DEFAULTS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method nvm::restore_defaults (ID = 0x00000000)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void nvmServerAppInit(void)
{
    nvm_registerServerApi(&nvmServerApiCtx);
}
