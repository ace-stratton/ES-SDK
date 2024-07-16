/*!
********************************************************************************************
* @file FP_OBC_ES_COORDSYSServerApp.c
* @brief ServerApp implementation template generator
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

#include "FP_OBC_ES_COORDSYSProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include "es_coordsys.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_COORDSYSSET_GYROSCOPE_FRAMERequestData_t* pRequestData);

static void OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMERequestData_t* pRequestData);

static void OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMERequestData_t* pRequestData);

static void OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMERequestData_t* pRequestData);

static void OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMERequestData_t* pRequestData);

static void OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static OBC_ES_COORDSYS_ServerApi_t OBC_ES_COORDSYSServerApiCtx =
{
  .OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandler = (pfOBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandler_t) OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandler = (pfOBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandler_t) OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandler = (pfOBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandler_t) OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandler = (pfOBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandler_t) OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandler = (pfOBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandler_t) OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandler = (pfOBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandler_t) OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandler = (pfOBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandler_t) OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandler = (pfOBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandler_t) OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandler = (pfOBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandler_t) OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandlerImpl,
  .OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandler = (pfOBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandler_t) OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandlerImpl,
  .OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandler = (pfOBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandler_t) OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandlerImpl,
  .OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandler = (pfOBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandler_t) OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method OBC_ES_COORDSYS::SET_GYROSCOPE_FRAME (ID = 0x00000001)
static void OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMERequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_COORDSYSSET_GYROSCOPE_FRAMERequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::SET_GYROSCOPE_FRAME@
    es_coordsys_gyr_frame_t desiredFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::SET_GYROSCOPE_FRAME@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::SET_GYROSCOPE_FRAME@

        /* Unpack the information */
        desiredFrame.gyr1 = pRequestData->sDesiredGyrFrame.eGyroscope1;
        desiredFrame.gyr2 = pRequestData->sDesiredGyrFrame.eGyroscope2;
        desiredFrame.gyr3 = pRequestData->sDesiredGyrFrame.eGyroscope3;

        /* Apply the desired frame */
        coordSys_setGyrMatrix(&desiredFrame);

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::SET_GYROSCOPE_FRAME@

        respResult = OBC_ES_COORDSYS_SET_GYROSCOPE_FRAMEResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_SET_GYROSCOPE_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::SET_GYROSCOPE_FRAME (ID = 0x00000001)

// @START@ Request handler for method OBC_ES_COORDSYS::GET_GYROSCOPE_FRAME (ID = 0x00000002)
static void OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_GYROSCOPE_FRAME_t sActiveGyrFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::GET_GYROSCOPE_FRAME@
    es_coordsys_gyr_frame_t activeFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::GET_GYROSCOPE_FRAME@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::GET_GYROSCOPE_FRAME@

        /* Retrieve the desired frame */
        coordSys_getGyrMatrix(&activeFrame);

        /* Unpack the information */
        sActiveGyrFrame.eGyroscope1 = activeFrame.gyr1;
        sActiveGyrFrame.eGyroscope2 = activeFrame.gyr2;
        sActiveGyrFrame.eGyroscope3 = activeFrame.gyr3;

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::GET_GYROSCOPE_FRAME@

        respResult = OBC_ES_COORDSYS_GET_GYROSCOPE_FRAMEResp(
                        &respCtx,
                        &sActiveGyrFrame,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_GET_GYROSCOPE_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::GET_GYROSCOPE_FRAME (ID = 0x00000002)

// @START@ Request handler for method OBC_ES_COORDSYS::SET_MAGNETOMETER_FRAME (ID = 0x00000003)
static void OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMERequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_COORDSYSSET_MAGNETOMETER_FRAMERequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::SET_MAGNETOMETER_FRAME@
    es_coordsys_mag_frame_t desiredFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::SET_MAGNETOMETER_FRAME@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::SET_MAGNETOMETER_FRAME@

        /* Unpack the information */
        desiredFrame.mag_x = pRequestData->sDesiredMagFrame.eMagnetometer_x;
        desiredFrame.mag_y = pRequestData->sDesiredMagFrame.eMagnetometer_y;
        desiredFrame.mag_z = pRequestData->sDesiredMagFrame.eMagnetometer_z;

        /* Apply the desired frame */
        coordSys_setMagMatrix(&desiredFrame);

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::SET_MAGNETOMETER_FRAME@

        respResult = OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAMEResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::SET_MAGNETOMETER_FRAME (ID = 0x00000003)

// @START@ Request handler for method OBC_ES_COORDSYS::GET_MAGNETOMETER_FRAME (ID = 0x00000004)
static void OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_MAGNETOMETER_FRAME_t sActiveMagFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::GET_MAGNETOMETER_FRAME@
    es_coordsys_mag_frame_t activeFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::GET_MAGNETOMETER_FRAME@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::GET_MAGNETOMETER_FRAME@

        /* Retrieve the desired frame */
        coordSys_getMagMatrix(&activeFrame);

        /* Unpack the information */
        sActiveMagFrame.eMagnetometer_x = activeFrame.mag_x;
        sActiveMagFrame.eMagnetometer_y = activeFrame.mag_y;
        sActiveMagFrame.eMagnetometer_z = activeFrame.mag_z;

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::GET_MAGNETOMETER_FRAME@

        respResult = OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAMEResp(
                        &respCtx,
                        &sActiveMagFrame,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::GET_MAGNETOMETER_FRAME (ID = 0x00000004)

// @START@ Request handler for method OBC_ES_COORDSYS::SET_MAGNETORQUER_FRAME (ID = 0x00000005)
static void OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMERequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_COORDSYSSET_MAGNETORQUER_FRAMERequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::SET_MAGNETORQUER_FRAME@
    es_coordsys_mtq_frame_t desiredFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::SET_MAGNETORQUER_FRAME@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::SET_MAGNETORQUER_FRAME@

        /* Unpack the information */
        desiredFrame.mtq1 = pRequestData->sDesiredMtqFrame.eMagnetorquer1;
        desiredFrame.mtq2 = pRequestData->sDesiredMtqFrame.eMagnetorquer2;
        desiredFrame.mtq3 = pRequestData->sDesiredMtqFrame.eMagnetorquer3;

        /* Apply the desired frame */
        coordSys_setMtqMatrix(&desiredFrame);

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::SET_MAGNETORQUER_FRAME@

        respResult = OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAMEResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_SET_MAGNETORQUER_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::SET_MAGNETORQUER_FRAME (ID = 0x00000005)

// @START@ Request handler for method OBC_ES_COORDSYS::GET_MAGNETORQUER_FRAME (ID = 0x00000006)
static void OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_MAGNETORQUER_FRAME_t sActiveMtqFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::GET_MAGNETORQUER_FRAME@
    es_coordsys_mtq_frame_t activeFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::GET_MAGNETORQUER_FRAME@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::GET_MAGNETORQUER_FRAME@

        /* Retrieve the desired frame */
        coordSys_getMtqMatrix(&activeFrame);

        /* Unpack the information */
        sActiveMtqFrame.eMagnetorquer1 = activeFrame.mtq1;
        sActiveMtqFrame.eMagnetorquer2 = activeFrame.mtq2;
        sActiveMtqFrame.eMagnetorquer3 = activeFrame.mtq3;

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::GET_MAGNETORQUER_FRAME@

        respResult = OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAMEResp(
                        &respCtx,
                        &sActiveMtqFrame,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_GET_MAGNETORQUER_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::GET_MAGNETORQUER_FRAME (ID = 0x00000006)

// @START@ Request handler for method OBC_ES_COORDSYS::SET_COARSE_SUN_SENSOR_FRAME (ID = 0x00000007)
static void OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMERequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_COORDSYSSET_COARSE_SUN_SENSOR_FRAMERequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::SET_COARSE_SUN_SENSOR_FRAME@
    es_coordsys_css_frame_t desiredFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::SET_COARSE_SUN_SENSOR_FRAME@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::SET_COARSE_SUN_SENSOR_FRAME@

        /* Unpack the information */
        desiredFrame.css1 = pRequestData->sDesiredCssFrame.eCoarseSunSensor1;
        desiredFrame.css2 = pRequestData->sDesiredCssFrame.eCoarseSunSensor2;
        desiredFrame.css3 = pRequestData->sDesiredCssFrame.eCoarseSunSensor3;
        desiredFrame.css4 = pRequestData->sDesiredCssFrame.eCoarseSunSensor4;
        desiredFrame.css5 = pRequestData->sDesiredCssFrame.eCoarseSunSensor5;
        desiredFrame.css6 = pRequestData->sDesiredCssFrame.eCoarseSunSensor6;

        /* Apply the desired frame */
        coordSys_setCssMatrix(&desiredFrame);

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::SET_COARSE_SUN_SENSOR_FRAME@

        respResult = OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAMEResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_SET_COARSE_SUN_SENSOR_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::SET_COARSE_SUN_SENSOR_FRAME (ID = 0x00000007)

// @START@ Request handler for method OBC_ES_COORDSYS::GET_COARSE_SUN_SENSOR_FRAME (ID = 0x00000008)
static void OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_COARSE_SUN_SENSOR_FRAME_t sActiveCssFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::GET_COARSE_SUN_SENSOR_FRAME@
    es_coordsys_css_frame_t activeFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::GET_COARSE_SUN_SENSOR_FRAME@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::GET_COARSE_SUN_SENSOR_FRAME@

        /* Retrieve the desired frame */
        coordSys_getCssMatrix(&activeFrame);

        /* Unpack the information */
        sActiveCssFrame.eCoarseSunSensor1 = activeFrame.css1;
        sActiveCssFrame.eCoarseSunSensor2 = activeFrame.css2;
        sActiveCssFrame.eCoarseSunSensor3 = activeFrame.css3;
        sActiveCssFrame.eCoarseSunSensor4 = activeFrame.css4;
        sActiveCssFrame.eCoarseSunSensor5 = activeFrame.css5;
        sActiveCssFrame.eCoarseSunSensor6 = activeFrame.css6;

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::GET_COARSE_SUN_SENSOR_FRAME@

        respResult = OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAMEResp(
                        &respCtx,
                        &sActiveCssFrame,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_GET_COARSE_SUN_SENSOR_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::GET_COARSE_SUN_SENSOR_FRAME (ID = 0x00000008)

// @START@ Request handler for method OBC_ES_COORDSYS::SAVE_COORDSYS_CONFIG (ID = 0x00000009)
static void OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::SAVE_COORDSYS_CONFIG@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::SAVE_COORDSYS_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::SAVE_COORDSYS_CONFIG@

        coordSys_save_config_to_NVM();

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::SAVE_COORDSYS_CONFIG@

        respResult = OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::SAVE_COORDSYS_CONFIG (ID = 0x00000009)

// @START@ Request handler for method OBC_ES_COORDSYS::LOAD_COORDSYS_CONFIG (ID = 0x0000000A)
static void OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::LOAD_COORDSYS_CONFIG@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::LOAD_COORDSYS_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::LOAD_COORDSYS_CONFIG@

        coordSys_load_config_from_NVM();

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::LOAD_COORDSYS_CONFIG@

        respResult = OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::LOAD_COORDSYS_CONFIG (ID = 0x0000000A)

// @START@ Request handler for method OBC_ES_COORDSYS::SET_ACCELEROMETER_FRAME (ID = 0x0000000B)
static void OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMERequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_COORDSYSSET_ACCELEROMETER_FRAMERequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::SET_ACCELEROMETER_FRAME@
    es_coordsys_acc_frame_t desiredFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::SET_ACCELEROMETER_FRAME@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::SET_ACCELEROMETER_FRAME@
        
        /* Unpack the information */
        desiredFrame.acc_x = pRequestData->sDesiredAccFrame.eAccelerometer_x;
        desiredFrame.acc_y = pRequestData->sDesiredAccFrame.eAccelerometer_y;
        desiredFrame.acc_z = pRequestData->sDesiredAccFrame.eAccelerometer_z;

        /* Apply the desired frame */
        coordSys_setAccMatrix(&desiredFrame);

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::SET_ACCELEROMETER_FRAME@

        respResult = OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAMEResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_SET_ACCELEROMETER_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::SET_ACCELEROMETER_FRAME (ID = 0x0000000B)

// @START@ Request handler for method OBC_ES_COORDSYS::GET_ACCELEROMETER_FRAME (ID = 0x0000000C)
static void OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMERequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_COORDSYS_ACCELEROMETER_FRAME_t sActiveAccFrame;
    OBC_ES_COORDSYS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_COORDSYS::GET_ACCELEROMETER_FRAME@
    es_coordsys_acc_frame_t activeFrame;
    // @USER_VAR_SECTION_END@OBC_ES_COORDSYS::GET_ACCELEROMETER_FRAME@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_COORDSYS::GET_ACCELEROMETER_FRAME@
        
        /* Retrieve the desired frame */
        coordSys_getAccMatrix(&activeFrame);

        /* Unpack the information */
        sActiveAccFrame.eAccelerometer_x = activeFrame.acc_x;
        sActiveAccFrame.eAccelerometer_y = activeFrame.acc_y;
        sActiveAccFrame.eAccelerometer_z = activeFrame.acc_z;

        eOpResult = OBC_ES_COORDSYS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_COORDSYS::GET_ACCELEROMETER_FRAME@

        respResult = OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAMEResp(
                        &respCtx,
                        &sActiveAccFrame,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_COORDSYS, OBC_ES_COORDSYS_GET_ACCELEROMETER_FRAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_COORDSYS::GET_ACCELEROMETER_FRAME (ID = 0x0000000C)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void OBC_ES_COORDSYSServerAppInit(void)
{
    OBC_ES_COORDSYS_registerServerApi(&OBC_ES_COORDSYSServerApiCtx);
}
