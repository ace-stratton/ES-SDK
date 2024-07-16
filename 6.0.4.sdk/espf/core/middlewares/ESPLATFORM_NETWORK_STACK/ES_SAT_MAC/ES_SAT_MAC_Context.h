/*
*		Definition of ES inter-SAT MAC layer context, used between MAC driver and Stack driver
*/

#ifndef __ES_SAT_MAC_CONTEXT_H__
#define __ES_SAT_MAC_CONTEXT_H__

#include <stdint.h>
#include "ESSA_StackConfigTypes.h"

#pragma pack(push)
#pragma pack(1)

typedef enum
{
	ESSATMAC_EC_OK = 0,
	ESSATMAC_EC_ERROR,
	ESSATMAC_EC_NULL,
	ESSATMAC_EC_BUSY,
	ESSATMAC_EC_NO_MEM,
	ESSATMAC_EC_Q_FULL,
	ESSATMAC_EC_Q_NOT_EMPTY,
	ESSATMAC_EC_RETRY_COUNT_LIMIT,
	ESSATMAC_EC_TX_COLLISION,			// Collision while try to transmit (several times)
	ESSATMAC_EC_UNSUPPORTED_NET_TYPE,
	ESSATMAC_EC_INVALID_PARAMS,
	ESSATMAC_EC_BUS_BUSSY,				// BUS is busy (all retries) and we can't transmit message
} ESSATMAC_ErrCodes;

// Callback function to inform sender for enqueued message
typedef void (*ESSATMAC_DrvResult_Cbk_t)(uint32_t nMsgID, ESSATMAC_ErrCodes fp_eReturnCode);

// Manipulated with memcpy & memset in code
typedef struct
{
	// Base fields, relevant to both send and receive
	uint8_t nInterfaceNumber;						// zero based integer, mapped to physically available RS485 MAC channels (came from stack, above stack should be with some enums, we may want to configure these in future)
	ESSASNetType netType;                           // identifies the MAC network bus type, e.g. internal, air, etc.
	uint8_t nPayloadProtocol;						// Protocol above MAC layer, defined in ES_SAT_MAC_Protocols.h
	uint8_t nTargetAddr;							// Target device address or multicast/broadcast address

	// Receive related fields
	uint8_t nSourceAddr;							// Sender device address, when message is received

	// Send related fields
	uint8_t nSendBasePriority;						// Min / initial priority integer in TQ - must be set from "Stack" based on some predefined enums (pre-launch configurable)
	uint32_t nMsgID;								// Number to identify messages when callback of send success or failure (generated in stack to be unique, returned to app layer)
	ESSATMAC_DrvResult_Cbk_t pSendCallback;			// Callback to be called when message is sent or not, may be NULL if not interested

} ESSATMAC_Context;
#pragma pack(pop)
#endif		// #ifndef __ES_SAT_MAC_CONTEXT_H__

