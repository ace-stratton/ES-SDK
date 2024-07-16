#ifndef SX_BAND_CMD_ITER_TYPES_H
#define SX_BAND_CMD_ITER_TYPES_H

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup es_sxband S/X Band Transmitter
 * @{
 *
 * Declaration of the SXBand general iterator types
 *
 * @file     sxband_cmd_iter_types.h
 * @brief    S/X Band iterator types
 *
 * @}
 * @}
 *
 */

#include "es_cdef.h"

/**
 * @brief Command list header structure definition
 */
typedef struct
{
    char hdr_sig[15];            /**< Command list signature in ASCIIZ format -> "ES_OBC_CMD_LIST" */
    bool store_file_summary;     /**< true - store the result from the execution of every command in a file as a summary, false - do not store command result in a file */
    char summary_fname[31];      /**< Name of the file containing the summary of execution (if store_file_summary is set to true) in ASCIIZ format */
    uint16_t sxband_dev_id;      /**< SXBand Device Identifier to use for the commands in the list (This ID is hardcoded in the SXBand device and does not change) */
    uint16_t hdr_crc;            /**< CRC16-CCITT checksum of the header */
} PACKED cmd_list_hdr_t;

/**
 * @brief Command header definition
 *
 * Each command entry in the command list contains a header, data and footer. The data is the number of bytes
 * specified by the size field.
 */
typedef struct
{
    uint8_t cmd;                  /**< SXBand command ID */
    char type;                    /**< ASCII capital char: 'R' - read command, 'W' - write command */
    uint8_t size;                 /**< Number of command bytes that follow */
} PACKED cmd_list_command_hdr_t;

/**
 * @brief Command footer definition
 */
typedef struct
{
    uint16_t cmd_crc;            /**< CRC16-CCITT checksum of all command bytes starting from cmd field */
} PACKED cmd_list_command_footer_t;

/**
 * @brief A full SXBand command in-memory representation
 */
typedef struct
{
    cmd_list_command_hdr_t hdr;            /**< Command header */
    uint8_t data[255U];                    /**< Current command data as read by the iterator */
    cmd_list_command_footer_t footer;      /**< Command footer */
} PACKED cmd_list_command_t;

/**
 * @brief Structure of a single SXBand command recognized by the scheduler
 */
typedef struct
{
    uint32_t cmd_idx;                        /**< Command index in the file */
    cmd_list_command_hdr_t *p_cmd_hdr;       /**< A pointer to the command header */
    uint8_t * p_data;                        /**< A pointer to the command parameters data */
} sxband_sched_cmd_t;

#endif    /* SX_BAND_CMD_ITER_TYPES_H */
