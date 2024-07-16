/*!
********************************************************************************************
* @file FP_OBCServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface OBC v3.4
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

#include "FP_OBCProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "CommandsApi.h"
#include "module_id.h"
#include "debug.h"
#include "FWUPD_Persistor.h"
#include "AppTasks.h"
#include "nvm_resetcounters.h"
#include "nvm.h"

// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
static inline OBC_HwResult_t getHwResultFor(status_t status);
static inline OBC_StandardResult_t getStdResFor(StdResult_t res);
// @END_USER@ USER_LOCAL_FUNC_DECL
static void OBC_getGpOutputStatesRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_setGpOutputStateRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBCsetGpOutputStateRequestData_t* pRequestData);

static void OBC_getI2CPullUpsStateRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_setI2CPullUpsStateRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBCsetI2CPullUpsStateRequestData_t* pRequestData);

static void OBC_get_uptimeRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_getResetCountersRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_clearResetCounterRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBCclearResetCounterRequestData_t* pRequestData);

static void OBC_triggerResetInModeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBCtriggerResetInModeRequestData_t* pRequestData);

static void OBC_set_device_mac_addressRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBCset_device_mac_addressRequestData_t* pRequestData);

static void OBC_get_device_mac_addressRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBCget_device_mac_addressRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
static inline OBC_HwResult_t getHwResultFor(status_t status)
{
    OBC_HwResult_t hwRes;

    switch (status)
    {
        case SEN_SUCCESS :
            hwRes = OBC_HWRESULT_SUCCESS;
        break;

        case SEN_ERROR :
            hwRes = OBC_HWRESULT_ERROR;
        break;

        case SEN_DISABLED :
            hwRes = OBC_HWRESULT_DISABLED;
        break;

        default:
            hwRes = OBC_HWRESULT_ERROR;
        break;
    }

    return hwRes;
}

static inline OBC_StandardResult_t getStdResFor(StdResult_t res)
{
    OBC_StandardResult_t stdRes;

    switch (res)
    {
        case STDRESULT_SUCCESS :
            stdRes = OBC_STANDARDRESULT_SUCCESS;
        break;

        case STDRESULT_ERROR :
            stdRes = OBC_STANDARDRESULT_ERROR;
        break;

        case STDRESULT_INVALID_ARGS :
            stdRes = OBC_STANDARDRESULT_INVALID_ARGS;
        break;

        default:
            stdRes = OBC_STANDARDRESULT_ERROR;
        break;
    }

    return stdRes;
}
// @END_USER@ USER_LOCAL_VARS_DECL

static OBC_ServerApi_t OBCServerApiCtx =
{
  .OBC_getGpOutputStatesRequestHandler = (pfOBC_getGpOutputStatesRequestHandler_t) OBC_getGpOutputStatesRequestHandlerImpl,
  .OBC_setGpOutputStateRequestHandler = (pfOBC_setGpOutputStateRequestHandler_t) OBC_setGpOutputStateRequestHandlerImpl,
  .OBC_getI2CPullUpsStateRequestHandler = (pfOBC_getI2CPullUpsStateRequestHandler_t) OBC_getI2CPullUpsStateRequestHandlerImpl,
  .OBC_setI2CPullUpsStateRequestHandler = (pfOBC_setI2CPullUpsStateRequestHandler_t) OBC_setI2CPullUpsStateRequestHandlerImpl,
  .OBC_get_uptimeRequestHandler = (pfOBC_get_uptimeRequestHandler_t) OBC_get_uptimeRequestHandlerImpl,
  .OBC_getResetCountersRequestHandler = (pfOBC_getResetCountersRequestHandler_t) OBC_getResetCountersRequestHandlerImpl,
  .OBC_clearResetCounterRequestHandler = (pfOBC_clearResetCounterRequestHandler_t) OBC_clearResetCounterRequestHandlerImpl,
  .OBC_triggerResetInModeRequestHandler = (pfOBC_triggerResetInModeRequestHandler_t) OBC_triggerResetInModeRequestHandlerImpl,
  .OBC_set_device_mac_addressRequestHandler = (pfOBC_set_device_mac_addressRequestHandler_t) OBC_set_device_mac_addressRequestHandlerImpl,
  .OBC_get_device_mac_addressRequestHandler = (pfOBC_get_device_mac_addressRequestHandler_t) OBC_get_device_mac_addressRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method OBC::getGpOutputStates (ID = 0x0000000E)
static void OBC_getGpOutputStatesRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_GpioStatus_t sData;

    // @USER_VAR_SECTION_START@OBC::getGpOutputStates@
    // Put your local variables in this section to preserve during merge!
    GpioStat_t outputStates;
    // @USER_VAR_SECTION_END@OBC::getGpOutputStates@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::getGpOutputStates@
        outputStates = ReadHandler_GpOutputState();

        sData.u8GpioStatusBitField = outputStates.gpioStatusBitField;
        // @USER_CODE_SECTION_END@OBC::getGpOutputStates@

        respResult = OBC_getGpOutputStatesResp(
                        &respCtx,
                        &sData
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_GETGPOUTPUTSTATES_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::getGpOutputStates (ID = 0x0000000E)

// @START@ Request handler for method OBC::setGpOutputState (ID = 0x0000000F)
static void OBC_setGpOutputStateRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBCsetGpOutputStateRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_HwResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC::setGpOutputState@
    // Put your local variables in this section to preserve during merge!
    HwRes_t res;
    // @USER_VAR_SECTION_END@OBC::setGpOutputState@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::setGpOutputState@
                // We must only send 1 or 0 for the state value
        uint8_t u8_value = 0;
        if (true == pRequestData->bValue)
        {
            u8_value = 1;
        }

        res = WriteHandler_GpOutputState(pRequestData->u8PinId, u8_value);

        switch (res)
        {
            case HWRES_SUCCESS:
            {
                eOpResult = OBC_HWRESULT_SUCCESS;
                break;
            }

            case HWRES_ERROR:
            {
                eOpResult = OBC_HWRESULT_ERROR;
                break;
            }

            case HWRES_DISABLED:
            {
                eOpResult = OBC_HWRESULT_DISABLED;
                break;
            }

            default:
            {
                eOpResult = OBC_HWRESULT_ERROR;
                break;
            }
        }
        // @USER_CODE_SECTION_END@OBC::setGpOutputState@

        respResult = OBC_setGpOutputStateResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_SETGPOUTPUTSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::setGpOutputState (ID = 0x0000000F)

// @START@ Request handler for method OBC::getI2CPullUpsState (ID = 0x00000012)
static void OBC_getI2CPullUpsStateRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_I2CPullUpsState_t sNvm_pullupsState;
    OBC_I2CPullUpsState_t sIo_pullupsState;

    // @USER_VAR_SECTION_START@OBC::getI2CPullUpsState@
    // Put your local variables in this section to preserve during merge!
    i2c_config_t i2c_config;
    // @USER_VAR_SECTION_END@OBC::getI2CPullUpsState@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::getI2CPullUpsState@
        Nvm_GetBlockById(NVM_BLOCK_I2C_CONFIG, &i2c_config);

        sNvm_pullupsState.bSystemBus_4K7 = (i2c_config.i2c_pull_up_config[I2C_BUS_SYSTEM].pull_up_4k7);
        sNvm_pullupsState.bSystemBus_10K = (i2c_config.i2c_pull_up_config[I2C_BUS_SYSTEM].pull_up_10k);
        sNvm_pullupsState.bPayloadBus_4K7 = (i2c_config.i2c_pull_up_config[I2C_BUS_PAYLOAD].pull_up_4k7);
        sNvm_pullupsState.bPayloadBus_10K = (i2c_config.i2c_pull_up_config[I2C_BUS_PAYLOAD].pull_up_10k);

        I2CPullUpsState_t i2c_io_cfg = MCU_Init_I2cPullUps_Get();

        sIo_pullupsState.bSystemBus_4K7 = i2c_io_cfg.pins.sys_bus_4K7;
        sIo_pullupsState.bSystemBus_10K = i2c_io_cfg.pins.sys_bus_10K;
        sIo_pullupsState.bPayloadBus_4K7 = i2c_io_cfg.pins.pay_bus_4K7;
        sIo_pullupsState.bPayloadBus_10K = i2c_io_cfg.pins.pay_bus_10K;
        // @USER_CODE_SECTION_END@OBC::getI2CPullUpsState@

        respResult = OBC_getI2CPullUpsStateResp(
                        &respCtx,
                        &sNvm_pullupsState,
                        &sIo_pullupsState
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_GETI2CPULLUPSSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::getI2CPullUpsState (ID = 0x00000012)

// @START@ Request handler for method OBC::setI2CPullUpsState (ID = 0x00000013)
static void OBC_setI2CPullUpsStateRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBCsetI2CPullUpsStateRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_I2CPullUpsState_t sPullupsIoState;

    // @USER_VAR_SECTION_START@OBC::setI2CPullUpsState@
    // Put your local variables in this section to preserve during merge!
    i2c_config_t i2c_config;
    // @USER_VAR_SECTION_END@OBC::setI2CPullUpsState@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::setI2CPullUpsState@
        (void) memset(&i2c_config, 0U, sizeof(i2c_config));

        i2c_config.i2c_pull_up_config[I2C_BUS_SYSTEM].pull_up_4k7 = pRequestData->sPullupsState.bSystemBus_4K7;
        i2c_config.i2c_pull_up_config[I2C_BUS_SYSTEM].pull_up_10k = pRequestData->sPullupsState.bSystemBus_10K;
        i2c_config.i2c_pull_up_config[I2C_BUS_PAYLOAD].pull_up_4k7 = pRequestData->sPullupsState.bPayloadBus_4K7;
        i2c_config.i2c_pull_up_config[I2C_BUS_PAYLOAD].pull_up_10k = pRequestData->sPullupsState.bPayloadBus_10K;

        Nvm_SetBlockById(NVM_BLOCK_I2C_CONFIG, &i2c_config, NVMSETBLOCK_STORE_IMMEDIATELY);

        // apply the new NVM settings to the GPIOs...
        MCU_Init_I2cPullUps_Nvm();

        // read back GPIO status directly...
        I2CPullUpsState_t i2c_io_state;
        i2c_io_state = MCU_Init_I2cPullUps_Get();

        sPullupsIoState.bSystemBus_4K7 = i2c_io_state.pins.sys_bus_4K7;
        sPullupsIoState.bSystemBus_10K = i2c_io_state.pins.sys_bus_10K;
        sPullupsIoState.bPayloadBus_4K7 = i2c_io_state.pins.pay_bus_4K7;
        sPullupsIoState.bPayloadBus_10K = i2c_io_state.pins.pay_bus_10K;
        // @USER_CODE_SECTION_END@OBC::setI2CPullUpsState@

        respResult = OBC_setI2CPullUpsStateResp(
                        &respCtx,
                        &sPullupsIoState
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_SETI2CPULLUPSSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::setI2CPullUpsState (ID = 0x00000013)

// @START@ Request handler for method OBC::get_uptime (ID = 0x00000018)
static void OBC_get_uptimeRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Uptime;

    // @USER_VAR_SECTION_START@OBC::get_uptime@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC::get_uptime@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::get_uptime@
        
        u32Uptime = get_uptime_seconds();
        
        // @USER_CODE_SECTION_END@OBC::get_uptime@

        respResult = OBC_get_uptimeResp(
                        &respCtx,
                        u32Uptime
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_GET_UPTIME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::get_uptime (ID = 0x00000018)

// @START@ Request handler for method OBC::getResetCounters (ID = 0x0000002A)
static void OBC_getResetCountersRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ResetCountersInfo_t sStatus;

    // @USER_VAR_SECTION_START@OBC::getResetCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC::getResetCounters@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::getResetCounters@
        boot_struct BootData;
        Nvm_GetBlockById(NVM_BLOCK_BOOTDATA, &BootData);

        sStatus.u32WWD = BootData.RST_WWD;
        sStatus.u32IWD = BootData.RST_IWD;
        sStatus.u32LPR = BootData.RST_LPR;
        sStatus.u32POR = BootData.RST_POR;
        sStatus.u32RstPin = BootData.RST_RstPin;
        sStatus.u32BOR = BootData.RST_BOR;
        sStatus.u32HardFault = BootData.RST_HardFault;
        sStatus.u32MemFault = BootData.RST_MemFault;
        sStatus.u32BusFault = BootData.RST_BusFault;
        sStatus.u32UsageFault = BootData.RST_UsageFault;
        // @USER_CODE_SECTION_END@OBC::getResetCounters@

        respResult = OBC_getResetCountersResp(
                        &respCtx,
                        &sStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_GETRESETCOUNTERS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::getResetCounters (ID = 0x0000002A)

// @START@ Request handler for method OBC::clearResetCounter (ID = 0x0000002B)
static void OBC_clearResetCounterRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBCclearResetCounterRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC::clearResetCounter@
    // Put your local variables in this section to preserve during merge!
    RstCounterId_t rstCntrId;
    // @USER_VAR_SECTION_END@OBC::clearResetCounter@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::clearResetCounter@
        switch (pRequestData->eId)
        {
            case OBC_RESETCNTRID_WWD:
                rstCntrId = RSTCOUNTERID_WWD;
            break;

            case OBC_RESETCNTRID_IWD:
                rstCntrId = RSTCOUNTERID_IWD;
            break;

            case OBC_RESETCNTRID_LPR:
                rstCntrId = RSTCOUNTERID_LPR;
            break;

            case OBC_RESETCNTRID_POR:
                rstCntrId = RSTCOUNTERID_POR;
            break;

            case OBC_RESETCNTRID_RSTPIN:
                rstCntrId = RSTCOUNTERID_RSTPIN;
            break;

            case OBC_RESETCNTRID_BOR:
                rstCntrId = RSTCOUNTERID_BOR;
            break;

            case OBC_RESETCNTRID_HARDFAULT:
                rstCntrId = RSTCOUNTERID_HARDFAULT;
            break;

            case OBC_RESETCNTRID_MEMFAULT:
                rstCntrId = RSTCOUNTERID_MEMFAULT;
            break;

            case OBC_RESETCNTRID_BUSFAULT:
                rstCntrId = RSTCOUNTERID_BUSFAULT;
            break;

            case OBC_RESETCNTRID_USAGEFAULT:
                rstCntrId = RSTCOUNTERID_USAGEFAULT;
            break;

            case OBC_RESETCNTRID_ALL:
                rstCntrId = RSTCOUNTERID_ALL;
            break;

            default:
                rstCntrId = RSTCOUNTERID_MAX;
            break;
        }

        eOpResult = (NvmResetCounters_ClearCounter(rstCntrId)) ?
                    (OBC_STANDARDRESULT_SUCCESS) :
                    (OBC_STANDARDRESULT_INVALID_ARGS);
        // @USER_CODE_SECTION_END@OBC::clearResetCounter@

        respResult = OBC_clearResetCounterResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_CLEARRESETCOUNTER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::clearResetCounter (ID = 0x0000002B)

// @START@ Request handler for method OBC::triggerResetInMode (ID = 0x00000036)
static void OBC_triggerResetInModeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBCtriggerResetInModeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC::triggerResetInMode@
    // Put your local variables in this section to preserve during merge!
    AppMode_t newAppMode;
    StdResult_t res;
    // @USER_VAR_SECTION_END@OBC::triggerResetInMode@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::triggerResetInMode@
        switch (pRequestData->eStartMode)
        {
            case OBC_APPLICATIONMODE_APPLICATION:
                newAppMode = APPMODE_APPLICATION;
            break;

            case OBC_APPLICATIONMODE_BOOTLOADER:
                newAppMode = APPMODE_BOOTLOADER;
            break;

            default:
                newAppMode = APPMODE_MAX;
            break;
        }

        res = WriteHandler_ResetInBootOrAppMode(newAppMode);

        eOpResult = getStdResFor(res);
        // @USER_CODE_SECTION_END@OBC::triggerResetInMode@

        respResult = OBC_triggerResetInModeResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_TRIGGERRESETINMODE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::triggerResetInMode (ID = 0x00000036)

// @START@ Request handler for method OBC::set_device_mac_address (ID = 0x00000040)
static void OBC_set_device_mac_addressRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBCset_device_mac_addressRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC::set_device_mac_address@
    mac_address_book_t addresses = {0};
    // @USER_VAR_SECTION_END@OBC::set_device_mac_address@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::set_device_mac_address@
        if (MAC_ADDR_BOOK_MAX <= pRequestData->u8Device_id){
            eOpResult = OBC_STANDARDRESULT_INVALID_ARGS;
        }
        // Check for invalid MAC ADDRESSES
        else if(ESSATMAC_ADDR_BROADCAST == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_GATEWAY_DEV == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_UNINITIALIZED_DEV == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_GATEWAY_EPSIIBP == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_GATEWAY_EPSIIPDM == pRequestData->u8New_mac_address
             || ESSATMAC_ADDR_EXTERNAL_MAC_DONGLE == pRequestData->u8New_mac_address)
        {
            eOpResult = OBC_STANDARDRESULT_INVALID_ARGS;
        }
        else {
            eOpResult = OBC_STANDARDRESULT_ERROR;
            // Read the NVM
            Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

            // Verify if the nvm was read
            if (NULL != addresses.a_mac_address){
                addresses.a_mac_address[pRequestData->u8Device_id] = pRequestData->u8New_mac_address;
                Nvm_SetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses, true);
                eOpResult = OBC_STANDARDRESULT_SUCCESS;
            }
        }
        // @USER_CODE_SECTION_END@OBC::set_device_mac_address@

        respResult = OBC_set_device_mac_addressResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_SET_DEVICE_MAC_ADDRESS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::set_device_mac_address (ID = 0x00000040)

// @START@ Request handler for method OBC::get_device_mac_address (ID = 0x00000041)
static void OBC_get_device_mac_addressRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBCget_device_mac_addressRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Mac_address;
    OBC_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC::get_device_mac_address@
    mac_address_book_t addresses = {0};
    // @USER_VAR_SECTION_END@OBC::get_device_mac_address@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC::get_device_mac_address@
        // Set default value to 0, invalid MAC address
        u8Mac_address = 0;

        if (MAC_ADDR_BOOK_MAX <= pRequestData->u8Device_id){
            eOpResult = OBC_STANDARDRESULT_INVALID_ARGS;
        }
        else {
            eOpResult = OBC_STANDARDRESULT_ERROR;

            // Read the NVM
            Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

            u8Mac_address = addresses.a_mac_address[pRequestData->u8Device_id];
            eOpResult = OBC_STANDARDRESULT_SUCCESS;
        }
        // @USER_CODE_SECTION_END@OBC::get_device_mac_address@

        respResult = OBC_get_device_mac_addressResp(
                        &respCtx,
                        u8Mac_address,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC, OBC_GET_DEVICE_MAC_ADDRESS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC::get_device_mac_address (ID = 0x00000041)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void OBCServerAppInit(void)
{
    OBC_registerServerApi(&OBCServerApiCtx);
}
