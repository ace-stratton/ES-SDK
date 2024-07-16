/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __AOCS_CNTRL_TYPES_H__
#define __AOCS_CNTRL_TYPES_H__

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_cntrl_types.c
 * @brief    AOCS control common types
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

/* @brief Enumeration of return statuses for AOCS service APIs
 *
 */
typedef enum
{
    AOCS_CNTRL_ERR_OK,
    AOCS_CNTRL_ERR_BUSY,
    AOCS_CNTRL_ERR_FAILED
} aocs_cntrl_err_status;


/* @brief Enumeration of all the AOCS system state types
 *
 */
typedef enum
{
    // The spacecraft is an undefined control state, the OBC is still collecting data on the control
    AOCS_CNTRL_SYS_STATE_UNDEFINED,
    // The spacecraft is under existing control that has not been commanded by the OBC since last reset
    AOCS_CNTRL_SYS_STATE_EXISTING_CONTROL,

    // Estimators are active
    AOCS_CNTRL_SYS_STATE_NO_CONTROL,

    // Magnetic control
    AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING,
	AOCS_CNTRL_SYS_STATE_Y_THOMSON,
	AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE,
	AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING,
	AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING,

	// One-RWheel nadir pointing
	AOCS_CNTRL_SYS_STATE_Y_MOMENTUM,
	AOCS_CNTRL_SYS_STATE_Y_MOMENTUM_FULL_STATE_EKF,

	// 3-axis pointing with offset angles (default is nadir)
	AOCS_CNTRL_SYS_STATE_3AXIS,

	// 3-axis sun-pointing mode
    AOCS_CNTRL_SYS_STATE_SUN_TRACKING,

    // 3-axis target tracking with the +Z SBC side
    AOCS_CNTRL_SYS_STATE_TARGET_TRACKING,

    // User defined modes
    AOCS_CNTRL_SYS_STATE_USER1,
    AOCS_CNTRL_SYS_STATE_USER2,
    AOCS_CNTRL_SYS_STATE_USER3,

	AOCS_CNTRL_SYS_NUMBER

} aocs_cntrl_sys_state_types_t;

/* @brief Enumeration of all state transition states of the system state change
 *
 */
typedef enum
{
    AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED,
    AOCS_CNTRL_SYS_STATE_STATE_REQ_NEW_REQ,
	AOCS_CNTRL_SYS_STATE_STATE_REQ_IN_PROGRESS,
    AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED,

	AOCS_CNTRL_SYS_STATE_STATE_MAX

} aocs_cntrl_sys_state_req_state_t;

/* @brief Enumeration of all state transition states of the system state change
 *
 */
typedef enum
{
	EST_ATT_ANGL,
	EST_ANG_RATES,
	MEAS_MAG_FIELD_VEC,
	EST_INNOVATION_VEC,
	Q_ERR_VEC,
	MAG_MCU_TEMP,
	RATE_SENS_TEMP,
	RATE_CONVERGENCE
}aocs_log_data_types_t;

/* @brief Enumeration of commissioning status states that can be commanded/retrieved
 * through the AOCS service
 *
 */
typedef enum
{
    CMS_NOT_DONE,
    CMS_COMPLETE
}aocs_cms_status_t;

/* @brief AOCS system errors */
typedef uint32_t aocs_cntrl_aocs_sys_errs;

/* @brief Norm of the estimated angular rate in [mrad/s] */
typedef int32_t aocs_cntrl_est_ang_rate_norm;

/* @brief Angular rate in [mrad/s] */
typedef struct
{
	int32_t X;
	int32_t Y;
	int32_t Z;

} PACKED aocs_cntrl_est_ang_rate_t;

/* @brief Estimated attitude angles [mdeg] */
typedef struct
{
	int32_t roll;
	int32_t pitch;
	int32_t yaw;

} PACKED aocs_cntrl_est_att_t;

/* @brief Wheel speed [RPM] */
typedef struct
{
	int16_t rwl0_speed;
	int16_t rwl1_speed;
	int16_t rwl2_speed;
	int16_t rwl3_speed;

} PACKED aocs_cntrl_wheel_speed_t;

/* @brief Values for assessment */
typedef struct
{
	int32_t value1;
	int32_t value2;
	int32_t value3;
} PACKED aocs_cntrl_log_data_t;

/* @brief Reference parameters for pointing requests */
typedef struct
{
    float ref_param_1;   /*!< Roll, Latitude or X component of an ECI pointing vector */
    float ref_param_2;   /*!< Pitch, Longitude or Y component of an ECI pointing vector */
    float ref_param_3;   /*!< Yaw, Altitude or Z component of an ECI pointing vector */
} PACKED aocs_cntrl_reference_params_t;

/* @brief Offset values */
typedef struct
{
	int32_t offset_value[3];
} PACKED aocs_cntrl_offset_t;




#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __AOCS_CNTRL_TYPES_H__
