/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GNSS_TYPES_H_
#define GNSS_TYPES_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_types.h
 *
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "es_cdef.h"


/**
 * @brief ASCII message header (structure taken from OEM719 user manual)
 */
typedef struct
{
    char       sync;                        /**< Sync character. The ASCII message is always preceded by a single ‘#’ symbol                                  */
    char       message[25];                 /**< The ASCII name of the log or command                                                                         */
    char       port[8];                     /**< The name of the port from which the log was generated.                                                       */
    int32_t    sequence;                    /**< Used for multiple related logs                                                                               */
    float      idle_time;                   /**< Time the processor is idle, calculated once per second. This value is a percentage, ranging from 0 to 100 %  */
    uint32_t   time_status;                 /**< Indicates the quality of the GPS reference time                                                              */
    uint32_t   week;                        /**< GPS reference week number                                                                                    */
    float      seconds;                     /**< Seconds from the beginning of the GPS reference week                                                         */
    uint32_t   receiver_status;             /**< 32-bits representing the status of various hardware and software components of the receiver                  */
    uint32_t   reserved;                    /**< Reserved for internal use                                                                                    */
    uint32_t   receiver_sw_version;         /**< A value (0 - 65535) representing the receiver software build number                                          */
    char       end;                         /**< The character indicates the end of the header ‘;’ symbol                                                     */
} PACKED gnss_hdr_t;


/**
 * @brief Response to LOG BESTXYZA (structure taken from OEM719 user manual)
 */
typedef struct
{
    gnss_hdr_t header;
    uint32_t   p_sol_status;                /**< Solution status                                               */
    uint32_t   pos_type;                    /**< Position type                                                 */
    double     px;                          /**< Position X-coordinate (m)                                     */
    double     py;                          /**< Position Y-coordinate (m)                                     */
    double     pz;                          /**< Position Z-coordinate (m)                                     */
    float      pxo;                         /**< Standard deviation of P-X (m)                                 */
    float      pyo;                         /**< Standard deviation of P-Y (m)                                 */
    float      pzo;                         /**< Standard deviation of P-Z (m)                                 */
    uint32_t   v_sol_status;                /**< Solution status                                               */
    uint32_t   vel_type;                    /**< Velocity type                                                 */
    double     vx;                          /**< Velocity vector along X-axis (m/s)                            */
    double     vy;                          /**< Velocity vector along Y-axis (m/s)                            */
    double     vz;                          /**< Velocity vector along Z-axis (m/s)                            */
    float      vxo;                         /**< Standard deviation of V-X (m/s)                               */
    float      vyo;                         /**< Standard deviation of V-Y (m/s)                               */
    float      vzo;                         /**< Standard deviation of V-Z (m/s)                               */
    char       stn_id[4];                   /**< Base station identification                                   */
    float      v_latency;                   /**< A measure of the latency in the velocity time tag in seconds. */
    float      diff_age;                    /**< Differential age in seconds                                   */
    float      sol_age;                     /**< Solution age in seconds                                       */
    uint8_t    svs;                         /**< Number of satellites tracked                                  */
    uint8_t    solnsvs;                     /**< Number of satellite vehicles used in solution                 */
    uint8_t    ggl1;                        /**< Number of GPS plus GLONASS plus BDS L1/B1 used in solution    */
    uint8_t    solnmultisvs;                /**< Number of satellites with L1/E1/B1 signals used in solution   */
    uint8_t    reserved;                    /**<                                                               */
    uint8_t    ext_sol_stat;                /**< Extended solution status                                      */
    uint8_t    galileo_and_beidou_sig_mask; /**< Galileo and BeiDou signals used mask                          */
    uint8_t    gps_and_glonass_sig_mask;    /**< GPS and GLONASS signals used mask                             */
    uint32_t   crc32;                       /**< 32-bit CRC                                                    */
    char       end[2];                      /**< CR + LF                                                       */
} PACKED gnss_xyz_t;


/**
 * @brief Response to LOG TIMEA (structure taken from OEM719 user manual)
 */
typedef struct
{
    gnss_hdr_t header;
    uint32_t   clock_status;                /**< Clock model status (not including current measurement data)                     */
    double     offset;                      /**< Receiver clock offset in seconds from GPS system time.                          */
    double     offset_std;                  /**< Receiver clock offset standard deviation (s)                                    */
    double     utc_offset;                  /**< The offset of GPS system time from UTC time, computed using almanac parameters. */
    uint32_t   utc_year;                    /**< UTC year                                                                        */
    uint8_t    utc_month;                   /**< UTC month (0-12). If UTC time is unknown, the value for month is 0.             */
    uint8_t    utc_day;                     /**< UTC day (0-31). If UTC time is unknown, the value for day is 0.                 */
    uint8_t    utc_hour;                    /**< UTC hour (0-23)                                                                 */
    uint8_t    utc_min;                     /**< UTC minute (0-59)                                                               */
    uint32_t   utc_ms;                      /**< UTC millisecond (0-60999). Maximum of 60999 when leap second is applied.        */
    uint32_t   utc_status;                  /**< UTC status 0 = Invalid, 1 = Valid, 2 = Warning                                  */
    uint32_t   crc32;                       /**< 32-bit CRC                                                                      */
    char       end[2];                      /**< CR + LF                                                                         */
} PACKED gnss_time_t;


#ifdef __cplusplus
}
#endif

#endif /* GNSS_TYPES_H_ */
