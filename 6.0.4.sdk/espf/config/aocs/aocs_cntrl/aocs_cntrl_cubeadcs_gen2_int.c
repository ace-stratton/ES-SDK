/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_cntrl_cubeadcs_gen2_int.c
 * @brief    Attitude and Orbit Control System CubeADCS Gen2 integration source
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include <math.h>
#include "assertions.h"
#include "es_cdef.h"
#include "datacache.h"
#include "aocs_cntrl_cubeadcs_gen2_int.h"
#include "aocs_pm_cfg.h"
#include "cubeadcs_gen2.h"
#include "cubeadcs_gen2_gw.h"
#include "cubeadcs_gen2_sm_user.h"
#include "cubeadcs_gen2_fdir.h"
#include "nvm.h"
#include "fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ProtocolTypes.h"


/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
#define UNIT2MUNIT(X) (X*1000)
#define DEGREE2RADIAN(X) (X*M_PI/180.0)
/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_sys_state_chng_req(const aocs_cntrl_sys_state_types_t sys_state,
                                                                           const aocs_cntrl_reference_params_t * const p_ref_params);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_sys_state_get_req_state(aocs_cntrl_sys_state_types_t *p_sys_state,
                                                                                aocs_cntrl_sys_state_req_state_t *p_sys_state_req_state);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_aocs_system_errors(aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_est_ang_rates(aocs_cntrl_est_ang_rate_t *p_est_ang_rates,
                                                                          aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_est_att_ang(aocs_cntrl_est_att_t *p_est_att_ang);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_meas_wheel_speed(aocs_cntrl_wheel_speed_t *p_meas_wheel_speed);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_log_data(aocs_cntrl_log_data_t *p_log_data,
                                                                     aocs_log_data_types_t data_type,
                                                                     aocs_cntrl_offset_t* offset_values);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_cms_status(uint8_t * const p_cms_status);
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_cntrl_status(bool * const p_cntrl_status);
static aocs_cntrl_sys_state_req_state_t fs_aocs_cntrl_cubeadcs_gen2_get_aocs_change_status(const cubeadcs_gen2_sys_state_change_status_t state_change_status);

static int16_t fs_aocs_cntrl_cubeadcs_gen2_int_select_wheel_speed(const TctlmCommonFrameworkEnums_NodeType wheel_type,
                                                                  const ErrorCode err_meas_cube,
                                                                  const ErrorCode err_meas_nss,
                                                                  const Boolean cube_valid,
                                                                  const Boolean nss_valid,
                                                                  const F32 speed_cube,
                                                                  const F32 speed_nss);
/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/
aocs_cntrl_t aocs_cntrl_cubeadcs_gen2_int =
{
        .p_sys_state_chng_req      = fs_aocs_cntrl_cubeadcs_gen2_int_sys_state_chng_req,
        .p_sys_state_get_req_state = fs_aocs_cntrl_cubeadcs_gen2_int_sys_state_get_req_state,
        .p_get_aocs_system_errors = fs_aocs_cntrl_cubeadcs_gen2_int_get_aocs_system_errors,
        .p_get_est_ang_rates = fs_aocs_cntrl_cubeadcs_gen2_int_get_est_ang_rates,
        .p_get_est_att_ang = fs_aocs_cntrl_cubeadcs_gen2_int_get_est_att_ang,
        .p_get_meas_wheel_speed = fs_aocs_cntrl_cubeadcs_gen2_int_get_meas_wheel_speed,
        .p_get_log_data = fs_aocs_cntrl_cubeadcs_gen2_int_get_log_data,
        .p_get_cms_status = fs_aocs_cntrl_cubeadcs_gen2_int_get_cms_status,
        .p_get_cntrl_status = fs_aocs_cntrl_cubeadcs_gen2_int_get_cntrl_status
};

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/


/*
 *********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/* @brief Request a new system state change to the Gen2 CubeADCS
 *
 * @param[in] aocs_cntrl_sys_state_types_t sys_state - the new system state
 * @param[in] aocs_cntrl_reference_params_t p_ref_params - reference parameters for some ADCS control modes
 *
 * @return status after performing the request
 *
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_sys_state_chng_req(const aocs_cntrl_sys_state_types_t sys_state,
                                                                           const aocs_cntrl_reference_params_t * const p_ref_params)
{
    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;
    cubeadcs_gen2_service_ctx_t adcs_ctx;
    cubeadcs_gen2_sys_states_cfg_t sys_state_nvm_cfg;
    uint8_t nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_MAX_CNT;

    if ( true == cubeadcs_gen2_get_service_ctx(&adcs_ctx) )
    {
        Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_GEN2_SYS_STATE_CFG, (void *)&sys_state_nvm_cfg);

        sm_event_ctx_t sm_evt_ctx;
        cubeadcs_gen2_sys_state_t * const p_new_adcs_state = &sm_evt_ctx.sys_state;

        static_assert(sizeof(p_new_adcs_state->req_state_id) == sizeof(sys_state));

        p_new_adcs_state->req_state_id = (uint8_t)sys_state;

        if (NULL != p_ref_params)
        {
            p_new_adcs_state->ref_params.ref_param_1 = p_ref_params->ref_param_1;
            p_new_adcs_state->ref_params.ref_param_2 = p_ref_params->ref_param_2;
            p_new_adcs_state->ref_params.ref_param_3 = p_ref_params->ref_param_3;
        }
        else
        {
            p_new_adcs_state->ref_params.ref_param_1 = 0.0f;
            p_new_adcs_state->ref_params.ref_param_2 = 0.0f;
            p_new_adcs_state->ref_params.ref_param_3 = 0.0f;
        }

        switch (sys_state)
        {
        case AOCS_CNTRL_SYS_STATE_NO_CONTROL:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_NO_CONTROL;
            break;
        case AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_NORMAL_DETUMBLING;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_THOMSON:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_Y_THOMSON;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_Y_THOMSON_MEMS_RATE;
            break;
        case AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_FAST_DETUMBLING;
            break;
        case AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_VERY_FAST_DETUMBLING;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_MOMENTUM:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_Y_MOMENTUM;
            break;
        case AOCS_CNTRL_SYS_STATE_Y_MOMENTUM_FULL_STATE_EKF:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_Y_MOMENTUM_FULL_STATE_EKF;
            break;
        case AOCS_CNTRL_SYS_STATE_3AXIS:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_THREE_AXIS;
            break;
        case AOCS_CNTRL_SYS_STATE_SUN_TRACKING:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_SUN_TRACKING;
            break;
        case AOCS_CNTRL_SYS_STATE_TARGET_TRACKING:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_TARGET_TRACKING;
            break;
        case AOCS_CNTRL_SYS_STATE_USER1:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_USER1;
            break;
        case AOCS_CNTRL_SYS_STATE_USER2:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_USER2;
            break;
        case AOCS_CNTRL_SYS_STATE_USER3:
            nvm_state_num = OBC_CUBEADCS_GEN2_SYS_STATES_USER3;
            break;
        default:
            break;
        }

        if ( nvm_state_num < OBC_CUBEADCS_GEN2_SYS_STATES_MAX_CNT)
        {
            p_new_adcs_state->sys_state_core_cfg.cntrl_mode = sys_state_nvm_cfg.sys_state_cfg[nvm_state_num].cntrl_mode;
            p_new_adcs_state->sys_state_core_cfg.est_mode_main = sys_state_nvm_cfg.sys_state_cfg[nvm_state_num].est_mode_main;
            p_new_adcs_state->sys_state_core_cfg.est_mode_backup = sys_state_nvm_cfg.sys_state_cfg[nvm_state_num].est_mode_backup;
            memcpy(&p_new_adcs_state->sys_state_core_cfg.pwr_state, &sys_state_nvm_cfg.sys_state_cfg[nvm_state_num].pwr_state, sizeof(p_new_adcs_state->sys_state_core_cfg.pwr_state));

            if (false != cubeadcs_gen2_trigger_sm(ev_cubeadcs_gen2_sm_request_a_state_change, &sm_evt_ctx))
            {
                op_res = AOCS_CNTRL_OK;
            }
        }
    }

    return op_res;
}

/* @brief Get the last requested system state and its status
 *
 * @param[out] aocs_cntrl_sys_state_types_t *sys_state - pointer to the storage location for the system state
 * @param[out] aocs_cntrl_sys_state_req_state_t *sys_state_req_state - pointer to the storage location for the request state
 *
 * @return status after performing the request
 *
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_sys_state_get_req_state(aocs_cntrl_sys_state_types_t *p_sys_state,
                                                                                aocs_cntrl_sys_state_req_state_t *p_sys_state_req_state)
{
    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

    if ( (NULL != p_sys_state) && (NULL != p_sys_state_req_state) )
    {
        cubeadcs_gen2_service_ctx_t srv_ctx;

        *p_sys_state = AOCS_CNTRL_SYS_NUMBER;
        *p_sys_state_req_state = AOCS_CNTRL_SYS_STATE_STATE_MAX;

        if (false != cubeadcs_gen2_get_service_ctx(&srv_ctx))
        {
            *p_sys_state = srv_ctx.current_system_state.req_state_id;
            *p_sys_state_req_state = fs_aocs_cntrl_cubeadcs_gen2_get_aocs_change_status(srv_ctx.state_change_status);

            op_res = AOCS_CNTRL_OK;
        }
    }
    else
    {
        CRIT_ASSERT(false);
    }

    return op_res;
}

/* @brief Get the Gen2 CubeADCS reported errors
 *
 * @param[out] aocs_cntrl_aocs_sys_errs *p_aocs_sys_errs - pointer to the storage location for the system errors
 *
 * @return status after performing the request
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_aocs_system_errors(aocs_cntrl_aocs_sys_errs * p_aocs_sys_errs)
{
    CRIT_ASSERT(NULL != p_aocs_sys_errs);

    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

    cubeadcs_gen2_fdir_errors_t gen2_errors = (cubeadcs_gen2_fdir_errors_t)0;
    if (false != cubeadcs_gen2_fdir_get_errors(&gen2_errors))
    {
        op_res = AOCS_CNTRL_OK;
    }

    return op_res;
}

/* @brief Get the Gen2 CubeADCS reported estimated angular rates and norm
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *p_est_ang_rates - pointer to the storage location for the estimated angular rates
 * @param[out] aocs_cntrl_est_ang_rate_norm *p_est_ang_rate_norm - pointer to the storage location for the norm
 *
 * @return status after performing the request
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_est_ang_rates(aocs_cntrl_est_ang_rate_t * p_est_ang_rates,
                                                                          aocs_cntrl_est_ang_rate_norm * p_est_ang_rate_norm)
{
    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

    if ( (NULL != p_est_ang_rates) && (NULL != p_est_ang_rate_norm) )
    {
        TODO(Handling of backup estimator)
        TctlmCubeComputerControlProgram8_TlmEstimatorMain est_telemetry;
        const ErrorCode err = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER,
                                                                                                    &est_telemetry,
                                                                                                    CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
        if (CUBEOBC_ERROR_OK == err)
        {
            p_est_ang_rates->X = (int32_t)UNIT2MUNIT(DEGREE2RADIAN(est_telemetry.estRateOrcX));
            p_est_ang_rates->Y = (int32_t)UNIT2MUNIT(DEGREE2RADIAN(est_telemetry.estRateOrcY));
            p_est_ang_rates->Z = (int32_t)UNIT2MUNIT(DEGREE2RADIAN(est_telemetry.estRateOrcZ));

            *p_est_ang_rate_norm = (aocs_cntrl_est_ang_rate_norm)sqrt( (p_est_ang_rates->X * p_est_ang_rates->X) +
                                                                       (p_est_ang_rates->Y * p_est_ang_rates->Y) +
                                                                       (p_est_ang_rates->Z * p_est_ang_rates->Z) );
            op_res = AOCS_CNTRL_OK;
        }
    }
    else
    {
        CRIT_ASSERT(false);
    }

    return op_res;
}

/* @brief Get the Gen2 CubeADCS reported estimated attitude angles
 *
 * @param[out] aocs_cntrl_est_ang_rate_t *p_est_att_ang - pointer to the storage location for the estimated attitude angles
 *
 * @return status after performing the request
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_est_att_ang(aocs_cntrl_est_att_t * p_est_att_ang)
{
    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

    if (NULL != p_est_att_ang)
    {
        TODO(Handling of backup estimator)
        TctlmCubeComputerControlProgram8_TlmEstimatorMain est_telemetry;
        const ErrorCode err = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER,
                                                                                                   &est_telemetry,
                                                                                                   CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
        if (CUBEOBC_ERROR_OK == err)
        {
            p_est_att_ang->roll = (int32_t)UNIT2MUNIT(est_telemetry.estRpyRoll);
            p_est_att_ang->pitch = (int32_t)UNIT2MUNIT(est_telemetry.estRpyPitch);
            p_est_att_ang->yaw = (int32_t)UNIT2MUNIT(est_telemetry.estRpyYaw);

            op_res = AOCS_CNTRL_OK;
        }
    }
    else
    {
        CRIT_ASSERT(false);
    }

    return op_res;
}


/* @brief Returns the speed of a reaction wheel based on the wheel's type and validity
 *
 * @param[in] TctlmCommonFrameworkEnums_NodeType wheel_type - type of the reaction wheel as reported by the Gen2 API
 * @param[in] ErrorCode err_meas_cube - error status of the telemetry read operation for a CubeWheel
 * @param[in] ErrorCode err_meas_nss - error status of the telemetry read operation for an NSS wheel
 * @param[in] Boolean cube_valid - validity flag for the speed value read for a CubeWheel
 * @param[in] Boolean nss_valid - validity flag for the speed value read for an NSS wheel
 * @param[in] F32 speed_cube - speed value [RPM] read for a CubeWheel
 * @param[in] F32 speed_nss - speed value [RPM] read for an NSS wheel
 *
 * @return speed of the reaction wheel in RPM
 */
static int16_t fs_aocs_cntrl_cubeadcs_gen2_int_select_wheel_speed(const TctlmCommonFrameworkEnums_NodeType wheel_type,
                                                                  const ErrorCode err_meas_cube,
                                                                  const ErrorCode err_meas_nss,
                                                                  const Boolean cube_valid,
                                                                  const Boolean nss_valid,
                                                                  const F32 speed_cube,
                                                                  const F32 speed_nss)
{
    int16_t result = 0;

    switch (wheel_type)
    {
    case TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_WHEEL:
        if ( (CUBEOBC_ERROR_OK == err_meas_cube) && (FALSE != cube_valid) )
        {
            result = (int16_t)speed_cube;
        }
        break;

    case TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_NODE_NSSRWL:
        if ( (CUBEOBC_ERROR_OK == err_meas_nss) && (FALSE != nss_valid) )
        {
            result = (int16_t)speed_nss;
        }
        break;

    default:
        break;
    }

    return result;
}

/* @brief Get the Gen2 CubeADCS measured wheel speed
 *
 * @param[out] aocs_cntrl_wheel_speed_t *p_meas_wheel_speed - pointer to the storage location for the measured wheel speed
 *
 * @return status after performing the request
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_meas_wheel_speed(aocs_cntrl_wheel_speed_t * p_meas_wheel_speed)
{
    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

    if (NULL != p_meas_wheel_speed)
    {
        TctlmCubeComputerControlProgram8_TlmSensorRawRwl rwl_meas_cube;
        TctlmCubeComputerControlProgram8_TlmRwlNssRwlRaw rwl_meas_nss;

        const ErrorCode err_meas_cube = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwlRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER,
                                                                                                                     &rwl_meas_cube,
                                                                                                                     CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
        const ErrorCode err_meas_nss = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRawRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER,
                                                                                                         &rwl_meas_nss,
                                                                                                         CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);

        TctlmCommonFrameworkEnums_NodeType wheel_type = cubeadcs_gen2_get_node_type(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_RWL_0);
        p_meas_wheel_speed->rwl0_speed = fs_aocs_cntrl_cubeadcs_gen2_int_select_wheel_speed(wheel_type, err_meas_cube, err_meas_nss,
                                                                                         rwl_meas_cube.rwl0IsValid, rwl_meas_nss.rwl0IsValid,
                                                                                         rwl_meas_cube.rwl0MeasSpeed, rwl_meas_nss.rwl0MeasSpeed);

        wheel_type = cubeadcs_gen2_get_node_type(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_RWL_1);
        p_meas_wheel_speed->rwl1_speed = fs_aocs_cntrl_cubeadcs_gen2_int_select_wheel_speed(wheel_type, err_meas_cube, err_meas_nss,
                                                                                         rwl_meas_cube.rwl1IsValid, rwl_meas_nss.rwl1IsValid,
                                                                                         rwl_meas_cube.rwl1MeasSpeed, rwl_meas_nss.rwl1MeasSpeed);

        wheel_type = cubeadcs_gen2_get_node_type(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_RWL_2);
        p_meas_wheel_speed->rwl2_speed = fs_aocs_cntrl_cubeadcs_gen2_int_select_wheel_speed(wheel_type, err_meas_cube, err_meas_nss,
                                                                                         rwl_meas_cube.rwl2IsValid, rwl_meas_nss.rwl2IsValid,
                                                                                         rwl_meas_cube.rwl2MeasSpeed, rwl_meas_nss.rwl2MeasSpeed);

        wheel_type = cubeadcs_gen2_get_node_type(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_RWL_3);
        p_meas_wheel_speed->rwl3_speed = fs_aocs_cntrl_cubeadcs_gen2_int_select_wheel_speed(wheel_type, err_meas_cube, err_meas_nss,
                                                                                         rwl_meas_cube.rwl3IsValid, rwl_meas_nss.rwl3IsValid,
                                                                                         rwl_meas_cube.rwl3MeasSpeed, rwl_meas_nss.rwl3MeasSpeed);
        op_res = AOCS_CNTRL_OK;
    }

    return op_res;
}

/* @brief Get the corresponding data for logging and offsets. The offset are the commanded
 * angles and it is only for EST_ATT_ANGL, in all other cases they should be 0.
 * @param[out] aocs_cntrl_log_data_t *p_log_data - array of data to be passed to the PM
 * @param[out] aocs_cntrl_offset_t* offset_values - array of offsets to pass to the PM
 * @param[in] aocs_log_data_types_t data_type - what kind of data to get from the datacache
 *
 * @return status after performing the request
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_log_data(aocs_cntrl_log_data_t *p_log_data, aocs_log_data_types_t data_type, aocs_cntrl_offset_t* offset_values)
{
    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

    // TODO: Implement
    (void)data_type;
    (void)p_log_data;
    (void)offset_values;

    return op_res;
}

/* @brief Get the commissioning status of the Gen2 CubeADCS
 * @param[out] uint8_t * p_cms_status - commissioning status
 *
 * @return status after performing the request
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_cms_status(uint8_t * const p_cms_status)
{
    aocs_cntrl_res_t op_res = AOCS_CNTRL_FAILED;

    if (false != cubeadcs_gen2_get_cms_status(p_cms_status))
    {
        op_res = AOCS_CNTRL_OK;
    }

    return op_res;
}

/* @brief Get the presence of a running control algorithm
 * @param[out] bool * p_cntrl_status - true if there is an active control mode, false otherwise
 *
 * @return status after performing the request
 */
static aocs_cntrl_res_t fs_aocs_cntrl_cubeadcs_gen2_int_get_cntrl_status(bool * const p_cntrl_status)
{
    aocs_cntrl_res_t result = AOCS_CNTRL_FAILED;

    if (NULL != p_cntrl_status)
    {
        TctlmCubeComputerControlProgram8_ConMode cntrl_mode;
        ErrorCode err = CubeADCS_Gen2_CubeComputerControlProgram8_getConModeRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER,
                                                                                      &cntrl_mode,
                                                                                      CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
        if (CUBEOBC_ERROR_OK == err)
        {
            *p_cntrl_status = false;
            if (cntrl_mode.controlMode != TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_NONE)
            {
                *p_cntrl_status = true;
            }

            result = AOCS_CNTRL_OK;
        }
    }

    return result;
}

/* @brief Convert enumeration values from cubeadcs_gen2_sys_state_change_status_t to aocs_cntrl_sys_state_req_state_t.
 * @param[out] TctlmCubeComputerCommon3_PowerState * p_power_state - structure representing the power state.
 *
 * @return State of the change request for new AOCS system state.
 */
static aocs_cntrl_sys_state_req_state_t fs_aocs_cntrl_cubeadcs_gen2_get_aocs_change_status(const cubeadcs_gen2_sys_state_change_status_t state_change_status)
{
    aocs_cntrl_sys_state_req_state_t res;

    switch (state_change_status)
    {
    case CUBEADCS_GEN2_SYS_STATE_CHANGE_SUCCESS:
        res = AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED;
        break;

    case CUBEADCS_GEN2_SYS_STATE_CHANGE_ERROR:
        res = AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED;
        break;

    case CUBEADCS_GEN2_SYS_STATE_CHANGE_IN_PROGRESS:
        res = AOCS_CNTRL_SYS_STATE_STATE_REQ_IN_PROGRESS;
        break;

    default:
        res = AOCS_CNTRL_SYS_STATE_STATE_MAX;
        break;
    }

    return res;
}

