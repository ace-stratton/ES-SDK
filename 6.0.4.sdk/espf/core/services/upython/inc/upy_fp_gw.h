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
 * @defgroup upython
 * @{
 *
 * @file upy_fp_gw.h
 * @brief upython fp command gateway interface file
 *
 * @}
 * @}
 */
#ifndef UPYTHON_FP_GW_H_
#define UPYTHON_FP_GW_H_

#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_Stack.h"
#include "CP_Handler.h"

#define MICROPYTHON_GW_IF_ID   (ESSASNI_PAY_PRI)
#define UPYFPGW_RESPONSE_TIMEOUT_MS     ((uint32_t) 4000)

//
//
// MicroPython FP gateway
//
ESSATMAC_ErrCodes upy_fp_gw_enq_message(ESSATMAC_Context *pMACContext, uint8_t *pMsgData, uint8_t nMsgDataSize);
eCPDispatchResult_t upy_fp_gw_send_cmd(uint8_t *pMsgData, uint8_t nMsgDataSize, uint8_t *pRespBuff, uint8_t nRespBuffSize, uint8_t *const u8TLError);

#endif /*UPYTHON_FP_GW_H_*/
/***end of file***/
