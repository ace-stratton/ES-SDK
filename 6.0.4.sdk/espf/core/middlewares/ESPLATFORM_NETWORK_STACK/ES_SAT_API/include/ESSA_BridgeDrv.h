/*
 * Bridge Driver Declaraion
 * Here types between TL and STACK are declared
 */

#ifndef _STACK_INCLUDE_BRIDGE_DRV_H_
#define _STACK_INCLUDE_BRIDGE_DRV_H_

#include <stdint.h>

#include "../include/ESSA_Stack.h"

typedef ESSATMAC_ErrCodes (*ESSA_pTL_SendFrame_t)(ESSASNetInterface nNetIntf, ESSASNetType netType, uint8_t nTargetAddress, uint8_t *pMsgData, uint8_t nMsgDataSize, ESSATMAC_MsgPriority nMsgPriority, uint32_t *pMsgId);
extern ESSA_pTL_SendFrame_t ESSA_TL_ProtocolUserInit(ESSA_pfStack_DataHandler_Cbk_t pfOnNewData, ESSATMAC_DrvResult_Cbk_t pfOnSendResult);

#endif // _STACK_INCLUDE_BRIDGE_DRV_H_
