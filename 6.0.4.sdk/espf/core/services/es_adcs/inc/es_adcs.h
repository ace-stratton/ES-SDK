/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ES_ADCS_H
#define ES_ADCS_H

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup es_adcs EnduroSat ADCS
 * @{
 * EnduroSat ADCS for 1U/1.5U satellites
 * 
 * ## Initiating Mode Transitions
 * ### From inside the OBC SDK
 * The mode transitions can be triggered using **es_adcs_set_op_mode(uint8_t desiredOpMode)**.
 * The possible modes are shown below:
 *
 * @code {.c}
 * // Stated identifiers
 * enum es_adcs_op_modes_sm_states
 * {
 *     STATE_ROOT,
 *     STATE_ADCS_RUN,
 *     STATE_ADCS_TRIGGER,
 *     STATE_ADCS_IDLE,
 *     STATE_ADCS_NOT_INIT,
 *     STATE_MAX
 * };
 * @endcode
 *
 * where **STATE_ROOT**, **STATE_ADCS_NOT_INIT** and **STATE_MAX** are internal states and **are not** part of
 * the ES ADCS operational modes. Passing them as parameter to the function will result in an error.
 *
 * ### From outside the OBC SDK (using FIDL)
 * The mode transitions can be triggered using the **OBC_ES_ADCS_SET_OP_MODE** function found in `<OBC SDK>/espf/core/fidl/obc/fp/OBC_ES_ADCS.fidl`.
 * The function has a reduced parameter list that excludes the internal states **STATE_ROOT**, **STATE_ADCS_NOT_INIT** and **STATE_MAX**.
 *
 * ## Reading status information
 * ### From inside the OBC SDK
 * The main status information can be retrieved using **es_adcs_get_status()**.
 * The return type is shown below:
 *
 * @code {.c}
 * typedef struct
 * {
 *     es_adcs_result_t estimatorResult;     // Estimator general result
 *     es_adcs_result_t controllerResult;    // Controller general result
 *     uint8_t adcs_hsm_state;               // The corresponding enum is es_adcs_op_modes_sm_states
 * } es_adcs_status_t;
 * @endcode
 *
 * where the **es_adcs_result_t** is as follows:
 *
 * @code {.c}
 * typedef enum
 * {
 *     ES_ADCS_RESULT_OK,           // Operation was successful
 *     ES_ADCS_RESULT_INIT_FAIL,    // ADCS initialization failed
 *     ES_ADCS_RESULT_FAIL          // Operation has failed
 * } es_adcs_result_t;
 * @endcode
 *
 * Estimator specific status can be obtained using **es_adcs_get_status_estimator()**.
 * The return type is shown below:
 *
 * @code {.c}
 * typedef struct
 * {
 *     es_adcs_estimator_warning_t     lastWarningGeneral;                           // General estimator warning
 *     es_adcs_estimator_error_t       lastErrorGeneral;                             // General estimator error
 *     es_adcs_estimator_algo_status_t algoStatus[ES_ADCS_ACTIVE_ESTIMATORS_MAX];    // Status variable for each executed estimator
 * } es_adcs_estimator_status_t;
 * @endcode
 *
 * where **es_adcs_estimator_warning_t** is as follows:
 *
 * @code {.c}
 * typedef enum
 * {
 *     ES_ADCS_ESTIMATOR_WARN_NONE,      // No estimator warnings
 *     ES_ADCS_ESTIMATOR_WARN_GENERAL    // Estimator general warning
 * } es_adcs_estimator_warning_t;
 * @endcode
 *
 * and **es_adcs_estimator_error_t** is one of the following:
 *
 * @code {.c}
 * typedef enum
 * {
 *     ES_ADCS_ESTIMATOR_ERROR_NONE,                    // No estimator errors
 *     ES_ADCS_ESTIMATOR_ERROR_DATA_CACHE_GET,          // Estimator has failed to retrieve data from the DataCache
 *     ES_ADCS_ESTIMATOR_ERROR_MAGNETOMETER_INVALID,    // Estimator has failed to identify a valid magnetometer
 *     ES_ADCS_ESTIMATOR_ERROR_INVALID_ALGO,            // Estimator has failed to identify a valid algorithm
 *     ES_ADCS_ESTIMATOR_ERROR_ALGO_IDENTICAL,          // Estimator is asked to execute two identical algorithms
 *     ES_ADCS_ESTIMATOR_ERROR_GENERAL                  // Estimator general error
 * } es_adcs_estimator_error_t;
 * @endcode
 *
 * The last member of the struct represents algorithm specific status, each one having a warning and an error part as described below:
 *
 * @code {.c}
 * typedef struct
 * {
 *     es_adcs_estimator_warning_t lastWarningAlgo;    // Estimator algorithm warning
 *     es_adcs_estimator_error_t   lastErrorAlgo;      // Estimator algorithm error
 * } es_adcs_estimator_algo_status_t;
 * @endcode
 *
 * The define **ES_ADCS_ACTIVE_ESTIMATORS_MAX** is set to 2, which is the number of estimation algorithms that can be run concurrently.
 *
 * Controller specific status can be obtained using **es_adcs_get_status_controller()**.
 * The return type is shown below:
 *
 * @code {.c}
 * typedef struct
 * {
 *     es_adcs_controller_warning_t     lastWarningGeneral;    // General controller warning
 *     es_adcs_controller_error_t       lastErrorGeneral;      // General controller error
 *     es_adcs_controller_algo_status_t algoStatus;            // Status variable for the executed controller
 * } es_adcs_controller_status_t;
 * @endcode
 *
 * where **es_adcs_controller_warning_t** is as follows:
 *
 * @code {.c}
 * typedef enum
 * {
 *     ES_ADCS_CONTROLLER_WARN_NONE,                // No controller warnings
 *     ES_ADCS_CONTROLLER_WARN_SATURATION_UPPER,    // Controller has reached upper limit of allowed control values
 *     ES_ADCS_CONTROLLER_WARN_SATURATION_LOWER,    // Controller has reached lower limit of allowed control values
 *     ES_ADCS_CONTROLLER_WARN_GENERAL              // Controller general warning
 * } es_adcs_controller_warning_t;
 * @endcode
 *
 * and **es_adcs_controller_error_t** is one of the following:
 *
 * @code {.c}
 * typedef enum
 * {
 *     ES_ADCS_CONTROLLER_ERROR_NONE,              // No controller errors
 *     ES_ADCS_CONTROLLER_ERROR_DATA_CACHE_GET,    // Controller has failed to retrieve data from the DataCache
 *     ES_ADCS_CONTROLLER_ERROR_INVALID_ALGO,      // Controller has failed to identify a valid algorithm
 *     ES_ADCS_CONTROLLER_ERROR_GENERAL            // Controller general error
 * } es_adcs_controller_error_t;
 * @endcode
 *
 * The last member of the struct represents algorithm specific status, each one having a warning and an error part as described below:
 *
 * @code {.c}
 * typedef struct
 * {
 *     es_adcs_controller_warning_t lastWarningAlgo;    // Controller algorithm warning
 *     es_adcs_controller_error_t   lastErrorAlgo;      // Controller algorithm error
 * } es_adcs_controller_algo_status_t;
 * @endcode
 *
 * ### From outside the OBC SDK (using FIDL)
 * The status functions described above are available through a FIDL file - `<OBC SDK>/espf/core/fidl/obc/fp/OBC_ES_ADCS.fidl`.
 * Their names are as follows:
 *
 * - OBC_ES_ADCS_GET_STATUS
 * - OBC_ES_ADCS_GET_STATUS_ESTIMATORS
 * - OBC_ES_ADCS_GET_STATUS_CONTROLLER
 *
 * ## Auxiliary modules
 * ### Coordsys transformations library
 * Within the OBC SDK, the rotation matrices can be changed by using functions found inside the file `<OBC SDK>/espf/core/services/es_coordsys/inc/es_coordsys.h`.
 *
 * Saving the active configuration to NVM or loading from NVM can be done using **coordSys_save_config_to_NVM()** and **coordSys_load_config_from_NVM()** respectively.
 *
 * Outside the OBC SDK (using FIDL), these configurations can be changed using functions found in `<OBC SDK>/espf/core/fidl/obc/fp/OBC_ES_COORDSYS.fidl`.
 *
 * ### Actuator Control Service
 * Within the OBC SDK, the status information can be accessed using **actuator_control_service_status_t actuator_control_service_get_status()**.
 *
 * Outside the OBC SDK (using FIDL), this status information can be accessed using functions in `<OBC SDK>/espf/core/fidl/obc/fp/OBC_ACTUATOR_CONTROL_SERVICE.fidl`.
 *
 * Additional functions for start/stop of the service can be found in `<OBC SDK>/espf/core/services/actuator_control_service/inc/actuator_control_service.h`.
 *
 * Their FIDL equivalents are found in the already mentioned FIDL file.
 *
 * ## Examples of usage
 * ### Normal operation
 * Under normal circumstances, all the configurations for the ES ADCS should be preloaded in their respective NVM entries.
 *
 * The recommended sequence of operation is described below:
 *
 * 1. Check operational mode using **es_adcs_get_op_mode()** (in OBC SDK) or **OBC_ES_ADCS_GET_OP_MODE** (in FIDL).
 *    Expected result is `IDLE(3)`.
 * 2. Check configured estimators using **es_adcs_get_estimator(es_adcs_estimator_t *currentEstimators)** (in OBC SDK) or **OBC_ES_ADCS_GET_ESTIMATORS** (in FIDL).
 * 3. Check configured controller using es_adcs_get_controller() (in OBC SDK) or **OBC_ES_ADCS_GET_CONTROLLER** (in FIDL).
 * 4. Check the appropriate configuration for the chosen controller (example: es_adcs_get_controller_bdot_config() (in OBC SDK) or **OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIG** (in FIDL)).
 * 5. Check if the expected magnetometer is being used by the ES ADCS with es_adcs_get_used_magnetometer() (in OBC SDK) or **OBC_ES_ADCS_GET_MAGNETOMETER** (in FIDL).
 * 6. After making sure all results from the previous steps satisfy the user - enable the ES ADCS by calling **es_adcs_set_op_mode(uint8_t desiredOpMode)** (in OBC SDK) or **OBC_ES_ADCS_SET_OP_MODE** (in FIDL) with the `RUN(1)` state as a parameter.
 *
 * @note
 *     Steps 2-5 can be combined by calling the function **es_adcs_get_config()** (in OBC SDK) or **OBC_ES_ADCS_GET_ADCS_CONFIG** (in FIDL).
 *
 * Following the successful execution of step 6, it is recommended to call **es_adcs_get_status()** (in OBC SDK) or **OBC_ES_ADCS_GET_STATUS** (in FIDL) to confirm that the ES ADCS has not experienced any errors with estimation or control and the operational mode has switched to `RUN(1)`.
 *
 * The ES ADCS configuration can be saved to NVM when the user has decided that it provides good performance. To do so, use **es_adcs_save_config_to_NVM()** (in OBC SDK) or **OBC_ES_ADCS_SAVE_ADCS_CONFIG** (in FIDL).
 *
 * In case the configuration is not satisfactory, the user can revert to the last saved NVM configuration using **es_adcs_load_config_from_NVM()** (in OBC SDK) or **OBC_ES_ADCS_LOAD_ADCS_CONFIG** (in FIDL).
 *
 * ### Reconfiguring the coordinate frames
 * There exists a possibility that the hardware on the satellite has been mounted differently than what was initially expected. In such cases, the rotation (transformation) matrices must be changed accordingly.
 *
 * When using FIDL, the functions are found inside the file `<OBC SDK>/espf/core/fidl/obc/fp/OBC_ES_COORDSYS.fidl`.
 *
 * Though it is possible to change the rotation matrices during active operation of the ES ADCS, it is not recommended. As such, the following sequence assumes that the ES ADCS is in `IDLE(3)` mode.
 *
 * @note
 *     The sequence provides an example for changing the magnetometer rotation matrix - other sensors/actuators follow an identical sequence with their own functions.
 *
 * 1. Call **coordSys_getMagMatrix(es_coordsys_mag_frame_t *activeMagFrame)** (in OBC SDK) or **OBC_ES_COORDSYS_GET_MAGNETOMETER_FRAME** (in FIDL).
 *    Evaluate that the coordinate frame is indeed incorrect.
 * 2. Call **coordSys_setMagMatrix(const es_coordsys_mag_frame_t *newMagFrame)** (in OBC SDK) or **OBC_ES_COORDSYS_SET_MAGNETOMETER_FRAME** (in FIDL).
 * 3. Once the frame is set, use **coordSys_save_config_to_NVM()** (in OBC SDK) or **OBC_ES_COORDSYS_SAVE_COORDSYS_CONFIG** (in FIDL) to transfer the active configuration to NVM.
 *
 * @note
 *     As with the ES ADCS config, the coordsys library also provides the capability to revert to last saved NVM configuration using **coordSys_load_config_from_NVM()** (in OBC SDK) or **OBC_ES_COORDSYS_LOAD_COORDSYS_CONFIG** (in FIDL).
 * @attention
 *     During step 2, it is possible to define a rotation matrix with more than one sensor/actuator per axis, thus making the rotation matrix invalid. It is important to take great care when configuring new rotation matrices.
 *
 * @file     es_adcs.h
 * @brief    EnduroSat ADCS main header file
 *
 * @}
 * @}
 *
*/

#include <if_sys_mod.h>
#include "es_adcs_estimators.h"
#include "es_adcs_controllers.h"

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @brief General ADCS status */
typedef struct
{
    es_adcs_result_t estimatorResult;     /**< Estimator general result */
    es_adcs_result_t controllerResult;    /**< Controller general result */
    uint8_t adcs_hsm_state;               /**< The corresponding enum is es_adcs_op_modes_sm_states */
    // extend when needed
} es_adcs_status_t;

/**********************************************************************
 *
 * External type declarations
 *
 **********************************************************************/
/** Configuration interface for the system instancer */
extern if_sys_mod_t adcs_module_configuration;

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
/** @brief Initialization routine for the ES ADCS component
 *  @param[in] sys_init_level_id_t level - the level of initialization to be performed
 *  @return STATUS_FAILED: initialization went wrong
 *  @return STATUS_OK: everything is initialized
 *  @return STATUS_NOT_SUPPORTED: there is no such level of initialization for the module */
extern mod_op_status_id_t es_adcs_init(sys_init_level_id_t level);

/** @brief Starts the ADCS module and places the ADCS HSM in RUN mode
 *  @return STATUS_FAILED: failed to start the module
 *  @return STATUS_OK: the module is running
 *  @return STATUS_NOT_SUPPORTED: not implemented for this module */
extern mod_op_status_id_t es_adcs_start(void);

/** @brief Stops the adcs module and places the state machine in IDLE mode
 *  @return STATUS_FAILED: failed to stop the module
 *  @return STATUS_OK: module dependencies stopped
 *  @return STATUS_NOT_SUPPORTED: not implemented for this module */
extern mod_op_status_id_t es_adcs_stop(void);

/** @brief Deinitialization routine for the ES ADCS component
 *  @return STATUS_FAILED: deinitialization went wrong
 *  @return STATUS_OK: everything is deinitialized
 *  @return STATUS_NOT_SUPPORTED: there is no such level of deinitialization for the module */
extern mod_op_status_id_t es_adcs_deinit(sys_init_level_id_t level);

/** @brief Get the ADCS module latched error number
 *  @return uint16_t - the number of errors occured since last init */
extern uint16_t es_adcs_get_latched_errors(void);

/** @brief Get the ADCS module current status
 *  @return es_adcs_status_t - the current status of the ADCS module */
extern es_adcs_status_t es_adcs_get_status(void);

/** @brief Get the estimator submodule current status
 *  @return es_adcs_estimator_status_t - the current status of the estimator submodule */
extern es_adcs_estimator_status_t es_adcs_get_status_estimator(void);

/** @brief Get the controller submodule current status
 *  @return es_adcs_controller_status_t - the current status of the controller submodule */
extern es_adcs_controller_status_t es_adcs_get_status_controller(void);

/** @brief Set the ADCS Skip loop variable, used for the ADCS control loop operation
 *  @note This is automatically reset by the ADCS logic */
extern void es_adcs_set_skip_loop(void);

/** @brief Set the ADCS HSM mode
 *  @param[in] uint8_t desiredOpMode - corresponds to es_adcs_op_modes_sm_states enum */
extern void es_adcs_set_op_mode(uint8_t desiredOpMode);

/** @brief Get the ADCS HSM mode
 *  @return uint8_t              - corresponds to es_adcs_op_modes_sm_states enum */
extern uint8_t es_adcs_get_op_mode(void);

/** @brief Set the type of estimators to be used by the ADCS
 *  @param[in] es_adcs_estimator_t - desiredEstimator1
 *  @param[in] es_adcs_estimator_t - desiredEstimator2 */
extern void es_adcs_set_estimator(es_adcs_estimator_t desiredEstimator1, es_adcs_estimator_t desiredEstimator2);

/** @brief Get the type of estimators used by the ADCS
 *  @param[out] es_adcs_estimator_t * - pointer to array of currently active estimators */
extern void es_adcs_get_estimator(es_adcs_estimator_t *currentEstimators);

/** @brief Set the type of controller to be used by the ADCS
 *  @param[in] es_adcs_controller_t - desiredController */
extern void es_adcs_set_controller(es_adcs_controller_t desiredController);

/** @brief Get the type of controller used by the ADCS
 *  @return es_adcs_controller_t - the currently active controller */
extern es_adcs_controller_t es_adcs_get_controller(void);

/** @brief Set the type of bdot controller configuration to be used by the ADCS
 *  @param[in] es_adcs_controller_bdot_config_t - the desired bdot config */
extern void es_adcs_set_controller_bdot_config(es_adcs_controller_bdot_config_t desiredBdotConfig);

/** @brief Get the type of bdot controller configuration used by the ADCS
 *  @return es_adcs_controller_bdot_config_t - the currently active bdot configuration */
extern es_adcs_controller_bdot_config_t es_adcs_get_controller_bdot_config(void);

/** @brief Set the used magnetometer by the ADCS
 *  @param[in] es_adcs_estimator_magnetometer_used_t - desiredMagnetometer */
extern void es_adcs_set_used_magnetometer(es_adcs_used_magnetometer_t desiredMagnetometer);

/** @brief Get the used magnetometer by the ADCS
 *  @return es_adcs_estimator_magnetometer_used_t - the currently used magnetometer */
extern es_adcs_used_magnetometer_t es_adcs_get_used_magnetometer(void);

/** @brief Set the current ADCS main configuration
 *  @param[in] es_adcs_config_t - desiredConfig */
extern void es_adcs_set_config(es_adcs_config_t desiredConfig);

/** @brief Get the current ADCS main configuration
 *  @return es_adcs_config_t - the currently active ADCS configuration */
extern es_adcs_config_t es_adcs_get_config(void);

/** @brief Save the current ADCS main configuration to NVM */
extern void es_adcs_save_config_to_NVM(void);

/** @brief Load the current ADCS main configuration from NVM */
extern void es_adcs_load_config_from_NVM(void);

#endif /* ES_ADCS_H */
/* ******************************************************************************************* */
