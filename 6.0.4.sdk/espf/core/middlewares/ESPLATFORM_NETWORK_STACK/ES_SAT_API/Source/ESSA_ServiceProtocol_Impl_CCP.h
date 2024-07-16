/*	
 *	This part of service protocol will be moved to GS commands...someday
 */

#ifndef _ESSA_SERVICEPROTOCOL_IMPL_CCP_H_
#define _ESSA_SERVICEPROTOCOL_IMPL_CCP_H_

#include <stdint.h>

#include "ESSA_StackConfig.h"
#include "../include/ESSA_Stack.h"
#include "../include/ESSA_ServiceProtocol_Types.h"

// TODO: remove these
//#define ESSASP_SUPPORT_GS_CMD_CLIENT
//#define ESSASP_SUPPORT_GS_CMD_SERVER

void ESSASP_GS_Init();

// ESSASP_SUPPORT_DISCOVERY_CLIENT
void ESSASP_DCGS_Task(ESSASNetInterface nPhyIntf);
void ESSASP_DCGS_RxInfo(ESSA_Stack_DataDispatchInfo_t* pDataInfo);

void ESSASP_DSGS_Task(ESSASNetInterface nPhyIntf);
void ESSASP_DSGS_OnClientConfirm(ESSA_Stack_DataDispatchInfo_t* pDataInfo);
void ESSASP_DSGS_OnDiscoveryRequest(ESSA_Stack_DataDispatchInfo_t* pDataInfo);

#endif // _ESSA_SERVICEPROTOCOL_IMPL_CCP_H_
