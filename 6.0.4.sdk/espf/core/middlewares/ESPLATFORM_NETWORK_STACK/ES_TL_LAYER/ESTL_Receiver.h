#ifndef __ESTL_RECEIVER_H__
#define __ESTL_RECEIVER_H__

#include <stdint.h>
#include <stdbool.h>

#include "ES_TL_Layer.h"
#include "../ES_SAT_API/include/ESSA_BridgeDrv.h"

// bitmask for OnESTLR_GetBufferOnNewPacket pnOptionsMask field
#define EESTLR_RCVOPT_NONE                  0x0
#define EESTLR_RCVOPT_PARTIAL_RECEIVE       0x1 // Callback is provided for every received chunk

// TODO: Currently one large enough buffer to hold entire command is only implemented.
// However, this is not suitable for large packets, that are stored in file system.
// Therefore, we must extend this to support partial buffers (enough to store chunk data transfer).
// Use flag EESTLR_RCVOPT_PARTIAL_RECEIVE to indicate that this is the case.
// Logic in class also need to be changed.
// This is not needed for satellite modules, but may be needed for ground station implementation. TBD.


typedef uint8_t (*OnESTLR_NewChunk_t)(uint8_t* pChunk, uint16_t nReceivedSize, uint64_t* pPacketNumber);

typedef struct
{
    // Provided
    uint8_t nTLHostProtocolID;          // Protocol over TL level
    uint64_t nTLHostContext;            // Context depending on host layer (usually sequence ID of some sort)

    // Required
    uint64_t nOptionsMask;              // EESTLR_RCVOPT_...
    uint8_t *pBuff;                     // Receive buffer
    uint32_t nBuffSize;                 // sizeof pBuff, in/out param supplied required minimum buffer to store incoming packet
    uint32_t nPartialReceivedSize;      // Already received healthy chunk if any
    OnESTLR_NewChunk_t OnNewChunk;      // If this callback is provided, it will be called on every new chunk data and 'pBuff' / 'nBuffSize' will be unused
} STLReceiveBufferContext;

//-----------------------------------------------------------------------------------------------------------------
// Interface

// Interface between ESTL_Drv and ESTL_Receiver
typedef void (*OnESTLR_DataFrameReceivedRcv_t)(uint8_t nTLHostProtocolID);
typedef void (*OnESTLR_DataProgressRcv_t)(uint8_t nTLHostProtocolID, uint32_t nWholePacketSize, uint32_t nReceivedSize);
typedef uint8_t (*OnESTLR_GetBufferOnNewPacketRcv_t)(STLReceiveBufferContext *pReceiveBufferContext);
typedef void (*OnESTLR_PacketReceiveCompletedRcv_t)(uint8_t nTLHostProtocolID, uint32_t nPacketSize, const ESSATMAC_Context *pMACContext);

typedef struct
{
    OnESTLR_DataFrameReceivedRcv_t OnDataFrameReceived;
    OnESTLR_DataProgressRcv_t OnDataProgress;
    OnESTLR_GetBufferOnNewPacketRcv_t OnGetBufferOnNewPacket;
    OnESTLR_PacketReceiveCompletedRcv_t OnPacketReceiveCompleted;
    ESSA_pTL_SendFrame_t SendFrame;
} SESTL_ReceiverIntf;

// Interface functions
void ESTL_Receiver_Init(SESTL_ReceiverIntf* pDrvIntf);
void ESTL_Receiver_Task();

void ESTL_Receiver_OnTL_Packet(const ESSATMAC_Context *pMACContext, SESTL_Hdr *pTLHdr, uint16_t nPktSize);       // Called on new packet from MAC layer
void ESTL_Receiver_OnTL_MACSendFrameResult(uint32_t nMACFrameID, ESSATMAC_ErrCodes nMACError);


#endif // __ESTL_RECEIVER_H__
