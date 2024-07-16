/*
*		Definition of ES inter-SAT MAC layer structures
*/

#ifndef __ES_SAT_MAC_H__
#define __ES_SAT_MAC_H__

#include <stdint.h>
#include "ES_SAT_MAC_Context.h"

// Special MAC addresses
// For production use addresses above 0x10
#define ESSATMAC_ADDR_BROADCAST				((uint8_t) 0xFF)
#define ESSATMAC_ADDR_GATEWAY_DEV			((uint8_t) 0x01)
#define ESSATMAC_ADDR_UNINITIALIZED_DEV		((uint8_t) 0x02)		/* to be removed soon, uninitialized dev will have addr 0 */
#define ESSATMAC_ADDR_GATEWAY_EPSIIBP		((uint8_t) 0x03)		/* used for gateway through EPSII BP USB port */
#define ESSATMAC_ADDR_GATEWAY_EPSIIPDM		((uint8_t) 0x04)		/* used for gateway through EPSII PDM PC104 Uart */
#define ESSATMAC_ADDR_EXTERNAL_MAC_DONGLE	((uint8_t) 0x05)		/* to be used for external MAC dongle device */

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

#define ESSATMAC_MAX_DATA_SIZE            255

// Network lowest layer message, as it is serialized over network
// Old name RS485_RxTxMessage_t
typedef struct
{
	uint8_t  u8TargetAddr;		// For special addresses see above
	uint8_t  u8SourceAddr;
	uint8_t  u8Protocol;		// Defined in ES_SAT_MAC_Protocols.h : ES_SAT_MAC_PROTOCOL_ID_...
	uint8_t  u8DataSize;		// sizeof au8Data only, CRC is appended directly after size index
	uint16_t uHdrCRC16;			// CRC 16 of above fields - CRC-CCITT-BR (MSP430 cpu 16 bit CRC HW), send LSB first
	uint8_t  au8Data[ESSATMAC_MAX_DATA_SIZE];
	uint32_t u32CRC;            // CRC 32 of all message above, including header and it's CRC - CRC32-ISO3309 (MSP430 cpu 32 bit CRC HW), send LSB first
}  ESSATMAC_Message;

typedef ESSATMAC_ErrCodes (*fpDrvEnqMessage)(ESSATMAC_Context *pMACContext, uint8_t *pMsgData, uint8_t nMsgDataSize);

#define ESSATMAC_MAX_MSG_SIZE			sizeof(ESSATMAC_Message)
#define ESSATMAC_HEADER_SIZE			6
#define ESSATMAC_FOOTER_SIZE			4

#pragma pack(pop)				// #pragma pack(1) - end of byte aligned structures

// Following functions are required to be provided by MAC layer driver and BSP for each module
//////////////////////////////////////////////////////////////////////////

// Enqueue message to be sent
// void *pMACContext is supposed to identify target MAC interface (old param type pRS485_ctx_t, to be returned)
// ESSATMAC_EnqMessage to be removed in flavor of ESSATMAC_DrvEnqMessage
ESSATMAC_ErrCodes ESSATMAC_EnqMessage(void *pMACContext, uint32_t nMsgID, ESSATMAC_Message *fp_pMes, ESSATMAC_DrvResult_Cbk_t fp_Cbk);

// New function with proper context
// pMsgData - Message after MAC header
// Data pointed to by pMACContext and pMsgData shall be copied physically by the driver
ESSATMAC_ErrCodes ESSATMAC_DrvEnqMessage(ESSATMAC_Context *pMACContext, uint8_t *pMsgData, uint8_t nMsgDataSize);

// Should be implemented in each module
// Individual module MAC address should be stored in NVM memmory somewhere, device specific
uint8_t ESSATMAC_GetModuleAddr();

#endif		// #ifndef __ES_SAT_MAC_H__

