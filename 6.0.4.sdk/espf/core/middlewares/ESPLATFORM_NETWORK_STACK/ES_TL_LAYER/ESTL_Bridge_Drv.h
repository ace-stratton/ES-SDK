#ifndef __ESTL_BRIDGE_DRV_H__
#define __ESTL_BRIDGE_DRV_H__

// Only needed if module is UHF or other that need to retransmit TL packets in/out of sat internal network
// Module restart it's state machine each time new transfer is started.
// GS is responsible to transmit packets one by one

//#define ES_MOD_SAT_ID                          (2)     /* one-time configuration for preserved in all modules */

#include <stdint.h>
#include <stdbool.h>
#include "../ES_SAT_API/include/ESSA_BridgeDrv.h"

//------------------------------------------------------------------------------------------------------------
// Interface

ESSA_pTL_SendFrame_t ESTL_BridgeDriverAddHostLayer(ESSA_pfStack_DataHandler_Cbk_t pfOnNewData, ESSATMAC_DrvResult_Cbk_t pfOnSendResult);
void ESTL_Bridge_Drv_Init(bool bAfterReset);
void ESTL_Bridge_Drv_Task();

#endif // __ESTL_BRIDGE_DRV_H__
