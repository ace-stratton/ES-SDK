/*!
********************************************************************************************
* @file FP_OBC_ES_COORDSYSProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface OBC_ES_COORDSYS v3.0
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

#ifndef __FP_OBC_ES_COORDSYSPROTOCOLSERVER_H__
#define __FP_OBC_ES_COORDSYSPROTOCOLSERVER_H__

#include "FP_OBC_ES_COORDSYSProtocolTypes.h"

typedef void (*pfOBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandler_t)(ReqContext_t *ctx, OBC_ES_COORDSYSSET_GYROSCOPE_FRAMERequestData_t *pRequestData);
typedef void (*pfOBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandler_t)(ReqContext_t *ctx, OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMERequestData_t *pRequestData);
typedef void (*pfOBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandler_t)(ReqContext_t *ctx, OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMERequestData_t *pRequestData);
typedef void (*pfOBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandler_t)(ReqContext_t *ctx, OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMERequestData_t *pRequestData);
typedef void (*pfOBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandler_t)(ReqContext_t *ctx, OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMERequestData_t *pRequestData);
typedef void (*pfOBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfOBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandler_t OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandler_t OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandler_t OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandler_t OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandler_t OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandler_t OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandler_t OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandler_t OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandler_t OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandler;
    pfOBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandler_t OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandler;
    pfOBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandler_t OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandler;
    pfOBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandler_t OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandler;
} OBC_ES_COORDSYS_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_ES_COORDSYSProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void OBC_ES_COORDSYS_registerServerApi(OBC_ES_COORDSYS_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_OBC_ES_COORDSYSProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t OBC_ES_COORDSYS_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_GYROSCOPE_FRAME_t * const sActiveGyrFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_MAGNETOMETER_FRAME_t * const sActiveMagFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_MAGNETORQUER_FRAME_t * const sActiveMtqFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_COARSE_SUN_SENSOR_FRAME_t * const sActiveCssFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMEResp(
                RespContext_t* ctx,
                const OBC_ES_COORDSYS_ACCELEROMETER_FRAME_t * const sActiveAccFrame,
                const OBC_ES_COORDSYS_RESULT_t eOpResult
);


#endif  // #ifndef __FP_OBC_ES_COORDSYSPROTOCOLSERVER_H__
