/*
 * DiscoveryProtocol.h
 *
 *  Created on: May 16, 2020
 *      Author: Georgi-EnduroSat
 */

#ifndef __ESSA_DISCOVERYPROTOCOL_H__
#define __ESSA_DISCOVERYPROTOCOL_H__

#include <stdint.h>

#include "../include/ESSA_Stack.h"
#include "../include/ESSA_Discovery.h"

#define ESSA_DISCOVERY_REQUEST_VERSION_ID    ((uint8_t) 0)
#define ESSA_DISCOVERY_REQUEST_NODEINFO_ID   ((uint8_t) 1)
#define ESSA_DISCOVERY_REQUEST_SET_ID_ID     ((uint8_t) 2)
#define ESSA_DISCOVERY_REQUEST_REQ_TYPE_ID   ((uint8_t) 3)

#define ESSA_DISCOVERY_RESPONSE_VERSION_ID   ((uint8_t) 125 + 0)
#define ESSA_DISCOVERY_RESPONSE_NODEINFO_ID  ((uint8_t) 125 + 1)
#define ESSA_DISCOVERY_RESPONSE_SET_ID_ID    ((uint8_t) 125 + 2)

typedef struct
{
    uint8_t u8FuncId;
} __attribute__((__packed__)) ESSA_DiscoveryProtocolRequestHdr_t;

// Version
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
} __attribute__((__packed__)) ESSA_DiscoveryProtocolRequestVersion_t;

// Node Info
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_DiscoveryProtocolRequestNodeInfo_t;

// Set ID
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
	ESSA_Discovery_RequestSetId_t      Data;
} __attribute__((__packed__))   ESSA_DiscoveryProtocolRequestSetID_t;

// Req ID
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
	ESSA_Discovery_RequestReqId_t      Data;
} __attribute__((__packed__))   ESSA_DiscoveryProtocolRequestReqID_t;

// Response to Version
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
	ESSA_DiscoveryResponseVersion_t    Data;
} __attribute__((__packed__)) ESSA_DiscoveryProtocolResponseVersion_t;

// Response to NodeInfo
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
	ESSA_DiscoveryNodeInfo_t           Data;
} __attribute__((__packed__)) ESSA_DiscoveryProtocolResponseNodeInfo_t;

// Response to SetID
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
	ESSA_DiscoveryResponseSetId_t      Data;
} __attribute__((__packed__)) ESSA_DiscoveryProtocolResponseSetId_t;

// Response to ReqID
typedef struct
{
	ESSA_DiscoveryProtocolRequestHdr_t Hdr;
	ESSA_DiscoveryNodeInfo_t           Data;
} __attribute__((__packed__)) ESSA_DiscoveryProtocolResponseReqId_t;

ESSA_pStack_ProtocolInfo_t ESSA_StackDiscoveryProtocol(void);

#endif // __ESSA_DISCOVERYPROTOCOL_H__
