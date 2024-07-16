#ifndef __ESFWUPD_MOD_DRV_H__
#define __ESFWUPD_MOD_DRV_H__

#include "../ES_TL_LAYER/ES_TL_Layer.h"
#include "../ES_TL_LAYER/ESTL_Drv.h"
#include "ES_FileTransport_Layer.h"
#include "App_UpdateHeader.h"

//-----------------------------------------------------------------------------------------------------------------------
// Types

typedef uint8_t* (*ESFWUPD_RequestBundleBuffer_t)(uint32_t *pBuffSize);
typedef uint8_t (*ESFWUPD_CheckFirmwareBundle_t)(SESSoftwareUPD_Bundle *pBundle, uint32_t nPktSize);
typedef void (*ESFWUPD_GoFirmwareUpdate_t)(SESSoftwareUPD_Bundle *pBundle, uint32_t nPktSize);

// Interface structure to upper layer update handler
typedef struct
{
    ESFWUPD_RequestBundleBuffer_t OnRequestBundleBuffer; // Pointer to reusable buffer (most commonly address of update storage partition)
    ESFWUPD_CheckFirmwareBundle_t OnCheckFirmwareBundle; // Called on new update bundle received, return SESUL_UPLE_SUCCESS if bundle is ok
    ESFWUPD_GoFirmwareUpdate_t OnGoFirmwareUpdate;
} SESFWUPDHandlerIntf;


//-----------------------------------------------------------------------------------------------------------------------
// Interface

void ESFWUPD_ModDrv_GetInterface(ESTL_SHostLayerItem* pIntf);

void ESFWUPD_ModDrv_Init(SESFWUPDHandlerIntf *pHostHandler, bool bAfterReset);
void ESFWUPD_ModDrv_Task();
void ESFWUPD_ModDrv_SetUpdateError(uint8_t nUpdErr);

#endif // __ESFWUPD_MOD_DRV_H__
