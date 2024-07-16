/*!
********************************************************************************************
* @file FP_gnssProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface gnss v1.0
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

#ifndef __FP_GNSSPROTOCOLSERVER_H__
#define __FP_GNSSPROTOCOLSERVER_H__

#include "FP_gnssProtocolTypes.h"

typedef void (*pfgnss_set_powerRequestHandler_t)(ReqContext_t *ctx, gnssset_powerRequestData_t *pRequestData);
typedef void (*pfgnss_get_powerRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfgnss_set_powerRequestHandler_t gnss_set_powerRequestHandler;
    pfgnss_get_powerRequestHandler_t gnss_get_powerRequestHandler;
} gnss_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_gnssProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void gnss_registerServerApi(gnss_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_gnssProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t gnss_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes gnss_set_powerResp(
                RespContext_t* ctx,
                const GNSS_operation_t eOp_status
);

ESSATMAC_ErrCodes gnss_get_powerResp(
                RespContext_t* ctx,
                const GNSS_operation_t eOp_status,
                const GNSS_power_t ePwr_status
);


#endif  // #ifndef __FP_GNSSPROTOCOLSERVER_H__
