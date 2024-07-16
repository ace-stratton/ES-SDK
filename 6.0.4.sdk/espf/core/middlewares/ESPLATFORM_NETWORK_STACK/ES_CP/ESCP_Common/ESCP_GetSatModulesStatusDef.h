#ifndef __ESCP_GETSATMODULESSTATUSDEF_H__
#define __ESCP_GETSATMODULESSTATUSDEF_H__

/*
	Workflow of CP commands is to create new command on each change
	TripType = SESCP_CTT_IMMEDIATE_RESPONSE
*/

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

// CP Command request
typedef struct
{
}  ESCP_GetSatModulesStatusReq;

// ESCP_GetSatModulesStatusNodeInfo::nOperationalMode
typedef enum
{
	ESCPOM_OM_UNKNOWN = 0,
	ESCPOM_OM_NORMAL,
	ESCPOM_OM_FAILSAFE
} ESCPGSMSOperationMode;

typedef struct 
{
	uint8_t nMACAddr;									// Current one, may be 0 if not set
	uint8_t nNetInterface;								// Internal MAC interface (ESSASNetInterface)
	uint16_t nModuleType;								// or DevName. From ESPLATFORM_COMMON\ESSAT_ModuleTypes.h
	uint64_t nModuleHWConfig;							// Device specific, use 0 if not used
	uint16_t nModuleHWRevision;							// Device specific, use 0 if not used
	uint8_t nOperationalMode;							// ESCPGSMSOperationMode
	uint16_t nModuleFWVariant;							// or Type. Firmware type if normal mode of operation. Device specific, use 0 if not used
	uint16_t nFWVersionMaj;
	uint16_t nFWVersionMin;
	uint16_t nFlags;									// TBD

} ESCP_GetSatModulesStatusNodeInfo;

typedef enum
{
	ESCPGSMSRE_SUCCESS = 0,
	ESCPGSMSRE_GENERAL_ERROR,
	ESCPGSMSRE_SC_BUSY,					/* Service protocol busy and can't execute command at the moment */
	ESCPGSMSRE_NOT_IMPLEMENTED,			/* Command not implemented */
	ESCPGSMSRE_BAD_PARAMS,				/* Command with bad params received */
	ESCPGSMSRE_TIMEOUT,					/* Command timeout, device(s) not respond */
	ESCPGSMSRE_MAC_SEND_ERROR,			/* Unable to send MAC packet */
	ESCPGSMSRE_RES_OUT_OF_MEM,			/* Unable to fit all data into supplied CP result buffer */

} ESCPGSMSRError;

// CP Command response
typedef struct
{
	uint16_t nConOpsID;									// ID of current sat con ops mode

	uint8_t nErr;										// ESCPGSMSRError : If request not properly executed, but still some data are returned
	uint16_t nNodesInfoCount;							// Count in nNodesInfo
	ESCP_GetSatModulesStatusNodeInfo nNodesInfo[1];

}  ESCP_GetSatModulesStatusResp;

#define ESCP_GSMSR_HDR_SIZE		(sizeof(ESCP_GetSatModulesStatusResp) - sizeof(ESCP_GetSatModulesStatusNodeInfo))

#pragma pack(pop)				// #pragma pack(1) - end of byte aligned structures

#endif		// #ifndef __ESCP_GETSATMODULESSTATUSDEF_H__

