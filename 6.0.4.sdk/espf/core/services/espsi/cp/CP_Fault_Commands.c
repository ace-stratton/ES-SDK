/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#include "CP_Fault_Commands.h"
#include "ESCP_CommandsLocalConf.h"
#include "fault_persistor.h"

/** @brief Input arguments for the FAULT READ ALL CP command */
typedef struct
{
    bool clear_storage;     /**< indicates whether the persistent storage shall be cleared after reading */
} cmd_fault_read_all_in_args_t;

eCPDispatchResult_t cp_fault_commands_read_all_faults(sCPDispatchContext_t * const psDispCtx)
{
    eCPDispatchResult_t res = ECPDISPATCHRESULT_ERROR;

    if (CPCmdHandler_IsDispContextValid(psDispCtx, CP_CMD_FAULT_READ_ALL))
    {
        if (psDispCtx->u32CmdDataSize >= sizeof(cmd_fault_read_all_in_args_t))
        {
            cmd_fault_read_all_in_args_t *p_cmd_in_args = (cmd_fault_read_all_in_args_t *) psDispCtx->pu8CmdData;

            fault_persistor_read_all(psDispCtx->pu8ResponseBuf, psDispCtx->u32ResponseBufSize, &psDispCtx->u32ResponseActualSize);

            if (0U == psDispCtx->u32ResponseActualSize)
            {
                (void) memset(psDispCtx->pu8ResponseBuf, 0U, psDispCtx->u32ResponseBufSize);
            }

            if (p_cmd_in_args->clear_storage)
            {
                fault_persistor_clear();
            }

            psDispCtx->u8TLError = EESTL_SFERR_SUCCESS;
        }
        else
        {
            psDispCtx->u32ResponseActualSize = 0U;
            psDispCtx->u8TLError = EESTL_SFERR_BAD_CMD_PARAMS;
        }

        res = ECPDISPATCHRESULT_RESULT_OK;
    }

    return res;
}



