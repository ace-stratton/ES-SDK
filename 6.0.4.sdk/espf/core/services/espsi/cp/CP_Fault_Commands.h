/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CP_FAULT_COMMANDS_H
#define CP_FAULT_COMMANDS_H

#include "CP_Handler.h"

/** @brief A CP command handler to read all stored HW stack exception frames from NVM
 *  @parma[in/out] psDispCtx command dispatcher context
 * */
eCPDispatchResult_t cp_fault_commands_read_all_faults(sCPDispatchContext_t * const psDispCtx);

#endif /* CP_FAULT_COMMANDS_H */
