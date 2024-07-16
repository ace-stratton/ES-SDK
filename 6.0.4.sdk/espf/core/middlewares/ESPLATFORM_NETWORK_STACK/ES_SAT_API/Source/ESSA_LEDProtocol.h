/*
 * LED_Protocol.h
 *
 *  Created on: May 15, 2020
 *      Author: Georgi-EnduroSat
 */

#ifndef STACK_INCLUDE_LED_PROTOCOL_H_
#define STACK_INCLUDE_LED_PROTOCOL_H_

#include <stdint.h>

#include "../include/ESSA_Stack.h"
#include "../include/ESSA_LED.h"

#define ESSA_LED_REQUEST_VERSION_ID    ((uint8_t) 0)
#define ESSA_LED_REQUEST_LED_ON_ID     ((uint8_t) 1)
#define ESSA_LED_REQUEST_LED_OFF_ID    ((uint8_t) 2)
#define ESSA_LED_REQUEST_LED_TOGGLE_ID ((uint8_t) 3)
#define ESSA_LED_REQUEST_LED_BLINK_ID  ((uint8_t) 4)

#define ESSA_LED_RESPONSE_VERSION_ID    ((uint8_t) 125 + 0)
#define ESSA_LED_RESPONSE_LED_ON_ID     ((uint8_t) 125 + 1)
#define ESSA_LED_RESPONSE_LED_OFF_ID    ((uint8_t) 125 + 2)
#define ESSA_LED_RESPONSE_LED_TOGGLE_ID ((uint8_t) 125 + 3)
#define ESSA_LED_RESPONSE_LED_BLINK_ID  ((uint8_t) 125 + 4)

typedef struct
{
    uint8_t u8FuncId;
} __attribute__((__packed__)) ESSA_LedProtocolRequestHdr_t;

typedef struct
{
    ESSA_LedProtocolRequestHdr_t Hdr;
    uint16_t                u16LedId;
} __attribute__((__packed__)) ESSA_LedProtoclRequestData_t;

typedef struct
{
    ESSA_LedProtocolRequestHdr_t Hdr;
    ESSA_LedResponseData_t       Data;
} __attribute__((__packed__)) ESSA_LedProtoclResponseData_t;


typedef struct
{
    ESSA_LedProtocolRequestHdr_t Hdr;
} __attribute__((__packed__)) ESSA_LedProtocolRequestVersion_t;

typedef struct
{
    ESSA_LedProtocolRequestHdr_t Hdr;
    ESSA_LedResponseVersion_t    Data;
} __attribute__((__packed__)) ESSA_LedProtocolResponseVersion_t;

ESSA_pStack_ProtocolInfo_t ESSA_StackLedProtocol(void);

void ESSA_LedProtocol_SetLedState(uint32_t    fp_u32DestAddr,
                                              uint16_t    fp_u16LedId,
                                              eESSA_LedState_t fp_eState);

#endif /* STACK_INCLUDE_LED_PROTOCOL_H_ */
