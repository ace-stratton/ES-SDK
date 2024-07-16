/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _CP_SX_BAND_COMMANDS_H_
#define _CP_SX_BAND_COMMANDS_H_

/**
 * @addtogroup cp
 * @{
 *
 * @file    CP_SX_Band_Commands.h
 * @brief   Command Protocol S/X Band commands declarations
 *
 * @}
 */

#include "CP_Handler.h"
/**
 * @brief Send the CP commands received from the GS to the SX Band
 *
 * @param[in/out] psDispCtx dispatcher context structure providing information on the received input data buffers
 *                          and output buffers allocated for the command response
 * @return result of the command execution
 */
eCPDispatchResult_t CPCmdHandler_SXBand_GwSendCmd(sCPDispatchContext_t * const psDispCtx);

#if defined(SXBAND_SCHEDULER_ENABLED)
/**
 * @brief Executes an SXBand command sequence using a schedule file encoded in the CP buffer
 *
 * The command writes the buffer content to a file with a user-specified name and then triggers the sxband_sched service
 * to execute the command sequence. The command will immediately confirm the starting of the schedule and the result will be
 * provided via polling with a separate command because the command schedule may take longer to execute than the configured
 * GS timeouts, thus losing the actual status of the operation.
 *
 * @param[in/out] psDispCtx dispatcher context structure providing information on the received input data buffers
 *                          and output buffers allocated for the command response
 * @return result of the command execution
 */
eCPDispatchResult_t CPCmdHandler_SXBand_Sched_Run(sCPDispatchContext_t * const psDispCtx);

/**
 * @brief Polls the status of the last SXBand scheduler sequence executed via CP command
 *
 * @param[in/out] psDispCtx dispatcher context structure providing information on the received input data buffers
 *                          and output buffers allocated for the command response
 * @return result of the command execution
 */
eCPDispatchResult_t CPCmdHandler_SXBand_Sched_Poll(sCPDispatchContext_t * const psDispCtx);
#endif // #if defined(SXBAND_SCHEDULER_ENABLED)

#endif // _CP_SX_BAND_COMMANDS_H_
