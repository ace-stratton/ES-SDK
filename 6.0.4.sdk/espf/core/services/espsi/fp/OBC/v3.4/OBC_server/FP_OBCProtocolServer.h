/*!
********************************************************************************************
* @file FP_OBCProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface OBC v3.4
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

#ifndef __FP_OBCPROTOCOLSERVER_H__
#define __FP_OBCPROTOCOLSERVER_H__

#include "FP_OBCProtocolTypes.h"

typedef void (*pfOBC_getGpOutputStatesRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_setGpOutputStateRequestHandler_t)(ReqContext_t *ctx, OBCsetGpOutputStateRequestData_t *pRequestData);
typedef void (*pfOBC_getI2CPullUpsStateRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_setI2CPullUpsStateRequestHandler_t)(ReqContext_t *ctx, OBCsetI2CPullUpsStateRequestData_t *pRequestData);
typedef void (*pfOBC_get_uptimeRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_getResetCountersRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_clearResetCounterRequestHandler_t)(ReqContext_t *ctx, OBCclearResetCounterRequestData_t *pRequestData);
typedef void (*pfOBC_triggerResetInModeRequestHandler_t)(ReqContext_t *ctx, OBCtriggerResetInModeRequestData_t *pRequestData);
typedef void (*pfOBC_set_device_mac_addressRequestHandler_t)(ReqContext_t *ctx, OBCset_device_mac_addressRequestData_t *pRequestData);
typedef void (*pfOBC_get_device_mac_addressRequestHandler_t)(ReqContext_t *ctx, OBCget_device_mac_addressRequestData_t *pRequestData);

typedef struct {
    pfOBC_getGpOutputStatesRequestHandler_t OBC_getGpOutputStatesRequestHandler;
    pfOBC_setGpOutputStateRequestHandler_t OBC_setGpOutputStateRequestHandler;
    pfOBC_getI2CPullUpsStateRequestHandler_t OBC_getI2CPullUpsStateRequestHandler;
    pfOBC_setI2CPullUpsStateRequestHandler_t OBC_setI2CPullUpsStateRequestHandler;
    pfOBC_get_uptimeRequestHandler_t OBC_get_uptimeRequestHandler;
    pfOBC_getResetCountersRequestHandler_t OBC_getResetCountersRequestHandler;
    pfOBC_clearResetCounterRequestHandler_t OBC_clearResetCounterRequestHandler;
    pfOBC_triggerResetInModeRequestHandler_t OBC_triggerResetInModeRequestHandler;
    pfOBC_set_device_mac_addressRequestHandler_t OBC_set_device_mac_addressRequestHandler;
    pfOBC_get_device_mac_addressRequestHandler_t OBC_get_device_mac_addressRequestHandler;
} OBC_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_OBCProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void OBC_registerServerApi(OBC_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_OBCProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t OBC_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes OBC_getGpOutputStatesResp(
                RespContext_t* ctx,
                const OBC_GpioStatus_t * const sData
);

ESSATMAC_ErrCodes OBC_setGpOutputStateResp(
                RespContext_t* ctx,
                const OBC_HwResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_getI2CPullUpsStateResp(
                RespContext_t* ctx,
                const OBC_I2CPullUpsState_t * const sNvm_pullupsState,
                const OBC_I2CPullUpsState_t * const sIo_pullupsState
);

ESSATMAC_ErrCodes OBC_setI2CPullUpsStateResp(
                RespContext_t* ctx,
                const OBC_I2CPullUpsState_t * const sPullupsIoState
);

ESSATMAC_ErrCodes OBC_get_uptimeResp(
                RespContext_t* ctx,
                const uint32_t u32Uptime
);

ESSATMAC_ErrCodes OBC_getResetCountersResp(
                RespContext_t* ctx,
                const OBC_ResetCountersInfo_t * const sStatus
);

ESSATMAC_ErrCodes OBC_clearResetCounterResp(
                RespContext_t* ctx,
                const OBC_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_triggerResetInModeResp(
                RespContext_t* ctx,
                const OBC_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_set_device_mac_addressResp(
                RespContext_t* ctx,
                const OBC_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_get_device_mac_addressResp(
                RespContext_t* ctx,
                const uint8_t u8Mac_address,
                const OBC_StandardResult_t eOpResult
);


#endif  // #ifndef __FP_OBCPROTOCOLSERVER_H__
