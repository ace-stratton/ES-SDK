#ifndef __ESSA_MACTEST_H__
#define __ESSA_MACTEST_H__

#include <stdint.h>
#include "../include/ESSA_Stack.h"

// ESSA_MACTestHeader::nCmd
#define ESSAMACT_CMD_REPLY						0
#define ESSAMACT_CMD_START_FLOOD				1
#define ESSAMACT_CMD_STOP_FLOOD					2
#define ESSAMACT_CMD_GET_FLOOD_STATS			3
#define ESSAMACT_CMD_START_COUNT_PKTS			4
#define ESSAMACT_CMD_COUNT_PKT					5
#define ESSAMACT_CMD_GET_PKTS_COUNT				6

// Each mac test packet is sent with this header and random number of data after it
// Tested device (DUT) should return exact packet back to sender, obey data from this structure
typedef struct 
{
	uint8_t nCmd;					// ESSAMACT_CMD_...
	uint8_t nReturnPriority;		// ESSASMP_... from ESSA_Stack.h
	uint32_t nPktSequence;			// Used to identify lost packets
} __attribute__((__packed__)) ESSA_MACTestHeader;

// Get accumulated pkt count. CMD = ESSAMACT_CMD_GET_PKTS_COUNT
typedef struct 
{
	ESSA_MACTestHeader hdr;			// Keep first

	uint32_t nPktsCount;

} __attribute__((__packed__)) ESSA_MACTestGetPktCount;

// Get flood test statistics. CMD = ESSAMACT_CMD_START_FLOOD
typedef struct 
{
	ESSA_MACTestHeader hdr;			// Keep first

	uint8_t bEnableDynamicSendPrioritization;

} __attribute__((__packed__)) ESSA_MACTestStartFlood;

// Get flood test statistics. CMD = ESSAMACT_CMD_GET_FLOOD_STATS
typedef struct 
{
	ESSA_MACTestHeader hdr;			// Keep first

	char szSerial[50];				// Target device serial (TLV random data as HEX string), if szSerial[0] = 0, do not check it, just return stats
	uint32_t nFloodTestTime;		// Measured by device
	uint32_t nFloodSuccessBytes;	// Measured by device

	uint16_t nStatsCountersCount;	// Filled in nStatsCounters counters
	uint32_t StatsCounters[20];		// MAC driver specific counters

} __attribute__((__packed__)) ESSA_MACTestFloodStatistics;

// Diagnostic functions
extern uint32_t ESSA_MACTEST_GetLastPktID();

// For MAC network tests
typedef void (*pfESSA_MACTestFloodStart)(ESSATMAC_MsgPriority nStackPriority, bool bEnableDynamicSendPrioritization);
typedef void (*pfESSA_MACTestFloodStop)();
typedef void (*pfESSA_MACTestSendFloodStats)(ESSATMAC_Context *pMACContext, ESSA_MACTestFloodStatistics *pReqPkt);

// For MAC network tests
void ESSA_MACTEST_SetFloodFn(pfESSA_MACTestFloodStart FloodStartFn, pfESSA_MACTestFloodStop FloodStopFn, pfESSA_MACTestSendFloodStats FloodSendStatsFn);

#endif // __ESSA_MACTEST_H__
