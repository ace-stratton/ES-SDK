/*!
********************************************************************************************
* @file FP_EPS1ClientApp.c
* @brief ClientApp implementation template generator
********************************************************************************************
* @version           interface EPS1 v0.1
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

#include "FP_EPS1ProtocolClient.h"

// @START_USER@ USER_INCLUDES
#include "eps_ctrl_cfg.h"
#include "eps_i.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL

static void EPS1_getSoftwareVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getSoftwareVersionResponseData_t* pResponseData);

static void EPS1_getBatteryInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getBatteryInfoResponseData_t* pResponseData);

static void EPS1_getBusesInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getBusesInfoResponseData_t* pResponseData);

static void EPS1_getSolarPanelsInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getSolarPanelsInfoResponseData_t* pResponseData);

static void EPS1_getStatisticInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getStatisticInfoResponseData_t* pResponseData);

static void EPS1_getTemperaturesInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getTemperaturesInfoResponseData_t* pResponseData);

static void EPS1_getConfigurationInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getConfigurationInfoResponseData_t* pResponseData);

static void EPS1_queryControlsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryControlsResponseData_t* pResponseData);

static void EPS1_queryRBatRawResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryRBatRawResponseData_t* pResponseData);

static void EPS1_queryDefaultsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryDefaultsResponseData_t* pResponseData);

static void EPS1_queryLaunchStateResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryLaunchStateResponseData_t* pResponseData);

static void EPS1_queryWatchdogResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryWatchdogResponseData_t* pResponseData);

static void EPS1_resetWatchdogResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1resetWatchdogResponseData_t* pResponseData);

static void EPS1_resetPowerSupplyResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1resetPowerSupplyResponseData_t* pResponseData);

static void EPS1_SetSerialNumberResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1SetSerialNumberResponseData_t* pResponseData);

static void EPS1_GetSerialNumberResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1GetSerialNumberResponseData_t* pResponseData);

static void EPS1_HellModeReadResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HellModeReadResponseData_t* pResponseData);

static void EPS1_HellModeWriteResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HellModeWriteResponseData_t* pResponseData);

static void EPS1_HeatersSettingsReadResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HeatersSettingsReadResponseData_t* pResponseData);

static void EPS1_HeatersSettingsWriteResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HeatersSettingsWriteResponseData_t* pResponseData);

static void EPS1_ToggleOutPutResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1ToggleOutPutResponseData_t* pResponseData);

static void EPS1_NotificationsSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1NotificationsSettingsResponseData_t* pResponseData);

static void EPS1_GetTelemetryAltogetherResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1GetTelemetryAltogetherResponseData_t* pResponseData);

static void EPS1_bload_getVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_getVersionResponseData_t* pResponseData);

static void EPS1_bload_eraseFlashResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_eraseFlashResponseData_t* pResponseData);

static void EPS1_bload_writeFlashResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_writeFlashResponseData_t* pResponseData);

static void EPS1_bload_executeResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_executeResponseData_t* pResponseData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static EPS1_ClientApi_t EPS1ClientApiCtx =
{
  .EPS1_getSoftwareVersionResponseHandler = (pfEPS1_getSoftwareVersionResponseHandler_t) EPS1_getSoftwareVersionResponseHandlerImpl,
  .EPS1_getBatteryInfoResponseHandler = (pfEPS1_getBatteryInfoResponseHandler_t) EPS1_getBatteryInfoResponseHandlerImpl,
  .EPS1_getBusesInfoResponseHandler = (pfEPS1_getBusesInfoResponseHandler_t) EPS1_getBusesInfoResponseHandlerImpl,
  .EPS1_getSolarPanelsInfoResponseHandler = (pfEPS1_getSolarPanelsInfoResponseHandler_t) EPS1_getSolarPanelsInfoResponseHandlerImpl,
  .EPS1_getStatisticInfoResponseHandler = (pfEPS1_getStatisticInfoResponseHandler_t) EPS1_getStatisticInfoResponseHandlerImpl,
  .EPS1_getTemperaturesInfoResponseHandler = (pfEPS1_getTemperaturesInfoResponseHandler_t) EPS1_getTemperaturesInfoResponseHandlerImpl,
  .EPS1_getConfigurationInfoResponseHandler = (pfEPS1_getConfigurationInfoResponseHandler_t) EPS1_getConfigurationInfoResponseHandlerImpl,
  .EPS1_queryControlsResponseHandler = (pfEPS1_queryControlsResponseHandler_t) EPS1_queryControlsResponseHandlerImpl,
  .EPS1_queryRBatRawResponseHandler = (pfEPS1_queryRBatRawResponseHandler_t) EPS1_queryRBatRawResponseHandlerImpl,
  .EPS1_queryDefaultsResponseHandler = (pfEPS1_queryDefaultsResponseHandler_t) EPS1_queryDefaultsResponseHandlerImpl,
  .EPS1_queryLaunchStateResponseHandler = (pfEPS1_queryLaunchStateResponseHandler_t) EPS1_queryLaunchStateResponseHandlerImpl,
  .EPS1_queryWatchdogResponseHandler = (pfEPS1_queryWatchdogResponseHandler_t) EPS1_queryWatchdogResponseHandlerImpl,
  .EPS1_resetWatchdogResponseHandler = (pfEPS1_resetWatchdogResponseHandler_t) EPS1_resetWatchdogResponseHandlerImpl,
  .EPS1_resetPowerSupplyResponseHandler = (pfEPS1_resetPowerSupplyResponseHandler_t) EPS1_resetPowerSupplyResponseHandlerImpl,
  .EPS1_SetSerialNumberResponseHandler = (pfEPS1_SetSerialNumberResponseHandler_t) EPS1_SetSerialNumberResponseHandlerImpl,
  .EPS1_GetSerialNumberResponseHandler = (pfEPS1_GetSerialNumberResponseHandler_t) EPS1_GetSerialNumberResponseHandlerImpl,
  .EPS1_HellModeReadResponseHandler = (pfEPS1_HellModeReadResponseHandler_t) EPS1_HellModeReadResponseHandlerImpl,
  .EPS1_HellModeWriteResponseHandler = (pfEPS1_HellModeWriteResponseHandler_t) EPS1_HellModeWriteResponseHandlerImpl,
  .EPS1_HeatersSettingsReadResponseHandler = (pfEPS1_HeatersSettingsReadResponseHandler_t) EPS1_HeatersSettingsReadResponseHandlerImpl,
  .EPS1_HeatersSettingsWriteResponseHandler = (pfEPS1_HeatersSettingsWriteResponseHandler_t) EPS1_HeatersSettingsWriteResponseHandlerImpl,
  .EPS1_ToggleOutPutResponseHandler = (pfEPS1_ToggleOutPutResponseHandler_t) EPS1_ToggleOutPutResponseHandlerImpl,
  .EPS1_NotificationsSettingsResponseHandler = (pfEPS1_NotificationsSettingsResponseHandler_t) EPS1_NotificationsSettingsResponseHandlerImpl,
  .EPS1_GetTelemetryAltogetherResponseHandler = (pfEPS1_GetTelemetryAltogetherResponseHandler_t) EPS1_GetTelemetryAltogetherResponseHandlerImpl,
  .EPS1_bload_getVersionResponseHandler = (pfEPS1_bload_getVersionResponseHandler_t) EPS1_bload_getVersionResponseHandlerImpl,
  .EPS1_bload_eraseFlashResponseHandler = (pfEPS1_bload_eraseFlashResponseHandler_t) EPS1_bload_eraseFlashResponseHandlerImpl,
  .EPS1_bload_writeFlashResponseHandler = (pfEPS1_bload_writeFlashResponseHandler_t) EPS1_bload_writeFlashResponseHandlerImpl,
  .EPS1_bload_executeResponseHandler = (pfEPS1_bload_executeResponseHandler_t) EPS1_bload_executeResponseHandlerImpl,
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Response handler for method EPS1::getSoftwareVersion (ID = 0x00000000)
static void EPS1_getSoftwareVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getSoftwareVersionResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::getSoftwareVersion@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::getSoftwareVersion@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::getSoftwareVersion@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::getSoftwareVersion@
    }
}
// @END@ Response handler for method EPS1::getSoftwareVersion (ID = 0x00000000)

// @START@ Response handler for method EPS1::getBatteryInfo (ID = 0x00000001)
static void EPS1_getBatteryInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getBatteryInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::getBatteryInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::getBatteryInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::getBatteryInfo@
        
    	// Send the battery info the the EPS I module
    	eps_i_info_to_datacache(pResponseData);

        // @USER_CODE_SECTION_END@EPS1::getBatteryInfo@
    }
}
// @END@ Response handler for method EPS1::getBatteryInfo (ID = 0x00000001)

// @START@ Response handler for method EPS1::getBusesInfo (ID = 0x00000002)
static void EPS1_getBusesInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getBusesInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::getBusesInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::getBusesInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::getBusesInfo@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::getBusesInfo@
    }
}
// @END@ Response handler for method EPS1::getBusesInfo (ID = 0x00000002)

// @START@ Response handler for method EPS1::getSolarPanelsInfo (ID = 0x00000003)
static void EPS1_getSolarPanelsInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getSolarPanelsInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::getSolarPanelsInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::getSolarPanelsInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::getSolarPanelsInfo@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::getSolarPanelsInfo@
    }
}
// @END@ Response handler for method EPS1::getSolarPanelsInfo (ID = 0x00000003)

// @START@ Response handler for method EPS1::getStatisticInfo (ID = 0x00000004)
static void EPS1_getStatisticInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getStatisticInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::getStatisticInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::getStatisticInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::getStatisticInfo@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::getStatisticInfo@
    }
}
// @END@ Response handler for method EPS1::getStatisticInfo (ID = 0x00000004)

// @START@ Response handler for method EPS1::getTemperaturesInfo (ID = 0x00000005)
static void EPS1_getTemperaturesInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getTemperaturesInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::getTemperaturesInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::getTemperaturesInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::getTemperaturesInfo@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::getTemperaturesInfo@
    }
}
// @END@ Response handler for method EPS1::getTemperaturesInfo (ID = 0x00000005)

// @START@ Response handler for method EPS1::getConfigurationInfo (ID = 0x00000006)
static void EPS1_getConfigurationInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1getConfigurationInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::getConfigurationInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::getConfigurationInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::getConfigurationInfo@
		eps_ctrl_cfg_get_ch_notif_eps_i(pRespCtx->seqId, pResponseData->sConfig);

        // @USER_CODE_SECTION_END@EPS1::getConfigurationInfo@
    }
}
// @END@ Response handler for method EPS1::getConfigurationInfo (ID = 0x00000006)

// @START@ Response handler for method EPS1::queryControls (ID = 0x00000007)
static void EPS1_queryControlsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryControlsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::queryControls@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::queryControls@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::queryControls@
        
        // No need of passing the response data, we assume the request is being processed in the EPS I
		eps_ctrl_cfg_set_ch_notif_eps_i(pRespCtx->seqId);
        
        // @USER_CODE_SECTION_END@EPS1::queryControls@
    }
}
// @END@ Response handler for method EPS1::queryControls (ID = 0x00000007)

// @START@ Response handler for method EPS1::queryRBatRaw (ID = 0x00000008)
static void EPS1_queryRBatRawResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryRBatRawResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::queryRBatRaw@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::queryRBatRaw@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::queryRBatRaw@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::queryRBatRaw@
    }
}
// @END@ Response handler for method EPS1::queryRBatRaw (ID = 0x00000008)

// @START@ Response handler for method EPS1::queryDefaults (ID = 0x00000009)
static void EPS1_queryDefaultsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryDefaultsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::queryDefaults@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::queryDefaults@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::queryDefaults@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::queryDefaults@
    }
}
// @END@ Response handler for method EPS1::queryDefaults (ID = 0x00000009)

// @START@ Response handler for method EPS1::queryLaunchState (ID = 0x0000000A)
static void EPS1_queryLaunchStateResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryLaunchStateResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::queryLaunchState@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::queryLaunchState@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::queryLaunchState@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::queryLaunchState@
    }
}
// @END@ Response handler for method EPS1::queryLaunchState (ID = 0x0000000A)

// @START@ Response handler for method EPS1::queryWatchdog (ID = 0x0000000B)
static void EPS1_queryWatchdogResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1queryWatchdogResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::queryWatchdog@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::queryWatchdog@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::queryWatchdog@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::queryWatchdog@
    }
}
// @END@ Response handler for method EPS1::queryWatchdog (ID = 0x0000000B)

// @START@ Response handler for method EPS1::resetWatchdog (ID = 0x0000000C)
static void EPS1_resetWatchdogResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1resetWatchdogResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::resetWatchdog@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::resetWatchdog@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::resetWatchdog@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::resetWatchdog@
    }
}
// @END@ Response handler for method EPS1::resetWatchdog (ID = 0x0000000C)

// @START@ Response handler for method EPS1::resetPowerSupply (ID = 0x0000000D)
static void EPS1_resetPowerSupplyResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1resetPowerSupplyResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::resetPowerSupply@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::resetPowerSupply@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::resetPowerSupply@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::resetPowerSupply@
    }
}
// @END@ Response handler for method EPS1::resetPowerSupply (ID = 0x0000000D)

// @START@ Response handler for method EPS1::SetSerialNumber (ID = 0x0000000E)
static void EPS1_SetSerialNumberResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1SetSerialNumberResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::SetSerialNumber@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::SetSerialNumber@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::SetSerialNumber@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::SetSerialNumber@
    }
}
// @END@ Response handler for method EPS1::SetSerialNumber (ID = 0x0000000E)

// @START@ Response handler for method EPS1::GetSerialNumber (ID = 0x0000000F)
static void EPS1_GetSerialNumberResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1GetSerialNumberResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::GetSerialNumber@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::GetSerialNumber@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::GetSerialNumber@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::GetSerialNumber@
    }
}
// @END@ Response handler for method EPS1::GetSerialNumber (ID = 0x0000000F)

// @START@ Response handler for method EPS1::HellModeRead (ID = 0x00000010)
static void EPS1_HellModeReadResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HellModeReadResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::HellModeRead@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::HellModeRead@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::HellModeRead@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::HellModeRead@
    }
}
// @END@ Response handler for method EPS1::HellModeRead (ID = 0x00000010)

// @START@ Response handler for method EPS1::HellModeWrite (ID = 0x00000011)
static void EPS1_HellModeWriteResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HellModeWriteResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::HellModeWrite@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::HellModeWrite@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::HellModeWrite@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::HellModeWrite@
    }
}
// @END@ Response handler for method EPS1::HellModeWrite (ID = 0x00000011)

// @START@ Response handler for method EPS1::HeatersSettingsRead (ID = 0x00000012)
static void EPS1_HeatersSettingsReadResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HeatersSettingsReadResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::HeatersSettingsRead@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::HeatersSettingsRead@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::HeatersSettingsRead@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::HeatersSettingsRead@
    }
}
// @END@ Response handler for method EPS1::HeatersSettingsRead (ID = 0x00000012)

// @START@ Response handler for method EPS1::HeatersSettingsWrite (ID = 0x00000013)
static void EPS1_HeatersSettingsWriteResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1HeatersSettingsWriteResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::HeatersSettingsWrite@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::HeatersSettingsWrite@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::HeatersSettingsWrite@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::HeatersSettingsWrite@
    }
}
// @END@ Response handler for method EPS1::HeatersSettingsWrite (ID = 0x00000013)

// @START@ Response handler for method EPS1::ToggleOutPut (ID = 0x00000014)
static void EPS1_ToggleOutPutResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1ToggleOutPutResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::ToggleOutPut@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::ToggleOutPut@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::ToggleOutPut@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::ToggleOutPut@
    }
}
// @END@ Response handler for method EPS1::ToggleOutPut (ID = 0x00000014)

// @START@ Response handler for method EPS1::NotificationsSettings (ID = 0x00000015)
static void EPS1_NotificationsSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1NotificationsSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::NotificationsSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::NotificationsSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::NotificationsSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::NotificationsSettings@
    }
}
// @END@ Response handler for method EPS1::NotificationsSettings (ID = 0x00000015)

// @START@ Response handler for method EPS1::GetTelemetryAltogether (ID = 0x00000016)
static void EPS1_GetTelemetryAltogetherResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1GetTelemetryAltogetherResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::GetTelemetryAltogether@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::GetTelemetryAltogether@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::GetTelemetryAltogether@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::GetTelemetryAltogether@
    }
}
// @END@ Response handler for method EPS1::GetTelemetryAltogether (ID = 0x00000016)

// @START@ Response handler for method EPS1::bload_getVersion (ID = 0x10000000)
static void EPS1_bload_getVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_getVersionResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::bload_getVersion@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::bload_getVersion@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::bload_getVersion@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::bload_getVersion@
    }
}
// @END@ Response handler for method EPS1::bload_getVersion (ID = 0x10000000)

// @START@ Response handler for method EPS1::bload_eraseFlash (ID = 0x10000001)
static void EPS1_bload_eraseFlashResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_eraseFlashResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::bload_eraseFlash@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::bload_eraseFlash@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::bload_eraseFlash@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::bload_eraseFlash@
    }
}
// @END@ Response handler for method EPS1::bload_eraseFlash (ID = 0x10000001)

// @START@ Response handler for method EPS1::bload_writeFlash (ID = 0x10000002)
static void EPS1_bload_writeFlashResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_writeFlashResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::bload_writeFlash@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::bload_writeFlash@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::bload_writeFlash@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::bload_writeFlash@
    }
}
// @END@ Response handler for method EPS1::bload_writeFlash (ID = 0x10000002)

// @START@ Response handler for method EPS1::bload_execute (ID = 0x10000003)
static void EPS1_bload_executeResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPS1bload_executeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPS1::bload_execute@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPS1::bload_execute@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPS1::bload_execute@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPS1::bload_execute@
    }
}
// @END@ Response handler for method EPS1::bload_execute (ID = 0x10000003)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void EPS1ClientAppInit(void)
{
    EPS1_registerClientApi(&EPS1ClientApiCtx);
}
