#include "../inc/upy_fp_gw.h"

#include "CP_Handler.h"
#include "DataSink.h"
#include "ESSA_Stack.h"
#include "es_cdef.h"
#include "upy.h"
/**
 * @addtogroup Services
 * @{
 *
 * @defgroup upython
 * @{
 *
 * @file upy_cp_gw.c
 * @brief upython service cp command gateway
 *
 * @}
 * @}
 */

// FP command GW response context (only one because only one FP command can be
// served at a time)
static sUserResponseCtx_t uPyRespCtx;

typedef struct
{
    // size of GW frame which includes the MAC FP header and data payload
    uint8_t u8PayloadSize;
} PACKED sMicroPythonGwHdr_t;

// this function will be called by the ESSA Stack when the FP layer replies back
// to the received FP request
ESSATMAC_ErrCodes upy_fp_gw_enq_message(ESSATMAC_Context *pMACContext, uint8_t *pMsgData, uint8_t nMsgDataSize) // NOSONAR
{
    ESSATMAC_ErrCodes result = ESSATMAC_EC_ERROR;

    if ((pMACContext != NULL) && (pMsgData != NULL) &&
        (nMsgDataSize >= sizeof(sMicroPythonGwHdr_t)))
    {
        if ((pMACContext->netType == ESSASNETT_MICROPYTHON_GW) &&
            (pMACContext->nInterfaceNumber == MICROPYTHON_GW_IF_ID) &&
            (pMACContext->nPayloadProtocol ==
             ES_SAT_MAC_PROTOCOL_ID_FP_LAYER) &&
            (uPyRespCtx.pu8DataBuf != NULL) &&
            (uPyRespCtx.u32MaxDataSize >= nMsgDataSize))
        {
            // transfer message data back to CP buffer
            (void)memcpy(uPyRespCtx.pu8DataBuf, pMsgData, nMsgDataSize);

            // store actual data size for CP command reply dispatch in
            // cp_cmd_handler_mac_fp_gw_send_cmd(...)
            uPyRespCtx.u32ResponseSize = nMsgDataSize;

            upy_release_thread_wait();

            result = ESSATMAC_EC_OK;
        }
        else
        {
            result = ESSATMAC_EC_INVALID_PARAMS;
        }
    }

    return result;
}

eCPDispatchResult_t upy_fp_gw_send_cmd(uint8_t *pMsgData, uint8_t nMsgDataSize,
                                       uint8_t *pRespBuff, uint8_t nRespBuffSize,
                                       uint8_t *const u8TLError)
{
    eCPDispatchResult_t res = ECPDISPATCHRESULT_ERROR;
    ESSATMAC_Context    MACContext;
    eThreadBlockEvt_t   waitResult = THREADBLOCKEVT_ERROR;

    if (NULL != pMsgData)
    {
        (void)memset((void *)&MACContext, (uint8_t)0, sizeof(ESSATMAC_Context));

        // setup response buffer for ESSA Stack
        uPyRespCtx.pu8DataBuf         = pRespBuff;
        uPyRespCtx.u32MaxDataSize     = nRespBuffSize;
        uPyRespCtx.u32ResponseSize    = 0U;
        uPyRespCtx.onCmdResponseReady = NULL;
        uPyRespCtx.pUserCtx           = NULL;

        MACContext.nInterfaceNumber = MICROPYTHON_GW_IF_ID;
        MACContext.nPayloadProtocol = ES_SAT_MAC_PROTOCOL_ID_FP_LAYER;
        MACContext.nSourceAddr      = 0x00U;
        MACContext.nTargetAddr      = 0x00U;
        MACContext.netType          = ESSASNETT_MICROPYTHON_GW;

        upy_prepare_thread_wait();

        // inject message to ESSA Stack for FP dispatching...
        ESSA_Stack_DataDispatch(&MACContext, pMsgData, nMsgDataSize);

        // wait for CPCmdHandler_uPyFpGwEnqMessage() to be called or timeout...
        waitResult = upy_thread_wait_for_event(UPYFPGW_RESPONSE_TIMEOUT_MS);

        if (waitResult == THREADBlOCKEVT_WAITFINISHED)
        {
            *u8TLError = EESTL_SFERR_SUCCESS;
        }
        else
        {
            if (waitResult == THREADBLOCKEVT_WAITTIMEOUT)
            {
                *u8TLError = EESTL_SFERR_RECEIVE_TIMEOUT;
            }
            else
            {
                *u8TLError = EESTL_SFERR_UNKNOWN;
            }
        }

        res = ECPDISPATCHRESULT_RESULT_OK;
    }

    return res;
}
