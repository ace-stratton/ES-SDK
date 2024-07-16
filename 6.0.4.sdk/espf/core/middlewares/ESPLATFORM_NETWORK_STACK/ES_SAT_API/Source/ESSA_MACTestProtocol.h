/*
 * Protocol for testing MAC driver operation.
 * Here are system/private protocol data types and constants not accessible to the user.
 */

#ifndef _ESSA_MACTESTPROTOCOL_H_
#define _ESSA_MACTESTPROTOCOL_H_

#include <stdint.h>
#include "../include/ESSA_Stack.h"

extern const ESSA_Stack_ProtocolInfo_t g_MACTestProtocolCbks;

// Protocol callbacks, used from 'STACK' engine
ESSA_pStack_ProtocolInfo_t ESSA_MACTEST_Protocol();
uint32_t ESSA_MACTEST_GetLastPktID();

#endif // _ESSA_MACTESTPROTOCOL_H_
