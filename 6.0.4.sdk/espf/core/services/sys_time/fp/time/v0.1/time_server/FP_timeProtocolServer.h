/*!
********************************************************************************************
* @file FP_timeProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface time v0.1
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

#ifndef __FP_TIMEPROTOCOLSERVER_H__
#define __FP_TIMEPROTOCOLSERVER_H__

#include "FP_timeProtocolTypes.h"

typedef void (*pftime_set_dateRequestHandler_t)(ReqContext_t *ctx, timeset_dateRequestData_t *pRequestData);
typedef void (*pftime_get_dateRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pftime_set_timeRequestHandler_t)(ReqContext_t *ctx, timeset_timeRequestData_t *pRequestData);
typedef void (*pftime_get_timeRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pftime_enable_calibration_outputRequestHandler_t)(ReqContext_t *ctx, timeenable_calibration_outputRequestData_t *pRequestData);
typedef void (*pftime_configure_rtc_calibration_parametersRequestHandler_t)(ReqContext_t *ctx, timeconfigure_rtc_calibration_parametersRequestData_t *pRequestData);
typedef void (*pftime_retrieve_rtc_calibration_parametersRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pftime_get_rtc_clock_sourceRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pftime_set_dateRequestHandler_t time_set_dateRequestHandler;
    pftime_get_dateRequestHandler_t time_get_dateRequestHandler;
    pftime_set_timeRequestHandler_t time_set_timeRequestHandler;
    pftime_get_timeRequestHandler_t time_get_timeRequestHandler;
    pftime_enable_calibration_outputRequestHandler_t time_enable_calibration_outputRequestHandler;
    pftime_configure_rtc_calibration_parametersRequestHandler_t time_configure_rtc_calibration_parametersRequestHandler;
    pftime_retrieve_rtc_calibration_parametersRequestHandler_t time_retrieve_rtc_calibration_parametersRequestHandler;
    pftime_get_rtc_clock_sourceRequestHandler_t time_get_rtc_clock_sourceRequestHandler;
} time_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_timeProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void time_registerServerApi(time_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_timeProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t time_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes time_set_dateResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
);

ESSATMAC_ErrCodes time_get_dateResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus,
                const TIME_sdate_t * const sDate
);

ESSATMAC_ErrCodes time_set_timeResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
);

ESSATMAC_ErrCodes time_get_timeResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus,
                const TIME_stime_t * const sTime
);

ESSATMAC_ErrCodes time_enable_calibration_outputResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
);

ESSATMAC_ErrCodes time_configure_rtc_calibration_parametersResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus
);

ESSATMAC_ErrCodes time_retrieve_rtc_calibration_parametersResp(
                RespContext_t* ctx,
                const TIME_calp_pulses_t eCalp,
                const uint16_t u16Calm
);

ESSATMAC_ErrCodes time_get_rtc_clock_sourceResp(
                RespContext_t* ctx,
                const TIME_op_status_t eStatus,
                const TIME_s_rtc_info_t * const sInfo
);


#endif  // #ifndef __FP_TIMEPROTOCOLSERVER_H__
