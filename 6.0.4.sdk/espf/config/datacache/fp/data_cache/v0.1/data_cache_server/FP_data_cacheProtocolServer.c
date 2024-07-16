/*!
********************************************************************************************
* @file FP_data_cacheProtocolServer.c
* @brief ESSA Stack server-side implementation
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
#include "FP_common/FP_ProtocolServerCommon.h"

#define data_cache_PROTOCOL_VERSION_MAJOR   ((uint8_t) 0)
#define data_cache_PROTOCOL_VERSION_MINOR   ((uint8_t) 1)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_OBC_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_OBC_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_OBC_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_OBC_0_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_OBC_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_OBC_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_OBC_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ADCS_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ADCS_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ADCS_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_0_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ADCS_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ADCS_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ADCS_1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ADCS_1_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ADCS_1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_1_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ADCS_1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_1_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ADCS_1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ADCS_2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ADCS_2_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ADCS_2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_2_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ADCS_2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_2_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ADCS_2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_0_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SSP_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SSP_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SSP_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_0_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SSP_0_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_0_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SSP_0_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SSP_1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SSP_1_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SSP_1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_1_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SSP_1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_1_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SSP_1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SSP_2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SSP_2_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SSP_2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_2_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SSP_2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_2_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SSP_2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_AOCS_CNTRL_TLM_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_AOCS_CNTRL_TLM_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_AOCS_CNTRL_TLM_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_AOCS_CNTRL_TLM_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_AOCS_CNTRL_TLM_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_AOCS_CNTRL_TLM_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_AOCS_CNTRL_TLM_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_OS_Task_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_OS_Task_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_OS_Task_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_OS_Task_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_OS_Task_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_OS_Task_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_OS_Task_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SSP_3_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SSP_3_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SSP_3_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_3_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SSP_3_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SSP_3_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SSP_3_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_MAG_PRIMARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_MAG_PRIMARY_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_MAG_PRIMARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_MAG_SECONDARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_MAG_SECONDARY_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_MAG_SECONDARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_GYRO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_GYRO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_GYRO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_GYRO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_GYRO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_GYRO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_GYRO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_COARSE_SUN_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_COARSE_SUN_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_COARSE_SUN_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_COARSE_SUN_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_COARSE_SUN_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_COARSE_SUN_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_COARSE_SUN_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ES_ADCS_SENSOR_GYRO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_GYRO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_GYRO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ES_ADCS_SENSOR_CSS_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_CSS_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_SENSOR_CSS_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ConOpsFlags_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ConOpsFlags_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ConOpsFlags_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ConOpsFlags_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ConOpsFlags_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ConOpsFlags_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ConOpsFlags_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_AOCS_CNTRL_SYS_STATE_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_AOCS_CNTRL_SYS_STATE_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_AOCS_CNTRL_SYS_STATE_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ADCS_3_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ADCS_3_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ADCS_3_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_3_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ADCS_3_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_3_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ADCS_3_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_ADCS_4_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_ADCS_4_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_ADCS_4_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_4_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_ADCS_4_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_ADCS_4_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_ADCS_4_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS_9_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS_9_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS_9_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_9_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS_9_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_9_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS_9_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS_10_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS_10_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS_10_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_10_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS_10_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_10_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS_10_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS_14_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS_14_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS_14_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_14_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS_14_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS_14_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS_14_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_ACC_PRIMARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_PRIMARY_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_PRIMARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_ACC_SECONDARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_SECONDARY_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_SECONDARY_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_PANEL_TEMP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_PANEL_TEMP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_PANEL_TEMP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_PANEL_TEMP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_PANEL_TEMP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_PANEL_TEMP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_PANEL_TEMP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_GYRO_TEMP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_GYRO_TEMP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_GYRO_TEMP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_GYRO_TEMP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_GYRO_TEMP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_GYRO_TEMP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_GYRO_TEMP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_AOCS_CNTRL_REF_PARAMS_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_AOCS_CNTRL_REF_PARAMS_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_AOCS_CNTRL_REF_PARAMS_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_GNSS_TIME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_GNSS_TIME_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_GNSS_TIME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_GNSS_TIME_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_GNSS_TIME_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_GNSS_TIME_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_GNSS_TIME_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_GNSS_BESTXYZ_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_GNSS_BESTXYZ_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_GNSS_BESTXYZ_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_GNSS_BESTXYZ_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_GNSS_BESTXYZ_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_GNSS_BESTXYZ_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_GNSS_BESTXYZ_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EpsOverallBatteryInfo_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EpsOverallBatteryInfo_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EpsOverallBatteryInfo_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EpsOverallBatteryInfo_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EpsOverallBatteryInfo_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EpsOverallBatteryInfo_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EpsOverallBatteryInfo_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_BP_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BP_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BP_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_BP_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BP_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BP_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_BP_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BP_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BP_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataResponseData_t data;
} PACKED_STRUCT data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataRequestData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataResponseData_t data;
} PACKED_STRUCT data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_OBC_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_OBC_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ADCS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ADCS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ADCS_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ADCS_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ADCS_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ADCS_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SSP_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SSP_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SSP_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SSP_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SSP_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SSP_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_AOCS_CNTRL_TLM_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_AOCS_CNTRL_TLM_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_OS_Task_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_OS_Task_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SSP_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SSP_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_COARSE_SUN_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_COARSE_SUN_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ES_ADCS_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ES_ADCS_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ES_ADCS_SENSOR_CSS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ES_ADCS_SENSOR_CSS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ES_ADCS_ESTIMATES_BDOT_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ES_ADCS_ESTIMATES_BDOT_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ES_ADCS_CONTROL_VALUES_MTQ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ES_ADCS_CONTROL_VALUES_MTQ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ConOpsFlags_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ConOpsFlags_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_AOCS_CNTRL_SYS_STATE_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_AOCS_CNTRL_SYS_STATE_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ADCS_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ADCS_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_ADCS_4_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_ADCS_4_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS_9_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS_9_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS_10_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS_10_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS_14_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS_14_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_ACC_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_ACC_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_ACC_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_ACC_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_PANEL_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_PANEL_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_GYRO_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_GYRO_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_OP_STATUS_APP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_OP_STATUS_APP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_AOCS_CNTRL_REF_PARAMS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_AOCS_CNTRL_REF_PARAMS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_166_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_166_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_167_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_167_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_168_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_168_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_169_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_169_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_170_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_170_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_171_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_171_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_172_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_172_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_173_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_173_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_174_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_174_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_175_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_175_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_176_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_176_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_177_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_177_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_178_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_178_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_179_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_179_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_180_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_180_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_203_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_203_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_204_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_204_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_205_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_205_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_206_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_206_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_207_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_207_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_209_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_209_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_210_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_210_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_211_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_211_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_212_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_212_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_213_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_213_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_214_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_214_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_216_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_216_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_217_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_217_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_218_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_218_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_225_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_225_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_226_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_226_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_CUBEADCS_GEN2_TLM_FRAME_165_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_CUBEADCS_GEN2_TLM_FRAME_165_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_GNSS_TIME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_GNSS_TIME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_GNSS_BESTXYZ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_GNSS_BESTXYZ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EpsOverallBatteryInfo_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EpsOverallBatteryInfo_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST0_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST0_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST1_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST1_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_EPS2_BP_INST2_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_set_EPS2_BP_INST2_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_data_cacheProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static data_cache_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { DATA_CACHE_GET_OBC_0_DATA_FUNC_ID, fs_get_OBC_0_DataReq },
    { DATA_CACHE_SET_OBC_0_DATA_FUNC_ID, fs_set_OBC_0_DataReq },
    { DATA_CACHE_GET_ADCS_0_DATA_FUNC_ID, fs_get_ADCS_0_DataReq },
    { DATA_CACHE_SET_ADCS_0_DATA_FUNC_ID, fs_set_ADCS_0_DataReq },
    { DATA_CACHE_GET_ADCS_1_DATA_FUNC_ID, fs_get_ADCS_1_DataReq },
    { DATA_CACHE_SET_ADCS_1_DATA_FUNC_ID, fs_set_ADCS_1_DataReq },
    { DATA_CACHE_GET_ADCS_2_DATA_FUNC_ID, fs_get_ADCS_2_DataReq },
    { DATA_CACHE_SET_ADCS_2_DATA_FUNC_ID, fs_set_ADCS_2_DataReq },
    { DATA_CACHE_GET_EPS_0_DATA_FUNC_ID, fs_get_EPS_0_DataReq },
    { DATA_CACHE_SET_EPS_0_DATA_FUNC_ID, fs_set_EPS_0_DataReq },
    { DATA_CACHE_GET_SSP_0_DATA_FUNC_ID, fs_get_SSP_0_DataReq },
    { DATA_CACHE_SET_SSP_0_DATA_FUNC_ID, fs_set_SSP_0_DataReq },
    { DATA_CACHE_GET_SSP_1_DATA_FUNC_ID, fs_get_SSP_1_DataReq },
    { DATA_CACHE_SET_SSP_1_DATA_FUNC_ID, fs_set_SSP_1_DataReq },
    { DATA_CACHE_GET_SSP_2_DATA_FUNC_ID, fs_get_SSP_2_DataReq },
    { DATA_CACHE_SET_SSP_2_DATA_FUNC_ID, fs_set_SSP_2_DataReq },
    { DATA_CACHE_GET_AOCS_CNTRL_TLM_DATA_FUNC_ID, fs_get_AOCS_CNTRL_TLM_DataReq },
    { DATA_CACHE_SET_AOCS_CNTRL_TLM_DATA_FUNC_ID, fs_set_AOCS_CNTRL_TLM_DataReq },
    { DATA_CACHE_GET_OS_TASK_DATA_FUNC_ID, fs_get_OS_Task_DataReq },
    { DATA_CACHE_SET_OS_TASK_DATA_FUNC_ID, fs_set_OS_Task_DataReq },
    { DATA_CACHE_GET_SSP_3_DATA_FUNC_ID, fs_get_SSP_3_DataReq },
    { DATA_CACHE_SET_SSP_3_DATA_FUNC_ID, fs_set_SSP_3_DataReq },
    { DATA_CACHE_GET_SENSOR_MAG_PRIMARY_DATA_FUNC_ID, fs_get_SENSOR_MAG_PRIMARY_DataReq },
    { DATA_CACHE_SET_SENSOR_MAG_PRIMARY_DATA_FUNC_ID, fs_set_SENSOR_MAG_PRIMARY_DataReq },
    { DATA_CACHE_GET_SENSOR_MAG_SECONDARY_DATA_FUNC_ID, fs_get_SENSOR_MAG_SECONDARY_DataReq },
    { DATA_CACHE_SET_SENSOR_MAG_SECONDARY_DATA_FUNC_ID, fs_set_SENSOR_MAG_SECONDARY_DataReq },
    { DATA_CACHE_GET_SENSOR_GYRO_DATA_FUNC_ID, fs_get_SENSOR_GYRO_DataReq },
    { DATA_CACHE_SET_SENSOR_GYRO_DATA_FUNC_ID, fs_set_SENSOR_GYRO_DataReq },
    { DATA_CACHE_GET_SENSOR_COARSE_SUN_DATA_FUNC_ID, fs_get_SENSOR_COARSE_SUN_DataReq },
    { DATA_CACHE_SET_SENSOR_COARSE_SUN_DATA_FUNC_ID, fs_set_SENSOR_COARSE_SUN_DataReq },
    { DATA_CACHE_GET_ES_ADCS_SENSOR_MAG_PRIMARY_DATA_FUNC_ID, fs_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataReq },
    { DATA_CACHE_SET_ES_ADCS_SENSOR_MAG_PRIMARY_DATA_FUNC_ID, fs_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataReq },
    { DATA_CACHE_GET_ES_ADCS_SENSOR_MAG_SECONDARY_DATA_FUNC_ID, fs_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataReq },
    { DATA_CACHE_SET_ES_ADCS_SENSOR_MAG_SECONDARY_DATA_FUNC_ID, fs_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataReq },
    { DATA_CACHE_GET_ES_ADCS_SENSOR_GYRO_DATA_FUNC_ID, fs_get_ES_ADCS_SENSOR_GYRO_DataReq },
    { DATA_CACHE_SET_ES_ADCS_SENSOR_GYRO_DATA_FUNC_ID, fs_set_ES_ADCS_SENSOR_GYRO_DataReq },
    { DATA_CACHE_GET_ES_ADCS_SENSOR_CSS_DATA_FUNC_ID, fs_get_ES_ADCS_SENSOR_CSS_DataReq },
    { DATA_CACHE_SET_ES_ADCS_SENSOR_CSS_DATA_FUNC_ID, fs_set_ES_ADCS_SENSOR_CSS_DataReq },
    { DATA_CACHE_GET_ES_ADCS_ESTIMATES_BDOT_DATA_FUNC_ID, fs_get_ES_ADCS_ESTIMATES_BDOT_DataReq },
    { DATA_CACHE_SET_ES_ADCS_ESTIMATES_BDOT_DATA_FUNC_ID, fs_set_ES_ADCS_ESTIMATES_BDOT_DataReq },
    { DATA_CACHE_GET_ES_ADCS_CONTROL_VALUES_MTQ_DATA_FUNC_ID, fs_get_ES_ADCS_CONTROL_VALUES_MTQ_DataReq },
    { DATA_CACHE_SET_ES_ADCS_CONTROL_VALUES_MTQ_DATA_FUNC_ID, fs_set_ES_ADCS_CONTROL_VALUES_MTQ_DataReq },
    { DATA_CACHE_GET_CONOPSFLAGS_DATA_FUNC_ID, fs_get_ConOpsFlags_DataReq },
    { DATA_CACHE_SET_CONOPSFLAGS_DATA_FUNC_ID, fs_set_ConOpsFlags_DataReq },
    { DATA_CACHE_GET_AOCS_CNTRL_SYS_STATE_DATA_FUNC_ID, fs_get_AOCS_CNTRL_SYS_STATE_DataReq },
    { DATA_CACHE_SET_AOCS_CNTRL_SYS_STATE_DATA_FUNC_ID, fs_set_AOCS_CNTRL_SYS_STATE_DataReq },
    { DATA_CACHE_GET_ADCS_3_DATA_FUNC_ID, fs_get_ADCS_3_DataReq },
    { DATA_CACHE_SET_ADCS_3_DATA_FUNC_ID, fs_set_ADCS_3_DataReq },
    { DATA_CACHE_GET_ADCS_4_DATA_FUNC_ID, fs_get_ADCS_4_DataReq },
    { DATA_CACHE_SET_ADCS_4_DATA_FUNC_ID, fs_set_ADCS_4_DataReq },
    { DATA_CACHE_GET_EPS_9_DATA_FUNC_ID, fs_get_EPS_9_DataReq },
    { DATA_CACHE_SET_EPS_9_DATA_FUNC_ID, fs_set_EPS_9_DataReq },
    { DATA_CACHE_GET_EPS_10_DATA_FUNC_ID, fs_get_EPS_10_DataReq },
    { DATA_CACHE_SET_EPS_10_DATA_FUNC_ID, fs_set_EPS_10_DataReq },
    { DATA_CACHE_GET_EPS_14_DATA_FUNC_ID, fs_get_EPS_14_DataReq },
    { DATA_CACHE_SET_EPS_14_DATA_FUNC_ID, fs_set_EPS_14_DataReq },
    { DATA_CACHE_GET_SENSOR_ACC_PRIMARY_DATA_FUNC_ID, fs_get_SENSOR_ACC_PRIMARY_DataReq },
    { DATA_CACHE_SET_SENSOR_ACC_PRIMARY_DATA_FUNC_ID, fs_set_SENSOR_ACC_PRIMARY_DataReq },
    { DATA_CACHE_GET_SENSOR_ACC_SECONDARY_DATA_FUNC_ID, fs_get_SENSOR_ACC_SECONDARY_DataReq },
    { DATA_CACHE_SET_SENSOR_ACC_SECONDARY_DATA_FUNC_ID, fs_set_SENSOR_ACC_SECONDARY_DataReq },
    { DATA_CACHE_GET_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA_FUNC_ID, fs_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataReq },
    { DATA_CACHE_SET_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA_FUNC_ID, fs_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataReq },
    { DATA_CACHE_GET_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA_FUNC_ID, fs_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataReq },
    { DATA_CACHE_SET_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA_FUNC_ID, fs_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataReq },
    { DATA_CACHE_GET_SENSOR_PANEL_TEMP_DATA_FUNC_ID, fs_get_SENSOR_PANEL_TEMP_DataReq },
    { DATA_CACHE_SET_SENSOR_PANEL_TEMP_DATA_FUNC_ID, fs_set_SENSOR_PANEL_TEMP_DataReq },
    { DATA_CACHE_GET_SENSOR_PANEL_TEMP_SAT_FRAME_DATA_FUNC_ID, fs_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataReq },
    { DATA_CACHE_SET_SENSOR_PANEL_TEMP_SAT_FRAME_DATA_FUNC_ID, fs_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataReq },
    { DATA_CACHE_GET_SENSOR_GYRO_TEMP_DATA_FUNC_ID, fs_get_SENSOR_GYRO_TEMP_DataReq },
    { DATA_CACHE_SET_SENSOR_GYRO_TEMP_DATA_FUNC_ID, fs_set_SENSOR_GYRO_TEMP_DataReq },
    { DATA_CACHE_GET_SENSOR_GYRO_TEMP_SAT_FRAME_DATA_FUNC_ID, fs_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataReq },
    { DATA_CACHE_SET_SENSOR_GYRO_TEMP_SAT_FRAME_DATA_FUNC_ID, fs_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_OP_STATUS_APP_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_OP_STATUS_APP_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_OP_STATUS_APP_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_OP_STATUS_APP_DataReq },
    { DATA_CACHE_GET_AOCS_CNTRL_REF_PARAMS_DATA_FUNC_ID, fs_get_AOCS_CNTRL_REF_PARAMS_DataReq },
    { DATA_CACHE_SET_AOCS_CNTRL_REF_PARAMS_DATA_FUNC_ID, fs_set_AOCS_CNTRL_REF_PARAMS_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_166_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_166_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_166_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_166_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_167_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_167_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_167_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_167_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_168_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_168_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_168_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_168_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_169_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_169_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_169_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_169_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_170_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_170_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_170_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_170_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_171_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_171_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_171_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_171_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_172_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_172_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_172_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_172_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_173_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_173_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_173_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_173_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_174_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_174_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_174_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_174_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_175_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_175_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_175_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_175_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_176_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_176_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_176_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_176_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_177_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_177_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_177_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_177_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_178_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_178_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_178_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_178_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_179_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_179_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_179_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_179_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_180_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_180_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_180_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_180_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_203_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_203_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_203_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_203_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_204_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_204_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_204_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_204_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_205_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_205_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_205_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_205_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_206_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_206_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_206_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_206_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_207_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_207_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_207_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_207_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_209_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_209_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_209_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_209_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_210_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_210_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_210_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_210_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_211_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_211_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_211_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_211_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_212_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_212_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_212_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_212_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_213_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_213_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_213_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_213_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_214_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_214_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_214_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_214_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_216_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_216_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_216_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_216_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_217_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_217_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_217_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_217_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_218_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_218_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_218_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_218_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_225_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_225_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_225_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_225_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_226_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_226_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_226_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_226_DataReq },
    { DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_165_DATA_FUNC_ID, fs_get_CUBEADCS_GEN2_TLM_FRAME_165_DataReq },
    { DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_165_DATA_FUNC_ID, fs_set_CUBEADCS_GEN2_TLM_FRAME_165_DataReq },
    { DATA_CACHE_GET_GNSS_TIME_DATA_FUNC_ID, fs_get_GNSS_TIME_DataReq },
    { DATA_CACHE_SET_GNSS_TIME_DATA_FUNC_ID, fs_set_GNSS_TIME_DataReq },
    { DATA_CACHE_GET_GNSS_BESTXYZ_DATA_FUNC_ID, fs_get_GNSS_BESTXYZ_DataReq },
    { DATA_CACHE_SET_GNSS_BESTXYZ_DATA_FUNC_ID, fs_set_GNSS_BESTXYZ_DataReq },
    { DATA_CACHE_GET_EPSOVERALLBATTERYINFO_DATA_FUNC_ID, fs_get_EpsOverallBatteryInfo_DataReq },
    { DATA_CACHE_SET_EPSOVERALLBATTERYINFO_DATA_FUNC_ID, fs_set_EpsOverallBatteryInfo_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_BP_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_BP_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_BP_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_BP_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_INA_SENSOR1_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_INA_SENSOR1_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_INA_SENSOR1_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_INA_SENSOR1_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_INA_SENSOR2_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_INA_SENSOR2_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_INA_SENSOR2_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_INA_SENSOR2_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_BALANCER_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_BALANCER_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_STATUS_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_BALANCER_STATUS_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_STATUS_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_BALANCER_STATUS_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_XP_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_CHARGER_XP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_XP_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_CHARGER_XP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_XR_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_CHARGER_XR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_XR_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_CHARGER_XR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_YP_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_CHARGER_YP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_YP_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_CHARGER_YP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_YR_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_CHARGER_YR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_YR_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_CHARGER_YR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_ZP_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_CHARGER_ZP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_ZP_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_CHARGER_ZP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_ZR_DATA_FUNC_ID, fs_get_EPS2_BP_INST0_CHARGER_ZR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_ZR_DATA_FUNC_ID, fs_set_EPS2_BP_INST0_CHARGER_ZR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_BP_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_BP_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_BP_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_BP_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_INA_SENSOR1_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_INA_SENSOR1_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_INA_SENSOR1_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_INA_SENSOR1_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_INA_SENSOR2_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_INA_SENSOR2_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_INA_SENSOR2_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_INA_SENSOR2_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_BALANCER_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_BALANCER_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_STATUS_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_BALANCER_STATUS_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_STATUS_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_BALANCER_STATUS_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_XP_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_CHARGER_XP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_XP_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_CHARGER_XP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_XR_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_CHARGER_XR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_XR_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_CHARGER_XR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_YP_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_CHARGER_YP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_YP_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_CHARGER_YP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_YR_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_CHARGER_YR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_YR_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_CHARGER_YR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_ZP_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_CHARGER_ZP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_ZP_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_CHARGER_ZP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_ZR_DATA_FUNC_ID, fs_get_EPS2_BP_INST1_CHARGER_ZR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_ZR_DATA_FUNC_ID, fs_set_EPS2_BP_INST1_CHARGER_ZR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_BP_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_BP_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_BP_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_BP_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_INA_SENSOR1_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_INA_SENSOR1_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_INA_SENSOR1_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_INA_SENSOR1_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_INA_SENSOR2_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_INA_SENSOR2_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_INA_SENSOR2_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_INA_SENSOR2_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_BALANCER_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_BALANCER_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_STATUS_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_BALANCER_STATUS_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_STATUS_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_BALANCER_STATUS_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_XP_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_CHARGER_XP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_XP_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_CHARGER_XP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_XR_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_CHARGER_XR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_XR_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_CHARGER_XR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_YP_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_CHARGER_YP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_YP_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_CHARGER_YP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_YR_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_CHARGER_YR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_YR_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_CHARGER_YR_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_ZP_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_CHARGER_ZP_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_ZP_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_CHARGER_ZP_DataReq },
    { DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_ZR_DATA_FUNC_ID, fs_get_EPS2_BP_INST2_CHARGER_ZR_DataReq },
    { DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_ZR_DATA_FUNC_ID, fs_set_EPS2_BP_INST2_CHARGER_ZR_DataReq }
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

static void fs_get_OBC_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_OBC_0_DataProtocolRequestData_t *fullrequest = (data_cacheget_OBC_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_OBC_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_OBC_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_OBC_0_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_OBC_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_OBC_0_DataProtocolRequestData_t *fullrequest = (data_cacheset_OBC_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_OBC_0_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_OBC_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_OBC_0_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_OBC_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_OBC_0_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ADCS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ADCS_0_DataProtocolRequestData_t *fullrequest = (data_cacheget_ADCS_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ADCS_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ADCS_0_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ADCS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ADCS_0_DataProtocolRequestData_t *fullrequest = (data_cacheset_ADCS_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ADCS_0_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ADCS_0_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ADCS_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ADCS_0_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ADCS_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ADCS_1_DataProtocolRequestData_t *fullrequest = (data_cacheget_ADCS_1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ADCS_1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ADCS_1_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ADCS_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ADCS_1_DataProtocolRequestData_t *fullrequest = (data_cacheset_ADCS_1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ADCS_1_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ADCS_1_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ADCS_1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ADCS_1_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ADCS_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ADCS_2_DataProtocolRequestData_t *fullrequest = (data_cacheget_ADCS_2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ADCS_2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ADCS_2_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ADCS_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ADCS_2_DataProtocolRequestData_t *fullrequest = (data_cacheset_ADCS_2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ADCS_2_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ADCS_2_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ADCS_2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ADCS_2_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS_0_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS_0_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS_0_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS_0_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS_0_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS_0_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SSP_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SSP_0_DataProtocolRequestData_t *fullrequest = (data_cacheget_SSP_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SSP_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SSP_0_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SSP_0_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SSP_0_DataProtocolRequestData_t *fullrequest = (data_cacheset_SSP_0_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SSP_0_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_0_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SSP_0_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SSP_0_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SSP_0_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SSP_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SSP_1_DataProtocolRequestData_t *fullrequest = (data_cacheget_SSP_1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SSP_1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SSP_1_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SSP_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SSP_1_DataProtocolRequestData_t *fullrequest = (data_cacheset_SSP_1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SSP_1_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SSP_1_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SSP_1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SSP_1_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SSP_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SSP_2_DataProtocolRequestData_t *fullrequest = (data_cacheget_SSP_2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SSP_2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SSP_2_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SSP_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SSP_2_DataProtocolRequestData_t *fullrequest = (data_cacheset_SSP_2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SSP_2_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SSP_2_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SSP_2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SSP_2_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_AOCS_CNTRL_TLM_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_AOCS_CNTRL_TLM_DataProtocolRequestData_t *fullrequest = (data_cacheget_AOCS_CNTRL_TLM_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_AOCS_CNTRL_TLM_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_AOCS_CNTRL_TLM_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_AOCS_CNTRL_TLM_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_AOCS_CNTRL_TLM_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_AOCS_CNTRL_TLM_DataProtocolRequestData_t *fullrequest = (data_cacheset_AOCS_CNTRL_TLM_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_AOCS_CNTRL_TLM_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_AOCS_CNTRL_TLM_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_AOCS_CNTRL_TLM_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_AOCS_CNTRL_TLM_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_AOCS_CNTRL_TLM_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_OS_Task_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_OS_Task_DataProtocolRequestData_t *fullrequest = (data_cacheget_OS_Task_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_OS_Task_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_OS_Task_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_OS_Task_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_OS_Task_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_OS_Task_DataProtocolRequestData_t *fullrequest = (data_cacheset_OS_Task_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_OS_Task_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_OS_Task_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_OS_Task_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_OS_Task_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_OS_Task_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SSP_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SSP_3_DataProtocolRequestData_t *fullrequest = (data_cacheget_SSP_3_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_3_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SSP_3_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SSP_3_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SSP_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SSP_3_DataProtocolRequestData_t *fullrequest = (data_cacheset_SSP_3_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SSP_3_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_3_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SSP_3_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SSP_3_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SSP_3_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_MAG_PRIMARY_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_MAG_PRIMARY_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_MAG_PRIMARY_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_MAG_PRIMARY_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_MAG_SECONDARY_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_MAG_SECONDARY_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_MAG_SECONDARY_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_MAG_SECONDARY_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_GYRO_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_GYRO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_GYRO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_GYRO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_GYRO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_GYRO_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_GYRO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_GYRO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_GYRO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_GYRO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_GYRO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_GYRO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_COARSE_SUN_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_COARSE_SUN_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_COARSE_SUN_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_COARSE_SUN_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_COARSE_SUN_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_COARSE_SUN_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_COARSE_SUN_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_COARSE_SUN_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_COARSE_SUN_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_COARSE_SUN_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_COARSE_SUN_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_COARSE_SUN_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_COARSE_SUN_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_COARSE_SUN_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *fullrequest = (data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *fullrequest = (data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *fullrequest = (data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *fullrequest = (data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ES_ADCS_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t *fullrequest = (data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_GYRO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ES_ADCS_SENSOR_GYRO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t *fullrequest = (data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ES_ADCS_SENSOR_GYRO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ES_ADCS_SENSOR_GYRO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_GYRO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ES_ADCS_SENSOR_CSS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t *fullrequest = (data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ES_ADCS_SENSOR_CSS_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ES_ADCS_SENSOR_CSS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t *fullrequest = (data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ES_ADCS_SENSOR_CSS_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ES_ADCS_SENSOR_CSS_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ES_ADCS_SENSOR_CSS_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ES_ADCS_ESTIMATES_BDOT_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t *fullrequest = (data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ES_ADCS_ESTIMATES_BDOT_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t *fullrequest = (data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ES_ADCS_CONTROL_VALUES_MTQ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t *fullrequest = (data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ES_ADCS_CONTROL_VALUES_MTQ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t *fullrequest = (data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ConOpsFlags_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ConOpsFlags_DataProtocolRequestData_t *fullrequest = (data_cacheget_ConOpsFlags_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ConOpsFlags_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ConOpsFlags_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ConOpsFlags_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ConOpsFlags_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ConOpsFlags_DataProtocolRequestData_t *fullrequest = (data_cacheset_ConOpsFlags_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ConOpsFlags_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ConOpsFlags_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ConOpsFlags_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ConOpsFlags_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ConOpsFlags_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_AOCS_CNTRL_SYS_STATE_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t *fullrequest = (data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_AOCS_CNTRL_SYS_STATE_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_AOCS_CNTRL_SYS_STATE_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t *fullrequest = (data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_AOCS_CNTRL_SYS_STATE_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_AOCS_CNTRL_SYS_STATE_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_AOCS_CNTRL_SYS_STATE_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ADCS_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ADCS_3_DataProtocolRequestData_t *fullrequest = (data_cacheget_ADCS_3_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_3_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ADCS_3_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ADCS_3_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ADCS_3_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ADCS_3_DataProtocolRequestData_t *fullrequest = (data_cacheset_ADCS_3_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ADCS_3_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_3_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ADCS_3_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ADCS_3_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ADCS_3_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_ADCS_4_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_ADCS_4_DataProtocolRequestData_t *fullrequest = (data_cacheget_ADCS_4_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_4_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_ADCS_4_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_ADCS_4_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_ADCS_4_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_ADCS_4_DataProtocolRequestData_t *fullrequest = (data_cacheset_ADCS_4_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_ADCS_4_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_4_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_ADCS_4_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_ADCS_4_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_ADCS_4_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS_9_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS_9_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS_9_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_9_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS_9_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS_9_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS_9_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS_9_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS_9_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS_9_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_9_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS_9_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS_9_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS_9_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS_10_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS_10_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS_10_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_10_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS_10_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS_10_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS_10_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS_10_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS_10_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS_10_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_10_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS_10_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS_10_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS_10_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS_14_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS_14_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS_14_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_14_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS_14_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS_14_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS_14_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS_14_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS_14_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS_14_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_14_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS_14_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS_14_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS_14_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_ACC_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_ACC_PRIMARY_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_ACC_PRIMARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_ACC_PRIMARY_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_ACC_PRIMARY_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_ACC_PRIMARY_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_ACC_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_ACC_SECONDARY_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_ACC_SECONDARY_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_ACC_SECONDARY_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_ACC_SECONDARY_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_ACC_SECONDARY_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_PANEL_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_PANEL_TEMP_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_PANEL_TEMP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_PANEL_TEMP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_PANEL_TEMP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_PANEL_TEMP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_PANEL_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_PANEL_TEMP_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_PANEL_TEMP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_PANEL_TEMP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_PANEL_TEMP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_PANEL_TEMP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_PANEL_TEMP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_PANEL_TEMP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_GYRO_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_GYRO_TEMP_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_GYRO_TEMP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_GYRO_TEMP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_GYRO_TEMP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_GYRO_TEMP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_GYRO_TEMP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_GYRO_TEMP_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_GYRO_TEMP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_GYRO_TEMP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_GYRO_TEMP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_GYRO_TEMP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_GYRO_TEMP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_GYRO_TEMP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t *fullrequest = (data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_OP_STATUS_APP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_OP_STATUS_APP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_AOCS_CNTRL_REF_PARAMS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t *fullrequest = (data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_AOCS_CNTRL_REF_PARAMS_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_AOCS_CNTRL_REF_PARAMS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t *fullrequest = (data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_AOCS_CNTRL_REF_PARAMS_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_AOCS_CNTRL_REF_PARAMS_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_AOCS_CNTRL_REF_PARAMS_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_166_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_166_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_167_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_167_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_168_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_168_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_169_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_169_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_170_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_170_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_171_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_171_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_172_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_172_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_173_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_173_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_174_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_174_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_175_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_175_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_176_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_176_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_177_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_177_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_178_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_178_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_179_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_179_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_180_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_180_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_203_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_203_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_204_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_204_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_205_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_205_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_206_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_206_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_207_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_207_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_209_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_209_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_210_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_210_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_211_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_211_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_212_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_212_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_213_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_213_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_214_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_214_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_216_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_216_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_217_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_217_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_218_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_218_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_225_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_225_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_226_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_226_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_CUBEADCS_GEN2_TLM_FRAME_165_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t *fullrequest = (data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_CUBEADCS_GEN2_TLM_FRAME_165_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t *fullrequest = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_GNSS_TIME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_GNSS_TIME_DataProtocolRequestData_t *fullrequest = (data_cacheget_GNSS_TIME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_GNSS_TIME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_GNSS_TIME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_GNSS_TIME_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_GNSS_TIME_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_GNSS_TIME_DataProtocolRequestData_t *fullrequest = (data_cacheset_GNSS_TIME_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_GNSS_TIME_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_GNSS_TIME_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_GNSS_TIME_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_GNSS_TIME_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_GNSS_TIME_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_GNSS_BESTXYZ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_GNSS_BESTXYZ_DataProtocolRequestData_t *fullrequest = (data_cacheget_GNSS_BESTXYZ_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_GNSS_BESTXYZ_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_GNSS_BESTXYZ_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_GNSS_BESTXYZ_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_GNSS_BESTXYZ_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_GNSS_BESTXYZ_DataProtocolRequestData_t *fullrequest = (data_cacheset_GNSS_BESTXYZ_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_GNSS_BESTXYZ_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_GNSS_BESTXYZ_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_GNSS_BESTXYZ_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_GNSS_BESTXYZ_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_GNSS_BESTXYZ_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EpsOverallBatteryInfo_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EpsOverallBatteryInfo_DataProtocolRequestData_t *fullrequest = (data_cacheget_EpsOverallBatteryInfo_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EpsOverallBatteryInfo_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EpsOverallBatteryInfo_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EpsOverallBatteryInfo_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EpsOverallBatteryInfo_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EpsOverallBatteryInfo_DataProtocolRequestData_t *fullrequest = (data_cacheset_EpsOverallBatteryInfo_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EpsOverallBatteryInfo_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EpsOverallBatteryInfo_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EpsOverallBatteryInfo_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EpsOverallBatteryInfo_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EpsOverallBatteryInfo_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BP_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_BP_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_BP_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BP_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST0_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST0_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BP_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_BP_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_BP_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BP_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST1_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST1_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BP_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_BP_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_BP_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_BP_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BP_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_INA_SENSOR1_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_INA_SENSOR2_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_BALANCER_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_BALANCER_STATUS_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_CHARGER_XP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_CHARGER_XR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_CHARGER_YP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_CHARGER_YR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_CHARGER_ZP_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_EPS2_BP_INST2_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t *fullrequest = (data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler(&requestCtx);
    }
}

static void fs_set_EPS2_BP_INST2_CHARGER_ZR_DataReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t *fullrequest = (data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t *) fp_DataInfo->pu8Data;
    data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataRequestHandler(&requestCtx,
                                        requestPayload);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void data_cache_registerServerApi(data_cache_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t data_cache_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_data_cacheProtocolServerInfo;
}

ESSATMAC_ErrCodes data_cache_get_OBC_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_OBC_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_OBC_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_OBC_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_OBC_0_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_OBC_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_OBC_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_OBC_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_OBC_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_OBC_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_OBC_0_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_OBC_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_OBC_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ADCS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ADCS_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ADCS_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_0_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ADCS_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ADCS_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ADCS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ADCS_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ADCS_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_0_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ADCS_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ADCS_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ADCS_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_1_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ADCS_1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ADCS_1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_1_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ADCS_1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ADCS_1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ADCS_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ADCS_1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ADCS_1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_1_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ADCS_1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ADCS_1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ADCS_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_2_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ADCS_2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ADCS_2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_2_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ADCS_2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ADCS_2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ADCS_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ADCS_2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ADCS_2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_2_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ADCS_2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ADCS_2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_0_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_0_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SSP_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_0_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SSP_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SSP_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_0_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SSP_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SSP_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SSP_0_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SSP_0_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SSP_0_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_0_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SSP_0_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SSP_0_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SSP_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_1_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SSP_1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SSP_1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_1_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SSP_1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SSP_1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SSP_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SSP_1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SSP_1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_1_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SSP_1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SSP_1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SSP_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_2_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SSP_2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SSP_2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_2_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SSP_2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SSP_2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SSP_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SSP_2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SSP_2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_2_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SSP_2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SSP_2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_AOCS_CNTRL_TLM_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_AOCS_CNTRL_TLM_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_AOCS_CNTRL_TLM_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_AOCS_CNTRL_TLM_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_AOCS_CNTRL_TLM_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_AOCS_CNTRL_TLM_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_AOCS_CNTRL_TLM_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_AOCS_CNTRL_TLM_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_AOCS_CNTRL_TLM_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_AOCS_CNTRL_TLM_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_AOCS_CNTRL_TLM_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_AOCS_CNTRL_TLM_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_AOCS_CNTRL_TLM_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_OS_Task_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_TaskStats_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_OS_Task_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_OS_Task_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_OS_Task_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_OS_TASK_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_OS_Task_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_OS_Task_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_OS_Task_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_OS_Task_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_OS_Task_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_OS_TASK_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_OS_Task_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SSP_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SSP_3_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SSP_3_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SSP_3_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SSP_3_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SSP_3_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SSP_3_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SSP_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SSP_3_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SSP_3_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SSP_3_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SSP_3_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SSP_3_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_MAG_PRIMARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_MAG_SECONDARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_GYRO_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_GYRO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_GYRO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_GYRO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_GYRO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_GYRO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_GYRO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_GYRO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_GYRO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_GYRO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_GYRO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_COARSE_SUN_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_COARSE_SUN_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_COARSE_SUN_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_COARSE_SUN_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_COARSE_SUN_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_COARSE_SUN_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_COARSE_SUN_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_COARSE_SUN_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_COARSE_SUN_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_COARSE_SUN_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_COARSE_SUN_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_COARSE_SUN_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_COARSE_SUN_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ES_ADCS_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_MAG_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ES_ADCS_SENSOR_MAG_PRIMARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ES_ADCS_SENSOR_MAG_PRIMARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ES_ADCS_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_MAG_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ES_ADCS_SENSOR_MAG_SECONDARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ES_ADCS_SENSOR_MAG_SECONDARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_GYRO_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ES_ADCS_SENSOR_GYRO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_GYRO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ES_ADCS_SENSOR_GYRO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ES_ADCS_SENSOR_GYRO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_SENSOR_CSS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_SENSOR_CSS_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ES_ADCS_SENSOR_CSS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_SENSOR_CSS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ES_ADCS_SENSOR_CSS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ES_ADCS_SENSOR_CSS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_ESTIMATES_BDOT_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ES_ADCS_ESTIMATES_BDOT_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_ESTIMATES_BDOT_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ES_ADCS_ESTIMATES_BDOT_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ES_ADCS_ESTIMATES_BDOT_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ES_ADCS_CONTROL_VALUES_MTQ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ES_ADCS_CONTROL_VALUES_MTQ_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ES_ADCS_CONTROL_VALUES_MTQ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ES_ADCS_CONTROL_VALUES_MTQ_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ES_ADCS_CONTROL_VALUES_MTQ_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ConOpsFlags_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ConOpsFlags_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ConOpsFlags_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ConOpsFlags_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ConOpsFlags_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CONOPSFLAGS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ConOpsFlags_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ConOpsFlags_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ConOpsFlags_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ConOpsFlags_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ConOpsFlags_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CONOPSFLAGS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ConOpsFlags_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_AOCS_CNTRL_SYS_STATE_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_AOCS_CNTRL_SYS_STATE_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_AOCS_CNTRL_SYS_STATE_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_AOCS_CNTRL_SYS_STATE_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_AOCS_CNTRL_SYS_STATE_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ADCS_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_3_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ADCS_3_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ADCS_3_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_3_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ADCS_3_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ADCS_3_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ADCS_3_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ADCS_3_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ADCS_3_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_3_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ADCS_3_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ADCS_3_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_ADCS_4_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_ADCS_4_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_ADCS_4_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_ADCS_4_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_ADCS_4_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_ADCS_4_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_ADCS_4_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_ADCS_4_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_ADCS_4_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_ADCS_4_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_ADCS_4_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_ADCS_4_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_ADCS_4_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS_9_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_9_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS_9_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS_9_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_9_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS_9_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS_9_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS_9_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS_9_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS_9_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_9_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS_9_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS_9_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS_10_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_10_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS_10_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS_10_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_10_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS_10_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS_10_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS_10_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS_10_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS_10_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_10_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS_10_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS_10_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS_14_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EPS_14_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS_14_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS_14_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS_14_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS_14_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS_14_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS_14_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS_14_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS_14_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS_14_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS_14_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS_14_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_PRIMARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_ACC_PRIMARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_PRIMARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_ACC_PRIMARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_ACC_PRIMARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_SECONDARY_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_ACC_SECONDARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_SECONDARY_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_ACC_SECONDARY_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_ACC_SECONDARY_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_PRIMARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_ACC_PRIMARY_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_ACC_SECONDARY_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_ACC_SECONDARY_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_PANEL_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_PANEL_TEMP_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_PANEL_TEMP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_PANEL_TEMP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_PANEL_TEMP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_PANEL_TEMP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_PANEL_TEMP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_PANEL_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_PANEL_TEMP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_PANEL_TEMP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_PANEL_TEMP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_PANEL_TEMP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_PANEL_TEMP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_PANEL_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_PANEL_TEMP_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_PANEL_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_PANEL_TEMP_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_PANEL_TEMP_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_GYRO_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_GYRO_TEMP_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_GYRO_TEMP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_GYRO_TEMP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_GYRO_TEMP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_GYRO_TEMP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_GYRO_TEMP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_GYRO_TEMP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_GYRO_TEMP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_GYRO_TEMP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_GYRO_TEMP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_GYRO_TEMP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_GYRO_TEMP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_SENSOR_GYRO_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_SENSOR_GYRO_TEMP_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_SENSOR_GYRO_TEMP_SAT_FRAME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_SENSOR_GYRO_TEMP_SAT_FRAME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_SENSOR_GYRO_TEMP_SAT_FRAME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_OP_STATUS_COMMON_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_OP_STATUS_COMMON_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_OP_STATUS_APP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_OP_STATUS_APP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_OP_STATUS_APP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_OP_STATUS_APP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_OP_STATUS_APP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_AOCS_CNTRL_REF_PARAMS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_AOCS_CNTRL_REF_PARAMS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_AOCS_CNTRL_REF_PARAMS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_AOCS_CNTRL_REF_PARAMS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_AOCS_CNTRL_REF_PARAMS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_166_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_166_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_166_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_166_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_166_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_167_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_167_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_167_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_167_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_167_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_168_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_168_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_168_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_168_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_168_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_169_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_169_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_169_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_169_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_169_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_170_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_170_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_170_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_170_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_170_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_171_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_171_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_171_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_171_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_171_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_172_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_172_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_172_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_172_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_172_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_173_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_173_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_173_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_173_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_173_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_174_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_174_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_174_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_174_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_174_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_175_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_175_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_175_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_175_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_175_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_176_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_176_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_176_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_176_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_176_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_177_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_177_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_177_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_177_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_177_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_178_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_178_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_178_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_178_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_178_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_179_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_179_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_179_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_179_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_179_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_180_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_180_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_180_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_180_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_180_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_203_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_203_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_203_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_203_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_203_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_204_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_204_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_204_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_204_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_204_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_205_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_205_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_205_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_205_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_205_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_206_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_206_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_206_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_206_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_206_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_207_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_207_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_207_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_207_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_207_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_208_2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_208_2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_209_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_209_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_209_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_209_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_209_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_210_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_210_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_210_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_210_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_210_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_211_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_211_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_211_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_211_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_211_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_212_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_212_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_212_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_212_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_212_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_213_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_213_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_213_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_213_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_213_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_214_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_214_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_214_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_214_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_214_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_216_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_216_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_216_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_216_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_216_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_217_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_217_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_217_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_217_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_217_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_218_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_218_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_218_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_218_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_218_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_225_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_225_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_225_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_225_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_225_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_226_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_226_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_226_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_226_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_226_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_CUBEADCS_GEN2_TLM_FRAME_165_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_CUBEADCS_GEN2_TLM_FRAME_165_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_CUBEADCS_GEN2_TLM_FRAME_165_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_CUBEADCS_GEN2_TLM_FRAME_165_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_CUBEADCS_GEN2_TLM_FRAME_165_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_GNSS_TIME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_GNSS_TIME_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_GNSS_TIME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_GNSS_TIME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_GNSS_TIME_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_GNSS_TIME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_GNSS_TIME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_GNSS_TIME_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_GNSS_TIME_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_GNSS_TIME_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_GNSS_TIME_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_GNSS_TIME_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_GNSS_TIME_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_GNSS_BESTXYZ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_GNSS_BESTXYZ_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_GNSS_BESTXYZ_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_GNSS_BESTXYZ_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_GNSS_BESTXYZ_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_GNSS_BESTXYZ_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_GNSS_BESTXYZ_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_GNSS_BESTXYZ_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_GNSS_BESTXYZ_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_GNSS_BESTXYZ_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_GNSS_BESTXYZ_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_GNSS_BESTXYZ_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_GNSS_BESTXYZ_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EpsOverallBatteryInfo_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_EpsOverallBatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EpsOverallBatteryInfo_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EpsOverallBatteryInfo_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EpsOverallBatteryInfo_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPSOVERALLBATTERYINFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EpsOverallBatteryInfo_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EpsOverallBatteryInfo_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EpsOverallBatteryInfo_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EpsOverallBatteryInfo_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EpsOverallBatteryInfo_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPSOVERALLBATTERYINFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EpsOverallBatteryInfo_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_BP_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_BP_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_BP_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0InaSensors1Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_INA_SENSOR1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_INA_SENSOR1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_INA_SENSOR1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0InaSensors2Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_INA_SENSOR2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_INA_SENSOR2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_INA_SENSOR2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BalancerInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_BALANCER_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BalancerStatusType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_STATUS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_STATUS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_BALANCER_STATUS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_BALANCER_CELLS_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerXpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_XP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_XP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_XP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerXrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_XR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_XR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_XR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerYpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_YP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_YP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_YP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerYrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_YR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_YR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_YR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerZpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_ZP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_ZP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_ZP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST0_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst0ChargerZrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST0_CHARGER_ZR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST0_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST0_CHARGER_ZR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST0_CHARGER_ZR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_BP_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_BP_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_BP_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1InaSensors1Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_INA_SENSOR1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_INA_SENSOR1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_INA_SENSOR1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1InaSensors2Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_INA_SENSOR2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_INA_SENSOR2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_INA_SENSOR2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BalancerInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_BALANCER_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BalancerStatusType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_STATUS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_STATUS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_BALANCER_STATUS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_BALANCER_CELLS_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerXpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_XP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_XP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_XP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerXrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_XR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_XR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_XR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerYpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_YP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_YP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_YP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerYrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_YR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_YR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_YR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerZpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_ZP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_ZP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_ZP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST1_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst1ChargerZrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST1_CHARGER_ZR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST1_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST1_CHARGER_ZR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST1_CHARGER_ZR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BatteryInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_BP_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BP_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_BP_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_BP_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2InaSensors1Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_INA_SENSOR1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_INA_SENSOR1_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_INA_SENSOR1_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_INA_SENSOR1_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2InaSensors2Type_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_INA_SENSOR2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_INA_SENSOR2_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_INA_SENSOR2_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_INA_SENSOR2_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BalancerInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BALANCER_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_BALANCER_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BalancerStatusType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_STATUS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BALANCER_STATUS_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_STATUS_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_BALANCER_STATUS_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_BALANCER_CELLS_INFO_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerXpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_XP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_XP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_XP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_XP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerXrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_XR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_XR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_XR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_XR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerYpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_YP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_YP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_YP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_YP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerYrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_YR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_YR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_YR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_YR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerZpType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_ZP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_ZP_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_ZP_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_ZP_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_get_EPS2_BP_INST2_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_Eps2Inst2ChargerZrType_t * const sOutput_data,
                const DATA_CACHE_DCDataStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t);

    if ((ctx != NULL) && (sOutput_data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_GET_EPS2_BP_INST2_CHARGER_ZR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sOutput_data != NULL)
        {
            responseParams.data.sOutput_data = *(sOutput_data);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sOutput_data,
                          0U,
                          sizeof(responseParams.data.sOutput_data));
        }
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheget_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes data_cache_set_EPS2_BP_INST2_CHARGER_ZR_DataResp(
                RespContext_t* ctx,
                const DATA_CACHE_DCDataUpdateStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_DATA_CACHE;
        responseParams.hdr.funcId  = DATA_CACHE_SET_EPS2_BP_INST2_CHARGER_ZR_DATA_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
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
                                            sizeof(data_cacheset_EPS2_BP_INST2_CHARGER_ZR_DataProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


