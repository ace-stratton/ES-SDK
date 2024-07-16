/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ES_COORDSYS_TYPES_H_
#define ES_COORDSYS_TYPES_H_

/**
 * @addtogroup es_coordsys
 * @{
 *
 * @file     es_coordsys_types.h
 * @brief    Coordinate System Transformation service types file
 *
 * @}
 */

#include <stdint.h>

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @brief Satellite axes */
typedef enum
{
    SAT_X_AXIS_POSITIVE,    /**< Satellite frame positive X axis */
    SAT_Y_AXIS_POSITIVE,    /**< Satellite frame positive Y axis */
    SAT_Z_AXIS_POSITIVE,    /**< Satellite frame positive Z axis */
    SAT_X_AXIS_NEGATIVE,    /**< Satellite frame negative X axis */
    SAT_Y_AXIS_NEGATIVE,    /**< Satellite frame negative Y axis */
    SAT_Z_AXIS_NEGATIVE     /**< Satellite frame negative Z axis */
} es_coordsys_satellite_axes_t;

/** @brief Gyroscope frame */
typedef struct
{
    es_coordsys_satellite_axes_t gyr1;    /**< Which satellite axis does gyroscope 1 correspond to */
    es_coordsys_satellite_axes_t gyr2;    /**< Which satellite axis does gyroscope 2 correspond to */
    es_coordsys_satellite_axes_t gyr3;    /**< Which satellite axis does gyroscope 3 correspond to */
    // extend when needed
} es_coordsys_gyr_frame_t;

/** @brief Magnetometer frame. The magnetometer is a 3-axis in one package therefore it does not need to be represented as 3 individual magnetometers */
typedef struct
{
    es_coordsys_satellite_axes_t mag_x;    /**< Which satellite axis does magnetometer X axis correspond to */
    es_coordsys_satellite_axes_t mag_y;    /**< Which satellite axis does magnetometer Y axis correspond to */
    es_coordsys_satellite_axes_t mag_z;    /**< Which satellite axis does magnetometer Z axis correspond to */
    // extend when needed
} es_coordsys_mag_frame_t;

/** @brief Accelerometer frame. The accelerometer is a 3-axis in one package therefore it does not need to be represented as 3 individual accelerometers */
typedef struct
{
    es_coordsys_satellite_axes_t acc_x;    /**< Which satellite axis does accelerometer X axis correspond to */
    es_coordsys_satellite_axes_t acc_y;    /**< Which satellite axis does accelerometer Y axis correspond to */
    es_coordsys_satellite_axes_t acc_z;    /**< Which satellite axis does accelerometer Z axis correspond to */
    // extend when needed
} es_coordsys_acc_frame_t;

/** @brief Magnetorquer frame */
typedef struct
{
    es_coordsys_satellite_axes_t mtq1;    /**< Which satellite axis does magnetorquer 1 correspond to */
    es_coordsys_satellite_axes_t mtq2;    /**< Which satellite axis does magnetorquer 2 correspond to */
    es_coordsys_satellite_axes_t mtq3;    /**< Which satellite axis does magnetorquer 3 correspond to */
    // extend when needed
} es_coordsys_mtq_frame_t;

/** @brief Coarse Sun Sensor frame */
typedef struct
{
    es_coordsys_satellite_axes_t css1;    /**< Which satellite axis does coarse sun sensor 1 correspond to */
    es_coordsys_satellite_axes_t css2;    /**< Which satellite axis does coarse sun sensor 2 correspond to */
    es_coordsys_satellite_axes_t css3;    /**< Which satellite axis does coarse sun sensor 3 correspond to */
    es_coordsys_satellite_axes_t css4;    /**< Which satellite axis does coarse sun sensor 4 correspond to */
    es_coordsys_satellite_axes_t css5;    /**< Which satellite axis does coarse sun sensor 5 correspond to */
    es_coordsys_satellite_axes_t css6;    /**< Which satellite axis does coarse sun sensor 6 correspond to */
    // extend when needed
} es_coordsys_css_frame_t;

/** @brief All sensor/actuator frames */
typedef struct
{
    es_coordsys_gyr_frame_t gyroscopeFrame;          /**< Gyroscope frame */
    es_coordsys_mag_frame_t magnetometerFrame;       /**< Magnetometer frame */
    es_coordsys_mtq_frame_t magnetorquerFrame;       /**< Magnetorquer frame */
    es_coordsys_css_frame_t coarseSunSensorFrame;    /**< Coarse Sun Sensor frame */
    es_coordsys_acc_frame_t accelerometerFrame;    	 /**< Accelerometer frame */
    uint32_t u32Crc;
} es_coordsys_frames_t;

#endif /* ES_COORDSYS_TYPES_H_ */
/* ******************************************************************************************* */
