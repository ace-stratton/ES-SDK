#ifndef __ESCP_MOD_DRV_H__
#define __ESCP_MOD_DRV_H__

#include "../ES_TL_LAYER/ESTL_Drv.h"

//-----------------------------------------------------------------------------------------------------------------------
// Defines

#define ESTL_CP_BEGIN_COMMAND_MAP()                                         \
static ESCP_SCommandHandlerItem m_Commands[] = {
#define ESTL_CP_REGISTER_COMMAND(commandID, CmdReceivedCbk, CmdCancelCbk)   \
    {                                                                       \
        .nCmdType = commandID,                                              \
        .OnESCP_CommandReceived = CmdReceivedCbk,                           \
        .OnESCP_CmdCancelRequest = CmdCancelCbk                             \
    },
#define ESTL_CP_END_COMMAND_MAP() };
#define ESTL_CP_GET_CMDENTRIES()		m_Commands
#define ESTL_CP_GET_CMDENTRIESCOUNT()	COUNT_OF(m_Commands)

//-----------------------------------------------------------------------------------------------------------------------
// Types

typedef void (*OnESCP_CommandReceived_t)(uint64_t nCmdID, uint32_t nCmdType, uint8_t *pCMDPkt, uint32_t nCMDPktSize);
typedef void (*OnESCP_CmdCancelRequest_t)(uint64_t nCmdID, uint32_t nCmdType);

// Interface structure to for upper layer item
typedef struct
{
    uint32_t nCmdType;
    OnESCP_CommandReceived_t OnESCP_CommandReceived;
    OnESCP_CmdCancelRequest_t OnESCP_CmdCancelRequest; // Call PrepareSimpleResult(EESTL_SFERR_CMD_CANCELLED)
} ESCP_SCommandHandlerItem;

// return EESTL_SFERR_SUCCESS on success or other
typedef uint8_t (*OnESCP_RequestCommandChunk_t)(const uint64_t nCmdID, const uint32_t nCmdType,
                                                const uint32_t nRequiredChunkSize, const uint32_t nOffset, uint8_t* pChunk);

// ModDrv configuration structure
typedef struct
{
	const ESCP_SCommandHandlerItem *pCommands;
	uint16_t nCommandsCount;
	uint8_t *pIN_CMDBuffer;
	uint32_t IN_CMDBufferSize;
	uint8_t *pOUT_CMDBuffer;
	uint32_t OUT_CMDBufferSize;
} ESCP_ModDrvConfig;

// Module states
typedef enum
{
    CESCPS_FREE = 0,
    CESCPS_PENDING,
    CESCPS_WAIT_SEND_RESULT
} EESCP_State;

//-----------------------------------------------------------------------------------------------------------------------
// Interface
void ESCP_ModDrv_GetInterface(ESTL_SHostLayerItem* pIntf);

void ESCP_ModDrv_Init(bool bAfterReset, ESCP_ModDrvConfig * const pUserConfig);
void ESCP_ModDrv_Task();

// Start actual transfer, on request from server
void ESCP_ModDrv_DoStartSendingResult(const ESSATMAC_Context *pReqMACInContext, uint64_t nCmdID, uint16_t nDownLinkIntf, uint32_t nMaxBurstSize);
// Received through CCP protocol in separate buffer
void ESCP_ModDrv_OnCancelRequest(uint32_t nCmdType, uint64_t nCmdID);

void ESCP_ModDrv_GetPendingCommand(uint64_t *pnCmdID, uint32_t *pnCmdType, uint8_t **ppCMDPkt, uint32_t *pnCMDPktSize);
uint8_t* ESCP_ModDrv_GetResultBuffer(uint32_t *pnBufferSize);
void ESCP_ModDrv_PrepareSimpleResult(uint8_t nTLError);
void ESCP_ModDrv_PrepareResult(uint32_t nCMDResultSize, uint8_t nTLError);
void ESCP_ModDrv_PrepareResultOnChunks(uint32_t nCMDResultSize, uint8_t nTLError, OnESCP_RequestCommandChunk_t pfOnNewChunk);
void ESCP_ModDrv_CalcBlockCRC(uint8_t* pBlock, uint32_t nBlockSize, bool bFirstBlock);
void ESCP_ModDrv_GetCmdStatus(uint64_t* pnCmdID, EESCP_State* pnCMDState);

#endif // __ESCP_MOD_DRV_H__
