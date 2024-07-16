/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef SBAND_TMTC_H_
#define SBAND_TMTC_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup sband_tmtc S Band TMTC
 * @{
 *
 * Interact with the Endurosat [S Band TMTC
 * module](https://endurosat.com/cubesat-store/cubesat-communication-modules/s-band-transceiver/).
 * This module is connected to the OBC using the RS-485 bus and the ESPS I protocol.
 *
 * ### Usage
 * OBC monitors that the SBand TMTC is active by requesting its uptime through the ESPS I bus.
 * using the FP function `SBAND_TMTC_ReadUpTimeReq`.
 *
 * Whenever a response arrives, the callback from the ESPS FP is called (`sband_tmtc_uptime_response_handler`)
 * and the status of the SBand can be checked by calling `sband_tmtc_is_active`.
 *
 * ### FP commands
 * This module enables access to all the Function Protocol commands generated for the
 * S Band TMTC @see FP_SBAND_TMTCProtocolClient.h
 *
 * @file     sband_tmtc.h
 *
 * @brief    Driver for EnduroSat S Band TMTC
 *
 * @}
 * @}
 *
 */

#include "fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCProtocolTypes.h"

/** @brief Initialize the S Band drivers and monitoring task
 */
void sband_tmtc_init(void);

/** @brief Check whether the S Band TMTC module active
 *
 *  @retval false: the monitoring task has not received response
 *  @retval true: S Band is active and responding the monitoring task
 */
bool sband_tmtc_is_active(void);

/** @brief Check whether the S Band TMTC module active
 *
 * @param resp_ctx      ESPS FP context
 * @param response_data contents of the response from the S Band TMTC
 */
void sband_tmtc_uptime_response_handler(
        const RespContext_t* const resp_ctx,
        const SBAND_TMTCReadUpTimeResponseData_t* const response_data
);


#endif /* SBAND_TMTC_H_ */
