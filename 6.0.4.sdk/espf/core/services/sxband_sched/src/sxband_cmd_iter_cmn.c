/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup es_sxband
 * @{
 *
 * @file     sxband_cmd_iter_cmn.c
 * @brief    S/X Band Command List Iterator Common Functions
 *
 * Provides command list iteration from a file using the standard if_sxband_pl_ctrl_cmd_iter
 * interface.
 *
 * @}
 *
 */

#include "es_cdef.h"
#include "sxband_cmd_iter_types.h"
#include "assertions.h"
#include "crc16-ccitt.h"

bool sxband_cmd_iter_cmn_verify_hdr(const cmd_list_hdr_t * const p_list_hdr)
{
	CRIT_ASSERT(NULL != p_list_hdr);

	return (p_list_hdr->hdr_crc == crc16_ccitt_table((const uint8_t *) p_list_hdr, sizeof(cmd_list_hdr_t) - sizeof(uint16_t)));
}

bool sxband_cmd_iter_cmn_verify_cmd(const cmd_list_command_hdr_t * const p_cmd_hdr, const uint8_t *p_data, const uint16_t cmd_crc)
{
	CRIT_ASSERT(NULL != p_cmd_hdr);
	CRIT_ASSERT(NULL != p_data);

	uint16_t calc_cmd_crc = crc16_ccitt_table((const uint8_t *) p_cmd_hdr, sizeof(cmd_list_command_hdr_t));
	calc_cmd_crc = crc16_ccitt_table_ex(p_data, p_cmd_hdr->size, calc_cmd_crc);

	return (calc_cmd_crc == cmd_crc);
}
