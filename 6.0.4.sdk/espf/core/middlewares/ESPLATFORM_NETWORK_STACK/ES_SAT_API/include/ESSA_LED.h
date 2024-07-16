/*
 *  Created on: May 16, 2020
 *      Author: Georgi-EnduroSat
 */

#ifndef __ESSA_LED_H__
#define __ESSA_LED_H__

#include <stdint.h>
#include "../include/ESSA_Stack.h"

typedef enum {
    eESSA_LED_ERR_OK = 0,
    eESSA_LED_ERR_ERROR,
    eESSA_LED_ERR_BAD_DATA,
    eESSA_LED_ERR_OUT_OF_RANGE,
} eESSA_LedResponse_t;

typedef enum {
    eESSA_LED_STATE_ON = 0,
    eESSA_LED_STATE_OFF,
    eESSA_LED_STATE_TOGGLE,
    eESSA_LED_STATE_BLINK,
} eESSA_LedState_t;

typedef struct {
    uint16_t u16LedId;
} __attribute__((__packed__)) ESSA_LedRequestData_t;

typedef struct {
    uint16_t u16LedId;
    uint8_t u8ResponseCode;
} __attribute__((__packed__)) ESSA_LedResponseData_t;

typedef struct {
    uint8_t  u8VersionMajor;
    uint16_t u16VersionMinor;
} __attribute__((__packed__)) ESSA_LedResponseVersion_t;

typedef eESSA_LedResponse_t (*pfESSA_LedFuncRequestHandler_t)(ESSA_LedRequestData_t *fp_pRequestData);
typedef void (*pfESSA_LedFuncResponseHandler_t)(ESSA_LedResponseData_t *fp_pResponseData);
typedef void (*pfESSA_LedFuncResponseVersionHandler_t)(ESSA_LedResponseVersion_t *fp_pResponseData);

typedef struct {
    uint8_t *pu8Info;
    uint8_t u8InfoSize;
    pfESSA_LedFuncRequestHandler_t ReqON_Handler;
    pfESSA_LedFuncRequestHandler_t ReqOFF_Handler;
    pfESSA_LedFuncRequestHandler_t ReqToggle_Handler;
    pfESSA_LedFuncRequestHandler_t ReqBlink_Handler;
    pfESSA_LedFuncResponseVersionHandler_t RespVersion_Handler;
    pfESSA_LedFuncResponseHandler_t RespON_Handler;
    pfESSA_LedFuncResponseHandler_t RespOFF_Handler;
    pfESSA_LedFuncResponseHandler_t RespToggle_Handler;
    pfESSA_LedFuncResponseHandler_t RespBlink_Handler;
	pfESSA_Stack_StatusHandler_Cbk_t Error_Handler;
} ESSA_LED_ProtocolApi;

extern void ESSA_LedProtocol_SetLedState(uint32_t fp_u32DestAddr, uint16_t fp_u16LedId, eESSA_LedState_t fp_eState);

#endif // __ESSA_LED_H__
