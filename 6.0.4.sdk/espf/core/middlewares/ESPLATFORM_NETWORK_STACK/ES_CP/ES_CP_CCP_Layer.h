#ifndef __ES_CP_CCP_LAYER_H__
#define __ES_CP_CCP_LAYER_H__

#include <stdint.h>

// SESCP_Hdr::nPreamble
// TODO: Use single source for all protocol preambles
#define SESCP_PREAMBLE						0x45632563

// SESCCP_Hdr::nProtoVersion
#define SESCP_PROTO_VERSION_HI				0x01		/* Incompatibility if different */
#define SESCP_PROTO_VERSION_LO				0x01		/* Fields may be added after header, compatibility preserved */

// SESCCP_Hdr::nProtoVersion
#define SESCCP_PROTO_VERSION_HI				0x02		/* Incompatibility if different */
#define SESCCP_PROTO_VERSION_LO				0x02		/* Fields may be added after header, compatibility preserved */

// SESCCP_Hdr::nTripType
#define SESCP_CTT_NO_RESPONSE				0x00		/* No response required/expected by GS */
#define SESCP_CTT_IMMEDIATE_RESPONSE		0x01		/* Immediate response through CP protocol required/expected by GS */
#define SESCP_CTT_POSTPONNED_RESPONSE		0x02		/* Command will not be executed immediately, and response will be polled by CCP protocol later on */


//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

typedef struct
{
	uint32_t nPreamble;			    // Used by SAT module. Used to validate start of packet = SESCP_PREAMBLE
	uint16_t nProtoVersion;		    // This structure version (not expected many iterations) = ((SESCP_PROTO_VERSION_HI << 8) | SESCP_PROTO_VERSION_LO)
	uint16_t nHeaderSize;		    // This header size
	uint64_t nFlags;			    // Currently unused (0)
	uint64_t nCmdID;			    // Used by GS, SAT module. Used to match partially send commands and request / response.
	uint32_t nCmdType;			    // Used by SAT module. Command type in "Payload" field : Specific Command..etc This is specific per module. Also used for versioning.
	uint8_t nTripType;			    // Communication trip type SESCP_CTT_...
	uint32_t nImmRespMaxBurstSize;  // If nTripType is SESCP_CTT_IMMEDIATE_RESPONSE, this will limit burst size, if not used set to 0xFFFFFFFF
	uint8_t nTLError;				// GUI, GS, SAT module. Response basic transport error if packet can't reach it's destination sat or module.

	// Payload
	// CRC32
} SESCP_Hdr;


// Each "Command Control Protocol" packet start with this structure
#define SESCCP_CTRL_NONE			0
#define SESCCP_CTRL_CANCEL			1		/* Request graceful cancellation of command, only header is sent, result is send through CP protocol as usual */
#define SESCCP_CTRL_GET_RESULT		2		/* Request to get result of command in header */

typedef struct
{
	uint32_t nPreamble;			// Used by SAT module. Used to validate start of packet = SESCP_PREAMBLE
	uint16_t nProtoVersion;		// This structure version (not expected many iterations) = ((SESCP_PROTO_VERSION_HI << 8) | SESCP_PROTO_VERSION_LO)
	uint16_t nHeaderSize;		// This header size
	uint64_t nCmdID;			// Command ID for which to get result
	uint32_t nCmdType;			// Used by SAT module. Command type in "Payload" field : Specific Command..etc This is specific per module. Also used for versioning.
	uint8_t nTLError;			// GUI, GS, SAT module. Response basic transport error if packet can't reach it's destination sat or module.

	uint16_t nCtrl;				// Command to be performed over CP command SESCCP_CTRL_...

	// Payload, depending of nCtrl
	// CRC32
} SESCCP_Hdr;

// Command to instruct module to return accumulated command result
// SESCCP_GetCMDResult::nDownLinkIntf
// Send over CCP layer
#define SESCCP_GCRDLI_REQUEST			0		/* Return through sender interface */

typedef struct
{
	SESCCP_Hdr hdr;				        // Keep first

	uint16_t nDownLinkIntf;		        // Down link interface SESCCP_GCRDLI_... now command results can be downloaded only through request interface of this command
	uint16_t nDownLinkMAC;		        // NOT USED, reserved for future implementations if needed

	uint32_t nResponseMaxBurstSize;		// Maximum burst transfer size
} SESCCP_GetCMDResult;

// Ensure we have spare for reception of bigger packets
#define SESCCP_MAX_INOUT_BUFF_RESERVED	(100)
#define SESCCP_MAX_INOUT_BUFF	((sizeof(SESCCP_GetCMDResult) + 4) + SESCCP_MAX_INOUT_BUFF_RESERVED)

#pragma pack(pop)
//////////////////////////////////////////////////////////////////////////////
// End fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////

#endif // __ES_CP_CCP_LAYER_H__
