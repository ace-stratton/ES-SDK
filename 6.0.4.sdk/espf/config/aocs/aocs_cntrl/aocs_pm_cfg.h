/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __AOCS_PM_CFG_H__
#define __AOCS_PM_CFG_H__

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_pm_cfg.h
 * @brief    AOCS performance monitor configuration
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "aocs_pm.h"

/** @brief Seconds in a minute */
#define SEC_TO_MIN 						60U

/** @brief This is the average contact time that we have in a pass in minutes,
 *  and the algorythm is based on that time */
#define CONTACT_TIME_IN_MINUTES 			8U

/** @brief Contact time in seconds */
#define CONTACT_TIME_IN_SECONDS 			CONTACT_TIME_IN_MINUTES * SEC_TO_MIN

/** @brief This is the length of time that the algorithm works with in seconds */
#define LONG_TERM_WINDOW 					CONTACT_TIME_IN_SECONDS * 16

/** @brief This is the length of time that the algorithm works with in seconds */
#define POLL_PERIOD_MIN						4U

/** @brief How many values is the algorithm assessing */
#define NUM_OF_VALUES_TO_EVALUATE			3U

/** @brief Each axis is skipping samples so the skip samples variable is multiplied by the number of samples
 * and this is the max number it can obtain before something breaks  */
#define MAX_SAMPLES_TO_SKIP 				21845U

/** @brief Multiplies the data read from the CubeADCS to convert it to mili units*/
#define DATA_MULTIPLIER_AOCS_INT			10U

/** @brief Used for constant offset when we are in AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE -1 deg/s */
#define CONSTANT_OFFSET_FOR_Y_TOMSON 		-1000

/** @brief Size of the array used write the header for the AOCS_PM log file */
#define SIZE_OF_ARRAY_HEADER				300U

/** @brief Constant for converting from miliseconds to seconds */
#define CONVERSION_CONST_FROMMS_TO_SEC		0.001f

/** @brief Constant for converting from regular units to mili units */
#define CONVERSION_CONST_UNITS_TO_MUNITS 	0.001f

/** @brief Size of the array of characters in the update buffer function */
#define AOCS_UPDATE_BUFFER_SIZE				48U

/** @brief Number that is written in the file when incorrect data is read from the DC */
#define MAGIC_NUMBER_FOR_INCORRECT_DATA 	123456.98f

/** @brief Constant for converting to percentage */
#define CONVERSION_TO_PROCENTAGE_CONSTANT 	100.0f

/** @brief Max percentage number */
#define MAXIMUM_PERCENTS 					100U

/** @brief Precision number for comparing floats */
#define PECISION_FOR_FLOAT_COMPARE 			0.00001f

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __AOCS_PM_CFG_H__
