/*!
********************************************************************************************
* @file FP_SPClientApp.c
* @brief ClientApp implementation template generator
********************************************************************************************
* @version           interface SP v0.4
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

#include "FP_SPProtocolClient.h"

// @START_USER@ USER_INCLUDES
#include "sp_service.h"

// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL

static void SP_GetSoftwareVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetSoftwareVersionResponseData_t* pResponseData);

static void SP_StartDeploymentResponseHandlerImpl(RespContext_t* pRespCtx);

static void SP_GetDeploymentStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetDeploymentStatusResponseData_t* pResponseData);

static void SP_GetUptimeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetUptimeResponseData_t* pResponseData);

static void SP_GetTelemetryResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetTelemetryResponseData_t* pResponseData);

static void SP_GetMainGyroDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetMainGyroDataResponseData_t* pResponseData);

static void SP_GetExtGyroDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetExtGyroDataResponseData_t* pResponseData);

static void SP_WriteMainGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx);

static void SP_WriteExtGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx);

static void SP_GetMainGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetMainGyroRegisterResponseData_t* pResponseData);

static void SP_GetExtGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetExtGyroRegisterResponseData_t* pResponseData);

static void SP_RestartFMWResponseHandlerImpl(RespContext_t* pRespCtx);

static void SP_WriteMTQParametersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPWriteMTQParametersResponseData_t* pResponseData);

static void SP_GetMTQParametersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetMTQParametersResponseData_t* pResponseData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static SP_ClientApi_t SPClientApiCtx =
{
  .SP_GetSoftwareVersionResponseHandler = (pfSP_GetSoftwareVersionResponseHandler_t) SP_GetSoftwareVersionResponseHandlerImpl,
  .SP_StartDeploymentResponseHandler = (pfSP_StartDeploymentResponseHandler_t) SP_StartDeploymentResponseHandlerImpl,
  .SP_GetDeploymentStatusResponseHandler = (pfSP_GetDeploymentStatusResponseHandler_t) SP_GetDeploymentStatusResponseHandlerImpl,
  .SP_GetUptimeResponseHandler = (pfSP_GetUptimeResponseHandler_t) SP_GetUptimeResponseHandlerImpl,
  .SP_GetTelemetryResponseHandler = (pfSP_GetTelemetryResponseHandler_t) SP_GetTelemetryResponseHandlerImpl,
  .SP_GetMainGyroDataResponseHandler = (pfSP_GetMainGyroDataResponseHandler_t) SP_GetMainGyroDataResponseHandlerImpl,
  .SP_GetExtGyroDataResponseHandler = (pfSP_GetExtGyroDataResponseHandler_t) SP_GetExtGyroDataResponseHandlerImpl,
  .SP_WriteMainGyroRegisterResponseHandler = (pfSP_WriteMainGyroRegisterResponseHandler_t) SP_WriteMainGyroRegisterResponseHandlerImpl,
  .SP_WriteExtGyroRegisterResponseHandler = (pfSP_WriteExtGyroRegisterResponseHandler_t) SP_WriteExtGyroRegisterResponseHandlerImpl,
  .SP_GetMainGyroRegisterResponseHandler = (pfSP_GetMainGyroRegisterResponseHandler_t) SP_GetMainGyroRegisterResponseHandlerImpl,
  .SP_GetExtGyroRegisterResponseHandler = (pfSP_GetExtGyroRegisterResponseHandler_t) SP_GetExtGyroRegisterResponseHandlerImpl,
  .SP_RestartFMWResponseHandler = (pfSP_RestartFMWResponseHandler_t) SP_RestartFMWResponseHandlerImpl,
  .SP_WriteMTQParametersResponseHandler = (pfSP_WriteMTQParametersResponseHandler_t) SP_WriteMTQParametersResponseHandlerImpl,
  .SP_GetMTQParametersResponseHandler = (pfSP_GetMTQParametersResponseHandler_t) SP_GetMTQParametersResponseHandlerImpl,
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Response handler for method SP::GetSoftwareVersion (ID = 0x00000000)
static void SP_GetSoftwareVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetSoftwareVersionResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetSoftwareVersion@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetSoftwareVersion@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetSoftwareVersion@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetSoftwareVersion@
    }
}
// @END@ Response handler for method SP::GetSoftwareVersion (ID = 0x00000000)

// @START@ Response handler for method SP::StartDeployment (ID = 0x00000001)
static void SP_StartDeploymentResponseHandlerImpl(RespContext_t* pRespCtx)
{
    // @USER_VAR_SECTION_START@SP::StartDeployment@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::StartDeployment@

    if (pRespCtx != NULL)
    {
        // @USER_CODE_SECTION_START@SP::StartDeployment@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::StartDeployment@
    }
}
// @END@ Response handler for method SP::StartDeployment (ID = 0x00000001)

// @START@ Response handler for method SP::GetDeploymentStatus (ID = 0x00000002)
static void SP_GetDeploymentStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetDeploymentStatusResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetDeploymentStatus@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetDeploymentStatus@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetDeploymentStatus@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetDeploymentStatus@
    }
}
// @END@ Response handler for method SP::GetDeploymentStatus (ID = 0x00000002)

// @START@ Response handler for method SP::GetUptime (ID = 0x00000003)
static void SP_GetUptimeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetUptimeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetUptime@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetUptime@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetUptime@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetUptime@
    }
}
// @END@ Response handler for method SP::GetUptime (ID = 0x00000003)

// @START@ Response handler for method SP::GetTelemetry (ID = 0x00000004)
static void SP_GetTelemetryResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetTelemetryResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetTelemetry@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetTelemetry@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetTelemetry@
        
        sp_response_received(pRespCtx, pResponseData);
        
        // @USER_CODE_SECTION_END@SP::GetTelemetry@
    }
}
// @END@ Response handler for method SP::GetTelemetry (ID = 0x00000004)

// @START@ Response handler for method SP::GetMainGyroData (ID = 0x00000005)
static void SP_GetMainGyroDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetMainGyroDataResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetMainGyroData@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetMainGyroData@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetMainGyroData@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetMainGyroData@
    }
}
// @END@ Response handler for method SP::GetMainGyroData (ID = 0x00000005)

// @START@ Response handler for method SP::GetExtGyroData (ID = 0x00000006)
static void SP_GetExtGyroDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetExtGyroDataResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetExtGyroData@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetExtGyroData@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetExtGyroData@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetExtGyroData@
    }
}
// @END@ Response handler for method SP::GetExtGyroData (ID = 0x00000006)

// @START@ Response handler for method SP::WriteMainGyroRegister (ID = 0x00000007)
static void SP_WriteMainGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx)
{
    // @USER_VAR_SECTION_START@SP::WriteMainGyroRegister@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::WriteMainGyroRegister@

    if (pRespCtx != NULL)
    {
        // @USER_CODE_SECTION_START@SP::WriteMainGyroRegister@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::WriteMainGyroRegister@
    }
}
// @END@ Response handler for method SP::WriteMainGyroRegister (ID = 0x00000007)

// @START@ Response handler for method SP::WriteExtGyroRegister (ID = 0x00000008)
static void SP_WriteExtGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx)
{
    // @USER_VAR_SECTION_START@SP::WriteExtGyroRegister@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::WriteExtGyroRegister@

    if (pRespCtx != NULL)
    {
        // @USER_CODE_SECTION_START@SP::WriteExtGyroRegister@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::WriteExtGyroRegister@
    }
}
// @END@ Response handler for method SP::WriteExtGyroRegister (ID = 0x00000008)

// @START@ Response handler for method SP::GetMainGyroRegister (ID = 0x00000009)
static void SP_GetMainGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetMainGyroRegisterResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetMainGyroRegister@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetMainGyroRegister@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetMainGyroRegister@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetMainGyroRegister@
    }
}
// @END@ Response handler for method SP::GetMainGyroRegister (ID = 0x00000009)

// @START@ Response handler for method SP::GetExtGyroRegister (ID = 0x0000000A)
static void SP_GetExtGyroRegisterResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetExtGyroRegisterResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetExtGyroRegister@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetExtGyroRegister@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetExtGyroRegister@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetExtGyroRegister@
    }
}
// @END@ Response handler for method SP::GetExtGyroRegister (ID = 0x0000000A)

// @START@ Response handler for method SP::RestartFMW (ID = 0x0000000B)
static void SP_RestartFMWResponseHandlerImpl(RespContext_t* pRespCtx)
{
    // @USER_VAR_SECTION_START@SP::RestartFMW@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::RestartFMW@

    if (pRespCtx != NULL)
    {
        // @USER_CODE_SECTION_START@SP::RestartFMW@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::RestartFMW@
    }
}
// @END@ Response handler for method SP::RestartFMW (ID = 0x0000000B)

// @START@ Response handler for method SP::WriteMTQParameters (ID = 0x0000000C)
static void SP_WriteMTQParametersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPWriteMTQParametersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::WriteMTQParameters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::WriteMTQParameters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::WriteMTQParameters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::WriteMTQParameters@
    }
}
// @END@ Response handler for method SP::WriteMTQParameters (ID = 0x0000000C)

// @START@ Response handler for method SP::GetMTQParameters (ID = 0x0000000D)
static void SP_GetMTQParametersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SPGetMTQParametersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SP::GetMTQParameters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SP::GetMTQParameters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SP::GetMTQParameters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SP::GetMTQParameters@
    }
}
// @END@ Response handler for method SP::GetMTQParameters (ID = 0x0000000D)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void SPClientAppInit(void)
{
    SP_registerClientApi(&SPClientApiCtx);
}
