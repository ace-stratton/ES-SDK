/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/** @addtogroup service_beacons
 * @{
 * @file beacons_sink_uhf.c
 *
 * @brief Beacon UHF sink adapter
 *
 * The component is responsible to forward beacon data to UHF over ESPS I.
 * @}
 */

#include <string.h>
#include "if_beacons_sink.h"
#include "assertions.h"
#include "fp/UHF/v0.4/UHF_client/FP_UHFProtocolClient.h"
#include "config/beacons/beacons_cfg_user.h"
#include "config/nvm/inc/nvm_data_types.h"

static uint8_t beacon_id = 0U;

void
beacons_uhf_cmd(const beacons_sink_adapter_cmd_t cmd)
{
    switch (cmd)
    {
        case BEACONS_SINK_ADAPTER_CMD_INIT:
        case BEACONS_SINK_ADAPTER_CMD_START:
        case BEACONS_SINK_ADAPTER_CMD_STOP:
        default:
            {
                break;
            }
    }
}

bool
beacons_uhf_send(uint8_t *const data, const uint8_t size, uint8_t *const p_id)
{
    CRIT_ASSERT(NULL != data);
    CRIT_ASSERT(size > 0U);

    if (NULL != p_id)
        *p_id = beacon_id++;

    ReqContext_t esps_req_ctx = { .nAddr = BEACONS_UHF_SINK_ESPS_ADDRESS,
                                  .nInterfaceNumber = ESSASNI_SYS_PRI,
                                  .netType          = ESSASNETT_INTERNAL };

    UHF_sExBeacon_t bcn_data = { .u8Size =
                                     MIN(size, sizeof(bcn_data.au8Data)) };

    (void)memcpy(bcn_data.au8Data, data, MIN(size, sizeof(bcn_data.au8Data)));

    // fill-up remaining bytes in beacon frame with zeroes
    if (size <= sizeof(bcn_data.au8Data))
        (void)memset(&bcn_data.au8Data[size], INVALID_BEACON_SLOT_ASSIGNMENT,
                     sizeof(bcn_data.au8Data) - size);

    // NOTE: internal seqId from ESPS FP layer cannot be obtained with the
    // current version of the
    //         generators, therefore we use our own beacon_id internally
    ESSATMAC_ErrCodes res = UHF_ExBeaconSetSendReq(&esps_req_ctx, &bcn_data);

    // TODO: replace by false when tests with real UHF are performed
    return (ESSATMAC_EC_OK == res);
}

void
beacons_sink_uhf_send_status_cbk(
    RespContext_t                                *pRespCtx,
    const UHFExBeaconSetSendResponseData_t *const p_resp_data)
{
    CRIT_ASSERT(NULL != pRespCtx);
    CRIT_ASSERT(NULL != p_resp_data);

    beacons_confirm_sink_send(
        beacon_id, (UHF_EESSA_UHFSTATUS_OK == p_resp_data->eOpResult));
}

const beacons_sink_if_t beacons_sink = { .cmd  = &beacons_uhf_cmd,
                                         .send = &beacons_uhf_send };
