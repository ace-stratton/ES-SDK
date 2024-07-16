/*!
********************************************************************************************
* @file FP_obc_adis16265_gyroProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface obc_adis16265_gyro v3.0
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

#ifndef __FP_OBC_ADIS16265_GYROPROTOCOLSERVER_H__
#define __FP_OBC_ADIS16265_GYROPROTOCOLSERVER_H__

#include "FP_obc_adis16265_gyroProtocolTypes.h"

typedef void (*pfobc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandler_t)(ReqContext_t *ctx, obc_adis16265_gyroSET_GYROSCOPE_CONFIGRequestData_t *pRequestData);
typedef void (*pfobc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfobc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfobc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfobc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandler_t obc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandler;
    pfobc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandler_t obc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandler;
    pfobc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandler_t obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandler;
    pfobc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandler_t obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandler;
} obc_adis16265_gyro_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_obc_adis16265_gyroProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void obc_adis16265_gyro_registerServerApi(obc_adis16265_gyro_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_obc_adis16265_gyroProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t obc_adis16265_gyro_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes obc_adis16265_gyro_SET_GYROSCOPE_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
);

ESSATMAC_ErrCodes obc_adis16265_gyro_GET_GYROSCOPE_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_PANEL_t eX_AXIS_ACTIVE_PANEL,
                const OBC_ADIS16265_GYRO_PANEL_t eY_AXIS_ACTIVE_PANEL,
                const OBC_ADIS16265_GYRO_PANEL_t eZ_AXIS_ACTIVE_PANEL,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
);

ESSATMAC_ErrCodes obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
);

ESSATMAC_ErrCodes obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ADIS16265_GYRO_RESULT_t eOpResult
);


#endif  // #ifndef __FP_OBC_ADIS16265_GYROPROTOCOLSERVER_H__
