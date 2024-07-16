/*!
********************************************************************************************
* @file FP_OBC_ES_ADCSProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface OBC_ES_ADCS v3.0
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

#ifndef __FP_OBC_ES_ADCSPROTOCOLTYPES_H__
#define __FP_OBC_ES_ADCSPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS ((uint16_t) (0x00000012))

#define OBC_ES_ADCS_SET_OP_MODE_FUNC_ID ((funcIdType_t) 0x00000001)
#define OBC_ES_ADCS_GET_OP_MODE_FUNC_ID ((funcIdType_t) 0x00000002)
#define OBC_ES_ADCS_SET_ESTIMATORS_FUNC_ID ((funcIdType_t) 0x00000003)
#define OBC_ES_ADCS_GET_ESTIMATORS_FUNC_ID ((funcIdType_t) 0x00000004)
#define OBC_ES_ADCS_SET_CONTROLLER_FUNC_ID ((funcIdType_t) 0x00000005)
#define OBC_ES_ADCS_GET_CONTROLLER_FUNC_ID ((funcIdType_t) 0x00000006)
#define OBC_ES_ADCS_GET_STATUS_FUNC_ID ((funcIdType_t) 0x00000007)
#define OBC_ES_ADCS_GET_STATUS_ESTIMATORS_FUNC_ID ((funcIdType_t) 0x00000008)
#define OBC_ES_ADCS_GET_STATUS_CONTROLLER_FUNC_ID ((funcIdType_t) 0x00000009)
#define OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIG_FUNC_ID ((funcIdType_t) 0x0000000A)
#define OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIG_FUNC_ID ((funcIdType_t) 0x0000000B)
#define OBC_ES_ADCS_SET_MAGNETOMETER_FUNC_ID ((funcIdType_t) 0x0000000C)
#define OBC_ES_ADCS_GET_MAGNETOMETER_FUNC_ID ((funcIdType_t) 0x0000000D)
#define OBC_ES_ADCS_SET_ADCS_CONFIG_FUNC_ID ((funcIdType_t) 0x0000000E)
#define OBC_ES_ADCS_GET_ADCS_CONFIG_FUNC_ID ((funcIdType_t) 0x0000000F)
#define OBC_ES_ADCS_SAVE_ADCS_CONFIG_FUNC_ID ((funcIdType_t) 0x00000010)
#define OBC_ES_ADCS_LOAD_ADCS_CONFIG_FUNC_ID ((funcIdType_t) 0x00000011)
#define OBC_ES_ADCS_SET_OP_MODE_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define OBC_ES_ADCS_GET_OP_MODE_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define OBC_ES_ADCS_SET_ESTIMATORS_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define OBC_ES_ADCS_GET_ESTIMATORS_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define OBC_ES_ADCS_SET_CONTROLLER_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define OBC_ES_ADCS_GET_CONTROLLER_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define OBC_ES_ADCS_GET_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define OBC_ES_ADCS_GET_STATUS_ESTIMATORS_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define OBC_ES_ADCS_GET_STATUS_CONTROLLER_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define OBC_ES_ADCS_SET_MAGNETOMETER_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define OBC_ES_ADCS_GET_MAGNETOMETER_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define OBC_ES_ADCS_SET_ADCS_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define OBC_ES_ADCS_GET_ADCS_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define OBC_ES_ADCS_SAVE_ADCS_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000010)
#define OBC_ES_ADCS_LOAD_ADCS_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000011)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define OBC_ES_ADCS_RESULT_OK ((uint8_t) 0)
#define OBC_ES_ADCS_RESULT_INIT_FAIL ((uint8_t) 1)
#define OBC_ES_ADCS_RESULT_FAIL ((uint8_t) 2)
#define OBC_ES_ADCS_RESULT_MAX_CNT  ((uint8_t) 3)
typedef uint8_t OBC_ES_ADCS_RESULT_t;

/*
    This corresponds to enum es_adcs_op_modes_sm_states from file es_adcs_op_modes_sm_user.h
    It must be manually updated if the file is changed.
*/
#define OBC_ES_ADCS_OP_MODES_STATE_ROOT ((uint8_t) 0)
#define OBC_ES_ADCS_OP_MODES_STATE_ADCS_RUN ((uint8_t) 1)
#define OBC_ES_ADCS_OP_MODES_STATE_ADCS_TRIGGER ((uint8_t) 2)
#define OBC_ES_ADCS_OP_MODES_STATE_ADCS_IDLE ((uint8_t) 3)
#define OBC_ES_ADCS_OP_MODES_STATE_ADCS_NOT_INIT ((uint8_t) 4)
#define OBC_ES_ADCS_OP_MODES_MAX_CNT  ((uint8_t) 5)
typedef uint8_t OBC_ES_ADCS_OP_MODES_t;

/*
    This is a reduced version of the above enum, which is used for the SET_OP_MODE function.
    The reduction is required because not all HSM states are accessible under normal operation.
*/
#define OBC_ES_ADCS_OP_MODES_INPUT_STATE_ADCS_RUN ((uint8_t) 1)
#define OBC_ES_ADCS_OP_MODES_INPUT_STATE_ADCS_TRIGGER ((uint8_t) 2)
#define OBC_ES_ADCS_OP_MODES_INPUT_STATE_ADCS_IDLE ((uint8_t) 3)
#define OBC_ES_ADCS_OP_MODES_INPUT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_ES_ADCS_OP_MODES_INPUT_t;

#define OBC_ES_ADCS_ESTIMATOR_WARNING_NONE ((uint8_t) 0)
#define OBC_ES_ADCS_ESTIMATOR_WARNING_GENERAL ((uint8_t) 1)
#define OBC_ES_ADCS_ESTIMATOR_WARNING_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ES_ADCS_ESTIMATOR_WARNING_t;

#define OBC_ES_ADCS_ESTIMATOR_ERROR_NONE ((uint8_t) 0)
#define OBC_ES_ADCS_ESTIMATOR_ERROR_DATA_CACHE_GET ((uint8_t) 1)
#define OBC_ES_ADCS_ESTIMATOR_ERROR_MAGNETOMETER_INVALID ((uint8_t) 2)
#define OBC_ES_ADCS_ESTIMATOR_ERROR_INVALID_ALGO ((uint8_t) 3)
#define OBC_ES_ADCS_ESTIMATOR_ERROR_ALGO_IDENTICAL ((uint8_t) 4)
#define OBC_ES_ADCS_ESTIMATOR_ERROR_GENERAL ((uint8_t) 5)
#define OBC_ES_ADCS_ESTIMATOR_ERROR_MAX_CNT  ((uint8_t) 6)
typedef uint8_t OBC_ES_ADCS_ESTIMATOR_ERROR_t;

#define OBC_ES_ADCS_USED_MAGNETOMETER_PRIMARY ((uint8_t) 0)
#define OBC_ES_ADCS_USED_MAGNETOMETER_SECONDARY ((uint8_t) 1)
#define OBC_ES_ADCS_USED_MAGNETOMETER_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ES_ADCS_USED_MAGNETOMETER_t;

#define OBC_ES_ADCS_ESTIMATOR_ALGO_NONE ((uint8_t) 0)
#define OBC_ES_ADCS_ESTIMATOR_ALGO_BDOT_MAG ((uint8_t) 1)
#define OBC_ES_ADCS_ESTIMATOR_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ES_ADCS_ESTIMATOR_t;

#define OBC_ES_ADCS_CONTROLLER_WARNING_NONE ((uint8_t) 0)
#define OBC_ES_ADCS_CONTROLLER_WARNING_SATURATION_UPPER ((uint8_t) 1)
#define OBC_ES_ADCS_CONTROLLER_WARNING_SATURATION_LOWER ((uint8_t) 2)
#define OBC_ES_ADCS_CONTROLLER_WARNING_GENERAL ((uint8_t) 3)
#define OBC_ES_ADCS_CONTROLLER_WARNING_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_ES_ADCS_CONTROLLER_WARNING_t;

#define OBC_ES_ADCS_CONTROLLER_ERROR_NONE ((uint8_t) 0)
#define OBC_ES_ADCS_CONTROLLER_ERROR_DATA_CACHE_GET ((uint8_t) 1)
#define OBC_ES_ADCS_CONTROLLER_ERROR_INVALID_ALGO ((uint8_t) 2)
#define OBC_ES_ADCS_CONTROLLER_ERROR_GENERAL ((uint8_t) 3)
#define OBC_ES_ADCS_CONTROLLER_ERROR_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_ES_ADCS_CONTROLLER_ERROR_t;

#define OBC_ES_ADCS_CONTROLLER_ALGO_NONE ((uint8_t) 0)
#define OBC_ES_ADCS_CONTROLLER_ALGO_BDOT_MAG ((uint8_t) 1)
#define OBC_ES_ADCS_CONTROLLER_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ES_ADCS_CONTROLLER_t;

typedef struct {
    OBC_ES_ADCS_ESTIMATOR_WARNING_t eLastWarningAlgo;
    OBC_ES_ADCS_ESTIMATOR_ERROR_t eLastErrorAlgo;
} PACKED_STRUCT OBC_ES_ADCS_ESTIMATOR_ALGO_STATUS_t;

typedef struct {
    OBC_ES_ADCS_ESTIMATOR_WARNING_t eLastWarningGeneral;
    OBC_ES_ADCS_ESTIMATOR_ERROR_t eLastErrorGeneral;
    OBC_ES_ADCS_ESTIMATOR_ALGO_STATUS_t asAlgoStatus[2];
} PACKED_STRUCT OBC_ES_ADCS_ESTIMATOR_STATUS_t;

typedef struct {
    OBC_ES_ADCS_ESTIMATOR_t aeActiveEstimators[2];
} PACKED_STRUCT OBC_ES_ADCS_ESTIMATOR_CONFIG_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_WARNING_t eLastWarningAlgo;
    OBC_ES_ADCS_CONTROLLER_ERROR_t eLastErrorAlgo;
} PACKED_STRUCT OBC_ES_ADCS_CONTROLLER_ALGO_STATUS_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_WARNING_t eLastWarningGeneral;
    OBC_ES_ADCS_CONTROLLER_ERROR_t eLastErrorGeneral;
    OBC_ES_ADCS_CONTROLLER_ALGO_STATUS_t sAlgoStatus;
} PACKED_STRUCT OBC_ES_ADCS_CONTROLLER_STATUS_t;

typedef struct {
    double dBdot_gain_coeff_X;
    double dBdot_gain_coeff_Y;
    double dBdot_gain_coeff_Z;
} PACKED_STRUCT OBC_ES_ADCS_CONTROLLER_BDOT_CONFIG_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_t eActiveController;
    OBC_ES_ADCS_CONTROLLER_BDOT_CONFIG_t sBdotConfig;
} PACKED_STRUCT OBC_ES_ADCS_CONTROLLER_CONFIG_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eEstimatorResult;
    OBC_ES_ADCS_RESULT_t eControllerResult;
    OBC_ES_ADCS_OP_MODES_t eActiveMode;
} PACKED_STRUCT OBC_ES_ADCS_STATUS_t;

typedef struct {
    OBC_ES_ADCS_ESTIMATOR_CONFIG_t sEstimatorConfig;
    OBC_ES_ADCS_CONTROLLER_CONFIG_t sControllerConfig;
    OBC_ES_ADCS_USED_MAGNETOMETER_t eUsedMagnetometer;
} PACKED_STRUCT OBC_ES_ADCS_CONFIG_t;

typedef struct {
    double dX;
    double dY;
    double dZ;
} PACKED_STRUCT OBC_ES_ADCS_VEC_3D_t;


typedef struct {
    OBC_ES_ADCS_OP_MODES_INPUT_t eDesiredMode;
} PACKED_STRUCT OBC_ES_ADCSSET_OP_MODERequestData_t;

typedef struct {
    OBC_ES_ADCS_ESTIMATOR_t eDesiredEstimator1;
    OBC_ES_ADCS_ESTIMATOR_t eDesiredEstimator2;
} PACKED_STRUCT OBC_ES_ADCSSET_ESTIMATORSRequestData_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_t eDesiredController;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLERRequestData_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_BDOT_CONFIG_t sDesiredBdotConfig;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGRequestData_t;

typedef struct {
    OBC_ES_ADCS_USED_MAGNETOMETER_t eDesiredMagnetometer;
} PACKED_STRUCT OBC_ES_ADCSSET_MAGNETOMETERRequestData_t;

typedef struct {
    OBC_ES_ADCS_CONFIG_t sDesiredConfig;
} PACKED_STRUCT OBC_ES_ADCSSET_ADCS_CONFIGRequestData_t;


typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSSET_OP_MODEResponseData_t;

typedef struct {
    OBC_ES_ADCS_OP_MODES_t eActiveMode;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_OP_MODEResponseData_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSSET_ESTIMATORSResponseData_t;

typedef struct {
    OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator1;
    OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator2;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_ESTIMATORSResponseData_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLERResponseData_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_t eActiveController;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_CONTROLLERResponseData_t;

typedef struct {
    OBC_ES_ADCS_STATUS_t sCurrentStatus;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUSResponseData_t;

typedef struct {
    OBC_ES_ADCS_ESTIMATOR_STATUS_t sCurrentStatusEstimators;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUS_ESTIMATORSResponseData_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_STATUS_t sCurrentStatusController;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_STATUS_CONTROLLERResponseData_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGResponseData_t;

typedef struct {
    OBC_ES_ADCS_CONTROLLER_BDOT_CONFIG_t sActiveBdotConfig;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_CONTROLLER_BDOT_CONFIGResponseData_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSSET_MAGNETOMETERResponseData_t;

typedef struct {
    OBC_ES_ADCS_USED_MAGNETOMETER_t eActiveMagnetometer;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_MAGNETOMETERResponseData_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSSET_ADCS_CONFIGResponseData_t;

typedef struct {
    OBC_ES_ADCS_CONFIG_t sActiveConfig;
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSGET_ADCS_CONFIGResponseData_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSSAVE_ADCS_CONFIGResponseData_t;

typedef struct {
    OBC_ES_ADCS_RESULT_t eOpResult;
} PACKED_STRUCT OBC_ES_ADCSLOAD_ADCS_CONFIGResponseData_t;


#endif  // #ifndef __FP_OBC_ES_ADCSPROTOCOLTYPES_H__

