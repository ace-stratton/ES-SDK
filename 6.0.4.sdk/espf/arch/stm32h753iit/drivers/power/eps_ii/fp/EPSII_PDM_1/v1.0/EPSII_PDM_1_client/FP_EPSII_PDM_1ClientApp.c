/*!
********************************************************************************************
* @file FP_EPSII_PDM_1ClientApp.c
* @brief ClientApp implementation template generator
********************************************************************************************
* @version           interface EPSII_PDM_1 v1.0
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

#include "FP_EPSII_PDM_1ProtocolClient.h"

// @START_USER@ USER_INCLUDES
#include "eps_ctrl_cfg.h"
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

static void EPSII_PDM_1_GetDeviceInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetDeviceInfoResponseData_t* pResponseData);

static void EPSII_PDM_1_GetPowerDistributionInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetPowerDistributionInfoResponseData_t* pResponseData);

static void EPSII_PDM_1_GetDeviceHealthInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetDeviceHealthInfoResponseData_t* pResponseData);

static void EPSII_PDM_1_SetPC104GPIOResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1SetPC104GPIOResponseData_t* pResponseData);

static void EPSII_PDM_1_GetPC104GPIOResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetPC104GPIOResponseData_t* pResponseData);

static void EPSII_PDM_1_GetRAWSensorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetRAWSensorsResponseData_t* pResponseData);

static void EPSII_PDM_1_SetPowerOutputsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1SetPowerOutputsResponseData_t* pResponseData);

static void EPSII_PDM_1_GetPowerOutputsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetPowerOutputsResponseData_t* pResponseData);

static void EPSII_PDM_1_SetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1SetBasicSettingsResponseData_t* pResponseData);

static void EPSII_PDM_1_GetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBasicSettingsResponseData_t* pResponseData);

static void EPSII_PDM_1_GetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBasicAppExceptionsResponseData_t* pResponseData);

static void EPSII_PDM_1_GetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBasicAppErrCountersResponseData_t* pResponseData);

static void EPSII_PDM_1_GetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetMainAppExceptionsResponseData_t* pResponseData);

static void EPSII_PDM_1_GetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetMainAppErrCountersResponseData_t* pResponseData);

static void EPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetMainAppErrCountersResponseData_t* pResponseData);

static void EPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetMainAppExceptionsResponseData_t* pResponseData);

static void EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetBasicAppErrCountersResponseData_t* pResponseData);

static void EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetBasicAppExceptionsResponseData_t* pResponseData);

static void EPSII_PDM_1_GetBulkTelemetryResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBulkTelemetryResponseData_t* pResponseData);

static void EPSII_PDM_1_ResetDeviceResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ResetDeviceResponseData_t* pResponseData);

static void EPSII_PDM_1_ForceInstallMainAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ForceInstallMainAppResponseData_t* pResponseData);

static void EPSII_PDM_1_ForceInstallBasicAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ForceInstallBasicAppResponseData_t* pResponseData);

static void EPSII_PDM_1_GetBootLoaderErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBootLoaderErrCountersResponseData_t* pResponseData);

static void EPSII_PDM_1_ResetBootLdrErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ResetBootLdrErrCountersResponseData_t* pResponseData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static EPSII_PDM_1_ClientApi_t EPSII_PDM_1ClientApiCtx =
{
  .EPSII_PDM_1_GetDeviceInfoResponseHandler = (pfEPSII_PDM_1_GetDeviceInfoResponseHandler_t) EPSII_PDM_1_GetDeviceInfoResponseHandlerImpl,
  .EPSII_PDM_1_GetPowerDistributionInfoResponseHandler = (pfEPSII_PDM_1_GetPowerDistributionInfoResponseHandler_t) EPSII_PDM_1_GetPowerDistributionInfoResponseHandlerImpl,
  .EPSII_PDM_1_GetDeviceHealthInfoResponseHandler = (pfEPSII_PDM_1_GetDeviceHealthInfoResponseHandler_t) EPSII_PDM_1_GetDeviceHealthInfoResponseHandlerImpl,
  .EPSII_PDM_1_SetPC104GPIOResponseHandler = (pfEPSII_PDM_1_SetPC104GPIOResponseHandler_t) EPSII_PDM_1_SetPC104GPIOResponseHandlerImpl,
  .EPSII_PDM_1_GetPC104GPIOResponseHandler = (pfEPSII_PDM_1_GetPC104GPIOResponseHandler_t) EPSII_PDM_1_GetPC104GPIOResponseHandlerImpl,
  .EPSII_PDM_1_GetRAWSensorsResponseHandler = (pfEPSII_PDM_1_GetRAWSensorsResponseHandler_t) EPSII_PDM_1_GetRAWSensorsResponseHandlerImpl,
  .EPSII_PDM_1_SetPowerOutputsResponseHandler = (pfEPSII_PDM_1_SetPowerOutputsResponseHandler_t) EPSII_PDM_1_SetPowerOutputsResponseHandlerImpl,
  .EPSII_PDM_1_GetPowerOutputsResponseHandler = (pfEPSII_PDM_1_GetPowerOutputsResponseHandler_t) EPSII_PDM_1_GetPowerOutputsResponseHandlerImpl,
  .EPSII_PDM_1_SetBasicSettingsResponseHandler = (pfEPSII_PDM_1_SetBasicSettingsResponseHandler_t) EPSII_PDM_1_SetBasicSettingsResponseHandlerImpl,
  .EPSII_PDM_1_GetBasicSettingsResponseHandler = (pfEPSII_PDM_1_GetBasicSettingsResponseHandler_t) EPSII_PDM_1_GetBasicSettingsResponseHandlerImpl,
  .EPSII_PDM_1_GetBasicAppExceptionsResponseHandler = (pfEPSII_PDM_1_GetBasicAppExceptionsResponseHandler_t) EPSII_PDM_1_GetBasicAppExceptionsResponseHandlerImpl,
  .EPSII_PDM_1_GetBasicAppErrCountersResponseHandler = (pfEPSII_PDM_1_GetBasicAppErrCountersResponseHandler_t) EPSII_PDM_1_GetBasicAppErrCountersResponseHandlerImpl,
  .EPSII_PDM_1_GetMainAppExceptionsResponseHandler = (pfEPSII_PDM_1_GetMainAppExceptionsResponseHandler_t) EPSII_PDM_1_GetMainAppExceptionsResponseHandlerImpl,
  .EPSII_PDM_1_GetMainAppErrCountersResponseHandler = (pfEPSII_PDM_1_GetMainAppErrCountersResponseHandler_t) EPSII_PDM_1_GetMainAppErrCountersResponseHandlerImpl,
  .EPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandler = (pfEPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandler_t) EPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandlerImpl,
  .EPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandler = (pfEPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandler_t) EPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandlerImpl,
  .EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandler = (pfEPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandler_t) EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandlerImpl,
  .EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandler = (pfEPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandler_t) EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandlerImpl,
  .EPSII_PDM_1_GetBulkTelemetryResponseHandler = (pfEPSII_PDM_1_GetBulkTelemetryResponseHandler_t) EPSII_PDM_1_GetBulkTelemetryResponseHandlerImpl,
  .EPSII_PDM_1_ResetDeviceResponseHandler = (pfEPSII_PDM_1_ResetDeviceResponseHandler_t) EPSII_PDM_1_ResetDeviceResponseHandlerImpl,
  .EPSII_PDM_1_ForceInstallMainAppResponseHandler = (pfEPSII_PDM_1_ForceInstallMainAppResponseHandler_t) EPSII_PDM_1_ForceInstallMainAppResponseHandlerImpl,
  .EPSII_PDM_1_ForceInstallBasicAppResponseHandler = (pfEPSII_PDM_1_ForceInstallBasicAppResponseHandler_t) EPSII_PDM_1_ForceInstallBasicAppResponseHandlerImpl,
  .EPSII_PDM_1_GetBootLoaderErrCountersResponseHandler = (pfEPSII_PDM_1_GetBootLoaderErrCountersResponseHandler_t) EPSII_PDM_1_GetBootLoaderErrCountersResponseHandlerImpl,
  .EPSII_PDM_1_ResetBootLdrErrCountersResponseHandler = (pfEPSII_PDM_1_ResetBootLdrErrCountersResponseHandler_t) EPSII_PDM_1_ResetBootLdrErrCountersResponseHandlerImpl,
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Response handler for method EPSII_PDM_1::GetDeviceInfo (ID = 0x00000001)
static void EPSII_PDM_1_GetDeviceInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetDeviceInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetDeviceInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetDeviceInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetDeviceInfo@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetDeviceInfo@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetDeviceInfo (ID = 0x00000001)

// @START@ Response handler for method EPSII_PDM_1::GetPowerDistributionInfo (ID = 0x00000002)
static void EPSII_PDM_1_GetPowerDistributionInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetPowerDistributionInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetPowerDistributionInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetPowerDistributionInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetPowerDistributionInfo@
        
        eps_ii_pow_dist_info_notif(pResponseData);
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetPowerDistributionInfo@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetPowerDistributionInfo (ID = 0x00000002)

// @START@ Response handler for method EPSII_PDM_1::GetDeviceHealthInfo (ID = 0x00000003)
static void EPSII_PDM_1_GetDeviceHealthInfoResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetDeviceHealthInfoResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetDeviceHealthInfo@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetDeviceHealthInfo@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetDeviceHealthInfo@
        
        eps_ii_pdm_dev_health_notif(pResponseData);
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetDeviceHealthInfo@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetDeviceHealthInfo (ID = 0x00000003)

// @START@ Response handler for method EPSII_PDM_1::SetPC104GPIO (ID = 0x00000004)
static void EPSII_PDM_1_SetPC104GPIOResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1SetPC104GPIOResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::SetPC104GPIO@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::SetPC104GPIO@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::SetPC104GPIO@
        
        // Notify eps_ctrl
        bool b_success = (EPSII_PDM_1_SGGPIO_SETERROR_SGGPIOE_SUCCESS == pResponseData->eErr);
        eps_ctrl_cfg_set_ch_notif_eps_ii(pRespCtx->seqId, b_success);
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::SetPC104GPIO@
    }
}
// @END@ Response handler for method EPSII_PDM_1::SetPC104GPIO (ID = 0x00000004)

// @START@ Response handler for method EPSII_PDM_1::GetPC104GPIO (ID = 0x00000005)
static void EPSII_PDM_1_GetPC104GPIOResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetPC104GPIOResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetPC104GPIO@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetPC104GPIO@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetPC104GPIO@
        
        eps_ctrl_cfg_get_ch_notif_eps_ii_gpio(pRespCtx->seqId, pResponseData->u8CurrentValues);
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetPC104GPIO@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetPC104GPIO (ID = 0x00000005)

// @START@ Response handler for method EPSII_PDM_1::GetRAWSensors (ID = 0x00000006)
static void EPSII_PDM_1_GetRAWSensorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetRAWSensorsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetRAWSensors@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetRAWSensors@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetRAWSensors@
        
        eps_ii_raw_sensors_notif(pRespCtx, pResponseData);
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetRAWSensors@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetRAWSensors (ID = 0x00000006)

// @START@ Response handler for method EPSII_PDM_1::SetPowerOutputs (ID = 0x00000007)
static void EPSII_PDM_1_SetPowerOutputsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1SetPowerOutputsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::SetPowerOutputs@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::SetPowerOutputs@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::SetPowerOutputs@

        // Notify eps_ctrl
        bool b_success = (EPSII_PDM_1_SGPO_SETERROR_SGPOSE_SUCCESS == pResponseData->eErr);
        eps_ctrl_cfg_set_ch_notif_eps_ii(pRespCtx->seqId, b_success);

        // @USER_CODE_SECTION_END@EPSII_PDM_1::SetPowerOutputs@
    }
}
// @END@ Response handler for method EPSII_PDM_1::SetPowerOutputs (ID = 0x00000007)

// @START@ Response handler for method EPSII_PDM_1::GetPowerOutputs (ID = 0x00000008)
static void EPSII_PDM_1_GetPowerOutputsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetPowerOutputsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetPowerOutputs@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetPowerOutputs@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetPowerOutputs@

        eps_ctrl_cfg_get_ch_notif_eps_ii_sgpo(pRespCtx->seqId, pResponseData->u32ValuesMask);

        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetPowerOutputs@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetPowerOutputs (ID = 0x00000008)

// @START@ Response handler for method EPSII_PDM_1::SetBasicSettings (ID = 0x00000009)
static void EPSII_PDM_1_SetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1SetBasicSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::SetBasicSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::SetBasicSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::SetBasicSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::SetBasicSettings@
    }
}
// @END@ Response handler for method EPSII_PDM_1::SetBasicSettings (ID = 0x00000009)

// @START@ Response handler for method EPSII_PDM_1::GetBasicSettings (ID = 0x0000000A)
static void EPSII_PDM_1_GetBasicSettingsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBasicSettingsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetBasicSettings@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetBasicSettings@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetBasicSettings@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetBasicSettings@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetBasicSettings (ID = 0x0000000A)

// @START@ Response handler for method EPSII_PDM_1::GetBasicAppExceptions (ID = 0x0000000B)
static void EPSII_PDM_1_GetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBasicAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetBasicAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetBasicAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetBasicAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetBasicAppExceptions@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetBasicAppExceptions (ID = 0x0000000B)

// @START@ Response handler for method EPSII_PDM_1::GetBasicAppErrCounters (ID = 0x0000000C)
static void EPSII_PDM_1_GetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBasicAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetBasicAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetBasicAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetBasicAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetBasicAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetBasicAppErrCounters (ID = 0x0000000C)

// @START@ Response handler for method EPSII_PDM_1::GetMainAppExceptions (ID = 0x0000000D)
static void EPSII_PDM_1_GetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetMainAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetMainAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetMainAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetMainAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetMainAppExceptions@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetMainAppExceptions (ID = 0x0000000D)

// @START@ Response handler for method EPSII_PDM_1::GetMainAppErrCounters (ID = 0x0000000E)
static void EPSII_PDM_1_GetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetMainAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetMainAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetMainAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetMainAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetMainAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetMainAppErrCounters (ID = 0x0000000E)

// @START@ Response handler for method EPSII_PDM_1::OnESCP_ResetMainAppErrCounters (ID = 0x0000000F)
static void EPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetMainAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::OnESCP_ResetMainAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::OnESCP_ResetMainAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::OnESCP_ResetMainAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::OnESCP_ResetMainAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_PDM_1::OnESCP_ResetMainAppErrCounters (ID = 0x0000000F)

// @START@ Response handler for method EPSII_PDM_1::OnESCP_ResetMainAppExceptions (ID = 0x00000010)
static void EPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetMainAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::OnESCP_ResetMainAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::OnESCP_ResetMainAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::OnESCP_ResetMainAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::OnESCP_ResetMainAppExceptions@
    }
}
// @END@ Response handler for method EPSII_PDM_1::OnESCP_ResetMainAppExceptions (ID = 0x00000010)

// @START@ Response handler for method EPSII_PDM_1::OnESCP_ResetBasicAppErrCounters (ID = 0x00000011)
static void EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetBasicAppErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::OnESCP_ResetBasicAppErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::OnESCP_ResetBasicAppErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::OnESCP_ResetBasicAppErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::OnESCP_ResetBasicAppErrCounters@
    }
}
// @END@ Response handler for method EPSII_PDM_1::OnESCP_ResetBasicAppErrCounters (ID = 0x00000011)

// @START@ Response handler for method EPSII_PDM_1::OnESCP_ResetBasicAppExceptions (ID = 0x00000012)
static void EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1OnESCP_ResetBasicAppExceptionsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::OnESCP_ResetBasicAppExceptions@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::OnESCP_ResetBasicAppExceptions@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::OnESCP_ResetBasicAppExceptions@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::OnESCP_ResetBasicAppExceptions@
    }
}
// @END@ Response handler for method EPSII_PDM_1::OnESCP_ResetBasicAppExceptions (ID = 0x00000012)

// @START@ Response handler for method EPSII_PDM_1::GetBulkTelemetry (ID = 0x00000013)
static void EPSII_PDM_1_GetBulkTelemetryResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBulkTelemetryResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetBulkTelemetry@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetBulkTelemetry@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetBulkTelemetry@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetBulkTelemetry@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetBulkTelemetry (ID = 0x00000013)

// @START@ Response handler for method EPSII_PDM_1::ResetDevice (ID = 0x00000020)
static void EPSII_PDM_1_ResetDeviceResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ResetDeviceResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::ResetDevice@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::ResetDevice@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::ResetDevice@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::ResetDevice@
    }
}
// @END@ Response handler for method EPSII_PDM_1::ResetDevice (ID = 0x00000020)

// @START@ Response handler for method EPSII_PDM_1::ForceInstallMainApp (ID = 0x00000021)
static void EPSII_PDM_1_ForceInstallMainAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ForceInstallMainAppResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::ForceInstallMainApp@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::ForceInstallMainApp@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::ForceInstallMainApp@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::ForceInstallMainApp@
    }
}
// @END@ Response handler for method EPSII_PDM_1::ForceInstallMainApp (ID = 0x00000021)

// @START@ Response handler for method EPSII_PDM_1::ForceInstallBasicApp (ID = 0x00000022)
static void EPSII_PDM_1_ForceInstallBasicAppResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ForceInstallBasicAppResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::ForceInstallBasicApp@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::ForceInstallBasicApp@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::ForceInstallBasicApp@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::ForceInstallBasicApp@
    }
}
// @END@ Response handler for method EPSII_PDM_1::ForceInstallBasicApp (ID = 0x00000022)

// @START@ Response handler for method EPSII_PDM_1::GetBootLoaderErrCounters (ID = 0x00000023)
static void EPSII_PDM_1_GetBootLoaderErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1GetBootLoaderErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::GetBootLoaderErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::GetBootLoaderErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::GetBootLoaderErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::GetBootLoaderErrCounters@
    }
}
// @END@ Response handler for method EPSII_PDM_1::GetBootLoaderErrCounters (ID = 0x00000023)

// @START@ Response handler for method EPSII_PDM_1::ResetBootLdrErrCounters (ID = 0x00000024)
static void EPSII_PDM_1_ResetBootLdrErrCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const EPSII_PDM_1ResetBootLdrErrCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@EPSII_PDM_1::ResetBootLdrErrCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@EPSII_PDM_1::ResetBootLdrErrCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@EPSII_PDM_1::ResetBootLdrErrCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@EPSII_PDM_1::ResetBootLdrErrCounters@
    }
}
// @END@ Response handler for method EPSII_PDM_1::ResetBootLdrErrCounters (ID = 0x00000024)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void EPSII_PDM_1ClientAppInit(void)
{
    EPSII_PDM_1_registerClientApi(&EPSII_PDM_1ClientApiCtx);
}
