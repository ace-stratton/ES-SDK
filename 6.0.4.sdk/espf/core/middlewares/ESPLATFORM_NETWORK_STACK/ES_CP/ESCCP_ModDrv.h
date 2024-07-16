#ifndef __ESCCP_MOD_DRV_H__
#define __ESCCP_MOD_DRV_H__

/*
 * Command Control Protocol Layer
 * Send/Receive commands from GS, used to control commands flow along with CP buddy layer.
 * Only one command can be hold/processed at a time within this module buffer
 * On receive, input buffer will be blocked, till host layer release buffer.
 * This is usually after host layer send response, but commands that can be queued (somewhere else) or do not require response can be freed from within OnCommandReceived notification
 */

#include "../ES_TL_LAYER/ESTL_Drv.h"

//-----------------------------------------------------------------------------------------------------------------------
// Interface
void ESCCP_ModDrv_GetInterface(ESTL_SHostLayerItem* pIntf);

void ESCCP_ModDrv_Init(bool bAfterReset);
void ESCCP_ModDrv_Task();

void ESCCP_ModDrv_SendOOBResult(STLSendContext *pSendContext, uint8_t nTLError);

#endif // __ESCCP_MOD_DRV_H__
