/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_gw.c
 * @brief    Gateway for accessing the API of CubeADCS Gen2. File is partially generated!
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "../inc/cubeadcs_gen2_gw.h"
#include "cubeObc/arch/cubeObc_critical.h"
#include "es_cdef.h"


/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

/**
 * @brief Gain exclusive access to the CubeADCS Gen2 API.
 */
static inline bool cubeadcs_gen2_crit_section_start(const uint32_t timeout)
{
    return cubeObc_critical_enter(timeout);
}

/**
 * @brief Relinquish exclusive access to the CubeADCS Gen2 API.
 */
static inline void cubeadcs_gen2_crit_section_end(void)
{
    cubeObc_critical_exit();
}

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void cubeadcs_gen2_setup_endpoint(TypeDef_TctlmEndpoint* const p_endpoint,
                                  const TypeDef_CommsEndpointType endpoint_type,
                                  const U32 timeout)
{
    if (p_endpoint != NULL)
    {
        // OBC communicates directly only with the CubeComputer node.
        p_endpoint->nodeType = TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER;
        p_endpoint->type = endpoint_type;
        p_endpoint->addr = 0;
        p_endpoint->addrPass = 0;
        p_endpoint->timeout = timeout;
        p_endpoint->passthrough = FALSE;

    }
}


ErrorCode cubeadcs_gen2_setup_passthrough(TypeDef_TctlmEndpoint* const p_endpoint,
                                    const TctlmCommonFrameworkEnums_AbstractNode node_id)
{
    ErrorCode result = CUBEOBC_ERROR_TODO;

    if (    (node_id != TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_INVALID)
         && (node_id != TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER))
    {
        if (p_endpoint != NULL)
        {
            // Do not allow the endpoint to be used for pass-through communication unless the target node is successfully set.
            p_endpoint->passthrough = FALSE;
            // Command CubeADCS to set a target node for pass-through communication.
            result = tctlmCubeComputerCommon3_setPassThrough(p_endpoint, node_id);
            if (result == CUBEOBC_ERROR_OK)
            {
                // Target node successfully set. Enable pass-through communication via the node.
                p_endpoint->passthrough = TRUE;
            }
        }
    }
    else
    {
        // No pass-through is actually requested
        result = CUBEOBC_ERROR_OK;
    }

    return result;
}

// CUBE_ADCS_GEN_SECTION_START
ErrorCode CubeADCS_Gen2_CommonFramework1_setResetRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ResetVal setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_setReset(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_setUnixTimeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_UnixTime* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_setUnixTime(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_setErrorLogIndexRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ErrorLogIndex* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_setErrorLogIndex(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_setErrorLogEntryRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ErrorLogEntry* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_setErrorLogEntry(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_setErrorLogClearRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_setErrorLogClear(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_setErrorLogSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ErrorLogSettings* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_setErrorLogSettings(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_setConfigPersistRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_setConfigPersist(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getIdentificationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_Identification* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getIdentification(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getSerialNumberRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_SerialNumber* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getSerialNumber(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getErrorLogIndexRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ErrorLogIndex* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getErrorLogIndex(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getErrorLogEntryRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ErrorLogEntry* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getErrorLogEntry(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getErrorLogSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ErrorLogSettings* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getErrorLogSettings(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getUnixTimeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_UnixTime* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getUnixTime(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getConfigPersistDiagnosticsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_ConfigPersistDiagnostics* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getConfigPersistDiagnostics(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getCommsStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_CommsStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getCommsStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getVersionRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_Version* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getVersion(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getBootStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_BootStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getBootStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getTelecommandAcknowledgeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_TelecommandAcknowledge* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getTelecommandAcknowledge(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonFramework1_getCommonErrorCodesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFramework1_CommonErrorCodes* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonFramework1_getCommonErrorCodes(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonTransfer1_setTransferFrameRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U16 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonTransfer1_setTransferFrame(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonTransfer1_setFrameRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonTransfer1_Frame* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonTransfer1_setFrame(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonTransfer1_getFrameInfoRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonTransfer1_FrameInfo* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonTransfer1_getFrameInfo(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CommonTransfer1_getFrameRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonTransfer1_Frame* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCommonTransfer1_getFrame(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_ResetVal setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setReset(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setHaltRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setHalt(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_Config* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setConfig(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setDefaultAppTargetRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setDefaultAppTarget(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultAppRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setJumpToDefaultApp(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAppRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setJumpToApp(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAddressRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setJumpToAddress(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetFileInfoIdxRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setResetFileInfoIdx(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteFileSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setWriteFileSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setDeleteFileEntryRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setDeleteFileEntry(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteMemorySetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_WriteMemorySetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setWriteMemorySetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setReadMemorySetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_ReadMemorySetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setReadMemorySetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setEraseMemorySetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_EraseMemorySetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setEraseMemorySetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setOptionBytesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_OptionBytes* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setOptionBytes(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_setCommitOptionBytesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_setCommitOptionBytes(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getIdentificationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_Identification* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getIdentification(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getSerialNumberRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_SerialNumber* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getSerialNumber(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_Config* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getConfig(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_State* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getState(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getErrorsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_Errors* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getErrors(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getFileInfoRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_FileInfo* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getFileInfo(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getDefaultAppTargetRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getDefaultAppTarget(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getOptionBytesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_OptionBytes* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getOptionBytes(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getCommsStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_CommsStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getCommsStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeCommonBaseBootloader5_getTelecommandAcknowledgeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeCommonBaseBootloader5_TelecommandAcknowledge* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeCommonBaseBootloader5_getTelecommandAcknowledge(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigDefaultModesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigDefaultModes* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigDefaultModes(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMountRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMount* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigMount(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag0OrbitCalRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMag0OrbitCal* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigMag0OrbitCal(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag1OrbitCalRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMag1OrbitCal* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigMag1OrbitCal(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsControllerRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAdcsController* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigAdcsController(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsEstimatorRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAdcsEstimator* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigAdcsEstimator(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsSatelliteRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAdcsSatellite* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigAdcsSatellite(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitSatParamsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigOrbitSatParams* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigOrbitSatParams(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitTargetParamsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigOrbitTargetParams* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigOrbitTargetParams(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigNodeSelectionRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigNodeSelection* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigNodeSelection(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorRwlRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigActuatorRwl* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigActuatorRwl(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorMtqRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigActuatorMtq* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigActuatorMtq(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMagSensingElementRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMagSensingElement* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigMagSensingElement(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAsgp4RequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAsgp4* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConfigAsgp4(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setConModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConMode* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setConMode(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setEstModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_EstMode* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setEstMode(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setOrbModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OrbModeSelect setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setOrbMode(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsRunModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_AdcsRunModeSelect setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setAdcsRunMode(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsOpStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_AdcsOpStateSelect setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setAdcsOpState(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setSimSensorRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_SimSensorRaw* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setSimSensorRaw(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandMtqRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OpenLoopCommandMtq* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setOpenLoopCommandMtq(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandRwlRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OpenLoopCommandRwl* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setOpenLoopCommandRwl(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandHxyzRWRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setOpenLoopCommandHxyzRW(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommandsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ReferenceCommands* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setReferenceCommands(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setStrTctlmInstanceRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_StrInstanceSelect setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setStrTctlmInstance(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setFssTctlmInstanceRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_FssInstanceSelect setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setFssTctlmInstance(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setDeployCommandMagRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_DeployCommandMag* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setDeployCommandMag(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setGnssSensorCmdRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_GnssSensorCmd* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setGnssSensorCmd(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_setFileTransferSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_FileTransferSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_setFileTransferSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigDefaultModesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigDefaultModes* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigDefaultModes(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMountRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMount* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigMount(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag0OrbitCalRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMag0OrbitCal* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigMag0OrbitCal(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag1OrbitCalRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMag1OrbitCal* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigMag1OrbitCal(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsControllerRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAdcsController* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigAdcsController(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsEstimatorRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAdcsEstimator* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigAdcsEstimator(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsSatelliteRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAdcsSatellite* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigAdcsSatellite(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitSatParamsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigOrbitSatParams* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigOrbitSatParams(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitTargetParamsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigOrbitTargetParams* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigOrbitTargetParams(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigNodeSelectionRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigNodeSelection* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigNodeSelection(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorRwlRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigActuatorRwl* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigActuatorRwl(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorMtqRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigActuatorMtq* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigActuatorMtq(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMagSensingElementRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigMagSensingElement* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigMagSensingElement(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAsgp4RequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConfigAsgp4* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConfigAsgp4(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getConModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ConMode* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getConMode(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getEstModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_EstMode* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getEstMode(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getOrbModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OrbModeSelect* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getOrbMode(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsRunModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_AdcsRunModeSelect* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getAdcsRunMode(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsOpStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_AdcsOpStateSelect* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getAdcsOpState(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getSimSensorRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_SimSensorRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getSimSensorRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandMtqRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OpenLoopCommandMtq* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getOpenLoopCommandMtq(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandRwlRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OpenLoopCommandRwl* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getOpenLoopCommandRwl(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandHxyzRWRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getOpenLoopCommandHxyzRW(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommandsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_ReferenceCommands* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getReferenceCommands(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHilRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmHil* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmHil(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExecutionPointRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_AcpExecutionPoint* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmExecutionPoint(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNodeInitStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmNodeInitState* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmNodeInitState(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_FileTransferSetup* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getFileTransferSetup(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_FileTransferStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getFileTransferStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getFileInfoRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_FileInfo* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getFileInfo(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawCssRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorRawCss* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorRawCss(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawMagRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorRawMag* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorRawMag(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawGyroRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorRawGyro* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorRawGyro(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwlRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorRawRwl* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorRawRwl(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalFssRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalFss* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalFss(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalCssRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalCss* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalCss(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalMagRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalMag* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalMag(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGyroRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalGyro* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalGyro(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalHssRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalHss* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalHss(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalStrRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalStr* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalStr(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGnssRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalGnss* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalGnss(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalRwlRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmSensorCalRwl* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmSensorCalRwl(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmModelsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmModels* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmModels(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmEstimatorMain* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmEstimatorMain(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorBackupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmEstimatorBackup* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmEstimatorBackup(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainHighResRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmEstimatorMainHighRes* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmEstimatorMainHighRes(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmControllerRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmController* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmController(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmGnssRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmGnssRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmGnssRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExtSensorRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmExtSensorRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmExtSensorRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmStrPst3sRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmStrPst3sRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmFssCubeSenseSunRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmHssCubeSenseEarthRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmRwlNssRwlRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmRwlNssRwlRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmAcpExecutionRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmAcpExecution* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmAcpExecution(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmTorquerCurrentsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmTorquerCurrents* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmTorquerCurrents(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeComputerHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmCubeComputerHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmCubeComputerHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmFssCubeSenseSunHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmHssCubeSenseEarthHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeMagHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmCubeMagHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmCubeMagHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmRwlHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmRwlHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmStrPst3sHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmStrPst3sHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNssRwlHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmNssRwlHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmNssRwlHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrHealthRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerControlProgram8_TlmStrHealth* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerControlProgram8_getTlmStrHealth(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setPassThroughRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFrameworkEnums_AbstractNode setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setPassThrough(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setPowerStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_PowerState* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setPowerState(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setImageTransferSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_ImageTransferSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setImageTransferSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setImageFileInfoResetRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setImageFileInfoReset(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setPortMapRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_PortMap* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setPortMap(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setEraseLogDataRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_EraseMagicNumbers setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setEraseLogData(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setEventLogFilterTransferSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_EventLogFilterTransferSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setEventLogFilterTransferSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setTelemetryLogTransferSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_TelemetryLogTransferSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setTelemetryLogTransferSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setDummyEventRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_DummyEvent* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setDummyEvent(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedEventSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_UnsolicitedEventSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setUnsolicitedEventSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedTlmSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_UnsolicitedTlmSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_setUnsolicitedTlmSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getPassThroughRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCommonFrameworkEnums_AbstractNode* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getPassThrough(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getPowerStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_PowerState* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getPowerState(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getPortDiagnosticsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_PortDiagnostics* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getPortDiagnostics(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getPortMapRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_PortMap* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getPortMap(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getExpectedNodesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_ExpectedNodes* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getExpectedNodes(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getImageTransferStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_ImageTransferStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getImageTransferStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getImageFileInfoRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_ImageFileInfo* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getImageFileInfo(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getComponentErrorCodesRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_ComponentErrorCodes* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getComponentErrorCodes(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getEventLogStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_EventLogStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getEventLogStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_TelemtryLogStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getTelemtryLogStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedEventSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_UnsolicitedEventSetup* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getUnsolicitedEventSetup(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedTlmSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_UnsolicitedTlmSetup* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getUnsolicitedTlmSetup(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogInclusionMasksRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeComputerCommon3_TelemtryLogInclusionMasks* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeComputerCommon3_getTelemtryLogInclusionMasks(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_setConfigurationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_Configuration* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_setConfiguration(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_setImageTransferSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_ImageTransferSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_setImageTransferSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_setDeadPixelsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_DeadPixels* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_setDeadPixels(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_setRequestDeadPixelRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_setRequestDeadPixel(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementAndTriggerRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_MeasurementAndTrigger* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_getMeasurementAndTrigger(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_Measurement* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_getMeasurement(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementMetadataRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_MeasurementMetadata* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_getMeasurementMetadata(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_getHealthTlmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_HealthTlm* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_getHealthTlm(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_getConfigurationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_Configuration* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_getConfiguration(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_getProfileTimingRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_ProfileTiming* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_getProfileTiming(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeIrControlProgram1_getRequestedDeadPixelRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeIrControlProgram1_RequestedDeadPixel* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeIrControlProgram1_getRequestedDeadPixel(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_MmcConfig* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_setMmcConfig(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_setSamplePrimaryRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_setSamplePrimary(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_setConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_Config* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_setConfig(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcCalibrationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_MmcCalibration* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_setMmcCalibration(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_MmcConfig* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_getMmcConfig(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_State* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_getState(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurement* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_getPrimaryMagMeasurement(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurementRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_getPrimaryMagMeasurementRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagTempRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            F32 tmp_res;
            err = tctlmCubeMagControlProgramCommon1_getPrimaryMagTemp(&endpoint, &tmp_res);
            memcpy(returnVal, &tmp_res, sizeof(F32));
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_Config* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_getConfig(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagDiagnosticsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_PrimaryMagDiagnostics* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_getPrimaryMagDiagnostics(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcCalibrationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCommon1_MmcCalibration* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCommon1_getMmcCalibration(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramCompact1_getHealthTlmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramCompact1_HealthTlm* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramCompact1_getHealthTlm(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_PniConfig* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_setPniConfig(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_setSampleRedRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_setSampleRed(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_MagicDeploy setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_setDeploy(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployArmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_MagicDeployArm setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_setDeployArm(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniCalibrationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_PniCalibration* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_setPniCalibration(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getHealthTlmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_HealthTlm* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_getHealthTlm(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_PniConfig* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_getPniConfig(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_RedMagMeasurement* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_getRedMagMeasurement(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_RedMagMeasurementRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_getRedMagMeasurementRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagTempRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            F32 tmp_res;
            err = tctlmCubeMagControlProgramDeploy1_getRedMagTemp(&endpoint, &tmp_res);
            memcpy(returnVal, &tmp_res, sizeof(F32));
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getDeploymentStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_DeploymentStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_getDeploymentStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagDiagnosticsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_RedMagDiagnostics* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_getRedMagDiagnostics(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniCalibrationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeMagControlProgramDeploy1_PniCalibration* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeMagControlProgramDeploy1_getPniCalibration(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNodeSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_setNodeSvcSettings(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcSettings* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_setNssRwlSvcSettings(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlActiveStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NssRwlActiveState setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_setNssRwlActiveStatus(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlWheelSpeedRefRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_setNssRwlWheelSpeedRef(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlTorqueRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_setNssRwlTorque(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlMotorCurrentRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_setNssRwlMotorCurrent(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSoftwareResetRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_setNssRwlSoftwareReset(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_getNodeSvcSettings(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NodeSvcStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_getNodeSvcStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcSettings* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_getNssRwlSvcSettings(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_getNssRwlSvcStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlWheelSpeedRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            F32 tmp_res;
            err = tctlmCubeNodeControlProgramNssrwl1_getNssRwlWheelSpeed(&endpoint, &tmp_res);
            memcpy(returnVal, &tmp_res, sizeof(F32));
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmStandardRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmStandard* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_getNssRwlTlmStandard(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmExtendedRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmExtended* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_getNssRwlTlmExtended(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmSystemRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmSystem* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramNssrwl1_getNssRwlTlmSystem(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sNumberNavigationStarsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sNumberNavigationStars(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sExposureRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sExposure(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sFourStarSearchThresholdRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sFourStarSearchThreshold(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSecondCalibrationRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sSecondCalibration(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sTrackingModeThresholdRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sTrackingModeThreshold(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sQuaternionFilteringRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sQuaternionFilteringSetState setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sQuaternionFiltering(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSystemResetRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sSystemReset(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sActiveStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sActiveStatus* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sActiveStatus(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sImageFixedThresholdRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sImageFixedThreshold(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sSvcSettings* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sSvcSettings(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setNodeSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setNodeSvcSettings(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sSaaWorkingMode setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sSaaMode(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaThresholdRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sSaaThreshold(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sDynamicModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sDynamicModeEnum setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sDynamicMode(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sEdacOffRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_setPst3sEdacOff(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sSvcStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getPst3sSvcStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sTlmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sTlm* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getPst3sTlm(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sAttitudeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sAttitude* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getPst3sAttitude(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sHousekeepingRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sHousekeeping* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getPst3sHousekeeping(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sConfig* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getPst3sConfig(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_Pst3sSvcSettings* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getPst3sSvcSettings(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcStatusRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeControlProgramPst3s1_NodeSvcStatus* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getNodeSvcStatus(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeControlProgramPst3s1_getNodeSvcSettings(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeCommon1_setPowerSwitchStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeCommon1_SwitchState setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeCommon1_setPowerSwitchState(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeCommon1_getHealthTlmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeCommon1_HealthTlm* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeCommon1_getHealthTlm(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeNodeCommon1_getPowerSwitchStateRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeNodeCommon1_SwitchState* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeNodeCommon1_getPowerSwitchState(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setCamLensDistortionRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_CamLensDistortion* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setCamLensDistortion(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setCaptureDetectRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setCaptureDetect(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setDetectRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setDetect(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setClearOvercurrentFlagsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setClearOvercurrentFlags(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setImageCaptureRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_LocSelection setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setImageCapture(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setImageTransferSetupRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_ImageTransferSetup* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setImageTransferSetup(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setCamBoresightRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_CamBoresight* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setCamBoresight(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setCamMaskRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_CamMask* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setCamMask(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setCamThresholdRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setCamThreshold(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_setDetectionAreaRowSelectRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_setDetectionAreaRowSelect(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsTimestampRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_SensorResultsTimestamp* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getSensorResultsTimestamp(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getCamLensDistortionRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_CamLensDistortion* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getCamLensDistortion(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getCamMasksRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_CamMasks* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getCamMasks(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_SensorResults* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getSensorResults(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultTriggerRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_SensorResultTrigger* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getSensorResultTrigger(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getAutoCamSensorRawRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_AutoCamSensorRaw* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getAutoCamSensorRaw(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getDetectionAreaRowRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, U8* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getDetectionAreaRow(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseControlProgram5_getCamBoresightRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseControlProgram5_CamBoresight* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseControlProgram5_getCamBoresight(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseCommon1_setCamAutoAdjustRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseCommon1_setCamAutoAdjust(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseCommon1_setCamSettingsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseCommon1_CamSettings* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseCommon1_setCamSettings(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseCommon1_getConfigRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseCommon1_Config* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseCommon1_getConfig(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeSenseCommon1_getHealthTlmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeSenseCommon1_HealthTlm* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeSenseCommon1_getHealthTlm(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setWheelSpeedRefRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setWheelSpeedRef(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setWheelDutyRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setWheelDuty(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setBackupWheelModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setBackupWheelMode(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setClearErrorsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setClearErrors(&endpoint);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setMainGainRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_MainGain* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setMainGain(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setBackupGainRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_BackupGain* setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setBackupGain(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setPWMGainRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32 setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setPWMGain(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_setMotorPowerRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean setVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_setMotorPower(&endpoint, setVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getBackupGainRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_BackupGain* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getBackupGain(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getMainGainRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_MainGain* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getMainGain(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getPWMGainRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            F32 tmp_res;
            err = tctlmCubeWheelControlProgram3_getPWMGain(&endpoint, &tmp_res);
            memcpy(returnVal, &tmp_res, sizeof(F32));
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getStatusErrorFlagsRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_StatusErrorFlags* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getStatusErrorFlags(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDataRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_WheelData* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getWheelData(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDutyRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            F32 tmp_res;
            err = tctlmCubeWheelControlProgram3_getWheelDuty(&endpoint, &tmp_res);
            memcpy(returnVal, &tmp_res, sizeof(F32));
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getHealthTlmRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_HealthTlm* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getHealthTlm(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRefRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, F32* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            F32 tmp_res;
            err = tctlmCubeWheelControlProgram3_getWheelSpeedRef(&endpoint, &tmp_res);
            memcpy(returnVal, &tmp_res, sizeof(F32));
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_WheelSpeed* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getWheelSpeed(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getMotorPowerRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getMotorPower(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getControlModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, TctlmCubeWheelControlProgram3_ControlModeVal* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getControlMode(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

ErrorCode CubeADCS_Gen2_CubeWheelControlProgram3_getBackupWheelModeRequestGw(const TctlmCommonFrameworkEnums_AbstractNode nodeId, Boolean* returnVal, const U32 timeout)
{
    ErrorCode err = CUBEADCS_GEN2_CRIT_SECT_ERR;
    TypeDef_TctlmEndpoint endpoint;
    cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);
    if (true == cubeadcs_gen2_crit_section_start(timeout))
    {
        err = cubeadcs_gen2_setup_passthrough(&endpoint, nodeId);
        if (err == CUBEOBC_ERROR_OK)
        {
            err = tctlmCubeWheelControlProgram3_getBackupWheelMode(&endpoint, returnVal);
        }
        cubeadcs_gen2_crit_section_end();
    }
    return err;
}

// CUBE_ADCS_GEN_SECTION_END

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/* ******************************************************************************************* */
