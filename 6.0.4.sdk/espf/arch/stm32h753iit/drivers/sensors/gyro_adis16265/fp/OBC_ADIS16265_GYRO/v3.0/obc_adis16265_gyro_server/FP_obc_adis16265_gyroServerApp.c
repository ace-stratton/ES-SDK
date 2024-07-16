/*!
********************************************************************************************
* @file FP_obc_adis16265_gyroServerApp.c
* @brief ServerApp implementation template generator
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

#include "FP_obc_adis16265_gyroProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include "adis16265_driver.h"
#include "panels.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void obc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx,
            const obc_adis16265_gyroSET_GYROSCOPE_CONFIGRequestData_t* pRequestData);

static void obc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);

static void obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);

static void obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static obc_adis16265_gyro_ServerApi_t obc_adis16265_gyroServerApiCtx =
{
  .obc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandler = (pfobc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandler_t) obc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandlerImpl,
  .obc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandler = (pfobc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandler_t) obc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandlerImpl,
  .obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandler = (pfobc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandler_t) obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandlerImpl,
  .obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandler = (pfobc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandler_t) obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method obc_adis16265_gyro::SET_GYROSCOPE_CONFIG (ID = 0x00000001)
static void obc_adis16265_gyro_SET_GYROSCOPE_CONFIGRequestHandlerImpl(ReqContext_t *pReqCtx,
            const obc_adis16265_gyroSET_GYROSCOPE_CONFIGRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@obc_adis16265_gyro::SET_GYROSCOPE_CONFIG@
    Panel_Number_t x_panel, y_panel, z_panel;
    // @USER_VAR_SECTION_END@obc_adis16265_gyro::SET_GYROSCOPE_CONFIG@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@obc_adis16265_gyro::SET_GYROSCOPE_CONFIG@

        x_panel = pRequestData->eX_AXIS_PANEL;
        y_panel = pRequestData->eY_AXIS_PANEL;
        z_panel = pRequestData->eZ_AXIS_PANEL;

        ADIS16265_SetPanel(PAN_X_P, x_panel);
        ADIS16265_SetPanel(PAN_Y_P, y_panel);
        ADIS16265_SetPanel(PAN_Z_P, z_panel);

        eOpResult = OBC_ADIS16265_GYRO_RESULT_OK;
        // @USER_CODE_SECTION_END@obc_adis16265_gyro::SET_GYROSCOPE_CONFIG@

        respResult = obc_adis16265_gyro_SET_GYROSCOPE_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO, OBC_ADIS16265_GYRO_SET_GYROSCOPE_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method obc_adis16265_gyro::SET_GYROSCOPE_CONFIG (ID = 0x00000001)

// @START@ Request handler for method obc_adis16265_gyro::GET_GYROSCOPE_CONFIG (ID = 0x00000002)
static void obc_adis16265_gyro_GET_GYROSCOPE_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ADIS16265_GYRO_PANEL_t eX_AXIS_ACTIVE_PANEL;
    OBC_ADIS16265_GYRO_PANEL_t eY_AXIS_ACTIVE_PANEL;
    OBC_ADIS16265_GYRO_PANEL_t eZ_AXIS_ACTIVE_PANEL;
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@obc_adis16265_gyro::GET_GYROSCOPE_CONFIG@
    Panel_Number_t active_x_panel, active_y_panel, active_z_panel;
    // @USER_VAR_SECTION_END@obc_adis16265_gyro::GET_GYROSCOPE_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@obc_adis16265_gyro::GET_GYROSCOPE_CONFIG@
        
        active_x_panel = ADIS16265_GetPanel(PAN_X_P);
        active_y_panel = ADIS16265_GetPanel(PAN_Y_P);
        active_z_panel = ADIS16265_GetPanel(PAN_Z_P);
        
        eX_AXIS_ACTIVE_PANEL = active_x_panel;
        eY_AXIS_ACTIVE_PANEL = active_y_panel;
        eZ_AXIS_ACTIVE_PANEL = active_z_panel;

        eOpResult = OBC_ADIS16265_GYRO_RESULT_OK;

        // @USER_CODE_SECTION_END@obc_adis16265_gyro::GET_GYROSCOPE_CONFIG@

        respResult = obc_adis16265_gyro_GET_GYROSCOPE_CONFIGResp(
                        &respCtx,
                        eX_AXIS_ACTIVE_PANEL,
                        eY_AXIS_ACTIVE_PANEL,
                        eZ_AXIS_ACTIVE_PANEL,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO, OBC_ADIS16265_GYRO_GET_GYROSCOPE_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method obc_adis16265_gyro::GET_GYROSCOPE_CONFIG (ID = 0x00000002)

// @START@ Request handler for method obc_adis16265_gyro::SAVE_GYRO_PANEL_CONFIG (ID = 0x00000003)
static void obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@obc_adis16265_gyro::SAVE_GYRO_PANEL_CONFIG@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@obc_adis16265_gyro::SAVE_GYRO_PANEL_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@obc_adis16265_gyro::SAVE_GYRO_PANEL_CONFIG@
        
        ADIS16265_Save_Config_to_NVM();
        
        eOpResult = OBC_ADIS16265_GYRO_RESULT_OK;

        // @USER_CODE_SECTION_END@obc_adis16265_gyro::SAVE_GYRO_PANEL_CONFIG@

        respResult = obc_adis16265_gyro_SAVE_GYRO_PANEL_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO, OBC_ADIS16265_GYRO_SAVE_GYRO_PANEL_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method obc_adis16265_gyro::SAVE_GYRO_PANEL_CONFIG (ID = 0x00000003)

// @START@ Request handler for method obc_adis16265_gyro::LOAD_GYRO_PANEL_CONFIG (ID = 0x00000004)
static void obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@obc_adis16265_gyro::LOAD_GYRO_PANEL_CONFIG@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@obc_adis16265_gyro::LOAD_GYRO_PANEL_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@obc_adis16265_gyro::LOAD_GYRO_PANEL_CONFIG@
        
        ADIS16265_Load_Config_from_NVM();

        eOpResult = OBC_ADIS16265_GYRO_RESULT_OK;
        
        // @USER_CODE_SECTION_END@obc_adis16265_gyro::LOAD_GYRO_PANEL_CONFIG@

        respResult = obc_adis16265_gyro_LOAD_GYRO_PANEL_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO, OBC_ADIS16265_GYRO_LOAD_GYRO_PANEL_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method obc_adis16265_gyro::LOAD_GYRO_PANEL_CONFIG (ID = 0x00000004)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void obc_adis16265_gyroServerAppInit(void)
{
    obc_adis16265_gyro_registerServerApi(&obc_adis16265_gyroServerApiCtx);
}
