/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_ii
 * @{
 *
 * ## Telemetry
 *
 * The telemetry of the EPS II is split between the PDM (Power Distribution Module) and the BP
 * (Battery Pack). Both devices have a number of sensors from which telemetry can be requested.
 *
 * The task `eps_ii_telemetry_task` is periodically sending requests to both modules and it takes care
 * of receiving the responses with the `eps_ii_*_notif` callback functions and filling up the information in the
 * datacache.
 *
 * The period is defined as @ref EPS_II_TELEMETRY_PERIOD.
 *
 * @file     eps_ii_telemetry.h
 * @brief    Telemetry definitions for gathering EPS II telemetry
 *
 * @}
 */

#ifndef EPS_II_TELEMETRY_H_
#define EPS_II_TELEMETRY_H_

#include "fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolTypes.h"
#include "fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolTypes.h"

/** @brief Initialize telemetry memory
 */
void eps_ii_tlm_init_memory(void);

/** @brief Initialize telemetry task
 */
void eps_ii_tlm_init_os(void);


/** @brief Write in to the datacache the battery information
 *  @param battery_info response obtained from the Battery Pack
 *
 *  @warning The values for the battery current, voltage and temperature are truncated
 *              from int64 to int32 for EPS_0 data
 */
void eps_ii_batt_info_notif(const RespContext_t* const pRespCtx, const EPSII_BP_1GetBatteryInfoResponseData_t* const battery_info);

/** @brief Write in to the datacache the device health information from the battery pack
 *  @param p_dev_health_info response from EPS II with the data
 */
void eps_ii_bp_dev_health_notif(const RespContext_t* const pRespCtx, const EPSII_BP_1GetDeviceHealthInfoResponseData_t* const p_dev_health_info);

/** @brief Write in to the datacache the Power Distribution information from the PDM
 *  @param p_pow_dist_info  response from EPS II with the data
 */
void eps_ii_pow_dist_info_notif(const EPSII_PDM_1GetPowerDistributionInfoResponseData_t* const p_pow_dist_info);

/** @brief Write in to the datacache the device health information from the PDM
 *  @param p_dev_health_info response from EPS II with the data
 */
void eps_ii_pdm_dev_health_notif(const EPSII_PDM_1GetDeviceHealthInfoResponseData_t* const p_dev_health_info);

/** @brief Write in to the datacache the raw sensors information from the BP and the PDM
 *  @param p_raw_sensors response from EPS II with the sensors information
 *
 *  @note It can be a pointer to EPSII_PDM_1GetRAWSensorsResponseData_t or EPSII_BP_1GetRAWSensorsResponseData_t
 */
void eps_ii_raw_sensors_notif(const RespContext_t* const pRespCtx, const void * p_raw_sensors);

#endif /* EPS_II_TELEMETRY_H_ */
