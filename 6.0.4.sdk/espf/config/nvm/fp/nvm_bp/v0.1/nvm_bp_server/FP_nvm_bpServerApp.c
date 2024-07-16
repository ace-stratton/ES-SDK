/*!
********************************************************************************************
* @file FP_nvm_bpServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface nvm_bp v0.1
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

#include "FP_nvm_bpProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "CommandsApi.h"
#include "module_id.h"
#include "debug.h"
#include "FWUPD_Persistor.h"
#include "AppTasks.h"
#include "nvm_resetcounters.h"
#include "nvm.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void nvm_bp_set_eps_bp_mac_addressRequestHandlerImpl(ReqContext_t* pReqCtx,
            const nvm_bpset_eps_bp_mac_addressRequestData_t* pRequestData);

static void nvm_bp_get_eps_bp_mac_addressRequestHandlerImpl(ReqContext_t* pReqCtx,
            const nvm_bpget_eps_bp_mac_addressRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static nvm_bp_ServerApi_t nvm_bpServerApiCtx =
{
  .nvm_bp_set_eps_bp_mac_addressRequestHandler = (pfnvm_bp_set_eps_bp_mac_addressRequestHandler_t) nvm_bp_set_eps_bp_mac_addressRequestHandlerImpl,
  .nvm_bp_get_eps_bp_mac_addressRequestHandler = (pfnvm_bp_get_eps_bp_mac_addressRequestHandler_t) nvm_bp_get_eps_bp_mac_addressRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method nvm_bp::set_eps_bp_mac_address (ID = 0x00000001)
static void nvm_bp_set_eps_bp_mac_addressRequestHandlerImpl(ReqContext_t *pReqCtx,
            const nvm_bpset_eps_bp_mac_addressRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    NVM_BP_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@nvm_bp::set_eps_bp_mac_address@
    mac_address_book_t addresses = {0};
    // @USER_VAR_SECTION_END@nvm_bp::set_eps_bp_mac_address@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@nvm_bp::set_eps_bp_mac_address@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        if (NVM_BP_EPSBPIDTYPE_MAX_CNT <= pRequestData->eDevice_id){
            eOp_result = NVM_BP_STANDARDRESULT_INVALID_ARGS;
        }
        // Check for invalid MAC ADDRESSES
        else if( ESSATMAC_ADDR_BROADCAST == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_GATEWAY_DEV == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_UNINITIALIZED_DEV == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_GATEWAY_EPSIIBP == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_GATEWAY_EPSIIPDM == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_EXTERNAL_MAC_DONGLE == pRequestData->u8New_mac_address)
        {
            eOp_result = NVM_BP_STANDARDRESULT_INVALID_ARGS;
        }
        else {
            eOp_result = NVM_BP_STANDARDRESULT_ERROR;
            // Read the NVM
            Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

            // Verify if the nvm was read
            if (NULL != addresses.a_mac_address){
                addresses.a_eps_batterypack_addresses[pRequestData->eDevice_id] = pRequestData->u8New_mac_address;
                Nvm_SetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses, true);
                eOp_result = NVM_BP_STANDARDRESULT_SUCCESS;
            }
        }
        
        // @USER_CODE_SECTION_END@nvm_bp::set_eps_bp_mac_address@

        respResult = nvm_bp_set_eps_bp_mac_addressResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_NVM_BP, NVM_BP_SET_EPS_BP_MAC_ADDRESS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method nvm_bp::set_eps_bp_mac_address (ID = 0x00000001)

// @START@ Request handler for method nvm_bp::get_eps_bp_mac_address (ID = 0x00000002)
static void nvm_bp_get_eps_bp_mac_addressRequestHandlerImpl(ReqContext_t *pReqCtx,
            const nvm_bpget_eps_bp_mac_addressRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Mac_address;
    NVM_BP_StandardResult_t eOp_result;

    // @USER_VAR_SECTION_START@nvm_bp::get_eps_bp_mac_address@
    mac_address_book_t addresses = {0};
    // @USER_VAR_SECTION_END@nvm_bp::get_eps_bp_mac_address@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@nvm_bp::get_eps_bp_mac_address@
        
        u8Mac_address = 0;

        if (NVM_BP_EPSBPIDTYPE_MAX_CNT <= pRequestData->eDevice_id){
            eOp_result = NVM_BP_STANDARDRESULT_INVALID_ARGS;
        }
        else {
            eOp_result = NVM_BP_STANDARDRESULT_ERROR;

            // Read the NVM
            Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

            u8Mac_address = addresses.a_eps_batterypack_addresses[pRequestData->eDevice_id];
            eOp_result = NVM_BP_STANDARDRESULT_SUCCESS;
        }
        
        // @USER_CODE_SECTION_END@nvm_bp::get_eps_bp_mac_address@

        respResult = nvm_bp_get_eps_bp_mac_addressResp(
                        &respCtx,
                        u8Mac_address,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_NVM_BP, NVM_BP_GET_EPS_BP_MAC_ADDRESS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method nvm_bp::get_eps_bp_mac_address (ID = 0x00000002)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void nvm_bpServerAppInit(void)
{
    nvm_bp_registerServerApi(&nvm_bpServerApiCtx);
}
