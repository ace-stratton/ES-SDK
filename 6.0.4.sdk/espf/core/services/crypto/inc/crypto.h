/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __CRYPTO_H__
#define __CRYPTO_H__

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup crypto Cryptography
 * @{
 *
 * The crypto service is responsible for:
 *     - Applying a fixed cryptography algorithm to encode files.
 *     - Notifying users when the file is encrypted and can be used.
 *
 * @note The current implementation of this service is quite basic and it serves mostly as a place-holder for
 *          future work on cryptography support in the OBC.
 *
 * @file crypto.h
 *
 * @brief Basic File Cryptography services
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"
#include "cmox_crypto.h"
#include "SdMngr.h"

/** @brief Size of the associated data field stored in the encryption file */
#define AAD_SIZE_BYTES                    (FF_LFN_BUF)

/** @brief Size of the ASCII cipher algo description stored in the encrypted file */
#define CIPHER_ALGO_SIZE                  (16U)

/** @brief Expected size of the authentication tag to be generated for the encrypted data */
#define AUTH_TAG_SIZE                     (16U)

/** @brief Binary encrypted file signature */
#define ENCRYPTED_DATA_SIGNATURE          "ES|CRYCAP|"

/** @brief A string marker used to indicate the beginning of the authentication tag at the end of the encrypted file */
#define FOOTER_SIGNATURE                  "ES|CRYCAP|FOOTER|"

/** @brief Number of bytes reserved for the encryption Init Vector */
#define IV_SIZE_BYTES                     (12U)

/** @brief Minimum size in bytes of the CMOX library buffer */
#define MIN_CRYPTO_BUF_SIZE               (16U)

/** @brief General error codes which can be returned by the crypto service (not all of these codes are actually used by the streams implementation) */
typedef enum
{
    CRYPTO_API_RES_EOS,                  /**< end-of-stream */
    CRYPTO_API_RES_INVALID_HEADER,       /**< the encrypted file header is invalid */
    CRYPTO_API_RES_INVALID_FOOTER,       /**< the encrypted file footer is invalid */
    CRYPTO_API_RES_INVALID_CIPHER_OFS,   /**< invalid cipher offset specified in header */
    CRYPTO_API_RES_FILE_ERROR,           /**< file system error when trying to work with source file */
    CRYPTO_API_RES_CRYPTOLIB_ERROR,      /**< error in the cryptographic library */
    CRYPTO_API_RES_CRYPTOLIB_KEY_ERROR,  /**< could not set cryptolib key */
    CRYPTO_API_RES_CRYPTOLIB_IV_ERROR,   /**< could not set IV to cryptolib */
    CRYPTO_API_RES_CRYPTOLIB_AAD_ERROR,  /**< could not set AAD to cryptolib */
    CRYPTO_API_RES_PARTIAL_FILE,         /**< source file seems incomplete */
    CRYPTO_API_RES_AUTH_ERROR,           /**< stream authentication error */
    CRYPTO_API_RES_BAD_PARAMS,           /**< invalid/NULL parameters passed to function */
    CRYPTO_API_RES_NO_KEY,               /**< cipher key not programmed into device */
    CRYPTO_API_RES_ABORTED,              /**< the operation was aborted by the user */
    CRYPTO_API_RES_ERROR,                /**< the user operation failed due to error (if any other error code doesn't fit) */
    CRYPTO_API_RES_NO_FILE,              /**< source file for crypto operation does not exist */
    CRYPTO_API_RES_BUSY,                 /**< crypto service is now busy and cannot take another operation */
    CRYPTO_API_RES_OK,                   /**< the current stage operation finished and there is no more data to return */
    CRYPTO_API_RES_MAX                   /**< used for range checking */
} crypto_api_res_t;

/** @brief A general status used by all Crypto service APIs */
typedef enum
{
    CRYPTO_REQ_STATUS_NO_FILE,          /**< Specified source file does not exist */
    CRYPTO_REQ_STATUS_NO_KEY,           /**< AES encryption key is not programmed into the device */
    CRYPTO_REQ_STATUS_QUEUE_FULL,       /**< no space in the request queue, try again later */
    CRYPTO_REQ_STATUS_OK,               /**< the request is accepted for execution and the user will be optionally notified for the status later */
    CRYPTO_REQ_STATUS_MAX               /**< used for validity checking only */
} crypto_req_status_t;

/** @brief Key store update status enumeration */
typedef enum
{
    CRYPTO_KEY_UPD_STATUS_BAD_SIZE,     /**< The key size does not match the expectations for the selected algorithm */
    CRYPTO_KEY_UPD_STATUS_STORE_ERROR,  /**< Key store error */
    CRYPTO_KEY_UPD_STATUS_OK,           /**< Key stored successfully */
    CRYPTO_KEY_UPD_STATUS_MAX           /**< used for validity checking only */
} crypto_key_upd_status_t;

/** @brief Abort types supported by the service */
typedef enum
{
    CRYPTO_ABORT_OP_CURRENT,            /**< Abort the currently running operation and switch to the next one in the queue (if any) */
    CRYPTO_ABORT_OP_ALL,                /**< Abort the currently running operation and clear the operations queue */
    CRYPTO_ABORT_OP_MAX                 /**< used for validity checking only */
} crypto_abort_op_t;

/** @brief Enumerates the supported crypt/decrypt operations by this service */
typedef enum
{
    OP_CMOX_AES_GCM_ENC,
    OP_CMOX_AES_GCM_DEC,
    OP_CMOX_MAX
} cipher_alg_type_t;

/** @brief EnduroSat encrypted data header format */
typedef struct
{
    uint8_t data_sig[sizeof(ENCRYPTED_DATA_SIGNATURE) - 1];         /**< encrypted data block signature - fixed string value (see @ENCRYPTED_DATA_SIGNATURE) */
    uint8_t major_ver;                                              /**< header major version */
    uint8_t minor_ver;                                              /**< header minor version */
    uint8_t cipher_algo[CIPHER_ALGO_SIZE];                          /**< textual description of the cipher algorithm used for the encryption */
    uint8_t iv[IV_SIZE_BYTES];                                      /**< Initialization Vector used for the encryption */
    uint8_t aad[AAD_SIZE_BYTES];                                    /**< Additional Associated Data field used for the authentication tag calculation */
    uint64_t cipher_text_size;                                      /**< size of the encrypted message that follows in bytes */
    uint32_t cipher_text_offset;                                    /**< physical position of the cipher text where decryption shall start; this field is used to provide an extension point for future changes */
} PACKED encrypted_data_hdr_t;

typedef struct
{
    uint8_t footer_sig[sizeof(FOOTER_SIGNATURE) - 1];         /**< encrypted data block signature - fixed string value (see @ENCRYPTED_DATA_SIGNATURE) */
    uint8_t auth_tag[AUTH_TAG_SIZE];                          /**< Calculated Authentication tag for the encrypted data */
} PACKED encrypted_data_footer_t;

/** @brief A handle used to keep the state of an opened crypto data stream */
typedef struct
{
    cmox_cipher_handle_t *cipher_ctx;               /**< general cypher context */
    cmox_gcm_handle_t gcm_hnd;                      /**< GCM encryption algo handle */
    FIL f_src_hnd;                                  /**< source file handle */
    encrypted_data_hdr_t encr_block_hdr;            /**< cipher block header */
    encrypted_data_footer_t data_footer;            /**< cipher footer block containing authentication data */
    uint32_t stage_bytes_read;                      /**< total bytes read from the current section */
    uint32_t cipher_text_bytes_read;                /**< total bytes read from the cipher section (this is a separate counter because the cipher stage may have substages which utilize the stage_bytes_read counter */
    void * p_current_stage_hnd;                     /**< a pointer to the stream pipeline stage handler to execute upon next stream read operation */
    cipher_alg_type_t impl_type;                    /**< cipher algorithm to use for the stream operations */
    char src_file_name[AAD_SIZE_BYTES];             /**< source file name associated to the stream */
    uint8_t tmp_cipher_buf[MIN_CRYPTO_BUF_SIZE];    /**< temporary cipher buffer to use if the user buffer doesn't have enough space for CMOX library processing */
    uint32_t tmp_cipher_buf_prep_size;              /**< number of bytes prepared in the tmp_cipher_buf (e.g. it could happen that only part of the buffer is filled with data) */
} crypto_stream_hnd_t;

/** @brief A type for a user-provided notification when the requested crypto service operation is finished
 *
 *     @param[in] op_status Provides the outcome of the cipher operation
 *     @param[in] p_encrypted_fname Encrypted file name for which the status is provided
 *     @paramp[in] op_time indicates how many milliseconds the operation took to execute
 */
typedef void (*p_crypto_notif)(const crypto_api_res_t op_status, const char *const p_encrypted_fname, const uint32_t op_time);

/** @brief Initialises the service memory and prepares it for operation */
void crypto_init(void);

/** @brief Spawns the service OS-tasks and enables the service API */
void crypto_start(void);

/** @brief The operation queues a user-specified file for encryption using the default (pre-configured)
 *            cipher algorithm.
 *
 *  As the operation may take longer depending on the size of the file, the Crypto service will notify
 *  the user if a user-callback is supplied as part of the p_file_req structure.
 *
 *  @param[in] p_src_file_name name of the file to encrypt
 *  @param[in] p_target_file_name name of the encrypted file to create on the SD card
 *  @param[in] p_user_cbk a pointer to a user callback to be invoked when the encryption is finished
 *
 *  @return status of the requested operation
 */
crypto_req_status_t crypto_std_encrypt_file(const char * const p_src_file_name, const char * const p_target_file_name, const p_crypto_notif p_user_cbk);

/** @brief The operation queues a user-specified file for decryption using the default (pre-configured)
 *         cipher algorithm.
 *
 *  As the operation may take longer depending on the size of the file, the Crypto service will notify
 *  the user if a user-callback is supplied as part of the p_file_req structure.
 *
 *  @param[in] p_src_file_name name of the file to decrypt
 *  @param[in] p_target_file_name name of the decrypted file to create on the SD card
 *  @param[in] p_user_cbk a pointer to a user callback to be invoked when the decryption is finished
 *
 *  @return status of the requested operation
 */
crypto_req_status_t crypto_std_decrypt_file(const char * const p_src_file_name, const char * const p_target_file_name, const p_crypto_notif p_user_cbk);

/** @brief Updates the symmetric encryption key to the currently configured key store
 *  @param[in] p_key a pointer to the key data
 *  @param[in] key_size size of the key in bytes (for the current AES CGM encryption, a 32-byte key is expected)
 *
 *  @return see crypto_key_upd_status_t type values for details
 */
crypto_key_upd_status_t crypto_update_key_store(const uint8_t * const p_key, const uint8_t key_size);

/** @brief Aborts one or more cipher operations
 *
 *  @param[in] op_type type of abort operation to execute
 *
 */
void crypto_abort(const crypto_abort_op_t op_type);

/** @brief Opens a crypto stream from a file
 *
 *  @param[in] p_stream_hnd user stream context structure
 *  @param[in] p_src_file_name name of the file to open for stream operation
 *  @param[in] impl_type type of cipher algorithm to use for the stream read operations
 *
 *  @return stream status (the function will fail with CRYPTO_API_RES_NO_KEY is no key is programmed in the device)
 */
crypto_api_res_t crypto_stream_open(crypto_stream_hnd_t * const p_stream_hnd, const char * const p_src_file_name, const cipher_alg_type_t impl_type);

/** @brief Opens a crypto stream from a file
 *
 *  The function performs streaming encryption/decryption only if a key is programmed in the device. Otherwise it will fail.
 *
 *  @param[in] p_stream_hnd user stream context structure
 *  @param[in] p_src_file_name name of the file to open for stream operation
 *  @param[in] impl_type type of cipher algorithm to use for the stream read operations
 *
 *  @return stream status
 */
crypto_api_res_t crypto_stream_open_always(crypto_stream_hnd_t * const p_stream_hnd, const char * const p_src_file_name, const cipher_alg_type_t impl_type);

/** @brief Reads data from an opened stream using the associated cipher algorithm
 *
 *  The function performs streaming encryption/decryption if a key is programmed in the device but if no key is available, it will just open the file
 *  as a plain stream and will read from it, i.e. it will not fail as @crypto_stream_open will do. The function is useful if you want to support
 *  cipher operations in your implementation but if the device is not provisioned, your code will still return data as a result of the stream read calls but that
 *  data will be in plain form.
 *
 *  @param[in] p_stream_hnd user stream context structure
 *  @param[out] p_output_buf output buffer where streamed data is written to
 *  @param[in] output_buf_size size of the output buffer in bytes
 *  @param[out] p_bytes_read number of actual bytes read from the stream on this call (should usually match the output_buf_size unless the stream ends before the output buffer is filled-in
 *
 *  @return stream status
 */
crypto_api_res_t crypto_stream_read(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * const p_output_buf, const uint32_t output_buf_size, uint32_t * const p_bytes_read);

/** @brief Returns the final size of the associated cipher stream in bytes
 *
 *  @param[in] p_stream_hnd user stream context structure
 *  @param[out] p_stream_size buffer where to store the stream size
 *
 *  @note The stream must have been opened before trying to get the associated size.
 *
 *  @return stream status
 */
crypto_api_res_t crypto_stream_get_size(crypto_stream_hnd_t * const p_stream_hnd, uint32_t * const p_stream_size);

/** @brief Closes an active stream and frees all resources
 *
 *  @param[in] p_stream_hnd user stream context structure
 */
void crypto_stream_close(crypto_stream_hnd_t * const p_stream_hnd);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif    // __CRYPTO_H__
