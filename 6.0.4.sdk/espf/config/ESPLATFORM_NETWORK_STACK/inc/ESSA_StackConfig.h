/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __ESSA_STACKCONFIG_H__
#define __ESSA_STACKCONFIG_H__

/**
 * @addtogroup ESPS_I
 * @{
 *
 * @file    ESSA_Stack_Config.h
 * @brief   ESPS Stack protocols configuration
 *
 * @}
 */

#include "ESPLATFORM_NETWORK_STACK/ES_SAT_MAC/ES_SAT_MAC.h"
#include "core/middlewares/ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_FP.h"
#include "cp/cp_cmd_handler.h"
#include "ESSA_CommonUtils.h"
#include "FreeRTOS.h"

#include "esps_drv.h"

#define ESSA_USE_TRANSPORT_LAYER_PROTOCOL

#define FS_PROTOCOL_HANDLERS_LIST                                                           \
    &g_ServiceProtocolCbks,                                                             	\
    &g_MACTestProtocolCbks,                                                                 \
    &g_TL_BridgeDriverProtocolCbks,                                                         \
	&FP_ProtocolServerInfo,																	\

// General Enable/Disable of internal MAC network channels
#define ESSA_SYS_PRI_ENABLED
//#define ESSA_SYS_SEC_ENABLED
//#define ESSA_PAY_PRI_ENABLED
//#define ESSA_PAY_SEC_ENABLED

// Tune for service protocol
#define ESSASP_TickGet16                    ESSA_CommonUtils_getTickU16
#define ESSASP_ASSERT                       CRIT_ASSERT

void ESSA_StackConfig_Init(void);

#endif  // __ESSA_STACKCONFIG_H__
