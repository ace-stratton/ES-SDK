/*!
********************************************************************************************
* @file FP_fault_opsServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface fault_ops v0.1
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

#include "FP_fault_opsProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "fault_persistor.h"
#include "nvm.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
static void access_disabled_coprocessor(void)
{
  __asm volatile(
      "ldr r0, =0xE000ED88 \n"
      "mov r1, #0 \n"
      "str r1, [r0] \n"
      "dsb \n"
      "vmov r0, s0 \n"
      );
}
// @END_USER@ USER_LOCAL_FUNC_DECL
static void fault_ops_get_fault_infoRequestHandlerImpl(ReqContext_t* pReqCtx);

static void fault_ops_read_fault_by_index_rawRequestHandlerImpl(ReqContext_t* pReqCtx,
            const fault_opsread_fault_by_index_rawRequestData_t* pRequestData);

static void fault_ops_clear_all_faultsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void fault_ops_simulate_faultRequestHandlerImpl(ReqContext_t* pReqCtx,
            const fault_opssimulate_faultRequestData_t* pRequestData);

static void fault_ops_read_fault_by_indexRequestHandlerImpl(ReqContext_t* pReqCtx,
            const fault_opsread_fault_by_indexRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static fault_ops_ServerApi_t fault_opsServerApiCtx =
{
  .fault_ops_get_fault_infoRequestHandler = (pffault_ops_get_fault_infoRequestHandler_t) fault_ops_get_fault_infoRequestHandlerImpl,
  .fault_ops_read_fault_by_index_rawRequestHandler = (pffault_ops_read_fault_by_index_rawRequestHandler_t) fault_ops_read_fault_by_index_rawRequestHandlerImpl,
  .fault_ops_clear_all_faultsRequestHandler = (pffault_ops_clear_all_faultsRequestHandler_t) fault_ops_clear_all_faultsRequestHandlerImpl,
  .fault_ops_simulate_faultRequestHandler = (pffault_ops_simulate_faultRequestHandler_t) fault_ops_simulate_faultRequestHandlerImpl,
  .fault_ops_read_fault_by_indexRequestHandler = (pffault_ops_read_fault_by_indexRequestHandler_t) fault_ops_read_fault_by_indexRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method fault_ops::get_fault_info (ID = 0x00000000)
static void fault_ops_get_fault_infoRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Occupied_fault_slots;
    uint8_t u8Available_fault_slots;

    // @USER_VAR_SECTION_START@fault_ops::get_fault_info@
    // Put your local variables in this section to preserve during merge!
    fault_info_t fault_info = { .slots_available = 0, .slots_occupied = 0 };
    // @USER_VAR_SECTION_END@fault_ops::get_fault_info@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@fault_ops::get_fault_info@

        fault_persistor_get_info(&fault_info);
        u8Occupied_fault_slots = fault_info.slots_occupied;
        u8Available_fault_slots = fault_info.slots_available;

        // @USER_CODE_SECTION_END@fault_ops::get_fault_info@

        respResult = fault_ops_get_fault_infoResp(
                        &respCtx,
                        u8Occupied_fault_slots,
                        u8Available_fault_slots
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FAULT_OPS, FAULT_OPS_GET_FAULT_INFO_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method fault_ops::get_fault_info (ID = 0x00000000)

// @START@ Request handler for method fault_ops::read_fault_by_index_raw (ID = 0x00000001)
static void fault_ops_read_fault_by_index_rawRequestHandlerImpl(ReqContext_t *pReqCtx,
            const fault_opsread_fault_by_index_rawRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    bool bIs_data_valid;
    uint8_t au8Exception_data_raw[152];

    // @USER_VAR_SECTION_START@fault_ops::read_fault_by_index_raw@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@fault_ops::read_fault_by_index_raw@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@fault_ops::read_fault_by_index_raw@

        (void) memset((void *) au8Exception_data_raw, 0U, sizeof(au8Exception_data_raw));
        bIs_data_valid = fault_persistor_read_single(pRequestData->u8Slot_id, (persisted_ram_x_frame_t *) au8Exception_data_raw);

        // @USER_CODE_SECTION_END@fault_ops::read_fault_by_index_raw@

        respResult = fault_ops_read_fault_by_index_rawResp(
                        &respCtx,
                        bIs_data_valid,
                        au8Exception_data_raw
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FAULT_OPS, FAULT_OPS_READ_FAULT_BY_INDEX_RAW_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method fault_ops::read_fault_by_index_raw (ID = 0x00000001)

// @START@ Request handler for method fault_ops::clear_all_faults (ID = 0x00000002)
static void fault_ops_clear_all_faultsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    bool bIs_clear_ok;

    // @USER_VAR_SECTION_START@fault_ops::clear_all_faults@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@fault_ops::clear_all_faults@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@fault_ops::clear_all_faults@

        fault_persistor_clear();
        bIs_clear_ok = true;

        // @USER_CODE_SECTION_END@fault_ops::clear_all_faults@

        respResult = fault_ops_clear_all_faultsResp(
                        &respCtx,
                        bIs_clear_ok
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FAULT_OPS, FAULT_OPS_CLEAR_ALL_FAULTS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method fault_ops::clear_all_faults (ID = 0x00000002)

// @START@ Request handler for method fault_ops::simulate_fault (ID = 0x00000003)
static void fault_ops_simulate_faultRequestHandlerImpl(ReqContext_t *pReqCtx,
            const fault_opssimulate_faultRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;

    // @USER_VAR_SECTION_START@fault_ops::simulate_fault@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@fault_ops::simulate_fault@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@fault_ops::simulate_fault@

        // TODO: Put your implementation to handle the
        // received server response here!
        switch (pRequestData->eFault_type)
        {
            case FAULT_OPS_FAULTTYPE_USAGE_FAULT:
            {
                // attempt access to the FPU after disabling it
                access_disabled_coprocessor();

                break;
            }

            case FAULT_OPS_FAULTTYPE_BUS_FAULT:
            {
                volatile uint32_t bad_addr_value = *(volatile uint32_t *) 0xbadcafe;

                break;
            }

            case FAULT_OPS_FAULTTYPE_MEM_FAULT:
            {
                // attempt to execute an invalid instruction
                // system space is always marked as XN (Execute Never), thus
                // we get an MPU fault
                int (*bad_instruction)(void) = (void *)0xE0000000;
                bad_instruction();

                break;
            }

            default:
            {
                break;
            }
        }

        // @USER_CODE_SECTION_END@fault_ops::simulate_fault@

        respResult = fault_ops_simulate_faultResp(
                        &respCtx
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FAULT_OPS, FAULT_OPS_SIMULATE_FAULT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method fault_ops::simulate_fault (ID = 0x00000003)

// @START@ Request handler for method fault_ops::read_fault_by_index (ID = 0x00000004)
static void fault_ops_read_fault_by_indexRequestHandlerImpl(ReqContext_t *pReqCtx,
            const fault_opsread_fault_by_indexRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    bool bIs_data_valid;
    FAULT_OPS_x_frame_t sException_data;

    // @USER_VAR_SECTION_START@fault_ops::read_fault_by_index@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@fault_ops::read_fault_by_index@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@fault_ops::read_fault_by_index@

        persisted_ram_x_frame_t stored_x_frame;
        bIs_data_valid = fault_persistor_read_single(pRequestData->u8Slot_id, (persisted_ram_x_frame_t *) &stored_x_frame);

        if (bIs_data_valid)
        {
            sException_data.sHdr.u32Record_type = stored_x_frame.hdr.record_type;
            sException_data.sHdr.u32Rtc_timestamp = stored_x_frame.hdr.exception_rtc_ts;
            sException_data.sHdr.u32Uptime = stored_x_frame.hdr.uptime;
            static_assert(sizeof(sException_data.sHdr.au8Reserved) == sizeof(stored_x_frame.hdr.reserved));
            (void) memcpy(sException_data.sHdr.au8Reserved, stored_x_frame.hdr.reserved, sizeof(sException_data.sHdr.au8Reserved));

            sException_data.u32Abfsr = stored_x_frame.abfsr;
            sException_data.u32Bfar = stored_x_frame.bfar;
            sException_data.u32Cfsr = stored_x_frame.cfsr;
            sException_data.u32Hfsr = stored_x_frame.hfsr;
            sException_data.u32Mmfar = stored_x_frame.mmfar;
            sException_data.u32Sp = stored_x_frame.sp;
            sException_data.u32Stack_frame_len = stored_x_frame.stack_frame_len;
            sException_data.u32Vtor = stored_x_frame.vtor;
            sException_data.sStack_frame.u32Fpscr = stored_x_frame.stack_frame.fpscr;
            static_assert(sizeof(sException_data.sStack_frame.au32Fp_ext_reg_s) == sizeof(stored_x_frame.stack_frame.fp_ext_reg_s));
            (void) memcpy(sException_data.sStack_frame.au32Fp_ext_reg_s, stored_x_frame.stack_frame.fp_ext_reg_s, sizeof(sException_data.sStack_frame.au32Fp_ext_reg_s));
            sException_data.sStack_frame.sBasic_regs.u32R0 = stored_x_frame.stack_frame.basic_regs.r0;
            sException_data.sStack_frame.sBasic_regs.u32R1 = stored_x_frame.stack_frame.basic_regs.r1;
            sException_data.sStack_frame.sBasic_regs.u32R2 = stored_x_frame.stack_frame.basic_regs.r2;
            sException_data.sStack_frame.sBasic_regs.u32R3 = stored_x_frame.stack_frame.basic_regs.r3;
            sException_data.sStack_frame.sBasic_regs.u32R12 = stored_x_frame.stack_frame.basic_regs.r12;
            sException_data.sStack_frame.sBasic_regs.u32Lr = stored_x_frame.stack_frame.basic_regs.lr;
            sException_data.sStack_frame.sBasic_regs.u32Pc = stored_x_frame.stack_frame.basic_regs.pc;
            sException_data.sStack_frame.sBasic_regs.u32Psr = stored_x_frame.stack_frame.basic_regs.psr;
            sException_data.u32Crc = stored_x_frame.crc;
        }
        else
        {
            (void) memset(&sException_data, 0U, sizeof(sException_data));
        }
        // @USER_CODE_SECTION_END@fault_ops::read_fault_by_index@

        respResult = fault_ops_read_fault_by_indexResp(
                        &respCtx,
                        bIs_data_valid,
                        &sException_data
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FAULT_OPS, FAULT_OPS_READ_FAULT_BY_INDEX_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method fault_ops::read_fault_by_index (ID = 0x00000004)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void fault_opsServerAppInit(void)
{
    fault_ops_registerServerApi(&fault_opsServerApiCtx);
}
