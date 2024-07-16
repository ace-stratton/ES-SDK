/*!
********************************************************************************************
* @file FP_data_cacheProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_DATA_CACHEPROTOCOLSERVER_H__
#define __FP_DATA_CACHEPROTOCOLSERVER_H__

#include "FP_data_cacheProtocolTypes.h"

typedef void (*pfdata_cache_get_OBC_0_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_OBC_0_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_OBC_0_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ADCS_0_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ADCS_0_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ADCS_0_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ADCS_1_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ADCS_1_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ADCS_1_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ADCS_2_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ADCS_2_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ADCS_2_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS_0_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS_0_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS_0_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SSP_0_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SSP_0_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SSP_0_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SSP_1_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SSP_1_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SSP_1_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SSP_2_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SSP_2_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SSP_2_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_AOCS_CNTRL_TLM_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_AOCS_CNTRL_TLM_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_AOCS_CNTRL_TLM_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_OS_Task_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_OS_Task_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_OS_Task_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SSP_3_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SSP_3_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SSP_3_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_MAG_PRIMARY_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_MAG_SECONDARY_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_GYRO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_GYRO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_GYRO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_COARSE_SUN_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_COARSE_SUN_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_COARSE_SUN_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ES_ADCS_SENSOR_GYRO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ES_ADCS_SENSOR_CSS_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ConOpsFlags_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ConOpsFlags_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ConOpsFlags_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_AOCS_CNTRL_SYS_STATE_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ADCS_3_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ADCS_3_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ADCS_3_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_ADCS_4_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_ADCS_4_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_ADCS_4_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS_9_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS_9_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS_9_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS_10_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS_10_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS_10_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS_14_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS_14_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS_14_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_ACC_PRIMARY_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_ACC_SECONDARY_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_PANEL_TEMP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_PANEL_TEMP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_PANEL_TEMP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_GYRO_TEMP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_GYRO_TEMP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_GYRO_TEMP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_AOCS_CNTRL_REF_PARAMS_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_GNSS_TIME_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_GNSS_TIME_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_GNSS_TIME_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_GNSS_BESTXYZ_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_GNSS_BESTXYZ_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_GNSS_BESTXYZ_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EpsOverallBatteryInfo_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EpsOverallBatteryInfo_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EpsOverallBatteryInfo_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_BP_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_BP_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_BP_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataRequestData_t *pRequestData);
typedef void (*pfdata_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfdata_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler_t)(ReqContext_t *ctx, data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataRequestData_t *pRequestData);

typedef struct {
    pfdata_cache_get_OBC_0_DataRequestHandler_t data_cache_get_OBC_0_DataRequestHandler;
    pfdata_cache_set_OBC_0_DataRequestHandler_t data_cache_set_OBC_0_DataRequestHandler;
    pfdata_cache_get_ADCS_0_DataRequestHandler_t data_cache_get_ADCS_0_DataRequestHandler;
    pfdata_cache_set_ADCS_0_DataRequestHandler_t data_cache_set_ADCS_0_DataRequestHandler;
    pfdata_cache_get_ADCS_1_DataRequestHandler_t data_cache_get_ADCS_1_DataRequestHandler;
    pfdata_cache_set_ADCS_1_DataRequestHandler_t data_cache_set_ADCS_1_DataRequestHandler;
    pfdata_cache_get_ADCS_2_DataRequestHandler_t data_cache_get_ADCS_2_DataRequestHandler;
    pfdata_cache_set_ADCS_2_DataRequestHandler_t data_cache_set_ADCS_2_DataRequestHandler;
    pfdata_cache_get_EPS_0_DataRequestHandler_t data_cache_get_EPS_0_DataRequestHandler;
    pfdata_cache_set_EPS_0_DataRequestHandler_t data_cache_set_EPS_0_DataRequestHandler;
    pfdata_cache_get_SSP_0_DataRequestHandler_t data_cache_get_SSP_0_DataRequestHandler;
    pfdata_cache_set_SSP_0_DataRequestHandler_t data_cache_set_SSP_0_DataRequestHandler;
    pfdata_cache_get_SSP_1_DataRequestHandler_t data_cache_get_SSP_1_DataRequestHandler;
    pfdata_cache_set_SSP_1_DataRequestHandler_t data_cache_set_SSP_1_DataRequestHandler;
    pfdata_cache_get_SSP_2_DataRequestHandler_t data_cache_get_SSP_2_DataRequestHandler;
    pfdata_cache_set_SSP_2_DataRequestHandler_t data_cache_set_SSP_2_DataRequestHandler;
    pfdata_cache_get_AOCS_CNTRL_TLM_DataRequestHandler_t data_cache_get_AOCS_CNTRL_TLM_DataRequestHandler;
    pfdata_cache_set_AOCS_CNTRL_TLM_DataRequestHandler_t data_cache_set_AOCS_CNTRL_TLM_DataRequestHandler;
    pfdata_cache_get_OS_Task_DataRequestHandler_t data_cache_get_OS_Task_DataRequestHandler;
    pfdata_cache_set_OS_Task_DataRequestHandler_t data_cache_set_OS_Task_DataRequestHandler;
    pfdata_cache_get_SSP_3_DataRequestHandler_t data_cache_get_SSP_3_DataRequestHandler;
    pfdata_cache_set_SSP_3_DataRequestHandler_t data_cache_set_SSP_3_DataRequestHandler;
    pfdata_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandler_t data_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandler;
    pfdata_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandler_t data_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandler;
    pfdata_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandler_t data_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandler;
    pfdata_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandler_t data_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandler;
    pfdata_cache_get_SENSOR_GYRO_DataRequestHandler_t data_cache_get_SENSOR_GYRO_DataRequestHandler;
    pfdata_cache_set_SENSOR_GYRO_DataRequestHandler_t data_cache_set_SENSOR_GYRO_DataRequestHandler;
    pfdata_cache_get_SENSOR_COARSE_SUN_DataRequestHandler_t data_cache_get_SENSOR_COARSE_SUN_DataRequestHandler;
    pfdata_cache_set_SENSOR_COARSE_SUN_DataRequestHandler_t data_cache_set_SENSOR_COARSE_SUN_DataRequestHandler;
    pfdata_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler_t data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler;
    pfdata_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler_t data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler;
    pfdata_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler_t data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler;
    pfdata_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler_t data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler;
    pfdata_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandler_t data_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandler;
    pfdata_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandler_t data_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandler;
    pfdata_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandler_t data_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandler;
    pfdata_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandler_t data_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandler;
    pfdata_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler_t data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler;
    pfdata_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler_t data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler;
    pfdata_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler_t data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler;
    pfdata_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler_t data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler;
    pfdata_cache_get_ConOpsFlags_DataRequestHandler_t data_cache_get_ConOpsFlags_DataRequestHandler;
    pfdata_cache_set_ConOpsFlags_DataRequestHandler_t data_cache_set_ConOpsFlags_DataRequestHandler;
    pfdata_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandler_t data_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandler;
    pfdata_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandler_t data_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandler;
    pfdata_cache_get_ADCS_3_DataRequestHandler_t data_cache_get_ADCS_3_DataRequestHandler;
    pfdata_cache_set_ADCS_3_DataRequestHandler_t data_cache_set_ADCS_3_DataRequestHandler;
    pfdata_cache_get_ADCS_4_DataRequestHandler_t data_cache_get_ADCS_4_DataRequestHandler;
    pfdata_cache_set_ADCS_4_DataRequestHandler_t data_cache_set_ADCS_4_DataRequestHandler;
    pfdata_cache_get_EPS_9_DataRequestHandler_t data_cache_get_EPS_9_DataRequestHandler;
    pfdata_cache_set_EPS_9_DataRequestHandler_t data_cache_set_EPS_9_DataRequestHandler;
    pfdata_cache_get_EPS_10_DataRequestHandler_t data_cache_get_EPS_10_DataRequestHandler;
    pfdata_cache_set_EPS_10_DataRequestHandler_t data_cache_set_EPS_10_DataRequestHandler;
    pfdata_cache_get_EPS_14_DataRequestHandler_t data_cache_get_EPS_14_DataRequestHandler;
    pfdata_cache_set_EPS_14_DataRequestHandler_t data_cache_set_EPS_14_DataRequestHandler;
    pfdata_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandler_t data_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandler;
    pfdata_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandler_t data_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandler;
    pfdata_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandler_t data_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandler;
    pfdata_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandler_t data_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandler;
    pfdata_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler_t data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler;
    pfdata_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler_t data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler;
    pfdata_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler_t data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler;
    pfdata_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler_t data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler;
    pfdata_cache_get_SENSOR_PANEL_TEMP_DataRequestHandler_t data_cache_get_SENSOR_PANEL_TEMP_DataRequestHandler;
    pfdata_cache_set_SENSOR_PANEL_TEMP_DataRequestHandler_t data_cache_set_SENSOR_PANEL_TEMP_DataRequestHandler;
    pfdata_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler_t data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler;
    pfdata_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler_t data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler;
    pfdata_cache_get_SENSOR_GYRO_TEMP_DataRequestHandler_t data_cache_get_SENSOR_GYRO_TEMP_DataRequestHandler;
    pfdata_cache_set_SENSOR_GYRO_TEMP_DataRequestHandler_t data_cache_set_SENSOR_GYRO_TEMP_DataRequestHandler;
    pfdata_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler_t data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler;
    pfdata_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler_t data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler;
    pfdata_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandler_t data_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandler;
    pfdata_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandler_t data_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler;
    pfdata_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler_t data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler;
    pfdata_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler_t data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler;
    pfdata_cache_get_GNSS_TIME_DataRequestHandler_t data_cache_get_GNSS_TIME_DataRequestHandler;
    pfdata_cache_set_GNSS_TIME_DataRequestHandler_t data_cache_set_GNSS_TIME_DataRequestHandler;
    pfdata_cache_get_GNSS_BESTXYZ_DataRequestHandler_t data_cache_get_GNSS_BESTXYZ_DataRequestHandler;
    pfdata_cache_set_GNSS_BESTXYZ_DataRequestHandler_t data_cache_set_GNSS_BESTXYZ_DataRequestHandler;
    pfdata_cache_get_EpsOverallBatteryInfo_DataRequestHandler_t data_cache_get_EpsOverallBatteryInfo_DataRequestHandler;
    pfdata_cache_set_EpsOverallBatteryInfo_DataRequestHandler_t data_cache_set_EpsOverallBatteryInfo_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler_t data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler_t data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler_t data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler_t data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler;
    pfdata_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler_t data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler;
    pfdata_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler_t data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler;
} data_cache_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_data_cacheProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void data_cache_registerServerApi(data_cache_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_data_cacheProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t data_cache_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes data_cache_get_OBC_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_OBC_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_OBC_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ADCS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ADCS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ADCS_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_1_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ADCS_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ADCS_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_2_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ADCS_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SSP_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SSP_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SSP_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_1_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SSP_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SSP_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_2_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SSP_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_AOCS_CNTRL_TLM_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_AOCS_CNTRL_TLM_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_AOCS_CNTRL_TLM_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_OS_Task_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_TaskStats_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_OS_Task_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SSP_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_3_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SSP_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_MAG_PRIMARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_MAG_SECONDARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_GYRO_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_COARSE_SUN_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_COARSE_SUN_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_COARSE_SUN_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_GYRO_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_CSS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_CSS_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_CSS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ConOpsFlags_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ConOpsFlags_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ConOpsFlags_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_AOCS_CNTRL_SYS_STATE_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_AOCS_CNTRL_SYS_STATE_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ADCS_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_3_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ADCS_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_ADCS_4_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_4_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_ADCS_4_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS_9_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_9_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS_9_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS_10_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_10_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS_10_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS_14_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_14_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS_14_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_PRIMARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_SECONDARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_PANEL_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_PANEL_TEMP_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_PANEL_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_GYRO_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_GYRO_TEMP_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_GYRO_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_AOCS_CNTRL_REF_PARAMS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_AOCS_CNTRL_REF_PARAMS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_GNSS_TIME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_GNSS_TIME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_GNSS_TIME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_GNSS_BESTXYZ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_GNSS_BESTXYZ_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_GNSS_BESTXYZ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EpsOverallBatteryInfo_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EpsOverallBatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EpsOverallBatteryInfo_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0InaSensors1Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0InaSensors2Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BalancerInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BalancerStatusType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerXpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerXrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerYpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerYrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerZpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerZrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1InaSensors1Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1InaSensors2Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BalancerInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BalancerStatusType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerXpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerXrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerYpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerYrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerZpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerZrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2InaSensors1Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2InaSensors2Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BalancerInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BalancerStatusType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerXpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerXrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerYpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerYrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerZpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerZrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
);

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
);


#endif  // #ifndef __FP_DATA_CACHEPROTOCOLSERVER_H__
