#ifndef __ESTL_DRV_H__
#define __ESTL_DRV_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main GS Transport protocols header file, need to be included on every GS Protocol driver!
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Standard C headers
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Following file must exist in every project, here user declarations can be made.
// If no need of additional declarations, create empty one.
#include "ESTL_UserDeclarations.h"

// GS protocol headers
#include "ES_TL_Layer.h"

#include "../ES_SAT_API/include/ESSA_BridgeDrv.h"
#include "ESTL_Sender.h"
#include "ESTL_Receiver.h"

//------------------------------------------------------------------------------------------------------------
// Macros

#ifndef ASSERT
#   define ASSERT(exp)                                  \
        if(!(exp))                                      \
            if(ESTL_Drv_GetHostIntf()->OnException)     \
                ESTL_Drv_GetHostIntf()->OnException((uint16_t) CESTL_EXEPT_FILE_ID, __LINE__);
#endif
#ifndef ASSERT_DBG
#   define ASSERT_DBG(exp)                              \
        if(!(exp))                                      \
            if(ESTL_Drv_GetHostIntf()->OnNotification)  \
                ESTL_Drv_GetHostIntf()->OnNotification((uint16_t) CESTL_EXEPT_FILE_ID, __LINE__);
#endif

#ifndef static_assert
#   define static_assert(...)
#endif
#ifndef NULL
#   define NULL (void *) 0
#endif

// 32 bit platform tend to calc in 32 bit values, 64 bit to 64
// So use these for timeout measurement :
#define IS_TIMER_ELAPSED_16(start_tmr, timeoutval)      (((ESTL_Drv_GetHostIntf()->TickGet16() - start_tmr) & 0xFFFF) > (timeoutval))
#define IS_TIMER_ELAPSED_32(start_tmr, timeoutval)      (((ESTL_Drv_GetHostIntf()->TickGet32() - start_tmr) & 0xFFFFFFFF) > (timeoutval))

//------------------------------------------------------------------------------------------------------------
// Types

// Enum with unique file ID for each driver module source files
// used from exceptions, to be able to identify in which file the exceptions is occurred.
// If new file is created, entry has to be added in this enum.
typedef enum
{
    ESTL_Unknown_FileID = 0,
    ESTL_Drv_FileID,
    ESTL_Bridge_Drv_FileID,
    ESTL_Sender_FileID,
    ESTL_Receiver_FileID,
    ESCP_ModDrv_FileID,
    ESCCP_ModDrv_FileID,
    ESFWUPD_ModDrv_FileID,
    ESHS_ModDrv_FileID,
    ESTL_Utils_FileID
} EESTL_FileID;

// Interface structure for host module
typedef uint16_t (*ESTL_TickGet16_t)();
typedef uint32_t (*ESTL_TickGet32_t)();
typedef void (*ESTL_OnException_t)(uint16_t nFileID, uint16_t nLine);

typedef struct
{
    // Module MAC address
    uint8_t nMacAddress;

    // Timer functions
    ESTL_TickGet16_t TickGet16;
    ESTL_TickGet32_t TickGet32;

    // Exceptions
    ESTL_OnException_t OnException;
    ESTL_OnException_t OnNotification;

} ESTL_TL_HostIntf;

// Interface structure to for upper layer item

typedef void (*OnESTLR_DataFrameReceived_t)();
typedef void (*OnESTLR_DataProgress_t)(uint32_t nWholePacketSize, uint32_t nReceivedSize);
typedef uint8_t (*OnESTLR_GetBufferOnNewPacket_t)(STLReceiveBufferContext *pReceiveBufferContext);
typedef void (*OnESTLR_PacketReceiveCompleted_t)(uint8_t nTLHostProtocolID, uint32_t nPacketSize, const ESSATMAC_Context *pMACContext);
typedef void (*OnESTLS_SendCompleted_t)(uint64_t nTLHostContext, uint32_t nSessionTransfSize, uint32_t nTotalTransfSize, uint8_t nTLError);                  // Send was failed, but partial data may pass through
typedef uint8_t (*OnESTLS_GetDataChunk_t)(uint64_t nTLHostContext, uint32_t nStartOffset, uint32_t nSize, uint8_t **ppData, uint32_t* pnMaxChunkSize);

typedef struct
{
    uint8_t nTLHostProtocol;
    OnESTLR_DataFrameReceived_t OnESTLR_DataFrameReceived;
    OnESTLR_DataProgress_t OnESTLR_DataProgress;
    OnESTLR_GetBufferOnNewPacket_t OnESTLR_GetBufferOnNewPacket;        // Return TL Error
    OnESTLR_PacketReceiveCompleted_t OnESTLR_PacketReceiveCompleted;

    // Sender notifications
    OnESTLS_SendCompleted_t OnESTLS_SendCompleted;
    OnESTLS_GetDataChunk_t OnESTLS_GetDataChunk;

} ESTL_SHostLayerItem;

typedef void (*HostLayerHandler)(uint8_t index, ESTL_SHostLayerItem* item);
//------------------------------------------------------------------------------------------------------------
// Module interface
uint8_t ESTL_Drv_MACToTLError(ESSATMAC_ErrCodes nMACError);
uint16_t ESTL_Drv_GetGenPurpBuff(uint8_t** ppBuff);

void ESTL_Drv_Init(ESTL_TL_HostIntf* pIntf, bool bAfterReset);
ESTL_TL_HostIntf* ESTL_Drv_GetHostIntf();
void ESTL_Drv_AddHostLayer(ESTL_SHostLayerItem* pItem);
void ESTL_Drv_Task();
void ESTL_Get_HostLayers(HostLayerHandler visitor);

#endif // __ESTL_DRV_H__
