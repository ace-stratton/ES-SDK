/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
  * @addtogroup service_beacons
  * @{
  *
  * @file beacons_sink_uhf.h
  *
  * @brief Beacons UHF sink public interface
  *
  * The interface provides the callbacks used by the ESPS UHF FP client application.
  *
  * @}
  */

#ifndef __IF_BEACONS_SINK_UHF_H__
#define __IF_BEACONS_SINK_UHF_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "fp/UHF/v0.2/FP_UHFProtocolTypes.h"

/** @brief UHF FP client application response callback
 *
 * @param pRespCtx ESPS stack-specific addressing information
 * @param p_resp_data Status of the send operation as provided by the UHF module
*/
void beacons_sink_uhf_send_status_cbk(RespContext_t* pRespCtx,
									  const UHFExBeaconSetSendResponseData_t * const p_resp_data);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __IF_BEACONS_SINK_UHF_H__
