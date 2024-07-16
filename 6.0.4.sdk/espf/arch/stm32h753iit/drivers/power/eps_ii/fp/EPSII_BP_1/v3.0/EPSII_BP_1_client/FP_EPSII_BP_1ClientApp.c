/*!
********************************************************************************************
* @file FP_EPSII_BP_1ClientApp.c
* @brief ClientApp implementation template generator
********************************************************************************************
* @version           interface EPSII_BP_1 v3.0
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

#include "FP_EPSII_BP_1ProtocolClient.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "eps_ii_telemetry.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL

static void EPSII_BP_1_GetDeviceInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetDeviceInfoResponseData_t* pResponseData);

static void EPSII_BP_1_GetRAWSensorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetRAWSensorsResponseData_t* pResponseData);

static void EPSII_BP_1_GetBatteryInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBatteryInfoResponseData_t* pResponseData);

static void EPSII_BP_1_GetDeviceHealthInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetDeviceHealthInfoResponseData_t* pResponseData);

static void EPSII_BP_1_SetBatHeaterSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetBatHeaterSettingsResponseData_t* pResponseData);

static void EPSII_BP_1_GetBatHeaterSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBatHeaterSettingsResponseData_t* pResponseData);

static void EPSII_BP_1_SetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetBasicSettingsResponseData_t* pResponseData);

static void EPSII_BP_1_GetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBasicSettingsResponseData_t* pResponseData);

static void EPSII_BP_1_GetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBasicAppExceptionsResponseData_t* pResponseData);

static void EPSII_BP_1_GetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBasicAppErrCountersResponseData_t* pResponseData);

static void EPSII_BP_1_GetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetMainAppExceptionsResponseData_t* pResponseData);

static void EPSII_BP_1_GetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetMainAppErrCountersResponseData_t* pResponseData);

static void EPSII_BP_1_GetMainAppErrCounters2ResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetMainAppErrCounters2ResponseData_t* pResponseData);

static void EPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetMainAppErrCountersResponseData_t* pResponseData);

static void EPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetMainAppExceptionsResponseData_t* pResponseData);

static void EPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetBasicAppErrCountersResponseData_t* pResponseData);

static void EPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetBasicAppExceptionsResponseData_t* pResponseData);

static void EPSII_BP_1_GetBalancerStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBalancerStatusResponseData_t* pResponseData);

static void EPSII_BP_1_ResetDeviceResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ResetDeviceResponseData_t* pResponseData);

static void EPSII_BP_1_ForceInstallMainAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ForceInstallMainAppResponseData_t* pResponseData);

static void EPSII_BP_1_ForceInstallBasicAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ForceInstallBasicAppResponseData_t* pResponseData);

static void EPSII_BP_1_GetBootLoaderErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBootLoaderErrCountersResponseData_t* pResponseData);

static void EPSII_BP_1_ResetBootLdrErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ResetBootLdrErrCountersResponseData_t* pResponseData);

static void EPSII_BP_1_SetChargerSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetChargerSettingsResponseData_t* pResponseData);

static void EPSII_BP_1_SetRTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetRTCResponseData_t* pResponseData);

static void EPSII_BP_1_GetRTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetRTCResponseData_t* pResponseData);

static void EPSII_BP_1_LeaveNoHibModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1LeaveNoHibModeResponseData_t* pResponseData);

static void EPSII_BP_1_RequestPowerDownResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1RequestPowerDownResponseData_t* pResponseData);

static void EPSII_BP_1_GetBpModeSmRollingTraceResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBpModeSmRollingTraceResponseData_t* pResponseData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static EPSII_BP_1_ClientApi_t EPSII_BP_1ClientApiCtx =
{
  .EPSII_BP_1_GetDeviceInfoResponseHandler = (pfEPSII_BP_1_GetDeviceInfoResponseHandler_t) EPSII_BP_1_GetDeviceInfoResponseHandlerImpl,
  .EPSII_BP_1_GetRAWSensorsResponseHandler = (pfEPSII_BP_1_GetRAWSensorsResponseHandler_t) EPSII_BP_1_GetRAWSensorsResponseHandlerImpl,
  .EPSII_BP_1_GetBatteryInfoResponseHandler = (pfEPSII_BP_1_GetBatteryInfoResponseHandler_t) EPSII_BP_1_GetBatteryInfoResponseHandlerImpl,
  .EPSII_BP_1_GetDeviceHealthInfoResponseHandler = (pfEPSII_BP_1_GetDeviceHealthInfoResponseHandler_t) EPSII_BP_1_GetDeviceHealthInfoResponseHandlerImpl,
  .EPSII_BP_1_SetBatHeaterSettingsResponseHandler = (pfEPSII_BP_1_SetBatHeaterSettingsResponseHandler_t) EPSII_BP_1_SetBatHeaterSettingsResponseHandlerImpl,
  .EPSII_BP_1_GetBatHeaterSettingsResponseHandler = (pfEPSII_BP_1_GetBatHeaterSettingsResponseHandler_t) EPSII_BP_1_GetBatHeaterSettingsResponseHandlerImpl,
  .EPSII_BP_1_SetBasicSettingsResponseHandler = (pfEPSII_BP_1_SetBasicSettingsResponseHandler_t) EPSII_BP_1_SetBasicSettingsResponseHandlerImpl,
  .EPSII_BP_1_GetBasicSettingsResponseHandler = (pfEPSII_BP_1_GetBasicSettingsResponseHandler_t) EPSII_BP_1_GetBasicSettingsResponseHandlerImpl,
  .EPSII_BP_1_GetBasicAppExceptionsResponseHandler = (pfEPSII_BP_1_GetBasicAppExceptionsResponseHandler_t) EPSII_BP_1_GetBasicAppExceptionsResponseHandlerImpl,
  .EPSII_BP_1_GetBasicAppErrCountersResponseHandler = (pfEPSII_BP_1_GetBasicAppErrCountersResponseHandler_t) EPSII_BP_1_GetBasicAppErrCountersResponseHandlerImpl,
  .EPSII_BP_1_GetMainAppExceptionsResponseHandler = (pfEPSII_BP_1_GetMainAppExceptionsResponseHandler_t) EPSII_BP_1_GetMainAppExceptionsResponseHandlerImpl,
  .EPSII_BP_1_GetMainAppErrCountersResponseHandler = (pfEPSII_BP_1_GetMainAppErrCountersResponseHandler_t) EPSII_BP_1_GetMainAppErrCountersResponseHandlerImpl,
  .EPSII_BP_1_GetMainAppErrCounters2ResponseHandler = (pfEPSII_BP_1_GetMainAppErrCounters2ResponseHandler_t) EPSII_BP_1_GetMainAppErrCounters2ResponseHandlerImpl,
  .EPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandler = (pfEPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandler_t) EPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandlerImpl,
  .EPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandler = (pfEPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandler_t) EPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandlerImpl,
  .EPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandler = (pfEPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandler_t) EPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandlerImpl,
  .EPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandler = (pfEPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandler_t) EPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandlerImpl,
  .EPSII_BP_1_GetBalancerStatusResponseHandler = (pfEPSII_BP_1_GetBalancerStatusResponseHandler_t) EPSII_BP_1_GetBalancerStatusResponseHandlerImpl,
  .EPSII_BP_1_ResetDeviceResponseHandler = (pfEPSII_BP_1_ResetDeviceResponseHandler_t) EPSII_BP_1_ResetDeviceResponseHandlerImpl,
  .EPSII_BP_1_ForceInstallMainAppResponseHandler = (pfEPSII_BP_1_ForceInstallMainAppResponseHandler_t) EPSII_BP_1_ForceInstallMainAppResponseHandlerImpl,
  .EPSII_BP_1_ForceInstallBasicAppResponseHandler = (pfEPSII_BP_1_ForceInstallBasicAppResponseHandler_t) EPSII_BP_1_ForceInstallBasicAppResponseHandlerImpl,
  .EPSII_BP_1_GetBootLoaderErrCountersResponseHandler = (pfEPSII_BP_1_GetBootLoaderErrCountersResponseHandler_t) EPSII_BP_1_GetBootLoaderErrCountersResponseHandlerImpl,
  .EPSII_BP_1_ResetBootLdrErrCountersResponseHandler = (pfEPSII_BP_1_ResetBootLdrErrCountersResponseHandler_t) EPSII_BP_1_ResetBootLdrErrCountersResponseHandlerImpl,
  .EPSII_BP_1_SetChargerSettingsResponseHandler = (pfEPSII_BP_1_SetChargerSettingsResponseHandler_t) EPSII_BP_1_SetChargerSettingsResponseHandlerImpl,
  .EPSII_BP_1_SetRTCResponseHandler = (pfEPSII_BP_1_SetRTCResponseHandler_t) EPSII_BP_1_SetRTCResponseHandlerImpl,
  .EPSII_BP_1_GetRTCResponseHandler = (pfEPSII_BP_1_GetRTCResponseHandler_t) EPSII_BP_1_GetRTCResponseHandlerImpl,
  .EPSII_BP_1_LeaveNoHibModeResponseHandler = (pfEPSII_BP_1_LeaveNoHibModeResponseHandler_t) EPSII_BP_1_LeaveNoHibModeResponseHandlerImpl,
  .EPSII_BP_1_RequestPowerDownResponseHandler = (pfEPSII_BP_1_RequestPowerDownResponseHandler_t) EPSII_BP_1_RequestPowerDownResponseHandlerImpl,
  .EPSII_BP_1_GetBpModeSmRollingTraceResponseHandler = (pfEPSII_BP_1_GetBpModeSmRollingTraceResponseHandler_t) EPSII_BP_1_GetBpModeSmRollingTraceResponseHandlerImpl,
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Response handler for method EPSII_BP_1::GetDeviceInfo (ID = 0x00000001)
static void EPSII_BP_1_GetDeviceInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetDeviceInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetDeviceInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetDeviceInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetDeviceInfo@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetDeviceInfo@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetDeviceInfo (ID = 0x00000001)

// @START@ Response handler for method EPSII_BP_1::GetRAWSensors (ID = 0x00000002)
static void EPSII_BP_1_GetRAWSensorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetRAWSensorsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetRAWSensors@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetRAWSensors@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetRAWSensors@
        
        eps_ii_raw_sensors_notif(pRespCtx, pResponseData);
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetRAWSensors@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetRAWSensors (ID = 0x00000002)

// @START@ Response handler for method EPSII_BP_1::GetBatteryInfo (ID = 0x00000003)
static void EPSII_BP_1_GetBatteryInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBatteryInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBatteryInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBatteryInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBatteryInfo@
        
        // Callback to eps_ii drivers to update the datacache
        eps_ii_batt_info_notif(pRespCtx, pResponseData);
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBatteryInfo@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBatteryInfo (ID = 0x00000003)

// @START@ Response handler for method EPSII_BP_1::GetDeviceHealthInfo (ID = 0x00000004)
static void EPSII_BP_1_GetDeviceHealthInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetDeviceHealthInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetDeviceHealthInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetDeviceHealthInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetDeviceHealthInfo@
        
        eps_ii_bp_dev_health_notif(pRespCtx, pResponseData);
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetDeviceHealthInfo@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetDeviceHealthInfo (ID = 0x00000004)

// @START@ Response handler for method EPSII_BP_1::SetBatHeaterSettings (ID = 0x00000005)
static void EPSII_BP_1_SetBatHeaterSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetBatHeaterSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::SetBatHeaterSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::SetBatHeaterSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::SetBatHeaterSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::SetBatHeaterSettings@
    }
}
// @END@ Response handler for method EPSII_BP_1::SetBatHeaterSettings (ID = 0x00000005)

// @START@ Response handler for method EPSII_BP_1::GetBatHeaterSettings (ID = 0x00000006)
static void EPSII_BP_1_GetBatHeaterSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBatHeaterSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBatHeaterSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBatHeaterSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBatHeaterSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBatHeaterSettings@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBatHeaterSettings (ID = 0x00000006)

// @START@ Response handler for method EPSII_BP_1::SetBasicSettings (ID = 0x00000007)
static void EPSII_BP_1_SetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetBasicSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::SetBasicSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::SetBasicSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::SetBasicSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::SetBasicSettings@
    }
}
// @END@ Response handler for method EPSII_BP_1::SetBasicSettings (ID = 0x00000007)

// @START@ Response handler for method EPSII_BP_1::GetBasicSettings (ID = 0x00000008)
static void EPSII_BP_1_GetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBasicSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBasicSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBasicSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBasicSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBasicSettings@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBasicSettings (ID = 0x00000008)

// @START@ Response handler for method EPSII_BP_1::GetBasicAppExceptions (ID = 0x0000000B)
static void EPSII_BP_1_GetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBasicAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBasicAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBasicAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBasicAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBasicAppExceptions@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBasicAppExceptions (ID = 0x0000000B)

// @START@ Response handler for method EPSII_BP_1::GetBasicAppErrCounters (ID = 0x0000000C)
static void EPSII_BP_1_GetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBasicAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBasicAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBasicAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBasicAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBasicAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBasicAppErrCounters (ID = 0x0000000C)

// @START@ Response handler for method EPSII_BP_1::GetMainAppExceptions (ID = 0x0000000D)
static void EPSII_BP_1_GetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetMainAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetMainAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetMainAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetMainAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetMainAppExceptions@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetMainAppExceptions (ID = 0x0000000D)

// @START@ Response handler for method EPSII_BP_1::GetMainAppErrCounters (ID = 0x0000000E)
static void EPSII_BP_1_GetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetMainAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetMainAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetMainAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetMainAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetMainAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetMainAppErrCounters (ID = 0x0000000E)

// @START@ Response handler for method EPSII_BP_1::GetMainAppErrCounters2 (ID = 0x00000030)
static void EPSII_BP_1_GetMainAppErrCounters2ResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetMainAppErrCounters2ResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetMainAppErrCounters2@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetMainAppErrCounters2@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetMainAppErrCounters2@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetMainAppErrCounters2@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetMainAppErrCounters2 (ID = 0x00000030)

// @START@ Response handler for method EPSII_BP_1::OnESCP_ResetMainAppErrCounters (ID = 0x0000000F)
static void EPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetMainAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::OnESCP_ResetMainAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::OnESCP_ResetMainAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::OnESCP_ResetMainAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::OnESCP_ResetMainAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_BP_1::OnESCP_ResetMainAppErrCounters (ID = 0x0000000F)

// @START@ Response handler for method EPSII_BP_1::OnESCP_ResetMainAppExceptions (ID = 0x00000010)
static void EPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetMainAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::OnESCP_ResetMainAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::OnESCP_ResetMainAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::OnESCP_ResetMainAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::OnESCP_ResetMainAppExceptions@
    }
}
// @END@ Response handler for method EPSII_BP_1::OnESCP_ResetMainAppExceptions (ID = 0x00000010)

// @START@ Response handler for method EPSII_BP_1::OnESCP_ResetBasicAppErrCounters (ID = 0x00000011)
static void EPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetBasicAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::OnESCP_ResetBasicAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::OnESCP_ResetBasicAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::OnESCP_ResetBasicAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::OnESCP_ResetBasicAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_BP_1::OnESCP_ResetBasicAppErrCounters (ID = 0x00000011)

// @START@ Response handler for method EPSII_BP_1::OnESCP_ResetBasicAppExceptions (ID = 0x00000012)
static void EPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1OnESCP_ResetBasicAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::OnESCP_ResetBasicAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::OnESCP_ResetBasicAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::OnESCP_ResetBasicAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::OnESCP_ResetBasicAppExceptions@
    }
}
// @END@ Response handler for method EPSII_BP_1::OnESCP_ResetBasicAppExceptions (ID = 0x00000012)

// @START@ Response handler for method EPSII_BP_1::GetBalancerStatus (ID = 0x00000013)
static void EPSII_BP_1_GetBalancerStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBalancerStatusResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBalancerStatus@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBalancerStatus@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBalancerStatus@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBalancerStatus@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBalancerStatus (ID = 0x00000013)

// @START@ Response handler for method EPSII_BP_1::ResetDevice (ID = 0x00000020)
static void EPSII_BP_1_ResetDeviceResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ResetDeviceResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::ResetDevice@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::ResetDevice@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::ResetDevice@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::ResetDevice@
    }
}
// @END@ Response handler for method EPSII_BP_1::ResetDevice (ID = 0x00000020)

// @START@ Response handler for method EPSII_BP_1::ForceInstallMainApp (ID = 0x00000021)
static void EPSII_BP_1_ForceInstallMainAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ForceInstallMainAppResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::ForceInstallMainApp@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::ForceInstallMainApp@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::ForceInstallMainApp@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::ForceInstallMainApp@
    }
}
// @END@ Response handler for method EPSII_BP_1::ForceInstallMainApp (ID = 0x00000021)

// @START@ Response handler for method EPSII_BP_1::ForceInstallBasicApp (ID = 0x00000022)
static void EPSII_BP_1_ForceInstallBasicAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ForceInstallBasicAppResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::ForceInstallBasicApp@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::ForceInstallBasicApp@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::ForceInstallBasicApp@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::ForceInstallBasicApp@
    }
}
// @END@ Response handler for method EPSII_BP_1::ForceInstallBasicApp (ID = 0x00000022)

// @START@ Response handler for method EPSII_BP_1::GetBootLoaderErrCounters (ID = 0x00000023)
static void EPSII_BP_1_GetBootLoaderErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBootLoaderErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBootLoaderErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBootLoaderErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBootLoaderErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBootLoaderErrCounters@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBootLoaderErrCounters (ID = 0x00000023)

// @START@ Response handler for method EPSII_BP_1::ResetBootLdrErrCounters (ID = 0x00000024)
static void EPSII_BP_1_ResetBootLdrErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1ResetBootLdrErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::ResetBootLdrErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::ResetBootLdrErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::ResetBootLdrErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::ResetBootLdrErrCounters@
    }
}
// @END@ Response handler for method EPSII_BP_1::ResetBootLdrErrCounters (ID = 0x00000024)

// @START@ Response handler for method EPSII_BP_1::SetChargerSettings (ID = 0x00000025)
static void EPSII_BP_1_SetChargerSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetChargerSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::SetChargerSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::SetChargerSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::SetChargerSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::SetChargerSettings@
    }
}
// @END@ Response handler for method EPSII_BP_1::SetChargerSettings (ID = 0x00000025)

// @START@ Response handler for method EPSII_BP_1::SetRTC (ID = 0x00000026)
static void EPSII_BP_1_SetRTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1SetRTCResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::SetRTC@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::SetRTC@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::SetRTC@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::SetRTC@
    }
}
// @END@ Response handler for method EPSII_BP_1::SetRTC (ID = 0x00000026)

// @START@ Response handler for method EPSII_BP_1::GetRTC (ID = 0x00000027)
static void EPSII_BP_1_GetRTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetRTCResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetRTC@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetRTC@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetRTC@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetRTC@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetRTC (ID = 0x00000027)

// @START@ Response handler for method EPSII_BP_1::LeaveNoHibMode (ID = 0x00000028)
static void EPSII_BP_1_LeaveNoHibModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1LeaveNoHibModeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::LeaveNoHibMode@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::LeaveNoHibMode@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::LeaveNoHibMode@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::LeaveNoHibMode@
    }
}
// @END@ Response handler for method EPSII_BP_1::LeaveNoHibMode (ID = 0x00000028)

// @START@ Response handler for method EPSII_BP_1::RequestPowerDown (ID = 0x00000029)
static void EPSII_BP_1_RequestPowerDownResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1RequestPowerDownResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::RequestPowerDown@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::RequestPowerDown@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::RequestPowerDown@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::RequestPowerDown@
    }
}
// @END@ Response handler for method EPSII_BP_1::RequestPowerDown (ID = 0x00000029)

// @START@ Response handler for method EPSII_BP_1::GetBpModeSmRollingTrace (ID = 0x00000031)
static void EPSII_BP_1_GetBpModeSmRollingTraceResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_BP_1GetBpModeSmRollingTraceResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_BP_1::GetBpModeSmRollingTrace@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_BP_1::GetBpModeSmRollingTrace@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_BP_1::GetBpModeSmRollingTrace@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_BP_1::GetBpModeSmRollingTrace@
    }
}
// @END@ Response handler for method EPSII_BP_1::GetBpModeSmRollingTrace (ID = 0x00000031)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void EPSII_BP_1ClientAppInit(void)
{
    EPSII_BP_1_registerClientApi(&EPSII_BP_1ClientApiCtx);
}
