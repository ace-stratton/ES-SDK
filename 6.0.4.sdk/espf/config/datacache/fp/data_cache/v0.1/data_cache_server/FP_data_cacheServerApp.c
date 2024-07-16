/*!
********************************************************************************************
* @file FP_data_cacheServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface data_cache v0.1
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

#include "FP_data_cacheProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void data_cache_get_OBC_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_OBC_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_OBC_0_DataRequestData_t* pRequestData);

static void data_cache_get_ADCS_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ADCS_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ADCS_0_DataRequestData_t* pRequestData);

static void data_cache_get_ADCS_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ADCS_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ADCS_1_DataRequestData_t* pRequestData);

static void data_cache_get_ADCS_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ADCS_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ADCS_2_DataRequestData_t* pRequestData);

static void data_cache_get_EPS_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS_0_DataRequestData_t* pRequestData);

static void data_cache_get_SSP_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SSP_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SSP_0_DataRequestData_t* pRequestData);

static void data_cache_get_SSP_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SSP_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SSP_1_DataRequestData_t* pRequestData);

static void data_cache_get_SSP_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SSP_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SSP_2_DataRequestData_t* pRequestData);

static void data_cache_get_AOCS_CNTRL_TLM_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_AOCS_CNTRL_TLM_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_AOCS_CNTRL_TLM_DataRequestData_t* pRequestData);

static void data_cache_get_OS_Task_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_OS_Task_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_OS_Task_DataRequestData_t* pRequestData);

static void data_cache_get_SSP_3_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SSP_3_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SSP_3_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_MAG_PRIMARY_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_MAG_SECONDARY_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_GYRO_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_COARSE_SUN_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_COARSE_SUN_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_COARSE_SUN_DataRequestData_t* pRequestData);

static void data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestData_t* pRequestData);

static void data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestData_t* pRequestData);

static void data_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_GYRO_DataRequestData_t* pRequestData);

static void data_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_CSS_DataRequestData_t* pRequestData);

static void data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataRequestData_t* pRequestData);

static void data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestData_t* pRequestData);

static void data_cache_get_ConOpsFlags_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ConOpsFlags_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ConOpsFlags_DataRequestData_t* pRequestData);

static void data_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_AOCS_CNTRL_SYS_STATE_DataRequestData_t* pRequestData);

static void data_cache_get_ADCS_3_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ADCS_3_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ADCS_3_DataRequestData_t* pRequestData);

static void data_cache_get_ADCS_4_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_ADCS_4_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_ADCS_4_DataRequestData_t* pRequestData);

static void data_cache_get_EPS_9_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS_9_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS_9_DataRequestData_t* pRequestData);

static void data_cache_get_EPS_10_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS_10_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS_10_DataRequestData_t* pRequestData);

static void data_cache_get_EPS_14_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS_14_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS_14_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_ACC_PRIMARY_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_ACC_SECONDARY_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_PANEL_TEMP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_PANEL_TEMP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_PANEL_TEMP_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_GYRO_TEMP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_GYRO_TEMP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_GYRO_TEMP_DataRequestData_t* pRequestData);

static void data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestData_t* pRequestData);

static void data_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_AOCS_CNTRL_REF_PARAMS_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestData_t* pRequestData);

static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestData_t* pRequestData);

static void data_cache_get_GNSS_TIME_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_GNSS_TIME_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_GNSS_TIME_DataRequestData_t* pRequestData);

static void data_cache_get_GNSS_BESTXYZ_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_GNSS_BESTXYZ_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_GNSS_BESTXYZ_DataRequestData_t* pRequestData);

static void data_cache_get_EpsOverallBatteryInfo_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EpsOverallBatteryInfo_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EpsOverallBatteryInfo_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BP_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BP_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BP_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataRequestData_t* pRequestData);

static void data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx);

static void data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static data_cache_ServerApi_t data_cacheServerApiCtx =
{
  .data_cache_get_OBC_0_DataRequestHandler = (pfdata_cache_get_OBC_0_DataRequestHandler_t) data_cache_get_OBC_0_DataRequestHandlerImpl,
  .data_cache_set_OBC_0_DataRequestHandler = (pfdata_cache_set_OBC_0_DataRequestHandler_t) data_cache_set_OBC_0_DataRequestHandlerImpl,
  .data_cache_get_ADCS_0_DataRequestHandler = (pfdata_cache_get_ADCS_0_DataRequestHandler_t) data_cache_get_ADCS_0_DataRequestHandlerImpl,
  .data_cache_set_ADCS_0_DataRequestHandler = (pfdata_cache_set_ADCS_0_DataRequestHandler_t) data_cache_set_ADCS_0_DataRequestHandlerImpl,
  .data_cache_get_ADCS_1_DataRequestHandler = (pfdata_cache_get_ADCS_1_DataRequestHandler_t) data_cache_get_ADCS_1_DataRequestHandlerImpl,
  .data_cache_set_ADCS_1_DataRequestHandler = (pfdata_cache_set_ADCS_1_DataRequestHandler_t) data_cache_set_ADCS_1_DataRequestHandlerImpl,
  .data_cache_get_ADCS_2_DataRequestHandler = (pfdata_cache_get_ADCS_2_DataRequestHandler_t) data_cache_get_ADCS_2_DataRequestHandlerImpl,
  .data_cache_set_ADCS_2_DataRequestHandler = (pfdata_cache_set_ADCS_2_DataRequestHandler_t) data_cache_set_ADCS_2_DataRequestHandlerImpl,
  .data_cache_get_EPS_0_DataRequestHandler = (pfdata_cache_get_EPS_0_DataRequestHandler_t) data_cache_get_EPS_0_DataRequestHandlerImpl,
  .data_cache_set_EPS_0_DataRequestHandler = (pfdata_cache_set_EPS_0_DataRequestHandler_t) data_cache_set_EPS_0_DataRequestHandlerImpl,
  .data_cache_get_SSP_0_DataRequestHandler = (pfdata_cache_get_SSP_0_DataRequestHandler_t) data_cache_get_SSP_0_DataRequestHandlerImpl,
  .data_cache_set_SSP_0_DataRequestHandler = (pfdata_cache_set_SSP_0_DataRequestHandler_t) data_cache_set_SSP_0_DataRequestHandlerImpl,
  .data_cache_get_SSP_1_DataRequestHandler = (pfdata_cache_get_SSP_1_DataRequestHandler_t) data_cache_get_SSP_1_DataRequestHandlerImpl,
  .data_cache_set_SSP_1_DataRequestHandler = (pfdata_cache_set_SSP_1_DataRequestHandler_t) data_cache_set_SSP_1_DataRequestHandlerImpl,
  .data_cache_get_SSP_2_DataRequestHandler = (pfdata_cache_get_SSP_2_DataRequestHandler_t) data_cache_get_SSP_2_DataRequestHandlerImpl,
  .data_cache_set_SSP_2_DataRequestHandler = (pfdata_cache_set_SSP_2_DataRequestHandler_t) data_cache_set_SSP_2_DataRequestHandlerImpl,
  .data_cache_get_AOCS_CNTRL_TLM_DataRequestHandler = (pfdata_cache_get_AOCS_CNTRL_TLM_DataRequestHandler_t) data_cache_get_AOCS_CNTRL_TLM_DataRequestHandlerImpl,
  .data_cache_set_AOCS_CNTRL_TLM_DataRequestHandler = (pfdata_cache_set_AOCS_CNTRL_TLM_DataRequestHandler_t) data_cache_set_AOCS_CNTRL_TLM_DataRequestHandlerImpl,
  .data_cache_get_OS_Task_DataRequestHandler = (pfdata_cache_get_OS_Task_DataRequestHandler_t) data_cache_get_OS_Task_DataRequestHandlerImpl,
  .data_cache_set_OS_Task_DataRequestHandler = (pfdata_cache_set_OS_Task_DataRequestHandler_t) data_cache_set_OS_Task_DataRequestHandlerImpl,
  .data_cache_get_SSP_3_DataRequestHandler = (pfdata_cache_get_SSP_3_DataRequestHandler_t) data_cache_get_SSP_3_DataRequestHandlerImpl,
  .data_cache_set_SSP_3_DataRequestHandler = (pfdata_cache_set_SSP_3_DataRequestHandler_t) data_cache_set_SSP_3_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandler = (pfdata_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandler_t) data_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandler = (pfdata_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandler_t) data_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandler = (pfdata_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandler_t) data_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandler = (pfdata_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandler_t) data_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_GYRO_DataRequestHandler = (pfdata_cache_get_SENSOR_GYRO_DataRequestHandler_t) data_cache_get_SENSOR_GYRO_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_GYRO_DataRequestHandler = (pfdata_cache_set_SENSOR_GYRO_DataRequestHandler_t) data_cache_set_SENSOR_GYRO_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_COARSE_SUN_DataRequestHandler = (pfdata_cache_get_SENSOR_COARSE_SUN_DataRequestHandler_t) data_cache_get_SENSOR_COARSE_SUN_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_COARSE_SUN_DataRequestHandler = (pfdata_cache_set_SENSOR_COARSE_SUN_DataRequestHandler_t) data_cache_set_SENSOR_COARSE_SUN_DataRequestHandlerImpl,
  .data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler = (pfdata_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler_t) data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl,
  .data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler = (pfdata_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler_t) data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl,
  .data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler = (pfdata_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler_t) data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl,
  .data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler = (pfdata_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler_t) data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl,
  .data_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandler = (pfdata_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandler_t) data_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandlerImpl,
  .data_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandler = (pfdata_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandler_t) data_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandlerImpl,
  .data_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandler = (pfdata_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandler_t) data_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandlerImpl,
  .data_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandler = (pfdata_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandler_t) data_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandlerImpl,
  .data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler = (pfdata_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler_t) data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandlerImpl,
  .data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler = (pfdata_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler_t) data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandlerImpl,
  .data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler = (pfdata_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler_t) data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandlerImpl,
  .data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler = (pfdata_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler_t) data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandlerImpl,
  .data_cache_get_ConOpsFlags_DataRequestHandler = (pfdata_cache_get_ConOpsFlags_DataRequestHandler_t) data_cache_get_ConOpsFlags_DataRequestHandlerImpl,
  .data_cache_set_ConOpsFlags_DataRequestHandler = (pfdata_cache_set_ConOpsFlags_DataRequestHandler_t) data_cache_set_ConOpsFlags_DataRequestHandlerImpl,
  .data_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandler = (pfdata_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandler_t) data_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandlerImpl,
  .data_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandler = (pfdata_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandler_t) data_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandlerImpl,
  .data_cache_get_ADCS_3_DataRequestHandler = (pfdata_cache_get_ADCS_3_DataRequestHandler_t) data_cache_get_ADCS_3_DataRequestHandlerImpl,
  .data_cache_set_ADCS_3_DataRequestHandler = (pfdata_cache_set_ADCS_3_DataRequestHandler_t) data_cache_set_ADCS_3_DataRequestHandlerImpl,
  .data_cache_get_ADCS_4_DataRequestHandler = (pfdata_cache_get_ADCS_4_DataRequestHandler_t) data_cache_get_ADCS_4_DataRequestHandlerImpl,
  .data_cache_set_ADCS_4_DataRequestHandler = (pfdata_cache_set_ADCS_4_DataRequestHandler_t) data_cache_set_ADCS_4_DataRequestHandlerImpl,
  .data_cache_get_EPS_9_DataRequestHandler = (pfdata_cache_get_EPS_9_DataRequestHandler_t) data_cache_get_EPS_9_DataRequestHandlerImpl,
  .data_cache_set_EPS_9_DataRequestHandler = (pfdata_cache_set_EPS_9_DataRequestHandler_t) data_cache_set_EPS_9_DataRequestHandlerImpl,
  .data_cache_get_EPS_10_DataRequestHandler = (pfdata_cache_get_EPS_10_DataRequestHandler_t) data_cache_get_EPS_10_DataRequestHandlerImpl,
  .data_cache_set_EPS_10_DataRequestHandler = (pfdata_cache_set_EPS_10_DataRequestHandler_t) data_cache_set_EPS_10_DataRequestHandlerImpl,
  .data_cache_get_EPS_14_DataRequestHandler = (pfdata_cache_get_EPS_14_DataRequestHandler_t) data_cache_get_EPS_14_DataRequestHandlerImpl,
  .data_cache_set_EPS_14_DataRequestHandler = (pfdata_cache_set_EPS_14_DataRequestHandler_t) data_cache_set_EPS_14_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandler = (pfdata_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandler_t) data_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandler = (pfdata_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandler_t) data_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandler = (pfdata_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandler_t) data_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandler = (pfdata_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandler_t) data_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler = (pfdata_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler_t) data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler = (pfdata_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler_t) data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler = (pfdata_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler_t) data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler = (pfdata_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler_t) data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_PANEL_TEMP_DataRequestHandler = (pfdata_cache_get_SENSOR_PANEL_TEMP_DataRequestHandler_t) data_cache_get_SENSOR_PANEL_TEMP_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_PANEL_TEMP_DataRequestHandler = (pfdata_cache_set_SENSOR_PANEL_TEMP_DataRequestHandler_t) data_cache_set_SENSOR_PANEL_TEMP_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler = (pfdata_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler_t) data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler = (pfdata_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler_t) data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_GYRO_TEMP_DataRequestHandler = (pfdata_cache_get_SENSOR_GYRO_TEMP_DataRequestHandler_t) data_cache_get_SENSOR_GYRO_TEMP_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_GYRO_TEMP_DataRequestHandler = (pfdata_cache_set_SENSOR_GYRO_TEMP_DataRequestHandler_t) data_cache_set_SENSOR_GYRO_TEMP_DataRequestHandlerImpl,
  .data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler = (pfdata_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler_t) data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler = (pfdata_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler_t) data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandlerImpl,
  .data_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandler = (pfdata_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandler_t) data_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandlerImpl,
  .data_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandler = (pfdata_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandler_t) data_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandlerImpl,
  .data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler = (pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler_t) data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandlerImpl,
  .data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler = (pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler_t) data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandlerImpl,
  .data_cache_get_GNSS_TIME_DataRequestHandler = (pfdata_cache_get_GNSS_TIME_DataRequestHandler_t) data_cache_get_GNSS_TIME_DataRequestHandlerImpl,
  .data_cache_set_GNSS_TIME_DataRequestHandler = (pfdata_cache_set_GNSS_TIME_DataRequestHandler_t) data_cache_set_GNSS_TIME_DataRequestHandlerImpl,
  .data_cache_get_GNSS_BESTXYZ_DataRequestHandler = (pfdata_cache_get_GNSS_BESTXYZ_DataRequestHandler_t) data_cache_get_GNSS_BESTXYZ_DataRequestHandlerImpl,
  .data_cache_set_GNSS_BESTXYZ_DataRequestHandler = (pfdata_cache_set_GNSS_BESTXYZ_DataRequestHandler_t) data_cache_set_GNSS_BESTXYZ_DataRequestHandlerImpl,
  .data_cache_get_EpsOverallBatteryInfo_DataRequestHandler = (pfdata_cache_get_EpsOverallBatteryInfo_DataRequestHandler_t) data_cache_get_EpsOverallBatteryInfo_DataRequestHandlerImpl,
  .data_cache_set_EpsOverallBatteryInfo_DataRequestHandler = (pfdata_cache_set_EpsOverallBatteryInfo_DataRequestHandler_t) data_cache_set_EpsOverallBatteryInfo_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandlerImpl,
  .data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler = (pfdata_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler_t) data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandlerImpl,
  .data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler = (pfdata_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler_t) data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method data_cache::get_OBC_0_Data (ID = 0x00000000)
static void data_cache_get_OBC_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_OBC_0_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_OBC_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_OBC_0_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_obc_0_data(&sOutput_data);

        respResult = data_cache_get_OBC_0_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_OBC_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_OBC_0_Data (ID = 0x00000000)

// @START@ Request handler for method data_cache::set_OBC_0_Data (ID = 0x00000001)
static void data_cache_set_OBC_0_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_OBC_0_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_OBC_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_OBC_0_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_OBC_0_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_OBC_0_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_OBC_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_OBC_0_Data (ID = 0x00000001)

// @START@ Request handler for method data_cache::get_ADCS_0_Data (ID = 0x00000002)
static void data_cache_get_ADCS_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ADCS_0_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ADCS_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ADCS_0_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_adcs_0_data(&sOutput_data);

        respResult = data_cache_get_ADCS_0_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ADCS_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ADCS_0_Data (ID = 0x00000002)

// @START@ Request handler for method data_cache::set_ADCS_0_Data (ID = 0x00000003)
static void data_cache_set_ADCS_0_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ADCS_0_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ADCS_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ADCS_0_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ADCS_0_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ADCS_0_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ADCS_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ADCS_0_Data (ID = 0x00000003)

// @START@ Request handler for method data_cache::get_ADCS_1_Data (ID = 0x00000004)
static void data_cache_get_ADCS_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ADCS_1_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ADCS_1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ADCS_1_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_adcs_1_data(&sOutput_data);

        respResult = data_cache_get_ADCS_1_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ADCS_1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ADCS_1_Data (ID = 0x00000004)

// @START@ Request handler for method data_cache::set_ADCS_1_Data (ID = 0x00000005)
static void data_cache_set_ADCS_1_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ADCS_1_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ADCS_1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ADCS_1_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ADCS_1_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ADCS_1_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ADCS_1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ADCS_1_Data (ID = 0x00000005)

// @START@ Request handler for method data_cache::get_ADCS_2_Data (ID = 0x00000006)
static void data_cache_get_ADCS_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ADCS_2_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ADCS_2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ADCS_2_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_adcs_2_data(&sOutput_data);

        respResult = data_cache_get_ADCS_2_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ADCS_2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ADCS_2_Data (ID = 0x00000006)

// @START@ Request handler for method data_cache::set_ADCS_2_Data (ID = 0x00000007)
static void data_cache_set_ADCS_2_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ADCS_2_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ADCS_2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ADCS_2_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ADCS_2_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ADCS_2_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ADCS_2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ADCS_2_Data (ID = 0x00000007)

// @START@ Request handler for method data_cache::get_EPS_0_Data (ID = 0x00000008)
static void data_cache_get_EPS_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_EPS_0_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS_0_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps_0_data(&sOutput_data);

        respResult = data_cache_get_EPS_0_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS_0_Data (ID = 0x00000008)

// @START@ Request handler for method data_cache::set_EPS_0_Data (ID = 0x00000009)
static void data_cache_set_EPS_0_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS_0_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS_0_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS_0_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS_0_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS_0_Data (ID = 0x00000009)

// @START@ Request handler for method data_cache::get_SSP_0_Data (ID = 0x0000000A)
static void data_cache_get_SSP_0_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SSP_0_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SSP_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SSP_0_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_ssp_0_data(&sOutput_data);

        respResult = data_cache_get_SSP_0_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SSP_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SSP_0_Data (ID = 0x0000000A)

// @START@ Request handler for method data_cache::set_SSP_0_Data (ID = 0x0000000B)
static void data_cache_set_SSP_0_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SSP_0_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SSP_0_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SSP_0_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SSP_0_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SSP_0_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SSP_0_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SSP_0_Data (ID = 0x0000000B)

// @START@ Request handler for method data_cache::get_SSP_1_Data (ID = 0x0000000C)
static void data_cache_get_SSP_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SSP_1_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SSP_1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SSP_1_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_ssp_1_data(&sOutput_data);

        respResult = data_cache_get_SSP_1_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SSP_1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SSP_1_Data (ID = 0x0000000C)

// @START@ Request handler for method data_cache::set_SSP_1_Data (ID = 0x0000000D)
static void data_cache_set_SSP_1_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SSP_1_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SSP_1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SSP_1_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SSP_1_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SSP_1_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SSP_1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SSP_1_Data (ID = 0x0000000D)

// @START@ Request handler for method data_cache::get_SSP_2_Data (ID = 0x0000000E)
static void data_cache_get_SSP_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SSP_2_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SSP_2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SSP_2_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_ssp_2_data(&sOutput_data);

        respResult = data_cache_get_SSP_2_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SSP_2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SSP_2_Data (ID = 0x0000000E)

// @START@ Request handler for method data_cache::set_SSP_2_Data (ID = 0x0000000F)
static void data_cache_set_SSP_2_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SSP_2_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SSP_2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SSP_2_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SSP_2_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SSP_2_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SSP_2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SSP_2_Data (ID = 0x0000000F)

// @START@ Request handler for method data_cache::get_AOCS_CNTRL_TLM_Data (ID = 0x00000010)
static void data_cache_get_AOCS_CNTRL_TLM_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_AOCS_CNTRL_TLM_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_AOCS_CNTRL_TLM_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_AOCS_CNTRL_TLM_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_aocs_cntrl_tlm_data(&sOutput_data);

        respResult = data_cache_get_AOCS_CNTRL_TLM_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_AOCS_CNTRL_TLM_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_AOCS_CNTRL_TLM_Data (ID = 0x00000010)

// @START@ Request handler for method data_cache::set_AOCS_CNTRL_TLM_Data (ID = 0x00000011)
static void data_cache_set_AOCS_CNTRL_TLM_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_AOCS_CNTRL_TLM_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_AOCS_CNTRL_TLM_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_AOCS_CNTRL_TLM_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_AOCS_CNTRL_TLM_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_AOCS_CNTRL_TLM_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_AOCS_CNTRL_TLM_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_AOCS_CNTRL_TLM_Data (ID = 0x00000011)

// @START@ Request handler for method data_cache::get_OS_Task_Data (ID = 0x00000012)
static void data_cache_get_OS_Task_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_TaskStats_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_OS_Task_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_OS_Task_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_os_task_data(&sOutput_data);

        respResult = data_cache_get_OS_Task_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_OS_TASK_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_OS_Task_Data (ID = 0x00000012)

// @START@ Request handler for method data_cache::set_OS_Task_Data (ID = 0x00000013)
static void data_cache_set_OS_Task_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_OS_Task_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_OS_Task_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_OS_Task_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_OS_TASK_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_OS_Task_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_OS_TASK_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_OS_Task_Data (ID = 0x00000013)

// @START@ Request handler for method data_cache::get_SSP_3_Data (ID = 0x00000014)
static void data_cache_get_SSP_3_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SSP_3_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SSP_3_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SSP_3_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_ssp_3_data(&sOutput_data);

        respResult = data_cache_get_SSP_3_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SSP_3_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SSP_3_Data (ID = 0x00000014)

// @START@ Request handler for method data_cache::set_SSP_3_Data (ID = 0x00000015)
static void data_cache_set_SSP_3_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SSP_3_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SSP_3_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SSP_3_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SSP_3_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SSP_3_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SSP_3_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SSP_3_Data (ID = 0x00000015)

// @START@ Request handler for method data_cache::get_SENSOR_MAG_PRIMARY_Data (ID = 0x00000016)
static void data_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_MAG_PRIMARY_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_MAG_PRIMARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_MAG_PRIMARY_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_mag_primary_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_MAG_PRIMARY_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_MAG_PRIMARY_Data (ID = 0x00000016)

// @START@ Request handler for method data_cache::set_SENSOR_MAG_PRIMARY_Data (ID = 0x00000017)
static void data_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_MAG_PRIMARY_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_MAG_PRIMARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_MAG_PRIMARY_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_MAG_PRIMARY_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_MAG_PRIMARY_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_MAG_PRIMARY_Data (ID = 0x00000017)

// @START@ Request handler for method data_cache::get_SENSOR_MAG_SECONDARY_Data (ID = 0x00000018)
static void data_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_MAG_SECONDARY_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_MAG_SECONDARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_MAG_SECONDARY_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_mag_secondary_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_MAG_SECONDARY_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_MAG_SECONDARY_Data (ID = 0x00000018)

// @START@ Request handler for method data_cache::set_SENSOR_MAG_SECONDARY_Data (ID = 0x00000019)
static void data_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_MAG_SECONDARY_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_MAG_SECONDARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_MAG_SECONDARY_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_MAG_SECONDARY_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_MAG_SECONDARY_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_MAG_SECONDARY_Data (ID = 0x00000019)

// @START@ Request handler for method data_cache::get_SENSOR_GYRO_Data (ID = 0x0000001A)
static void data_cache_get_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_GYRO_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_GYRO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_GYRO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_gyro_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_GYRO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_GYRO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_GYRO_Data (ID = 0x0000001A)

// @START@ Request handler for method data_cache::set_SENSOR_GYRO_Data (ID = 0x0000001B)
static void data_cache_set_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_GYRO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_GYRO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_GYRO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_GYRO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_GYRO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_GYRO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_GYRO_Data (ID = 0x0000001B)

// @START@ Request handler for method data_cache::get_SENSOR_COARSE_SUN_Data (ID = 0x0000001C)
static void data_cache_get_SENSOR_COARSE_SUN_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_COARSE_SUN_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_COARSE_SUN_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_COARSE_SUN_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_coarse_sun_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_COARSE_SUN_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_COARSE_SUN_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_COARSE_SUN_Data (ID = 0x0000001C)

// @START@ Request handler for method data_cache::set_SENSOR_COARSE_SUN_Data (ID = 0x0000001D)
static void data_cache_set_SENSOR_COARSE_SUN_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_COARSE_SUN_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_COARSE_SUN_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_COARSE_SUN_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_COARSE_SUN_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_COARSE_SUN_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_COARSE_SUN_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_COARSE_SUN_Data (ID = 0x0000001D)

// @START@ Request handler for method data_cache::get_ES_ADCS_SENSOR_MAG_PRIMARY_Data (ID = 0x0000001E)
static void data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ES_ADCS_SENSOR_MAG_PRIMARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ES_ADCS_SENSOR_MAG_PRIMARY_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_es_adcs_sensor_mag_primary_data(&sOutput_data);

        respResult = data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ES_ADCS_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ES_ADCS_SENSOR_MAG_PRIMARY_Data (ID = 0x0000001E)

// @START@ Request handler for method data_cache::set_ES_ADCS_SENSOR_MAG_PRIMARY_Data (ID = 0x0000001F)
static void data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ES_ADCS_SENSOR_MAG_PRIMARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ES_ADCS_SENSOR_MAG_PRIMARY_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ES_ADCS_SENSOR_MAG_PRIMARY_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ES_ADCS_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ES_ADCS_SENSOR_MAG_PRIMARY_Data (ID = 0x0000001F)

// @START@ Request handler for method data_cache::get_ES_ADCS_SENSOR_MAG_SECONDARY_Data (ID = 0x00000020)
static void data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ES_ADCS_SENSOR_MAG_SECONDARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ES_ADCS_SENSOR_MAG_SECONDARY_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_es_adcs_sensor_mag_secondary_data(&sOutput_data);

        respResult = data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ES_ADCS_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ES_ADCS_SENSOR_MAG_SECONDARY_Data (ID = 0x00000020)

// @START@ Request handler for method data_cache::set_ES_ADCS_SENSOR_MAG_SECONDARY_Data (ID = 0x00000021)
static void data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ES_ADCS_SENSOR_MAG_SECONDARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ES_ADCS_SENSOR_MAG_SECONDARY_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ES_ADCS_SENSOR_MAG_SECONDARY_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ES_ADCS_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ES_ADCS_SENSOR_MAG_SECONDARY_Data (ID = 0x00000021)

// @START@ Request handler for method data_cache::get_ES_ADCS_SENSOR_GYRO_Data (ID = 0x00000022)
static void data_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ES_ADCS_SENSOR_GYRO_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ES_ADCS_SENSOR_GYRO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ES_ADCS_SENSOR_GYRO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_es_adcs_sensor_gyro_data(&sOutput_data);

        respResult = data_cache_get_ES_ADCS_SENSOR_GYRO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ES_ADCS_SENSOR_GYRO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ES_ADCS_SENSOR_GYRO_Data (ID = 0x00000022)

// @START@ Request handler for method data_cache::set_ES_ADCS_SENSOR_GYRO_Data (ID = 0x00000023)
static void data_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_GYRO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ES_ADCS_SENSOR_GYRO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ES_ADCS_SENSOR_GYRO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ES_ADCS_SENSOR_GYRO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ES_ADCS_SENSOR_GYRO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ES_ADCS_SENSOR_GYRO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ES_ADCS_SENSOR_GYRO_Data (ID = 0x00000023)

// @START@ Request handler for method data_cache::get_ES_ADCS_SENSOR_CSS_Data (ID = 0x00000024)
static void data_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ES_ADCS_SENSOR_CSS_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ES_ADCS_SENSOR_CSS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ES_ADCS_SENSOR_CSS_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_es_adcs_sensor_css_data(&sOutput_data);

        respResult = data_cache_get_ES_ADCS_SENSOR_CSS_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ES_ADCS_SENSOR_CSS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ES_ADCS_SENSOR_CSS_Data (ID = 0x00000024)

// @START@ Request handler for method data_cache::set_ES_ADCS_SENSOR_CSS_Data (ID = 0x00000025)
static void data_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ES_ADCS_SENSOR_CSS_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ES_ADCS_SENSOR_CSS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ES_ADCS_SENSOR_CSS_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ES_ADCS_SENSOR_CSS_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ES_ADCS_SENSOR_CSS_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ES_ADCS_SENSOR_CSS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ES_ADCS_SENSOR_CSS_Data (ID = 0x00000025)

// @START@ Request handler for method data_cache::get_ES_ADCS_ESTIMATES_BDOT_Data (ID = 0x00000026)
static void data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ES_ADCS_ESTIMATES_BDOT_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ES_ADCS_ESTIMATES_BDOT_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_es_adcs_estimates_bdot_data(&sOutput_data);

        respResult = data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ES_ADCS_ESTIMATES_BDOT_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ES_ADCS_ESTIMATES_BDOT_Data (ID = 0x00000026)

// @START@ Request handler for method data_cache::set_ES_ADCS_ESTIMATES_BDOT_Data (ID = 0x00000027)
static void data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ES_ADCS_ESTIMATES_BDOT_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ES_ADCS_ESTIMATES_BDOT_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ES_ADCS_ESTIMATES_BDOT_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ES_ADCS_ESTIMATES_BDOT_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ES_ADCS_ESTIMATES_BDOT_Data (ID = 0x00000027)

// @START@ Request handler for method data_cache::get_ES_ADCS_CONTROL_VALUES_MTQ_Data (ID = 0x00000028)
static void data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ES_ADCS_CONTROL_VALUES_MTQ_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ES_ADCS_CONTROL_VALUES_MTQ_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_es_adcs_control_values_mtq_data(&sOutput_data);

        respResult = data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ES_ADCS_CONTROL_VALUES_MTQ_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ES_ADCS_CONTROL_VALUES_MTQ_Data (ID = 0x00000028)

// @START@ Request handler for method data_cache::set_ES_ADCS_CONTROL_VALUES_MTQ_Data (ID = 0x00000029)
static void data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ES_ADCS_CONTROL_VALUES_MTQ_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ES_ADCS_CONTROL_VALUES_MTQ_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ES_ADCS_CONTROL_VALUES_MTQ_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ES_ADCS_CONTROL_VALUES_MTQ_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ES_ADCS_CONTROL_VALUES_MTQ_Data (ID = 0x00000029)

// @START@ Request handler for method data_cache::get_ConOpsFlags_Data (ID = 0x0000002A)
static void data_cache_get_ConOpsFlags_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ConOpsFlags_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ConOpsFlags_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ConOpsFlags_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_conopsflags_data(&sOutput_data);

        respResult = data_cache_get_ConOpsFlags_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CONOPSFLAGS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ConOpsFlags_Data (ID = 0x0000002A)

// @START@ Request handler for method data_cache::set_ConOpsFlags_Data (ID = 0x0000002B)
static void data_cache_set_ConOpsFlags_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ConOpsFlags_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ConOpsFlags_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ConOpsFlags_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CONOPSFLAGS_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ConOpsFlags_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CONOPSFLAGS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ConOpsFlags_Data (ID = 0x0000002B)

// @START@ Request handler for method data_cache::get_AOCS_CNTRL_SYS_STATE_Data (ID = 0x0000002C)
static void data_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_AOCS_CNTRL_SYS_STATE_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_AOCS_CNTRL_SYS_STATE_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_AOCS_CNTRL_SYS_STATE_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_aocs_cntrl_sys_state_data(&sOutput_data);

        respResult = data_cache_get_AOCS_CNTRL_SYS_STATE_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_AOCS_CNTRL_SYS_STATE_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_AOCS_CNTRL_SYS_STATE_Data (ID = 0x0000002C)

// @START@ Request handler for method data_cache::set_AOCS_CNTRL_SYS_STATE_Data (ID = 0x0000002D)
static void data_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_AOCS_CNTRL_SYS_STATE_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_AOCS_CNTRL_SYS_STATE_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_AOCS_CNTRL_SYS_STATE_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_AOCS_CNTRL_SYS_STATE_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_AOCS_CNTRL_SYS_STATE_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_AOCS_CNTRL_SYS_STATE_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_AOCS_CNTRL_SYS_STATE_Data (ID = 0x0000002D)

// @START@ Request handler for method data_cache::get_ADCS_3_Data (ID = 0x0000002E)
static void data_cache_get_ADCS_3_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ADCS_3_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ADCS_3_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ADCS_3_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_adcs_3_data(&sOutput_data);

        respResult = data_cache_get_ADCS_3_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ADCS_3_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ADCS_3_Data (ID = 0x0000002E)

// @START@ Request handler for method data_cache::set_ADCS_3_Data (ID = 0x0000002F)
static void data_cache_set_ADCS_3_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ADCS_3_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ADCS_3_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ADCS_3_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ADCS_3_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ADCS_3_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ADCS_3_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ADCS_3_Data (ID = 0x0000002F)

// @START@ Request handler for method data_cache::get_ADCS_4_Data (ID = 0x00000030)
static void data_cache_get_ADCS_4_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_ADCS_4_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_ADCS_4_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_ADCS_4_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_adcs_4_data(&sOutput_data);

        respResult = data_cache_get_ADCS_4_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_ADCS_4_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_ADCS_4_Data (ID = 0x00000030)

// @START@ Request handler for method data_cache::set_ADCS_4_Data (ID = 0x00000031)
static void data_cache_set_ADCS_4_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_ADCS_4_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_ADCS_4_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_ADCS_4_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_ADCS_4_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_ADCS_4_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_ADCS_4_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_ADCS_4_Data (ID = 0x00000031)

// @START@ Request handler for method data_cache::get_EPS_9_Data (ID = 0x00000032)
static void data_cache_get_EPS_9_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_EPS_9_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS_9_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS_9_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps_9_data(&sOutput_data);

        respResult = data_cache_get_EPS_9_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS_9_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS_9_Data (ID = 0x00000032)

// @START@ Request handler for method data_cache::set_EPS_9_Data (ID = 0x00000033)
static void data_cache_set_EPS_9_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS_9_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS_9_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS_9_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS_9_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS_9_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS_9_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS_9_Data (ID = 0x00000033)

// @START@ Request handler for method data_cache::get_EPS_10_Data (ID = 0x00000034)
static void data_cache_get_EPS_10_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_EPS_10_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS_10_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS_10_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps_10_data(&sOutput_data);

        respResult = data_cache_get_EPS_10_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS_10_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS_10_Data (ID = 0x00000034)

// @START@ Request handler for method data_cache::set_EPS_10_Data (ID = 0x00000035)
static void data_cache_set_EPS_10_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS_10_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS_10_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS_10_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS_10_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS_10_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS_10_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS_10_Data (ID = 0x00000035)

// @START@ Request handler for method data_cache::get_EPS_14_Data (ID = 0x00000036)
static void data_cache_get_EPS_14_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_EPS_14_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS_14_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS_14_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps_14_data(&sOutput_data);

        respResult = data_cache_get_EPS_14_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS_14_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS_14_Data (ID = 0x00000036)

// @START@ Request handler for method data_cache::set_EPS_14_Data (ID = 0x00000037)
static void data_cache_set_EPS_14_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS_14_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS_14_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS_14_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS_14_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS_14_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS_14_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS_14_Data (ID = 0x00000037)

// @START@ Request handler for method data_cache::get_SENSOR_ACC_PRIMARY_Data (ID = 0x00000038)
static void data_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_ACC_PRIMARY_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_ACC_PRIMARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_ACC_PRIMARY_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_acc_primary_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_ACC_PRIMARY_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_ACC_PRIMARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_ACC_PRIMARY_Data (ID = 0x00000038)

// @START@ Request handler for method data_cache::set_SENSOR_ACC_PRIMARY_Data (ID = 0x00000039)
static void data_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_ACC_PRIMARY_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_ACC_PRIMARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_ACC_PRIMARY_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_ACC_PRIMARY_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_ACC_PRIMARY_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_ACC_PRIMARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_ACC_PRIMARY_Data (ID = 0x00000039)

// @START@ Request handler for method data_cache::get_SENSOR_ACC_SECONDARY_Data (ID = 0x0000003A)
static void data_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_ACC_SECONDARY_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_ACC_SECONDARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_ACC_SECONDARY_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_acc_secondary_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_ACC_SECONDARY_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_ACC_SECONDARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_ACC_SECONDARY_Data (ID = 0x0000003A)

// @START@ Request handler for method data_cache::set_SENSOR_ACC_SECONDARY_Data (ID = 0x0000003B)
static void data_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_ACC_SECONDARY_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_ACC_SECONDARY_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_ACC_SECONDARY_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_ACC_SECONDARY_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_ACC_SECONDARY_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_ACC_SECONDARY_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_ACC_SECONDARY_Data (ID = 0x0000003B)

// @START@ Request handler for method data_cache::get_SENSOR_ACC_PRIMARY_SAT_FRAME_Data (ID = 0x0000003C)
static void data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_ACC_PRIMARY_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_ACC_PRIMARY_SAT_FRAME_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_acc_primary_sat_frame_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_ACC_PRIMARY_SAT_FRAME_Data (ID = 0x0000003C)

// @START@ Request handler for method data_cache::set_SENSOR_ACC_PRIMARY_SAT_FRAME_Data (ID = 0x0000003D)
static void data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_ACC_PRIMARY_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_ACC_PRIMARY_SAT_FRAME_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_ACC_PRIMARY_SAT_FRAME_Data (ID = 0x0000003D)

// @START@ Request handler for method data_cache::get_SENSOR_ACC_SECONDARY_SAT_FRAME_Data (ID = 0x0000003E)
static void data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_ACC_SECONDARY_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_ACC_SECONDARY_SAT_FRAME_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_acc_secondary_sat_frame_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_ACC_SECONDARY_SAT_FRAME_Data (ID = 0x0000003E)

// @START@ Request handler for method data_cache::set_SENSOR_ACC_SECONDARY_SAT_FRAME_Data (ID = 0x0000003F)
static void data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_ACC_SECONDARY_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_ACC_SECONDARY_SAT_FRAME_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_ACC_SECONDARY_SAT_FRAME_Data (ID = 0x0000003F)

// @START@ Request handler for method data_cache::get_SENSOR_PANEL_TEMP_Data (ID = 0x00000040)
static void data_cache_get_SENSOR_PANEL_TEMP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_PANEL_TEMP_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_PANEL_TEMP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_PANEL_TEMP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_panel_temp_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_PANEL_TEMP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_PANEL_TEMP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_PANEL_TEMP_Data (ID = 0x00000040)

// @START@ Request handler for method data_cache::set_SENSOR_PANEL_TEMP_Data (ID = 0x00000041)
static void data_cache_set_SENSOR_PANEL_TEMP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_PANEL_TEMP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_PANEL_TEMP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_PANEL_TEMP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_PANEL_TEMP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_PANEL_TEMP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_PANEL_TEMP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_PANEL_TEMP_Data (ID = 0x00000041)

// @START@ Request handler for method data_cache::get_SENSOR_PANEL_TEMP_SAT_FRAME_Data (ID = 0x00000042)
static void data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_PANEL_TEMP_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_PANEL_TEMP_SAT_FRAME_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_panel_temp_sat_frame_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_PANEL_TEMP_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_PANEL_TEMP_SAT_FRAME_Data (ID = 0x00000042)

// @START@ Request handler for method data_cache::set_SENSOR_PANEL_TEMP_SAT_FRAME_Data (ID = 0x00000043)
static void data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_PANEL_TEMP_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_PANEL_TEMP_SAT_FRAME_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_PANEL_TEMP_SAT_FRAME_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_PANEL_TEMP_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_PANEL_TEMP_SAT_FRAME_Data (ID = 0x00000043)

// @START@ Request handler for method data_cache::get_SENSOR_GYRO_TEMP_Data (ID = 0x00000044)
static void data_cache_get_SENSOR_GYRO_TEMP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_GYRO_TEMP_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_GYRO_TEMP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_GYRO_TEMP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_gyro_temp_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_GYRO_TEMP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_GYRO_TEMP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_GYRO_TEMP_Data (ID = 0x00000044)

// @START@ Request handler for method data_cache::set_SENSOR_GYRO_TEMP_Data (ID = 0x00000045)
static void data_cache_set_SENSOR_GYRO_TEMP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_GYRO_TEMP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_GYRO_TEMP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_GYRO_TEMP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_GYRO_TEMP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_GYRO_TEMP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_GYRO_TEMP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_GYRO_TEMP_Data (ID = 0x00000045)

// @START@ Request handler for method data_cache::get_SENSOR_GYRO_TEMP_SAT_FRAME_Data (ID = 0x00000046)
static void data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_SENSOR_GYRO_TEMP_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_SENSOR_GYRO_TEMP_SAT_FRAME_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_sensor_gyro_temp_sat_frame_data(&sOutput_data);

        respResult = data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_SENSOR_GYRO_TEMP_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_SENSOR_GYRO_TEMP_SAT_FRAME_Data (ID = 0x00000046)

// @START@ Request handler for method data_cache::set_SENSOR_GYRO_TEMP_SAT_FRAME_Data (ID = 0x00000047)
static void data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_SENSOR_GYRO_TEMP_SAT_FRAME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_SENSOR_GYRO_TEMP_SAT_FRAME_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_SENSOR_GYRO_TEMP_SAT_FRAME_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_SENSOR_GYRO_TEMP_SAT_FRAME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_SENSOR_GYRO_TEMP_SAT_FRAME_Data (ID = 0x00000047)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_OP_STATUS_COMMON_Data (ID = 0x00000048)
static void data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_OP_STATUS_COMMON_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_OP_STATUS_COMMON_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_op_status_common_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_OP_STATUS_COMMON_Data (ID = 0x00000048)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_OP_STATUS_COMMON_Data (ID = 0x00000049)
static void data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_OP_STATUS_COMMON_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_OP_STATUS_COMMON_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_OP_STATUS_COMMON_Data (ID = 0x00000049)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_OP_STATUS_APP_Data (ID = 0x0000004A)
static void data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_OP_STATUS_APP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_OP_STATUS_APP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_op_status_app_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_OP_STATUS_APP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_OP_STATUS_APP_Data (ID = 0x0000004A)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_OP_STATUS_APP_Data (ID = 0x0000004B)
static void data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_OP_STATUS_APP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_OP_STATUS_APP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_OP_STATUS_APP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_OP_STATUS_APP_Data (ID = 0x0000004B)

// @START@ Request handler for method data_cache::get_AOCS_CNTRL_REF_PARAMS_Data (ID = 0x0000004C)
static void data_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_AOCS_CNTRL_REF_PARAMS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_AOCS_CNTRL_REF_PARAMS_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_aocs_cntrl_ref_params_data(&sOutput_data);

        respResult = data_cache_get_AOCS_CNTRL_REF_PARAMS_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_AOCS_CNTRL_REF_PARAMS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_AOCS_CNTRL_REF_PARAMS_Data (ID = 0x0000004C)

// @START@ Request handler for method data_cache::set_AOCS_CNTRL_REF_PARAMS_Data (ID = 0x0000004D)
static void data_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_AOCS_CNTRL_REF_PARAMS_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_AOCS_CNTRL_REF_PARAMS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_AOCS_CNTRL_REF_PARAMS_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_AOCS_CNTRL_REF_PARAMS_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_AOCS_CNTRL_REF_PARAMS_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_AOCS_CNTRL_REF_PARAMS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_AOCS_CNTRL_REF_PARAMS_Data (ID = 0x0000004D)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_166_Data (ID = 0x0000004E)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_166_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_166_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_166_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_166_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_166_Data (ID = 0x0000004E)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_166_Data (ID = 0x0000004F)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_166_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_166_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_166_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_166_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_166_Data (ID = 0x0000004F)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_167_Data (ID = 0x00000050)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_167_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_167_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_167_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_167_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_167_Data (ID = 0x00000050)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_167_Data (ID = 0x00000051)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_167_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_167_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_167_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_167_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_167_Data (ID = 0x00000051)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_168_Data (ID = 0x00000052)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_168_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_168_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_168_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_168_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_168_Data (ID = 0x00000052)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_168_Data (ID = 0x00000053)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_168_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_168_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_168_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_168_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_168_Data (ID = 0x00000053)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_169_Data (ID = 0x00000054)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_169_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_169_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_169_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_169_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_169_Data (ID = 0x00000054)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_169_Data (ID = 0x00000055)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_169_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_169_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_169_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_169_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_169_Data (ID = 0x00000055)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_170_Data (ID = 0x00000056)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_170_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_170_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_170_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_170_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_170_Data (ID = 0x00000056)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_170_Data (ID = 0x00000057)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_170_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_170_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_170_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_170_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_170_Data (ID = 0x00000057)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_171_Data (ID = 0x00000058)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_171_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_171_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_171_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_171_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_171_Data (ID = 0x00000058)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_171_Data (ID = 0x00000059)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_171_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_171_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_171_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_171_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_171_Data (ID = 0x00000059)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_172_Data (ID = 0x0000005A)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_172_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_172_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_172_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_172_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_172_Data (ID = 0x0000005A)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_172_Data (ID = 0x0000005B)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_172_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_172_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_172_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_172_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_172_Data (ID = 0x0000005B)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_173_Data (ID = 0x0000005C)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_173_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_173_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_173_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_173_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_173_Data (ID = 0x0000005C)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_173_Data (ID = 0x0000005D)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_173_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_173_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_173_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_173_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_173_Data (ID = 0x0000005D)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_174_Data (ID = 0x0000005E)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_174_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_174_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_174_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_174_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_174_Data (ID = 0x0000005E)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_174_Data (ID = 0x0000005F)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_174_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_174_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_174_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_174_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_174_Data (ID = 0x0000005F)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_175_Data (ID = 0x00000060)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_175_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_175_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_175_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_175_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_175_Data (ID = 0x00000060)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_175_Data (ID = 0x00000061)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_175_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_175_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_175_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_175_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_175_Data (ID = 0x00000061)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_176_Data (ID = 0x00000062)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_176_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_176_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_176_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_176_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_176_Data (ID = 0x00000062)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_176_Data (ID = 0x00000063)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_176_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_176_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_176_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_176_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_176_Data (ID = 0x00000063)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_177_Data (ID = 0x00000064)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_177_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_177_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_177_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_177_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_177_Data (ID = 0x00000064)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_177_Data (ID = 0x00000065)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_177_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_177_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_177_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_177_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_177_Data (ID = 0x00000065)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_178_Data (ID = 0x00000066)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_178_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_178_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_178_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_178_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_178_Data (ID = 0x00000066)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_178_Data (ID = 0x00000067)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_178_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_178_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_178_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_178_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_178_Data (ID = 0x00000067)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_179_Data (ID = 0x00000068)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_179_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_179_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_179_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_179_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_179_Data (ID = 0x00000068)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_179_Data (ID = 0x00000069)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_179_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_179_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_179_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_179_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_179_Data (ID = 0x00000069)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_180_Data (ID = 0x0000006A)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_180_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_180_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_180_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_180_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_180_Data (ID = 0x0000006A)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_180_Data (ID = 0x0000006B)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_180_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_180_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_180_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_180_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_180_Data (ID = 0x0000006B)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_203_Data (ID = 0x0000006C)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_203_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_203_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_203_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_203_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_203_Data (ID = 0x0000006C)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_203_Data (ID = 0x0000006D)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_203_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_203_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_203_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_203_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_203_Data (ID = 0x0000006D)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_204_Data (ID = 0x0000006E)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_204_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_204_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_204_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_204_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_204_Data (ID = 0x0000006E)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_204_Data (ID = 0x0000006F)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_204_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_204_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_204_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_204_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_204_Data (ID = 0x0000006F)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_205_Data (ID = 0x00000070)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_205_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_205_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_205_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_205_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_205_Data (ID = 0x00000070)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_205_Data (ID = 0x00000071)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_205_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_205_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_205_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_205_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_205_Data (ID = 0x00000071)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_206_Data (ID = 0x00000072)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_206_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_206_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_206_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_206_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_206_Data (ID = 0x00000072)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_206_Data (ID = 0x00000073)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_206_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_206_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_206_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_206_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_206_Data (ID = 0x00000073)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_207_Data (ID = 0x00000074)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_207_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_207_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_207_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_207_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_207_Data (ID = 0x00000074)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_207_Data (ID = 0x00000075)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_207_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_207_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_207_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_207_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_207_Data (ID = 0x00000075)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_1_Data (ID = 0x00000076)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_1_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_208_1_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_1_Data (ID = 0x00000076)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_1_Data (ID = 0x00000077)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_1_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_1_Data (ID = 0x00000077)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_2_Data (ID = 0x00000078)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_2_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_208_2_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_208_2_Data (ID = 0x00000078)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_2_Data (ID = 0x00000079)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_2_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_208_2_Data (ID = 0x00000079)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_209_Data (ID = 0x0000007A)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_209_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_209_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_209_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_209_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_209_Data (ID = 0x0000007A)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_209_Data (ID = 0x0000007B)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_209_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_209_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_209_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_209_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_209_Data (ID = 0x0000007B)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_210_Data (ID = 0x0000007C)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_210_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_210_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_210_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_210_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_210_Data (ID = 0x0000007C)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_210_Data (ID = 0x0000007D)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_210_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_210_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_210_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_210_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_210_Data (ID = 0x0000007D)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_211_Data (ID = 0x0000007E)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_211_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_211_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_211_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_211_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_211_Data (ID = 0x0000007E)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_211_Data (ID = 0x0000007F)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_211_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_211_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_211_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_211_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_211_Data (ID = 0x0000007F)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_212_Data (ID = 0x00000080)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_212_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_212_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_212_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_212_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_212_Data (ID = 0x00000080)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_212_Data (ID = 0x00000081)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_212_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_212_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_212_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_212_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_212_Data (ID = 0x00000081)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_213_Data (ID = 0x00000082)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_213_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_213_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_213_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_213_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_213_Data (ID = 0x00000082)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_213_Data (ID = 0x00000083)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_213_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_213_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_213_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_213_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_213_Data (ID = 0x00000083)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_214_Data (ID = 0x00000084)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_214_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_214_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_214_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_214_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_214_Data (ID = 0x00000084)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_214_Data (ID = 0x00000085)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_214_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_214_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_214_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_214_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_214_Data (ID = 0x00000085)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_216_Data (ID = 0x00000086)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_216_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_216_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_216_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_216_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_216_Data (ID = 0x00000086)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_216_Data (ID = 0x00000087)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_216_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_216_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_216_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_216_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_216_Data (ID = 0x00000087)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_217_Data (ID = 0x00000088)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_217_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_217_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_217_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_217_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_217_Data (ID = 0x00000088)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_217_Data (ID = 0x00000089)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_217_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_217_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_217_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_217_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_217_Data (ID = 0x00000089)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_218_Data (ID = 0x0000008A)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_218_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_218_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_218_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_218_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_218_Data (ID = 0x0000008A)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_218_Data (ID = 0x0000008B)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_218_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_218_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_218_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_218_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_218_Data (ID = 0x0000008B)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_225_Data (ID = 0x0000008C)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_225_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_225_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_225_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_225_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_225_Data (ID = 0x0000008C)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_225_Data (ID = 0x0000008D)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_225_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_225_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_225_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_225_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_225_Data (ID = 0x0000008D)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_226_Data (ID = 0x0000008E)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_226_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_226_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_226_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_226_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_226_Data (ID = 0x0000008E)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_226_Data (ID = 0x0000008F)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_226_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_226_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_226_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_226_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_226_Data (ID = 0x0000008F)

// @START@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_165_Data (ID = 0x00000090)
static void data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_165_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_CUBEADCS_GEN2_TLM_FRAME_165_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_cubeadcs_gen2_tlm_frame_165_data(&sOutput_data);

        respResult = data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_165_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_CUBEADCS_GEN2_TLM_FRAME_165_Data (ID = 0x00000090)

// @START@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_165_Data (ID = 0x00000091)
static void data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_165_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_CUBEADCS_GEN2_TLM_FRAME_165_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_165_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_165_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_CUBEADCS_GEN2_TLM_FRAME_165_Data (ID = 0x00000091)

// @START@ Request handler for method data_cache::get_GNSS_TIME_Data (ID = 0x00000092)
static void data_cache_get_GNSS_TIME_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_GNSS_TIME_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_GNSS_TIME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_GNSS_TIME_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_gnss_time_data(&sOutput_data);

        respResult = data_cache_get_GNSS_TIME_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_GNSS_TIME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_GNSS_TIME_Data (ID = 0x00000092)

// @START@ Request handler for method data_cache::set_GNSS_TIME_Data (ID = 0x00000093)
static void data_cache_set_GNSS_TIME_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_GNSS_TIME_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_GNSS_TIME_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_GNSS_TIME_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_GNSS_TIME_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_GNSS_TIME_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_GNSS_TIME_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_GNSS_TIME_Data (ID = 0x00000093)

// @START@ Request handler for method data_cache::get_GNSS_BESTXYZ_Data (ID = 0x00000094)
static void data_cache_get_GNSS_BESTXYZ_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_GNSS_BESTXYZ_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_GNSS_BESTXYZ_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_GNSS_BESTXYZ_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_gnss_bestxyz_data(&sOutput_data);

        respResult = data_cache_get_GNSS_BESTXYZ_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_GNSS_BESTXYZ_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_GNSS_BESTXYZ_Data (ID = 0x00000094)

// @START@ Request handler for method data_cache::set_GNSS_BESTXYZ_Data (ID = 0x00000095)
static void data_cache_set_GNSS_BESTXYZ_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_GNSS_BESTXYZ_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_GNSS_BESTXYZ_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_GNSS_BESTXYZ_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_GNSS_BESTXYZ_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_GNSS_BESTXYZ_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_GNSS_BESTXYZ_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_GNSS_BESTXYZ_Data (ID = 0x00000095)

// @START@ Request handler for method data_cache::get_EpsOverallBatteryInfo_Data (ID = 0x00000096)
static void data_cache_get_EpsOverallBatteryInfo_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_EpsOverallBatteryInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EpsOverallBatteryInfo_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EpsOverallBatteryInfo_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_epsoverallbatteryinfo_data(&sOutput_data);

        respResult = data_cache_get_EpsOverallBatteryInfo_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPSOVERALLBATTERYINFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EpsOverallBatteryInfo_Data (ID = 0x00000096)

// @START@ Request handler for method data_cache::set_EpsOverallBatteryInfo_Data (ID = 0x00000097)
static void data_cache_set_EpsOverallBatteryInfo_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EpsOverallBatteryInfo_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EpsOverallBatteryInfo_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EpsOverallBatteryInfo_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPSOVERALLBATTERYINFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EpsOverallBatteryInfo_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPSOVERALLBATTERYINFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EpsOverallBatteryInfo_Data (ID = 0x00000097)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_BP_INFO_Data (ID = 0x00000098)
static void data_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0BatteryInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_BP_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_BP_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_bp_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_BP_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_BP_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_BP_INFO_Data (ID = 0x00000098)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_BP_INFO_Data (ID = 0x00000099)
static void data_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BP_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_BP_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_BP_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_BP_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_BP_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_BP_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_BP_INFO_Data (ID = 0x00000099)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data (ID = 0x0000009A)
static void data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_device_health_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data (ID = 0x0000009A)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data (ID = 0x0000009B)
static void data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_Data (ID = 0x0000009B)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_INA_SENSOR1_Data (ID = 0x0000009C)
static void data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0InaSensors1Type_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_INA_SENSOR1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_INA_SENSOR1_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_ina_sensor1_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_INA_SENSOR1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_INA_SENSOR1_Data (ID = 0x0000009C)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_INA_SENSOR1_Data (ID = 0x0000009D)
static void data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_INA_SENSOR1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_INA_SENSOR1_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_INA_SENSOR1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_INA_SENSOR1_Data (ID = 0x0000009D)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_INA_SENSOR2_Data (ID = 0x0000009E)
static void data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0InaSensors2Type_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_INA_SENSOR2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_INA_SENSOR2_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_ina_sensor2_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_INA_SENSOR2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_INA_SENSOR2_Data (ID = 0x0000009E)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_INA_SENSOR2_Data (ID = 0x0000009F)
static void data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_INA_SENSOR2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_INA_SENSOR2_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_INA_SENSOR2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_INA_SENSOR2_Data (ID = 0x0000009F)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_BALANCER_INFO_Data (ID = 0x000000A0)
static void data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0BalancerInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_BALANCER_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_BALANCER_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_balancer_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_BALANCER_INFO_Data (ID = 0x000000A0)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_BALANCER_INFO_Data (ID = 0x000000A1)
static void data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_BALANCER_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_BALANCER_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_BALANCER_INFO_Data (ID = 0x000000A1)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_BALANCER_STATUS_Data (ID = 0x000000A2)
static void data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0BalancerStatusType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_BALANCER_STATUS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_BALANCER_STATUS_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_balancer_status_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_STATUS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_BALANCER_STATUS_Data (ID = 0x000000A2)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_BALANCER_STATUS_Data (ID = 0x000000A3)
static void data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_BALANCER_STATUS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_BALANCER_STATUS_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_STATUS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_BALANCER_STATUS_Data (ID = 0x000000A3)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data (ID = 0x000000A4)
static void data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_balancer_cells_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data (ID = 0x000000A4)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data (ID = 0x000000A5)
static void data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_BALANCER_CELLS_INFO_Data (ID = 0x000000A5)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_XP_Data (ID = 0x000000A6)
static void data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0ChargerXpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_CHARGER_XP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_CHARGER_XP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_charger_xp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_XP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_XP_Data (ID = 0x000000A6)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_XP_Data (ID = 0x000000A7)
static void data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_CHARGER_XP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_CHARGER_XP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_XP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_XP_Data (ID = 0x000000A7)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_XR_Data (ID = 0x000000A8)
static void data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0ChargerXrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_CHARGER_XR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_CHARGER_XR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_charger_xr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_XR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_XR_Data (ID = 0x000000A8)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_XR_Data (ID = 0x000000A9)
static void data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_CHARGER_XR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_CHARGER_XR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_XR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_XR_Data (ID = 0x000000A9)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_YP_Data (ID = 0x000000AA)
static void data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0ChargerYpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_CHARGER_YP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_CHARGER_YP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_charger_yp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_YP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_YP_Data (ID = 0x000000AA)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_YP_Data (ID = 0x000000AB)
static void data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_CHARGER_YP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_CHARGER_YP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_YP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_YP_Data (ID = 0x000000AB)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_YR_Data (ID = 0x000000AC)
static void data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0ChargerYrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_CHARGER_YR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_CHARGER_YR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_charger_yr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_YR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_YR_Data (ID = 0x000000AC)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_YR_Data (ID = 0x000000AD)
static void data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_CHARGER_YR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_CHARGER_YR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_YR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_YR_Data (ID = 0x000000AD)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_ZP_Data (ID = 0x000000AE)
static void data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0ChargerZpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_CHARGER_ZP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_CHARGER_ZP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_charger_zp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_ZP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_ZP_Data (ID = 0x000000AE)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_ZP_Data (ID = 0x000000AF)
static void data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_CHARGER_ZP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_CHARGER_ZP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_ZP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_ZP_Data (ID = 0x000000AF)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_ZR_Data (ID = 0x000000B0)
static void data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst0ChargerZrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST0_CHARGER_ZR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST0_CHARGER_ZR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst0_charger_zr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_ZR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST0_CHARGER_ZR_Data (ID = 0x000000B0)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_ZR_Data (ID = 0x000000B1)
static void data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST0_CHARGER_ZR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST0_CHARGER_ZR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_ZR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST0_CHARGER_ZR_Data (ID = 0x000000B1)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_BP_INFO_Data (ID = 0x000000B2)
static void data_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1BatteryInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_BP_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_BP_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_bp_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_BP_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_BP_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_BP_INFO_Data (ID = 0x000000B2)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_BP_INFO_Data (ID = 0x000000B3)
static void data_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BP_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_BP_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_BP_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_BP_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_BP_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_BP_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_BP_INFO_Data (ID = 0x000000B3)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data (ID = 0x000000B4)
static void data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_device_health_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data (ID = 0x000000B4)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data (ID = 0x000000B5)
static void data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_Data (ID = 0x000000B5)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_INA_SENSOR1_Data (ID = 0x000000B6)
static void data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1InaSensors1Type_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_INA_SENSOR1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_INA_SENSOR1_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_ina_sensor1_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_INA_SENSOR1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_INA_SENSOR1_Data (ID = 0x000000B6)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_INA_SENSOR1_Data (ID = 0x000000B7)
static void data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_INA_SENSOR1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_INA_SENSOR1_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_INA_SENSOR1_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_INA_SENSOR1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_INA_SENSOR1_Data (ID = 0x000000B7)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_INA_SENSOR2_Data (ID = 0x000000B8)
static void data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1InaSensors2Type_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_INA_SENSOR2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_INA_SENSOR2_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_ina_sensor2_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_INA_SENSOR2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_INA_SENSOR2_Data (ID = 0x000000B8)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_INA_SENSOR2_Data (ID = 0x000000B9)
static void data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_INA_SENSOR2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_INA_SENSOR2_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_INA_SENSOR2_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_INA_SENSOR2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_INA_SENSOR2_Data (ID = 0x000000B9)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_BALANCER_INFO_Data (ID = 0x000000BA)
static void data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1BalancerInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_BALANCER_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_BALANCER_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_balancer_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_BALANCER_INFO_Data (ID = 0x000000BA)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_BALANCER_INFO_Data (ID = 0x000000BB)
static void data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_BALANCER_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_BALANCER_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_BALANCER_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_BALANCER_INFO_Data (ID = 0x000000BB)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_BALANCER_STATUS_Data (ID = 0x000000BC)
static void data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1BalancerStatusType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_BALANCER_STATUS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_BALANCER_STATUS_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_balancer_status_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_STATUS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_BALANCER_STATUS_Data (ID = 0x000000BC)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_BALANCER_STATUS_Data (ID = 0x000000BD)
static void data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_BALANCER_STATUS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_BALANCER_STATUS_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_BALANCER_STATUS_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_STATUS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_BALANCER_STATUS_Data (ID = 0x000000BD)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data (ID = 0x000000BE)
static void data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_balancer_cells_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data (ID = 0x000000BE)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data (ID = 0x000000BF)
static void data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_BALANCER_CELLS_INFO_Data (ID = 0x000000BF)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_XP_Data (ID = 0x000000C0)
static void data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1ChargerXpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_CHARGER_XP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_CHARGER_XP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_charger_xp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_XP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_XP_Data (ID = 0x000000C0)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_XP_Data (ID = 0x000000C1)
static void data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_CHARGER_XP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_CHARGER_XP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_XP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_XP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_XP_Data (ID = 0x000000C1)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_XR_Data (ID = 0x000000C2)
static void data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1ChargerXrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_CHARGER_XR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_CHARGER_XR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_charger_xr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_XR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_XR_Data (ID = 0x000000C2)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_XR_Data (ID = 0x000000C3)
static void data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_CHARGER_XR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_CHARGER_XR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_XR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_XR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_XR_Data (ID = 0x000000C3)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_YP_Data (ID = 0x000000C4)
static void data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1ChargerYpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_CHARGER_YP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_CHARGER_YP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_charger_yp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_YP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_YP_Data (ID = 0x000000C4)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_YP_Data (ID = 0x000000C5)
static void data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_CHARGER_YP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_CHARGER_YP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_YP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_YP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_YP_Data (ID = 0x000000C5)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_YR_Data (ID = 0x000000C6)
static void data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1ChargerYrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_CHARGER_YR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_CHARGER_YR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_charger_yr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_YR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_YR_Data (ID = 0x000000C6)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_YR_Data (ID = 0x000000C7)
static void data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_CHARGER_YR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_CHARGER_YR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_YR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_YR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_YR_Data (ID = 0x000000C7)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_ZP_Data (ID = 0x000000C8)
static void data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1ChargerZpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_CHARGER_ZP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_CHARGER_ZP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_charger_zp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_ZP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_ZP_Data (ID = 0x000000C8)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_ZP_Data (ID = 0x000000C9)
static void data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_CHARGER_ZP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_CHARGER_ZP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_ZP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_ZP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_ZP_Data (ID = 0x000000C9)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_ZR_Data (ID = 0x000000CA)
static void data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst1ChargerZrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST1_CHARGER_ZR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST1_CHARGER_ZR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst1_charger_zr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_ZR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST1_CHARGER_ZR_Data (ID = 0x000000CA)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_ZR_Data (ID = 0x000000CB)
static void data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST1_CHARGER_ZR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST1_CHARGER_ZR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_ZR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_ZR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST1_CHARGER_ZR_Data (ID = 0x000000CB)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_BP_INFO_Data (ID = 0x000000CC)
static void data_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2BatteryInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_BP_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_BP_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_bp_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_BP_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_BP_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_BP_INFO_Data (ID = 0x000000CC)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_BP_INFO_Data (ID = 0x000000CD)
static void data_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BP_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_BP_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_BP_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_BP_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_BP_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_BP_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_BP_INFO_Data (ID = 0x000000CD)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data (ID = 0x000000CE)
static void data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_device_health_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data (ID = 0x000000CE)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data (ID = 0x000000CF)
static void data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_Data (ID = 0x000000CF)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_INA_SENSOR1_Data (ID = 0x000000D0)
static void data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2InaSensors1Type_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_INA_SENSOR1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_INA_SENSOR1_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_ina_sensor1_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_INA_SENSOR1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_INA_SENSOR1_Data (ID = 0x000000D0)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_INA_SENSOR1_Data (ID = 0x000000D1)
static void data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_INA_SENSOR1_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_INA_SENSOR1_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_INA_SENSOR1_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_INA_SENSOR1_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_INA_SENSOR1_Data (ID = 0x000000D1)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_INA_SENSOR2_Data (ID = 0x000000D2)
static void data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2InaSensors2Type_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_INA_SENSOR2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_INA_SENSOR2_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_ina_sensor2_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_INA_SENSOR2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_INA_SENSOR2_Data (ID = 0x000000D2)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_INA_SENSOR2_Data (ID = 0x000000D3)
static void data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_INA_SENSOR2_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_INA_SENSOR2_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_INA_SENSOR2_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_INA_SENSOR2_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_INA_SENSOR2_Data (ID = 0x000000D3)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_BALANCER_INFO_Data (ID = 0x000000D4)
static void data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2BalancerInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_BALANCER_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_BALANCER_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_balancer_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_BALANCER_INFO_Data (ID = 0x000000D4)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_BALANCER_INFO_Data (ID = 0x000000D5)
static void data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_BALANCER_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_BALANCER_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_BALANCER_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_BALANCER_INFO_Data (ID = 0x000000D5)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_BALANCER_STATUS_Data (ID = 0x000000D6)
static void data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2BalancerStatusType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_BALANCER_STATUS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_BALANCER_STATUS_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_balancer_status_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_STATUS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_BALANCER_STATUS_Data (ID = 0x000000D6)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_BALANCER_STATUS_Data (ID = 0x000000D7)
static void data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_BALANCER_STATUS_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_BALANCER_STATUS_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_BALANCER_STATUS_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_STATUS_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_BALANCER_STATUS_Data (ID = 0x000000D7)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data (ID = 0x000000D8)
static void data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_balancer_cells_info_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data (ID = 0x000000D8)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data (ID = 0x000000D9)
static void data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_BALANCER_CELLS_INFO_Data (ID = 0x000000D9)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_XP_Data (ID = 0x000000DA)
static void data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2ChargerXpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_CHARGER_XP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_CHARGER_XP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_charger_xp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_XP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_XP_Data (ID = 0x000000DA)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_XP_Data (ID = 0x000000DB)
static void data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_CHARGER_XP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_CHARGER_XP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_XP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_XP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_XP_Data (ID = 0x000000DB)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_XR_Data (ID = 0x000000DC)
static void data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2ChargerXrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_CHARGER_XR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_CHARGER_XR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_charger_xr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_XR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_XR_Data (ID = 0x000000DC)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_XR_Data (ID = 0x000000DD)
static void data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_CHARGER_XR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_CHARGER_XR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_XR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_XR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_XR_Data (ID = 0x000000DD)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_YP_Data (ID = 0x000000DE)
static void data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2ChargerYpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_CHARGER_YP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_CHARGER_YP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_charger_yp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_YP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_YP_Data (ID = 0x000000DE)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_YP_Data (ID = 0x000000DF)
static void data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_CHARGER_YP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_CHARGER_YP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_YP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_YP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_YP_Data (ID = 0x000000DF)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_YR_Data (ID = 0x000000E0)
static void data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2ChargerYrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_CHARGER_YR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_CHARGER_YR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_charger_yr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_YR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_YR_Data (ID = 0x000000E0)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_YR_Data (ID = 0x000000E1)
static void data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_CHARGER_YR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_CHARGER_YR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_YR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_YR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_YR_Data (ID = 0x000000E1)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_ZP_Data (ID = 0x000000E2)
static void data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2ChargerZpType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_CHARGER_ZP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_CHARGER_ZP_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_charger_zp_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_ZP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_ZP_Data (ID = 0x000000E2)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_ZP_Data (ID = 0x000000E3)
static void data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_CHARGER_ZP_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_CHARGER_ZP_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_ZP_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_ZP_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_ZP_Data (ID = 0x000000E3)

// @START@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_ZR_Data (ID = 0x000000E4)
static void data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_Eps2Inst2ChargerZrType_t sOutput_data;
    DATA_CACHE_DCDataStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::get_EPS2_BP_INST2_CHARGER_ZR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::get_EPS2_BP_INST2_CHARGER_ZR_Data@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        eStatus = dc_get_eps2_bp_inst2_charger_zr_data(&sOutput_data);

        respResult = data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataResp(
                        &respCtx,
                        &sOutput_data,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_ZR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::get_EPS2_BP_INST2_CHARGER_ZR_Data (ID = 0x000000E4)

// @START@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_ZR_Data (ID = 0x000000E5)
static void data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandlerImpl(ReqContext_t *pReqCtx,
            const data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    DATA_CACHE_DCDataUpdateStatus_t eStatus;

    // @USER_VAR_SECTION_START@data_cache::set_EPS2_BP_INST2_CHARGER_ZR_Data@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@data_cache::set_EPS2_BP_INST2_CHARGER_ZR_Data@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        dc_set_raw_data(DC_DATA_INPUT_EXTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_ZR_DATA, &pRequestData->sInput_data, sizeof(pRequestData->sInput_data));

        eStatus = DCDATA_UPDATE_STATUS_OK;

        respResult = data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE, DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_ZR_DATA_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method data_cache::set_EPS2_BP_INST2_CHARGER_ZR_Data (ID = 0x000000E5)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void data_cacheServerAppInit(void)
{
    data_cache_registerServerApi(&data_cacheServerApiCtx);
}
