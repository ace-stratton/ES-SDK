/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __TELEMETRY_TYPES_H__
#define __TELEMETRY_TYPES_H__

/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_types.h
 *
 * @brief Telemetry types header
 *
 * @}
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

#define TLM_FILE_SIGN	"ESTLM"

/** @typedef tlm_file_hdr_t
 *  @brief Telemetry file header definition
 */
typedef struct
{
	uint8_t  signature[sizeof(TLM_FILE_SIGN)];			/**< File signature TLM_FILE_SIGN */
	uint32_t version;				/**< Telemetry format version */
	uint32_t next_write_offset;		/**< file offset where the next write can happen when using files in a cyclic fashion */
	uint32_t last_timestamp;		/**< Unix timestamp of last telemetry message in the file where this header belongs */
	bool file_complete;             /**< indicates whether the file is completely written or there are partial writes in progress */
	uint16_t crc;					/**< header CRC */
} PACKED tlm_file_hdr_t;

/** @typedef tlm_msg_hdr_t
 *  @brief Telemetry message header definition
 */
typedef struct
{
	uint16_t msg_type;				/**< a unique identifier used to interpret the telemetry message data field */
	uint8_t  tlm_data_status;		/**< status of the provided data, e.g. see @ref dc_data_status_t for details on value encoding */
	uint16_t data_len;				/**< length in bytes of the telemetry message data field */
} PACKED tlm_msg_hdr_t;

/** @typedef tlm_msg_footer_t
 *  @brief Telemetry message footer definition
 */
typedef struct
{
	uint16_t  crc;		/**< CRC16 over the entire frame bytes range */
} PACKED tlm_msg_footer_t;

/** @typedef tlm_frame_hdr_t
 *  @brief Telemetry header definition
 */
typedef struct
{
	uint32_t timestamp;		/**< UNIX time stamp */
	uint8_t rolling_cntr;	/**< beacon rolling counter used to detect gaps in transmitted beacons */
	uint8_t obc_opmode;		/**< current OBC operational mode at the moment of beacon sending */
	tlm_msg_hdr_t msg_hdr;	/**< encapsulated message header information */
} PACKED tlm_frame_hdr_t;

/** Defines the least possible size of a telemetry message containing 1 byte payload data + headers and footers */
#define TLM_MSG_SIZE_BYTES_LEAST	((uint32_t) (sizeof(tlm_msg_hdr_t) + 1U + sizeof(tlm_msg_footer_t)))

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef __TELEMETRY_TYPES_H__
