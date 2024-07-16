/*!
********************************************************************************************
* @file FP_ModuleIdServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface ModuleId v0.1
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

#include "FP_ModuleIdProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include <string.h>
#include "module_id.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void ModuleId_getModuleVersionInfoRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static ModuleId_ServerApi_t ModuleIdServerApiCtx =
{
  .ModuleId_getModuleVersionInfoRequestHandler = (pfModuleId_getModuleVersionInfoRequestHandler_t) ModuleId_getModuleVersionInfoRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method ModuleId::getModuleVersionInfo (ID = 0x00000000)
static void ModuleId_getModuleVersionInfoRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    MODULEID_VersionInfo_t sSettings;

    // @USER_VAR_SECTION_START@ModuleId::getModuleVersionInfo@
    // Put your local variables in this section to preserve during merge!
    MODID_VersionInfo_t versionInfo;
    // @USER_VAR_SECTION_END@ModuleId::getModuleVersionInfo@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@ModuleId::getModuleVersionInfo@
        module_id_get_info(&versionInfo);

        sSettings.u8ActiveImageId = versionInfo.u8ActiveImageId;
        sSettings.eActiveImageType = versionInfo.eActiveImageType;
        sSettings.sFwVersion.u16Major = versionInfo.sFwVersion.u16Major;
        sSettings.sFwVersion.u16Minor = versionInfo.sFwVersion.u16Minor;
        sSettings.sFwVersion.u16Patch = versionInfo.sFwVersion.u16Patch;
        sSettings.sHwVersion.u16Major = versionInfo.sHwVersion.u16Major;
        sSettings.sHwVersion.u16Minor = versionInfo.sHwVersion.u16Minor;
        sSettings.sHwVersion.u16Patch = versionInfo.sHwVersion.u16Patch;
        sSettings.u16ModuleType = versionInfo.u16ModuleType;
        (void) memcpy(sSettings.au8BuildDate, versionInfo.au8BuildDate, sizeof(sSettings.au8BuildDate));
        (void) memcpy(sSettings.au8BuildTime, versionInfo.au8BuildTime, sizeof(sSettings.au8BuildTime));
        (void) memcpy(sSettings.au8HwSerialNumber, versionInfo.au8HwSerialNumber, sizeof(sSettings.au8HwSerialNumber));
        (void) memcpy(sSettings.au8BuildDescription, versionInfo.au8BuildDescription, sizeof(sSettings.au8BuildDescription));
        // @USER_CODE_SECTION_END@ModuleId::getModuleVersionInfo@

        respResult = ModuleId_getModuleVersionInfoResp(
                        &respCtx,
                        &sSettings
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_MODULEID, MODULEID_GETMODULEVERSIONINFO_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method ModuleId::getModuleVersionInfo (ID = 0x00000000)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void ModuleIdServerAppInit(void)
{
    ModuleId_registerServerApi(&ModuleIdServerApiCtx);
}
