/*
 *  Created on: May 15, 2020
 *      Author: Georgi-EnduroSat
 *
 *	If you are provider or consumer of certain protocol/API, uncomment corresponding line below.
 *	Also add corresponding files from ESPLATFORM_NETWORK_STACK\ES_SAT_STACK\... to your project.
 *
 */

#ifndef __ESSA_STACKCONFIG_H__
#define __ESSA_STACKCONFIG_H__

#include "ES_SAT_MAC/ES_SAT_MAC.h"
//#include "ES_SAT_API/Source/ESSA_BridgeDrvProtocol.h"
#include "ES_SAT_API/Source/ESSA_MACTestProtocol.h"

// These are not needed any more and should be removed completely !
// Adding function pointer below and including relevant c/h files in project should be enough
//#define ESSA_USE_LED_PROTOCOL
//#define ESSA_USE_DISCOVERY_PROTOCOL
//#define ESSA_USE_UHF_PROTOCOL
//#define ESSA_USE_DEBUG_PROTOCOL
//#define ESSA_USE_FW_UPD_PROTOCOL
//#define ESSA_USE_DIAGNOSTICS_PROTOCOL
//#define ESSA_USE_EPSII_PDM_PROTOCOL
//#define ESSA_USE_EPSII_BP_PROTOCOL
//#define ESSA_USE_EPS1_PROTOCOL
//#define ESSA_USE_TRANSPORT_LAYER_PROTOCOL

// General Enable/Disable of internal MAC network channels
#define ESSA_SYS_PRI_ENABLED
//#define ESSA_SYS_SEC_ENABLED
//#define ESSA_PAY_PRI_ENABLED
//#define ESSA_PAY_SEC_ENABLED

// Tune for service protocol
#define ESSASP_TickGet16					TickGet16
#define ESSASP_ASSERT						ASSERT

//#define ESSASP_SUPPORT_DISCOVERY_CLIENT
//#define ESSASP_SUPPORT_SET_REMOTE_DEVICE_MAC_ADDR
//#define ESSASP_SUPPORT_GS_CMD_CLIENT
#define ESSASP_SUPPORT_GS_CMD_SERVER

// Installation of available MAC drivers
#define NETTYPE_HANDLER_ENTRIES_LIST    \
        NETTYPE_HANDLER_ENTRY(ESSASNETT_INTERNAL, ESSATMAC_DrvEnqMessage),  \
        NETTYPE_HANDLER_ENTRY(ESSASNETT_AIR,      NULL)

// Installation of handlers of "FunctionLayer" module-to-module API protocols
#define FUNCTION_PROTOCOL_HANDLERS_LIST

// Handlers for MAC payload protocols, defined in ES_SAT_MAC_Protocols.h
#define FS_PROTOCOL_HANDLERS_LIST            /*   ESSA_TL_BridgeDriverProtocol, */	\
												&g_MACTestProtocolCbks


#endif  // __ESSA_STACKCONFIG_H__
