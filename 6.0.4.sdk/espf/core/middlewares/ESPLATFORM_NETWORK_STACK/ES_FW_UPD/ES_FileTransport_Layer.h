#ifndef __ES_FILE_TRANSPORT_LAYER_H__
#define __ES_FILE_TRANSPORT_LAYER_H__

#include <stdint.h>

// SESFileTransport_Hdr::nPreamble
#define SEFTL_PREAMBLE						0xABCDEF01

// SESFileTransport_Hdr::nProtoVersion
#define SEFTL_PROTO_VER						1

// SESFileTransport_Hdr::nFlags - bitmask
#define SEFTL_FL_NONE						0x0000

// SESFileTransport_Hdr::nPayloadType
#define SEFTL_PLT_NONE						0
#define SEFTL_PLT_UPDATE					1 /* Payload header is SESSoftwareUPD_Hdr */
#define SEFTL_PLT_COMMAND					2 /* Payload header is SESCP_Hdr */
#define SEFTL_PLT_CMD_CONTROL			3 /* Payload header is SESCCP_Hdr */
#define SEFTL_PLT_HANDSHAKE				4

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

typedef struct
{
	uint32_t nPreamble;			// SEFTL_PREAMBLE, Used by SAT module. Used to validate start of packet = SESCP_PREAMBLE
	uint16_t nProtoVersion;		// SEFTL_PROTO_VER, Used by GS, SAT module. This structure version (not expected many iterations)
	uint32_t nPacketSize;		// Used by GS, SAT module. This is whole packet size, including CRC field. Take special care not to use this field without checking CRC first (i.e.in segmentation receive logic)
	uint64_t nSatID;			// Generated and set by GS on packet queue
	uint8_t nModuleMAC;			// These should be known by GS server andapp that will generate this packet. These addresses are pre - launch configured.
	uint64_t nCmdID;			// Used by GS, SAT module. Used to match partially send commands and request / response.
	uint8_t nPayloadType;		// Encapsulated payload header SEFTL_PLT_...
	uint64_t nFlags;			// Additional information for payload like if compressed / encrypted etc. SEFTL_FL_...
	uint8_t nPriority;			// Priority of the given commnad.
	uint8_t nTLError;			// Response basic transport error if packet can't reach it's destination sat or module.
	uint32_t nHdrCRC;			// CRC of this header, payload after that also have CRC32 at the end
} SESFileTransport_Hdr;

//   {
//     "ClassType": "SESFileTransport_Hdr"
//     "nPreamble": 0xABCDEF01,
//     "nProtoVersion": 1,
//     "nPacketSize": 51,
//     "nSatID": 27,
//     "nModuleMAC": 52,
//     "nCmdID": 35,
//     "nPayloadType": "SEFTL_PLT_COMMAND",
//     "nFlags": 0,
//     "nPriority": 1,
//     "nTLError": 0,
//     "nHdrCRC": 2535,
//     {
//       "ClassType": "SESCP_Hdr",
//       "nPreamble": 0x45632563,
//       "nProtoVersion": 1,
//       "nHeaderSize": 20,
//       "nFlags": 0,
//       "nCmdID": 35,
//       "nCmdType": 1,
//       "nTripType": "SESCP_CTT_POSTPONNED_RESPONSE",
//       "nImmRespMaxBurstSize": 0,
//     }
//     "Payload": [1, 23, 45, 66, 77, 33]
//   }
  

typedef struct
{
  uint64_t nCmdID;			// Used by GS, SAT module. Used to match partially send commands and request / response.
  uint8_t  u8DataSize;		// Size of Data
  uint8_t nTLError;			// Response basic transport error if packet can't reach it's destination sat or module.
  uint8_t  Data[255];			// MAX 255
  uint16_t nDataCRC;			// CRC of this header, payload after that also have CRC32 at the end
} SESFileResponse_Hdr;
#pragma pack(pop)
//////////////////////////////////////////////////////////////////////////////
// End fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////

#endif // __ES_FILE_TRANSPORT_LAYER_H__

