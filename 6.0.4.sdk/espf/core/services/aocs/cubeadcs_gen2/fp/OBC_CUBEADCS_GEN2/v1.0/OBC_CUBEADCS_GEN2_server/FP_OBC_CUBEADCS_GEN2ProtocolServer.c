/*!
********************************************************************************************
* @file FP_OBC_CUBEADCS_GEN2ProtocolServer.c
* @brief ESSA Stack server-side implementation
********************************************************************************************
* @version           interface OBC_CUBEADCS_GEN2 v1.0
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

#include "FP_OBC_CUBEADCS_GEN2ProtocolServer.h"
#include "FP_common/FP_ProtocolServerCommon.h"

#define OBC_CUBEADCS_GEN2_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_PROTOCOL_VERSION_MINOR   ((uint8_t) 0)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2reqStateMachineStateChangeRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2reqStateMachineStateChangeResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2getStateMachineStateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2getStateMachineStateResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2getStateMachineStateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2getOpStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2getOpStatusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2getOpStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2reqSoftResetAndModeRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2reqSoftResetAndModeResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2get_events_since_last_power_upResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2clear_events_since_last_power_upResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_evtRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_evtProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_evtResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_evtProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_evt_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_evt_statusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_evt_statusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_tlmRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_tlmProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_tlmResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_tlmProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_tlm_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_tlm_statusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_tlm_statusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_img_storedRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_img_storedProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_img_storedResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_img_storedProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_img_stored_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2download_img_stored_statusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_img_stored_statusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_fdir_statsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2get_fdir_statsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_fdir_statsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_fdir_statsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2clear_fdir_statsResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_fdir_statsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_commissioning_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2get_commissioning_statusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_commissioning_statusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2set_commissioning_statusRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_commissioning_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2set_commissioning_statusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_commissioning_statusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_tlm_cfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2get_tlm_cfgResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_tlm_cfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2set_tlm_cfgRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_tlm_cfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2set_tlm_cfgResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_tlm_cfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2get_nvm_system_states_cfgRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2get_nvm_system_states_cfgResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2set_nvm_system_states_cfgRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2set_nvm_system_states_cfgResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2fw_update_cube_computerRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2fw_update_cube_computerResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2fw_update_cube_computer_statusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2fw_update_cube_nodeRequestData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2fw_update_cube_nodeResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    OBC_CUBEADCS_GEN2fw_update_cube_node_statusResponseData_t data;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_reqStateMachineStateChangeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getStateMachineStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getOpStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_reqSoftResetAndModeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_events_since_last_power_upReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clear_events_since_last_power_upReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_download_evtReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_download_evt_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_download_tlmReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_download_tlm_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_download_img_storedReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_download_img_stored_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_fdir_unrecovarable_errorsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clear_fdir_unrecovarable_errorsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_fdir_statsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clear_fdir_statsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_commissioning_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_commissioning_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_tlm_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_tlm_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_nvm_system_states_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_nvm_system_states_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fw_update_cube_computerReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fw_update_cube_computer_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fw_update_cube_nodeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fw_update_cube_node_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_CUBEADCS_GEN2ProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static OBC_CUBEADCS_GEN2_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { OBC_CUBEADCS_GEN2_REQSTATEMACHINESTATECHANGE_FUNC_ID, fs_reqStateMachineStateChangeReq },
    { OBC_CUBEADCS_GEN2_GETSTATEMACHINESTATE_FUNC_ID, fs_getStateMachineStateReq },
    { OBC_CUBEADCS_GEN2_GETOPSTATUS_FUNC_ID, fs_getOpStatusReq },
    { OBC_CUBEADCS_GEN2_REQSOFTRESETANDMODE_FUNC_ID, fs_reqSoftResetAndModeReq },
    { OBC_CUBEADCS_GEN2_GET_EVENTS_SINCE_LAST_POWER_UP_FUNC_ID, fs_get_events_since_last_power_upReq },
    { OBC_CUBEADCS_GEN2_CLEAR_EVENTS_SINCE_LAST_POWER_UP_FUNC_ID, fs_clear_events_since_last_power_upReq },
    { OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_FUNC_ID, fs_download_evtReq },
    { OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_STATUS_FUNC_ID, fs_download_evt_statusReq },
    { OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_FUNC_ID, fs_download_tlmReq },
    { OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_STATUS_FUNC_ID, fs_download_tlm_statusReq },
    { OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_FUNC_ID, fs_download_img_storedReq },
    { OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_STATUS_FUNC_ID, fs_download_img_stored_statusReq },
    { OBC_CUBEADCS_GEN2_GET_FDIR_UNRECOVARABLE_ERRORS_FUNC_ID, fs_get_fdir_unrecovarable_errorsReq },
    { OBC_CUBEADCS_GEN2_CLEAR_FDIR_UNRECOVARABLE_ERRORS_FUNC_ID, fs_clear_fdir_unrecovarable_errorsReq },
    { OBC_CUBEADCS_GEN2_GET_FDIR_STATS_FUNC_ID, fs_get_fdir_statsReq },
    { OBC_CUBEADCS_GEN2_CLEAR_FDIR_STATS_FUNC_ID, fs_clear_fdir_statsReq },
    { OBC_CUBEADCS_GEN2_GET_COMMISSIONING_STATUS_FUNC_ID, fs_get_commissioning_statusReq },
    { OBC_CUBEADCS_GEN2_SET_COMMISSIONING_STATUS_FUNC_ID, fs_set_commissioning_statusReq },
    { OBC_CUBEADCS_GEN2_GET_TLM_CFG_FUNC_ID, fs_get_tlm_cfgReq },
    { OBC_CUBEADCS_GEN2_SET_TLM_CFG_FUNC_ID, fs_set_tlm_cfgReq },
    { OBC_CUBEADCS_GEN2_GET_NVM_SYSTEM_STATES_CFG_FUNC_ID, fs_get_nvm_system_states_cfgReq },
    { OBC_CUBEADCS_GEN2_SET_NVM_SYSTEM_STATES_CFG_FUNC_ID, fs_set_nvm_system_states_cfgReq },
    { OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_FUNC_ID, fs_fw_update_cube_computerReq },
    { OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_STATUS_FUNC_ID, fs_fw_update_cube_computer_statusReq },
    { OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_FUNC_ID, fs_fw_update_cube_nodeReq },
    { OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_STATUS_FUNC_ID, fs_fw_update_cube_node_statusReq }
};

/**********************************************************************
 *
 *  Static methods implementation
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    ESSA_Stack_FP_MsgHdr_t *pHdr = NULL;
    bool bIsFuncSupported = false;
    uint8_t i;

    // Basic header validity check
    if ((fp_DataInfo == NULL) ||
        (fp_DataInfo->u16DataSize < sizeof(ESSA_Stack_FP_MsgHdr_t)) ||
        (fp_DataInfo->pu8Data == NULL))
    {
        return false;
    }

    pHdr = (ESSA_Stack_FP_MsgHdr_t *) fp_DataInfo->pu8Data;

    if (IS_REQUEST(*pHdr))
    {
        for (i = 0; i < COUNT_OF(fs_aFuncArray); i++)
        {
            if (fs_aFuncArray[i].funcId == pHdr->funcId)
            {
                if (fs_aFuncArray[i].pfFunc != NULL)
                {
                    bIsFuncSupported = true;
                    fs_aFuncArray[i].pfFunc(fp_DataInfo);
                }

                break;
            }
        }

        if (!bIsFuncSupported)
            (void) ProtocolSendErrorResp(fp_DataInfo, (uint8_t) ESSA_FP_ERRCODE_FUNC_NOT_SUPPORTED);
    }

    return bIsFuncSupported;
}

static void fs_reqStateMachineStateChangeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2reqStateMachineStateChangeRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2reqStateMachineStateChangeRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_reqStateMachineStateChangeRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getStateMachineStateReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2getStateMachineStateProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2getStateMachineStateProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2getStateMachineStateProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_getStateMachineStateRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_getStateMachineStateRequestHandler(&requestCtx);
    }
}

static void fs_getOpStatusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2getOpStatusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2getOpStatusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2getOpStatusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_getOpStatusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_getOpStatusRequestHandler(&requestCtx);
    }
}

static void fs_reqSoftResetAndModeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2reqSoftResetAndModeRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2reqSoftResetAndModeRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_reqSoftResetAndModeRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_events_since_last_power_upReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_get_events_since_last_power_upRequestHandler(&requestCtx);
    }
}

static void fs_clear_events_since_last_power_upReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_clear_events_since_last_power_upRequestHandler(&requestCtx);
    }
}

static void fs_download_evtReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2download_evtProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2download_evtProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2download_evtRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_evtProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2download_evtRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_download_evtRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_download_evtRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_download_evt_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2download_evt_statusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2download_evt_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_evt_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_download_evt_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_download_evt_statusRequestHandler(&requestCtx);
    }
}

static void fs_download_tlmReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2download_tlmProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2download_tlmProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2download_tlmRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_tlmProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2download_tlmRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_download_tlmRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_download_tlmRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_download_tlm_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2download_tlm_statusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2download_tlm_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_tlm_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_download_tlm_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_download_tlm_statusRequestHandler(&requestCtx);
    }
}

static void fs_download_img_storedReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2download_img_storedProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2download_img_storedProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2download_img_storedRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_img_storedProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2download_img_storedRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_download_img_storedRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_download_img_storedRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_download_img_stored_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2download_img_stored_statusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2download_img_stored_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_img_stored_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_download_img_stored_statusRequestHandler(&requestCtx);
    }
}

static void fs_get_fdir_unrecovarable_errorsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsRequestHandler(&requestCtx);
    }
}

static void fs_clear_fdir_unrecovarable_errorsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsRequestHandler(&requestCtx);
    }
}

static void fs_get_fdir_statsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2get_fdir_statsProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2get_fdir_statsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_fdir_statsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_get_fdir_statsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_get_fdir_statsRequestHandler(&requestCtx);
    }
}

static void fs_clear_fdir_statsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2clear_fdir_statsProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2clear_fdir_statsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2clear_fdir_statsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_clear_fdir_statsRequestHandler(&requestCtx);
    }
}

static void fs_get_commissioning_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2get_commissioning_statusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2get_commissioning_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_commissioning_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_get_commissioning_statusRequestHandler(&requestCtx);
    }
}

static void fs_set_commissioning_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2set_commissioning_statusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2set_commissioning_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2set_commissioning_statusRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2set_commissioning_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2set_commissioning_statusRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_set_commissioning_statusRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_tlm_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2get_tlm_cfgProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2get_tlm_cfgProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_tlm_cfgProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_get_tlm_cfgRequestHandler(&requestCtx);
    }
}

static void fs_set_tlm_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2set_tlm_cfgProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2set_tlm_cfgProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2set_tlm_cfgRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2set_tlm_cfgProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2set_tlm_cfgRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_set_tlm_cfgRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_nvm_system_states_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2get_nvm_system_states_cfgRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2get_nvm_system_states_cfgRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_set_nvm_system_states_cfgReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2set_nvm_system_states_cfgRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2set_nvm_system_states_cfgRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fw_update_cube_computerReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2fw_update_cube_computerRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2fw_update_cube_computerRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_computerRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fw_update_cube_computer_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusRequestHandler(&requestCtx);
    }
}

static void fs_fw_update_cube_nodeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    OBC_CUBEADCS_GEN2fw_update_cube_nodeRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (OBC_CUBEADCS_GEN2fw_update_cube_nodeRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_nodeRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fw_update_cube_node_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolRequestData_t *fullrequest = (OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->OBC_CUBEADCS_GEN2_fw_update_cube_node_statusRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void OBC_CUBEADCS_GEN2_registerServerApi(OBC_CUBEADCS_GEN2_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t OBC_CUBEADCS_GEN2_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_OBC_CUBEADCS_GEN2ProtocolServerInfo;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_reqStateMachineStateChangeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_REQSTATEMACHINESTATECHANGE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2reqStateMachineStateChangeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_getStateMachineStateResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StateMachineStates_t eSm_state,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2getStateMachineStateProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2getStateMachineStateProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2getStateMachineStateProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GETSTATEMACHINESTATE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eSm_state = eSm_state;
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2getStateMachineStateProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_getOpStatusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_OpStatusCommon_t * const sOp_status_common,
                const OBC_CUBEADCS_GEN2_OpStatusApp_t * const sOp_status_app,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2getOpStatusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2getOpStatusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2getOpStatusProtocolResponseData_t);

    if ((ctx != NULL) && (sOp_status_common != NULL) && (sOp_status_app != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GETOPSTATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOp_status_common != NULL)
        {
            responseParams.data.sOp_status_common = *(sOp_status_common);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOp_status_common,
                          0U,
                          sizeof(responseParams.data.sOp_status_common));
        }
        if (sOp_status_app != NULL)
        {
            responseParams.data.sOp_status_app = *(sOp_status_app);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOp_status_app,
                          0U,
                          sizeof(responseParams.data.sOp_status_app));
        }
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2getOpStatusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_reqSoftResetAndModeResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_REQSOFTRESETANDMODE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2reqSoftResetAndModeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_events_since_last_power_upResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_events_t * const sAll_events,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolResponseData_t);

    if ((ctx != NULL) && (sAll_events != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GET_EVENTS_SINCE_LAST_POWER_UP_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sAll_events != NULL)
        {
            responseParams.data.sAll_events = *(sAll_events);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sAll_events,
                          0U,
                          sizeof(responseParams.data.sAll_events));
        }
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2get_events_since_last_power_upProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_clear_events_since_last_power_upResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_CLEAR_EVENTS_SINCE_LAST_POWER_UP_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2clear_events_since_last_power_upProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_evtResp(
                RespContext_t* ctx,
                const uint32_t u32Err
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2download_evtProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2download_evtProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_evtProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2download_evtProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_evt_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_download_event_status_t * const sStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2download_evt_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2download_evt_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_evt_statusProtocolResponseData_t);

    if ((ctx != NULL) && (sStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
        if (sStatus != NULL)
        {
            responseParams.data.sStatus = *(sStatus);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sStatus,
                          0U,
                          sizeof(responseParams.data.sStatus));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2download_evt_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_tlmResp(
                RespContext_t* ctx,
                const uint32_t u32Err
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2download_tlmProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2download_tlmProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_tlmProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2download_tlmProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_tlm_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_download_telemetry_status_t * const sStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2download_tlm_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2download_tlm_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_tlm_statusProtocolResponseData_t);

    if ((ctx != NULL) && (sStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
        if (sStatus != NULL)
        {
            responseParams.data.sStatus = *(sStatus);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sStatus,
                          0U,
                          sizeof(responseParams.data.sStatus));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2download_tlm_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_img_storedResp(
                RespContext_t* ctx,
                const uint32_t u32Err
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2download_img_storedProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2download_img_storedProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_img_storedProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2download_img_storedProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_download_img_stored_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_download_image_stored_status_t * const sStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2download_img_stored_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2download_img_stored_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2download_img_stored_statusProtocolResponseData_t);

    if ((ctx != NULL) && (sStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
        if (sStatus != NULL)
        {
            responseParams.data.sStatus = *(sStatus);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sStatus,
                          0U,
                          sizeof(responseParams.data.sStatus));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2download_img_stored_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_fdir_unrecovarable_errorsResp(
                RespContext_t* ctx,
                const uint32_t u32Errors,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GET_FDIR_UNRECOVARABLE_ERRORS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Errors = u32Errors;
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_clear_fdir_unrecovarable_errorsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_CLEAR_FDIR_UNRECOVARABLE_ERRORS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_fdir_statsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_fdir_stat_t * const asFdir_logic,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2get_fdir_statsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2get_fdir_statsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_fdir_statsProtocolResponseData_t);

    if ((ctx != NULL) && (asFdir_logic != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GET_FDIR_STATS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (asFdir_logic != NULL)
        {
            (void) memcpy((void *) &responseParams.data.asFdir_logic,
                          (const void *) asFdir_logic,
                          sizeof(responseParams.data.asFdir_logic));
        }
        else
        {
            (void) memset((void *) &responseParams.data.asFdir_logic,
                          0U,
                          sizeof(responseParams.data.asFdir_logic));
        }
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2get_fdir_statsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_clear_fdir_statsResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2clear_fdir_statsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2clear_fdir_statsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2clear_fdir_statsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_CLEAR_FDIR_STATS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2clear_fdir_statsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_commissioning_statusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_CommissioningStatus_t eStatus,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2get_commissioning_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2get_commissioning_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_commissioning_statusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GET_COMMISSIONING_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2get_commissioning_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_set_commissioning_statusResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOpResult
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2set_commissioning_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2set_commissioning_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2set_commissioning_statusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_SET_COMMISSIONING_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOpResult = eOpResult;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2set_commissioning_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_tlm_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_telemetry_mask_0_t * const sMask_0,
                const OBC_CUBEADCS_GEN2_telemetry_mask_1_t * const sMask_1,
                const OBC_CUBEADCS_GEN2_telemetry_mask_2_t * const sMask_2,
                const OBC_CUBEADCS_GEN2_telemetry_mask_3_t * const sMask_3,
                const OBC_CUBEADCS_GEN2_telemetry_mask_4_t * const sMask_4,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2get_tlm_cfgProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2get_tlm_cfgProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_tlm_cfgProtocolResponseData_t);

    if ((ctx != NULL) && (sMask_0 != NULL) && (sMask_1 != NULL) && (sMask_2 != NULL) && (sMask_3 != NULL) && (sMask_4 != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GET_TLM_CFG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sMask_0 != NULL)
        {
            responseParams.data.sMask_0 = *(sMask_0);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sMask_0,
                          0U,
                          sizeof(responseParams.data.sMask_0));
        }
        if (sMask_1 != NULL)
        {
            responseParams.data.sMask_1 = *(sMask_1);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sMask_1,
                          0U,
                          sizeof(responseParams.data.sMask_1));
        }
        if (sMask_2 != NULL)
        {
            responseParams.data.sMask_2 = *(sMask_2);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sMask_2,
                          0U,
                          sizeof(responseParams.data.sMask_2));
        }
        if (sMask_3 != NULL)
        {
            responseParams.data.sMask_3 = *(sMask_3);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sMask_3,
                          0U,
                          sizeof(responseParams.data.sMask_3));
        }
        if (sMask_4 != NULL)
        {
            responseParams.data.sMask_4 = *(sMask_4);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sMask_4,
                          0U,
                          sizeof(responseParams.data.sMask_4));
        }
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2get_tlm_cfgProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_set_tlm_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2set_tlm_cfgProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2set_tlm_cfgProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2set_tlm_cfgProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_SET_TLM_CFG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2set_tlm_cfgProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_get_nvm_system_states_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_state_change_core_args_t * const sSys_states_cfg,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolResponseData_t);

    if ((ctx != NULL) && (sSys_states_cfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_GET_NVM_SYSTEM_STATES_CFG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sSys_states_cfg != NULL)
        {
            responseParams.data.sSys_states_cfg = *(sSys_states_cfg);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sSys_states_cfg,
                          0U,
                          sizeof(responseParams.data.sSys_states_cfg));
        }
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2get_nvm_system_states_cfgProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_set_nvm_system_states_cfgResp(
                RespContext_t* ctx,
                const OBC_CUBEADCS_GEN2_StandardResult_t eOp_result
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_SET_NVM_SYSTEM_STATES_CFG_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eOp_result = eOp_result;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2set_nvm_system_states_cfgProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_computerResp(
                RespContext_t* ctx,
                const uint32_t u32Err
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2fw_update_cube_computerProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_computer_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_cube_computer_fw_update_status_t * const sStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolResponseData_t);

    if ((ctx != NULL) && (sStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
        if (sStatus != NULL)
        {
            responseParams.data.sStatus = *(sStatus);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sStatus,
                          0U,
                          sizeof(responseParams.data.sStatus));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2fw_update_cube_computer_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_nodeResp(
                RespContext_t* ctx,
                const uint32_t u32Err
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2fw_update_cube_nodeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes OBC_CUBEADCS_GEN2_fw_update_cube_node_statusResp(
                RespContext_t* ctx,
                const uint32_t u32Err,
                const OBC_CUBEADCS_GEN2_cube_node_fw_update_status_t * const sStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolResponseData_t);

    if ((ctx != NULL) && (sStatus != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2;
        responseParams.hdr.funcId  = OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Err = u32Err;
        if (sStatus != NULL)
        {
            responseParams.data.sStatus = *(sStatus);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sStatus,
                          0U,
                          sizeof(responseParams.data.sStatus));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(OBC_CUBEADCS_GEN2fw_update_cube_node_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


