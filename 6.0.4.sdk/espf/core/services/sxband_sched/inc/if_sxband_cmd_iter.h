#ifndef SX_BAND_PL_CTRL_FILE_ITER_H
#define SX_BAND_PL_CTRL_FILE_ITER_H

/**
 * @addtogroup Services
 * @{
 *
 * @addtogroup es_sxband S/X Band Transmitter
 * @{
 *
 * Definition of the SXBand payload controller command iterator interface
 *
 * @file     if_sxband_cmd_iter.h
 * @brief    S/X Band payload controller command iterator interface
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
 * @brief Command iterator status functions
 */
typedef enum
{
	PL_CTRL_ITER_STATUS_OK = 0U,
	PL_CTRL_ITER_STATUS_NOK,
	PL_CTRL_ITER_REACHED_END,
	PL_CTRL_ITER_STATUS_MAX
} pl_ctrl_iter_status_t;

/**
 * @brief Function pointer type to an iterator reset() function
 *
 * @param[in] p_ctx Iteration context provided by the specific iterator implementation
 * @return Reset operation status
 */
typedef pl_ctrl_iter_status_t (*sxband_cmd_iter_reset_t)(void * const p_ctx);

/**
 * @brief Function pointer type to an iterator has_next() function
 *
 * @param[in] p_ctx Iteration context provided by the specific iterator implementation*
 * @return true - if there are more elements to fetch
 * 		   false - iteration is over
 */
typedef bool (*sxband_cmd_iter_has_next_t)(void * const p_ctx);

/**
 * @brief Function pointer type to an iterator next() function
 *
 * @param[in] p_ctx Iteration context provided by the specific iterator implementation
 * @param[out] p_cmd Provides information about the fetched command in a user-supplied buffer
 * @return Operation status
 */
typedef pl_ctrl_iter_status_t (*sxband_cmd_iter_next_t)(void * const p_ctx, sxband_sched_cmd_t * const p_cmd);

/**
 * @brief Iterator interface type which can be implemented by different iterator implementations.
 */
typedef struct
{
	sxband_cmd_iter_reset_t p_reset;
	sxband_cmd_iter_has_next_t p_has_next;
	sxband_cmd_iter_next_t p_next;
} if_sxband_cmd_iter_t;

#ifdef __cplusplus
}
#endif


#endif    /* SX_BAND_PL_CTRL_FILE_ITER_H */
