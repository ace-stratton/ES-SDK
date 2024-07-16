#ifndef SX_BAND_PL_CTRL_H
#define SX_BAND_PL_CTRL_H

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup es_sxband S/X Band Transmitter
 * @{
 *
 * Declaration of the SXBand payload controller interface
 *
 * @file     sxband_pl_ctrl.h
 * @brief    S/X Band payload controller public interface
 *
 * @}
 * @}
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "if_payload_control.h"

/** Control interface for the payload controller */
extern const pl_control_if_t sxband_pl_ctrl_if;

#ifdef __cplusplus
}
#endif

#endif    /* SX_BAND_PL_CTRL_H */
