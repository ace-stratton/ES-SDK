/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ES_COORDSYS_H_
#define ES_COORDSYS_H_

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup es_coordsys Coordsys Transformations
 * @{
 * Service that transforms sensor or actuator data between coordinate systems.
 *
 * @file     es_coordsys.h
 * @brief    Coordinate system transformation service header file
 *
 * @}
 * @}
 *
*/

#include <stdbool.h>
#include "es_coordsys_types.h"
#include "debug.h"

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
/** @brief Initializes coordinate frames
    @return bool - 1 for success, 0 for fail */
extern bool coordSys_init(void);

/** @brief Transforms gyroscope data (angles, rates or temperature) to satellite frame
 *  @param[in]  inputData  - pointer to array with gyroscope data in sensor frame
 *  @param[out] outputData - pointer to array with gyroscope data in satellite frame
 *  @return bool - 1 for success, 0 for fail */
extern bool coordSys_transformGyr(const int32_t *inputData, int32_t *outputData);

/** @brief Transforms magnetometer data to satellite frame
 *  @param[in]  inputData  - pointer to array with magnetometer data in sensor frame
 *  @param[out] outputData - pointer to array with magnetometer data in satellite frame
 *  @return bool - 1 for success, 0 for fail */
extern bool coordSys_transformMag(const int32_t *inputData, int32_t *outputData);

/** @brief Transforms magnetorquer control values from satellite frame to actuator frame
 *  @param[in]  inputData  - pointer to array with magnetorquer data in satellite frame
 *  @param[out] outputData - pointer to array with magnetorquer data in actuator frame
 *  @return bool - 1 for success, 0 for fail */
extern bool coordSys_transformMtq(const int8_t  *inputData, int8_t  *outputData);

/** @brief Transforms coarse sun sensor (photosensor) data to satellite frame
 *  @param[in]  inputData  - pointer to array with coarse sun sensor data in sensor frame
 *  @param[out] outputData - pointer to array with coarse sun sensor data in satellite frame
 *  @return bool - 1 for success, 0 for fail */
extern bool coordSys_transformCss(const int32_t *inputData, int32_t *outputData);

/** @brief Transforms accelerometer data to satellite frame
 *  @param[in]  inputData  - pointer to array with accelerometer data in sensor frame
 *  @param[out] outputData - pointer to array with accelerometer data in satellite frame
 *  @return bool - 1 for success, 0 for fail */
extern bool coordSys_transformAcc(const int32_t *inputData, int32_t *outputData);

/** @brief Transforms panel temperature data to satellite frame. This makes a call to coordSys_transformCss
 *  as the CSS and temperature sensors are mounted on the same sides
 *  @param[in]  inputData  - pointer to array with panel temperature data in sensor frame
 *  @param[out] outputData - pointer to array with panel temperature data in satellite frame
 *  @return bool - 1 for success, 0 for fail */
extern bool coordSys_transform_panel_temp(const int32_t *inputData, int32_t *outputData);

/** @brief Transforms gyro temperature data to satellite frame. This makes a call to coordSys_transformGyr as
 *  it is the same gyroscope
 *  @param[in]  inputData  - pointer to array with gyro data in sensor frame
 *  @param[out] outputData - pointer to array with gyro data in satellite frame
 *  @return bool - 1 for success, 0 for fail */
extern bool coordSys_transform_gyro_temp(const int32_t *inputData, int32_t *outputData);

/** @brief Change the rotation matrix for gyroscope frame transformation
 *  @param[in] newGyrFrame - pointer to the new gyroscope frame */
extern void coordSys_setGyrMatrix(const es_coordsys_gyr_frame_t *newGyrFrame);

/** @brief Retrieve the rotation matrix for gyroscope frame transformation
 *  @param[out] activeGyrFrame - pointer to the active gyroscope frame */
extern void coordSys_getGyrMatrix(es_coordsys_gyr_frame_t *activeGyrFrame);

/** @brief Change the rotation matrix for magnetometer frame transformation
 *  @param[in] newMagFrame - pointer to the new magnetometer frame */
extern void coordSys_setMagMatrix(const es_coordsys_mag_frame_t *newMagFrame);

/** @brief Retrieve the rotation matrix for magnetometer frame transformation
 *  @param[out] activeMagFrame - pointer to the active magnetometer frame */
extern void coordSys_getMagMatrix(es_coordsys_mag_frame_t *activeMagFrame);

/** @brief Change the rotation matrix for magnetorquer frame transformation
 *  @param[in] newMtqFrame - pointer to the new magnetorquer frame */
extern void coordSys_setMtqMatrix(const es_coordsys_mtq_frame_t *newMtqFrame);

/** @brief Retrieve the rotation matrix for magnetorquer frame transformation
 *  @param[out] activeMtqFrame - pointer to the active magnetorquer frame */
extern void coordSys_getMtqMatrix(es_coordsys_mtq_frame_t *activeMtqFrame);

/** @brief Change the rotation matrix for coarse sun sensor (photosensor) frame transformation
 *  @param[in] newCssFrame - pointer to the new coarse sun sensor frame */
extern void coordSys_setCssMatrix(const es_coordsys_css_frame_t *newCssFrame);

/** @brief Retrieve the rotation matrix for coarse sun sensor (photosensor) frame transformation
 *  @param[out] activeCssFrame - pointer to the active coarse sun sensor frame */
extern void coordSys_getCssMatrix(es_coordsys_css_frame_t *activeCssFrame);

/** @brief Change the rotation matrix for accelerometer frame transformation
 *  @param[in] newAccFrame - pointer to the new accelerometer frame */
extern void coordSys_setAccMatrix(const es_coordsys_acc_frame_t *newAccFrame);

/** @brief Retrieve the rotation matrix for accelerometer frame transformation
 *  @param[out] activeAccFrame - pointer to the active accelerometer frame */
void coordSys_getAccMatrix(es_coordsys_acc_frame_t *activeAccFrame);

/** @brief Save the current coordinate frames configuration to NVM */
extern void coordSys_save_config_to_NVM(void);

/** @brief Load the current coordinate frames configuration from NVM */
extern void coordSys_load_config_from_NVM(void);

#endif /* ES_COORDSYS_H_ */
/* **************************************************************************************** */
