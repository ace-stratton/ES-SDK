/*!
********************************************************************************************
* @file FP_cryptoProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface crypto v0.1
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

#ifndef __FP_CRYPTOPROTOCOLSERVER_H__
#define __FP_CRYPTOPROTOCOLSERVER_H__

#include "FP_cryptoProtocolTypes.h"

typedef void (*pfcrypto_update_key_storeRequestHandler_t)(ReqContext_t *ctx, cryptoupdate_key_storeRequestData_t *pRequestData);
typedef void (*pfcrypto_perform_cipher_opRequestHandler_t)(ReqContext_t *ctx, cryptoperform_cipher_opRequestData_t *pRequestData);
typedef void (*pfcrypto_get_cipher_op_statusRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfcrypto_abortRequestHandler_t)(ReqContext_t *ctx, cryptoabortRequestData_t *pRequestData);

typedef struct {
    pfcrypto_update_key_storeRequestHandler_t crypto_update_key_storeRequestHandler;
    pfcrypto_perform_cipher_opRequestHandler_t crypto_perform_cipher_opRequestHandler;
    pfcrypto_get_cipher_op_statusRequestHandler_t crypto_get_cipher_op_statusRequestHandler;
    pfcrypto_abortRequestHandler_t crypto_abortRequestHandler;
} crypto_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_cryptoProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void crypto_registerServerApi(crypto_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_cryptoProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t crypto_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes crypto_update_key_storeResp(
                RespContext_t* ctx,
                const CRYPTO_key_update_status_t eOp_result
);

ESSATMAC_ErrCodes crypto_perform_cipher_opResp(
                RespContext_t* ctx,
                const CRYPTO_cipher_op_status_t eCipher_req_status
);

ESSATMAC_ErrCodes crypto_get_cipher_op_statusResp(
                RespContext_t* ctx,
                const CRYPTO_cipher_op_status_t eCipher_op_status,
                const uint32_t u32Op_time
);

ESSATMAC_ErrCodes crypto_abortResp(
                RespContext_t* ctx,
                const bool bStatus
);


#endif  // #ifndef __FP_CRYPTOPROTOCOLSERVER_H__
