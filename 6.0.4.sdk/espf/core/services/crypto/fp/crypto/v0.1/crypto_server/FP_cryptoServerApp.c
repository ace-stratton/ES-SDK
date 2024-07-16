/*!
********************************************************************************************
* @file FP_cryptoServerApp.c
* @brief ServerApp implementation template generator
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

#include "FP_cryptoProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "crypto.h"
#include "assertions.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
static void crypto_op_notif(const crypto_api_res_t op_status, const char *const p_encrypted_fname, const uint32_t op_time);
// @END_USER@ USER_LOCAL_FUNC_DECL
static void crypto_update_key_storeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const cryptoupdate_key_storeRequestData_t* pRequestData);

static void crypto_perform_cipher_opRequestHandlerImpl(ReqContext_t* pReqCtx,
            const cryptoperform_cipher_opRequestData_t* pRequestData);

static void crypto_get_cipher_op_statusRequestHandlerImpl(ReqContext_t* pReqCtx);

static void crypto_abortRequestHandlerImpl(ReqContext_t* pReqCtx,
            const cryptoabortRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable dclarations here to preserve them during merge!!!
static crypto_api_res_t last_cipher_op_status = CRYPTO_API_RES_MAX;
static bool fidl_crypto_op_in_progress = false;
static uint32_t last_op_time_ms = 0U;

static void crypto_op_notif(const crypto_api_res_t op_status, const char *const p_encrypted_fname, const uint32_t op_time)
{
    CRIT_ASSERT(op_status < CRYPTO_API_RES_MAX);

    (void) p_encrypted_fname;

    if (fidl_crypto_op_in_progress)
    {
        last_cipher_op_status = op_status;
        last_op_time_ms = op_time;

        fidl_crypto_op_in_progress = false;
    }
}

// @END_USER@ USER_LOCAL_VARS_DECL

static crypto_ServerApi_t cryptoServerApiCtx =
{
  .crypto_update_key_storeRequestHandler = (pfcrypto_update_key_storeRequestHandler_t) crypto_update_key_storeRequestHandlerImpl,
  .crypto_perform_cipher_opRequestHandler = (pfcrypto_perform_cipher_opRequestHandler_t) crypto_perform_cipher_opRequestHandlerImpl,
  .crypto_get_cipher_op_statusRequestHandler = (pfcrypto_get_cipher_op_statusRequestHandler_t) crypto_get_cipher_op_statusRequestHandlerImpl,
  .crypto_abortRequestHandler = (pfcrypto_abortRequestHandler_t) crypto_abortRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method crypto::update_key_store (ID = 0x00000000)
static void crypto_update_key_storeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const cryptoupdate_key_storeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CRYPTO_key_update_status_t eOp_result;

    // @USER_VAR_SECTION_START@crypto::update_key_store@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@crypto::update_key_store@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@crypto::update_key_store@

        crypto_key_upd_status_t res = crypto_update_key_store(pRequestData->au8Key, pRequestData->u8KeySize);

        if (CRYPTO_KEY_UPD_STATUS_BAD_SIZE == res)
        {
            eOp_result = CRYPTO_KEY_UPDATE_STATUS_BAD_SIZE;
        } else if (CRYPTO_KEY_UPD_STATUS_OK == res)
        {
            eOp_result = CRYPTO_KEY_UPDATE_STATUS_OK;
        } else if (CRYPTO_KEY_UPD_STATUS_STORE_ERROR == res)
        {
            eOp_result = CRYPTO_KEY_UPD_STATUS_STORE_ERROR;
        }
        else
        {
            eOp_result = CRYPTO_KEY_UPD_STATUS_STORE_ERROR;
        }

        // @USER_CODE_SECTION_END@crypto::update_key_store@

        respResult = crypto_update_key_storeResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CRYPTO, CRYPTO_UPDATE_KEY_STORE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method crypto::update_key_store (ID = 0x00000000)

// @START@ Request handler for method crypto::perform_cipher_op (ID = 0x00000001)
static void crypto_perform_cipher_opRequestHandlerImpl(ReqContext_t *pReqCtx,
            const cryptoperform_cipher_opRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CRYPTO_cipher_op_status_t eCipher_req_status;

    // @USER_VAR_SECTION_START@crypto::perform_cipher_op@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@crypto::perform_cipher_op@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@crypto::perform_cipher_op@

        if (!fidl_crypto_op_in_progress)
        {
            crypto_req_status_t crypto_req_status;

            fidl_crypto_op_in_progress = true;
            last_cipher_op_status = CRYPTO_API_RES_MAX;

            if (CRYPTO_CIPHER_OP_TYPE_ENCRYPT == pRequestData->eCipher_op)
            {
                crypto_req_status = crypto_std_encrypt_file(pRequestData->strSrc_file_name, pRequestData->strTarget_file_name, &crypto_op_notif);
            }
            else
            {
                crypto_req_status = crypto_std_decrypt_file(pRequestData->strSrc_file_name, pRequestData->strTarget_file_name, &crypto_op_notif);
            }

            if (CRYPTO_REQ_STATUS_OK == crypto_req_status)
            {
                eCipher_req_status = CRYPTO_API_RES_OK;
            }
            else if (CRYPTO_REQ_STATUS_NO_KEY == crypto_req_status)
            {
                fidl_crypto_op_in_progress = false;
                eCipher_req_status = CRYPTO_API_RES_NO_KEY;
            }
            else if (CRYPTO_REQ_STATUS_NO_FILE == crypto_req_status)
            {
            	fidl_crypto_op_in_progress = false;
            	eCipher_req_status = CRYPTO_API_RES_NO_FILE;
            }
            else
            {
            	fidl_crypto_op_in_progress = false;
                eCipher_req_status = CRYPTO_API_RES_ERROR;
            }
        }
        else
        {
            eCipher_req_status = CRYPTO_CIPHER_OP_STATUS_BUSY;
        }
        // @USER_CODE_SECTION_END@crypto::perform_cipher_op@

        respResult = crypto_perform_cipher_opResp(
                        &respCtx,
                        eCipher_req_status
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CRYPTO, CRYPTO_PERFORM_CIPHER_OP_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method crypto::perform_cipher_op (ID = 0x00000001)

// @START@ Request handler for method crypto::get_cipher_op_status (ID = 0x00000002)
static void crypto_get_cipher_op_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    CRYPTO_cipher_op_status_t eCipher_op_status;
    uint32_t u32Op_time;

    // @USER_VAR_SECTION_START@crypto::get_cipher_op_status@
    const CRYPTO_cipher_op_status_t api_res_map[CRYPTO_API_RES_MAX] =
    {
        CRYPTO_CIPHER_OP_STATUS_EOS,
        CRYPTO_CIPHER_OP_STATUS_INVALID_HEADER,
        CRYPTO_CIPHER_OP_STATUS_INVALID_FOOTER,
        CRYPTO_CIPHER_OP_STATUS_INVALID_CIPHER_OFS,
        CRYPTO_CIPHER_OP_STATUS_FILE_ERROR,
        CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_ERROR,
        CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_KEY_ERROR,
        CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_IV_ERROR,
        CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_AAD_ERROR,
        CRYPTO_CIPHER_OP_STATUS_PARTIAL_FILE,
        CRYPTO_CIPHER_OP_STATUS_AUTH_ERROR,
        CRYPTO_CIPHER_OP_STATUS_BAD_PARAMS,
        CRYPTO_CIPHER_OP_STATUS_NO_KEY,
        CRYPTO_CIPHER_OP_STATUS_ABORTED,
        CRYPTO_CIPHER_OP_STATUS_ERROR,
        CRYPTO_CIPHER_OP_STATUS_BUSY,
        CRYPTO_CIPHER_OP_STATUS_OK
    };
    // @USER_VAR_SECTION_END@crypto::get_cipher_op_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@crypto::get_cipher_op_status@

        u32Op_time = 0U;

        if (!fidl_crypto_op_in_progress)
        {
            if (last_cipher_op_status < CRYPTO_API_RES_MAX)
            {
                eCipher_op_status = api_res_map[last_cipher_op_status];
                u32Op_time = last_op_time_ms;
            }
            else
            {
                eCipher_op_status = CRYPTO_CIPHER_OP_STATUS_ERROR;
            }
        }
        else
        {
            eCipher_op_status = CRYPTO_CIPHER_OP_STATUS_BUSY;
        }
        // @USER_CODE_SECTION_END@crypto::get_cipher_op_status@

        respResult = crypto_get_cipher_op_statusResp(
                        &respCtx,
                        eCipher_op_status,
                        u32Op_time
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CRYPTO, CRYPTO_GET_CIPHER_OP_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method crypto::get_cipher_op_status (ID = 0x00000002)

// @START@ Request handler for method crypto::abort (ID = 0x00000003)
static void crypto_abortRequestHandlerImpl(ReqContext_t *pReqCtx,
            const cryptoabortRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    bool bStatus;

    // @USER_VAR_SECTION_START@crypto::abort@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@crypto::abort@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@crypto::abort@

        crypto_abort_op_t abort_op = CRYPTO_ABORT_OP_CURRENT;

        if (CRYPTO_ABORT_TYPE_CURRENT_ONLY == pRequestData->eOp_type)
        {
            abort_op = CRYPTO_ABORT_OP_CURRENT;
        } else if (CRYPTO_ABORT_TYPE_ALL == pRequestData->eOp_type)
        {
            abort_op = CRYPTO_ABORT_OP_ALL;
        }

        crypto_abort(abort_op);

        bStatus = true;

        // @USER_CODE_SECTION_END@crypto::abort@

        respResult = crypto_abortResp(
                        &respCtx,
                        bStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_CRYPTO, CRYPTO_ABORT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method crypto::abort (ID = 0x00000003)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void cryptoServerAppInit(void)
{
    crypto_registerServerApi(&cryptoServerApiCtx);
}
