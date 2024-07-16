#ifndef __ESFWUPD_MOD_DRV_H__
#define __ESFWUPD_MOD_DRV_H__

#include "../ES_TL_LAYER/ES_TL_Layer.h"
#include "../ES_TL_LAYER/ESTL_Drv.h"
#include "../ES_FW_UPD/ES_FileTransport_Layer.h"
#include "../ES_FW_UPD/App_UpdateHeader.h"

//-----------------------------------------------------------------------------------------------------------------------
// Types

typedef struct
{
    OnESTLR_NewChunk_t OnNewChunk;
    uint64_t nPartialReceivedSize;
} ESFWUPD_CB_ReqCallbackRet_t;

typedef ESFWUPD_CB_ReqCallbackRet_t (*ESFWUPD_CB_RequestBundleCallback_t)(uint64_t* pPacketNumber);
typedef uint8_t (*ESFWUPD_CB_CheckFirmwareBundle_t)(uint32_t nPktSize);
typedef void (*ESFWUPD_CB_GoFirmwareUpdate_t)(uint32_t nPktSize);

// Interface structure to upper layer update handler
typedef struct
{
    ESFWUPD_CB_RequestBundleCallback_t OnRequestBundleCallback; // Pointer to callback function for each newly received data chunk
    ESFWUPD_CB_CheckFirmwareBundle_t OnCheckFirmwareBundle;     // Called on new update bundle received, return SESUL_UPLE_SUCCESS if bundle is ok
    ESFWUPD_CB_GoFirmwareUpdate_t OnGoFirmwareUpdate;
} SESFWUPD_CB_HandlerIntf;


//-----------------------------------------------------------------------------------------------------------------------
// Interface

void ESFWUPD_ModDrv_GetInterface(ESTL_SHostLayerItem* pIntf);

void ESFWUPD_ModDrv_Init(SESFWUPD_CB_HandlerIntf *pHostHandler, bool bAfterReset);
void ESFWUPD_ModDrv_Task();
void ESFWUPD_ModDrv_SetUpdateError(uint8_t nUpdErr);

#endif // __ESFWUPD_MOD_DRV_H__
