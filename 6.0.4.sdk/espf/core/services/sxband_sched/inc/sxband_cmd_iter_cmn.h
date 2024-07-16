#ifndef SX_BAND_CMD_ITER_CMN_H
#define SX_BAND_CMD_ITER_CMN_H

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup es_sxband S/X Band Transmitter
 * @{
 *
 * Declaration of common iterator functions
 *
 * @file     sxband_cmd_iter_cmn.h
 * @brief    S/X Band file iterator common functions library
 *
 * @}
 * @}
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "es_cdef.h"
#include "sxband_cmd_iter_types.h"

/**
 * @brief Verifies a command list header
 *
 * @param[in] p_list_hdr pointer to the list header data
 * @return true - header is valid, otherwise - false
 */
bool sxband_cmd_iter_cmn_verify_hdr(const cmd_list_hdr_t * const p_list_hdr);

/**
 * @brief Verifies a command from the command list
 *
 * @param[in] p_cmd_hdr a pointer to the command header
 * @param[in] p_data a pointer to the command data
 * @param[in] cmd_crc CRC of the command as read by the iterator
 *
 * @return true - the command is valid, otherwise - false
 */
bool sxband_cmd_iter_cmn_verify_cmd(const cmd_list_command_hdr_t * const p_cmd_hdr, const uint8_t *p_data, const uint16_t cmd_crc);

#ifdef __cplusplus
}
#endif

#endif    /* SX_BAND_CMD_ITER_CMN_H */
