/*!
********************************************************************************************
* @file FP_timeServerApp.c
* @brief ServerApp implementation template generator
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

#include "FP_timeProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "sys_time.h"
#include "debug.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!

static TIME_rtc_source_t convert_rtc_clock_type(sys_time_osc_t type);

// @END_USER@ USER_LOCAL_FUNC_DECL
static void time_set_dateRequestHandlerImpl(ReqContext_t* pReqCtx,
            const timeset_dateRequestData_t* pRequestData);

static void time_get_dateRequestHandlerImpl(ReqContext_t* pReqCtx);

static void time_set_timeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const timeset_timeRequestData_t* pRequestData);

static void time_get_timeRequestHandlerImpl(ReqContext_t* pReqCtx);

static void time_enable_calibration_outputRequestHandlerImpl(ReqContext_t* pReqCtx,
            const timeenable_calibration_outputRequestData_t* pRequestData);

static void time_configure_rtc_calibration_parametersRequestHandlerImpl(ReqContext_t* pReqCtx,
            const timeconfigure_rtc_calibration_parametersRequestData_t* pRequestData);

static void time_retrieve_rtc_calibration_parametersRequestHandlerImpl(ReqContext_t* pReqCtx);

static void time_get_rtc_clock_sourceRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static time_ServerApi_t timeServerApiCtx =
{
  .time_set_dateRequestHandler = (pftime_set_dateRequestHandler_t) time_set_dateRequestHandlerImpl,
  .time_get_dateRequestHandler = (pftime_get_dateRequestHandler_t) time_get_dateRequestHandlerImpl,
  .time_set_timeRequestHandler = (pftime_set_timeRequestHandler_t) time_set_timeRequestHandlerImpl,
  .time_get_timeRequestHandler = (pftime_get_timeRequestHandler_t) time_get_timeRequestHandlerImpl,
  .time_enable_calibration_outputRequestHandler = (pftime_enable_calibration_outputRequestHandler_t) time_enable_calibration_outputRequestHandlerImpl,
  .time_configure_rtc_calibration_parametersRequestHandler = (pftime_configure_rtc_calibration_parametersRequestHandler_t) time_configure_rtc_calibration_parametersRequestHandlerImpl,
  .time_retrieve_rtc_calibration_parametersRequestHandler = (pftime_retrieve_rtc_calibration_parametersRequestHandler_t) time_retrieve_rtc_calibration_parametersRequestHandlerImpl,
  .time_get_rtc_clock_sourceRequestHandler = (pftime_get_rtc_clock_sourceRequestHandler_t) time_get_rtc_clock_sourceRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!

static TIME_rtc_source_t convert_rtc_clock_type(sys_time_osc_t type)
{
    TIME_rtc_source_t ret;
    if (SYS_TIME_OSC_NONE == type)
    {
        ret = TIME_RTC_SOURCE_RTC_OSC_NONE;
    }
    else if (SYS_TIME_OSC_LSE == type)
    {
        ret = TIME_RTC_SOURCE_RTC_OSC_LSE;
    }
    else if (SYS_TIME_OSC_LSI == type)
    {
        ret = TIME_RTC_SOURCE_RTC_OSC_LSI;
    }
    else if (SYS_TIME_OSC_HSE == type)
    {
        ret = TIME_RTC_SOURCE_RTC_OSC_HSE;
    }
    else
    {
        ret = TIME_RTC_SOURCE_RTC_OSC_UNKNOWN;
    }
    return ret;
}

// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method time::set_date (ID = 0x00000001)
static void time_set_dateRequestHandlerImpl(ReqContext_t *pReqCtx,
            const timeset_dateRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_op_status_t eStatus;

    // @USER_VAR_SECTION_START@time::set_date@
    // Put your local variables in this section to preserve during merge!
    sys_date_t date;
    // @USER_VAR_SECTION_END@time::set_date@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::set_date@

        date.year = pRequestData->sDate.u16Year;
        date.mon  = pRequestData->sDate.u8Mon;
        date.day  = pRequestData->sDate.u8Day;
        date.wday = pRequestData->sDate.eWday;

        if (sys_time_set_date(&date))
        {
            eStatus = TIME_OP_STATUS_OK;
        }
        else
        {
            eStatus = TIME_OP_STATUS_ERROR;
        }

        // @USER_CODE_SECTION_END@time::set_date@

        respResult = time_set_dateResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_SET_DATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::set_date (ID = 0x00000001)

// @START@ Request handler for method time::get_date (ID = 0x00000002)
static void time_get_dateRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_op_status_t eStatus;
    TIME_sdate_t sDate;

    // @USER_VAR_SECTION_START@time::get_date@
    // Put your local variables in this section to preserve during merge!
    sys_date_t date;
    // @USER_VAR_SECTION_END@time::get_date@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::get_date@

        if (sys_time_get_date(&date))
        {
            sDate.u16Year = date.year;
            sDate.u8Mon   = date.mon;
            sDate.u8Day   = date.day;
            sDate.eWday   = date.wday;

            eStatus = TIME_OP_STATUS_OK;
        }
        else
        {
            sDate.u16Year = 0;
            sDate.u8Mon   = 0;
            sDate.u8Day   = 0;
            sDate.eWday   = TIME_WEEK_DAY_INVALID;

            eStatus = TIME_OP_STATUS_ERROR;
        }

        // @USER_CODE_SECTION_END@time::get_date@

        respResult = time_get_dateResp(
                        &respCtx,
                        eStatus,
                        &sDate
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_GET_DATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::get_date (ID = 0x00000002)

// @START@ Request handler for method time::set_time (ID = 0x00000003)
static void time_set_timeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const timeset_timeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_op_status_t eStatus;

    // @USER_VAR_SECTION_START@time::set_time@
    // Put your local variables in this section to preserve during merge!
    sys_time_t time;
    // @USER_VAR_SECTION_END@time::set_time@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::set_time@

        time.hour = pRequestData->sTime.u8Hour;
        time.min  = pRequestData->sTime.u8Min;
        time.sec  = pRequestData->sTime.u8Sec;
        time.ms   = pRequestData->sTime.u16Ms;
        time.us   = pRequestData->sTime.u16Us;

        if (sys_time_set(&time))
        {
            eStatus = TIME_OP_STATUS_OK;
        }
        else
        {
            eStatus = TIME_OP_STATUS_ERROR;
        }

        // @USER_CODE_SECTION_END@time::set_time@

        respResult = time_set_timeResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_SET_TIME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::set_time (ID = 0x00000003)

// @START@ Request handler for method time::get_time (ID = 0x00000004)
static void time_get_timeRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_op_status_t eStatus;
    TIME_stime_t sTime;

    // @USER_VAR_SECTION_START@time::get_time@
    // Put your local variables in this section to preserve during merge!
    sys_time_t time;
    // @USER_VAR_SECTION_END@time::get_time@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::get_time@

        if (sys_time_get(&time))
        {
            sTime.u8Hour = time.hour;
            sTime.u8Min  = time.min;
            sTime.u8Sec  = time.sec;
            sTime.u16Ms  = time.ms;
            sTime.u16Us  = time.us;

            eStatus = TIME_OP_STATUS_OK;
        }
        else
        {
            sTime.u8Hour = 0;
            sTime.u8Min  = 0;
            sTime.u8Sec  = 0;
            sTime.u16Ms  = 0;
            sTime.u16Us  = 0;

            eStatus = TIME_OP_STATUS_ERROR;
        }

        // @USER_CODE_SECTION_END@time::get_time@

        respResult = time_get_timeResp(
                        &respCtx,
                        eStatus,
                        &sTime
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_GET_TIME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::get_time (ID = 0x00000004)

// @START@ Request handler for method time::enable_calibration_output (ID = 0x00000005)
static void time_enable_calibration_outputRequestHandlerImpl(ReqContext_t *pReqCtx,
            const timeenable_calibration_outputRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_op_status_t eStatus;

    // @USER_VAR_SECTION_START@time::enable_calibration_output@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@time::enable_calibration_output@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::enable_calibration_output@
        if (sys_time_en_calib_out(pRequestData->eF))
        {
            eStatus = TIME_OP_STATUS_OK;
        }
        else
        {
            eStatus = TIME_OP_STATUS_ERROR;
        }
        // @USER_CODE_SECTION_END@time::enable_calibration_output@

        respResult = time_enable_calibration_outputResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_ENABLE_CALIBRATION_OUTPUT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::enable_calibration_output (ID = 0x00000005)

// @START@ Request handler for method time::configure_rtc_calibration_parameters (ID = 0x00000006)
static void time_configure_rtc_calibration_parametersRequestHandlerImpl(ReqContext_t *pReqCtx,
            const timeconfigure_rtc_calibration_parametersRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_op_status_t eStatus;

    // @USER_VAR_SECTION_START@time::configure_rtc_calibration_parameters@
    sys_time_rtc_calib_settings_t rtc_calib_settings;
    // @USER_VAR_SECTION_END@time::configure_rtc_calibration_parameters@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::configure_rtc_calibration_parameters@
        rtc_calib_settings.calm = pRequestData->u16Calm;
        rtc_calib_settings.calp = pRequestData->eCalp;

        eStatus = TIME_OP_STATUS_ERROR;

        if (sys_time_update_rtc_calib_settings(&rtc_calib_settings))
        {
            if (sys_time_apply_rtc_calib())
            {
                eStatus = TIME_OP_STATUS_OK;
            }
        }
        // @USER_CODE_SECTION_END@time::configure_rtc_calibration_parameters@

        respResult = time_configure_rtc_calibration_parametersResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_CONFIGURE_RTC_CALIBRATION_PARAMETERS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::configure_rtc_calibration_parameters (ID = 0x00000006)

// @START@ Request handler for method time::retrieve_rtc_calibration_parameters (ID = 0x00000007)
static void time_retrieve_rtc_calibration_parametersRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_calp_pulses_t eCalp;
    uint16_t u16Calm;

    // @USER_VAR_SECTION_START@time::retrieve_rtc_calibration_parameters@
    sys_time_rtc_calib_settings_t rtc_calib_settings;
    // @USER_VAR_SECTION_END@time::retrieve_rtc_calibration_parameters@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::retrieve_rtc_calibration_parameters@
        
        if (sys_time_retrieve_rtc_calib_settings(&rtc_calib_settings))
        {
            eCalp = rtc_calib_settings.calp;
            u16Calm = rtc_calib_settings.calm;
        } else {
            eCalp = TIME_CALP_PULSES_MAX_CNT;
            u16Calm = UINT16_MAX;
        }
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@time::retrieve_rtc_calibration_parameters@

        respResult = time_retrieve_rtc_calibration_parametersResp(
                        &respCtx,
                        eCalp,
                        u16Calm
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_RETRIEVE_RTC_CALIBRATION_PARAMETERS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::retrieve_rtc_calibration_parameters (ID = 0x00000007)

// @START@ Request handler for method time::get_rtc_clock_source (ID = 0x00000008)
static void time_get_rtc_clock_sourceRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    TIME_op_status_t eStatus;
    TIME_s_rtc_info_t sInfo;

    // @USER_VAR_SECTION_START@time::get_rtc_clock_source@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@time::get_rtc_clock_source@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@time::get_rtc_clock_source@

        sys_time_rtc_clock_info_t   info = {false, SYS_TIME_OSC_UNKNOWN, 0, 0, 0};

        eStatus = TIME_OP_STATUS_ERROR;

        if (true == sys_time_get_rtc_clock_source(&info))
        {
            sInfo.eSource = convert_rtc_clock_type(info.source_osc);
            sInfo.bEnabled = info.enabled;
            sInfo.u8Hse_division_factor = info.hse_division_factor;
            sInfo.u8Rtc_asynchronous_prescaler = info.rtc_asynchronous_prescaler;
            sInfo.u16Rtc_synchronous_prescaler = info.rtc_synchronous_prescaler;
            eStatus = TIME_OP_STATUS_OK;
        }

        // @USER_CODE_SECTION_END@time::get_rtc_clock_source@

        respResult = time_get_rtc_clock_sourceResp(
                        &respCtx,
                        eStatus,
                        &sInfo
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_TIME, TIME_GET_RTC_CLOCK_SOURCE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method time::get_rtc_clock_source (ID = 0x00000008)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void timeServerAppInit(void)
{
    time_registerServerApi(&timeServerApiCtx);
}
