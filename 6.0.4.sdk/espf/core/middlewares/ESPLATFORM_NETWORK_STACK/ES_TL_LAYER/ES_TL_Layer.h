#ifndef __ES_TL_LAYER_H__
#define __ES_TL_LAYER_H__

#include <stdint.h>
#include <stdbool.h>

// TODO: Use common repository for these
// Scrambled for tests
// SESTL_Hdr::nTLHostProtocolID
#define EESTL_HP_UNKNOWN					0
#define EESTL_HP_CP							10					/* Command protocol */
#define EESTL_HP_CCP						12					/* Command control protocol */
#define EESTL_HP_FW_UPDATE					14					/* Firmware Update Protocol */
#define EESTL_HP_HANDSHAKE					16					/* Handshake Protocol */
#define EESTL_HP_BEEKON						18					/* Beacon */


// SESTL_Hdr::nTLFrameType
#define EESTL_FT_UNKNOWN					0
#define EESTL_FT_DATA_FRAME					10					/* Actual payload data transfer frame */
#define EESTL_FT_SYNC_FRAME					20					/* Flush all buffers throughout communication chain */
#define EESTL_FT_STATUS_FRAME				30					/* ES Transport Layer */

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

// Each TransportLayer packet start with this structure
typedef struct
{
	uint64_t nTLPacketID;			// Target device address or multicast/broadcast address
	uint8_t nTLHostProtocolID;	    // Destination should be able to receive different nPayloadProtocolID in different buffers, thus process them simultaneously if needed
	uint8_t nTLFrameType;			// determine next fields EESTL_FT_...
} SESTL_Hdr;

// For SESTL_Hdr::nTLFrameType == EESTL_FT_DATA_FRAME
typedef struct
{
	SESTL_Hdr Hdr;				// Keep first

	uint32_t nPayloadAddress;	// Start address of payload in this frame
	uint8_t Payload[1];			// Size depends from MAC layer size field
}SESTL_DataFrame;

#define TL_GET_SIZE_OF_HDR_DATA_FRAME()	(sizeof(SESTL_DataFrame) - 1)

// For SESTL_Hdr::nTLFrameType == EESTL_FT_SYNC_FRAME
// Send from "sender" side, to flush all burst transfers & get received status
// SESTL_SyncFrame::nTargetSystem
#define SESTLSF_TS_LOCAL			0			/* Packet is intended for local satellite/system, destination module is determined by MAC address, nTargetSystemAddress = 0 */
#define SESTLSF_TS_GS				1			/* Packet is intended for ground station, destination MAC address is 0 and nTargetSystemAddress is 0 */
#define SESTLSF_TS_SAT				2			/* Packet is intended for satellite, nTargetSystemAddress is SatID, nTargetLocalAddress is module MAC address */

typedef struct
{
	SESTL_Hdr Hdr;					// Keep first

	uint64_t nTLHostContext;		// Host protocol specific

	uint16_t nTargetSystemType;		// This is intended target system, helps route packets inside "router" modules
	uint64_t nTargetSystemAddress;	// This depends from type of destination, i.e. nTargetSystemType
	uint64_t nTargetLocalAddress;	// This depends from type of destination, i.e. nTargetSystemType, put MAC address 

	uint32_t nWholePacketSize;		// Upper level whole payload packet size
} SESTL_SyncFrame;

#define TL_GET_SIZE_OF_SYNC_FRAME()	sizeof(SESTL_SyncFrame)

// For SESTL_Hdr::nTLFrameType == EESTL_FT_STATUS_FRAME
// Send from "receiver" side in response to SESTL_SyncFrame

// SESTL_StatusFrame::nTLReceiverError
#define EESTL_SFERR_SUCCESS						0
	// Recoverable errors, should be repeated next time SAT is in contact (with reasonable repeat counter & progress monitoring)
#define EESTL_SFERR_BUFFER_BUSY					1		/* Device buffer busy with previous transfer */
#define EESTL_SFERR_SEND_TIMEOUT				2		/* Somewhere on the chain, confirmation is not received in time (many times). This is recoverable error! */
#define EESTL_SFERR_SYNC_HS_BROKEN				3		/* Sync handshake broken - sender does not received what is expected */
#define EESTL_SFERR_SEND_MAC_TIMEOUT			4		/* Somewhere on the chain, MAC layer is unresponsive or network is too busy */
#define EESTL_SFERR_CMD_PENDING					5		/* Command still pending for execution */
#define EESTL_SFERR_RECEIVE_TIMEOUT				6		/* Receive CMD result from GS timeout */
#define EESTL_SFERR_BAD_CMD_CRC					7		/* Bad CRC of CP protocol */
#define EESTL_SFERR_CANNOT_START_AIR_SESSION	8		/* Error sending ESSATAIRMAC_InitHandshake command to UHF */
#define EESTL_SFERR_SAT_TRACKING_STOPPED		9		/* Satellite tracking has been stopped */
#define EESTL_SFERR_TRANSCEIVER_IS_BUSY			10		/* GS Transceiver is busy, e.g. processing other command at the moment */

#define EESTL_SFERR_RECOVERABLE_MARGIN			100		/* If returned error is less than this, it is recoverable */

	// Unrecoverable errors
#define EESTL_SFERR_SIZE_MISMATCH				101		/* Some error related to size of received/send packet */
#define EESTL_SFERR_PROTO_NOT_SUPP				102		/* Protocol above TL is not supported */
#define EESTL_SFERR_IO_ERROR					103		/* Storage device (sender or receiver) is corrupted/not responsive */
#define EESTL_SFERR_BAD_PARAMS					104		/* Incorrect parameters detected */
#define EESTL_SFERR_BAD_CMD						105		/* Incorrectly formatted CMD, bad CRC, length or else */
#define EESTL_SFERR_BAD_CMD_PARAMS				106		/* Bad params in CP/CCP protocol header */
#define EESTL_SFERR_CMD_NOT_SUPP				107		/* Command not supported */
#define EESTL_SFERR_UNKNOWN_CMD_ID				108		/* Unknown Command/ not what expected */
#define EESTL_SFERR_FREE_CMD					109		/* Module does not execute any command at the moment */
#define EESTL_SFERR_CMD_CANCELLED				110		/* Command cancelled by GS */
#define EESTL_SFERR_UNKNOWN						111		/* Unknown error in underlying layers */
#define EESTL_SFERR_BAD_FRM_FORMAT				112		/* Bad frame format received */
#define EESTL_SFERR_BAD_FRM_FORMAT_G			113		/* Bad frame format received in gateway module */
#define EESTL_SFERR_OUT_OF_MEM					114		/* Out of memory on target device */
#define EESTL_SFERR_OVERFLOW					115		/* Received packet size is more than module can handle */
#define EESTL_SFERR_CANNOT_LOAD_UPD_BUNDLE		116		/* Error loading application update bundle */

#define EESTL_SFERR_DIFFERENT_MAC_ADDRESS		117		/* Packet with different MAC address is received */

#define EESTL_SFERR_MODULE_NOT_OPERATIONAL		118		/* Module that trying to send to is not operational */

typedef struct
{
	SESTL_Hdr Hdr;					    // Keep first

	uint32_t nReceivedPacketSize;		// Successfully sequential data received from 0 so far
	uint32_t nMaxBurstSize;			    // Smallest size for buffer on entire communication chain, that can receive burst payload data
	uint32_t nAIR_SuccessBurstData;	    // Successfully transmitted data in one burst transfer over the air

	uint8_t nTLReceiverError;			// If unrecoverable receiver error during last/first chunk transfer occurred. Current transmission is aborted (may repeat from upper layer later on)
} SESTL_StatusFrame;

#define TL_SIZE_OF_STATUS_FRAME	sizeof(SESTL_StatusFrame)

#pragma pack(pop)
//////////////////////////////////////////////////////////////////////////////
// End fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////

#endif // __ES_TL_LAYER_H__

