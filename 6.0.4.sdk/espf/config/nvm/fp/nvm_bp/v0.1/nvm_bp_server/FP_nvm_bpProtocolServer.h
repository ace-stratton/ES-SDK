/*!
********************************************************************************************
* @file FP_nvm_bpProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_NVM_BPPROTOCOLSERVER_H__
#define __FP_NVM_BPPROTOCOLSERVER_H__

#include "FP_nvm_bpProtocolTypes.h"

typedef void (*pfnvm_bp_set_eps_bp_mac_addressRequestHandler_t)(ReqContext_t *ctx, nvm_bpset_eps_bp_mac_addressRequestData_t *pRequestData);
typedef void (*pfnvm_bp_get_eps_bp_mac_addressRequestHandler_t)(ReqContext_t *ctx, nvm_bpget_eps_bp_mac_addressRequestData_t *pRequestData);

typedef struct {
    pfnvm_bp_set_eps_bp_mac_addressRequestHandler_t nvm_bp_set_eps_bp_mac_addressRequestHandler;
    pfnvm_bp_get_eps_bp_mac_addressRequestHandler_t nvm_bp_get_eps_bp_mac_addressRequestHandler;
} nvm_bp_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_nvm_bpProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void nvm_bp_registerServerApi(nvm_bp_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_nvm_bpProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t nvm_bp_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes nvm_bp_set_eps_bp_mac_addressResp(
                RespContext_t* ctx,
                const NVM_BP_StandardResult_t eOp_result
);

ESSATMAC_ErrCodes nvm_bp_get_eps_bp_mac_addressResp(
                RespContext_t* ctx,
                const uint8_t u8Mac_address,
                const NVM_BP_StandardResult_t eOp_result
);


#endif  // #ifndef __FP_NVM_BPPROTOCOLSERVER_H__
