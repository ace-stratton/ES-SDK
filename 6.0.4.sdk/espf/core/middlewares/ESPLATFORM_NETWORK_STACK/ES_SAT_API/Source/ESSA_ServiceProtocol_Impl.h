#ifndef _ESSA_SERVICEPROTOCOL_IMPL_H_
#define _ESSA_SERVICEPROTOCOL_IMPL_H_

#include <stdint.h>

#include "ESSA_StackConfig.h"
#include "../include/ESSA_Stack.h"
#include "../include/ESSA_ServiceProtocol_Types.h"

// TODO: remove these
//#define ESSASP_SUPPORT_DISCOVERY_CLIENT
//#define ESSASP_SUPPORT_SET_REMOTE_DEVICE_MAC_ADDR

//////////////////////////////////////////////////////////////////////////
// Callback functions that may need to be provided by main code
//////////////////////////////////////////////////////////////////////////

// Set module initial config, this should be able to execute only once, after JTAG programming
// We set initial configuration while device is alone in the network, connected to one dongle
extern ESSASP_NetError ESSASP_CB_SetInitConfig(ESSASP_NetSetInitConfig *pInitConfig);

// Restart module
extern void ESSASP_CB_RestartDev(ESSASP_OperationalMode nInMode);				// if nInMode == 0, just restart, no change in mode

// Set MAC Addr request
extern ESSASP_NetError ESSASP_CB_OnSetMACAddr(uint8_t nNewMacAddr);

// Ship mode
extern void ESSASP_CB_PrepareShipMode(ESSASP_ReplyContext *pRC);						// Expected result is send async (no timeout in host) via ESSASP_PrepareShipModeComplete with same params
extern void ESSASP_CB_EnterShipMode(ESSASP_ReplyContext *pRC);						// This is handled usually by power supply(s) to cut power to sat and enter ship mode, no result expected, but error may be returned within 5 seconds with ESSASP_EnterShipModeError

// Discovery - client
// Give ability to dynamically enumerate devices on network
// ESSASP_SUPPORT_DISCOVERY_CLIENT
extern void ESSASP_CB_OnAsyncNodeInfo(ESSASP_NetDiscoveryNodeInfo *pNodeInfo, ESSASNetInterface nPhyIntf);		// Node may send occasional broadcast with its parameters in case it is restarted or mode of operation was changed etc.
extern void ESSASP_CB_OnNodeInfo(ESSASP_NetDiscoveryNodeInfo *pNodeInfo, ESSASNetInterface nPhyIntf);			// Node info received in response to explicit call to ESSASP_StartDiscover
extern void ESSASP_CB_OnDiscoveryFinished(ESSASP_NetError nStatus, ESSASNetInterface nPhyIntf);					// Usually called within few seconds (max ~5) after ESSASP_StartDiscover was called

// Discovery - server
// Give ability for this node to be discovered dynamically on network
// Called in response to network request to get our info or ESSASP_SendAnnounce() is called by app layer or else
extern void ESSASP_CB_GetDeviceInfo(ESSASP_NetDiscoveryNodeInfo *pNodeInfo);	

// GSCmdStatus - client
// Give ability to collect status of commands issued by GS
// Usually needed by communication module
#ifdef ESSASP_SUPPORT_GS_CMD_CLIENT
extern void ESSASP_CB_OnGSCmdStatus(ESSASP_NetGS_CP_CmdInfo *pCmdInfo, ESSASNetInterface nPhyIntf);				// Command status received from some module
extern void ESSASP_CB_OnGSCmdStatusFinished(ESSASP_NetError nStatus, ESSASNetInterface nPhyIntf);				// Usually called within few seconds (max ~5) after ESSASP_StartCollectGSCmdStatus was called
#endif

// If this device have ability to set MAC address of other device
#ifdef ESSASP_SUPPORT_SET_REMOTE_DEVICE_MAC_ADDR
// Called for each successfull call to ESSASP_SetRemoteDevMACAddr
extern void ESSASP_CB_OnSetRemoteDevMACFinished(ESSASP_NetError nStatus);
#endif

// GSCmdStatus - server
// Give ability to report command status, executed by GS
// If your module support GS commands, it need this
#ifdef ESSASP_SUPPORT_GS_CMD_SERVER
extern ESSASP_NetError ESSASP_CB_OnReqGSCmdStatus(ESSASP_NetGS_CP_CmdInfo *pCmdInfo);	// Called in response to network request to get currently executed GS command status. Fill pCmdInfo or return error code
#endif

// Called in response to ESSASP_RestartRemoteDev call
// This ensures message leave current device on network only
void ESSASP_CB_OnRestartRemoteDevFinished(ESSASP_NetError nStatus);

//////////////////////////////////////////////////////////////////////////
// Commands executed by service protocol
//////////////////////////////////////////////////////////////////////////
const char *ESSASP_GetNetErrAsString(ESSASP_NetError nErr);

// Send async announce on application request
// Will send on all internal MAC interfaces
// Will call internally ESSASP_CB_OnReqNodeInfo to get node info
void ESSASP_SendAnnounce(ESSASNetInterface nPhyIntf);

// Call this in response to ESSASP_CB_PrepareShipMode
// Ship mode can be executed async to request, and can take unlimited amount of time to complete
void ESSASP_PrepareShipModeComplete(ESSASP_ReplyContext *pRC, ESSASP_NetError nErr);

// After attempt to enter ship mode with ESSASP_CB_EnterShipMode, if that fails, we can return fail result to host with this function
void ESSASP_EnterShipModeError(ESSASP_ReplyContext *pRC, ESSASP_NetError nErr);

#ifdef ESSASP_SUPPORT_DISCOVERY_CLIENT
/*	
	Start async operation to discover devices on MAC network.
	Each call will end-up with call to ESSASP_CB_OnDiscoveryFinished.
	ESSASP_CB_OnNodeInfo will be called on any reception of node info within ESSASP_StartDiscover - ESSASP_CB_OnDiscoveryFinished timeframe.
	ESSASP_CB_OnNodeInfo will NOT be called with two or more times with information about same node.
	nDevTypeFilter - Filter devices by type, defined in ESPLATFORM_COMMON\ESSAT_ModuleTypes.h or 0 if all devices should be queried.
	nOpModeFilter - 0 if all devices should respond.
	bOnlyMasters - != 0 if interested of only master devices.
	You can have simultaneous requests for each physical interface.
*/
ESSASP_NetError ESSASP_StartDiscover(ESSASP_OperationalMode nOpModeFilter, uint16_t nDevTypeFilter, bool bOnlyMasters, ESSASNetInterface nPhyIntf);
#endif

// Used by communication module to collect all modules command execution status
// ESSASP_CB_OnGSCmdStatus will be called for each module that report it's GS command status
// Will end-up with ESSASP_CB_OnGSCmdStatusFinished
#ifdef ESSASP_SUPPORT_GS_CMD_CLIENT
ESSASP_NetError ESSASP_StartCollectGSCmdStatus(ESSASNetInterface nPhyIntf);
#endif

#ifdef ESSASP_SUPPORT_SET_REMOTE_DEVICE_MAC_ADDR
// If returned ESSASPNE_SUCCESS, async operation started. 
// Will always endup with a call to ESSASP_CB_OnSetRemoteDevMACFinished
// Previous operation may be interrupted with new call
// NOT TO BE USED ON SAT! ALL MAC ADDRESSES SHOULD BE SET ON THE GROUND BEFORE FLIGHT
ESSASP_NetError ESSASP_SetRemoteDevMACAddr(const char *szModuleSerial, uint8_t nNewMACAddr, ESSASNetInterface nPhyIntf);
#endif

// Restart remote device in specific mode
// nMacAddr can be broadcast, but current module will not be restarted
// ESSASP_CB_OnRestartRemoteDevFinished will be called after message is sent or error by driver
void ESSASP_RestartRemoteDev(uint8_t nDestMacAddr, ESSASP_OperationalMode nInOpMode, ESSASNetInterface nPhyIntf);


//////////////////////////////////////////////////////////////////////////
// Main functionality
//////////////////////////////////////////////////////////////////////////
ESSA_pStack_ProtocolInfo_t ESSASP_ServiceProtocolHook();

extern const ESSA_Stack_ProtocolInfo_t g_ServiceProtocolCbks;

void ESSASP_Init();
void ESSASP_Task();
void ESSASP_Exit();

#endif // _ESSA_SERVICEPROTOCOL_IMPL_H_
