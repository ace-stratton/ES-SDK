/*!
********************************************************************************************
* @file FP_nvmProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_NVMPROTOCOLSERVER_H__
#define __FP_NVMPROTOCOLSERVER_H__

#include "FP_nvmProtocolTypes.h"

typedef void (*pfnvm_restore_defaultsRequestHandler_t)(ReqContext_t *ctx, nvmrestore_defaultsRequestData_t *pRequestData);

typedef struct {
    pfnvm_restore_defaultsRequestHandler_t nvm_restore_defaultsRequestHandler;
} nvm_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_nvmProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void nvm_registerServerApi(nvm_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_nvmProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t nvm_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes nvm_restore_defaultsResp(
                RespContext_t* ctx,
                const NVM_StandardResult_t eOp_result
);


#endif  // #ifndef __FP_NVMPROTOCOLSERVER_H__
