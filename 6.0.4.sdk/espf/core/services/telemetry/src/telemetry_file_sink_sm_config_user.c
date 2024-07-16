#include "libhsm.h"
#include "telemetry_file_sink_sm_config_user.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!

/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_file_sink_sm_config_user.c
 * @brief Telemetry file sink state machine functions implementation
 *
 * @note This file contains generated code by libhsm based on `telemetry_file_sink_sm.yaml`.
 *
 * @}
 */

#include "es_cdef.h"
#include "es_exeh.h"
#include "assertions.h"
#include "SdMngr.h"
#include "crc16-ccitt.h"
#include "telemetry_queue.h"
#include "telemetry_types.h"
#include "timer.h"

#include <stdio.h>
#include <string.h>

static uint32_t telemetry_file_sink_getfreebytes(void);
static void telemetry_file_sink_prepare_fname(uint16_t index);
static void telemetry_file_sink_find_first_slot(void);
static bool telemetry_file_sink_shall_write(uint32_t next_write_offset, uint16_t msg_size);
static void telemetry_file_sink_prepare_next_slot(void);
static bool telemetry_file_sink_is_fhdr_valid(tlm_file_hdr_t *p_hdr);
static inline bool telemetry_file_sink_is_file_complete(tlm_file_hdr_t * const p_fhdr, FIL * const f_handle);
static void telemetry_file_sink_init_header(tlm_file_hdr_t * const p_hdr);
static inline void telemetry_file_sink_update_hdr_crc(tlm_file_hdr_t * const p_hdr);
static inline void telemetry_file_sink_write_hdr(FIL * const f_handle, tlm_file_hdr_t * const p_hdr);

void telemetry_file_sink_clean(void)
{
    FRESULT res;
    FF_DIR dinfo;
    FILINFO finfo;

    res = SdMngr_f_findfirst(&dinfo, &finfo, TLM_FILE_SINK_ROOT_PATH, tlm_filesink_rt_context.wildcard);

    while ((FR_OK == res) &&
           ('\0' != finfo.fname[0U]))
    {
        (void) SdMngr_f_unlink(finfo.fname);
        res = SdMngr_f_findnext(&dinfo, &finfo);
    }

    (void) SdMngr_f_closedir(&dinfo);
}

/** @brief Updates the header CRC and writes it to the provided file handle
 *  @param[in] f_handle file handle opened for writing
 *  @param[in/out] p_hdr telemetry header structure to write to the file after updating its CRC
 */
static inline void telemetry_file_sink_write_hdr(FIL * const f_handle, tlm_file_hdr_t * const p_hdr)
{
    CRIT_ASSERT(NULL != f_handle);
    CRIT_ASSERT(NULL != p_hdr);
    UINT bw = 0;

    telemetry_file_sink_update_hdr_crc(p_hdr);

    uint32_t prev_pos = SdMngr_f_tell(f_handle);
    // set file pointer to beginning of file in order to update the header
    FRESULT fr = SdMngr_f_lseek(f_handle, 0U);

    if (FR_OK != fr)
    {
        ES_TRACE_ERROR("file seek error [%ld]", fr);
        return;
    }

    fr = SdMngr_f_write(f_handle, (const void *) p_hdr, sizeof(tlm_file_hdr_t), &bw);

    if (FR_OK != fr)
    {
        ES_TRACE_ERROR("tlm header write error [%ld]", fr);
        return;
    }

    // restore file pointer where it was...
    (void) SdMngr_f_lseek(f_handle, prev_pos);
}

/** @brief Calculates the CRC of a file telemetry header
 *  @param[in/out] p_hdr pointer to a file telemetry header structure which receives the updated CRC
 */
static inline void telemetry_file_sink_update_hdr_crc(tlm_file_hdr_t * const p_hdr)
{
    CRIT_ASSERT(NULL != p_hdr);

    p_hdr->crc = crc16_ccitt_table((const uint8_t *) p_hdr, sizeof(tlm_file_hdr_t) - sizeof(p_hdr->crc));
}

/** @brief Populates a file header structure with default values
 *  @param[in] p_hdr pointer to a telemetry file header structure to fill-in
 */
static void telemetry_file_sink_init_header(tlm_file_hdr_t * const p_hdr)
{
    CRIT_ASSERT(NULL != p_hdr);

    (void) memcpy(&p_hdr->signature, TLM_FILE_SIGN, sizeof(p_hdr->signature));
    // TODO: hardcoded for now but shall be matched to DataCache version (which is currently not generated yet!)
    p_hdr->version = 0x00000101U;
    p_hdr->next_write_offset = sizeof(tlm_file_hdr_t);
    p_hdr->file_complete = false;
    p_hdr->last_timestamp = 0;
}

/** @brief The function abstracts the decision whether file writing is complete or not.
 *
 *  @param[in] p_fhdr a pointer to a valid telemetry file header
 *  @param[in] f_handle opened handle to the file so that its size can be checked
 *
 *  @return true: file is complete according to the configuration; false: writing can continue in the same file at next_write_position
 */
static inline bool telemetry_file_sink_is_file_complete(tlm_file_hdr_t * const p_fhdr, FIL * const f_handle)
{
    // currently unused
    (void) f_handle;

    return p_fhdr->file_complete;
}

/** @brief Returns the free space on the storage
 *  @return value in bytes
 */
static uint32_t telemetry_file_sink_getfreebytes(void)
{
    FATFS *fs;
    DWORD fre_clust;
    uint32_t free_bytes = 0U;

    FRESULT res = SdMngr_f_getfree(TLM_FILE_SINK_ROOT_PATH, &fre_clust, &fs);

    if (FR_OK == res)
    {
        free_bytes = fre_clust * fs->csize * FF_MIN_SS;
    }

    return free_bytes;
}

/** @brief Derives a telemetry file name based on index
 *  @param[in] index Telemetry file index
 *
 *  @note Relies on an external static memory buffer!
 */
static void telemetry_file_sink_prepare_fname(uint16_t index)
{
    snprintf(tlm_filesink_rt_context.current_file_name,
            sizeof(tlm_filesink_rt_context.current_file_name),
            "%s%05d.%s",
            TLM_FILE_SINK_ROOT_PATH,
            index,
            TLM_FILE_SINK_EXT);
}

/** @brief Responsible to scan existing files and decide in which file to continue/start
 *            telemetry logging.
 *
 *  @note To be used for size-limit-based logging because it considers the maximum number of files
 *        configured in NVM. For time-limit-based logging, there is no maximum number of files - only maximum size
 *        of an individual file.
 */
static void telemetry_file_sink_find_first_slot(void)
{
    FRESULT res;
    tlm_file_hdr_t fhdr;
    FIL fhnd;
    uint16_t last_valid_file_index = tlm_filesink_rt_context.current_idx;
    struct {
        uint16_t last_invalid_file_index;
        bool is_index_valid;
    } last_invalid_file_info = { .last_invalid_file_index = 0, .is_index_valid = false };
    UINT bytes_read = 0;

    bool partial_match_found = false;

    CRIT_ASSERT(tlm_filesink_rt_context.max_file_size_bytes >= TLM_MSG_SIZE_BYTES_LEAST);

    tlm_filesink_rt_context.current_idx = 0U;

    while (tlm_filesink_rt_context.current_idx < tlm_filesink_rt_context.cfg.max_log_files_cnt)
    {
        telemetry_file_sink_prepare_fname(tlm_filesink_rt_context.current_idx);

        ES_TRACE_DEBUG("opening '%s'", tlm_filesink_rt_context.current_file_name);
        res = SdMngr_f_open(&fhnd, tlm_filesink_rt_context.current_file_name, FA_OPEN_EXISTING | FA_READ);

        if (FR_OK == res)
        {
            // Note: This initialization is important in case of a failing SdMngr_f_read() call
            (void) memset(&fhdr, 0U, sizeof(fhdr));
            res = SdMngr_f_read(&fhnd, (void *) &fhdr, sizeof(fhdr), &bytes_read);
            (void) SdMngr_f_close(&fhnd);

            if ((FR_OK == res) && (sizeof(fhdr) == bytes_read) && (telemetry_file_sink_is_fhdr_valid(&fhdr)))
            {
                // store last valid file index - it may be complete or partial...
                last_valid_file_index = tlm_filesink_rt_context.current_idx;

                // check if writing to this file can continue...
                if (!telemetry_file_sink_is_file_complete(&fhdr, &fhnd))
                {
                    ES_TRACE_DEBUG("[%u] partial match", tlm_filesink_rt_context.current_idx);
                    partial_match_found = true;
                    // we found the last partial file...
                    break;
                }
                else
                {
                    ES_TRACE_DEBUG("[%u] file complete", tlm_filesink_rt_context.current_idx);
                }

                // if we reach a full or partial file, then we should not restore writing to the last invalid file, thus
                // invalidate last invalid file index
                last_invalid_file_info.is_index_valid = false;
                last_invalid_file_info.last_invalid_file_index = tlm_filesink_rt_context.current_idx;
            }
            else
            {
                ES_TRACE_DEBUG("[%u] invalid file header", tlm_filesink_rt_context.current_idx);
                // save last invalid file index to reuse if there are no any other partial slots after it in the sequence
                last_invalid_file_info.last_invalid_file_index = tlm_filesink_rt_context.current_idx;
                last_invalid_file_info.is_index_valid = true;
            }
        }
        else if (FR_NO_FILE == res)
        {
            // we didn't find a partial file and there are still free slots and maybe an invalid file slot to reuse...
            last_valid_file_index = (last_invalid_file_info.is_index_valid) ?
                    last_invalid_file_info.last_invalid_file_index :
                    tlm_filesink_rt_context.current_idx;
            // in this case, we still don't have all slot files created on the SD card, so we must
            // create a new slot file and continue from the current index instead of going back to 0 which
            // will be done once we completely fill all slot files on the SD card
            partial_match_found = true;

            break;
        }
        else
        {
            partial_match_found = false;
        }

        // make sure that the telemetry index is always changed regardless of error to
        // guarantee that the while loop is not infinite
        tlm_filesink_rt_context.current_idx++;
    }

    // in case the file was not closed above...
    (void) SdMngr_f_close(&fhnd);

    // prepare last valid file for use... if the last valid file was partially filled, continue with it, otherwise starts from slot 0
    tlm_filesink_rt_context.current_idx = partial_match_found ? last_valid_file_index : 0U;
    telemetry_file_sink_prepare_fname(tlm_filesink_rt_context.current_idx);
    ES_TRACE_DEBUG("preparing tlm file: '%s'", tlm_filesink_rt_context.current_file_name);
}

/** @brief The function makes a decision whether next write in the current file can occur
 *            based on the current configuration and state.
 *  @param[in] next_write_offset byte location where next write will take place in the current file
 *  @param[in] msg_size Size in bytes of the next message to write to the file
 *
 *  @return true: write can be performed; false: skip write and prepare another file to continue
 */
static bool telemetry_file_sink_shall_write(uint32_t next_write_offset, uint16_t msg_size)
{
    bool res = false;

    switch (tlm_filesink_rt_context.cfg.cfg_type)
    {
        case TLM_FILE_CFG_TYPE_TIME_LIMIT:
        {
            // time-limit parameters:
            // time_limit_sec
            // file_size_limit_kb

            break;
        }

        case TLM_FILE_CFG_TYPE_SIZE_LIMIT:
        default:
        {
            // size-limit parameters:
            // size_limit_kb
            // max_log_files_cnt

            if ((next_write_offset + msg_size) <= tlm_filesink_rt_context.max_file_size_bytes)
            {
                res = true;
            }

            break;
        }
    }

    return res;
}

/** @brief The function is responsible to prepare the next file slot to write to depending on the current state and
 *            configuration.
 */
static void telemetry_file_sink_prepare_next_slot(void)
{
    switch (tlm_filesink_rt_context.cfg.cfg_type)
    {
        case TLM_FILE_CFG_TYPE_TIME_LIMIT:
        {
            break;
        }

        case TLM_FILE_CFG_TYPE_SIZE_LIMIT:
        default:
        {
            tlm_filesink_rt_context.current_idx =
                    (tlm_filesink_rt_context.current_idx + 1U) % tlm_filesink_rt_context.cfg.max_log_files_cnt;

            telemetry_file_sink_prepare_fname(tlm_filesink_rt_context.current_idx);

            // reinitilize the new slot file header
            FIL tlm_file_handle;
            tlm_file_hdr_t fhdr;
            UINT bytes_read = 0;
            UINT bytes_written = 0;

            FRESULT res = SdMngr_f_open(&tlm_file_handle,
                                        tlm_filesink_rt_context.current_file_name,
                                        FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

            if (FR_OK == res)
            {
                res = SdMngr_f_read(&tlm_file_handle, &fhdr, sizeof(fhdr), &bytes_read);

                if ((FR_OK == res) && (sizeof(fhdr) == bytes_read))
                {
                    telemetry_file_sink_init_header(&fhdr);
                    telemetry_file_sink_update_hdr_crc(&fhdr);

                    // set file pointer to beginning of file in order to update the header
                    (void) SdMngr_f_lseek(&tlm_file_handle, 0U);
                    res = SdMngr_f_write(&tlm_file_handle, (const void *) &fhdr, sizeof(fhdr), &bytes_written);

                    if ((FR_OK == res) && (sizeof(fhdr) == bytes_written))
                    {
                        ES_TRACE_DEBUG("[%u] next slot header prepared for use", tlm_filesink_rt_context.current_idx);
                    }
                    else
                    {
                        ES_TRACE_DEBUG("[%u] error when trying to prepare new slot", tlm_filesink_rt_context.current_idx);
                    }
                }

                (void) SdMngr_f_close(&tlm_file_handle);
            }

            break;
        }
    }
}

static bool telemetry_file_sink_is_fhdr_valid(tlm_file_hdr_t *p_hdr)
{
    bool is_valid = false;

    CRIT_ASSERT(NULL != p_hdr);

    int sig_res = memcmp(p_hdr->signature, TLM_FILE_SIGN, sizeof(p_hdr->signature));

    if (0U == sig_res)
    {
        uint16_t fhdr_crc = p_hdr->crc;
        telemetry_file_sink_update_hdr_crc(p_hdr);

        is_valid = (fhdr_crc == p_hdr->crc);
    }

    return is_valid;
}

// USER_CODE_END::@main@

// Entry/Exit functions


// GEN_OBJ_START::telemetry_file_sink_sm_on_entry_Init
void telemetry_file_sink_sm_on_entry_Init(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Init

    tlm_filesink_rt_context.current_idx = 0U;
    tlm_filesink_rt_context.prev_cfg_type = TLM_FILE_CFG_TYPE_MAX;
    (void) memset(tlm_filesink_rt_context.tlm_msg_buffer, 0U, sizeof(tlm_filesink_rt_context.tlm_msg_buffer));
    tlm_filesink_rt_context.auto_resume_period_ms = 0U;
    timer_stop(&tlm_filesink_rt_context.auto_resume_timer);
    telemetry_file_sink_sm_action_reload_config(pSMRoot, pEvent);

    // USER_CODE_END::onEntry_Init
}
// GEN_OBJ_END::telemetry_file_sink_sm_on_entry_Init

// GEN_OBJ_START::telemetry_file_sink_sm_on_entry_Stopped
void telemetry_file_sink_sm_on_entry_Stopped(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Stopped
    (void) pSMRoot;
    (void) pEvent;

    // the timer is stopped here and can be started by an external event
    if (tlm_filesink_rt_context.auto_resume_period_ms > 0U)
    {
        timer_start(&tlm_filesink_rt_context.auto_resume_timer);
    }
    else
    {
        timer_stop(&tlm_filesink_rt_context.auto_resume_timer);
    }

    // USER_CODE_END::onEntry_Stopped
}
// GEN_OBJ_END::telemetry_file_sink_sm_on_entry_Stopped



// Guard condition functions
// GEN_OBJ_START::telemetry_file_sink_sm_guard_can_start_operation
bool telemetry_file_sink_sm_guard_can_start_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_can_start_operation
    (void) pSMRoot;
    (void) pEvent;

    return IS_TRUE(tlm_filesink_rt_context.gen_cfg.file_telemetry_en);
    // USER_CODE_END::guard_can_start_operation
}
// GEN_OBJ_END::telemetry_file_sink_sm_guard_can_start_operation

// GEN_OBJ_START::telemetry_file_sink_sm_guard_is_storage_available
bool telemetry_file_sink_sm_guard_is_storage_available(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_storage_available
    (void) pSMRoot;
    (void) pEvent;

    return (SdMngr_GetCardState() == SDMNGR_CARD_STATE_READY);
    // USER_CODE_END::guard_is_storage_available
}
// GEN_OBJ_END::telemetry_file_sink_sm_guard_is_storage_available

// GEN_OBJ_START::telemetry_file_sink_sm_guard_can_stop_operation
bool telemetry_file_sink_sm_guard_can_stop_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_can_stop_operation


    (void) pSMRoot;
    (void) pEvent;

    return true;

    // USER_CODE_END::guard_can_stop_operation
}
// GEN_OBJ_END::telemetry_file_sink_sm_guard_can_stop_operation

// GEN_OBJ_START::telemetry_file_sink_sm_guard_is_storage_blocked
bool telemetry_file_sink_sm_guard_is_storage_blocked(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_storage_blocked
    return !telemetry_file_sink_sm_guard_is_storage_available(pSMRoot, pEvent);
    // USER_CODE_END::guard_is_storage_blocked
}
// GEN_OBJ_END::telemetry_file_sink_sm_guard_is_storage_blocked

// GEN_OBJ_START::telemetry_file_sink_sm_guard_is_auto_resume_timer_elapsed
bool telemetry_file_sink_sm_guard_is_auto_resume_timer_elapsed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_auto_resume_timer_elapsed
    (void) pSMRoot;
    (void) pEvent;

    bool res = ((IS_TRUE(tlm_filesink_rt_context.auto_resume_timer.is_running)) &&
                (timer_is_elapsed(&tlm_filesink_rt_context.auto_resume_timer, tlm_filesink_rt_context.auto_resume_period_ms)));

    return res;
    // USER_CODE_END::guard_is_auto_resume_timer_elapsed
}
// GEN_OBJ_END::telemetry_file_sink_sm_guard_is_auto_resume_timer_elapsed


// Action handlers
// GEN_OBJ_START::telemetry_file_sink_sm_action_reload_config
void telemetry_file_sink_sm_action_reload_config(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_reload_config
    static safe_bool_t first_start = SAFE_TRUE;

    (void) pSMRoot;
    (void) pEvent;

    Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_FILE_CFG, &tlm_filesink_rt_context.cfg);
    Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_GENERAL, &tlm_filesink_rt_context.gen_cfg);

    if (IS_TRUE(first_start))
    {
        tlm_filesink_rt_context.prev_cfg_type = tlm_filesink_rt_context.cfg.cfg_type;

        SET_FALSE(first_start);
    }

    if (tlm_filesink_rt_context.prev_cfg_type != tlm_filesink_rt_context.cfg.cfg_type)
    {
        tlm_filesink_rt_context.prev_cfg_type = tlm_filesink_rt_context.cfg.cfg_type;

        // configuration change on the fly... remove existing telemetry and start anew...
        telemetry_file_sink_clean();
        tlm_filesink_rt_context.current_idx = 0U;
        telemetry_file_sink_prepare_fname(tlm_filesink_rt_context.current_idx);
    }

    switch (tlm_filesink_rt_context.cfg.cfg_type)
    {
        case TLM_FILE_CFG_TYPE_TIME_LIMIT:
        {
            tlm_filesink_rt_context.max_file_size_bytes = tlm_filesink_rt_context.cfg.file_size_limit_kb * 1024U;

            break;
        }

        case TLM_FILE_CFG_TYPE_SIZE_LIMIT:
        default:
        {
            CRIT_ASSERT(0U != tlm_filesink_rt_context.cfg.max_log_files_cnt);
            CRIT_ASSERT(0U != tlm_filesink_rt_context.cfg.size_limit_kb);

            tlm_filesink_rt_context.max_file_size_bytes =
                    (tlm_filesink_rt_context.cfg.size_limit_kb * 1024U) / tlm_filesink_rt_context.cfg.max_log_files_cnt;
            break;
        }
    }

    // USER_CODE_END::action_reload_config
}
// GEN_OBJ_END::telemetry_file_sink_sm_action_reload_config

// GEN_OBJ_START::telemetry_file_sink_sm_action_perform_file_scan
void telemetry_file_sink_sm_action_perform_file_scan(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_perform_file_scan

    switch (tlm_filesink_rt_context.cfg.cfg_type)
    {
        case TLM_FILE_CFG_TYPE_TIME_LIMIT:
        {
            // time-limit parameters:
            // time_limit_sec
            // file_size_limit_kb

            break;
        }

        case TLM_FILE_CFG_TYPE_SIZE_LIMIT:
        default:
        {
            // reload configuration explicitly, just in case we couldn't load it in one of the previous states
            telemetry_file_sink_sm_action_reload_config(pSMRoot, pEvent);

            // size-limit parameters:
            // size_limit_kb
            // max_log_files_cnt
            telemetry_file_sink_find_first_slot();

            break;
        }
    }

    // USER_CODE_END::action_perform_file_scan
}
// GEN_OBJ_END::telemetry_file_sink_sm_action_perform_file_scan

// GEN_OBJ_START::telemetry_file_sink_sm_action_store_telemetry
void telemetry_file_sink_sm_action_store_telemetry(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_store_telemetry
    FRESULT res;
    FIL tlm_file_handle;
    tlm_file_hdr_t fhdr;
    UINT bytes_read;

    (void) pSMRoot;
    (void) pEvent;

    telemetry_queue_update_stats(TLM_STATS_ID_ACTIVE_SLOT, tlm_filesink_rt_context.current_idx);

    (void) memset(&fhdr, 0U, sizeof(fhdr));
    res = SdMngr_f_open(&tlm_file_handle,
                        tlm_filesink_rt_context.current_file_name,
                        FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

    if (FR_OK == res)
    {
        // verify file header...
        res = SdMngr_f_read(&tlm_file_handle, &fhdr, sizeof(fhdr), &bytes_read);

        if ((FR_OK == res) && (sizeof(fhdr) == bytes_read) && (telemetry_file_sink_is_fhdr_valid(&fhdr)))
        {
            fhdr.next_write_offset = (telemetry_file_sink_is_file_complete(&fhdr, &tlm_file_handle)) ?
                                     (sizeof(tlm_file_hdr_t)) :
                                     (fhdr.next_write_offset);

            // restore file position pointer based on information from the header...
            SdMngr_f_lseek(&tlm_file_handle,
                           fhdr.next_write_offset);
        }
        else
        {
            telemetry_file_sink_init_header(&fhdr);

            telemetry_file_sink_write_hdr(&tlm_file_handle, &fhdr);

            // skip header and set file pointer position for first message
            (void) SdMngr_f_lseek(&tlm_file_handle, sizeof(fhdr));
        }

        uint16_t next_msg_size = telemetry_queue_peek();
        uint32_t free_bytes = telemetry_file_sink_getfreebytes();
        uint32_t batch_msg_count = 0U;

        if (free_bytes > next_msg_size)
        {
            while (next_msg_size > 0U)
            {
                UINT bytes_written = 0U;

                if (telemetry_file_sink_shall_write(fhdr.next_write_offset, next_msg_size))
                {
                    uint16_t bytes_read_from_queue = telemetry_queue_pop(tlm_filesink_rt_context.tlm_msg_buffer,
                                                                         sizeof(tlm_filesink_rt_context.tlm_msg_buffer));

                    CRIT_ASSERT(bytes_read_from_queue == next_msg_size);

                    res = SdMngr_f_write(&tlm_file_handle,
                                         tlm_filesink_rt_context.tlm_msg_buffer,
                                         bytes_read_from_queue,
                                         &bytes_written);

                    fhdr.next_write_offset = SdMngr_f_tell(&tlm_file_handle);

                    if ((FR_OK != res) || (bytes_written != bytes_read_from_queue))
                    {
                        EXEH_HANDLE_EX(eEXEHSeverity_Error,
                                       eEXEHModuleID_TELEMETRY_FILESINK,
                                       (int32_t) EXEH_TLM_FS_FILE_ERROR);

                        ES_TRACE_DEBUG("[%u] tlm wrt error [%d]", tlm_filesink_rt_context.current_idx, res);

                        break;
                    }
                    else
                    {
                        fhdr.file_complete = false;

                        telemetry_file_sink_write_hdr(&tlm_file_handle, &fhdr);

                        next_msg_size = telemetry_queue_peek();

                        batch_msg_count++;

                        ES_TRACE_DEBUG("[%u] tlm wrt @ offs %lu", tlm_filesink_rt_context.current_idx, fhdr.next_write_offset);
                    }
                }
                else
                {
                    ES_TRACE_DEBUG("no space in current file [%u]. switching to next slot...", tlm_filesink_rt_context.current_idx);

                    // TODO: timestamp is currently unused
                    fhdr.last_timestamp = 0U;
                    fhdr.file_complete = true;
                    // next writes in this file will start from
                    fhdr.next_write_offset = sizeof(tlm_file_hdr_t);

                    // Note: Order is important here in case of intermediate reset after this point! The next file slot must be
                    // prepared first before marking the current one as complete, otherwise we may end up with the current file complete and
                    // no partial slot to continue from next time after reset.
                    telemetry_file_sink_prepare_next_slot();

                    // call this after telemetry_file_sink_prepare_next_slot() to ensure correct recovery in case of CPU reset between these
                    // two calls
                    telemetry_file_sink_write_hdr(&tlm_file_handle, &fhdr);

                    break;
                }
            }

            // report statistics on last run...
            telemetry_queue_update_stats(TLM_STATS_ID_BATCH_COUNT, batch_msg_count);
        }

        (void) SdMngr_f_close(&tlm_file_handle);
    }

    // USER_CODE_END::action_store_telemetry
}
// GEN_OBJ_END::telemetry_file_sink_sm_action_store_telemetry

// GEN_OBJ_START::telemetry_file_sink_sm_action_clean_and_reload_cfg
void telemetry_file_sink_sm_action_clean_and_reload_cfg(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_clean_and_reload_cfg

    telemetry_file_sink_sm_action_reload_config(pSMRoot, pEvent);

    telemetry_file_sink_clean();
    tlm_filesink_rt_context.current_idx = 0U;

    // USER_CODE_END::action_clean_and_reload_cfg
}
// GEN_OBJ_END::telemetry_file_sink_sm_action_clean_and_reload_cfg
