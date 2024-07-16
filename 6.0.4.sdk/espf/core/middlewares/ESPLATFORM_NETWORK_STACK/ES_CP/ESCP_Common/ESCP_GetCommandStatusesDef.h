#ifndef __ESCP_GETCOMMANDSTATUSESDEF_H__
#define __ESCP_GETCOMMANDSTATUSESDEF_H__

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
}  ESCP_GetCommandStatusesReq;


// ESCP_CP_CmdInfo::nCP_CmdStatus
typedef enum
{
	ESCP_CCPCS_NONE = 0,					/* No command, module is free to receive other commands */
	ESCP_CCPCS_UPLOADING,					/* Command is currently uploading and may be resumed */
	ESCP_CCPCS_WAIT_EXEC,					/* Command is now waiting for execution */
	ESCP_CCPCS_DOWNLOADING,					/* Command is executed and wait to be downloaded (or start downloading, same thing) */
	ESCP_CCPCS_ERR							/* Some unexpected state result */

} ESCPGSGCCCmdStat;

// ESCP_GetCommandStatusesResp::nErr
typedef enum
{
	ESCPGSGCCE_SUCCESS = 0,
	ESCPGSGCCE_GENERAL_ERROR,
	ESCPGSGCCE_SC_BUSY,						/* Service protocol busy and can't execute command at the moment */
	ESCPGSGCCE_NOT_IMPLEMENTED,				/* Command not implemented */
	ESCPGSGCCE_BAD_PARAMS,					/* Command with bad params received */
	ESCPGSGCCE_TIMEOUT,						/* Command timeout, device(s) not respond */
	ESCPGSGCCE_MAC_SEND_ERROR,				/* Unable to send MAC packet */
	ESCPGSGCCE_RES_OUT_OF_MEM,				/* Unable to fit all data into supplied CP result buffer */

} ESCPGSGCCError;

typedef struct 
{
	uint8_t nMACAddr;						// Device ID
	uint8_t nNetInterface;					// Internal MAC interface (ESSASNetInterface)
	uint64_t nCP_CmdID;						// 0 if none at the moment
	uint8_t nCP_CmdStatus;					// Status of nCP_CmdID command - ESCPGSGCCCmdStat

} ESCP_CP_CmdInfo;

// CP Command response
typedef struct
{
	uint8_t nErr;							// ESCPGSGCCError, if request not properly executed, still some records may have info
	uint16_t nNodesInfoCount;				// Count in nNodesInfo
	ESCP_CP_CmdInfo nNodesInfo[1];

}  ESCP_GetCommandStatusesResp;

#define ESCP_GSGCSR_HDR_SIZE	(sizeof(ESCP_GetCommandStatusesResp) - sizeof(ESCP_CP_CmdInfo))


#pragma pack(pop)				// #pragma pack(1) - end of byte aligned structures

#endif		// #ifndef __ESCP_GETCOMMANDSTATUSESDEF_H__

