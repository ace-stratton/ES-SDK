/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2.c
 * @brief    Cubeadcs Gen2 main service
 *
 * @}
 */

/*
 ********************************************************************************************
 * INCLUDES
 ********************************************************************************************
 */

#include "cmsis_os2.h"

#include "es_cdef.h"
#include "es_exeh.h"
#include "taskmon_cfg.h"
#include "TaskMonitor.h"
#include "../inc/cubeadcs_gen2.h"
#include "../gen/cubeadcs_gen2_sm_user.h"
#include "../cfg/cubeadcs_gen2_cfg.h"
#include "assertions.h"
#include "../inc/cubeadcs_gen2_gw.h"
#include "datacache.h"
#include "../inc/cubeadcs_gen2_events.h"
#include "../inc/cubeadcs_gen2_fdir.h"
#include "../inc/cubeadcs_gen2_tlm.h"
#include "nvm.h"

#include <string.h>

/*
 *********************************************************************************************
 * INTERNAL DEFINES
 *********************************************************************************************
 */

/** @brief State change maximum number of retries */
#define CUBEADCS_GEN2_STATE_CHANGE_MAX_RTRY (3)

/*
 *********************************************************************************************
 * INTERNAL TYPES DEFINITION
 *********************************************************************************************
 */

/** @brief States of the SM state handler */
typedef enum
{
    STATE_HANDLER_IDLE,
    STATE_HANDLER_BUSY,

    STAT_HANDLER_MAX
} eStateHandlerStatus_t;

/** @brief State change states */
typedef enum
{
    STATE_CHANGE_PWR_ON,
    STATE_CHANGE_EST,
    STATE_CHANGE_CONTROL,
    STATE_CHANGE_REF_PARAMS,

    STATE_CHANGE_MAX
} eStateChange_t;

/** @brief State change stages */
typedef enum
{
    STATE_CHANGE_STAGE_CHECK,
    STATE_CHANGE_STAGE_SET,

    STATE_CHANGE_STAGE_MAX
} state_change_stages_t;


/** @brief Function pointer type for state handler functions*/
typedef void (*state_handler_t)(void);

/** @brief Function pointer type for API calls */
typedef bool (*api_call_t)(void);

/** @brief Simple linked list type used by the state change logic */
typedef struct state_change_step_s
{
    const api_call_t state_step_check;
    const api_call_t state_step_exec;
    const uint8_t next;
    const uint8_t max_rtry;
    uint8_t rtry;
} state_change_step_t;

/** @brief Type used to store any configuration data of the CubeComputer which is needed by the Gen2 service. */
typedef struct
{
    TctlmCubeComputerCommon3_ExpectedNodes exp_nodes; /**< Structure holding the list of nodes that the CubeComputer expects
                                                           to be connected to it */
    bool is_exp_nodes_init;                           /**< Flag indicating whether exp_nodes is filled with valid data from
                                                           CubeComputer */
} adcs_cfg_cache_t;

/*
 *********************************************************************************************
 * EXTERNAL VARIABLES DEFINITION
 *********************************************************************************************
 */

/*
 *********************************************************************************************
 * INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
 *********************************************************************************************
 */
/** @brief The gen2 service context */
static cubeadcs_gen2_service_ctx_t cubeadcs_gen2_service_ctx;

/** @brief The CubeADCS Gen2 control task attributes */
static const osThreadAttr_t cubeadcs_gen2_task_attr = {
        .name = "fs_cubeadcs_gen2_main_service_task",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 2048 // 1500 not enough ...
};

/** @brief CubeADCS Gen2 SM trigger control mutex */
static osMutexId_t cubeadcs_gen2_sm_lock;
/** @brief CubeADCS Gen2 SM trigger control mutex attributes */
static const osMutexAttr_t cubeadcs_gen2_sm_lock_attr = {
        "cubeadcs_gen2_sm_lock_mutex",
        osMutexRecursive | osMutexPrioInherit,
        NULL,
        0U
};

/** @brief Service context mutex */
static osMutexId_t cubeadcs_gen2_service_ctx_lock;
/** @brief Service context mutex */
static const osMutexAttr_t cubeadcs_gen2_service_ctx_lock_attr = {
        "cubeadcs_gen2_service_ctx_lock_mutex",
        osMutexRecursive | osMutexPrioInherit,
        NULL,
        0U
};

/** @brief Mutex used for accessing the cached ADCS configuration */
static osMutexId_t cubeadcs_gen2_adcs_cfg_cache_lock;

/** @brief Attributes for the mutex used for for accessing the cached ADCS configuration */
static const osMutexAttr_t cubeadcs_gen2_adcs_cfg_cache_lock_attr = {
        "cubeadcs_gen2_adcs_cfg_cache_lock_mutex",
        osMutexRecursive | osMutexPrioInherit,
        NULL,
        0U
};


/** @brief Stored configuration data of the Gen2 CubeComputer
 *
 *  @note It is expected to be read once on initialization of the Gen2 service
 */
static adcs_cfg_cache_t cubeadcs_gen2_adcs_cfg_cache = {.is_exp_nodes_init = false};
/*
 *********************************************************************************************
 * INTERNAL (STATIC) ROUTINES DECLARATION
 *********************************************************************************************
 */
STATIC void fs_cubeadcs_gen2_task(void *arg);
STATIC eStateHandlerStatus_t fs_cubeadcs_gen2_state_handler(const uint8_t sm_state);

STATIC void fs_cubeadcs_gen2_state_handler_dummy(void);
STATIC void fs_cubeadcs_gen2_state_handler_check(void);
STATIC void fs_cubeadcs_gen2_state_handler_event_dwn(void);
STATIC void fs_cubeadcs_gen2_state_handler_state_change(void);
STATIC void fs_cubeadcs_gen2_state_handler_state_fdir(void);
STATIC void fs_cubeadcs_gen2_state_handler_event_marker_acquisition(void);

STATIC bool fs_cubeadcs_gen2_state_change_pwr_check(void);
STATIC bool fs_cubeadcs_gen2_state_change_pwr_change(void);
STATIC bool fs_cubeadcs_gen2_state_change_est_check(void);
STATIC bool fs_cubeadcs_gen2_state_change_est_change(void);
STATIC bool fs_cubeadcs_gen2_state_change_ctrl_check(void);
STATIC bool fs_cubeadcs_gen2_state_change_ctrl_change(void);
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check(void);
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_change(void);

STATIC bool fs_cubeadcs_gen2_state_change_ref_params_common(const state_change_stages_t req_stage);
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_rpy(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage);
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_coord(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage);
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_eci(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage);
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_open_loop_rw(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage);

STATIC bool fs_cubeadcs_gen2_lock_ctx(void);
STATIC bool fs_cubeadcs_gen2_unlock_ctx(void);

STATIC bool fs_cubeadcs_gen2_get_exp_nodes_config(TctlmCubeComputerCommon3_ExpectedNodes * const p_exp_nodes);

/** @brief State handlers list */
STATIC const state_handler_t state_handler[STATE_MAX] = {
        fs_cubeadcs_gen2_state_handler_dummy,
        fs_cubeadcs_gen2_state_handler_dummy,
        fs_cubeadcs_gen2_state_handler_event_marker_acquisition,
        fs_cubeadcs_gen2_state_handler_dummy,
        fs_cubeadcs_gen2_state_handler_check,
        fs_cubeadcs_gen2_state_handler_event_dwn,
        fs_cubeadcs_gen2_state_handler_state_change,
        fs_cubeadcs_gen2_state_handler_state_fdir,
};

/** @brief State change list */
STATIC state_change_step_t state_change_list[STATE_CHANGE_MAX] =
{
        {fs_cubeadcs_gen2_state_change_pwr_check, fs_cubeadcs_gen2_state_change_pwr_change, STATE_CHANGE_EST, CUBEADCS_GEN2_STATE_CHANGE_MAX_RTRY, 0},
        {fs_cubeadcs_gen2_state_change_est_check, fs_cubeadcs_gen2_state_change_est_change, STATE_CHANGE_CONTROL, CUBEADCS_GEN2_STATE_CHANGE_MAX_RTRY, 0},
        {fs_cubeadcs_gen2_state_change_ctrl_check, fs_cubeadcs_gen2_state_change_ctrl_change, STATE_CHANGE_REF_PARAMS, CUBEADCS_GEN2_STATE_CHANGE_MAX_RTRY, 0},
        {fs_cubeadcs_gen2_state_change_ref_params_check, fs_cubeadcs_gen2_state_change_ref_params_change, STATE_CHANGE_PWR_ON, CUBEADCS_GEN2_STATE_CHANGE_MAX_RTRY, 0}
};

/*
 *********************************************************************************************
 * EXTERNAL (NON-STATIC) ROUTINES DEFINITION
 *********************************************************************************************
 */
void cubeadcs_gen2_os_init(void)
{
    cubeadcs_gen2_sm_lock = osMutexNew(&cubeadcs_gen2_sm_lock_attr);

    cubeadcs_gen2_service_ctx_lock = osMutexNew(&cubeadcs_gen2_service_ctx_lock_attr);

    cubeadcs_gen2_adcs_cfg_cache_lock = osMutexNew(&cubeadcs_gen2_adcs_cfg_cache_lock_attr);

    cubeadcs_gen2_service_ctx.cubeadcs_gen2_task_handle = osThreadNew(fs_cubeadcs_gen2_task, NULL, &cubeadcs_gen2_task_attr);

    cubeadcs_gen2_events_init_os();

    cubeadcs_gen2_fdir_init_os();

    if ( NULL == cubeadcs_gen2_service_ctx.cubeadcs_gen2_task_handle )
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Fatal, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_TASK_SPAWN_ERROR)
    }
    else
    {
        TaskMonitor_TaskInitialized(TASK_MONITOR_CUBEADCS_GEN2);
        task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_GEN2, TASK_MON_POLICY_MONITOR);
    }
}

void cubeadcs_gen2_os_deinit(void)
{
    task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_GEN2, TASK_MON_POLICY_DONT_CARE);
}

bool cubeadcs_gen2_trigger_sm(const uint32_t event_id, const sm_event_ctx_t * const event_ctx)
{
    bool op_res;

    sm_event_t event;

    if ( osOK != osMutexAcquire(cubeadcs_gen2_sm_lock, osWaitForever) )
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    event.base_event.id = event_id;

    if ( NULL != event_ctx)
    {
        memcpy(&event.event_ctx, event_ctx, sizeof(sm_event_ctx_t));
    }
    else
    {
        memset(&event.event_ctx, 0, sizeof(sm_event_ctx_t));
    }

    op_res = HSM_TriggerEvent_raw(cubeadcs_gen2_sm_instance, &event.base_event);

    if ( osOK != osMutexRelease(cubeadcs_gen2_sm_lock) )
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    return op_res;
}

const sState_t *cubeadcs_gen2_get_sm_state(void)
{
    return HSM_GetActiveState(cubeadcs_gen2_sm_instance);
}

void cubeadcs_gen2_state_change_init(void)
{
    for (uint8_t i = 0; i < STATE_CHANGE_MAX; i++)
    {
        state_change_list[i].rtry = 0;
    }
}

void cubeadcs_gen2_get_op_status(op_status_t * const p_op_status)
{
    CRIT_ASSERT(NULL != p_op_status);

    dc_data_status_t dc_status;

    dc_status = dc_get_raw_data(DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA, &p_op_status->common_tlm, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t), 0U, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t));
    (dc_status == DC_DATA_STATUS_OK) ? (p_op_status->common_tlm.is_valid = true) : (p_op_status->common_tlm.is_valid = false);

    dc_status = dc_get_raw_data(DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA, &p_op_status->app_tlm, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t), 0U, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t));
    (dc_status == DC_DATA_STATUS_OK) ? (p_op_status->app_tlm.is_valid = true) : (p_op_status->app_tlm.is_valid = false);

}

bool cubeadcs_gen2_set_sys_state(const cubeadcs_gen2_sys_state_t * const p_new_sys_state)
{
    CRIT_ASSERT(NULL != p_new_sys_state);

    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_lock_ctx() )
    {
        cubeadcs_gen2_service_ctx.current_system_state = *p_new_sys_state;

        op_res = true;

        (void)fs_cubeadcs_gen2_unlock_ctx();
    }

    return op_res;
}

bool cubeadcs_gen2_set_sys_state_change_status(const cubeadcs_gen2_sys_state_change_status_t new_sys_state_change_status)
{
    CRIT_ASSERT(new_sys_state_change_status < CUBEADCS_GEN2_SYS_STATE_CHANGE_MAX);

    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_lock_ctx() )
    {
        cubeadcs_gen2_service_ctx.state_change_status = new_sys_state_change_status;

        op_res = true;

        (void)fs_cubeadcs_gen2_unlock_ctx();
    }

    return op_res;
}

bool cubeadcs_gen2_get_service_ctx(cubeadcs_gen2_service_ctx_t * const p_ctx)
{
    CRIT_ASSERT(NULL != p_ctx);

    bool op_res = false;

    if ( true == fs_cubeadcs_gen2_lock_ctx() )
    {
        *p_ctx = cubeadcs_gen2_service_ctx;

        (void)fs_cubeadcs_gen2_unlock_ctx();

        op_res = true;
    }

    return op_res;
}

bool cubeadcs_gen2_reset_handler(cubeadcs_gen2_control_program_type_t prog_type_req)
{
    CRIT_ASSERT(prog_type_req < CUBEADCS_GEN2_CONTROL_PROGRAM_TYPE_MAX);

    bool op_res = true;

    if ((true == cubeadcs_gen2_trigger_sm(eHSM_StdEvent_Reset, NULL)) &&
            (CUBEOBC_ERROR_TOUT == CubeADCS_Gen2_CommonFramework1_setResetRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, TCTLM_COMMON_FRAMEWORK_1__SOFT, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)))
    {
        // Give it some time to boot
        osDelay(1000U);

        if ((CUBEADCS_GEN2_CONTROL_PROGRAM_TYPE_BOOTLOADER == prog_type_req) &&
                (CUBEOBC_ERROR_OK != CubeADCS_Gen2_CubeCommonBaseBootloader5_setHaltRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)))
        {
            op_res = false;
        }
    }
    else
    {
        op_res = false;
    }

    return op_res;
}

bool cubeadcs_gen2_get_cms_status(uint8_t * const p_status)
{
    bool op_res = false;

    if (NULL != p_status)
    {
        adcs_cms_status_t cms_status;

        Nvm_GetBlockById(NVM_BLOCK_ADCS_CMS_STATUS, &cms_status);
        *p_status = cms_status.cms_status;

        op_res = true;
    }
    else
    {
        CRIT_ASSERT(false);
    }

    return op_res;
}

bool cubeadcs_gen2_set_cms_status(const uint8_t new_status)
{
    adcs_cms_status_t cms_status;

    cms_status.cms_status = new_status;
    Nvm_SetBlockById(NVM_BLOCK_ADCS_CMS_STATUS, &cms_status, NVMSETBLOCK_STORE_IMMEDIATELY);

    return true;
}

bool cubeadcs_gen2_init_adcs_cfg_cache(void)
{
    bool result = false;

    if (osOK == osMutexAcquire(cubeadcs_gen2_adcs_cfg_cache_lock, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
    {
        const ErrorCode err = CubeADCS_Gen2_CubeComputerCommon3_getExpectedNodesRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER,
                                                                                                  &cubeadcs_gen2_adcs_cfg_cache.exp_nodes,
                                                                                                  CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
        if (CUBEOBC_ERROR_OK == err)
        {
            cubeadcs_gen2_adcs_cfg_cache.is_exp_nodes_init = true;
            result = true;
        }

        (void)osMutexRelease(cubeadcs_gen2_adcs_cfg_cache_lock);
    }

    return result;
}

TctlmCommonFrameworkEnums_NodeType cubeadcs_gen2_get_node_type(const TctlmCommonFrameworkEnums_AbstractNode abstract_node_type)
{
    TctlmCommonFrameworkEnums_NodeType     result = TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_INVALID;
    TctlmCubeComputerCommon3_ExpectedNodes exp_nodes;

    if (false != fs_cubeadcs_gen2_get_exp_nodes_config(&exp_nodes))
    {
        if (abstract_node_type == exp_nodes.expected0AbstractType)
        {
            result = exp_nodes.expected0NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected1AbstractType)
        {
            result = exp_nodes.expected1NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected2AbstractType)
        {
            result = exp_nodes.expected2NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected3AbstractType)
        {
            result = exp_nodes.expected3NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected4AbstractType)
        {
            result = exp_nodes.expected4NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected5AbstractType)
        {
            result = exp_nodes.expected5NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected6AbstractType)
        {
            result = exp_nodes.expected6NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected7AbstractType)
        {
            result = exp_nodes.expected7NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected8AbstractType)
        {
            result = exp_nodes.expected8NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected9AbstractType)
        {
            result = exp_nodes.expected9NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected10AbstractType)
        {
            result = exp_nodes.expected10NodeType;
        }
        else if (abstract_node_type == exp_nodes.expected11AbstractType)
        {
            result = exp_nodes.expected11NodeType;
        }
        else
        {
            // The abstract node is not present in the configuration.
        }
    }

    return result;
}

/*
 *********************************************************************************************
 * INTERNAL (STATIC) ROUTINES DEFINITION
 *********************************************************************************************
 */
/** @brief The CubeADCS Gen2 main service task
 *
 *  @param[in] void *args - task arguments
 *
 */
STATIC void fs_cubeadcs_gen2_task(void *arg)
{
    (void)cubeadcs_gen2_trigger_sm(eHSM_StdEvent_Reset, NULL);

    static uint32_t wait_mark;

    for(;;)
    {
        wait_mark = osKernelGetTickCount();

        CUBEADCS_GEN2_TRACE_INFO("%s: %s\r", CUBEADCS_GEN2_DBG_HEAD, cubeadcs_gen2_get_sm_state()->pName);

        if ( STATE_HANDLER_BUSY == fs_cubeadcs_gen2_state_handler(cubeadcs_gen2_get_sm_state()->state_id) )
        {
            osDelayUntil( (wait_mark + CUBEADCS_GEN2_SM_TASK_FAST_PERIOD_MS) );
        }
        else
        {
            (void)cubeadcs_gen2_trigger_sm(eHSM_StdEvent_Periodic, NULL);

            osDelayUntil( (wait_mark + CUBEADCS_GEN2_SM_TASK_BASE_PERIOD_MS) );
        }

        TaskMonitor_IamAlive(TASK_MONITOR_CUBEADCS_GEN2);
        vApplicationLowStackCheck(TASK_MONITOR_CUBEADCS_GEN2);
    }
}

/** @brief CubeADCS Gen2 SM handler logic
 *
 *  @param[in] uint8_t sm_state - the current state of the CubeADCS Gen2 SM
 * 
 *  @return eStateHandlerStatus_t - the status of the handler logic
 *
 */
STATIC eStateHandlerStatus_t fs_cubeadcs_gen2_state_handler(const uint8_t sm_state)
{
    eStateHandlerStatus_t op_res = STATE_HANDLER_IDLE;

    switch (sm_state)
    {
    case STATE_EVENTMARKERACQUISITION:
    case STATE_CHECK:
    case STATE_STATECHANGE:
    case STATE_EVENTDOWNLOAD:
    case STATE_FDIR:
    {
        state_handler[sm_state]();

        op_res = STATE_HANDLER_BUSY;
        break;
    }
    default:
    {
        break;
    }
    }

    return op_res;
}

/** @brief Dummy handler */
STATIC void fs_cubeadcs_gen2_state_handler_dummy(void)
{
    CUBEADCS_GEN2_TRACE_INFO("%s: State Handler Dummy\r", CUBEADCS_GEN2_DBG_HEAD);
}

/** @brief SM state check handler logic 
 * 
 * 
 *  @note Collects health check telemetry and stores it in a RAM buffer
 * 
 */
STATIC void fs_cubeadcs_gen2_state_handler_check(void)
{
    CUBEADCS_GEN2_TRACE_INFO("%s: State Handler Check\r", CUBEADCS_GEN2_DBG_HEAD);

    op_status_t op_status_cache = {0};

    op_status_cache.common_tlm.is_valid = true;
    op_status_cache.app_tlm.is_valid = false;

    if ((CUBEOBC_ERROR_OK == CubeADCS_Gen2_CommonFramework1_getBootStatusRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &op_status_cache.common_tlm.boot_status, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
            (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerCommon3_getPowerStateRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &op_status_cache.common_tlm.power_state, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
            (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerCommon3_getComponentErrorCodesRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &op_status_cache.common_tlm.comp_err_codes, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)))
    {
        dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA, &op_status_cache.common_tlm, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t));

        op_status_cache.app_tlm.is_valid = true;

        if ((TCTLM_COMMON_FRAMEWORK_1__APPLICATION_RUNNING == op_status_cache.common_tlm.boot_status.state) &&
                (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsRunModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &op_status_cache.app_tlm.run_mode, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
                (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getEstModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &op_status_cache.app_tlm.est_mode, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
                (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getConModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER,&op_status_cache.app_tlm.control_mode, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
                (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsOpStateRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &op_status_cache.app_tlm.op_state, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)))
        {
            dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA, &op_status_cache.app_tlm, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t));
        }
        else
        {
            op_status_cache.app_tlm.is_valid = false;

            EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2, EXEH_CUBEADCS_GEN2_PERIODIC_HEALTH_CHECK_FAILDED)
        }

        if ( TCTLM_COMMON_FRAMEWORK_1__APPLICATION_RUNNING == op_status_cache.common_tlm.boot_status.state )
        {
            cubeadcs_gen2_tlm_get_tlm();
        }
    }
    else
    {
        op_status_cache.common_tlm.is_valid = false;

        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2, EXEH_CUBEADCS_GEN2_PERIODIC_HEALTH_CHECK_FAILDED)
    }

    (void)cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_check_completed, NULL);
}

/** @brief SM state event download
 *
 *
 *  @note Downloads the events to a file and parses them. Invokes the FDIR logic in case of an error.
 *
 */
STATIC void fs_cubeadcs_gen2_state_handler_event_dwn(void)
{
    CUBEADCS_GEN2_TRACE_INFO("%s: State Handler Event Download\r", CUBEADCS_GEN2_DBG_HEAD);

    bool is_new_crit_event_detected;

    if ( true == cubeadcs_gen2_events_dwn_new_crit_events(&is_new_crit_event_detected) )
    {
        if ( true == is_new_crit_event_detected )
        {
            (void)cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_request_fdir, NULL);
        }
        else
        {
            (void)cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_event_download_completed, NULL);
        }
    }
}

/** @brief SM state state change handler logic 
 * 
 * 
 *  @note Executes the ADCS state change logic by checking and setting the run mode, nodes power state, estimator and controller, and ref. parameters
 * 
 */
STATIC void fs_cubeadcs_gen2_state_handler_state_change(void)
{
    static uint8_t step_indx = 0;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Handler State Change\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == state_change_list[step_indx].state_step_check() )
    {
        step_indx = state_change_list[step_indx].next;

        if ( 0 == step_indx )
        {
            (void)cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_state_change_completed, NULL);
        }
    }
    else
    {
        // We skip the check intentionally since there is a retry counter for the execution
        (void)state_change_list[step_indx].state_step_exec();

        ++state_change_list[step_indx].rtry;

        if ( state_change_list[step_indx].rtry >= state_change_list[step_indx].max_rtry )
        {
            step_indx = 0;

            EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS_GEN2,
                    EXEH_CUBEADCS_GEN2_SYS_STATE_CHANGE_FAILED)

            (void)cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_request_fdir, NULL);
        }
    }
}

/** @brief SM state fdir handler logic
 * 
 * 
 *  @note Executes the FDIR logic related to the detected error or notifies parent FDIR logic to take action
 * 
 */
STATIC void fs_cubeadcs_gen2_state_handler_state_fdir(void)
{
    CUBEADCS_GEN2_TRACE_INFO("%s: State Handler FDIR\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == cubeadcs_gen2_fdir_exec() )
    {
        (void)cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_fdir_completed, NULL);
    }
}

/** @brief SM state event marker acquisition handler logic
 * 
 * 
 *  @note Gets the last event from the CubeComputer and stores it in the event marker cache
 * 
 */
STATIC void fs_cubeadcs_gen2_state_handler_event_marker_acquisition(void)
{
    CUBEADCS_GEN2_TRACE_INFO("%s: State Handler Event Marker Acquisition\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == cubeadcs_gen2_events_get_marker() )
    {
        (void)cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_event_marker_acquired, NULL);
    }
}

/** @brief Check power state of nodes
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_state_change_pwr_check(void)
{
    bool op_res = false;

    TctlmCubeComputerCommon3_PowerState adcs_pwr_state;
    cubeadcs_gen2_service_ctx_t service_ctx;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Change Node Power Check\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == cubeadcs_gen2_get_service_ctx(&service_ctx) )
    {
        if ( (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerCommon3_getPowerStateRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &adcs_pwr_state, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
                (0 == memcmp(&adcs_pwr_state, &service_ctx.current_system_state.sys_state_core_cfg.pwr_state, sizeof(TctlmCubeComputerCommon3_PowerState))) )
        {
            op_res = true;
        }
    }

    return op_res;
}

/** @brief Change power state of nodes
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_state_change_pwr_change(void)
{
    bool op_res = false;
    cubeadcs_gen2_service_ctx_t service_ctx;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Change Node Power Change\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == cubeadcs_gen2_get_service_ctx(&service_ctx) )
    {
        if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerCommon3_setPowerStateRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &service_ctx.current_system_state.sys_state_core_cfg.pwr_state, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
        {
            op_res = true;
        }
    }

    return op_res;
}

/** @brief Check estimator modes
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_state_change_est_check(void)
{
    bool op_res = false;

    TctlmCubeComputerControlProgram8_EstMode adcs_est_modes;
    cubeadcs_gen2_service_ctx_t service_ctx;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Change Estimator Check\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == cubeadcs_gen2_get_service_ctx(&service_ctx) )
    {
        if ( (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getEstModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &adcs_est_modes, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
                (adcs_est_modes.estModeMain == service_ctx.current_system_state.sys_state_core_cfg.est_mode_main) &&
                (adcs_est_modes.estModeBackup == service_ctx.current_system_state.sys_state_core_cfg.est_mode_backup) )
        {
            op_res = true;
        }
    }

    return op_res;
}

/** @brief Change estimator modes
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_state_change_est_change(void)
{
    bool op_res = false;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Change Estimator Change\r", CUBEADCS_GEN2_DBG_HEAD);

    TctlmCubeComputerControlProgram8_EstMode adcs_est_modes;
    cubeadcs_gen2_service_ctx_t service_ctx;

    if ( true == cubeadcs_gen2_get_service_ctx(&service_ctx) )
    {
        adcs_est_modes.estModeMain = service_ctx.current_system_state.sys_state_core_cfg.est_mode_main;
        adcs_est_modes.estModeBackup = service_ctx.current_system_state.sys_state_core_cfg.est_mode_backup;

        if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_setEstModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &adcs_est_modes, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT) )
        {
            op_res = true;
        }
    }

    return op_res;
}

/** @brief Check control mode
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_state_change_ctrl_check(void)
{
    bool op_res = false;

    TctlmCubeComputerControlProgram8_ConMode adcs_ctrl_mode;

    cubeadcs_gen2_service_ctx_t service_ctx;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Change Control Mode Check\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == cubeadcs_gen2_get_service_ctx(&service_ctx) )
    {
        if ( (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getConModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &adcs_ctrl_mode, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT)) &&
                (adcs_ctrl_mode.controlMode == service_ctx.current_system_state.sys_state_core_cfg.cntrl_mode) )
        {
            op_res = true;
        }
    }

    return op_res;
}

/** @brief Change control mode
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_state_change_ctrl_change(void)
{
    bool op_res = false;

    TctlmCubeComputerControlProgram8_ConMode adcs_ctrl_mode;
    cubeadcs_gen2_service_ctx_t service_ctx;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Change Control Mode Change\r", CUBEADCS_GEN2_DBG_HEAD);

    if ( true == cubeadcs_gen2_get_service_ctx(&service_ctx) )
    {
        adcs_ctrl_mode.controlMode = service_ctx.current_system_state.sys_state_core_cfg.cntrl_mode;
        adcs_ctrl_mode.magConTimeout = 0U;

        if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_setConModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &adcs_ctrl_mode, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT) )
        {
            op_res = true;
        }
    }

    return op_res;
}

/** @brief Check reference parameters
 *
 *  @retval true - On success
 *  @retval false - On failure
 *
 *  @note This function intentionally returns FALSE until the last check to enforce the set of the parameters
 *
 */
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check(void)
{
    bool b_op_res = false;

    CUBEADCS_GEN2_TRACE_INFO("%s: State Change REF Params Check\r", CUBEADCS_GEN2_DBG_HEAD);

    // Skip all but the last check to force the set of the parameters
    if ( (CUBEADCS_GEN2_STATE_CHANGE_MAX_RTRY - 1) == state_change_list[STATE_CHANGE_REF_PARAMS].rtry )
    {
        b_op_res = fs_cubeadcs_gen2_state_change_ref_params_common(STATE_CHANGE_STAGE_CHECK);
    }

    return b_op_res;
}

/** @brief Change reference parameters
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_change(void)
{
    CUBEADCS_GEN2_TRACE_INFO("%s: State Change REF Params Set\r", CUBEADCS_GEN2_DBG_HEAD);

    return fs_cubeadcs_gen2_state_change_ref_params_common(STATE_CHANGE_STAGE_SET);
}

/** @brief Lock service context
 *
 *  @note Mutex lock is set to wait forever
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_lock_ctx(void)
{
    bool op_res = true;

    if ( osOK != osMutexAcquire(cubeadcs_gen2_service_ctx_lock, osWaitForever) )
    {
        op_res = false;

        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    return op_res;
}

/** @brief Unlock service context
 *
 *  @retval true - On success
 *  @retval false - On failure
 */
STATIC bool fs_cubeadcs_gen2_unlock_ctx(void)
{
    bool op_res = true;

    if ( osOK != osMutexRelease(cubeadcs_gen2_service_ctx_lock) )
    {
        op_res = false;

        EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_CUBEADCS_GEN2,
                EXEH_CUBEADCS_GEN2_OS_OBJ_ERR)
    }

    return op_res;
}

/** @brief Getter function for the configuration of expected nodes. Returns a copy of the configuration in its output parameter
 *
 *  @param[out] TctlmCubeComputerCommon3_ExpectedNodes * p_exp_nodes - address where the retrieved configuration shall be stored
 *
 *  @retval true  - On success
 *  @retval false - On failure. Will fail if the configuration is not yet read from CubeComputer, there is a mutex
 *                  acquisition error or the provided output pointer is NULL.
 */
STATIC bool fs_cubeadcs_gen2_get_exp_nodes_config(TctlmCubeComputerCommon3_ExpectedNodes * const p_exp_nodes)
{
    bool result = false;

    if (osOK == osMutexAcquire(cubeadcs_gen2_adcs_cfg_cache_lock, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
    {
        if ( (false != cubeadcs_gen2_adcs_cfg_cache.is_exp_nodes_init) && (NULL != p_exp_nodes) )
        {
            memcpy(p_exp_nodes, &cubeadcs_gen2_adcs_cfg_cache.exp_nodes, sizeof(TctlmCubeComputerCommon3_ExpectedNodes));
            result = true;
        }

        (void)osMutexRelease(cubeadcs_gen2_adcs_cfg_cache_lock);
    }

    return result;
}
/** @brief Common logic used during the state change for the reference parameters
 *
 *  @param[in] state_change_stages_t req_stage - requested stage of the state change
 *
 *  @retval true - On success
 *  @retval false - On failure
 *
 *  @note If the user coded control mode is used, no parameters are passed since it is unclear what this control mode is supposed to do!
 */
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_common(const state_change_stages_t req_stage)
{
    CRIT_ASSERT(req_stage < STATE_CHANGE_STAGE_MAX);

    bool b_op_res = false;

    cubeadcs_gen2_service_ctx_t service_ctx;

    if ( true == cubeadcs_gen2_get_service_ctx(&service_ctx) )
    {
        switch (service_ctx.current_system_state.sys_state_core_cfg.cntrl_mode)
        {
        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_XYZWHEEL:

            b_op_res = fs_cubeadcs_gen2_state_change_ref_params_check_rpy(service_ctx.current_system_state.ref_params, req_stage);

            break;

        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_TGT_TRACK:
        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_TGT_STEER:
        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_GND_TRACK:
        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YAW_TARGET:
        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_ROLL_TARGET:
        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YAW_TARGET_BEST:

            b_op_res = fs_cubeadcs_gen2_state_change_ref_params_check_coord(service_ctx.current_system_state.ref_params, req_stage);

            break;

        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_IRC_TRACK:

            b_op_res = fs_cubeadcs_gen2_state_change_ref_params_check_eci(service_ctx.current_system_state.ref_params, req_stage);

            break;

        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_HXYZ_RW:

            b_op_res = fs_cubeadcs_gen2_state_change_ref_params_check_open_loop_rw(service_ctx.current_system_state.ref_params, req_stage);

            break;

        case TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_USER:

            b_op_res = false;

            break;

        default:

            b_op_res = true;

            break;
        }
    }

    return b_op_res;
}

/** @brief Check the ADCS commanded RPY angles against the current request
 *
 *  @retval true - On success
 *  @retval false - On failure
 *
 *  @note We are intentionally skipping float checks (comparisons) here
 */
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_rpy(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage)
{
    bool b_op_res = false;

    TctlmCubeComputerControlProgram8_ReferenceCommands set_ref_commands = {
            .cmdRpyRoll = 0.0F, .cmdRpyPitch = 0.0F, .cmdRpyYaw = 0.0F,
            .cmdTargetLatitude = 0.0F, .cmdTargetLongitude = 0.0F, .cmdTargetAltitude = 0.0F,
            .cmdEciVecX = 0.0F, .cmdEciVecY = 0.0F, .cmdEciVecZ = 0.0F };

    if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommandsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
    {
        if ( STATE_CHANGE_STAGE_SET == req_stage)
        {
            set_ref_commands.cmdRpyRoll = req_ref_params.ref_param_1;
            set_ref_commands.cmdRpyPitch = req_ref_params.ref_param_2;
            set_ref_commands.cmdRpyYaw = req_ref_params.ref_param_3;

            if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommandsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
            {
                b_op_res = true;
            }
        }
        else
        {
            b_op_res = true;
        }
    }

    return b_op_res;
}

/** @brief Check the ADCS commanded Lat, Lon and Alt against the current request
 *
 *  @retval true - On success
 *  @retval false - On failure
 *
 *  @note We are intentionally skipping float checks (comparisons) here
 */
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_coord(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage)
{
    bool b_op_res = false;

    TctlmCubeComputerControlProgram8_ReferenceCommands set_ref_commands = {
            .cmdRpyRoll = 0.0F, .cmdRpyPitch = 0.0F, .cmdRpyYaw = 0.0F,
            .cmdTargetLatitude = 0.0F, .cmdTargetLongitude = 0.0F, .cmdTargetAltitude = 0.0F,
            .cmdEciVecX = 0.0F, .cmdEciVecY = 0.0F, .cmdEciVecZ = 0.0F };

    if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommandsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
    {
        if ( STATE_CHANGE_STAGE_SET == req_stage)
        {
            set_ref_commands.cmdTargetLatitude = req_ref_params.ref_param_1;
            set_ref_commands.cmdTargetLongitude = req_ref_params.ref_param_2;
            set_ref_commands.cmdTargetAltitude = req_ref_params.ref_param_3;

            if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommandsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
            {
                b_op_res = true;
            }
        }
        else
        {
            b_op_res = true;
        }
    }

    return b_op_res;
}

/** @brief Check the ADCS commanded ECI coords against the current request
 *
 *  @retval true - On success
 *  @retval false - On failure
 *
 *  @note We are intentionally skipping float checks (comparisons) here
 */
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_eci(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage)
{
    bool b_op_res = false;

    TctlmCubeComputerControlProgram8_ReferenceCommands set_ref_commands = {
            .cmdRpyRoll = 0.0F, .cmdRpyPitch = 0.0F, .cmdRpyYaw = 0.0F,
            .cmdTargetLatitude = 0.0F, .cmdTargetLongitude = 0.0F, .cmdTargetAltitude = 0.0F,
            .cmdEciVecX = 0.0F, .cmdEciVecY = 0.0F, .cmdEciVecZ = 0.0F };

    if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommandsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
    {
        if ( STATE_CHANGE_STAGE_SET == req_stage)
        {
            set_ref_commands.cmdEciVecX = req_ref_params.ref_param_1;
            set_ref_commands.cmdEciVecY = req_ref_params.ref_param_2;
            set_ref_commands.cmdEciVecZ = req_ref_params.ref_param_3;

            if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommandsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
            {
                b_op_res = true;
            }
        }
        else
        {
            b_op_res = true;
        }
    }

    return b_op_res;
}

/** @brief Check the ADCS commanded open loop commanded momentum vector against the current request
 *
 *  @retval true - On success
 *  @retval false - On failure
 *
 *  @note We are intentionally skipping float checks (comparisons) here
 */
STATIC bool fs_cubeadcs_gen2_state_change_ref_params_check_open_loop_rw(const cubeadcs_gen2_ref_params_t req_ref_params, const state_change_stages_t req_stage)
{
    bool b_op_res = false;

    TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW set_ref_commands = {.hx = 0.0F, .hy = 0.0F, .hz = 0.0F};

    if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandHxyzRWRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
    {
        if ( STATE_CHANGE_STAGE_SET == req_stage)
        {
            set_ref_commands.hx = req_ref_params.ref_param_1;
            set_ref_commands.hy = req_ref_params.ref_param_2;
            set_ref_commands.hz = req_ref_params.ref_param_3;

            if ( CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandHxyzRWRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &set_ref_commands, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT))
            {
                b_op_res = true;
            }
        }
        else
        {
            b_op_res = true;
        }
    }

    return b_op_res;
}

/* ******************************************************************************************* */
