/*!
********************************************************************************************
* @file FP_MacServicesServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface MacServices v0.1
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

#include "FP_MacServicesProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include <esps_drv_config.h>
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void MacServices_getMacBusTerminationSettingRequestHandlerImpl(ReqContext_t* pReqCtx,
            const MacServicesgetMacBusTerminationSettingRequestData_t* pRequestData);

static void MacServices_setMacBusTerminationSettingRequestHandlerImpl(ReqContext_t* pReqCtx,
            const MacServicessetMacBusTerminationSettingRequestData_t* pRequestData);

static void MacServices_setMacAddressRequestHandlerImpl(ReqContext_t* pReqCtx,
            const MacServicessetMacAddressRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static MacServices_ServerApi_t MacServicesServerApiCtx =
{
  .MacServices_getMacBusTerminationSettingRequestHandler = (pfMacServices_getMacBusTerminationSettingRequestHandler_t) MacServices_getMacBusTerminationSettingRequestHandlerImpl,
  .MacServices_setMacBusTerminationSettingRequestHandler = (pfMacServices_setMacBusTerminationSettingRequestHandler_t) MacServices_setMacBusTerminationSettingRequestHandlerImpl,
  .MacServices_setMacAddressRequestHandler = (pfMacServices_setMacAddressRequestHandler_t) MacServices_setMacAddressRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method MacServices::getMacBusTerminationSetting (ID = 0x00000000)
static void MacServices_getMacBusTerminationSettingRequestHandlerImpl(ReqContext_t *pReqCtx,
            const MacServicesgetMacBusTerminationSettingRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8SupportedInterfacesBitField;
    uint8_t u8BusTerminationSettingsBitField;

    // @USER_VAR_SECTION_START@MacServices::getMacBusTerminationSetting@
    // Put your local variables in this section to preserve during merge!
    uint8_t u8MacIfId;
    // @USER_VAR_SECTION_END@MacServices::getMacBusTerminationSetting@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@MacServices::getMacBusTerminationSetting@
        u8SupportedInterfacesBitField = 0U;
        u8BusTerminationSettingsBitField = 0U;

        for (u8MacIfId = 0; u8MacIfId < (uint8_t) eMAC_Interface_Count; u8MacIfId++)
        {
            u8SupportedInterfacesBitField |= (0x01U << u8MacIfId);

            u8BusTerminationSettingsBitField |= MacCfg_bGetBusTerminationState((eMACInterface_t) u8MacIfId, pRequestData->bReadPersistentSetting) << u8MacIfId;
        }
        // @USER_CODE_SECTION_END@MacServices::getMacBusTerminationSetting@

        respResult = MacServices_getMacBusTerminationSettingResp(
                        &respCtx,
                        u8SupportedInterfacesBitField,
                        u8BusTerminationSettingsBitField
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES, MACSERVICES_GETMACBUSTERMINATIONSETTING_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method MacServices::getMacBusTerminationSetting (ID = 0x00000000)

// @START@ Request handler for method MacServices::setMacBusTerminationSetting (ID = 0x00000001)
static void MacServices_setMacBusTerminationSettingRequestHandlerImpl(ReqContext_t *pReqCtx,
            const MacServicessetMacBusTerminationSettingRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;

    // @USER_VAR_SECTION_START@MacServices::setMacBusTerminationSetting@
    uint8_t u8MacIfId;
    // @USER_VAR_SECTION_END@MacServices::setMacBusTerminationSetting@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@MacServices::setMacBusTerminationSetting@

        for (u8MacIfId = 0; u8MacIfId < (uint8_t) eMAC_Interface_Count; u8MacIfId++)
        {
            if ((uint8_t) ((pRequestData->u8SupportedInterfacesBitField >> u8MacIfId) & 0x01U) == 0x01U)
            {
                MacCfg_vSetBusTerminationState((eMACInterface_t) u8MacIfId,
                                               (bool) (pRequestData->u8BusTerminationSettingsBitField >> u8MacIfId) & 0x01U,
                                               true);
            }
        }
        // @USER_CODE_SECTION_END@MacServices::setMacBusTerminationSetting@

        respResult = MacServices_setMacBusTerminationSettingResp(
                        &respCtx
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES, MACSERVICES_SETMACBUSTERMINATIONSETTING_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method MacServices::setMacBusTerminationSetting (ID = 0x00000001)

// @START@ Request handler for method MacServices::setMacAddress (ID = 0x00000010)
static void MacServices_setMacAddressRequestHandlerImpl(ReqContext_t *pReqCtx,
            const MacServicessetMacAddressRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8UpdatedMacAddr;

    // @USER_VAR_SECTION_START@MacServices::setMacAddress@
    eMACInterface_t eMacIf;
    // @USER_VAR_SECTION_END@MacServices::setMacAddress@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@MacServices::setMacAddress@
        // all MAC interfaces do have the same address for the moment but there is a
        // provision in the interface where the physical interface ID can be supplied as
        // the MS 8-bits of the address since the address itself is limited to 8 bits only
        eMacIf = (eMACInterface_t) (pRequestData->u8MacAddr >> 8);

        (void) MacCfg_bSetMacAddress(eMacIf,
                                     (uint8_t) pRequestData->u8MacAddr);

        u8UpdatedMacAddr = MacCfg_u8GetMacAddress(eMacIf);
        // @USER_CODE_SECTION_END@MacServices::setMacAddress@

        respResult = MacServices_setMacAddressResp(
                        &respCtx,
                        u8UpdatedMacAddr
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES, MACSERVICES_SETMACADDRESS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method MacServices::setMacAddress (ID = 0x00000010)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void MacServicesServerAppInit(void)
{
    MacServices_registerServerApi(&MacServicesServerApiCtx);
}
