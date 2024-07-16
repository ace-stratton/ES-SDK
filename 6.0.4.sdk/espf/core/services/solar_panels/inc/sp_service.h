/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef SP_SERVICE_H
#define SP_SERVICE_H

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup service_sp Solar Panels
 * @{
 *
 * The service performs:
 * - Basic telemetry collection from Endurosat Smart Solar Panel HW modules.
 * - Regular update of the telemetry values to the DataCache.
 *
 * This service is started automatically if the solar panels are configured for use with
 * the OBC SDK. After activation, the service regularly updates the DataCache `SSP_DATA_*`
 * data fields which can be used by other components in the system if they need access to
 * solar panel sensory information.
 *
 * @subsection sp_reading Reading sensor data from the Smart Solar Panels
 *
 * The Solar Panels service acts as a sensory information producer and exposes its acquired
 * data through the global system DataCache component.
 *
 * The service updates the following values:
 * | Panel ESPS bus address | DataCache data ID | DC function to access the data |
 * | ---------------------- | ----------------- | ------------------------------ |
 * | 0x51                   | `DC_DID_SSP_0_DATA` | `dc_get_ssp_0_data()`       |
 * | 0x52                   | `DC_DID_SSP_1_DATA` | `dc_get_ssp_1_data()`        |
 * | 0x53                   | `DC_DID_SSP_2_DATA` | `dc_get_ssp_2_data()`        |
 * | 0x54                   | `DC_DID_SSP_3_DATA` | `dc_get_ssp_3_data()`        |
 *
 * Here is an example how to read the actual solar panel data from the DataCache:
 * @code {.c}
 * #include "datacache.h"
 *
 * DATA_CACHE_SSP_0_t tlm_ssp_0;          // define storage for the solar panel data
 * dc_data_status_t ssp_dc_get_status;    // variable to keep the status of the DataCache read operation
 *
 * // copy the solar panel data to the local storage
 * ssp_dc_get_status = dc_get_ssp_0_data(&tlm_ssp_0);
 *
 * if (DC_DATA_STATUS_OK == ssp_dc_get_status)
 * {
 *      // the read SSP data is valid and can be used
 *      // ...
 * }
 * @endcode
 *
 * If you should need to scan the data from all the panels in a loop, you can use the DataCache IDs above
 * with the `dc_get_raw_data()` function.
 *
 * @file sp_service.h
 *
 * @brief Public interface of the Solar Panel telemetry collection service
 *
 * @}
 * @}
 */
#include "fp/SP/v0.4/SP_client/FP_SPProtocolClient.h"
#include "sys_instancer_ct.h"
#include "if_sys_mod.h"


/** @brief Configuration interface for the system instancer */
extern if_sys_mod_t sp_module_configuration;


// System module interface functions
mod_op_status_id_t sp_init(sys_init_level_id_t level);
mod_op_status_id_t sp_run(void);
mod_op_status_id_t sp_stop(void);
mod_op_status_id_t sp_deinit(sys_init_level_id_t level);

void sp_response_received(RespContext_t* p_resp_ctx, const SPGetTelemetryResponseData_t* p_resp_data);


#endif /* SP_SERVICE_H */
