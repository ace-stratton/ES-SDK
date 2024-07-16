/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup service_sp
 * @{
 *
 * @file sp_service.c
 * @brief Solar Panels telemetry collection service main implementation.
 *
 * @}
 */
#include "sp_service.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "es_crc32.h"
#include "assertions.h"
#include "TaskMonitor.h"
#include "datacache.h"
#include "sys_instancer_ct.h"
#include "nvm.h"


#define TH_FLAG_RESPONSE 0x10   /**< Flag value used with osThreadFlagsWait() to unblock main task in case a response from the SSP is received*/

/**
  * @name SSP sampling configuration parameters
  * @{
  * These parameters shall be tuned such that telemetry from panels is captured no later
  * than 10 seconds in-between samples. Also we have to make sure that the
  * overall_sampling_interval_time_ms <= DATACACHE_data_timeout value otherwise the
  * data status will be set automatically to DC_DATA_STATUS_TOUT automatically:
  *
  * <b>overall_sampling_interval_ms =</b> @n
  * <b>(4 - number_of_working_panels) * SP_MAX_RETRIES * SP_POLLING_INTERVAL_MS + </b> <i>// total waiting time for non-operational panels</i> @n
  * <b>number_of_working_panels * (SP_MAX_RETRIES - 1) * SP_RESP_TIMEOUT_MS + 200 ms + </b> <i>// worst-case time for successful communication on the last retry for all working panels (200 ms assumed time for successful communication)</i> @n
  * <b>SP_POLLING_INTERVAL_MS <= 10000 ms</b>
  */

/** @brief Maximum number of SSP communication retries before switching to the next panel in the configuration */
#define SP_MAX_RETRIES         (2U)

/** @brief Period in milliseconds on which polling of the SSPs is performed */
#define SP_POLING_INTERVAL_MS  (3000U)

/** @brief Maximum time in milliseconds to wait for the solar panel to respond on the bus */
#define SP_RESP_TIMEOUT_MS     (800U)
/**@}*/

/** @brief Configuration for a single solar panel */
typedef struct
{
    uint8_t mac_addr;   /**< solar panel MAC address on the bus */
    dc_did_id dc_id;    /**< DataCache identifier for the corresponding solar panel data */
} ssp_call_ctx_t;

/** @brief Configuration interface for the system instancer */
if_sys_mod_t sp_module_configuration =
{
    .init = sp_init,
    .run = sp_run,
    .stop = sp_stop,
    .deinit = sp_deinit,
};

/** @brief OS task handle for the SP service */
static osThreadId_t h_sp_service_task = NULL;

/** @brief ESPS I communication context used for communicating to the SSP HW modules */
static ReqContext_t ctx;

/** @brief SSP communication schedule configuration used by the service */
static ssp_call_ctx_t ssp_dc_config[] =
{
    {
        .mac_addr = 0, // set to default address
        .dc_id = DC_DID_SSP_0_DATA
    },
    {
        .mac_addr = 0, // set to default address
        .dc_id = DC_DID_SSP_1_DATA
    },
    {
        .mac_addr = 0, // set to default address
        .dc_id = DC_DID_SSP_2_DATA
    },
    {
        .mac_addr = 0, // set to default address
        .dc_id = DC_DID_SSP_3_DATA
    }
};

/** @brief temporary storage for SSP-received data */
static DATA_CACHE_SSP_0_t tlm_ssp;


static void sp_service_task(void* argument);


/**
 * @name Implementation of if_sys_instancer.h for the SP service.
 * @{
 */
mod_op_status_id_t sp_init(sys_init_level_id_t level)
{
    mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

    // Eventually, to split the initialisation into the different levels
    if (level ==  INIT_MEM)
    {
    	// Read the MAC Addresses from the NVM
    	mac_address_book_t addresses = {0};

    	// Read the NVM
    	Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

        // Update all the mac addresses
        CRIT_ASSERT(4 == CDEF_ELEMENT_COUNT(ssp_dc_config));
        ssp_dc_config[0].mac_addr = addresses.a_mac_address[MAC_ADDR_SP1];
        ssp_dc_config[1].mac_addr = addresses.a_mac_address[MAC_ADDR_SP2];
        ssp_dc_config[2].mac_addr = addresses.a_mac_address[MAC_ADDR_SP3];
        ssp_dc_config[3].mac_addr = addresses.a_mac_address[MAC_ADDR_SP4];

        ret = STATUS_OK;
    }
    else if (level ==  INIT_HW)
    {
        ret = STATUS_NOT_SUPPORTED;
    }
    else if (level ==  INIT_OS)
    {
        osThreadAttr_t attr =
        {
            .attr_bits  = osThreadDetached,
            .name       = "sp_service_task",
            .priority   = osPriorityNormal,
            .cb_mem     = NULL,
            .cb_size    = 0U,
            .stack_mem  = NULL,
            .stack_size = 128 * 16,
            .tz_module  = 0U,
            .reserved   = 0U,
        };

        if (NULL == h_sp_service_task)
        {
            h_sp_service_task = osThreadNew(sp_service_task, NULL, &attr);
            CRIT_ASSERT(h_sp_service_task);
        }

        // Set the task monitor policy
        task_mon_set_task_policy(TASK_MONITOR_SP, TASK_MON_POLICY_MONITOR);
        ret = STATUS_OK;
    }
    else
    {
        ret = STATUS_NOT_SUPPORTED;
    }

    return ret;
}


mod_op_status_id_t sp_run(void)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}


mod_op_status_id_t sp_stop(void)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}


mod_op_status_id_t sp_deinit(sys_init_level_id_t level)
{
    // This is to be implemented
    if (INIT_OS == level)
    {
        task_mon_set_task_policy(TASK_MONITOR_SP, TASK_MON_POLICY_DONT_CARE);
    }

    return STATUS_OK;
}
/**@}*/


/**
 * @brief Main SP OS task routine
 * Performs SSP regular sampling and stores the received sensory data to the
 * DataCache.
 *
 * @param[in] argument reserved for future argument passing to the OS task
 *
 */
static void sp_service_task(void* argument)
{
    (void)argument;
    int32_t wait_ret;
    ESSATMAC_ErrCodes reqStatus;

    TaskMonitor_TaskInitialized(TASK_MONITOR_SP);

    while(1)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_SP);

        for (uint8_t ssp_index = 0; ssp_index < CDEF_ELEMENT_COUNT(ssp_dc_config); ssp_index++)
        {
            for (uint8_t retry = 0; retry < SP_MAX_RETRIES; retry++)
            {
                ctx.nAddr = ssp_dc_config[ssp_index].mac_addr;
                ctx.nInterfaceNumber = ESSASNI_SYS_PRI;
                ctx.seqId = 0;
                ctx.netType = ESSASNETT_INTERNAL;

                reqStatus = SP_GetTelemetryReq(&ctx);

                if (reqStatus == ESSATMAC_EC_OK)
                {
                    // wait for response
                    wait_ret = osThreadFlagsWait(TH_FLAG_RESPONSE, osFlagsWaitAny, SP_RESP_TIMEOUT_MS);

                    if (TH_FLAG_RESPONSE == wait_ret)
                    {
                        dc_set_raw_data(DC_DATA_INPUT_INTERNAL,
                                        ssp_dc_config[ssp_index].dc_id,
                                        (void *) &tlm_ssp,
                                        sizeof(tlm_ssp));

                        break;
                    }
                }
            }
        }

        osDelay(SP_POLING_INTERVAL_MS);

        vApplicationLowStackCheck(TASK_MONITOR_SP);
    }
}


/**
 * @brief Called by the SP FIDL service when a response is received from any of the solar panels.
 *
 * Buffers the received SSP data to the local module cache and signals the main task that new
 * data is received.
 *
 * @param[in] pRespCtx Communication context structure
 * @param[in] pResponseData A pointer to the received solar panels data
 */
void sp_response_received(RespContext_t* p_resp_ctx, const SPGetTelemetryResponseData_t* p_resp_data)
{
    if (p_resp_ctx->nAddr == ctx.nAddr)
    {
        tlm_ssp.u16SunDataMain = p_resp_data->sData.sSunData.u16SunDataMain;
        tlm_ssp.u16SunDataExt  = p_resp_data->sData.sSunData.u16SunDataExt;
        tlm_ssp.i16TempMCU     = p_resp_data->sData.sTempData.i16TempDataMCU;
        tlm_ssp.i16TempMain    = p_resp_data->sData.sTempData.i16TempDataMain;
        tlm_ssp.i16TempExt1    = p_resp_data->sData.sTempData.i16TempDataExt1;
        tlm_ssp.i16TempExt2    = p_resp_data->sData.sTempData.i16TempDataExt2;

        osThreadFlagsSet(h_sp_service_task, TH_FLAG_RESPONSE);
    }
}
