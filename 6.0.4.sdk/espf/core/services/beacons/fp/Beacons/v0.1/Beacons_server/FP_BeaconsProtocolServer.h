/*!
********************************************************************************************
* @file FP_BeaconsProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface Beacons v0.1
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

#ifndef __FP_BEACONSPROTOCOLSERVER_H__
#define __FP_BEACONSPROTOCOLSERVER_H__

#include "FP_BeaconsProtocolTypes.h"

typedef void (*pfBeacons_getBeaconGeneralConfigRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfBeacons_setBeaconGeneralConfigRequestHandler_t)(ReqContext_t *ctx, BeaconssetBeaconGeneralConfigRequestData_t *pRequestData);
typedef void (*pfBeacons_getBeaconPresetConfigRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfBeacons_setBeaconPresetConfigRequestHandler_t)(ReqContext_t *ctx, BeaconssetBeaconPresetConfigRequestData_t *pRequestData);
typedef void (*pfBeacons_setActivePresetRequestHandler_t)(ReqContext_t *ctx, BeaconssetActivePresetRequestData_t *pRequestData);
typedef void (*pfBeacons_getActivePresetRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfBeacons_restoreActivePresetRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfBeacons_getBeaconGeneralConfigRequestHandler_t Beacons_getBeaconGeneralConfigRequestHandler;
    pfBeacons_setBeaconGeneralConfigRequestHandler_t Beacons_setBeaconGeneralConfigRequestHandler;
    pfBeacons_getBeaconPresetConfigRequestHandler_t Beacons_getBeaconPresetConfigRequestHandler;
    pfBeacons_setBeaconPresetConfigRequestHandler_t Beacons_setBeaconPresetConfigRequestHandler;
    pfBeacons_setActivePresetRequestHandler_t Beacons_setActivePresetRequestHandler;
    pfBeacons_getActivePresetRequestHandler_t Beacons_getActivePresetRequestHandler;
    pfBeacons_restoreActivePresetRequestHandler_t Beacons_restoreActivePresetRequestHandler;
} Beacons_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_BeaconsProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void Beacons_registerServerApi(Beacons_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_BeaconsProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t Beacons_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes Beacons_getBeaconGeneralConfigResp(
                RespContext_t* ctx,
                const BEACONS_bcn_general_cfg_t * const sCfg
);

ESSATMAC_ErrCodes Beacons_setBeaconGeneralConfigResp(
                RespContext_t* ctx,
                const BEACONS_StandardResult_t eRes
);

ESSATMAC_ErrCodes Beacons_getBeaconPresetConfigResp(
                RespContext_t* ctx,
                const uint8_t u8Slot_preset_cnt,
                const uint8_t u8Max_bcn_msg_cnt,
                const uint16_t * const au16Beacon_preset_cfg
);

ESSATMAC_ErrCodes Beacons_setBeaconPresetConfigResp(
                RespContext_t* ctx,
                const BEACONS_StandardResult_t eRes,
                const uint8_t * const au8Preset_error_slot_index
);

ESSATMAC_ErrCodes Beacons_setActivePresetResp(
                RespContext_t* ctx,
                const BEACONS_StandardResult_t eRes,
                const uint8_t u8Avail_presets_cnt
);

ESSATMAC_ErrCodes Beacons_getActivePresetResp(
                RespContext_t* ctx,
                const uint8_t u8Active_preset_id
);

ESSATMAC_ErrCodes Beacons_restoreActivePresetResp(
                RespContext_t* ctx,
                const BEACONS_StandardResult_t eRes
);


#endif  // #ifndef __FP_BEACONSPROTOCOLSERVER_H__
