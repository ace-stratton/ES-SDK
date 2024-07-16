/*!
********************************************************************************************
* @file FP_BaseProtocolTypes.h
* @brief Protocol base types declarations
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

#ifndef __FP_BASEPROTOCOLTYPES_H__
#define __FP_BASEPROTOCOLTYPES_H__

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "trace.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_Stack.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_FP.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_MAC/ES_SAT_MAC_Protocols.h"

typedef uint16_t SeqId_t;

typedef struct
{
    uint8_t nInterfaceNumber;
    ESSASNetType netType;
    // contains the target address when sending requests and the source address when
    // receiving requests
    uint8_t nAddr;
    SeqId_t seqId;
} ReqContext_t;

typedef struct
{
    uint8_t nInterfaceNumber;
    ESSASNetType netType;
    // contains the target address when sending responses and the source address when
    // receiving responses
    uint8_t nAddr;
    SeqId_t seqId;
} RespContext_t;

typedef struct
{
    funcIdType_t funcId;
    ESSA_pfStack_DataHandler_Cbk_t pfFunc;
} ProtocolFuncArrayEntry_t;

#define REQRESP_FUNC_ID_MASK ((funcIdType_t) 0x80000000)
#define GET_FUNC_ID(hdr)     ((funcIdType_t) ((hdr).funcId & ~REQRESP_FUNC_ID_MASK))
#define SET_REQUEST(hdr)     ((funcIdType_t) ((hdr).funcId &= ~REQRESP_FUNC_ID_MASK))
#define SET_RESPONSE(hdr)    ((funcIdType_t) ((hdr).funcId |= REQRESP_FUNC_ID_MASK))

#define IS_REQUEST(hdr)      (bool) (((funcIdType_t) ((hdr).funcId & REQRESP_FUNC_ID_MASK)) == (funcIdType_t) 0)
#define IS_RESPONSE(hdr)     (bool) (((funcIdType_t) ((hdr).funcId & REQRESP_FUNC_ID_MASK)) == REQRESP_FUNC_ID_MASK)

#define TRACE_ERROR(protocolId, functionId, errorCode) ES_TRACE_ERROR("FP ERROR: Protocol ID = %d, Function ID = %d, Error Code = %d\r\n")

#ifndef MIN
#define MIN(a, b)   (((a) <= (b)) ? ((a)) : ((b)))
#endif  // #ifndef MIN

#define PACKED_STRUCT __attribute__((__packed__))

#define STATIC_ASSERT_SIZE_CHECK(dataType) \
    static_assert(sizeof(dataType) <= ESSATMAC_MAX_MSG_SIZE - (ESSATMAC_FOOTER_SIZE + ESSATMAC_HEADER_SIZE), "Message cannot fit in a single MAC frame!")

#define STACK_SENDFRAME_DEFAULT_PRIO   ESSASMP_NORMAL

#endif  // #ifndef __FP_BASEPROTOCOLTYPES_H__

