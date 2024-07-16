/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CP_CMD_HANDLER_H
#define CP_CMD_HANDLER_H

/**
 * @addtogroup cp
 * @{
 *
 * @file    cp_cmd_handler.h
 * @brief   Command Protocol commands declarations
 *
 * @}
 */
#include <stdint.h>
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_Stack.h"
#include "ESPLATFORM_NETWORK_STACK/ES_CP/ESCP_ModDrv.h"
#include "CP_Handler.h"

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL TYPES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/

/**
 * @brief Initialize the CP Handler commands (doing nothin currently)
 */
void cp_cmd_handler_init(void);

/**
 * @brief Send an FP command to the queue to be transmitted
 * @param [in] p_mac_ctx pointer to the ESPS context
 * @param [in] p_msg_data buffer with the message data
 * @param [in] msg_data_sz size of the data buffer
 *
 * @return ESPS operation result
 */
ESSATMAC_ErrCodes cp_cmd_handler_mac_fp_gw_enq_message(ESSATMAC_Context *p_mac_ctx, uint8_t *p_msg_data, uint8_t msg_data_sz);

/**
 * @brief Called by the ESSA Stack when the FP layer replies back to the received CP request
 * @param [in] p_disp_ctx pointer to the dispatch context
 *
 * @return CP dispatcher operation result
 */
eCPDispatchResult_t cp_cmd_handler_mac_fp_gw_send_cmd(sCPDispatchContext_t *const p_disp_ctx);

/**
 * @brief Send a command to the CUBE ADCS computer
 * @param [in] p_disp_ctx pointer to the dispatch context
 *
 * @return CP dispatcher operation result
 */
eCPDispatchResult_t cp_cmd_handler_cubeadcs_gw_send_cmd(sCPDispatchContext_t *const p_disp_ctx);

/**
 * @brief Handles a download file request
 * @param [in] p_disp_ctx pointer to the dispatch context
 *
 * @return CP dispatcher operation result
 */
eCPDispatchResult_t cp_cmd_handler_download_file(sCPDispatchContext_t *const psDispCtx);

#endif /* CP_CMD_HANDLER_H */
