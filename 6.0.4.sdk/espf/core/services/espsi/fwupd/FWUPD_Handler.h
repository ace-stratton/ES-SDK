/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Services
 * @{
 *
 * @addtogroup ESPS_I
 * @{
 *
 * @defgroup fwupd Firmware Update
 * @{
 *
 * Service to handle the Firmware Update from the ESPS I Stack
 *
 * @file FWUPD_Handler.h
 * @brief FWUPD handler declarations
 *
 * @}
 * @}
 * @}
 *
 */

#ifndef TPLAYER_FWUPD_HANDLER_H_
#define TPLAYER_FWUPD_HANDLER_H_

#include <stdint.h>
#include "ESPLATFORM_NETWORK_STACK/ES_FW_UPD_CB_INTF/ESFWUPD_ModDrv.h"
#include "ESTL_UserDeclarations.h"

/**
 * @brief Initialize the FWUPD relevant functions from the ESPS I Stack
 */
void FWUPD_Handler_Init(void);

#endif /* TPLAYER_FWUPD_HANDLER_H_ */
