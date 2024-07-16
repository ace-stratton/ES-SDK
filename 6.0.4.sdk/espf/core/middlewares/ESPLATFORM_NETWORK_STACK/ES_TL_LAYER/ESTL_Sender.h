#ifndef __ESTL_SENDER_H__
#define __ESTL_SENDER_H__

#include <stdint.h>
#include <stdbool.h>
#include "ES_TL_Layer.h"
#include "../ES_SAT_API/include/ESSA_BridgeDrv.h"

//-----------------------------------------------------------------------------------------------------------------------
// Types

// Send context need when start new transfer
typedef struct
{
    ESSATMAC_Context m_OutContext;

    uint16_t m_nTargetSystemType;         // SESTL_SyncFrame::nTargetSystemType
    uint64_t m_nTargetSystemAddress;      // This depends from type of destination, i.e. SESTL_SyncFrame::nTargetSystemType
    uint64_t nTLHostContext;              // SESTL_SyncFrame::nTLHostContext - Host protocol specific
    uint8_t m_nTLHostProtocolID;          // SESTL_Hdr::nTLHostProtocolID
    uint32_t m_nWholeDataSize;            // Payload packet size
    uint32_t m_nMaxBurstDataSize;         // Set to 0xFFFFFFFF if not used
} STLSendContext;

// Interface between ESTL_Drv and ESTL_Sender
typedef void (*OnESTLS_SendCompletedSnd_t)(uint8_t nTLHostProtocolID, uint64_t nTLHostContext, uint32_t nSessionTransfSize, uint32_t nTotalTransfSize, uint8_t nTLError);
typedef uint8_t (*OnESTLS_GetDataChunkSnd_t)(uint8_t nTLHostProtocolID, uint64_t nTLHostContext, uint32_t nStartOffset, uint32_t nSize, uint8_t** ppData, uint32_t* pnMaxChunkSize);

typedef struct
{
    OnESTLS_SendCompletedSnd_t OnSendCompleted;
    OnESTLS_GetDataChunkSnd_t OnGetDataChunk;
    ESSA_pTL_SendFrame_t SendFrame;
} SESTL_SenderIntf;

//-----------------------------------------------------------------------------------------------------------------------
// Interface

// Interface functions
void ESTL_Sender_Init(SESTL_SenderIntf* pDrvIntf);
void ESTL_Sender_Task();
void ESTL_Sender_OnTL_Packet(const ESSATMAC_Context *pMACContext, SESTL_Hdr *pTLHdr, uint16_t nPktSize);       // Called on new packet from MAC layer
void ESTL_Sender_OnTL_MACSendFrameResult(uint32_t nMACFrameID, ESSATMAC_ErrCodes nMACError);

// Start or restart transfer
// nTargetSystemType from SESTL_SyncFrame::nTargetSystemType
void ESTL_Sender_StartTransfer(STLSendContext *pSendContext);

#endif // __ESTL_SENDER_H__
