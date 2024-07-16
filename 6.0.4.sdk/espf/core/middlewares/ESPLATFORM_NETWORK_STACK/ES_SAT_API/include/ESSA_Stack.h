/*!
********************************************************************************************
* @file ESSA_Stack.h
* @brief ESSA Stack public header
********************************************************************************************
* @version           N/A
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
********************************************************************************************
*/

#ifndef __ESSA_STACK_H__
#define __ESSA_STACK_H__

#include <stdbool.h>
#include <stdint.h>

#include "../../ES_SAT_MAC/ES_SAT_MAC_Protocols.h"
#include "../../ES_SAT_MAC/ES_SAT_MAC.h"
#include "../../ES_SAT_MAC/ES_SAT_MAC_Context.h"
#include "../../ES_SAT_AIRMAC/ES_SAT_AIRMAC.h"

/**********************************************************************
 *
 *  ESSA stack public defines
 *
 **********************************************************************/
#ifndef COUNT_OF
#define COUNT_OF(x) ((uint32_t) (sizeof(x) / sizeof(x[0])))
#endif  // #ifndef COUNT_OF

#ifndef NETTYPE_HANDLER_ENTRY
#define NETTYPE_HANDLER_ENTRY(netType, funcName)     (funcName)
#endif  // #ifndef NETTYPE_HANDLER_ENTRY

/**********************************************************************
 *
 *  ESSA stack public types
 *
 **********************************************************************/
// Values order used in ESSA_Stack_SendFrame fn
typedef enum
{
    ESSASNI_SYS_PRI = 0,
    ESSASNI_SYS_SEC = 1,
    ESSASNI_PAY_PRI = 2,
    ESSASNI_PAY_SEC = 3,
    ESSANI_MAX
} ESSASNetInterface;

typedef enum
{
    ESSA_eSTACK_OK,
    ESSA_eSTACK_ERROR,
    ESSA_eSTACK_NULL,
    ESSA_eSTACK_PROTOCOL_NOT_FOUND,
} ESSA_eStack_codes_t;

typedef struct
{
    ESSATMAC_Context *pMACContext;
    uint8_t          *pu8Data;
    uint16_t         u16DataSize;
} ESSA_Stack_DataDispatchInfo_t;

typedef struct
{
    uint8_t             u8ProtocolId;
    ESSA_eStack_codes_t eReturnCode;
} ESSA_Stack_StatusDispatchInfo_t;

// Keep those in TQ and at least 2 between them
// And not below 1, since inter byte delay may fool some node to start transmitting in middle of message
#define ESSASMP_PRIORITY_TQ_SPAN    6

typedef enum
{
	ESSASMP_CRITICAL =    1,											// Reserved only for operational modes ! - one needed to ensure at least 1 TQ is passed after last transmission
	ESSASMP_HIGH     =    3,											// Overlap half critical, half normal. Used for entering bootloader, service, discovery etc.
	ESSASMP_NORMAL   =    ESSASMP_CRITICAL + ESSASMP_PRIORITY_TQ_SPAN,	// Usual application level
	ESSASMP_LOW      =    ESSASMP_NORMAL + ESSASMP_PRIORITY_TQ_SPAN,	// Big not time critical packets like pictures etc
} ESSATMAC_MsgPriority;

typedef struct _ESSA_Stack_ProtocolInfo_t         *ESSA_pStack_ProtocolInfo_t;
typedef struct _ESSA_Stack_FunctionProtocolInfo_t *ESSA_pStack_FunctionProtocolInfo_t;

typedef ESSA_pStack_ProtocolInfo_t (*ESSA_pfStack_ProtocolInfoCbk)(void);
typedef void (*ESSA_pfStack_DataHandler_Cbk_t)(ESSA_Stack_DataDispatchInfo_t *pDataInfo);

typedef struct _ESSA_Stack_ProtocolInfo_t
{
    uint16_t                        u16ProtocolId;
    ESSA_pfStack_DataHandler_Cbk_t  pfDataHandlerCbk;
} ESSA_Stack_ProtocolInfo_t;

typedef struct
{
    fpDrvEnqMessage pNetTypeHandler;
    uint16_t mtu;
} ESSA_Stack_NetTypeCfg_t;

typedef struct
{
    const ESSA_Stack_ProtocolInfo_t **ppProtocolCollection;
    uint16_t                  u16ProtocolCollectionSize;
    const ESSA_Stack_NetTypeCfg_t   *p_nettype_cfg;
    uint16_t su16NetTypeHandlersSize;
} ESSA_Stack_Ctx_t;

#define GET_ESNET_PAYLOAD_MTU(net_type)		ESSA_Stack_GetMTU((net_type))

/**********************************************************************
 *
 *  Inter-module FunctionProtocol-related types
 *
 **********************************************************************/
// supported values for the ESSA_Stack_FP_MsgHdr_t::errorCode field
#pragma pack(push)
#pragma pack(1)

enum
{
    ESSA_FP_ERRCODE_NOERROR            = 0,
    ESSA_FP_ERRCODE_FUNC_NOT_SUPPORTED = 1
};

typedef uint32_t funcIdType_t;

// FunctionProtocol header
typedef struct
{
    uint16_t     protoId;        // Protocol ID (from FIDL interface) - TODO: Need common header file for this!
    funcIdType_t funcId;        // Function Identifier (MS bit = 1 -> response; MS bit = 0 -> request)
    uint16_t     seqId;
    // enum type is not used here on purpose to ensure the...
    // ...field size is always one byte
    uint8_t      errCode;
} ESSA_Stack_FP_MsgHdr_t;

#pragma pack(pop)                // #pragma pack(1) - end of byte aligned structures

/**********************************************************************
 *
 *  Public methods declarations
 *
 **********************************************************************/
ESSA_eStack_codes_t ESSA_Stack_Init(const ESSA_Stack_Ctx_t * const pCfg);

// MAC driver callback upon message reception
void ESSA_Stack_DataDispatch(ESSATMAC_Context *pMACContext, uint8_t *pMsgData, uint8_t nMsgDataSize);

// Basic function to send message with normal priority and less parameters
ESSATMAC_ErrCodes ESSA_Stack_SendFrame(ESSASNetInterface nNetIntf,
                                       uint8_t nTargetAddress,
                                       uint8_t nPayloadProtocol,
                                       uint8_t *pMsgData,
                                       uint8_t nMsgDataSize);

// Function to send reply to request from other device
// Received message is (should be) dispatched with MAC context, so it will be easy to receive msg and reply to sender with this function
// Destination module address is set from sender in context
ESSATMAC_ErrCodes ESSA_Stack_SendFrameReply(ESSATMAC_Context *pMACContext,
                                            uint8_t *pMsgData,
                                            uint8_t nMsgDataSize,
                                            ESSATMAC_MsgPriority nMsgPriority);

// Extended function with all parameters
ESSATMAC_ErrCodes ESSA_Stack_SendFrameEx(ESSASNetInterface nNetIntf,
                                         ESSASNetType netType,
                                         uint8_t nTargetAddress,
                                         uint8_t nPayloadProtocol,
                                         uint8_t *pMsgData,
                                         uint8_t nMsgDataSize,
                                         ESSATMAC_MsgPriority nMsgPriority,
                                         ESSATMAC_DrvResult_Cbk_t pSendCallback,
                                         uint32_t *pMsgId);

ESSATMAC_ErrCodes ESSA_Stack_SendFrameEx_Bridge(ESSASNetInterface nNetIntf,
                                                ESSASNetType netType,
                                                uint8_t nSourceAddress,
                                                uint8_t nTargetAddress,
                                                uint8_t nPayloadProtocol,
                                                uint8_t *pMsgData,
                                                uint8_t nMsgDataSize,
                                                ESSATMAC_MsgPriority nMsgPriority,
                                                ESSATMAC_DrvResult_Cbk_t pSendCallback,
                                                uint32_t *pMsgId);

uint16_t ESSA_Stack_GetMTU(const ESSASNetType netType);

#endif // __ESSA_STACK_H__
