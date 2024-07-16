/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup app_conops
 * @{
 *
 * @file conops.c
 * @brief Concept of Operations source file
 *
 * @}
 *
 */

#if defined(OPMODES_ENABLED)

#include "conops.h"
#include "conops_periodic_ev_task.h"

#include "aocs_cntrl.h"

#include "if_sys_conf.h"
#include "TaskMonitor.h"
#include "assertions.h"
#include "es_exeh.h"
#include "nvm/inc/nvm.h"

#include "string.h"
/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_CON_OPS)

#define CONOPS_DEFAULT_MULT			(1000U)

#define CONOPS_ADCS_NO_ERR_MASK             (0x0000)
#define CONOPS_ADCS_ERR_FLAG_NORMAL_MASK    (0x010F)
#define CONOPS_ADCS_ERR_FLAG_DETUMB_MASK    (0x010F)

// Only used for cube adcs
#define CONOPS_CUBE_ADCS_ERR_FLAG_NORMAL_MASK   (0x010F) /* Node, Range, Rate Sensor, Mtm and SysStateChg errors */
#define CONOPS_CUBE_ADCS_ERR_FLAG_DETUMB_MASK   (0x0109) /* Node, Mtm and SysStateChg errors */

/* If in Y-Thomson, the X and Z should be contained within +1:-1 range */ //todo - move this to the configuration
#define CONOPS_ADCS_Y_THOMSON_POS_THRESH_MRAD_S	 ((int16_t)0x0011)	/* ~ 1 deg/s, or 17 mRad/s */
#define CONOPS_ADCS_Y_THOMSON_NEG_THRESH_MRAD_S  ((int16_t)0xFFEF)	/* ~ -1 deg/s, or -17 mRad/s */

#define CONOPS_3AXIS_CHECK_OK	((uint8_t)0x03)
#define CONOPS_ADCS_T_YHOMSON_STABLE_VERIFIED	 ((uint8_t)0x03)



/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/
// Exceptions
typedef enum
{
    //Runtime error -
    eConOpsException_Runtime_Error,
} eConOpsException_t;

typedef enum {
    eCMPTYPE_ABOVE	= 0,
    eCMPTPYE_BELOW  = 255,
} eConOps_cmp_type_t;

/** @brief XYZ axis values in the data arrays
 *
 */
enum {
    X = 0,
    Y = 1,
    Z = 2
};

typedef struct {
    int32_t X;
    int32_t Y;
    int32_t Z;

} sConOps_3axis_vec_t;

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

/* Mutex control to ConOps SM event trigger */
static osMutexId_t conops_ev_mutex;

static const osMutexAttr_t conops_ev_mutex_attr = {
  "ConOpsEventTriggerMutex",                    // human readable mutex name
  osMutexRecursive | osMutexPrioInherit,        // attr_bits
  NULL,                                         // memory for control block
  0U                                            // size for control block
};

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/

STATIC ConOpsConfig_t 		sConOps_thresh_cfg;
STATIC conops_idle_pointreq_cfg_t sConOps_Idle_cfg;
/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
STATIC void fs_conops_ev_mutex_init(void);
STATIC bool fs_conops_cmp_cbatt(CONOPS_ThresholdValueTypes_t eThreshValType, uint8_t u8PayNum, eConOps_cmp_type_t eCmpType);
STATIC bool fs_conops_chk_raised_adcs_err_flags(uint32_t u32ErrFlags);
STATIC bool fs_conops_chk_stable_y_thomson(const sConOps_3axis_vec_t *psAngRateVec);

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void conops_init(void)
{
    fs_conops_ev_mutex_init();
    conops_p_ev_init();

    conops_trigger_hsm(eHSM_StdEvent_Reset, NULL);

    Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_CONFIG, &sConOps_thresh_cfg);
    Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_IDLE_CONFIG, &sConOps_Idle_cfg);

    conops_payload_register_callback();
}

void conops_trigger_hsm(const uint32_t event_id, const sConOps_pay_cfg_t *const pay_cfg)
{
    sConOps_event_t trigger_event;

    osMutexAcquire(conops_ev_mutex, osWaitForever);

    trigger_event.event_id.id = event_id;

    if ( NULL != pay_cfg )
    {
        memcpy(&trigger_event.event_data, pay_cfg, sizeof(sConOps_pay_cfg_t));
    }
    else
    {
        memset(&trigger_event.event_data, 0, sizeof(sConOps_pay_cfg_t));
    }

    (void)CONOPS_TRIGGER_HSM(&trigger_event.event_id);

    osMutexRelease(conops_ev_mutex);
}

void conops_get_hsm_active_state(uint8_t *u8StateCache)
{
    CRIT_ASSERT(NULL != u8StateCache);

    *u8StateCache = CONOPS_GET_HSM_ACTIVE_STATE()->state_id;
}

bool conops_set_thresh_val(int32_t const * const p_thres_val, uint8_t index,
                           CONOPS_ThresholdValueTypes_t thres_type)
{
    CRIT_ASSERT(NULL != p_thres_val);

    // Return true unless an error is detected
    bool bRes = true;

    switch (thres_type)
    {
        case CONOPS_THRESHOLDVALUETYPES_CBATT_SAFE:
            sConOps_thresh_cfg.cfg.i32CBattSafe = *p_thres_val;
            break;
        case CONOPS_THRESHOLDVALUETYPES_S_SAFE:
            sConOps_thresh_cfg.cfg.i32SSafe = *p_thres_val;
            break;
        case CONOPS_THRESHOLDVALUETYPES_S_DET:
            sConOps_thresh_cfg.cfg.i32SDet = *p_thres_val;
            break;
        case CONOPS_THRESHOLDVALUETYPES_S_PAY:
            if (index >= CDEF_ELEMENT_COUNT(sConOps_thresh_cfg.cfg.ai32SPay))
            {
                bRes = false;
            }
            else
            {
                sConOps_thresh_cfg.cfg.ai32SPay[index] = *p_thres_val;
            }
            break;
        case CONOPS_THRESHOLDVALUETYPES_ANGVEL_MAX:
            sConOps_thresh_cfg.cfg.i32AngVelMax = *p_thres_val;
            break;
        case CONOPS_THRESHOLDVALUETYPES_ANGVEL_MIN:
            sConOps_thresh_cfg.cfg.i32AngVelLow = *p_thres_val;
            break;
        case CONOPS_THRESHOLDVALUETYPES_ANGVEL_RANGE:
            if (index >= CDEF_ELEMENT_COUNT(sConOps_thresh_cfg.cfg.ai32AngVelRange))
            {
                bRes = false;
            }
            else
            {
                sConOps_thresh_cfg.cfg.ai32AngVelRange[index] = *p_thres_val;
            }
            break;
        default:
            EXEH_HANDLE(eEXEHSeverity_Error, (int32_t)eConOpsException_Runtime_Error);

            bRes = false;
            break;
    }

    if (true == bRes)
    {
        Nvm_SetBlockById(NVM_APP_BLOCK_CONOPS_CONFIG, &sConOps_thresh_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);
        Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_CONFIG, &sConOps_thresh_cfg);
    }

    return bRes;
}

bool conops_get_thresh_val(int32_t * p_thres_val, uint8_t index,
                           CONOPS_ThresholdValueTypes_t thres_type)
{
    CRIT_ASSERT(NULL != p_thres_val);

    // Return true unless an error is detected
    bool bRes = true;

    switch (thres_type)
    {
        case CONOPS_THRESHOLDVALUETYPES_CBATT_SAFE:
            *p_thres_val = sConOps_thresh_cfg.cfg.i32CBattSafe;
            break;
        case CONOPS_THRESHOLDVALUETYPES_S_SAFE:
            *p_thres_val = sConOps_thresh_cfg.cfg.i32SSafe;
            break;
        case CONOPS_THRESHOLDVALUETYPES_S_DET:
            *p_thres_val = sConOps_thresh_cfg.cfg.i32SDet;
            break;
        case CONOPS_THRESHOLDVALUETYPES_S_PAY:
            if (index >= CDEF_ELEMENT_COUNT(sConOps_thresh_cfg.cfg.ai32SPay))
            {
                bRes = false;
            }
            else
            {
                *p_thres_val = sConOps_thresh_cfg.cfg.ai32SPay[index];
            }
            break;
        case CONOPS_THRESHOLDVALUETYPES_ANGVEL_MAX:
            *p_thres_val = sConOps_thresh_cfg.cfg.i32AngVelMax;
            break;
        case CONOPS_THRESHOLDVALUETYPES_ANGVEL_MIN:
            *p_thres_val = sConOps_thresh_cfg.cfg.i32AngVelLow;
            break;
        case CONOPS_THRESHOLDVALUETYPES_ANGVEL_RANGE:
            if (index >= CDEF_ELEMENT_COUNT(sConOps_thresh_cfg.cfg.ai32AngVelRange))
            {
                bRes = false;
            }
            else
            {
                *p_thres_val = sConOps_thresh_cfg.cfg.ai32AngVelRange[index];
            }
            break;
        case CONOPS_THRESHOLDVALUETYPES_DEFAULT:
            *p_thres_val = (int32_t) CONOPS_DEFAULT_MULT;
            break;
        default:
            EXEH_HANDLE(eEXEHSeverity_Error, (int32_t)eConOpsException_Runtime_Error);
            bRes = false;
            break;
    }

    return bRes;
}

bool conops_set_all_thresh_val(CONOPS_ThresholdValues_t const * const p_conops_config)
{
    CRIT_ASSERT(NULL != p_conops_config);

    // Return true unless an error is detected
    bool bRes = true;

    // Update the runtime values structure
    memcpy(&sConOps_thresh_cfg, p_conops_config, sizeof(CONOPS_ThresholdValues_t));

    // Update the nvm
    Nvm_SetBlockById(NVM_APP_BLOCK_CONOPS_CONFIG, &sConOps_thresh_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);
    Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_CONFIG, &sConOps_thresh_cfg);

    return bRes;

}

bool conops_get_all_thresh_val(CONOPS_ThresholdValues_t * p_conops_config)
{
    CRIT_ASSERT(NULL != p_conops_config);

    // Return true unless an error is detected
    bool bRes = true;

    // Copy only the size of the data, excluding the CRC
    memcpy(p_conops_config, &sConOps_thresh_cfg, sizeof(CONOPS_ThresholdValues_t));

    return bRes;
}

void conops_set_logical_flag_value(eConOps_logical_flag_types_t eFlagType, bool bFlagVal)
{
    DATA_CACHE_ConOpsFlags_t dc_flags_data;

    dc_get_conopsflags_data(&dc_flags_data);

    switch (eFlagType)
    {
    case eFLAG_PAYLOAD_ERR:
        dc_flags_data.bPAY_ERR = bFlagVal;
        break;
    case eFLAG_ADCS_ERR:
        dc_flags_data.bADCS_ERR = bFlagVal;
        break;
    case eFLAG_DETUMB_COMPLETED:
        dc_flags_data.bDETUMB_COMPLETED = bFlagVal;
        break;
    default:
        break;
    }

    CONOPS_TRACE_DBG("%s: conops_set_logical_flag_value: %d:%d\r", CONOPS_SM_LOGIC_COND, eFlagType, bFlagVal);

    dc_set_conopsflags_data(&dc_flags_data);
}

bool conops_get_logical_flag(eConOps_logical_flag_types_t eFlagType)
{
    bool bFlag = false;

    DATA_CACHE_ConOpsFlags_t dc_flags_data;

    dc_get_conopsflags_data(&dc_flags_data);

    switch (eFlagType)
    {
    case eFLAG_PAYLOAD_ERR:
        bFlag = dc_flags_data.bPAY_ERR;
        break;
    case eFLAG_ADCS_ERR:
        bFlag = dc_flags_data.bADCS_ERR;
        break;
    case eFLAG_DETUMB_COMPLETED:
        bFlag = dc_flags_data.bDETUMB_COMPLETED;
        break;
    default:
        break;
    }

    CONOPS_TRACE_DBG("%s: conops_get_logical_flag: %d:%d\r", CONOPS_SM_LOGIC_COND, eFlagType, bFlag);

    conops_set_logical_flag_value(eFlagType, false);

    return bFlag;
}

bool conops_is_cbatt_above(CONOPS_ThresholdValueTypes_t eThreshValType, uint8_t u8PayNum)
{
    return fs_conops_cmp_cbatt(eThreshValType, u8PayNum, eCMPTYPE_ABOVE);
}

bool conops_is_cbatt_below(CONOPS_ThresholdValueTypes_t eThreshValType, uint8_t u8PayNum)
{
    return fs_conops_cmp_cbatt(eThreshValType, u8PayNum, eCMPTPYE_BELOW);
}

bool conops_is_omega_above_thresh(const aocs_cntrl_sys_state_types_t aocs_state)
{
    bool bRes;

    int32_t i32OmegaThresh;
    DATA_CACHE_AOCS_CNTRL_TLM_t sADCSData;

    bRes = false;

    if ( aocs_state > AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING )
    {
        return false;
    }

    if ( true != conops_get_thresh_val(&i32OmegaThresh, 0, CONOPS_THRESHOLDVALUETYPES_ANGVEL_MAX ) )
    {
        return false;
    }

    if ( DC_DATA_STATUS_OK == dc_get_aocs_cntrl_tlm_data(&sADCSData) )
    {
        if ( (AOCS_CNTRL_SYS_STATE_Y_THOMSON == aocs_state) || (AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE == aocs_state) )
        {
            sConOps_3axis_vec_t sAngRateVecTmp;

            sAngRateVecTmp.X = sADCSData.ai32EstAngRateVec[0];
            sAngRateVecTmp.Y = sADCSData.ai32EstAngRateVec[1];
            sAngRateVecTmp.Z = sADCSData.ai32EstAngRateVec[2];

            if ( false == fs_conops_chk_stable_y_thomson(&sAngRateVecTmp) )
            {
                bRes = true;
            }
        }
        else if ( sADCSData.i32EstAngRateNorm > i32OmegaThresh )
        {
            bRes = true;
        }
        else
        {
            bRes = false;
        }
    }

    CONOPS_TRACE_DBG("%s: conops_is_omega_above_thresh: %d\r", CONOPS_SM_TEST_COND, bRes);

    return bRes;
}

bool conops_is_error_flag_raised(void)
{
    bool bRes;

    DATA_CACHE_AOCS_CNTRL_TLM_t sADCSData;

    bRes = false;

    if ( DC_DATA_STATUS_OK == dc_get_aocs_cntrl_tlm_data(&sADCSData) ) {
            bRes = fs_conops_chk_raised_adcs_err_flags(sADCSData.u32AdcsErrFlags);
    }

    if ( false == bRes) {
        bRes = conops_get_logical_flag(eFLAG_ADCS_ERR);
    }

    CONOPS_TRACE_DBG("%s: conops_is_error_flag_raised: %d\r", CONOPS_SM_TEST_COND, bRes);

    return bRes;
}

bool conops_is_fast_detumb_activated(void)
{
    bool bRes = false;

    aocs_cntrl_sys_state_types_t aocs_state;
    aocs_cntrl_sys_state_req_state_t aocs_state_req_state;

    if ( conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state) &&
         (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == aocs_state_req_state) )
    {
        switch (aocs_state)
        {
        case AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING:
        case AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING:
            bRes = true;
            break;
        default:
            break;
        }
    }
    CONOPS_TRACE_DBG("%s: conops_is_fast_detumb_activated: %d\r", CONOPS_SM_TEST_COND, bRes);

    return bRes;
}

bool conops_is_detumb_completed(void)
{
    bool bRes = false;

    DATA_CACHE_AOCS_CNTRL_TLM_t sADCSData;

    if ( DC_DATA_STATUS_OK != dc_get_aocs_cntrl_tlm_data(&sADCSData) )
    {
        return bRes;
    }

    aocs_cntrl_sys_state_types_t aocs_state;
    aocs_cntrl_sys_state_req_state_t aocs_state_req_state;

    if ( conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state) &&
         (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == aocs_state_req_state) )
    {
        if ( AOCS_CNTRL_SYS_STATE_Y_THOMSON == aocs_state )
        {
            sConOps_3axis_vec_t sAngRateVecTmp;

            sAngRateVecTmp.X = sADCSData.ai32EstAngRateVec[0];
            sAngRateVecTmp.Y = sADCSData.ai32EstAngRateVec[1];
            sAngRateVecTmp.Z = sADCSData.ai32EstAngRateVec[2];

            bRes = fs_conops_chk_stable_y_thomson(&sAngRateVecTmp);
        }
        else
        {
            int32_t i32OmegaThresh;

            if ( true != conops_get_thresh_val(&i32OmegaThresh, 0, CONOPS_THRESHOLDVALUETYPES_ANGVEL_MIN ) )
            {
                return bRes;
            }

            if ( i32OmegaThresh > sADCSData.i32EstAngRateNorm )
            {
                bRes = true;
            }
        }

        if ( true == bRes)
        {
            conops_set_logical_flag_value(eFLAG_DETUMB_COMPLETED, true);
        }
    }

    CONOPS_TRACE_DBG("%s: conops_is_detumb_completed: %d\r", CONOPS_SM_TEST_COND, bRes);

    return bRes;
}

safe_bool_t conops_set_enable_sun_tracking_flag(safe_bool_t bValue)
{
    conops_idle_pointreq_cfg_t sIdle_cfg;

    if ( IS_TRUE(bValue) ) {
        SET_TRUE(sIdle_cfg.en_sun_tracking)
    } else if ( IS_FALSE(bValue) ) {
        SET_FALSE(sIdle_cfg.en_sun_tracking)
    }
    else {
        return SAFE_FALSE;
    }

    Nvm_SetBlockById(NVM_APP_BLOCK_CONOPS_IDLE_CONFIG, &sIdle_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);
    Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_IDLE_CONFIG, &sConOps_Idle_cfg);

    return SAFE_TRUE;
}

bool conops_get_enable_sun_tracking_flag(void)
{
    Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_IDLE_CONFIG, &sConOps_Idle_cfg);

    if ( IS_TRUE(sConOps_Idle_cfg.en_sun_tracking) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void conops_refresh_runtime_nvm_copies(void)
{
    Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_CONFIG, &sConOps_thresh_cfg);
    Nvm_GetBlockById(NVM_APP_BLOCK_CONOPS_IDLE_CONFIG, &sConOps_Idle_cfg);
}

bool conops_is_3axis_allowed(void)
{
    bool bRes;

    DATA_CACHE_AOCS_CNTRL_TLM_t sAdcsData;
    uint8_t u8Chk = 0;

    bRes = false;

    if ( DC_DATA_STATUS_OK == dc_get_aocs_cntrl_tlm_data(&sAdcsData) )
    {
        if ( (CONOPS_3AXIS_CONTROL_ANG_VEL_SAFETY_THRESH >= sAdcsData.ai32EstAngRateVec[X]) && (-CONOPS_3AXIS_CONTROL_ANG_VEL_SAFETY_THRESH <= sAdcsData.ai32EstAngRateVec[X]) )
        {
            ++u8Chk;
        }

        if ( (CONOPS_3AXIS_CONTROL_ANG_VEL_SAFETY_THRESH >= sAdcsData.ai32EstAngRateVec[Y]) && (-CONOPS_3AXIS_CONTROL_ANG_VEL_SAFETY_THRESH <= sAdcsData.ai32EstAngRateVec[Y]) )
        {
            ++u8Chk;
        }

        if ( (CONOPS_3AXIS_CONTROL_ANG_VEL_SAFETY_THRESH >= sAdcsData.ai32EstAngRateVec[Z]) && (-CONOPS_3AXIS_CONTROL_ANG_VEL_SAFETY_THRESH <= sAdcsData.ai32EstAngRateVec[Z]) )
        {
            ++u8Chk;
        }

        if ( CONOPS_3AXIS_CHECK_OK == u8Chk)
        {
            bRes = true;
        }
    }

    return bRes;
}

bool conops_get_aocs_sys_state(aocs_cntrl_sys_state_types_t *sys_state, aocs_cntrl_sys_state_req_state_t *sys_state_req_state)
{
    return aocs_cntrl_get_aocs_state(sys_state, sys_state_req_state);
}

void conops_set_aocs_sys_state(aocs_cntrl_sys_state_types_t sys_state, const aocs_cntrl_reference_params_t * const p_ref_params)
{
    aocs_cntrl_request_aocs_state(sys_state, p_ref_params);
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/*!
*********************************************************************************************
* @brief Initialises the ConOps event control mutex
*********************************************************************************************
*/

/**
 * @brief Create the event trigger mutex
 */
STATIC void fs_conops_ev_mutex_init(void)
{
    conops_ev_mutex = osMutexNew(&conops_ev_mutex_attr);
}

/**
 * @brief Compare battery capacity with threshold
 *
 * @param[in] CONOPS_ThresholdValueTypes_t eThreshValType - threshold value type
 * @param[in] uint8_t u8PayNum - payload number
 * @param[im] eConOps_cmp_type_t eCmpType - type of comparison, battery above or battery below
 *
 * @return bool
 *
 * @note This function compares the last measured battery capacity to a threshold
 * 		 formulated from the threshold configuration (CbattSafe * (u8PayNum_multiplier))
 */
STATIC bool fs_conops_cmp_cbatt(CONOPS_ThresholdValueTypes_t eThreshValType, uint8_t u8PayNum, eConOps_cmp_type_t eCmpType)
{
    bool bRes;

    int32_t i32CSafe;
    int32_t i32Mult;

    DATA_CACHE_EpsOverallBatteryInfoType_t sEPS_Data;

    bRes = false;

    if ( (true != conops_get_thresh_val(&i32CSafe, 0, CONOPS_THRESHOLDVALUETYPES_CBATT_SAFE )) ||
         (true != conops_get_thresh_val(&i32Mult, u8PayNum, eThreshValType)) )
    {
        return bRes;
    }

    if ( DC_DATA_STATUS_OK == dc_get_epsoverallbatteryinfo_data(&sEPS_Data) ) {
        switch (eCmpType) {
        case eCMPTYPE_ABOVE:
            if ( sEPS_Data.u32Capacity > (((uint32_t)i32CSafe * i32Mult) / 1000) )
            {
                bRes = true;
            }
            break;
        case eCMPTPYE_BELOW:
            if ( sEPS_Data.u32Capacity < (((uint32_t)i32CSafe * i32Mult) / 1000) )
            {
                bRes = true;
            }
            break;
        default:
            EXEH_HANDLE(eEXEHSeverity_Error,
                    (int32_t) eConOpsException_Runtime_Error);
            break;
        }

    }

    CONOPS_TRACE_DBG("%s: fs_conops_cmp_cbatt: %d\r", CONOPS_SM_TEST_COND, bRes);

    return bRes;
}

/**
 * @brief Check if the adcs internally raised flags should be evaluated by the conops logic
 *
 * @param[in] uint32_t u32ErrFlags - the internal adcs error flags
 *
 * @return bool
 *
 */
STATIC bool fs_conops_chk_raised_adcs_err_flags(uint32_t u32ErrFlags)
{
    bool bRes = false;

    TODO(Dependence on the system type and AOCS type not considered! This needs to be fix at next iteration.)

    if ( CONOPS_ADCS_NO_ERR_MASK != u32ErrFlags )
    {
        bRes = true;
    }

    return bRes;
}

/**
 * @brief Check if we are in a stable Y-Thomson mode
 *
 * @param[in] sConOps_3axis_vec_t *psAngRateVec - angular rate in milli-radians per second
 *
 * @return bool
 *
 */
STATIC bool fs_conops_chk_stable_y_thomson(const sConOps_3axis_vec_t *psAngRateVec)
{
    bool bRes;

    bRes = false;

    int32_t i32OmegaLowThresh;
    int32_t i32OmegaHighThresh;

    if ( true == conops_get_thresh_val(&i32OmegaLowThresh, 0, CONOPS_THRESHOLDVALUETYPES_ANGVEL_RANGE ) )
    {
        if ( true == conops_get_thresh_val(&i32OmegaHighThresh, 1, CONOPS_THRESHOLDVALUETYPES_ANGVEL_RANGE ) )
        {
            bRes = true;
        }
    }

    if ( true == bRes ) {
        uint8_t u8ChkCnt = 0;

        if ( (i32OmegaLowThresh < psAngRateVec->Y) && (psAngRateVec->Y < i32OmegaHighThresh) )
        {
            ++u8ChkCnt;
        }

        if ( (CONOPS_ADCS_Y_THOMSON_POS_THRESH_MRAD_S > psAngRateVec->X) && (psAngRateVec->X > CONOPS_ADCS_Y_THOMSON_NEG_THRESH_MRAD_S) )
        {
            ++u8ChkCnt;
        }

        if ( (CONOPS_ADCS_Y_THOMSON_POS_THRESH_MRAD_S > psAngRateVec->Z) && (psAngRateVec->Z > CONOPS_ADCS_Y_THOMSON_NEG_THRESH_MRAD_S) )
        {
            ++u8ChkCnt;
        }

        if ( CONOPS_ADCS_T_YHOMSON_STABLE_VERIFIED == u8ChkCnt)
        {
            bRes = true;
        }
        else
        {
            bRes = false;
        }
    }

    return bRes;
}

#endif /* OPMODES_ENABLED */
/* ******************************************************************************************* */
