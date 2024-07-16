/* 
	This protocol should be part of ANY satellite module, that support our MAC network.
	Also it should be available in any mode of operation.
	This protocol should preserve backward and forward compatibility by processing only fields of each structure it understands or available.
	That is, we never change existing structures, just add new structure, that "inherit" old one, add new members and increment version.
	Versions are per structure, not per protocol. The only mandatory thing is protocol header stays as it is.
	If received structure is previous version, we use only available fields.
	If received structure is newer version, we use only fields that we understand.
	Send always newest version of structure.
*/


#ifndef __ESSA_SERVICEPROTOCOL_TYPES_H__
#define __ESSA_SERVICEPROTOCOL_TYPES_H__

#include <stdint.h>
#include "../include/ESSA_Stack.h"

#define ESSASP_DEV_SERIAL_MAX_SIZE							30

// Commands client ESSA_Discovery_Header::nCmd
#define ESSASP_CMD_REQUEST_NODE_INFO						1				/* + ESSASP_NetDiscoveryNodeReq - broadcast to all */
#define ESSASP_CMD_CONFIRM_NODE_INFO						2				/* + ESSASP_NetHeader */
#define ESSASP_CMD_REQUEST_RESTART							3				/* + ESSASP_NetRestartDev, no response expected */
#define ESSASP_CMD_REQUEST_SET_ADDR							4				/* + ESSASP_NetMACAddr */
#define ESSASP_CMD_REQUEST_SET_INITIAL_CONFIG				5				/* ESSASP_NetSetInitConfig */
#define ESSASP_CMD_REQUEST_PREPARE_SHIP_MODE				6				/* ESSASP_NetShipModeReq */
#define ESSASP_CMD_REQUEST_ENTER_SHIP_MODE					7				/* ESSASP_NetShipModeReq - no response expected, since module may enter deep sleep */
#define ESSASP_CMD_REQUEST_GSCP_CMD_INFO					8				/* + ESSASP_NetHeader as broadcast */
#define ESSASP_CMD_CONFIRM_GSCP_CMD_INFO					9				/* + ESSASP_NetHeader */

// Commands server ESSA_Discovery_Header::nCmd
#define ESSASP_CMD_RESPONSE_NODEINFO						(125 + 1)		/* + ESSASP_NetDiscoveryNodeInfo */
#define ESSASP_CMD_ANNOUNCE_NODEINFO						(125 + 2)		/* + ESSASP_NetDiscoveryNodeInfo */
#define ESSASP_CMD_RESPONSE_SET_ADDR						(125 + 3)		/* + ESSASP_NetMACAddr */
#define ESSASP_CMD_RESPONSE_SET_INITIAL_CONFIG				(125 + 4)		/* ESSASP_NetSetInitConfig */
#define ESSASP_CMD_RESPONSE_PREPARE_SHIP_MODE				(125 + 5)		/* ESSASP_NetHeader */
#define ESSASP_CMD_RESPONSE_ENTER_SHIP_MODE_ERROR			(125 + 6)		/* + ESSASP_NetHeader */
#define ESSASP_CMD_RESPONSE_GSCP_CMD_INFO					(125 + 7)		/* + ESSASP_NetGS_CP_CmdInfo */

// Error codes
// UPDATE also ESSASP_GetNetErrAsString
typedef enum
{
	ESSASPNE_SUCCESS = 0,
	ESSASPNE_GENERAL_ERROR,
	ESSASPNE_SC_BUSY,								/* Dev : Service protocol busy and can't execute command at the moment */
	ESSASPNE_NOT_IMPLEMENTED,						/* Dev : Command not implemented */
	ESSASPNE_BAD_PARAMS,							/* Dev : Command with bad params received */
	ESSASPNE_TIMEOUT,								/* Dev : Command timeout, device(s) not respond */
	ESSASPNE_MAC_SEND_ERROR,						/* Dev : Unable to send MAC packet */
	ESSASPNE_BOOTLOADERS_NOT_HEALTHY,				/* Dev : Bootloaders not set/healthy */
	ESSASPNE_NVM_NOT_HEALTHY,						/* Dev : NVM memory not healthy */
	ESSASPNE_APPS_NOT_HEALTHY,						/* Dev : Application (main or failsafe or else) not healthy */
	ESSASPNE_CHIP_CONFIGURATION_NOT_SET,			/* Dev : Some chip configuration not set */
	ESSASPNE_INVALID_APP_INSTALLED,					/* Dev : Failsafe or other test app installed, not for flight! */
	ESSASPNE_DEVICE_CONFIGURATION_NOT_SET,			/* Dev : Some device configuration not set */
	ESSASPNE_APP_SERIAL_PORT_IN_USE,				/* App : Serial port in use! */
	ESSASPNE_APP_CANNOT_OPEN_SERIAL_PORT,			/* App : Can't open serial port! */
	ESSASPNE_APP_CANNOT_SEND_TO_SERIAL_PORT,		/* App : Can't sent to serial port! */
	ESSASPNE_APP_SEND_TO_SERIAL_PORT_TIMEOUT,		/* App : Msg sent timeout! */
	ESSASPNE_APP_INVALID_ANSWER_PAYLOAD_COMMAND,	/* App : Invalid answer payload! */
	ESSASPNE_APP_INVALID_ANSWER_PAYLOAD_SIZE,		/* App : Invalid answer payload size! */
	ESSASPNE_APP_INVALID_ANSWER_PAYLOAD_SEQID,		/* App : Invalid answer payload pkt sequence ID! */
	ESSASPNE_APP_SN_TOO_LONG,						/* App : Serial number too long! */

} ESSASP_NetError;

typedef enum
{
	ESSASP_OM_UNKNOWN = 0,
	ESSASP_OM_NORMAL = 1,
	ESSASP_OM_FAILSAFE = 2,
} ESSASP_OperationalMode;

//////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

//////////////////////////////////////////////////////////////////////////
// Header of ES_SAT_MAC_PROTOCOL_ID_SERVICE MAC Protocol
//////////////////////////////////////////////////////////////////////////
// Do not populate from client callbacks
typedef struct 
{
	uint16_t nVer;						// = 1 for now. Version of following structure, keep first. Later, we must have version for each structure.
	uint8_t  nCmd;						// ESSASP_CMD_...
	uint32_t nSeqID;					// Distinguish request/response
	uint8_t  nResultCode;				// ESSASP_NetError

} ESSASP_NetHeader;

// To be copied with memcpy
typedef struct 
{
	uint32_t nMsgID;
	uint8_t nSourceAddr;				// Sender device address
	ESSASNetInterface nPhyIntf;

} ESSASP_ReplyContext;

//////////////////////////////////////////////////////////////////////////
// Manipulation of device MAC addr
//////////////////////////////////////////////////////////////////////////

#define ESSASP_MAC_ADDR_SIGNATURE		0x45AD740FA5FFAA55

typedef struct 
{
	ESSASP_NetHeader Hdr;				// Keep first, do not populate from app callbacks

	uint64_t nSignature;				// = ESSASP_MAC_ADDR_SIGNATURE
	char szModuleSerial[ESSASP_DEV_SERIAL_MAX_SIZE];
	uint8_t nMACAddr;
} ESSASP_NetMACAddr;

//////////////////////////////////////////////////////////////////////////
// Restart device
//////////////////////////////////////////////////////////////////////////

#define ESSASP_RST_SIGNATURE		0x464FD4DA66FF6105

typedef struct 
{
	ESSASP_NetHeader Hdr;				// Keep first, do not populate from app callbacks

	uint64_t nSignature;				// = ESSASP_RST_SIGNATURE
	uint8_t nInMode;					// In what mode to restart, ESSASP_OperationalMode or 0 if just restart without switch of modes
} ESSASP_NetRestartDev;

//////////////////////////////////////////////////////////////////////////
// Ship mode
//////////////////////////////////////////////////////////////////////////

#define ESSASP_SHP_SIGNATURE		0x687648F3A7F2BBC5

typedef struct 
{
	ESSASP_NetHeader Hdr;				// Keep first, do not populate from app callbacks

	uint64_t nSignature;				// = ESSASP_SHP_SIGNATURE

} ESSASP_NetShipModeReq;

//////////////////////////////////////////////////////////////////////////
// Query Device information
//////////////////////////////////////////////////////////////////////////

// Bitmask flags
#define ESSASP_DPF_NONE						0
#define ESSASP_DPF_MASTER_DEV				1				/* Master device in redundancy configuration */

// Request to poll for device info
typedef struct 
{
	ESSASP_NetHeader Hdr;								// Keep first, do not populate from app callbacks

	uint8_t nOpModeFilter;								// Filter devices by ESSASP_OperationalMode or 0 if all devices should be queried
	uint16_t nDevTypeFilter;							// Filter devices by type, defined in ESPLATFORM_COMMON\ESSAT_ModuleTypes.h or 0 if all devices should be queried
	uint16_t nFlags;									// ESSASP_DPF_...

} ESSASP_NetDiscoveryNodeReq;

// Response to ESSA_DiscoveryNodeReq or send async on network to announce device mode change or restart etc
typedef struct 
{
	ESSASP_NetHeader Hdr;								// Keep first, do not populate from app callbacks

    uint16_t nModuleType;								// or DevName. From ESPLATFORM_COMMON\ESSAT_ModuleTypes.h
	uint64_t nModuleHWConfig;							// Device specific, use 0 if not used
	uint16_t nModuleHWRevision;							// Device specific, use 0 if not used
	char szModuleSerial[ESSASP_DEV_SERIAL_MAX_SIZE];
	uint8_t nOperationalMode;							// ESSASP_OperationalMode
	uint8_t nMACAddr;									// Current one, may be 0 if not set
	uint16_t nModuleFWVariant;							// or Type. Firmware type if normal mode of operation. Device specific, use 0 if not used
	uint16_t nFWVersionMaj;
	uint16_t nFWVersionMin;
	uint16_t nFlags;									// ESSASP_DPF_...

} ESSASP_NetDiscoveryNodeInfo;

//////////////////////////////////////////////////////////////////////////
// Get GS command info
//////////////////////////////////////////////////////////////////////////

typedef enum
{
	ESSASP_CCPCS_NONE = 0,								/* No command, module is free to receive other commands */
	ESSASP_CCPCS_UPLOADING,								/* Command is currently uploading and may be resumed */
	ESSASP_CCPCS_WAIT_EXEC,								/* Command is now waiting for execution */
	ESSASP_CCPCS_DOWNLOADING,							/* Command is executed and wait to be downloaded (or start downloading, same thing) */
} ESSASP_NetCCPCmdStatus;

typedef struct 
{
	ESSASP_NetHeader Hdr;								// Keep first, do not populate from app callbacks

	uint8_t nMACAddr;									// Current one, set by protocol handler, may not be correct on network
	uint64_t nCP_CmdID;									// 0 if none at the moment
	uint8_t nCP_CmdStatus;								// Status of nCP_CmdID command - ESSASP_NetCCPCmdStatus

} ESSASP_NetGS_CP_CmdInfo;

//////////////////////////////////////////////////////////////////////////
// Set device initial config
//////////////////////////////////////////////////////////////////////////
#define ESSASP_DEV_INIT_SIGNATURE		0x65FA4DF672305DD5

typedef struct 
{
	ESSASP_NetHeader Hdr;								// Keep first, do not populate from app callbacks

	uint64_t nSignature;								// = ESSASP_DEV_INIT_SIGNATURE

	uint16_t nModuleType;								// or DevName. From ESPLATFORM_COMMON\ESSAT_ModuleTypes.h
	uint64_t nModuleHWConfig;							// Device specific, use 0 if not used
	uint16_t nModuleHWRevision;							// Device specific, use 0 if not used
	char szModuleSerial[ESSASP_DEV_SERIAL_MAX_SIZE];

} ESSASP_NetSetInitConfig;

//////////////////////////////////////////////////////////////////////////
// End of packet structures
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif  // __ESSA_SERVICEPROTOCOL_TYPES_H__
