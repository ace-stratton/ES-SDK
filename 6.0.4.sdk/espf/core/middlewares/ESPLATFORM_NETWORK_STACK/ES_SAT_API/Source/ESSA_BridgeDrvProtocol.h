/*
 * Bridge Driver protocol declaretion
 * Here are system/private protocol data types and constants not accessible to the user
 */

#ifndef _STACK_INCLUDE_BRIDGE_DRV_PROTOCOL_H_
#define _STACK_INCLUDE_BRIDGE_DRV_PROTOCOL_H_

#include <stdint.h>

#include "../include/ESSA_BridgeDrv.h"

extern const ESSA_Stack_ProtocolInfo_t g_TL_BridgeDriverProtocolCbks;
//---------------------------------------------------------------------------------------------------------------------------
// Protocol callbacks, used from 'STACK' engine
ESSA_pStack_ProtocolInfo_t ESSA_TL_BridgeDriverProtocol(void);

#endif // _STACK_INCLUDE_BRIDGE_DRV_PROTOCOL_H_
