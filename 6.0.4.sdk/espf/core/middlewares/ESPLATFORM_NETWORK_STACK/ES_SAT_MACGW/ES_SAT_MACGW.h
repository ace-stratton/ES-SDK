/*
*		Definition of ES UART232 - ES MAC layer dongle
*/

#ifndef __ES_SAT_MACGW_H__
#define __ES_SAT_MACGW_H__

#include <stdint.h>

// Escape protocol symbols
#define SESMACGW_MSG_ESC				0x20
#define SESMACGW_MSG_BEGIN				0x21
#define SESMACGW_MSG_END				0x22
#define SESMACGW_IS_ESC_CHAR(ch)				((ch >= SESMACGW_MSG_ESC) && (ch <= SESMACGW_MSG_END))

//////////////////////////////////////////////////////////////////////////////
// Errors used
//////////////////////////////////////////////////////////////////////////////
#define SESMACGW_ERR_SUCCESS							0
#define SESMACGW_ERR_BAD_REQ_PKT						1		/* bad request packet, crc else */
#define SESMACGW_ERR_ERROR								2
#define SESMACGW_ERR_NULL								3
#define SESMACGW_ERR_BUSY								4
#define SESMACGW_ERR_NO_MEM								5
#define SESMACGW_ERR_Q_FULL								6
#define SESMACGW_ERR_Q_NOT_EMPTY						7
#define SESMACGW_ERR_RETRY_COUNT_LIMIT					8
#define SESMACGW_ERR_SEND_TIMEOUT						9
#define SESMACGW_ERR_API_OFFLINE						10
#define SESMACGW_ERR_RECEIVE_TIMEOUT					11
#define SESMACGW_ERR_TX_COLLISION						12
#define SESMACGW_ERR_UNSUPPORTED_NET_TYPE				13
#define SESMACGW_ERR_INVALID_PARAMS						14
#define SESMACGW_ERR_BUS_BUSSY							15
#define SESMACGW_ERR_BAD_PARAMS							16		/* Incorrect parameters in request to dongle */
#define SESMACGW_ERR_TC_WAIT_PKT_TIMEOUT				17		/* TC : Remote party not reply */
#define SESMACGW_ERR_TC_WRONG_PKT_DATA					18		/* TC : Wrong MAC payload returned by DUT */
#define SESMACGW_ERR_TC_UNEXPECTED_RESPONSE				19		/* TC : Unexpected response from DUT */
#define SESMACGW_ERR_TC_CNTRS_ERR						20		/* TC : Error situation during test detected by driver! */
#define SESMACGW_ERR_TC_UNKNOWN_TC						21		/* TC : Unknown/Not supported test! */
#define SESMACGW_ERR_TC_COLLISION_STOP_ERR				22		/* TC : DUT Not stop after collision detected! */
#define SESMACGW_ERR_TC_IBT_ERR							23		/* TC : Receive inter-byte time violation detected! */
#define SESMACGW_ERR_TC_MSG_HIGH_PRIORITY_VIOLATION		24		/* TC : DUT does not follow priority timeouts for HIGH priority message response! */
#define SESMACGW_ERR_TC_MSG_NORMAL_PRIORITY_VIOLATION	25		/* TC : DUT does not follow priority timeouts for NORMAL priority message response! */
#define SESMACGW_ERR_TC_MSG_LOW_PRIORITY_VIOLATION		26		/* TC : DUT does not follow priority timeouts for LOW priority message response! */
#define SESMACGW_ERR_TC_MSG_RANDOMIZE_NOT_OK			27		/* TC : Random part of priority timeout of messages is not big enough! */
#define SESMACGW_ERR_TC_DE_ON_OFF_NOT_OK				28		/* TC : RS485 Driver enable not switch on/off within one byte time around transmission! */
#define SESMACGW_ERR_TC_DUT_LOOSES_PKTS					29		/* TC : DUT Loose some packets on heavy load! */
#define SESMACGW_ERR_TESTDEV_TIMEOUT					30		/* Test controller device not respond in time */

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

// SESMACGWHdr::u8Version
#define SESMACGW_VERSION				1

// SESMACGWHdr::nPreamble
#define SESMACGW_PREAMBLE				0x55

// SESMACGWHdr::nChannel
#define SESMACGW_CHANNEL_NONE				0
#define SESMACGW_CHANNEL_TUNNEL_OUT			1		/* Send (SESMACGWTunnel) packet from host to sat RS485 MAC, result is SESMACGWTunnelRes */
#define SESMACGW_CHANNEL_TUNNEL_IN			2		/* Packet received from RS485 MAC to host - SESMACGWTunnel */
#define SESMACGW_CHANNEL_CMD				3		/* Command channel from host to GW and back result */
#define SESMACGW_CHANNEL_ASYNC_ERRORS		4		/* Async errors send from GW device to host */
#define SESMACGW_CHANNEL_MAC_TC				5		/* Channel for performing test cases */
#define SESMACGW_CHANNEL_SERIAL_DATA 		6		/*Channel intended for creating serial tunnels between modules*/
#define SESMACGW_CHANNEL_BEACON 			7		/* Channel used to transfer beacon data to GroundStation  */
#define SESMACGW_CHANNEL_TUNNEL_OUT_HFC		8		/* Same as SESMACGW_CHANNEL_TUNNEL_OUT, but confirmation will be returned before message reach MAC network */

// Header of each packet, only append if needed, keep these in that order
typedef struct
{
	uint8_t u8Preamble;				// = SESMACGW_PREAMBLE
	uint8_t u8Version;				// = SESMACGW_VERSION
	uint8_t u8Channel;
} SESMACGWHdr;

// Footer of each packet
typedef struct
{
	uint16_t  u16CRC;			// MSP poly of all data + header above
} SESMACGWFooter;

// Header of each packet for SESMACGW_CHANNEL_TUNNEL
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	SESMACGWHdr Hdr;			// Keep first

	uint32_t  u32SeqNum;		// Used to match send request with send result, works only when sending packets and send confirm

	uint8_t nInterfaceNumber;	// enum ESSASNetInterface from ESSA_Stack.h
	uint8_t nSendBasePriority;	// Message priority in TQ - ESSASMP_CRITICAL, ESSASMP_HIGH, ESSASMP_NORMAL, ESSASMP_LOW from Stack.h

	uint8_t  u8TargetAddr;		// Target device or multicast/broadcast
	uint8_t  u8SourceAddr;
	uint8_t  u8Protocol;			
	uint8_t  u8DataSize;		// Size of Data

	uint8_t  Data[1];			// Keep last

} SESMACGWTunnel;

#define SESMACGWT_HEADER_SIZE	(sizeof(SESMACGWTunnel) - 1)
#define SESMACGWT_MAX_PKT_SIZE	((sizeof(SESMACGWTunnel) - 1) + 255 + sizeof(SESMACGWFooter))

// Response of sent packet
typedef struct
{
	SESMACGWHdr Hdr;			// Keep first
	uint32_t  u32SeqNum;		// Same as last send pkt
	uint8_t  u8Err;				// SESMACGW_ERR_...

} SESMACGWTunnelRes;


// Header of each packet for SESMACGW_CHANNEL_ASYNC_ERRORS
//////////////////////////////////////////////////////////////////////////

#define SESMACGWAE_MAX_CHARS	150

typedef struct
{
	SESMACGWHdr Hdr;			// Keep first
	char szErr[1];				// up to SESMACGWAE_MAX_CHARS (or so), zero terminated

} SESMACGWCmdAsyncError;

//////////////////////////////////////////////////////////////////////////
// SESMACGW_CHANNEL_MAC_TC
//////////////////////////////////////////////////////////////////////////

// Send to GW dongle and expect same result when test is completed with proper error
typedef struct
{
	SESMACGWHdr Hdr;			// Keep first

	uint8_t  nTargetMACAddr;	// Target device
	uint32_t nTCNum;			// Test case number to be performed
	uint32_t nSeqNum;			// Same as request
	uint8_t  nErr;				// SESMACGW_ERR_...

} SESMACGWTestCase;

#pragma pack(pop)

#endif		// #ifndef __ES_SAT_MACGW_H__

