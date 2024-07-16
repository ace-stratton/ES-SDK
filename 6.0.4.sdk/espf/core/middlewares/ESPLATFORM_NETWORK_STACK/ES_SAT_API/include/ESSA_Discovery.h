/*
 *
 *  Created on: May 15, 2020
 *      Author: Georgi-EnduroSat
 */

#ifndef __ESSA_DISCOVERY_H__
#define __ESSA_DISCOVERY_H__

#include <stdint.h>
#include "../include/ESSA_Stack.h"
#include "../include/ESSA_Discovery.h"

#define ESSA_DISCOVERY_NODE_INFO_SIZE ((uint8_t) 12)
#define ESSA_NETWORK_MAC_ADDR_SIZE ((uint8_t) 8)
#define ESSA_DISCOVERY_REGISTRY_SIZE ((uint8_t) 12)

// Node types
#define ESSA_DISCOVERY_NODE_TYPE_BATTERY_PACK ((uint8_t) 1)
#define ESSA_DISCOVERY_NODE_TYPE_EPS          ((uint8_t) 2)
#define ESSA_DISCOVERY_NODE_TYPE_ANTENNA      ((uint8_t) 3)
#define ESSA_DISCOVERY_NODE_TYPE_OBC          ((uint8_t) 4)
#define ESSA_DISCOVERY_NODE_TYPE_CAM          ((uint8_t) 5)
#define ESSA_DISCOVERY_NODE_TYPE_LED          ((uint8_t) 6)

typedef enum {
    eESSA_DISCOVERY_RESPONSE_OK = 0,
    eESSA_DISCOVERY_RESPONSE_ERROR,
    eESSA_DISCOVERY_RESPONSE_BAD_DATA,
    eESSA_DISCOVERY_RESPONSE_INVALID_MAC,
    eESSA_DISCOVERY_RESPONSE_INVALID_SHORT_ADDR,
    eESSA_DISCOVERY_RESPONSE_OUT_OF_RANGE,
} eESSA_DiscoveryResponse_t;

typedef struct {
    uint8_t  u8VersionMajor;
    uint16_t u16VersionMinor;
} __attribute__((__packed__)) ESSA_DiscoveryResponseVersion_t;

typedef struct {
    uint8_t au8MACAddr[ESSA_NETWORK_MAC_ADDR_SIZE];
    uint8_t u8ShortAddr;
} __attribute__((__packed__))  ESSA_Discovery_RequestSetId_t;

typedef struct {
    uint8_t u8Type;
} __attribute__((__packed__))  ESSA_Discovery_RequestReqId_t;

typedef struct {
    uint8_t  au8MACAddr[ESSA_NETWORK_MAC_ADDR_SIZE];
    uint8_t  u8ShortAddr;
    uint8_t  u8ResultCode;
} __attribute__((__packed__)) ESSA_DiscoveryResponseSetId_t;

typedef struct {
    uint8_t u8Type;
    uint8_t au8Info[ESSA_DISCOVERY_NODE_INFO_SIZE];
    uint8_t au8MACAddr[ESSA_NETWORK_MAC_ADDR_SIZE];
    uint8_t u8ShortAddr;
    uint8_t u8Validity;
} __attribute__((__packed__))  ESSA_DiscoveryNodeInfo_t;

typedef ESSA_DiscoveryNodeInfo_t *(*pfESSA_DiscoveryFuncRequestNodeInfoHandler_t)(void);
typedef eESSA_DiscoveryResponse_t (*pfESSA_DiscoveryFuncRequestSetIdHandler_t)(ESSA_Discovery_RequestSetId_t *fp_pReqData);
typedef ESSA_DiscoveryNodeInfo_t *(*pfESSA_DiscoveryFuncRequestReqTypeHandler_t)(ESSA_Discovery_RequestReqId_t *fp_pReqData);

typedef void (*pfESSA_DiscoveryFuncResponseVersionHandler_t)(ESSA_DiscoveryResponseVersion_t *fp_pResponseData);

// Node Info response is for both ReqNodeInfo and ReqId requests. When ReqIdr request appear to be invalid the u8Validity
// should be set properly.
typedef void (*pfESSA_DiscoveryFuncResponseNodeInfoHandler_t)(ESSA_DiscoveryNodeInfo_t     *fp_pResponseData);
typedef void (*pfESSA_DiscoveryFuncResponseSetIdHandler_t) (ESSA_DiscoveryResponseSetId_t  *fp_pResponseData);

// TODO: Add debug commands for reading the Discovery registry
typedef struct {
    pfESSA_DiscoveryFuncRequestNodeInfoHandler_t  ReqNodeInfo_Handler;
    pfESSA_DiscoveryFuncRequestSetIdHandler_t     ReqSetId_Handler;
    pfESSA_DiscoveryFuncRequestReqTypeHandler_t   ReqReqType_Handler;
    pfESSA_DiscoveryFuncResponseVersionHandler_t  RespVersion_Handler;
    pfESSA_DiscoveryFuncResponseNodeInfoHandler_t RespNodeInfo_Handler;
    pfESSA_DiscoveryFuncResponseSetIdHandler_t    RespSetId_Handler;
    pfESSA_Stack_StatusHandler_Cbk_t              Error_Handler;
} ESSA_Discovery_Api;

typedef struct {
	ESSA_DiscoveryNodeInfo_t NodeInfo;
    uint16_t TTL;                // Time to live in ms, 0 = unlimited
    uint16_t CRC;
} ESSA_Discover_NodeEntry_t;

// User implementation call back invoked when an NodeInfo entry is added to the registry
// eg. a device is discovered.
extern void Impl_ESSA_DiscoveryOnEntryNotify(ESSA_DiscoveryNodeInfo_t *fp_pNodeInfo);

void                ESSA_RegistryInit(void);
ESSA_DiscoveryNodeInfo_t *ESSA_Discovery_ResolveByMAC(uint8_t *fp_pu8MAC);
ESSA_DiscoveryNodeInfo_t *ESSA_Discovery_ResolveByType(uint8_t fp_u8Type);

ESSA_Discovery_Api *ESSA_DiscoveryInit(void);

#endif  // __ESSA_DISCOVERY_H__
