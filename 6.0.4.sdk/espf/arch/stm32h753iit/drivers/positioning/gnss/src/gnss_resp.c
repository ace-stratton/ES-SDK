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
 * @file gnss_resp.c
 *
 *
 * @}
 * @}
 */
#include "gnss_resp.h"
#include <string.h>
#include <stdlib.h>


#define FS_CRC32_POLYNOMIAL      0xEDB88320L
#define FS_STATIC_STRLEN(str)    (sizeof(str) - 1)

#define UNKNOWN                  "UNKNOWN"
#define APPROXIMATE              "APPROXIMATE"
#define COARSEADJUSTING          "COARSEADJUSTING"
#define COARSE                   "COARSE"
#define COARSESTEERING           "COARSESTEERING"
#define FREEWHEELING             "FREEWHEELING"
#define FINEADJUSTING            "FINEADJUSTING"
#define FINE                     "FINE"
#define FINEBACKUPSTEERING       "FINEBACKUPSTEERING"
#define FINESTEERING             "FINESTEERING"
#define SATTIME                  "SATTIME"
#define VALID                    "VALID"
#define CONVERGING               "CONVERGIN"
#define ITERATING                "ITERATING"
#define INVALID                  "INVALID"
#define WARNING                  "WARNING"
#define SOL_COMPUTED             "SOL_COMPUTED"
#define INSUFFICIENT_OBS         "INSUFFICIENT_OBS"
#define NO_CONVERGENCE           "NO_CONVERGENCE"
#define SINGULARITY              "SINGULARITY"
#define COV_TRACE                "COV_TRACE"
#define TEST_DIST                "TEST_DIST"
#define COLD_START               "COLD_START"
#define V_H_LIMIT                "V_H_LIMIT"
#define VARIANCE                 "VARIANCE"
#define RESIDUALS                "RESIDUALS"
#define INTEGRITY_WARNING        "INTEGRITY_WARNING"
#define PENDING                  "PENDING"
#define INVALID_FIX              "INVALID_FIX"
#define UNAUTHORIZED             "UNAUTHORIZED"
#define INVALID_RATE             "INVALID_RATE"
#define NONE                     "NONE"
#define FIXEDPOS                 "FIXEDPOS"
#define FIXEDHEIGHT              "FIXEDHEIGHT"
#define DOPPLER_VELOCITY         "DOPPLER_VELOCITY"
#define SINGLE                   "SINGLE"
#define PSRDIFF                  "PSRDIFF"
#define WAAS                     "WAAS"
#define PROPAGATED               "PROPAGATED"
#define L1_FLOAT                 "L1_FLOAT"
#define NARROW_FLOAT             "NARROW_FLOAT"
#define L1_INT                   "L1_INT"
#define WIDE_INT                 "WIDE_INT"
#define NARROW_INT               "NARROW_INT"
#define RTK_DIRECT_INS           "RTK_DIRECT_INS"
#define INS_SBAS                 "INS_SBAS"
#define INS_PSRSP                "INS_PSRSP"
#define INS_PSRDIFF              "INS_PSRDIFF"
#define INS_RTKFLOAT             "INS_RTKFLOAT"
#define INS_RTKFIXED             "INS_RTKFIXED"
#define PPP_CONVERGING           "PPP_CONVERGING"
#define PPP                      "PPP"
#define OPERATIONAL              "OPERATIONAL"
#define OUT_OF_BOUNDS            "OUT_OF_BOUNDS"
#define INS_PPP_CONVERGING       "INS_PPP_CONVERGING"
#define INS_PPP                  "INS_PPP"
#define PPP_BASIC_CONVERGING     "PPP_BASIC_CONVERGING"
#define PPP_BASIC                "PPP_BASIC"
#define INS_PPP_BASIC_CONVERGING "INS_PPP_BASIC_CONVERGING"
#define INS_PPP_BASIC            "INS_PPP_BASIC"


static bool        fs_parse_ascii_hdr(const gnss_ascii_resp_info_t* const info, gnss_hdr_t* const hdr);
static bool        fs_verify_info(const gnss_ascii_resp_info_t* const info);
static const char* fs_strnchr(const char* start, const char* end, const char ch);
static const char* fs_strnstrn(const char* str1, const uint32_t str1_len, const char* str2, const uint32_t str2_len);
static uint32_t    fs_crc32_value(const uint32_t i);
static uint32_t    fs_crc32_calculate_block(const uint8_t* buf, const uint32_t buf_sz);
static uint32_t    fs_get_ascii_time_status(const char* data, uint32_t data_sz);
static uint32_t    fs_get_clock_status(const char* data, uint32_t data_sz);
static uint32_t    fs_get_utc_status(const char* data, uint32_t data_sz);
static uint32_t    fs_get_solution_status(const char* data, uint32_t data_sz);
static uint32_t    fs_get_pv_type(const char* data, uint32_t data_sz);


bool gnss_resp_parse_ascii_pv(const gnss_ascii_resp_info_t* const info, gnss_xyz_t* const pv)
{
    if (false == fs_verify_info(info))
    {
        return false;
    }

    if (false == fs_parse_ascii_hdr(info, (gnss_hdr_t*)pv))
    {
        return false;
    }

    const char delim = ',';
    const char* ch1 = fs_strnchr(info->data_start, info->data_end, delim);
    if (NULL == ch1)
    {
        return false;
    }

    pv->p_sol_status = fs_get_solution_status(info->data_start, (uint32_t)(ch1 - info->data_start));
    ch1 += 1;
    const char* ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->pos_type = fs_get_pv_type(ch1, (uint32_t)(ch2 - ch1));
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->px = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->py = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->pz = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->pxo = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->pyo = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->pzo = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->v_sol_status = fs_get_solution_status(ch1, (uint32_t)(ch2 - ch1));
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->vel_type = fs_get_pv_type(ch1, (uint32_t)(ch2 - ch1));
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->vx = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->vy = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->vz = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->vxo = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->vyo = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->vzo = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    if (ch2 < ch1)
    {
        return false;
    }

    if (sizeof(pv->stn_id) < (size_t)(ch2 - ch1))
    {
        return false;
    }

    (void)memset(pv->stn_id, 0, sizeof(pv->stn_id));
    (void)memcpy(pv->stn_id, ch1, (size_t)(ch2 - ch1));
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->v_latency = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->diff_age = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    pv->sol_age = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    uint32_t val;

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->svs = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->solnsvs = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->ggl1 = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->solnmultisvs = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->reserved = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 16);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->ext_sol_stat = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 16);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->galileo_and_beidou_sig_mask = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->crc_start, '*');
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 16);

    if (UINT8_MAX < val)
    {
        return false;
    }

    pv->gps_and_glonass_sig_mask = (uint8_t)val;
    ch1 = ch2 + 1;
    if (info->crc_end < ch1)
    {
        return false;
    }

    pv->crc32 = strtoul(info->crc_start, NULL, 16);

    pv->end[0] = *info->crc_end;
    pv->end[1] = '\n';

    return true;
}


bool gnss_resp_parse_ascii_tm(const gnss_ascii_resp_info_t* const info, gnss_time_t* const tim)
{
    if (false == fs_verify_info(info))
    {
        return false;
    }

    if (false == fs_parse_ascii_hdr(info, (gnss_hdr_t*)tim))
    {
        return false;
    }

    const char delim = ',';
    const char* ch1 = fs_strnchr(info->data_start, info->data_end, delim);

    tim->clock_status = fs_get_clock_status(info->data_start, (uint32_t)(ch1 - info->data_start));
    ch1 += 1;
    const char* ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    tim->offset = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    tim->offset_std = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    tim->utc_offset = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    tim->utc_year = strtoul(ch1, NULL, 10);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    uint32_t val;

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    tim->utc_month = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    tim->utc_day = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    tim->utc_hour = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    val = strtoul(ch1, NULL, 10);

    if (UINT8_MAX < val)
    {
        return false;
    }

    tim->utc_min = (uint8_t)val;
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->data_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    tim->utc_ms = strtoul(ch1, NULL, 10);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->crc_start, '*');
    if (NULL == ch2)
    {
        return false;
    }

    tim->utc_status = fs_get_utc_status(ch1, (uint32_t)(ch2 - ch1));
    ch1 = ch2 + 1;
    if (info->crc_end < ch1)
    {
        return false;
    }

    tim->crc32 = strtoul(ch1, NULL, 16);

    tim->end[0] = '\r';
    tim->end[1] = '\n';

    return true;
}


bool gnss_resp_is_ascii(const char* const data, const uint32_t data_sz)
{
    bool res = false;

    for (uint32_t i = 0; i < data_sz; i++)
    {
        // The receiver only accepts the following ASCII characters:
        //   1. characters between space (ASCII value 32) and '~' (ASCII value 126) inclusive
        //   2. vertical tab (ASCII value 9)
        //   3. line feed (ASCII value 10)
        //   4. horizontal tab (ASCII value 11)
        //   5. carriage return (ASCII value 13)
        if ((( 32 <= data[i])  &&
             (132 >= data[i])) ||
            (9  == data[i])  ||
            (10 == data[i])  ||
            (11 == data[i])  ||
            (13 == data[i]))
        {
            res = true;
        }
        else
        {
            res = false;
            break;
        }
    }

    return res;
}


bool gnss_resp_is_ascii_crc_valid(const gnss_ascii_resp_info_t* const info)
{
    bool ret = false;

    if (true == fs_verify_info(info))
    {
        uint32_t size = info->header_size + info->data_size;
        uint32_t crc32_calc = fs_crc32_calculate_block((const uint8_t*)info->header_start + 1, size);
        uint32_t crc32_recv = strtoul(info->crc_start, NULL, 16);

        if (crc32_calc == crc32_recv)
        {
            ret = true;
        }
    }

    return ret;
}


bool gnss_resp_get_ascii_info(const char* const data, const uint32_t data_sz, gnss_ascii_resp_info_t* const info)
{
    bool ret = false;

    if ((NULL != data) && (0 != data_sz) && (NULL != info))
    {
        info->header_start = fs_strnchr(data, (data + data_sz), '#');
        info->header_end   = fs_strnchr(info->header_start, (data + data_sz), ';');
        info->header_size  = (uint32_t)(info->header_end - info->header_start);
        info->data_start   = info->header_end + 1;
        info->data_end     = fs_strnchr(info->data_start, (data + data_sz), '*');
        info->data_size    = (uint32_t)(info->data_end - info->data_start);
        info->star         = info->data_end;
        info->crc_start    = info->star + 1;
        info->crc_end      = fs_strnchr(info->star, (data + data_sz), '\r');
        info->crc_size     = (uint32_t)(info->crc_end - info->crc_start);
        info->total_size   = (uint32_t)(info->crc_end + 2 - info->header_start); // +2 because of CR/LF

        if (true == fs_verify_info(info))
        {
            ret = true;
        }
    }


    return ret;
}


/**
 * @brief Verifies info structure limits
 *
 * @param[in] info Structure to be tested
 *
 * @retVal false Failed
 * @retVal true  Success
 */
static bool fs_verify_info(const gnss_ascii_resp_info_t* const info)
{
    bool ret = true;

    if ((NULL == info) ||
        ((NULL == info->header_start) || ((info->header_start + info->total_size) < info->header_start)) ||
        ((NULL == info->header_end  ) || ((info->header_start + info->total_size) < info->header_end  )) ||
        ((NULL == info->data_start  ) || ((info->header_start + info->total_size) < info->data_start  )) ||
        ((NULL == info->data_end    ) || ((info->header_start + info->total_size) < info->data_end    )) ||
        ((NULL == info->star        ) || ((info->header_start + info->total_size) < info->star        )) ||
        ((NULL == info->crc_start   ) || ((info->header_start + info->total_size) < info->crc_start   )) ||
        ((NULL == info->crc_end     ) || ((info->header_start + info->total_size) < info->crc_end     )))
    {
        ret = false;
    }

    return ret;
}


/**
 * @brief Extracts response header from raw data
 *
 * @param[in]  info Response information
 * @param[out] hdr  Parsed header
 *
 * @retVal false Failed
 * @retVal true  Success
 */
static bool fs_parse_ascii_hdr(const gnss_ascii_resp_info_t* const info, gnss_hdr_t* const hdr)
{
    if ((NULL == hdr) || (NULL == info) || (NULL == info->header_start))
    {
        return false;
    }

    const char* name_start = info->header_start + 1;
    const char  delim      = ',';

    const char* ch1 = fs_strnchr(name_start, info->header_end, delim);
    if (NULL == ch1)
    {
        return false;
    }

    // sync
    hdr->sync = info->header_start[0];

    if (sizeof(hdr->message) < (size_t)(ch1 - name_start))
    {
        return false;
    }

    (void)memset(hdr->message, 0, sizeof(hdr->message));
    (void)memcpy(hdr->message, name_start, (size_t)(ch1 - name_start));
    ch1 += 1;
    const char* ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // port
    if (ch2 < ch1)
    {
        return false;
    }

    if (sizeof(hdr->port) < (size_t)(ch2 - ch1))
    {
        return false;
    }

    (void)memset(hdr->port, 0, sizeof(hdr->port));
    (void)memcpy(hdr->port, ch1, (size_t)(ch2 - ch1));
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // sequence
    hdr->sequence = strtol(ch1, NULL, 10);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // idle time
    hdr->idle_time = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // time status
    hdr->time_status = fs_get_ascii_time_status(ch1, (uint32_t)(ch2 - ch1));
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // week
    hdr->week = strtoul(ch1, NULL, 10);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // seconds
    hdr->seconds = strtof(ch1, NULL);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // receiver status
    hdr->receiver_status = strtoul(ch1, NULL, 16);
    ch1 = ch2 + 1;
    ch2 = fs_strnchr(ch1, info->header_end, delim);
    if (NULL == ch2)
    {
        return false;
    }

    // reserved
    hdr->reserved = strtoul(ch1, NULL, 10);
    ch1 = ch2 + 1;
    if ((NULL == ch1) || (info->header_end < ch1))
    {
        return false;
    }

    // receiver sw version
    hdr->receiver_sw_version = strtoul(ch1, NULL, 10);

    // end
    hdr->end = info->header_end[0];

    return true;
}


/**
 * @brief Calculates CRC of single byte.
 *        Algorithm taken from OEM719 user manual
 *
 * @param[in] i Integer
 *
 * @return Byte CRC
 */
static uint32_t fs_crc32_value(const uint32_t i)
{
    uint32_t crc32 = i;

    for (uint8_t j = 8; j > 0; j--)
    {
        if (0 != (crc32 & 1))
        {
            crc32 = (crc32 >> 1) ^ FS_CRC32_POLYNOMIAL;
        }
        else
        {
            crc32 >>= 1;
        }
    }

    return crc32;
}


/**
 * @brief Calculates CRC32 of a byte buffer. Algorithm taken from OEM719 user manual.
 * 
 * @param[in] buf    Byte buffer
 * @param[in] buf_sz Byte buffer size
 * 
 * @return CRC32
 */
static uint32_t fs_crc32_calculate_block(const uint8_t* buf, const uint32_t buf_sz)
{
    uint32_t temp1;
    uint32_t temp2;
    uint32_t crc32 = 0;
    uint32_t sz = buf_sz;
    uint32_t i = 0;

    while (sz != 0)
    {
        temp1 = (crc32 >> 8) & 0x00FFFFFFL;
        temp2 = fs_crc32_value((crc32 ^ buf[i]) & 0xFF);
        crc32 = temp1 ^ temp2;

        sz--;
        i++;
    }

    return crc32;
}


/**
 * @brief Converts time status string to integer.
 *        The values are taken from oem719 user manual
 *
 * @param[in] data String
 * @param[in] data_sz String size in bytes
 *
 * @return Equivalent integer value
 */
static uint32_t fs_get_ascii_time_status(const char* data, uint32_t data_sz)
{
    uint32_t ret;

    if      (NULL != fs_strnstrn(UNKNOWN,            FS_STATIC_STRLEN(UNKNOWN           ), data, data_sz)) { ret =  20; }
    else if (NULL != fs_strnstrn(APPROXIMATE,        FS_STATIC_STRLEN(APPROXIMATE       ), data, data_sz)) { ret =  60; }
    else if (NULL != fs_strnstrn(COARSEADJUSTING,    FS_STATIC_STRLEN(COARSEADJUSTING   ), data, data_sz)) { ret =  80; }
    else if (NULL != fs_strnstrn(COARSE,             FS_STATIC_STRLEN(COARSE            ), data, data_sz)) { ret = 100; }
    else if (NULL != fs_strnstrn(COARSESTEERING,     FS_STATIC_STRLEN(COARSESTEERING    ), data, data_sz)) { ret = 120; }
    else if (NULL != fs_strnstrn(FREEWHEELING,       FS_STATIC_STRLEN(FREEWHEELING      ), data, data_sz)) { ret = 130; }
    else if (NULL != fs_strnstrn(FINEADJUSTING,      FS_STATIC_STRLEN(FINEADJUSTING     ), data, data_sz)) { ret = 140; }
    else if (NULL != fs_strnstrn(FINE,               FS_STATIC_STRLEN(FINE              ), data, data_sz)) { ret = 160; }
    else if (NULL != fs_strnstrn(FINEBACKUPSTEERING, FS_STATIC_STRLEN(FINEBACKUPSTEERING), data, data_sz)) { ret = 170; }
    else if (NULL != fs_strnstrn(FINESTEERING,       FS_STATIC_STRLEN(FINESTEERING      ), data, data_sz)) { ret = 180; }
    else if (NULL != fs_strnstrn(SATTIME,            FS_STATIC_STRLEN(SATTIME           ), data, data_sz)) { ret = 200; }
    else                                                                                                   { ret =   0; }

    return ret;
}


/**
 * @brief Converts clock status string to integer.
 *        The values are taken from oem719 user manual
 *
 * @param[in] data String
 * @param[in] data_sz String size in bytes
 *
 * @return Equivalent integer value
 */
static uint32_t fs_get_clock_status(const char* data, uint32_t data_sz)
{
    uint32_t ret;

    if      (NULL != fs_strnstrn(VALID,      FS_STATIC_STRLEN(VALID     ), data, data_sz)) { ret = 0; }
    else if (NULL != fs_strnstrn(CONVERGING, FS_STATIC_STRLEN(CONVERGING), data, data_sz)) { ret = 1; }
    else if (NULL != fs_strnstrn(ITERATING,  FS_STATIC_STRLEN(ITERATING ), data, data_sz)) { ret = 2; }
    else if (NULL != fs_strnstrn(INVALID,    FS_STATIC_STRLEN(INVALID   ), data, data_sz)) { ret = 3; }
    else                                                                                   { ret = 4; }

    return ret;
}


/**
 * @brief Converts utc status string to integer.
 *        The values are taken from oem719 user manual
 *
 * @param[in] data String
 * @param[in] data_sz String size in bytes
 *
 * @return Equivalent integer value
 */
static uint32_t fs_get_utc_status(const char* data, uint32_t data_sz)
{
    uint32_t ret;

    if      (NULL != fs_strnstrn(INVALID, FS_STATIC_STRLEN(INVALID), data, data_sz)) { ret = 0; }
    else if (NULL != fs_strnstrn(VALID,   FS_STATIC_STRLEN(VALID),   data, data_sz)) { ret = 1; }
    else if (NULL != fs_strnstrn(WARNING, FS_STATIC_STRLEN(WARNING), data, data_sz)) { ret = 2; }
    else                                                                             { ret = 3; }

    return ret;
}


/**
 * @brief Converts solution status string to integer.
 *        The values are taken from oem719 user manual
 *
 * @param[in] data String
 * @param[in] data_sz String size in bytes
 *
 * @return Equivalent integer value
 */
static uint32_t fs_get_solution_status(const char* data, uint32_t data_sz)
{
    uint32_t ret;

    if      (NULL != fs_strnstrn(SOL_COMPUTED,      FS_STATIC_STRLEN(SOL_COMPUTED     ), data, data_sz)) { ret =  0; }
    else if (NULL != fs_strnstrn(INSUFFICIENT_OBS,  FS_STATIC_STRLEN(INSUFFICIENT_OBS ), data, data_sz)) { ret =  1; }
    else if (NULL != fs_strnstrn(NO_CONVERGENCE,    FS_STATIC_STRLEN(NO_CONVERGENCE   ), data, data_sz)) { ret =  2; }
    else if (NULL != fs_strnstrn(SINGULARITY,       FS_STATIC_STRLEN(SINGULARITY      ), data, data_sz)) { ret =  3; }
    else if (NULL != fs_strnstrn(COV_TRACE,         FS_STATIC_STRLEN(COV_TRACE        ), data, data_sz)) { ret =  4; }
    else if (NULL != fs_strnstrn(TEST_DIST,         FS_STATIC_STRLEN(TEST_DIST        ), data, data_sz)) { ret =  5; }
    else if (NULL != fs_strnstrn(COLD_START,        FS_STATIC_STRLEN(COLD_START       ), data, data_sz)) { ret =  6; }
    else if (NULL != fs_strnstrn(V_H_LIMIT,         FS_STATIC_STRLEN(V_H_LIMIT        ), data, data_sz)) { ret =  7; }
    else if (NULL != fs_strnstrn(VARIANCE,          FS_STATIC_STRLEN(VARIANCE         ), data, data_sz)) { ret =  8; }
    else if (NULL != fs_strnstrn(RESIDUALS,         FS_STATIC_STRLEN(RESIDUALS        ), data, data_sz)) { ret =  9; }
    else if (NULL != fs_strnstrn(INTEGRITY_WARNING, FS_STATIC_STRLEN(INTEGRITY_WARNING), data, data_sz)) { ret = 13; }
    else if (NULL != fs_strnstrn(PENDING,           FS_STATIC_STRLEN(PENDING          ), data, data_sz)) { ret = 18; }
    else if (NULL != fs_strnstrn(INVALID_FIX,       FS_STATIC_STRLEN(INVALID_FIX      ), data, data_sz)) { ret = 19; }
    else if (NULL != fs_strnstrn(UNAUTHORIZED,      FS_STATIC_STRLEN(UNAUTHORIZED     ), data, data_sz)) { ret = 20; }
    else if (NULL != fs_strnstrn(INVALID_RATE,      FS_STATIC_STRLEN(INVALID_RATE     ), data, data_sz)) { ret = 22; }
    else                                                                                                 { ret = 23; }

    return ret;
}


/**
 * @brief Converts position type string to integer.
 *        The values are taken from oem719 user manual
 *
 * @param[in] data String
 * @param[in] data_sz String size in bytes
 *
 * @return Equivalent integer value
 */
static uint32_t fs_get_pv_type(const char* data, uint32_t data_sz)
{
    uint32_t ret;

    if      (NULL != fs_strnstrn(NONE,                     FS_STATIC_STRLEN(NONE                    ), data, data_sz)) { ret =  0; }
    else if (NULL != fs_strnstrn(FIXEDPOS,                 FS_STATIC_STRLEN(FIXEDPOS                ), data, data_sz)) { ret =  1; }
    else if (NULL != fs_strnstrn(FIXEDHEIGHT,              FS_STATIC_STRLEN(FIXEDHEIGHT             ), data, data_sz)) { ret =  2; }
    else if (NULL != fs_strnstrn(DOPPLER_VELOCITY,         FS_STATIC_STRLEN(DOPPLER_VELOCITY        ), data, data_sz)) { ret =  8; }
    else if (NULL != fs_strnstrn(SINGLE,                   FS_STATIC_STRLEN(SINGLE                  ), data, data_sz)) { ret = 16; }
    else if (NULL != fs_strnstrn(PSRDIFF,                  FS_STATIC_STRLEN(PSRDIFF                 ), data, data_sz)) { ret = 17; }
    else if (NULL != fs_strnstrn(WAAS,                     FS_STATIC_STRLEN(WAAS                    ), data, data_sz)) { ret = 18; }
    else if (NULL != fs_strnstrn(PROPAGATED,               FS_STATIC_STRLEN(PROPAGATED              ), data, data_sz)) { ret = 19; }
    else if (NULL != fs_strnstrn(L1_FLOAT,                 FS_STATIC_STRLEN(L1_FLOAT                ), data, data_sz)) { ret = 32; }
    else if (NULL != fs_strnstrn(NARROW_FLOAT,             FS_STATIC_STRLEN(NARROW_FLOAT            ), data, data_sz)) { ret = 34; }
    else if (NULL != fs_strnstrn(L1_INT,                   FS_STATIC_STRLEN(L1_INT                  ), data, data_sz)) { ret = 48; }
    else if (NULL != fs_strnstrn(WIDE_INT,                 FS_STATIC_STRLEN(WIDE_INT                ), data, data_sz)) { ret = 49; }
    else if (NULL != fs_strnstrn(NARROW_INT,               FS_STATIC_STRLEN(NARROW_INT              ), data, data_sz)) { ret = 50; }
    else if (NULL != fs_strnstrn(RTK_DIRECT_INS,           FS_STATIC_STRLEN(RTK_DIRECT_INS          ), data, data_sz)) { ret = 51; }
    else if (NULL != fs_strnstrn(INS_SBAS,                 FS_STATIC_STRLEN(INS_SBAS                ), data, data_sz)) { ret = 52; }
    else if (NULL != fs_strnstrn(INS_PSRSP,                FS_STATIC_STRLEN(INS_PSRSP               ), data, data_sz)) { ret = 53; }
    else if (NULL != fs_strnstrn(INS_PSRDIFF,              FS_STATIC_STRLEN(INS_PSRDIFF             ), data, data_sz)) { ret = 54; }
    else if (NULL != fs_strnstrn(INS_RTKFLOAT,             FS_STATIC_STRLEN(INS_RTKFLOAT            ), data, data_sz)) { ret = 55; }
    else if (NULL != fs_strnstrn(INS_RTKFIXED,             FS_STATIC_STRLEN(INS_RTKFIXED            ), data, data_sz)) { ret = 56; }
    else if (NULL != fs_strnstrn(PPP_CONVERGING,           FS_STATIC_STRLEN(PPP_CONVERGING          ), data, data_sz)) { ret = 68; }
    else if (NULL != fs_strnstrn(PPP,                      FS_STATIC_STRLEN(PPP                     ), data, data_sz)) { ret = 69; }
    else if (NULL != fs_strnstrn(OPERATIONAL,              FS_STATIC_STRLEN(OPERATIONAL             ), data, data_sz)) { ret = 70; }
    else if (NULL != fs_strnstrn(WARNING,                  FS_STATIC_STRLEN(WARNING                 ), data, data_sz)) { ret = 71; }
    else if (NULL != fs_strnstrn(OUT_OF_BOUNDS,            FS_STATIC_STRLEN(OUT_OF_BOUNDS           ), data, data_sz)) { ret = 72; }
    else if (NULL != fs_strnstrn(INS_PPP_CONVERGING,       FS_STATIC_STRLEN(INS_PPP_CONVERGING      ), data, data_sz)) { ret = 73; }
    else if (NULL != fs_strnstrn(INS_PPP,                  FS_STATIC_STRLEN(INS_PPP                 ), data, data_sz)) { ret = 74; }
    else if (NULL != fs_strnstrn(PPP_BASIC_CONVERGING,     FS_STATIC_STRLEN(PPP_BASIC_CONVERGING    ), data, data_sz)) { ret = 77; }
    else if (NULL != fs_strnstrn(PPP_BASIC,                FS_STATIC_STRLEN(PPP_BASIC               ), data, data_sz)) { ret = 78; }
    else if (NULL != fs_strnstrn(INS_PPP_BASIC_CONVERGING, FS_STATIC_STRLEN(INS_PPP_BASIC_CONVERGING), data, data_sz)) { ret = 79; }
    else if (NULL != fs_strnstrn(INS_PPP_BASIC,            FS_STATIC_STRLEN(INS_PPP_BASIC           ), data, data_sz)) { ret = 80; }
    else                                                                                                               { ret = 81; }

    return ret;
}


/**
 * @brief Checks if a string fully matches the beginning of another string
 *
 * @param[in] str1     Pointer to the sub string that must to be searched. Its length must be known.
 * @param[in] str1_len Maximum length to search through
 * @param[in] str2     Pointer to the string that must be inspected
 * @param[in] str2_len Maximum length to search through
 *
 * @retVal NULL str1 is not equivalent to str2 beginning
 * @retVal Pointer to the first matched character
 */
static const char* fs_strnstrn(const char* str1, const uint32_t str1_len, const char* str2, const uint32_t str2_len)
{
    if ((NULL == str1) || (NULL == str2) || (0 == str1_len) || (0 == str2_len))
    {
        return NULL;
    }

    bool     last_char_matched = false;
    uint32_t num_matched_chars = 0;
    uint32_t i = 0;
    uint32_t j = 0;

    while ((i < str1_len) && (j < str2_len))
    {
        if (!last_char_matched)
        {
            num_matched_chars = 0;
        }

        if (str1[i] == str2[j])
        {
            i++;
            j++;
            num_matched_chars++;
            last_char_matched = true;
        }
        else
        {
            return NULL;
        }
    }

    if ((num_matched_chars == str2_len) && (0 < num_matched_chars))
    {
        return (str1 + i - j);
    }
    else
    {
        return NULL;
    }
}


/**
 * @brief Finds first occurrence of a character in a string
 *
 * @param[in] start Start of the string
 * @param[in] end   End of the string
 * @param[in] ch    Character to search for
 *
 * @return NULL or valid pointer in range 'start <= pointer < end'
 */
static const char* fs_strnchr(const char* start, const char* end, const char ch)
{
    const char* ret = NULL;

    if ((NULL != start) && (NULL != end))
    {
        for (const char* i = start; i < end; i++)
        {
            if (*i == ch)
            {
                ret = i;
                break;
            }
        }
    }

    return ret;
}
