/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __SXBAND_SCHED_CFG_H__
#define __SXBAND_SCHED_CFG_H__

/**
 * @addtogroup service_sxband_sched
 * @{
 *
 * @file sxband_sched_cfg.h
 * @brief SXBand scheduler service configuration header
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/** period of the telemetry service task in milliseconds */
#define SXBAND_SCHED_TASK_PERIOD_MS                    (100U)

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SXBAND_SCHED_CFG_H__
