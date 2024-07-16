/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __CRYPTO_CFG_H__
#define __CRYPTO_CFG_H__

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup crypto Cryptography
 * @{
 *
 * @file crypto_cfg.h
 *
 * @brief Crypto service configuration header
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/** @brief Maximum number of simultaneously supported user requests for file encryption */
#define CRYPTO_FILE_USER_ENTRIES_CNT        (5U)

/** @brief Crypto service task idle period before actively checking for new encryption requests */
#define CRYPTO_SERVICE_IDLE_PERIOD_MS       (500U)

/** @brief Byte size of the data block used for cipher operations */
#define CIPHER_OP_CHUNK_SIZE_BYTES          (512U)

#if DEBUG_ENABLED
#define CRYPTO_TRACE_DBG(format_msg, ...)   ES_TRACE_DEBUG(format_msg, ##__VA_ARGS__)
#else
#define CRYPTO_TRACE_DBG(format_msg, ...)
#endif

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif    // __CRYPTO_CFG_H__
