#include "main.h"

#include "ESSA_ServiceProtocol_Handler.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/Source/ESSA_ServiceProtocol_Impl.h"
#include "ESPLATFORM_NETWORK_STACK/ES_CP/ESCP_ModDrv.h"
#include "ESPLATFORM_COMMON/ESSAT_ModuleTypes.h"
#include "MSP430FR_Library/MSP430FR5994/src/drivers/RS485/MAC_DRV_2/ESMAC_Drv_2.h"
#include "MSP430FR_Library/MSP430FR5994/src/TLV.h"
#include "MSP_BOOTLOADER/MSP430FR5994/common/MSP_NVMemory/NVMHeader.h"
#include "MSP430FR_Library/MSP430FR5994/src/NVMTask.h"
#include <string.h>
#include <stdio.h>

#pragma diag_suppress 1542                          // Detected memcpy() and recommend using DMA instead if greater than 100 words...
#pragma diag_suppress 2553                          // Array index (involving "nMinSerial") of type "int". Recommend using "unsigned int"

////////////////////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////////////////////
//typedef enum EBalI2CState { EBS_NONE = 0, EBS_WRITING = 1, EBS_READING = 2, EBS_RECOVER = 4, EBS_OP_COMPLETED = 8 } EBalI2CState;

////////////////////////////////////////////////////////////////////////////////////////////////
// Module members
////////////////////////////////////////////////////////////////////////////////////////////////
static char g_szDevSerial[21];

////////////////////////////////////////////////////////////////////////////////////////////////
// Forward
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////////////////////

// Put before stack initialization!
void ESSA_SP_Init(BOOL bAfterReset)
{
	// Should be moved to stack, once network stack becomes a real network stack
	ESSASP_Init();
}

void ESSA_SP_Task()
{
	// Should be moved to stack, once network stack becomes a real network stack
	ESSASP_Task();
}

void ESSA_SP_Exit()
{
	// Should be moved to stack, once network stack becomes a real network stack
	ESSASP_Exit();
}

// Set initial device configuration
// This is one time (after JTAG) very basic module configuration
// Make sure this is saved on several places in memory with recovery mechanism and not overridden by any software update other than JTAG
// If device loose this configuration it become useless!
// This configuration is applied with broadcast, before any MAC address can be set.
// So connect only your device and dongle when set this.
// Most of all other commands require this to be set to work correctly!
ESSASP_NetError ESSASP_CB_SetInitConfig(ESSASP_NetSetInitConfig *pInitConfig)
{
	return ESSASPNE_NOT_IMPLEMENTED;
}

// Restart device in specific mode.
// If nInMode = ESSASP_OM_UNKNOWN, no mode change, just restart
// If mode is not supported, restart device in current mode
void ESSASP_CB_RestartDev(ESSASP_OperationalMode nInMode)
{
	// TODO: Restart dev to requested mode
	Reset();
}

// Initial device configuration should be set before we could set MAC address.
ESSASP_NetError ESSASP_CB_OnSetMACAddr(uint8_t nNewMacAddr)
{
	// Set new MAC address
	ESMAC_SetSelfAddress(nNewMacAddr);

	// TODO: Set also to NVM

	return ESSASPNE_SUCCESS;
}

// Expected result is send async (no timeout in host) via ESSASP_PrepareShipModeComplete with same params
// If go async copy/preserve pRC with memcpy till ESSASP_PrepareShipModeComplete call
void ESSASP_CB_PrepareShipMode(ESSASP_ReplyContext *pRC)
{
	// This can be async operation and it has no timeout on it.
	// So long prepare operations can be performed
	ESSASP_PrepareShipModeComplete(pRC, ESSASPNE_SUCCESS);
}

// This is handled usually by power supply(s) to cut power to sat and enter ship mode, no result expected
// Error may be returned within 5 seconds with ESSASP_EnterShipModeError
// If go async copy/preserve pRC with memcpy till ESSASP_EnterShipModeError call
void ESSASP_CB_EnterShipMode(ESSASP_ReplyContext *pRC)
{
	// Nothing to do
}

// Discovery - server
// Give ability for this node to be discovered dynamically on network
// Called in response to network request to get our info or ESSASP_SendAnnounce() is called by app layer
void ESSASP_CB_GetDeviceInfo(ESSASP_NetDiscoveryNodeInfo *pNodeInfo)
{
	memset(pNodeInfo, 0, sizeof(pNodeInfo));			// It is a good practice to clear it, in case new fields are added

	MSP_DeviceInitialConfiguration nvmh;
	NVM_GetModuleInitialConfig(&nvmh);

	strncpy(pNodeInfo->szModuleSerial, nvmh.m_achDeviceSerial, sizeof(pNodeInfo->szModuleSerial));
	pNodeInfo->szModuleSerial[sizeof(pNodeInfo->szModuleSerial) - 1] = 0x0;		// just in case

	pNodeInfo->nModuleType = nvmh.m_nModuleHWType;				// or DevName. From ESPLATFORM_COMMON\ESSAT_ModuleTypes.h
	pNodeInfo->nModuleHWConfig = nvmh.m_nModuleHWConfig;		// Device specific, use 0 if not used
	pNodeInfo->nModuleHWRevision = nvmh.m_nModuleHWRevision;	// Device specific, use 0 if not used
	pNodeInfo->nOperationalMode = ESSASP_OM_NORMAL;			// ESSASP_OperationalMode
	pNodeInfo->nMACAddr = ESSATMAC_GetModuleAddr();				// Current one, may be 0 if not set

	// TODO: To be read from hardcoded values for current running version
	pNodeInfo->nModuleFWVariant = 0;							// or Type. Firmware type if normal mode of operation. Device specific, use 0 if not used
	pNodeInfo->nFWVersionMaj = 1;
	pNodeInfo->nFWVersionMin = 0;
	pNodeInfo->nFlags = ESSASP_DPF_NONE;						// ESSASP_DPF_...
}

// Called in response to network request to get currently executed GS command status. Fill pCmdInfo or return error code
ESSASP_NetError ESSASP_CB_OnReqGSCmdStatus(ESSASP_NetGS_CP_CmdInfo *pCmdInfo)
{
    EESCP_State eState;
    ESCP_ModDrv_GetCmdStatus(&pCmdInfo->nCP_CmdID, &eState);
    switch(eState)
    {
        case CESCPS_FREE:
        {
            if(pCmdInfo->nCP_CmdID)
                pCmdInfo->nCP_CmdStatus = ESSASP_CCPCS_UPLOADING;
            else
                pCmdInfo->nCP_CmdStatus = ESSASP_CCPCS_NONE;
            break;
        }
        case CESCPS_PENDING:
        {
            pCmdInfo->nCP_CmdStatus = ESSASP_CCPCS_WAIT_EXEC;
            break;
        }
        case CESCPS_WAIT_SEND_RESULT:
        {
            pCmdInfo->nCP_CmdStatus = ESSASP_CCPCS_DOWNLOADING;
            break;
        }
        default:
            return ESSASPNE_GENERAL_ERROR;
    }
	return ESSASPNE_SUCCESS;
}

// Called in response to ESSASP_RestartRemoteDev call
// This ensures message leave current device on network only
void ESSASP_CB_OnRestartRemoteDevFinished(ESSASP_NetError nStatus)
{
	const char *szErr = ESSASP_GetNetErrAsString(nStatus);
	TRACE("RestartRemoteDevFinished : %s\r\n", szErr);
}
