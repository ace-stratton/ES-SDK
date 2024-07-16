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

#ifndef EPS_II_TELEMETRY_CFG_H_
#define EPS_II_TELEMETRY_CFG_H_

enum {
    BP_INFO,
    BP_HEALTH_INFO,
    BP_INA_SENSOR1,
    BP_INA_SENSOR2,
    BP_BALANCER_INFO,
    BP_BALANCER_STATUS,
    BP_BALANCER_CELLS_INFO,
    BP_CHARGERS_MAIN_INFO_XP,
    BP_CHARGERS_MAIN_INFO_XR,
    BP_CHARGERS_MAIN_INFO_YP,
    BP_CHARGERS_MAIN_INFO_YR,
    BP_CHARGERS_MAIN_INFO_ZP,
    BP_CHARGERS_MAIN_INFO_ZR,
    BP_DATACACHE_CMD_COUNT
}bp_datacache_info_types_t;

typedef struct
{
    uint8_t * p_address;
    dc_did_id datacache_cmd_list[BP_DATACACHE_CMD_COUNT];
}bp_context_type;

// begin EPS BP generated code

//
// Global declarations for EPS BP INSTANCE
//
#define EPS_BP_CONFIGURATION \
{\
        .p_address = &eps_bp_mac_address[0],\
        .datacache_cmd_list = { \
            DC_DID_EPS2_BP_INST0_BP_INFO_DATA, \
            DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA,\
            DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA,\
            DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA,\
            DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA,\
            DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA,\
            DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA,\
            DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA,\
            DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA,\
            DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA,\
            DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA,\
            DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA,\
            DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA\
        }\
},\
{\
        .p_address = &eps_bp_mac_address[1],\
        .datacache_cmd_list = { \
            DC_DID_EPS2_BP_INST1_BP_INFO_DATA, \
            DC_DID_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA,\
            DC_DID_EPS2_BP_INST1_INA_SENSOR1_DATA,\
            DC_DID_EPS2_BP_INST1_INA_SENSOR2_DATA,\
            DC_DID_EPS2_BP_INST1_BALANCER_INFO_DATA,\
            DC_DID_EPS2_BP_INST1_BALANCER_STATUS_DATA,\
            DC_DID_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA,\
            DC_DID_EPS2_BP_INST1_CHARGER_XP_DATA,\
            DC_DID_EPS2_BP_INST1_CHARGER_XR_DATA,\
            DC_DID_EPS2_BP_INST1_CHARGER_YP_DATA,\
            DC_DID_EPS2_BP_INST1_CHARGER_YR_DATA,\
            DC_DID_EPS2_BP_INST1_CHARGER_ZP_DATA,\
            DC_DID_EPS2_BP_INST1_CHARGER_ZR_DATA\
        }\
},\
{\
        .p_address = &eps_bp_mac_address[2],\
        .datacache_cmd_list = { \
            DC_DID_EPS2_BP_INST2_BP_INFO_DATA, \
            DC_DID_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA,\
            DC_DID_EPS2_BP_INST2_INA_SENSOR1_DATA,\
            DC_DID_EPS2_BP_INST2_INA_SENSOR2_DATA,\
            DC_DID_EPS2_BP_INST2_BALANCER_INFO_DATA,\
            DC_DID_EPS2_BP_INST2_BALANCER_STATUS_DATA,\
            DC_DID_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA,\
            DC_DID_EPS2_BP_INST2_CHARGER_XP_DATA,\
            DC_DID_EPS2_BP_INST2_CHARGER_XR_DATA,\
            DC_DID_EPS2_BP_INST2_CHARGER_YP_DATA,\
            DC_DID_EPS2_BP_INST2_CHARGER_YR_DATA,\
            DC_DID_EPS2_BP_INST2_CHARGER_ZP_DATA,\
            DC_DID_EPS2_BP_INST2_CHARGER_ZR_DATA\
        }\
}\
// end EPS BP generated code

#endif /* EPS_II_TELEMETRY_H_ */
