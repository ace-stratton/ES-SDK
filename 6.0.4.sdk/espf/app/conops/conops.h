/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CONOPS_H_
#define CONOPS_H_

/** @addtogroup app
  * @{
  *
  * @defgroup app_conops conops
  * @{
  * Concept of Operations (ConOps)
  *
  * The ConOps is the logic, which controls the spececraft. It does this based on predefined logic, using inputs from the
  * different subsystems and considering the user configurable values (detailed description can be found under **Development recipes/Operational Modes**).
  * It also serves as the glue between the **Payload Controller** (check payload_ctrl.h) and the **Payload Scheduler** (check payload_scheduler.h) offering
  * great flexibility in the integration and operation of payloads.
  *
  * ## Introduction
  *
  * The current ConOps is built around a Hierarchical State Machine (HSM) generated using the libhsm.h engine. It consists of several
  * operational modes, namely:
  * - SAFE
  * - DETUMBLING
  * - IDLE
  * - PAYLOAD MODES
  *
  * By default, the OBC starts in **SAFE** mode. At the start of this mode all payloads are turned off. The requested turn-off mode is immediate, i.e. no soft shutdown is
  * envisioned, but this also depends on how the payload is integrated in the system. The other important thing which is triggered at the start of **SAFE** mode is the clearing
  * of any internal flags that have been set up to this moment.
  *
  * Mode transitions are triggered by two types of events (you can also check the **libhsm** documentation for more details):
  * - mode change requests - these are direct requests for a switch to a certain mode. The switch will happen only if the guard conditions are met.
  * - periodic checks request - these are sent every 10 seconds. When such a request is made the HSM evaluates the guard conditions and checks if it needs to switch to a new mode.
  *
  * ### The ConOps Task
  *
  * The ConOps task runs every 10 seconds, has normal priority and is responsible for:
  * - @emoji :white_check_mark: Checking for updates in the user configurable values
  * - @emoji :white_check_mark: Generating events for the periodic checks requests
  * - @emoji :white_check_mark: Putting the satellite back in sun-tracking mode (STT)
  * - @emoji :x: Checking if a power-off of the OBC may be approaching
  *
  * @note The check for the power-off is not implemented!
  *
  *
  * ## What are the guard conditions?
  *
  * Changing from one mode to another is controlled via the guard conditions. There, several types of inputs are evaluated and checked before a
  * **go/no-go** decision to change to a mode is made. Different inputs are listed below.
  *
  * ### Physical Parameters and AOCS Flags
  *
  * - **Battery capacity [mWh]** from **DATA_CACHE_EPS_0_t** type from datacache.h
  * - **Norm of the angular velocity vector as measured in the satellite body-frame [mrad/s]** from **DATA_CACHE_AOCS_CNTRL_TLM_t** type from datacache.h
  * - **The angular velocity vector as measured in the satellite body-frame [mrad/s]** from **DATA_CACHE_AOCS_CNTRL_TLM_t** type from datacache.h
  * - **Estimated attitude angles in [mdeg]** from **DATA_CACHE_AOCS_CNTRL_TLM_t** type from datacache.h
  * - **Measured wheel speed [RPM]** from **DATA_CACHE_AOCS_CNTRL_TLM_t** type from datacache.h
  * - **AOCS specific error flags** from **DATA_CACHE_AOCS_CNTRL_TLM_t** type from datacache.h. The exact errors mask depends on the used AOCS subsystem.
  *
  * ### The AOCS Commissioning Status
  *
  * The AOCS sub-system is used according to the level of its commissioning. Initially, until all components of the AOCS are checked the status is
  * kept to 0 (no commissioning, check cubeadcs.h) and most of the operational modes logic will not be triggered. Once the AOCS is commissioned, the full
  * capabilities of the ConOps can be used (including the sun-tracking logic).
  *
  * @note Currently, the commissioning status is hard-wired to the cubeadcs commissioning status.
  *
  * ### The AOCS System State
  *
  * The AOCS system state is an aggregation of the estimation mode, control mode, enabled AOCS specific periphery, etc. Its purpose is to
  * facilitate the control of the AOCS system. It resides in **DATA_CACHE_AOCS_CNTRL_SYS_STATE_t** type from datacache.h. Further information
  * regarding the AOCS system state can be found in aocs_cntrl.h
  *
  * ## The ConOps Flags
  *
  * Several flags are used to also control the behaviour of the ConOps. The flags are set from within the ConOps or coupled SW modules.
  * Once a set flag is read, its value is cleared without user intervention.
  *
  * All flags can also be set through the **DATA_CACHE_ConOpsFlags_t** type from datacache.h. This is especially useful when performing testing.
  *
  * ### Payload Error
  *
  * This logical flag is set by the activated payload. It will drop the ConOps from **PAYLOAD[x]** mode to **IDLE** mode. The actual error is not clear and it is up to the
  * payload logic to record the error or report it on user request.
  *
  * ### ADCS Error
  *
  * This error flag is reported when an error in the AOCS system has been identified. This may be produced by an internal AOCS system error or by the **Payload Controller** when
  * it attempts to put the AOCS system in a certain system state. If the error was produced by the AOCS system, it can be identified from the **DATA_CACHE_AOCS_CNTRL_TLM_t** type. However
  * the exact meaning of the error will depend on the exact AOCS system.
  *
  * ### Detumbling Completed
  *
  * This logical flag is set once detumbling or stable Y-Thomson control has been achieved. It is used to indicate that the **DETUMBLING** mode can be exited.
  *
  * ## Testing and Debugging
  *
  * ### Testing
  *
  * The ConOps transitions and paylaod activation can be tested without any additional hardware. To this end the **Data Cache** (datacache.h) types and relevant setters and getters are used.
  *
  * @warning By default each **Data Cache** type expires in 5 seconds!
  *
  * The user can feed the following types periodically:
  * - **DATA_CACHE_EPS_0_t**
  * - **DATA_CACHE_AOCS_CNTRL_TLM_t**
  *
  * and monitor:
  * - **DATA_CACHE_AOCS_CNTRL_SYS_STATE_t**
  * - **DATA_CACHE_ConOpsFlags_t**
  *
  * @warning Setting a **Data Cache** type externally (via command) will inhibit OBC's ability to internally update this type! This behaviour is cleared after reset.
  *
  * However, if more specific transitions need to be tested, the user can decide to modify all types and the commissioning status. The full list of transitions and
  * their dependence on the input parameters can be found in the **Developer's Guide**.
  *
  * ### Debugging
  *
  * The easiest way to debug the ConOps is to use the built-in tracing capabilities of the OBC.
  * Currently, there are three types of tracing that need to be enabled to fully monitor the ConOps behaviour:
  * - **DEBUG_TRACE_OP_MODES_ENABLED**
  * - **DEBUG_TRACE_AOCS_CNTRL_ENABLED**
  * - **DEBUG_TRACE_CUBEADCS_ENABLED**
  *
  * An example debug log:
  * ![Example debug log](../img/conops_trace_dbg.png)
  *
  * There are several headers used to describe specific parts of the ConOps:
  * - **[GUARD_DBG]** indicates a guard condition evaluation is started/exited.
  * - **[TEST_COND]** indicates the actual test which is being executed, within the guard condition.
  * - **[STT_DBG]** informs on the sun-tracking transition logic status and execution.
  * - **[AOCS_CNTRL]** informs on the AOCS control execution. It is important for monitoring the AOCS system state changes.
  * - **[CUBEADCS]** informs on the CubeADCS state machine changes. Again, it is important when monitoring AOCS system state changes.
  *
  * Refer to the **Developer's Guide** to learn more about debugging and tracing.
  *
  * ## Modifying the ConOps
  *
  * The provided ConOps can be extended or modified based on the user needs. Care must be taken to thoroughly test all transition if a modification is made.
  *
  * @file conops.h
  *
  * @brief Concept of Operations header file
  *
  * @}
  * @}
  */

#include "cmsis_os2.h"
#include "es_cdef.h"
#include "conops_cfg.h"
#include "conops_payload.h"
#include "fp/ConOps/v0.2/ConOps_server/FP_ConOpsProtocolTypes.h"
#include "aocs_cntrl_types.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/
typedef enum {
	eFLAG_PAYLOAD_ERR,
	eFLAG_ADCS_ERR,
	eFLAG_DETUMB_COMPLETED,

	eFLAG_MAX,

} eConOps_logical_flag_types_t;

typedef struct
{
    sHSM_EventType_t event_id;
    sConOps_pay_cfg_t event_data;
} sConOps_event_t;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/

/**
 * @brief Initialises the ConOps logic
 */
void conops_init(void);

/**
 * @brief Trigger the ConOps HSM
 * @param[input]      const uint32_t event_id - event id
 *                    const sConOps_pay_cfg_t *const - payload configuration
 * @note              Payload configuration is NULL in case no payload state is triggered
 */
void conops_trigger_hsm(const uint32_t event_id, const sConOps_pay_cfg_t *const pay_cfg);

/**
 * @brief Get the currently active state of the ConOps HSM
 * @param[input]      uint8_t *u8StateCache - pointer to the destination cache
 */
void conops_get_hsm_active_state(uint8_t *u8StateCache);

/**
 * @brief Set the platform general conops threshold values
 * @param[input]      int32 * - pointer to threshold value/s
 *                    index - payload number / angular velocity range
 *                    thres_type - threshold value to update
 */
bool conops_set_thresh_val(int32_t const * const p_thres_val, uint8_t index, CONOPS_ThresholdValueTypes_t thres_type);

/**
 * @brief Get the platform general conops threshold values
 * @param[input]      int32 * - pointer to threshold value/s
 *                    index - payload number / angular velocity range
 *                    thres_type - threshold value to update
 */
bool conops_get_thresh_val(int32_t * p_thres_val, uint8_t index, CONOPS_ThresholdValueTypes_t thres_type);

/**
 * @brief Set the platform general conops threshold values
 * @param[input]    p_conops_config - pointer to threshold value/s configuration
 * @retval  true:   successful operation
 * @retval  false:  operation failed
 */
bool conops_set_all_thresh_val(CONOPS_ThresholdValues_t const * const p_conops_config);

/**
 * @brief Get all the platform general conops threshold values
 * @param[input]      p_conops_config - pointer to threshold value/s configuration
 *
 * @retval  true:   successful operation
 * @retval  false:  operation failed
 */
bool conops_get_all_thresh_val(CONOPS_ThresholdValues_t * p_conops_config);

/**
 * @brief Set a new logical flag state - set or cleared
 */
void conops_set_logical_flag_value(eConOps_logical_flag_types_t eFlagType, bool bFlagVal);

/**
 * @brief Get the status of a logical flag - set or cleared
 * @param eFlagType eFLAG_PAYLOAD_ERR/eFLAG_DETUMB_COMPLETED
 *
 * @retval false: eFLAG_PAYLOAD_ERR
 * @retval true: any other value
 */
bool conops_get_logical_flag(eConOps_logical_flag_types_t eFlagType);

/**
 * @brief Check if battery capacity is above a threshold
 * @param[input]      CONOPS_ThresholdValueTypes_t - threshold value multiplier
 *
 * @return            bool
 * @note              The threshold is formulated as: CbattSafe * Mult, where the latter is defined
 *                    from the input parameter
 */
bool conops_is_cbatt_above(CONOPS_ThresholdValueTypes_t eThreshValType, uint8_t u8PayNum);

/**
 * @brief Check if battery capacity is below a threshold
 * @param[input]      CONOPS_ThresholdValueTypes_t - threshold value multiplier
 *
 * @return            bool
 * @note              The threshold is formulated as: CbattSafe * Mult, where the latter is defined
 *                    from the input parameter
 */
bool conops_is_cbatt_below(CONOPS_ThresholdValueTypes_t eThreshValType, uint8_t u8PayNum);

/**
 * @brief Check if angular velocity is above threshold
 * @param[input]      aocs_state - current state of the AOCS service
 * @return            bool
 * @note              Checks last read angular velocity against a defined threshold
 */
bool conops_is_omega_above_thresh(const aocs_cntrl_sys_state_types_t aocs_state);

/**
 * @brief Check if an error flag has been raised
 * @return            bool
 * @note              This is a filtered return, depending on subsystem states.
 */
bool conops_is_error_flag_raised(void);

/**
 * @brief Check if the ADCS is in a detumbling system state
 *
 * @return            bool
 */
bool conops_is_fast_detumb_activated(void);

/**
 * @brief Check if detumbling is completed
 *
 * @return            bool
 * @note              Check assumes we are in some sort of detumbling. It does not perform evaluation
 *                    of all the different control modes the ADCS can be in.
*/
bool conops_is_detumb_completed(void);

/**
 * @brief Sets the value of the Sun-Tracking flag for IDLE mode
 * @param[input]      safe_bool_t bValue
 *
 * @retval            SAFE_FALSE: received an invalid safe_bool_t
 * @retval            SAFE_TRUE: flag set correctly
 *
 */
safe_bool_t conops_set_enable_sun_tracking_flag(safe_bool_t bValue);

/**
 * @brief Gets the value of the Sun-Tracking flag for IDLE mode
 * @retval            FALSE: flag not set
 * @retval            TRUE: flag set
 *
 */
bool conops_get_enable_sun_tracking_flag(void);

/**
 * @brief Refresh runtime copies of the NVM stored configurations
 * @note              To be used by the periodic conops task
 */
void conops_refresh_runtime_nvm_copies(void);

/**
 * @brief Check if 3-axis control mode is allowed
 */
bool conops_is_3axis_allowed(void);

/**
 * @brief Get the current ADCS system state
 *
 * @param[out] aocs_cntrl_sys_state_types_t *sys_state - Current AOCS system state if the relevant data cache is STATUS_OK. Returns max system state if request failed.
 * @param[out] aocs_cntrl_sys_state_req_state_t *sys_state_req_state - AOCS system state request state. Returns max if request failed.
 *
 * @retval: true - on success
 * @retval: false -  on failure
 */
bool conops_get_aocs_sys_state(aocs_cntrl_sys_state_types_t *sys_state, aocs_cntrl_sys_state_req_state_t *sys_state_req_state);

/**
 * @brief Set a new ADCS system state
 *
 * @param[in] aocs_cntrl_sys_state_types_t sys_state - the new system state
 * @param[in] aocs_reference_params_t* p_ref_params  - reference parameters for some AOCS states
 *
 */
void conops_set_aocs_sys_state(const aocs_cntrl_sys_state_types_t sys_state, const aocs_cntrl_reference_params_t * const p_ref_params);

#endif    /* CONOPS_H_ */
