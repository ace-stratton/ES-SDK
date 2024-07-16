/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup ESPS_I
 * @{
 *
 * @file    ESSA_ServiceProtocol_Handler.c
 * @brief   ESPS stack Service Protocol definitions
 *
 * @}
 */

#include <esps_drv.h>
#include <esps_drv_config.h>
#include "ESSA_ServiceProtocol_Handler.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/Source/ESSA_ServiceProtocol_Impl.h"
#include "ESPLATFORM_NETWORK_STACK/ES_CP/ESCP_ModDrv.h"
#include "ESPLATFORM_COMMON/ESSAT_ModuleTypes.h"
#include "CommandsApi.h"
#include "SdMngr.h"
#include "nvm_resetcounters.h"
#include "nvm/inc/nvm.h"
#include "module_id.h"

#include <string.h>

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
    ESSASP_NetError res = ESSASPNE_BAD_PARAMS;
#ifdef COMM_RS485_MAC_LAYER_ENABLED
    if (pInitConfig != NULL)
    {
        sModuleIdPersistentSettings_t modIdSettings;
        Nvm_GetBlockById(NVM_BLOCK_MODULEID, &modIdSettings);

        modIdSettings.nModuleHWConfig = pInitConfig->nModuleHWConfig;
        modIdSettings.nModuleHWRevision = pInitConfig->nModuleHWRevision;
        modIdSettings.nModuleType = pInitConfig->nModuleType;
        (void) memcpy(modIdSettings.szModuleSerial,
                      pInitConfig->szModuleSerial,
                      ESSASP_DEV_SERIAL_MAX_SIZE);

        Nvm_SetBlockById(NVM_BLOCK_MODULEID, &modIdSettings, NVMSETBLOCK_STORE_IMMEDIATELY);

        res = ESSASPNE_SUCCESS;
    }
#endif
	return res;
}

// Restart device in specific mode.
// If nInMode = ESSASP_OM_UNKNOWN, no mode change, just restart
// If mode is not supported, restart device in current one
void ESSASP_CB_RestartDev(ESSASP_OperationalMode nInMode)
{
    AppMode_t reqMode;

	switch (nInMode)
	{
	    case ESSASP_OM_NORMAL:
	        reqMode = APPMODE_APPLICATION;
        break;

	    case ESSASP_OM_FAILSAFE:
	        reqMode = APPMODE_BOOTLOADER;
	    break;

	    // only reset without switching modes
	    case ESSASP_OM_UNKNOWN:
        default:
#if defined(BOOTLOADER)
            reqMode = APPMODE_BOOTLOADER;
#else   // #if defined(BOOTLOADER)
            reqMode = APPMODE_APPLICATION;
#endif
        break;
	}

    WriteHandler_ResetInBootOrAppMode(reqMode);
}

// Initial device configuration should be set before we could set MAC address.
ESSASP_NetError ESSASP_CB_OnSetMACAddr(uint8_t nNewMacAddr)
{
    ESSASP_NetError res = ESSASPNE_BAD_PARAMS;

    // Currently all physical MAC interfaces share the same address, therefore it doesn't matter
    // which interface address will be changed.
    if (MacCfg_bSetMacAddress(eMAC_Interface_Primary, nNewMacAddr))
    {
        MacCfg_vApplyMacAddrConfig(eMAC_Interface_Primary, nNewMacAddr);
        res = ESSASPNE_SUCCESS;
    }

	return res;
}

// Expected result is send async (no timeout in host) via ESSASP_PrepareShipModeComplete with same params
// If go async copy/preserve pRC with memcpy till ESSASP_PrepareShipModeComplete call
void ESSASP_CB_PrepareShipMode(ESSASP_ReplyContext *pRC)
{
    ESSASP_NetError psmRes;

    bool rstCntrsRes = NvmResetCounters_ClearCounter(RSTCOUNTERID_ALL);

    // format all SD cards
    FRESULT fr = SdMngr_RequestPartitionFormat(SD_MNGR_FATFS_SDCARD_PARTITION, true);

    psmRes = ((fr == FR_OK) && (rstCntrsRes)) ? (ESSASPNE_SUCCESS) : (ESSASPNE_GENERAL_ERROR);

	// This can be async operation and it has no timeout on it.
	// So long prepare operations can be performed
	ESSASP_PrepareShipModeComplete(pRC, psmRes);
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
    MODID_VersionInfo_t verInfo;

    if (pNodeInfo != NULL)
    {
        module_id_get_info(&verInfo);

        memset(pNodeInfo, 0, sizeof(*pNodeInfo));			// It is a good practice to clear it, in case new fields are added

        strncpy((char *) pNodeInfo->szModuleSerial, (const char *) verInfo.au8HwSerialNumber, (size_t) sizeof(pNodeInfo->szModuleSerial) - 1);
        pNodeInfo->szModuleSerial[sizeof(pNodeInfo->szModuleSerial) - 1] = 0x0;		// just in case

        pNodeInfo->nModuleType = verInfo.u16ModuleType;	            // or DevName. From ESPLATFORM_COMMON\ESSAT_ModuleTypes.h
        pNodeInfo->nModuleHWConfig = verInfo.sHwVersion.u16Major;							// Device specific, use 0 if not used
        pNodeInfo->nModuleHWRevision = verInfo.sHwVersion.u16Minor;						// Device specific, use 0 if not used
        pNodeInfo->nOperationalMode = (verInfo.eActiveImageType == MODID_SWIMGTYPE_BOOTLOADER) ? (ESSASP_OM_FAILSAFE) : (ESSASP_OM_NORMAL);			// ESSASP_OperationalMode
        pNodeInfo->nMACAddr = ESSATMAC_GetModuleAddr();			// Current one, may be 0 if not set
        pNodeInfo->nModuleFWVariant = 0;						// or Type. Firmware type if normal mode of operation. Device specific, use 0 if not used
        pNodeInfo->nFWVersionMaj = verInfo.sFwVersion.u16Major;
        pNodeInfo->nFWVersionMin = verInfo.sFwVersion.u16Minor;
        // TODO: Update after Primary/Secondary rules are clarified...
        pNodeInfo->nFlags = ESSASP_DPF_NONE;					// ESSASP_DPF_...
    }
}

// Node may send occasional broadcast with its parameters in case it is restarted or mode of operation was changed etc.
// This is in case device app layer do send such announce
void ESSASP_CB_OnAsyncNodeInfo(ESSASP_NetDiscoveryNodeInfo *pNodeInfo, ESSASNetInterface nPhyIntf)
{
	// Store and update internal catalog of devices from pNodeInfo if you wish
//	GW_OnAsyncNodeInfo(pNodeInfo, nPhyIntf);
}

// Node info received in response to explicit call to ESSASP_StartDiscover
void ESSASP_CB_OnNodeInfo(ESSASP_NetDiscoveryNodeInfo *pNodeInfo, ESSASNetInterface nPhyIntf)
{
//	GW_OnNodeInfo(pNodeInfo);
}

// Usually called within few seconds (max ~5) after ESSASP_StartDiscover was called
void ESSASP_CB_OnDiscoveryFinished(ESSASP_NetError nStatus, ESSASNetInterface nPhyIntf)
{
//	GW_OnRXAllTestComplete(nStatus);
}

// Called for each successfull call to ESSASP_SetRemoteDevMACAddr
void ESSASP_CB_OnSetRemoteDevMACFinished(ESSASP_NetError nStatus)
{
//	GW_OnDUTSetAddrPktRes(nStatus);
}

// Called in response to ESSASP_RestartRemoteDev call
// This ensures message leave current device on network only
void ESSASP_CB_OnRestartRemoteDevFinished(ESSASP_NetError nStatus)
{
	const char *szErr = ESSASP_GetNetErrAsString(nStatus);
	(void) szErr;

	TRACE("RestartRemoteDevFinished : %s\r\n", szErr);
}

// Command status received from some module
void ESSASP_CB_OnGSCmdStatus(ESSASP_NetGS_CP_CmdInfo *pCmdInfo, ESSASNetInterface nPhyIntf)
{
	// For UHF : Build GS command response with these
	TRACE("%02X, ", pCmdInfo->nMACAddr);
}

void ESSASP_CB_OnGSCmdStatusFinished(ESSASP_NetError nStatus, ESSASNetInterface nPhyIntf)
{
	// For UHF : Finish GS command and send result
	TRACE("finished\r\n");
}

// Called in response to network request to get currently executed GS command status. Fill pCmdInfo or return error code
ESSASP_NetError ESSASP_CB_OnReqGSCmdStatus(ESSASP_NetGS_CP_CmdInfo *pCmdInfo)
{
    EESCP_State eState = CESCPS_FREE;
	uint64_t nCP_CmdID = 0;
    ESCP_ModDrv_GetCmdStatus(&nCP_CmdID, &eState);
	pCmdInfo->nCP_CmdID = nCP_CmdID;

	pCmdInfo->nMACAddr = ESSATMAC_GetModuleAddr();

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
