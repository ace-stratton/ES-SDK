/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GNSS_RESP_H_
#define GNSS_RESP_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_resp.h
 *
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "gnss_types.h"


/**
 * @brief Defines GNSS ASCII response information structure
 */
typedef struct
{
    const char* header_start; /**< header start pointer */
    const char* header_end;   /**< header end pointer */
    uint32_t    header_size;  /**< header size in bytes */
    const char* data_start;   /**< message payload start pointer */
    const char* data_end;     /**< message payload end pointer */
    uint32_t    data_size;    /**< message payload size in bytes */
    const char* star;         /**< location of '*' symbol */
    const char* crc_start;    /**< crc start pointer */
    const char* crc_end;      /**< crc end pointer */
    uint32_t    crc_size;     /**< crc size in bytes */
    uint32_t    total_size;   /**< total response size */
} gnss_ascii_resp_info_t;


/**
 * @brief
 *
 * @param[in] data Raw ASCII response
 * @param[in] data Raw ASCII response size in bytes
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_resp_is_ascii(const char* const data, const uint32_t data_sz);

/**
 * @brief Extracts ASCII response information from raw ASCII response
 *
 * @param[in]  data Raw ASCII response
 * @param[in]  data Raw ASCII response size in bytes
 * @param[out] info Raw ASCII response information
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_resp_get_ascii_info(const char* const data, const uint32_t data_sz, gnss_ascii_resp_info_t* const info);

/**
 * @brief Checks if raw ASCII message CRC is valid
 *
 * @param[in] info ASCII response information
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_resp_is_ascii_crc_valid(const gnss_ascii_resp_info_t* const info);

/**
 * @brief Parses raw ASCII position log to binary data
 *
 * @param[in]  info ASCII response information
 * @param[out] pv   Parsed log
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_resp_parse_ascii_pv(const gnss_ascii_resp_info_t* const info, gnss_xyz_t* const pv);

/**
 * @brief Parses raw ASCII time log to binary data
 *
 * @param[in]  info ASCII response information
 * @param[out] tim  Parsed log
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_resp_parse_ascii_tm(const gnss_ascii_resp_info_t* const info, gnss_time_t* const tim);


#ifdef __cplusplus
}
#endif

#endif /* GNSS_RESP_H_ */
