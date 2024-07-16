/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TPLAYER_FWUPD_HANDLER_CFG_H_
#define TPLAYER_FWUPD_HANDLER_CFG_H_

/**
 * @addtogroup fwupd
 * @{
 *
 * @file    FWUPD_Handler_Cfg.h
 * @brief   FWUPD Hnalder configuration
 *
 * @}
 */

#include <stdbool.h>
#include "ESPLATFORM_NETWORK_STACK/ES_FW_UPD/ESFWUPD_ModDrv.h"
#include "ESPLATFORM_COMMON/ESSAT_ModuleTypes.h"
#include "FWUPD_Persistor.h"

// Defines used for the SESSoftwareUPD_Bundle header values
#define FW_OBC_MODULE_TYPE1               ESPCMT_UNKNOWN
#define FW_OBC_MODULE_TYPE2               ESPCMT_OBC2
// SUBMODULE_SELF --> OBC update image
#define FW_OBC_SUBMODULE_SELF             (0U)
// SUBMODULE_FILE --> OBC upload file
#define FW_OBC_SUBMODULE_FILE             (2U)

bool FWUPD_Handler_Cfg_HandleTransferComplete(sTransferInfo_t * const pTransferInfo,
                                              const uint64_t u64ActiveTransferId,
                                              const char * const pFileName);

#endif /* TPLAYER_FWUPD_HANDLER_CFG_H_ */
