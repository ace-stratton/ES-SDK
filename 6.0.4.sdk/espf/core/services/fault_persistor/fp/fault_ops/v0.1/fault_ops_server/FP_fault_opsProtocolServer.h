/*!
********************************************************************************************
* @file FP_fault_opsProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface fault_ops v0.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __FP_FAULT_OPSPROTOCOLSERVER_H__
#define __FP_FAULT_OPSPROTOCOLSERVER_H__

#include "FP_fault_opsProtocolTypes.h"

typedef void (*pffault_ops_get_fault_infoRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pffault_ops_read_fault_by_index_rawRequestHandler_t)(ReqContext_t *ctx, fault_opsread_fault_by_index_rawRequestData_t *pRequestData);
typedef void (*pffault_ops_clear_all_faultsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pffault_ops_simulate_faultRequestHandler_t)(ReqContext_t *ctx, fault_opssimulate_faultRequestData_t *pRequestData);
typedef void (*pffault_ops_read_fault_by_indexRequestHandler_t)(ReqContext_t *ctx, fault_opsread_fault_by_indexRequestData_t *pRequestData);

typedef struct {
    pffault_ops_get_fault_infoRequestHandler_t fault_ops_get_fault_infoRequestHandler;
    pffault_ops_read_fault_by_index_rawRequestHandler_t fault_ops_read_fault_by_index_rawRequestHandler;
    pffault_ops_clear_all_faultsRequestHandler_t fault_ops_clear_all_faultsRequestHandler;
    pffault_ops_simulate_faultRequestHandler_t fault_ops_simulate_faultRequestHandler;
    pffault_ops_read_fault_by_indexRequestHandler_t fault_ops_read_fault_by_indexRequestHandler;
} fault_ops_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_fault_opsProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void fault_ops_registerServerApi(fault_ops_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_fault_opsProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t fault_ops_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes fault_ops_get_fault_infoResp(
                RespContext_t* ctx,
                const uint8_t u8Occupied_fault_slots,
                const uint8_t u8Available_fault_slots
);

ESSATMAC_ErrCodes fault_ops_read_fault_by_index_rawResp(
                RespContext_t* ctx,
                const bool bIs_data_valid,
                const uint8_t * const au8Exception_data_raw
);

ESSATMAC_ErrCodes fault_ops_clear_all_faultsResp(
                RespContext_t* ctx,
                const bool bIs_clear_ok
);

ESSATMAC_ErrCodes fault_ops_simulate_faultResp(
                RespContext_t* ctx);

ESSATMAC_ErrCodes fault_ops_read_fault_by_indexResp(
                RespContext_t* ctx,
                const bool bIs_data_valid,
                const FAULT_OPS_x_frame_t * const sException_data
);


#endif  // #ifndef __FP_FAULT_OPSPROTOCOLSERVER_H__
