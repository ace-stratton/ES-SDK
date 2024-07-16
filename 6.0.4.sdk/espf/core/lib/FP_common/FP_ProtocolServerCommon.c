/*!
********************************************************************************************
* @file FP_ProtocolServerCommon.c
* @brief Protocol server common implementation (for use by multiple servers)
********************************************************************************************
* @version           
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.9
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#include "FP_common/FP_ProtocolServerCommon.h"

ESSATMAC_ErrCodes ProtocolSendErrorResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo, uint8_t errCode)
{
    ESSATMAC_ErrCodes res = ESSATMAC_EC_NULL;
#ifndef BIG_ENDIAN_PLATFORM
    ESSA_Stack_FP_MsgHdr_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(ESSA_Stack_FP_MsgHdr_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (fp_DataInfo != NULL)
    {
        if ((fp_DataInfo->pMACContext != NULL) &&
            (fp_DataInfo->pu8Data != NULL) &&
            (fp_DataInfo->u16DataSize >= sizeof(ESSA_Stack_FP_MsgHdr_t)))
        {
            responseParams = *((ESSA_Stack_FP_MsgHdr_t *) fp_DataInfo->pu8Data);

#ifndef BIG_ENDIAN_PLATFORM
            // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
            responseParams.errCode = errCode;
            SET_RESPONSE(responseParams);
#else // #ifndef BIG_ENDIAN_PLATFORM
        // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

            res = ESSA_Stack_SendFrameReply(fp_DataInfo->pMACContext,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(ESSA_Stack_FP_MsgHdr_t),
                                            ESSASMP_NORMAL);
        }
    }

    return res;
}
