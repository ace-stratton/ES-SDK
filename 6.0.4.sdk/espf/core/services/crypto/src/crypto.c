/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup crypto
 * @{
 *
 * @file crypto.c
 *
 * @brief Basic cryptography services for files relying on the STM32 Cryptographic library
 *
 * The crypto service stores encrypted data and the corresponding encryption parameters in its own format
 * due to the lack of stable and popular standards.
 *
 * @}
 */

#include <stddef.h>
#include <string.h>
#include <math.h>
#include "crypto.h"
#include "es_cdef.h"
#include "cmsis_os2.h"
#include "es_exeh.h"
#include "TaskMonitor.h"
#include "trace.h"
#include "SdMngr.h"
#include "es_exeh.h"
#include "crypto_cfg.h"
#include "csq_algo.h"
#include "cmox_crypto.h"
#include "module_id.h"
#include "rng.h"
#include "timer.h"
#include "nvm.h"
#include "assertions.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_CRYPTO

/** @brief Flag value used with osThreadFlagsWait() to unblock main task in case a processing event */
#define UNBLOCK_CRYPTO_TASK               (0x10)

/** @brief Number of bytes reserved for the RNG entropy seed */
#define ENTROPY_SIZE_BYTES                (32U)

/** @brief Number of bytes to use for the nonce value generated initially for seeding DRBG library */
#define NONCE_SIZE_BYTES                  (16U)

/** @brief Name of the cipher algo used by this crypto service which will be provided as part of the encrypted_data_hdr_t block in the encrypted file */
#define CIPHER_ALGO_NAME                  "AES_256_GCM"

/** @brief Major version of the encrypted_data_hdr_t block (increment when you make breaking changes to the header block) */
#define DATA_HDR_MAJOR                    (0U)

/** @brief Minor version of the encrypted_data_hdr_t block (increment when you make non-breaking changes to the header block) */
#define DATA_HDR_MINOR                    (1U)

/** @brief Configuration map cipher entry */
typedef struct
{
    cipher_alg_type_t cipher_type;                  /**< internal cipher alg type */
    const cmox_gcm_impl_t * const cmox_gcm_impl;    /**< corresponding CMOX library type */
} cipher_entry_t;

/** @brief The structure defines the parameters of a request to perform on a user-specified file */
typedef struct
{
    char src_file_name[FF_LFN_BUF];            /**< name of the source file to process */
    char target_file_name[FF_LFN_BUF];         /**< name of the service-produced file */
    p_crypto_notif p_user_notif;               /**< optional user notification callback */
    cipher_alg_type_t cipher_type;             /**< type of cipher algorithm to use */
} crypto_file_req_t;

/** @brief A function pointer to a stream pipeline handler
 *
 *  This is a generic interface which provides a specific handling at each stage of the stream operations pipeline.
 *
 *  @param[in] p_stream_hnd stream handler context structure (keeps the state of the stream)
 *  @param[in] p_read_buf a temporary read buffer provided for intermediate data storage (not all handlers will use that and it is a responsibility of the general handler to ensure the size of this buffer can accommodate bytes_to_read bytes
 *  @param[out] p_output_buf this is the buffer where processed data shall be copied
 *  @param[in] bytes_to_read number of bytes to read when the stage is executed
 *  @param[in] p_bytes_read the buffer receives the actual number of bytes processed by the function and returned in p_output_buf
 *
 *  @return stream status after the stage completes
 */
typedef crypto_api_res_t (*p_stream_stage_pipeline_t)(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);

/** @brief Crypto service runtime context structure */
typedef struct
{
    osThreadId_t os_task_hnd;                                        /**< OS task handle */
    crypto_file_req_t user_queue[CRYPTO_FILE_USER_ENTRIES_CNT];      /**< the array represents the user requests queue */
    crypto_file_req_t tmp_data;                                      /**< a temporary buffer to keep the @ref user_queue entry which was last popped out from the queue */
    cmox_init_retval_t cmox_init_retval;                             /**< return value of the cmox_initialize call */
    cmox_drbg_retval_t drbg_retval;                                  /**< return value for the last DRBG library call */
    cmox_ctr_drbg_handle_t drbg_ctr_hnd;                             /**< DRBG constructor handle */
    cmox_drbg_handle_t *drbg_hnd;                                    /**< DRBG library handle */
    uint8_t entropy[ENTROPY_SIZE_BYTES];                             /**< Entropy data to use for pseudo-random algo reseed (will be filled by TRNG sampling) */
    bool is_key_empty;                                               /**< true: programmed key is empty (i.e. all zeroes); false: key can be used by the crypto service */
    crypto_abort_op_t abort_op;                                      /**< type of abort operation requested */
} crypto_runtime_context_t;

STATIC inline bool is_key_valid(const uint8_t * const p_key, const uint8_t key_size);
STATIC void crypto_task(void * p_task_arg);
STATIC void safe_copy_str(char * const p_dst_str, const char * const p_src_str, const size_t dst_size);
STATIC crypto_req_status_t queue_cipher_op(const char * const p_src_file_name, const char * const p_target_file_name, const p_crypto_notif p_user_cbk, cipher_alg_type_t alg_type);
STATIC void csq_get_slot_data(const uint32_t slot_idx, void* const p_data_buf);
STATIC crypto_api_res_t crypt_decrypt_file(const char * const p_src_file_name, const char * const p_target_file_name, const cipher_alg_type_t impl_type);
STATIC void generate_iv(uint8_t * const p_iv, const uint32_t iv_size);
STATIC crypto_api_res_t prep_file_for_stream_encr(crypto_stream_hnd_t * const p_stream_hnd);
STATIC crypto_api_res_t prep_file_for_stream_decr(crypto_stream_hnd_t * const p_stream_hnd);
STATIC crypto_api_res_t read_from_buf(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * const p_buf, const uint32_t buf_size, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t read_from_header(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t read_from_temp_buf(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t read_from_footer(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t prepare_footer(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t verify_footer(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t read_chunk_and_process(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t prepare_temp_buf(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC crypto_api_res_t read_from_file(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read);
STATIC inline void set_next_stage(crypto_stream_hnd_t * const p_stream_hnd, p_stream_stage_pipeline_t const p_next_stage);


/** @brief Component runtime context structure */
static crypto_runtime_context_t crtc =
{
    .os_task_hnd = NULL,
    .is_key_empty = true,
    .abort_op = CRYPTO_ABORT_OP_MAX,
    .drbg_hnd = NULL
};

/** @brief Circular static queue handling instance
 *  @note The set function pointer is set to NULL because in our case it is more optimal to
 *  use the csq_algo_reserve() API and populate the entry directly in-place to avoid intermediate
 *  copying of strings.
 */
static CSQ_ALGO_INSTANCE(crypto_file_queue,
                         CRYPTO_FILE_USER_ENTRIES_CNT,
                         CSQ_ALGO_POLICY_NO_OVERWRITE,
                         NULL,
                         &csq_get_slot_data,
                         NULL);

/** @brief Mutex to use for synchronizing access to the component structures */
osMutexDef(crypto_lock);

/** @brief Cipher algo map */
const cipher_entry_t cipher_alg_map[OP_CMOX_MAX] =
{
    { OP_CMOX_AES_GCM_ENC, &CMOX_AES_GCM_ENC },
    { OP_CMOX_AES_GCM_DEC, &CMOX_AES_GCM_DEC },
};

/** @brief Crypto mutex attributes (used to avoid race conditions between the main task and the external Crypto
 *         service API
 */
static const osMutexAttr_t crypto_lock_attr =
{
    "crypto_mutex",       // human readable mutex name
    osMutexRecursive,     // attr_bits
    NULL,                 // memory for control block
    0U                    // size for control block
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t crypto_lock_id;

/** @brief Hard-coded init vector to use for encryption if DRBG generation fails */
static const uint8_t hard_iv[] =
{
    0x61, 0x1c, 0xe6, 0xf9, 0xa6, 0x88, 0x07, 0x50, 0xde, 0x7d, 0xa6, 0xcb
};

void crypto_init(void)
{
    MODID_VersionInfo_t ver_info;   /**< OBC module version info used to seed DRBG library with additional data */

    crtc.os_task_hnd = NULL;
    crtc.drbg_hnd = NULL;

    for (uint16_t user_entry = 0; user_entry < CDEF_ELEMENT_COUNT(crtc.user_queue); user_entry++)
    {
        (void) memset(crtc.user_queue[user_entry].src_file_name, 0, sizeof(crtc.user_queue[user_entry].src_file_name));
        (void) memset(crtc.user_queue[user_entry].target_file_name, 0, sizeof(crtc.user_queue[user_entry].target_file_name));
        crtc.user_queue[user_entry].p_user_notif = NULL;
    }

    csq_algo_clear(&crypto_file_queue);

    crtc.cmox_init_retval = cmox_initialize(NULL);

    // no need to check this but still keep it during debugging (if it is invalid, one of the other CMOX lib API calls will fail
    (void) crtc.cmox_init_retval;

    module_id_get_info(&ver_info);

    crtc.drbg_hnd = cmox_ctr_drbg_construct(&crtc.drbg_ctr_hnd, CMOX_CTR_DRBG_AES256);

    CRIT_ASSERT(NULL != crtc.drbg_hnd);

    uint8_t nonce[NONCE_SIZE_BYTES];

    // initialise entropy and nonce buffers with TRNG values
    rng_fill(crtc.entropy, sizeof(crtc.entropy));
    rng_fill(nonce, sizeof(nonce));

    // initialise the pseudo-random generator
    crtc.drbg_retval = cmox_drbg_init(crtc.drbg_hnd,
                                      crtc.entropy,
                                      sizeof(crtc.entropy),
                                      (const uint8_t *) &ver_info,
                                      sizeof(ver_info),
                                      nonce,
                                      sizeof(nonce));

    crypto_cfg_t crypto_cfg;

    Nvm_GetBlockById(NVM_BLOCK_CRYPTO_CFG, &crypto_cfg);

    crtc.is_key_empty = !is_key_valid(crypto_cfg.aes_key, sizeof(crypto_cfg.aes_key));

    // clear out key-related data from stack
    (void) memset(&crypto_cfg, 0, sizeof(crypto_cfg));
}

void crypto_start(void)
{
    STATIC const osThreadAttr_t task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "Crypto_Service_Task",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 10000        // TODO: Measure worst-case stack usage!
    };

    if (NULL == crypto_lock_id)
    {
        crypto_lock_id = osMutexNew(&crypto_lock_attr);
    }

    // create thread only if not already existing...
    if (NULL == crtc.os_task_hnd)
    {
        crtc.os_task_hnd = osThreadNew(&crypto_task,
                                       NULL,
                                       &task_attr);

        if (NULL == crtc.os_task_hnd)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal,
                        (int32_t) EXEH_CRYPTO_CANT_SPAWN_TASK);
        }
        else
        {
            TaskMonitor_TaskInitialized(TASK_CRYPTO_SRV);
        }
    }
}

crypto_req_status_t crypto_std_encrypt_file(const char * const p_src_file_name, const char * const p_target_file_name, const p_crypto_notif p_user_cbk)
{
    return queue_cipher_op(p_src_file_name, p_target_file_name, p_user_cbk, OP_CMOX_AES_GCM_ENC);
}

crypto_req_status_t crypto_std_decrypt_file(const char * const p_src_file_name, const char * const p_target_file_name, const p_crypto_notif p_user_cbk)
{
    return queue_cipher_op(p_src_file_name, p_target_file_name, p_user_cbk, OP_CMOX_AES_GCM_DEC);
}

crypto_key_upd_status_t crypto_update_key_store(const uint8_t * const p_key, const uint8_t key_size)
{
    crypto_key_upd_status_t res = CRYPTO_KEY_UPD_STATUS_BAD_SIZE;

    if (AES_KEY_SIZE_BYTES == key_size)
    {
        crypto_cfg_t crypto_cfg;

        (void) memcpy(crypto_cfg.aes_key, p_key, sizeof(crypto_cfg.aes_key));

        Nvm_SetBlockById(NVM_BLOCK_CRYPTO_CFG, &crypto_cfg, NVMSETBLOCK_STORE_IMMEDIATELY);

        crtc.is_key_empty = !is_key_valid(crypto_cfg.aes_key, sizeof(crypto_cfg.aes_key));

        // zero-out any remnants of the key in stack
        (void) memset(&crypto_cfg, 0, sizeof(crypto_cfg));

        res = CRYPTO_KEY_UPD_STATUS_OK;
    }

    return res;
}

void crypto_abort(const crypto_abort_op_t op_type)
{
    CRIT_ASSERT(op_type < CRYPTO_ABORT_OP_MAX);

    if (op_type < CRYPTO_ABORT_OP_MAX)
    {
        crtc.abort_op = op_type;

        // signal main task to execute
        osThreadFlagsSet(crtc.os_task_hnd, UNBLOCK_CRYPTO_TASK);
    }
}

crypto_api_res_t crypto_stream_open_always(crypto_stream_hnd_t * const p_stream_hnd, const char * const p_src_file_name, const cipher_alg_type_t impl_type)
{
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_src_file_name);
    CRIT_ASSERT(impl_type < OP_CMOX_MAX);

    if (crtc.is_key_empty)
    {
        // if no key is configured, this function will just open the file and return unprocessed content directly
        if ((NULL != p_stream_hnd) && (NULL != p_src_file_name) && (impl_type < OP_CMOX_MAX))
        {
            p_stream_hnd->impl_type = impl_type;
            p_stream_hnd->stage_bytes_read = 0U;
            p_stream_hnd->cipher_text_bytes_read = 0U;
            p_stream_hnd->cipher_ctx = NULL;

            set_next_stage(p_stream_hnd, NULL);

            safe_copy_str(p_stream_hnd->src_file_name, p_src_file_name, sizeof(p_stream_hnd->src_file_name));

            FRESULT f_src_res = SdMngr_f_open(&p_stream_hnd->f_src_hnd, p_src_file_name, FA_OPEN_EXISTING | FA_READ);

            if (FR_OK != f_src_res)
            {
                CRYPTO_TRACE_DBG("[crypto_stream_open_always] file system error: %d\n", f_src_res);
                return CRYPTO_API_RES_FILE_ERROR;
            }

            // update data size for the read stage...
            p_stream_hnd->encr_block_hdr.cipher_text_size = SdMngr_f_size(&p_stream_hnd->f_src_hnd);

            set_next_stage(p_stream_hnd, &read_from_file);

            return CRYPTO_API_RES_OK;
        }
    }
    else
    {
        return crypto_stream_open(p_stream_hnd, p_src_file_name, impl_type);
    }

    return CRYPTO_API_RES_ERROR;
}

crypto_api_res_t crypto_stream_open(crypto_stream_hnd_t * const p_stream_hnd, const char * const p_src_file_name, const cipher_alg_type_t impl_type)
{
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_src_file_name);
    CRIT_ASSERT(impl_type < OP_CMOX_MAX);

    crypto_api_res_t init_res = CRYPTO_API_RES_ERROR;

    if (crtc.is_key_empty)
    {
        return CRYPTO_API_RES_NO_KEY;
    }

    if ((NULL != p_stream_hnd) && (NULL != p_src_file_name) && (impl_type < OP_CMOX_MAX))
    {
        p_stream_hnd->impl_type = impl_type;
        p_stream_hnd->stage_bytes_read = 0U;
        p_stream_hnd->cipher_text_bytes_read = 0U;
        p_stream_hnd->cipher_ctx = NULL;

        set_next_stage(p_stream_hnd, NULL);

        safe_copy_str(p_stream_hnd->src_file_name, p_src_file_name, sizeof(p_stream_hnd->src_file_name));

        FRESULT f_src_res = SdMngr_f_open(&p_stream_hnd->f_src_hnd, p_src_file_name, FA_OPEN_EXISTING | FA_READ);

        if (FR_OK != f_src_res)
        {
            CRYPTO_TRACE_DBG("[crypto_stream_open] file system error: %d\n", f_src_res);
            return CRYPTO_API_RES_FILE_ERROR;
        }

        if (OP_CMOX_AES_GCM_ENC == impl_type)
        {
            init_res = prep_file_for_stream_encr(p_stream_hnd);
        } else if (OP_CMOX_AES_GCM_DEC == impl_type)
        {
            init_res = prep_file_for_stream_decr(p_stream_hnd);
        }
        else
        {
            CRIT_ASSERT(false);
        }

        if (CRYPTO_API_RES_OK == init_res)
        {
            p_stream_hnd->cipher_ctx = cmox_gcm_construct(&p_stream_hnd->gcm_hnd, *(cipher_alg_map[(uint8_t) impl_type].cmox_gcm_impl));

            // prepare CMOX library context
            cmox_cipher_retval_t cipher_retval = cmox_cipher_init(p_stream_hnd->cipher_ctx);

            if (cipher_retval != CMOX_CIPHER_SUCCESS)
            {
                CRYPTO_TRACE_DBG("cmox_cipher_init() failed with code %d\n", cipher_retval);

                return CRYPTO_API_RES_CRYPTOLIB_ERROR;
            }

            cipher_retval = cmox_cipher_setTagLen(p_stream_hnd->cipher_ctx, AUTH_TAG_SIZE);

            if (cipher_retval != CMOX_CIPHER_SUCCESS)
            {
                CRYPTO_TRACE_DBG("cmox_cipher_setTagLen() failed with code %d\n", cipher_retval);

                return CRYPTO_API_RES_CRYPTOLIB_ERROR;
            }

            crypto_cfg_t crypto_cfg_blk;

            Nvm_GetBlockById(NVM_BLOCK_CRYPTO_CFG, &crypto_cfg_blk);

            cipher_retval = cmox_cipher_setKey(p_stream_hnd->cipher_ctx, crypto_cfg_blk.aes_key, sizeof(crypto_cfg_blk.aes_key));

            if (cipher_retval != CMOX_CIPHER_SUCCESS)
            {
                CRYPTO_TRACE_DBG("cmox_cipher_setKey() failed with code %d\n", cipher_retval);

                return CRYPTO_API_RES_CRYPTOLIB_KEY_ERROR;
            }

            // clear out key-related data from the stack after writing the keys to the STM32 key register
            (void) memset(&crypto_cfg_blk, 0, sizeof(crypto_cfg_blk));

            cipher_retval = cmox_cipher_setIV(p_stream_hnd->cipher_ctx, p_stream_hnd->encr_block_hdr.iv, sizeof(p_stream_hnd->encr_block_hdr.iv));

            if (cipher_retval != CMOX_CIPHER_SUCCESS)
            {
                CRYPTO_TRACE_DBG("cmox_cipher_setIV() failed with code %d\n", cipher_retval);

                return CRYPTO_API_RES_CRYPTOLIB_IV_ERROR;
            }

            cipher_retval = cmox_cipher_appendAD(p_stream_hnd->cipher_ctx, (const uint8_t *) p_stream_hnd->encr_block_hdr.aad, sizeof(p_stream_hnd->encr_block_hdr.aad));

            if (cipher_retval != CMOX_CIPHER_SUCCESS)
            {
                CRYPTO_TRACE_DBG("cmox_cipher_appendAD() failed with code %d\n", cipher_retval);

                return CRYPTO_API_RES_CRYPTOLIB_AAD_ERROR;
            }
        }
    }

    return init_res;
}

crypto_api_res_t crypto_stream_read(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * const p_output_buf, const uint32_t output_buf_size, uint32_t * const p_bytes_read)
{
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_output_buf);
    CRIT_ASSERT(NULL != p_bytes_read);
    CRIT_ASSERT(output_buf_size > 0);

    crypto_api_res_t op_res = CRYPTO_API_RES_FILE_ERROR;
    uint32_t remaining_bytes = output_buf_size;
    uint32_t bytes_read = 0U;
    uint32_t actual_bytes_to_read = 0U;
    uint8_t tmp_read_buf[CIPHER_OP_CHUNK_SIZE_BYTES];
    p_stream_stage_pipeline_t p_read_func = NULL;

    while (remaining_bytes > 0)
    {
        actual_bytes_to_read = (uint32_t) fmin(sizeof(tmp_read_buf), remaining_bytes);

//this is done to ignore the warning "ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]"
        static_assert(sizeof(p_stream_hnd->p_current_stage_hnd) == sizeof(p_read_func));
PRAGMA_DIAG_PUSH()
PRAGMA_DIAG_IGNORED(-Wpedantic)
        p_read_func = (p_stream_stage_pipeline_t) p_stream_hnd->p_current_stage_hnd;
PRAGMA_DIAG_POP()

        if (NULL != p_read_func)
        {
            op_res = (*p_read_func)(p_stream_hnd, tmp_read_buf, &p_output_buf[output_buf_size - remaining_bytes], actual_bytes_to_read, &bytes_read);

            if (CRYPTO_API_RES_OK == op_res)
            {
                remaining_bytes -= bytes_read;
                *p_bytes_read += bytes_read;
            }
            else
            {
                *p_bytes_read = 0;

                return op_res;
            }
        }
        else
        {
            // all sections covered, streaming ends here
            return CRYPTO_API_RES_EOS;
        }
    }

    // we end up here if the stream is not over and we filled-in the complete user-provided buffer with
    // data

    return CRYPTO_API_RES_OK;
}

crypto_api_res_t crypto_stream_get_size(crypto_stream_hnd_t * const p_stream_hnd, uint32_t * const p_stream_size)
{
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_stream_size);

    crypto_api_res_t res = CRYPTO_API_RES_BAD_PARAMS;

    *p_stream_size = 0U;

    if ((NULL != p_stream_hnd) && (NULL != p_stream_size))
    {
        *p_stream_size = sizeof(p_stream_hnd->encr_block_hdr) + p_stream_hnd->encr_block_hdr.cipher_text_size + sizeof(p_stream_hnd->data_footer);

        res = CRYPTO_API_RES_OK;
    }

    return res;
}

void crypto_stream_close(crypto_stream_hnd_t * const p_stream_hnd)
{
    CRIT_ASSERT(NULL != p_stream_hnd);

    (void) SdMngr_f_close(&p_stream_hnd->f_src_hnd);

    if (NULL != p_stream_hnd->cipher_ctx)
    {
        (void) cmox_cipher_cleanup(p_stream_hnd->cipher_ctx);
    }
}

/** @brief Checks if the provided key is valid (i.e. being non-zero)
 *
 *  @param[in] p_key a pointer to the encryption key bytes
 *  @param[in] key_size size of the key in bytes
 *
 *  @return true: the key has at least one non-zero byte; false: the key is all zeroes
 */
STATIC bool is_key_valid(const uint8_t * const p_key, const uint8_t key_size)
{
    bool res = false;

    CRIT_ASSERT(NULL != p_key);
    CRIT_ASSERT(key_size > 0);

    for (uint8_t idx = 0; idx < key_size; idx++)
    {
        if (0 != p_key[idx])
        {
            res = true;
            break;
        }
    }

    return res;
}

/** @brief The function makes a copy of a null-terminated string to a buffer ensuring the buffer is null terminated
 *         even if the copy was partial.
 *
 *  @param[in] p_dst_str a pointer to the beginning of the buffer to copy p_str_str to
 *  @param[in] p_src_str a pointer to a null-terminated string to copy
 *  @param[in] dst_size size of the buffer pointed to by p_dst_str
 *
 */
STATIC void safe_copy_str(char * const p_dst_str, const char * const p_src_str, const size_t dst_size)
{
    CRIT_ASSERT(NULL != p_src_str);
    CRIT_ASSERT(NULL != p_dst_str);
    CRIT_ASSERT(dst_size > 0);

    size_t min_sz = (size_t) fmin(strlen(p_src_str), dst_size - 1);

    (void) strncpy(p_dst_str, p_src_str, min_sz);

    p_dst_str[min_sz] = '\0';
}

/** @brief Queues a cipher operation on a file for execution
 *  @param[in] p_src_file_name name of the file to encrypt
 *  @param[in] p_target_file_name name of the encrypted file to create on the SD card
 *  @param[in] p_user_cbk a pointer to a user callback to be invoked when the encryption is finished
 *
 *  @return queue operation status
 */
STATIC crypto_req_status_t queue_cipher_op(const char * const p_src_file_name, const char * const p_target_file_name, const p_crypto_notif p_user_cbk, cipher_alg_type_t alg_type)
{
    CRIT_ASSERT(NULL != p_src_file_name);
    CRIT_ASSERT(NULL != p_target_file_name);
    CRIT_ASSERT(alg_type < OP_CMOX_MAX);

    crypto_req_status_t res = CRYPTO_REQ_STATUS_QUEUE_FULL;

    FILINFO fno;
    FRESULT fres = SdMngr_f_stat(p_src_file_name, &fno);
    if ((NULL == p_src_file_name) || (FR_NO_FILE == fres) || (FR_NO_PATH == fres))
    {
    	res = CRYPTO_REQ_STATUS_NO_FILE;
    }
    else if (crtc.is_key_empty)
    {
        res = CRYPTO_REQ_STATUS_NO_KEY;
    }
    else
    {
        if ((NULL != p_src_file_name) && (NULL != p_target_file_name))
        {
            osMutexAcquire(crypto_lock_id, osWaitForever);

            uint32_t reserved_slot_idx = 0U;
            bool is_slot_reserved = csq_algo_reserve(&crypto_file_queue, &reserved_slot_idx);

            // if source file name is not assigned, then the slot is assumed to be free
            if (is_slot_reserved)
            {
                safe_copy_str(crtc.user_queue[reserved_slot_idx].src_file_name,
                              p_src_file_name,
                              sizeof(crtc.user_queue[reserved_slot_idx].src_file_name));

                safe_copy_str(crtc.user_queue[reserved_slot_idx].target_file_name,
                              p_target_file_name,
                              sizeof(crtc.user_queue[reserved_slot_idx].target_file_name));

                crtc.user_queue[reserved_slot_idx].p_user_notif = p_user_cbk;
                crtc.user_queue[reserved_slot_idx].cipher_type = alg_type;

                CRYPTO_TRACE_DBG("new file queued for processing (alg: %d): %s\n", (uint8_t) alg_type, p_src_file_name);

                res = CRYPTO_REQ_STATUS_OK;
            }
            else
            {
                CRYPTO_TRACE_DBG("could not enqueue file for processing (alg: %d): %s\n", (uint8_t) alg_type, p_src_file_name);
            }

            osMutexRelease(crypto_lock_id);

            if (CRYPTO_REQ_STATUS_OK == res)
            {
                // signal main task to start encryption on existing queue entries
                osThreadFlagsSet(crtc.os_task_hnd, UNBLOCK_CRYPTO_TASK);
            }
        }
    }

    return res;
}

/** @brief Main Crypto service OS task function
 *  @param[in] p_task_arg specific task parameters (unused)
 */
STATIC void crypto_task(void * p_task_arg)
{
    // currently unused
    (void) p_task_arg;

    for (;;)
    {
        bool is_queue_data_valid = false;
        uint32_t wait_ret = osThreadFlagsWait(UNBLOCK_CRYPTO_TASK, osFlagsWaitAny, CRYPTO_SERVICE_IDLE_PERIOD_MS);

        if (UNBLOCK_CRYPTO_TASK == wait_ret)
        {
            CRYPTO_TRACE_DBG("crypto service queue processing triggered!\n");

            // notify pending users for the abort operation
            if (CRYPTO_ABORT_OP_ALL == crtc.abort_op)
            {
                osMutexAcquire(crypto_lock_id, osWaitForever);

                do
                {
                    is_queue_data_valid = csq_algo_pop(&crypto_file_queue, &crtc.tmp_data);

                    if (is_queue_data_valid && (NULL != crtc.tmp_data.p_user_notif))
                    {
                        CRYPTO_TRACE_DBG("user abort notification sent!\n");
                        (*(crtc.tmp_data.p_user_notif))(CRYPTO_API_RES_ABORTED, crtc.tmp_data.target_file_name, 0U);
                    }
                }
                while (is_queue_data_valid);

                csq_algo_clear(&crypto_file_queue);

                // invalidate abort status
                crtc.abort_op = CRYPTO_ABORT_OP_MAX;

                osMutexRelease(crypto_lock_id);
            }
            else
            {
                osMutexAcquire(crypto_lock_id, osWaitForever);

                is_queue_data_valid = csq_algo_pop(&crypto_file_queue, &crtc.tmp_data);

                osMutexRelease(crypto_lock_id);

                if (is_queue_data_valid)
                {
                    timer_handle_t profile_timer;

                    timer_start(&profile_timer);

                    crypto_api_res_t cipher_op_res = crypt_decrypt_file(crtc.tmp_data.src_file_name, crtc.tmp_data.target_file_name, crtc.tmp_data.cipher_type);

                    (void) cipher_op_res;

                    uint32_t elapsed_time_ms = timer_get_elapsed_time(&profile_timer);
                    CRYPTO_TRACE_DBG("operation took %d milliseconds\n", elapsed_time_ms);

                    if (NULL != crtc.tmp_data.p_user_notif)
                    {
                        CRYPTO_TRACE_DBG("user notification sent with result %d!\n", (uint16_t) cipher_op_res);
                        (*(crtc.tmp_data.p_user_notif))(cipher_op_res, crtc.tmp_data.target_file_name, elapsed_time_ms);
                    }
                }
            }
        }

        TaskMonitor_IamAlive(TASK_CRYPTO_SRV);
        vApplicationLowStackCheck(TASK_CRYPTO_SRV);
    }
}

/** @brief User set function for CSQ_ALGO library
 *  @param[in] slot_idx queue index to retrieve data from
 *  @param[out] p_data_buf a buffer to receive a copy of the data at the given slot index
 *
 *  @return pointer to the data at the specified index
 */
STATIC void csq_get_slot_data(const uint32_t slot_idx, void* const p_data_buf)
{
    (void) memcpy(p_data_buf, &crtc.user_queue[slot_idx], sizeof(crypto_file_req_t));
}

/** @brief Performs a one-time generation of a random init vector for encryption.
 *
 *  @param[in] p_iv a pointer to the buffer for the IV
 *  @param[in] iv_size size of the IV buffer
 *
 *  @note If the DRBG algo fails, then a hard-coded IV is used.
 */
STATIC void generate_iv(uint8_t * const p_iv, const uint32_t iv_size)
{
    CRIT_ASSERT(NULL != p_iv);
    CRIT_ASSERT(iv_size > 0);

    crtc.drbg_retval = cmox_drbg_generate(crtc.drbg_hnd,
                                          NULL,
                                          0,
                                          (uint8_t *) p_iv,
                                          iv_size);

    if (CMOX_DRBG_SUCCESS != crtc.drbg_retval)
    {
        CRYPTO_TRACE_DBG("cmox_drbg_generate() error '%d'. Opting for hardcoded IV...\n", crtc.drbg_retval);

        (void) memcpy(p_iv, hard_iv, (size_t) fmin(iv_size, sizeof(hard_iv)));
    }

    crtc.drbg_retval = cmox_drbg_reseed(crtc.drbg_hnd,
                                        crtc.entropy,
                                        sizeof(crtc.entropy),
                                        NULL,
                                        0);

    if (CMOX_DRBG_SUCCESS != crtc.drbg_retval)
    {
        CRYPTO_TRACE_DBG("cmox_drbg_reseed() error '%d'\n", crtc.drbg_retval);
    }
}

/** @brief Performs a specified cipher algorithm on a file producing a new file with a given name
 *
 *  @note The function does not modify the original file.
 *
 *  @param[in] p_src_file_name original file name
 *  @param[in] p_target_file_name processed file name
 *  @param[in] impl_type specifies the type of algorithm to perform on the input file
 *  @return see @ref crypto_op_status_t values for details
 */
STATIC crypto_api_res_t crypt_decrypt_file(const char * const p_src_file_name, const char * const p_target_file_name, const cipher_alg_type_t impl_type)
{
    crypto_api_res_t op_res = CRYPTO_API_RES_FILE_ERROR;
    crypto_stream_hnd_t crypto_stream_hnd;
    uint8_t tmp_cipher_buf[CIPHER_OP_CHUNK_SIZE_BYTES];
    FIL target_file_hnd;

    if ((NULL != p_src_file_name) && (NULL != p_target_file_name) && (impl_type < OP_CMOX_MAX))
    {
        crypto_api_res_t stream_res = crypto_stream_open(&crypto_stream_hnd, p_src_file_name, impl_type);
        FRESULT f_target_res = SdMngr_f_open(&target_file_hnd, p_target_file_name, FA_CREATE_ALWAYS | FA_WRITE);

        if (CRYPTO_API_RES_OK != stream_res)
        {
            op_res = stream_res;
            goto stream_cleanup;
        }

        if (FR_OK == f_target_res)
        {
            while (CRYPTO_API_RES_OK == stream_res)
            {
                uint32_t bytes_read = 0U;
                uint32_t bytes_written = 0U;

                // make sure we are not reset by the WD if bigger streams get processed
                TaskMonitor_IamAlive(TASK_CRYPTO_SRV);

                stream_res = crypto_stream_read(&crypto_stream_hnd, tmp_cipher_buf, sizeof(tmp_cipher_buf), &bytes_read);

                if ((CRYPTO_API_RES_OK == stream_res) || (CRYPTO_API_RES_EOS == stream_res))
                {
                    // write the encrypted data to storage
                    f_target_res = SdMngr_f_write(&target_file_hnd, tmp_cipher_buf, bytes_read, (UINT *) &bytes_written);

                    if ((FR_OK != f_target_res) || (bytes_written != bytes_read))
                    {
                        CRYPTO_TRACE_DBG("file write failed with code %d\n", f_target_res);

                        op_res = CRYPTO_API_RES_FILE_ERROR;

                        break;
                    }

                    if (CRYPTO_API_RES_EOS == stream_res)
                    {
                        CRYPTO_TRACE_DBG("streaming completed!\n", stream_res);

                        op_res = stream_res;

                        break;
                    }
                }
                else
                {
                    CRYPTO_TRACE_DBG("stream error %d\n", stream_res);

                    op_res = stream_res;

                    break;
                }
            }
        }
    }

stream_cleanup: (void) SdMngr_f_close(&target_file_hnd);
    crypto_stream_close(&crypto_stream_hnd);

    return op_res;
}

/** @brief Refer to @ref p_stream_stage_pipeline_t function pointer type for a description of all parameters here */
STATIC crypto_api_res_t prep_file_for_stream_encr(crypto_stream_hnd_t * const p_stream_hnd)
{
    CRIT_ASSERT(NULL != p_stream_hnd);

    crypto_api_res_t res = CRYPTO_API_RES_BAD_PARAMS;

    if (NULL != p_stream_hnd)
    {
        // prepare the encrypted_data_hdr_t block at the beginning of the file
        (void) memcpy(p_stream_hnd->encr_block_hdr.data_sig, ENCRYPTED_DATA_SIGNATURE, sizeof(ENCRYPTED_DATA_SIGNATURE) - 1);

        p_stream_hnd->encr_block_hdr.major_ver = DATA_HDR_MAJOR;
        p_stream_hnd->encr_block_hdr.minor_ver = DATA_HDR_MINOR;

        (void) memset(p_stream_hnd->encr_block_hdr.cipher_algo, '\0', sizeof(p_stream_hnd->encr_block_hdr.cipher_algo));
        (void) memcpy(p_stream_hnd->encr_block_hdr.cipher_algo, CIPHER_ALGO_NAME, (size_t) fmin(sizeof(CIPHER_ALGO_NAME), sizeof(p_stream_hnd->encr_block_hdr.cipher_algo)));

        // regenerate init vectors for the new encryption
        generate_iv(p_stream_hnd->encr_block_hdr.iv, sizeof(p_stream_hnd->encr_block_hdr.iv));

        // set the associated data field to the name of the file being encrypted
        (void) memset(p_stream_hnd->encr_block_hdr.aad, (int) 0, sizeof(p_stream_hnd->encr_block_hdr.aad));

        safe_copy_str((char * const) p_stream_hnd->encr_block_hdr.aad, p_stream_hnd->src_file_name, sizeof(p_stream_hnd->encr_block_hdr.aad));

        // in this version of the file format implementation, the cipher text is placed immediately after the header
        p_stream_hnd->encr_block_hdr.cipher_text_offset = sizeof(encrypted_data_hdr_t);

        // the size of the cipher text will be the same as the size of the plain text
        p_stream_hnd->encr_block_hdr.cipher_text_size = SdMngr_f_size(&p_stream_hnd->f_src_hnd);

        set_next_stage(p_stream_hnd, &read_from_header);

        res = CRYPTO_API_RES_OK;
    }

    return res;
}

/** @brief Refer to @ref p_stream_stage_pipeline_t function pointer type for a description of all parameters here */
STATIC crypto_api_res_t prep_file_for_stream_decr(crypto_stream_hnd_t * const p_stream_hnd)
{
    CRIT_ASSERT(NULL != p_stream_hnd);

    uint32_t bytes_read = 0U;

    // read encrypted file header
    FRESULT f_src_res = SdMngr_f_read(&p_stream_hnd->f_src_hnd, &p_stream_hnd->encr_block_hdr, sizeof(encrypted_data_hdr_t), (UINT *) &bytes_read);

    if ((FR_OK != f_src_res) || (bytes_read != sizeof(encrypted_data_hdr_t)))
    {
        CRYPTO_TRACE_DBG("[prep_file_for_stream_decr] encrypted file header read error => read code '%d' / bytes_read: %d => expected: %d!\n", f_src_res, bytes_read, sizeof(encrypted_data_hdr_t));

        return CRYPTO_API_RES_PARTIAL_FILE;
    }
    else
    {
        if ((p_stream_hnd->encr_block_hdr.major_ver != DATA_HDR_MAJOR) ||
            (p_stream_hnd->encr_block_hdr.minor_ver != DATA_HDR_MINOR) ||
            (0 != memcmp(p_stream_hnd->encr_block_hdr.cipher_algo, CIPHER_ALGO_NAME, (size_t) fmin(sizeof(CIPHER_ALGO_NAME), sizeof(p_stream_hnd->encr_block_hdr.cipher_algo)))) ||
            (0 == p_stream_hnd->encr_block_hdr.cipher_text_size) ||
            (p_stream_hnd->encr_block_hdr.cipher_text_offset < sizeof(encrypted_data_hdr_t)))
        {
            CRYPTO_TRACE_DBG("[prep_file_for_stream_decr] invalid file header detected!\n");

            return CRYPTO_API_RES_INVALID_HEADER;
        }
        else
        {
            // position the file pointer to the beginning of the cipher text
            f_src_res = SdMngr_f_lseek(&p_stream_hnd->f_src_hnd, p_stream_hnd->encr_block_hdr.cipher_text_offset);

            if (FR_OK != f_src_res)
            {
                CRYPTO_TRACE_DBG("[prep_file_for_stream_decr] invalid cipher text offset attempted: %ld!\n", p_stream_hnd->encr_block_hdr.cipher_text_offset);

                return CRYPTO_API_RES_INVALID_CIPHER_OFS;
            }
        }
    }

    set_next_stage(p_stream_hnd, &read_chunk_and_process);

    return CRYPTO_API_RES_OK;
}

/** @brief A helper function to read a data in a streaming manner from a given buffer in RAM
 *
 *  @param[in] p_stream_hnd stream handler context structure (keeps the state of the stream)
 *  @param[in] p_buf a pointer to the data in RAM to be read as a stream
 *  @param[in] buf_size size of the p_struct-pointed data in bytes
 *  @param[in] p_read_buf a temporary read buffer provided for intermediate data storage (not all handlers will use that and it is a responsibility of the general handler to ensure the size of this buffer can accommodate bytes_to_read bytes
 *  @param[out] p_output_buf this is the buffer where processed data shall be copied
 *  @param[in] bytes_to_read number of bytes to read when the stage is executed
 *  @param[in] p_bytes_read the buffer receives the actual number of bytes processed by the function and returned in p_output_buf
 *
 *  @return stream status after reading
 */
STATIC crypto_api_res_t read_from_buf(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * const p_buf, const uint32_t buf_size, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_buf);
    CRIT_ASSERT(buf_size > 0);
    CRIT_ASSERT(NULL != p_read_buf);
    CRIT_ASSERT(NULL != p_output_buf);
    CRIT_ASSERT(NULL != p_bytes_read);

    (void) p_read_buf;

    uint32_t actual_bytes_to_read = 0U;

    if (p_stream_hnd->stage_bytes_read < buf_size)
    {
        actual_bytes_to_read = (uint32_t) fmin(bytes_to_read, buf_size - p_stream_hnd->stage_bytes_read);

        // copy the actual data
        (void) memcpy(p_output_buf, &p_buf[p_stream_hnd->stage_bytes_read], actual_bytes_to_read);

        p_stream_hnd->stage_bytes_read += actual_bytes_to_read;

        *p_bytes_read = actual_bytes_to_read;
    }
    else
    {
        *p_bytes_read = 0U;
    }


    return CRYPTO_API_RES_OK;
}

/** @brief Refer to @ref p_stream_stage_pipeline_t function pointer type for a description of all parameters here */
STATIC crypto_api_res_t read_from_header(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    crypto_api_res_t res = read_from_buf(p_stream_hnd, (uint8_t * const) &p_stream_hnd->encr_block_hdr, sizeof(p_stream_hnd->encr_block_hdr), p_read_buf, p_output_buf, bytes_to_read, p_bytes_read);

    if (p_stream_hnd->stage_bytes_read >= sizeof(p_stream_hnd->encr_block_hdr))
    {
        set_next_stage(p_stream_hnd, &read_chunk_and_process);
    }

    return res;
}

/** @brief Refer to @ref p_stream_stage_pipeline_t function pointer type for a description of all parameters here */
STATIC crypto_api_res_t read_from_footer(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    crypto_api_res_t res = read_from_buf(p_stream_hnd, (uint8_t * const) &p_stream_hnd->data_footer, sizeof(p_stream_hnd->data_footer), p_read_buf, p_output_buf, bytes_to_read, p_bytes_read);

    if (p_stream_hnd->stage_bytes_read >= sizeof(p_stream_hnd->data_footer))
    {
        // end of processing chain
        set_next_stage(p_stream_hnd, NULL);
    }

    return res;
}

STATIC crypto_api_res_t prepare_temp_buf(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    uint32_t bytes_read = 0U;

    (void) p_output_buf;
    (void) bytes_to_read;

    // if the remaining bytes of the cipher text to read are less than the internal buffer, it must be only partially filled
    // (this is important for the decryption step because SdMngr_f_read() will read after the cipher text block, crossing over to the
    // footer block... and we don't want to process the footer block data as cipher text);
    // in the case of streaming encryption, SdMngr_f_read() will be reading from the original file and it cannot go beyond the end of the file,
    // thus no issue there
    uint32_t actual_bytes_to_read = (uint32_t) fmin(sizeof(p_stream_hnd->tmp_cipher_buf), (double) (p_stream_hnd->encr_block_hdr.cipher_text_size - p_stream_hnd->cipher_text_bytes_read));

    FRESULT f_src_res = SdMngr_f_read(&p_stream_hnd->f_src_hnd, p_read_buf, actual_bytes_to_read, (UINT *) &bytes_read);

    if (FR_OK == f_src_res)
    {
        if (bytes_read > 0)
        {
            size_t processed_data_size = 0U;

            // encrypt what was read from the file
            cmox_cipher_retval_t cipher_retval = cmox_cipher_append(p_stream_hnd->cipher_ctx,
                                                                    p_read_buf,
                                                                    bytes_read,
                                                                    p_stream_hnd->tmp_cipher_buf,
                                                                    &processed_data_size);

            if ((cipher_retval != CMOX_CIPHER_SUCCESS) || (processed_data_size != bytes_read))
            {
                CRYPTO_TRACE_DBG("cmox_cipher_append() failed with code %d\n", cipher_retval);

                return CRYPTO_API_RES_CRYPTOLIB_ERROR;
            }
            else
            {
                // this step only prepares the temporary buffer, the next one will start depleting it without
                // calling the CMOX library
                *p_bytes_read = 0;

                // set the prepared size for use by the next stage...
                p_stream_hnd->tmp_cipher_buf_prep_size = processed_data_size;

                set_next_stage(p_stream_hnd, &read_from_temp_buf);

                return CRYPTO_API_RES_OK;
            }
        }
    }
    else
    {
        CRYPTO_TRACE_DBG("file read failed with code %d\n", f_src_res);

        return CRYPTO_API_RES_FILE_ERROR;
    }

    return CRYPTO_API_RES_ERROR;
}

/** @brief Refer to @ref p_stream_stage_pipeline_t function pointer type for a description of all parameters here */
STATIC crypto_api_res_t read_chunk_and_process(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_read_buf);
    CRIT_ASSERT(NULL != p_output_buf);
    CRIT_ASSERT(NULL != p_bytes_read);

    uint32_t actual_bytes_to_read = 0U;
    uint32_t bytes_read = 0U;

    *p_bytes_read = 0;

    if (p_stream_hnd->cipher_text_bytes_read < p_stream_hnd->encr_block_hdr.cipher_text_size)
    {
        uint64_t rem_cipher_text_size = p_stream_hnd->encr_block_hdr.cipher_text_size - p_stream_hnd->cipher_text_bytes_read;

        actual_bytes_to_read = (uint32_t) fmin(bytes_to_read, rem_cipher_text_size);

        // correct the amount of read bytes to a multiple of MIN_CRYPTO_BUF_SIZE due to a specific requirement by the cmox_cipher_append() call
        if (actual_bytes_to_read >= MIN_CRYPTO_BUF_SIZE)
        {
            actual_bytes_to_read -= actual_bytes_to_read % MIN_CRYPTO_BUF_SIZE;
        }
        else
        {
            // there is not enough space in the user-provided buffer to accommodate the minimum required CMOX library buffer size =>
            // therefore we must perform the cipher_append operation in a temporary buffer of the correct size (usually a multiple of 16)
            // and deplete the buffer before reading again in the user buffer
            set_next_stage(p_stream_hnd, &prepare_temp_buf);

            // we will not return any bytes at this time...
            *p_bytes_read = 0;

            return CRYPTO_API_RES_OK;
        }

        FRESULT f_src_res = SdMngr_f_read(&p_stream_hnd->f_src_hnd, p_read_buf, actual_bytes_to_read, (UINT *) &bytes_read);

        if (FR_OK == f_src_res)
        {
            if (bytes_read > 0)
            {
                size_t processed_data_size = 0U;

                // encrypt what was read from the file
                cmox_cipher_retval_t cipher_retval = cmox_cipher_append(p_stream_hnd->cipher_ctx,
                                                                        p_read_buf,
                                                                        bytes_read,
                                                                        p_output_buf,
                                                                        &processed_data_size);

                if ((cipher_retval != CMOX_CIPHER_SUCCESS) || (processed_data_size != bytes_read))
                {
                    CRYPTO_TRACE_DBG("cmox_cipher_append() failed with code %d\n", cipher_retval);

                    return CRYPTO_API_RES_CRYPTOLIB_ERROR;
                }
                else
                {
                    p_stream_hnd->cipher_text_bytes_read += bytes_read;

                    *p_bytes_read = bytes_read;

                    return CRYPTO_API_RES_OK;
                }
            }
        }
        else
        {
            CRYPTO_TRACE_DBG("file read failed with code %d\n", f_src_res);

            return CRYPTO_API_RES_FILE_ERROR;
        }
    }

    *p_bytes_read = 0U;

    if (OP_CMOX_AES_GCM_ENC == p_stream_hnd->impl_type)
    {
        set_next_stage(p_stream_hnd, &prepare_footer);
    }
    else
    {
        set_next_stage(p_stream_hnd, &verify_footer);
    }

    // no more data to read...
    return CRYPTO_API_RES_OK;
}

/** @brief Refer to @ref p_stream_stage_pipeline_t function pointer type for a description of all parameters here */
STATIC crypto_api_res_t prepare_footer(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    CRIT_ASSERT(OP_CMOX_AES_GCM_ENC == p_stream_hnd->impl_type);
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_read_buf);
    CRIT_ASSERT(NULL != p_output_buf);
    CRIT_ASSERT(NULL != p_bytes_read);

    uint32_t processed_data_size = 0U;

    // this is a generation step only, we don't return any bytes... next section will provide the footer block data
    *p_bytes_read = 0U;

    (void) memcpy(p_stream_hnd->data_footer.footer_sig, FOOTER_SIGNATURE, sizeof(FOOTER_SIGNATURE) - 1);

    cmox_cipher_retval_t cipher_retval = cmox_cipher_generateTag(p_stream_hnd->cipher_ctx,
                                                                 p_stream_hnd->data_footer.auth_tag,
                                                                 (size_t *) &processed_data_size);

    if (cipher_retval != CMOX_CIPHER_SUCCESS)
    {
        CRYPTO_TRACE_DBG("cmox_cipher_generateTag() failed with code %d\n", cipher_retval);

        return CRYPTO_API_RES_AUTH_ERROR;
    }

    if (processed_data_size != sizeof(p_stream_hnd->data_footer.auth_tag))
    {
        CRYPTO_TRACE_DBG("expected tag size is %d but actual calculated size is %d\n", sizeof(p_stream_hnd->data_footer.auth_tag), processed_data_size);

        return CRYPTO_API_RES_AUTH_ERROR;
    }

    set_next_stage(p_stream_hnd, &read_from_footer);

    return CRYPTO_API_RES_OK;
}

/** @brief Refer to @ref p_stream_stage_pipeline_t function pointer type for a description of all parameters here */
STATIC crypto_api_res_t verify_footer(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    CRIT_ASSERT(OP_CMOX_AES_GCM_DEC == p_stream_hnd->impl_type);
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_read_buf);
    CRIT_ASSERT(NULL != p_output_buf);
    CRIT_ASSERT(NULL != p_bytes_read);

    (void) bytes_to_read;

    uint32_t fault_check = CMOX_CIPHER_AUTH_FAIL;
    uint32_t bytes_read = 0;

    // we only care about the result of this operation, if the footer is already verified, no bytes will be
    // returned for the stream read operation
    *p_bytes_read = 0U;

    (void) memset(&p_stream_hnd->data_footer, 0, sizeof(p_stream_hnd->data_footer));

    (void) SdMngr_f_read(&p_stream_hnd->f_src_hnd, &p_stream_hnd->data_footer, sizeof(p_stream_hnd->data_footer), (UINT *) &bytes_read);

    if (sizeof(p_stream_hnd->data_footer) != bytes_read)
    {
        CRYPTO_TRACE_DBG("could not read authentication tag block\n");

        return CRYPTO_API_RES_FILE_ERROR;
    }

    if (0 != memcmp(p_stream_hnd->data_footer.footer_sig, FOOTER_SIGNATURE, sizeof(p_stream_hnd->data_footer.footer_sig)))
    {
        CRYPTO_TRACE_DBG("invalid authentication tag marker read from stream\n");

        return CRYPTO_API_RES_INVALID_FOOTER;
    }

    cmox_cipher_retval_t cipher_retval = cmox_cipher_verifyTag(p_stream_hnd->cipher_ctx,
                                                               p_stream_hnd->data_footer.auth_tag,
                                                               &fault_check);

    if (CMOX_CIPHER_AUTH_SUCCESS != cipher_retval)
    {
        CRYPTO_TRACE_DBG("authentication tag verification failed!\n");

        return CRYPTO_API_RES_AUTH_ERROR;
    }

    if (CMOX_CIPHER_AUTH_SUCCESS != fault_check)
    {
        CRYPTO_TRACE_DBG("fault check for tag verification failed!\n");

        return CRYPTO_API_RES_AUTH_ERROR;
    }

    // end of processing chain
    set_next_stage(p_stream_hnd, NULL);

    return CRYPTO_API_RES_OK;
}

STATIC inline void set_next_stage(crypto_stream_hnd_t * const p_stream_hnd, p_stream_stage_pipeline_t const p_next_stage)
{
    CRIT_ASSERT(NULL != p_stream_hnd);

    p_stream_hnd->stage_bytes_read = 0;

//this is done to ignore the warning "ISO C forbids conversion of function pointer to object pointer type [-Wpedantic]"
    static_assert(sizeof(p_stream_hnd->p_current_stage_hnd) == sizeof(p_next_stage));
PRAGMA_DIAG_PUSH()
PRAGMA_DIAG_IGNORED(-Wpedantic)
    p_stream_hnd->p_current_stage_hnd = (void *)p_next_stage;
PRAGMA_DIAG_POP()
}

STATIC crypto_api_res_t read_from_temp_buf(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    crypto_api_res_t res = read_from_buf(p_stream_hnd, p_stream_hnd->tmp_cipher_buf, p_stream_hnd->tmp_cipher_buf_prep_size, p_read_buf, p_output_buf, bytes_to_read, p_bytes_read);

    // update the cipher text counter as well because we are currently in a sub-stage of the read_chunk_and_process stage
    p_stream_hnd->cipher_text_bytes_read += *p_bytes_read;

    if (p_stream_hnd->stage_bytes_read >= p_stream_hnd->tmp_cipher_buf_prep_size)
    {
        set_next_stage(p_stream_hnd, &read_chunk_and_process);
    }

    return res;
}

STATIC crypto_api_res_t read_from_file(crypto_stream_hnd_t * const p_stream_hnd, uint8_t * p_read_buf, uint8_t * const p_output_buf, const uint32_t bytes_to_read, uint32_t * const p_bytes_read)
{
    CRIT_ASSERT(NULL != p_stream_hnd);
    CRIT_ASSERT(NULL != p_read_buf);
    CRIT_ASSERT(NULL != p_output_buf);
    CRIT_ASSERT(NULL != p_bytes_read);

    uint32_t actual_bytes_to_read = 0U;
    uint32_t bytes_read = 0U;

    (void) p_read_buf;

    *p_bytes_read = 0;

    if (p_stream_hnd->cipher_text_bytes_read < p_stream_hnd->encr_block_hdr.cipher_text_size)
    {
        uint32_t rem_cipher_text_size = p_stream_hnd->encr_block_hdr.cipher_text_size - p_stream_hnd->cipher_text_bytes_read;

        actual_bytes_to_read = (uint32_t) fmin(bytes_to_read, rem_cipher_text_size);

        FRESULT f_src_res = SdMngr_f_read(&p_stream_hnd->f_src_hnd, p_output_buf, actual_bytes_to_read, (UINT *) &bytes_read);

        if (FR_OK == f_src_res)
        {
            if (bytes_read > 0)
            {
                p_stream_hnd->cipher_text_bytes_read += bytes_read;

                *p_bytes_read = bytes_read;

                return CRYPTO_API_RES_OK;
            }
        }
        else
        {
            CRYPTO_TRACE_DBG("file read failed with code %d\n", f_src_res);

            return CRYPTO_API_RES_FILE_ERROR;
        }
    }

    // no more data to read...
    *p_bytes_read = 0U;
    set_next_stage(p_stream_hnd, NULL);

    return CRYPTO_API_RES_OK;
}
