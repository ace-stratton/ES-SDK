/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_config.c
 *
 * @brief GNSS driver configuration
 *
 * @}
 * @}
 */
#include "gnss.h"
#include "sys_time.h"
#include "datacache.h"
#include "trace.h"

#if defined CUBEADCS_GEN2_ENABLED
#include "if_sys_conf.h"
#include "cubeadcs_gen2_gw.h"
#include <cubeObc/arch/cubeObc_critical.h>
#endif // CUBEADCS_GEN2_ENABLED


/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

#if defined CUBEADCS_GEN2_ENABLED
/**
 * @brief is set to 1 - enables periodic time sync with GNSS
 */
#define FS_TIME_SYNC_ENABLE (0)

/**
 * @brief Conversion multiplier for position and velocity vector data
 */
#define NUM_CM_IN_M 100U

/**
 * @brief Conversion multiplier for fractional part of the Unix time stamp
 */
#define NUM_NS_IN_MS 1000000U

/**
 * @brief 60 seconds * 60 minutes * 24 hours * 7 days
 */
#define NUM_SEC_IN_WEEK 604800U

/**
 * @brief The number of seconds between 00:00:00 UTC on 1 January 1970 (Unix epoch) and 00:00:00 UTC on January 6, 1980 (GPS epoch)
 */
#define GPS_TO_UNIX_OFFSET 315964800U

/**
 * @brief Value of the clock status which indicates that the clock data can be used
 */
#define GNSS_CLOCK_STATUS_VALID 0U

/**
 * @brief Value of the position and velocity vectors' solution status which indicates that XYZ data can be used
 */
#define GNSS_XYZ_SOL_STAT_COMPUTED 0U

/**
 * @brief Value of the lowest time status which indicates that time is known with sufficient precision
 */
#define GNSS_TIM_STAT_FINE 160U

/**
 * @brief Value of the UTC status which indicates that time data can be used
 */
#define GNSS_UTC_STATUS_VALID 1U

/**
 * @brief Multiplier reciprocal to the accuracy of the GPS seconds reported by GNSS
 */
#define GPS_SEC_ACCURACY_MULT 1000U

/**
 * @brief Floating point comparison epsilon for the GPS seconds of TIME and BESTXYZ GNSS logs
 */
#define REF_TIME_EPSILON 0.5F

/**
 * @brief Timeout in milliseconds for the attempt to enter critical section of the ADCS API
 *
 * @note This timeout should be as small as possible. It is better to skip sending GNSS data than to send it with
 *       an unknown delay due to other components holding the critical section for an unknown amount of time
 */
#define ADCS_CRITICAL_SECTION_TIMEOUT 1U

/**
 * @brief Timeout in milliseconds of the command to ADCS which carries time and position data
 *
 * @note Value must be chosen so that the time between PPS pulse and completed transmission of the data
 *       is less than 100ms. This is requested by CubeSpace
 */
#define ADCS_COMM_TIMEOUT 60U

/**
 * @brief Defines whether the RTC of Gen2 CubeADCS is to be synchronized with the time data coming from GNSS
 *
 * @note  Usually set to FALSE if the ADCS has the PPS of the GNSS as direct input
 */
#define ADCS_RTC_SYNCH FALSE


#endif // CUBEADCS_GEN2_ENABLED
/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/


/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/


/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

#if FS_TIME_SYNC_ENABLE
static inline uint32_t fs_msec_to_sec(const uint32_t msec);
static inline uint32_t fs_sec_to_msec(const uint32_t sec);
#endif // FS_TIME_SYNC_ENABLE

#if defined CUBEADCS_GEN2_ENABLED
static void send_cmd_to_gen2_cubeadcs(const gnss_time_t * const p_time, const gnss_xyz_t* const p_xyz);
static void gnss_config_adcs_sync_callback(void);
#endif // CUBEADCS_GEN2_ENABLED


/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/


/**
 * @brief This callback is invoked on every new reception of position/velocity logs.
 *
 * @note Make sure to not put heavy operations inside the callback as this might lead to
 *       missed log events.
 *
 * @param[in] pv Parsed position/velocity log
 */
void gnss_config_pv_callback(const gnss_xyz_t* pv)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_GNSS_BESTXYZ_DATA, pv, sizeof(gnss_xyz_t));

#if defined CUBEADCS_GEN2_ENABLED
    gnss_config_adcs_sync_callback();
#endif // CUBEADCS_GEN2_ENABLED
}


/**
 * @brief This callback is invoked on every new reception of time logs.
 *
 * @note Make sure to not put heavy operations inside the callback as this might lead to
 *       missed log events.
 *
 * @note The data is validated only for its format and CRC. In order to make sure that the time itself
 *       is correct the user can use @ref gnss_is_tm_valid()
 *
 * @param[in] tim Parsed time log
 */
void gnss_config_tm_callback(const gnss_time_t* t)
{
#if FS_TIME_SYNC_ENABLE
    sys_time_t tim;
    sys_date_t date;

    if (true == gnss_is_tm_valid(t))
    {
        date.year = (uint16_t)t->utc_year;
        date.mon  = t->utc_month;
        date.day  = t->utc_day;

        tim.hour = t->utc_hour;
        tim.min  = t->utc_min;
        tim.sec  = (uint8_t)fs_msec_to_sec(t->utc_ms);
        tim.ms   = (uint16_t)(t->utc_ms - fs_sec_to_msec(tim.sec));

        sys_time_set(&tim);
        sys_time_set_date(&date);
    }
#endif

    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_GNSS_TIME_DATA, t, sizeof(gnss_time_t));

#if defined CUBEADCS_GEN2_ENABLED
    gnss_config_adcs_sync_callback();
#endif // CUBEADCS_GEN2_ENABLED
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

#if FS_TIME_SYNC_ENABLE
/**
 * @brief Converts milliseconds to seconds
 *
 * @param[in] msec Milliseconds
 *
 * @return uint32_t Seconds
 */
static inline uint32_t fs_msec_to_sec(const uint32_t msec)
{
    return (msec / 1000);
}


/**
 * @brief Converts seconds to milliseconds
 *
 * @param[in] sec Seconds
 * @return uint32_t Milliseconds
 */
static inline uint32_t fs_sec_to_msec(const uint32_t sec)
{
    return (sec * 1000U);
}
#endif


#if defined CUBEADCS_GEN2_ENABLED
/**
 * @brief Sends time and position data to ADCS for synchronization purposes
 *
 * @param[in] p_time Reference to TIME log data from GNSS
 * @param[in] p_xyz Reference to BESTXYZ log data from GNSS
 */
static void send_cmd_to_gen2_cubeadcs(const gnss_time_t * const p_time, const gnss_xyz_t* const p_xyz)
{
    if ((NULL != p_time) &&
        (NULL != p_xyz) &&
        (GNSS_XYZ_SOL_STAT_COMPUTED == p_xyz->p_sol_status) &&                      // Is the BESTXYZ position vector data reliable?
        (GNSS_XYZ_SOL_STAT_COMPUTED == p_xyz->v_sol_status) &&                      // Is the BESTXYZ velocity vector data reliable?
        (GNSS_TIM_STAT_FINE <= p_xyz->header.time_status) &&                        // Is the quality of GPS time measurements sufficient?
        (GNSS_UTC_STATUS_VALID == p_time->utc_status))                              // Can we trust the UTC time data?
    {

        // Accumulate Unix seconds by beginning with the whole weeks since the GPS epoch.
        // We use 64-bit integer to avoid multiple overflow checks
        uint64_t unix_sec_long = ((uint64_t)p_time->header.week * NUM_SEC_IN_WEEK) + GPS_TO_UNIX_OFFSET;

        // Add the seconds in current week.
        // Compensate deviation (dOffset) of GPS receiver clock from GPS system time to increase accuracy.
        // Also adjust with UTC offset to get the UTC time encoded in the Unix timestamp.
        // Double type is used to avoid overflow checks.
        const double unix_sec_dbl = (double)unix_sec_long + p_time->header.seconds + p_time->utc_offset - p_time->offset;

        if (unix_sec_dbl < ((double)UINT_MAX + 1)) // Because check for equality is a bit tricky with doubles
        {
            // Calculate the milliseconds fractional part.
            const uint32_t msec = (uint32_t)((unix_sec_dbl - (uint32_t)unix_sec_dbl) * GPS_SEC_ACCURACY_MULT);

            // Prepare command to ADCS
            TctlmCubeComputerControlProgram8_GnssSensorCmd adcs_cmd;
            // No overflow expected for the position coordinates, because they are normally between -7000000m and 7000000m
            adcs_cmd.gnssSatPosX = (S32)(p_xyz->px * NUM_CM_IN_M);
            adcs_cmd.gnssSatPosY = (S32)(p_xyz->py * NUM_CM_IN_M);
            adcs_cmd.gnssSatPosZ = (S32)(p_xyz->pz * NUM_CM_IN_M);
            // No overflow for the velocity vectors, because they cannot exceed 8000m/s
            adcs_cmd.gnssSatVelX = (S32)(p_xyz->vx * NUM_CM_IN_M);
            adcs_cmd.gnssSatVelY = (S32)(p_xyz->vy * NUM_CM_IN_M);
            adcs_cmd.gnssSatVelZ = (S32)(p_xyz->vz * NUM_CM_IN_M);
            adcs_cmd.gnssTimeSeconds = (U32) unix_sec_dbl;
            adcs_cmd.gnssTimeNs = msec * NUM_NS_IN_MS;

            adcs_cmd.syncTime = ADCS_RTC_SYNCH;

            // Send command to ADCS
            if (true == cubeObc_critical_enter(ADCS_CRITICAL_SECTION_TIMEOUT))
            {
                TypeDef_TctlmEndpoint endpoint;
                cubeadcs_gen2_setup_endpoint(&endpoint, TYPEDEF__COMMS_ENDPOINT_UART, ADCS_COMM_TIMEOUT);
                const ErrorCode err = tctlmCubeComputerControlProgram8_setGnssSensorCmd(&endpoint, &adcs_cmd);
                cubeObc_critical_exit();
                if (err != CUBEOBC_ERROR_OK)
                {
                    ES_TRACE_WARN("Could not send GNSS data to Gen2 CubeADCS!");
                }
            }

        }
        else
        {
            ES_TRACE_ERROR("Overflow error!");
        }
    }
}

/**
 * @brief This callback is invoked on every new reception of logs that contain data to be sent to ADCS module.
 *
 * @note Make sure to not put heavy operations inside the callback as this might lead to
 *       missed log events.
 *
 * @note Relevant log data is read from DataCache.
 */
static void gnss_config_adcs_sync_callback(void)
{
    if (false != sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
    {
        DATA_CACHE_GNSS_TIME_t time_data;
        (void)dc_get_gnss_time_data(&time_data);
        static_assert(sizeof(DATA_CACHE_GNSS_TIME_t) == sizeof(gnss_time_t));
        const gnss_time_t * const p_time = (const gnss_time_t* const)&time_data;
        if (true == gnss_is_tm_valid(p_time))
        {
            DATA_CACHE_GNSS_BESTXYZ_t pos_data;
            (void)dc_get_gnss_bestxyz_data(&pos_data);
            static_assert(sizeof(DATA_CACHE_GNSS_BESTXYZ_t) == sizeof(gnss_xyz_t));
            const gnss_xyz_t * const p_xyz = (const gnss_xyz_t * const)&pos_data;

            if (fabs(p_xyz->header.seconds - p_time->header.seconds) < REF_TIME_EPSILON ) // Are TIME and BESTXYZ logs for the same second?)
            {
                send_cmd_to_gen2_cubeadcs(p_time, p_xyz);
            }
        }
    }
}

#endif // CUBEADCS_GEN2_ENABLED

