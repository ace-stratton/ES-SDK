/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#include "fault_persistor.h"
#include "nvm.h"
#include <string.h>
#include <stdatomic.h>
#include "cmsis_os2.h"
#include "assertions.h"
#include "SdMngr.h"

/** @brief Slot index to NVM block index mapping */
static const uint16_t slot_fb_map[MAX_FAULT_BLOCKS_CNT] =
{
    NVM_BLOCK_FAULT_DATA0,  // slot index 0
    NVM_BLOCK_FAULT_DATA1,  // slot index 1
    NVM_BLOCK_FAULT_DATA2,  // slot index 2
    NVM_BLOCK_FAULT_DATA3,  // slot index 3
    NVM_BLOCK_FAULT_DATA4   // slot index 4
};

static const osMutexAttr_t fp_lock_attr =
{
    "fault_persistor_mutex",  // human readable mutex name
    osMutexPrioInherit |
    osMutexRecursive,         // attr_bits
    NULL,                     // memory for control block
    0U                        // size for control block
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t fp_lock_id;

/** @brief Basic fault block iterator context */
typedef struct
{
    uint8_t slot_id;            /**< keeps the currently iterated slot index */
    fault_index_t fault_idx;    /**< fault index block */
} fp_iter_ctx_t;

/** @brief Initializes a fault block iterator
 *  @param[in/out] p_iter iterator context
 * */
static void fp_iter_init(fp_iter_ctx_t * const p_iter);

/** @brief Returns the next stored exception frame
 *  @param[in/out] p_iter iterator context
 *  @param[out] p_frame buffer to receive the currently iterated frame data
 *
 *  @retval true: frame is copied successfully
 *  @retval false: no more frames to iterate over
 */
static bool fp_iter_next(fp_iter_ctx_t * const p_iter, persisted_ram_x_frame_t * const p_frame);

/** @brief Can be used to check if there are any fault records stored
 *  @param[in/out] p_iter iterator context
 *
 *  @retval true: fault records are available
 *  @retval false: fault records are not available
 */
static bool fp_iter_has_records(fp_iter_ctx_t * const p_iter);

void fault_persistor_init(void)
{
    if (NULL == fp_lock_id)
    {
        fp_lock_id = osMutexNew(&fp_lock_attr);
    }
}

void fault_persistor_get_info(fault_info_t * const p_fault_info)
{
    if (NULL != p_fault_info)
    {
        fault_index_t fault_idx = { .free_slots = MAX_FAULT_BLOCKS_CNT, .next_free_slot_index = 0U };

        Nvm_GetBlockById(NVM_BLOCK_FAULT_INDEX, &fault_idx);

        p_fault_info->slots_available = MAX_FAULT_BLOCKS_CNT;
        p_fault_info->slots_occupied = MAX_FAULT_BLOCKS_CNT - fault_idx.free_slots;
    }
}

void fault_persistor_store(void)
{
    static atomic_bool ram_faults_stored_in_nvm = false;

    // make sure this function can be called only once after reset
    if (ram_faults_stored_in_nvm)
    {
        return;
    }

    osMutexAcquire(fp_lock_id, osWaitForever);

    fault_block_t recovered_x_frame;
    fault_index_t fault_idx;

    bool is_valid_x_frame = arm_fault_handler_read_last((persisted_ram_x_frame_t *) &recovered_x_frame);

    if (is_valid_x_frame)
    {
        Nvm_GetBlockById(NVM_BLOCK_FAULT_INDEX, &fault_idx);

        if ((fault_idx.free_slots > 0) && (fault_idx.next_free_slot_index < MAX_FAULT_BLOCKS_CNT))
        {
            Nvm_SetBlockById(slot_fb_map[fault_idx.next_free_slot_index], (void *) &recovered_x_frame, NVMSETBLOCK_STORE_IMMEDIATELY);

            fault_idx.free_slots--;
            fault_idx.next_free_slot_index = (fault_idx.next_free_slot_index + 1) % MAX_FAULT_BLOCKS_CNT;

            Nvm_SetBlockById(NVM_BLOCK_FAULT_INDEX, (void *) &fault_idx, NVMSETBLOCK_STORE_IMMEDIATELY);
        }
    }

    ram_faults_stored_in_nvm = true;

    osMutexRelease(fp_lock_id);
}

void fault_persistor_read_all(uint8_t * const p_buf, const uint32_t buf_max_size, uint32_t * const p_bytes_written)
{
    uint32_t bytes_read = 0U;
    fp_iter_ctx_t iter;
    uint32_t size_to_copy = sizeof(persisted_ram_x_frame_t);

    if ((NULL == p_buf) || (0U == buf_max_size))
    {
        return;
    }

    osMutexAcquire(fp_lock_id, osWaitForever);

    persisted_ram_x_frame_t x_frame;

    fp_iter_init(&iter);

    while (fp_iter_next(&iter, &x_frame))
    {
        if (bytes_read + sizeof(persisted_ram_x_frame_t) > buf_max_size)
        {
            size_to_copy = buf_max_size - bytes_read;
        }

        (void) memcpy((void *) &p_buf[bytes_read], (void *) &x_frame, size_to_copy);
        bytes_read += size_to_copy;

        if (size_to_copy < sizeof(persisted_ram_x_frame_t))
        {
            break;
        }
    }

    if (NULL != p_bytes_written)
    {
        (*p_bytes_written) = bytes_read;
    }

    osMutexRelease(fp_lock_id);
}

bool fault_persistor_read_single(const uint8_t slot_id, persisted_ram_x_frame_t * const p_buf)
{
    bool res = false;
    fault_block_t nvm_fault_data;

    if ((slot_id >= MAX_FAULT_BLOCKS_CNT) || (NULL == p_buf))
    {
        return false;
    }

    osMutexAcquire(fp_lock_id, osWaitForever);

    (void) memset((void *) p_buf, 0U, sizeof(persisted_ram_x_frame_t));

    Nvm_GetBlockById(slot_fb_map[slot_id], (void *) &nvm_fault_data);

    if (arm_fault_handler_is_frame_valid((persisted_ram_x_frame_t *) &nvm_fault_data))
    {
        // this additional copy is needed because the NVM block contains some additional fields, like CRC
        // which must not be copied to the user buffer since it hasn't allocated space for them and thus
        // this will write outside of the persisted_ram_x_frame_t region
        (void) memcpy((void *) p_buf, &nvm_fault_data, sizeof(persisted_ram_x_frame_t));
        res = true;
    }

    osMutexRelease(fp_lock_id);

    return res;
}

void fault_persistor_dump_to_file(const char *p_file_name)
{
    if (NULL == p_file_name)
    {
        return;
    }

    FRESULT file_res = FR_DISK_ERR;
    FIL dump_file_hnd;
    fp_iter_ctx_t iter;

    fp_iter_init(&iter);

    if (!fp_iter_has_records(&iter))
    {
        return;
    }

    file_res = SdMngr_f_open(&dump_file_hnd, p_file_name, FA_WRITE | FA_CREATE_ALWAYS);

    if (FR_OK == file_res)
    {
        // add file signature
        (void) SdMngr_f_write(&dump_file_hnd, "FAULT_LST", 9, NULL);
        // write the record size as a header to the file
        uint32_t rec_size = sizeof(persisted_ram_x_frame_t);
        (void) SdMngr_f_write(&dump_file_hnd, &rec_size, sizeof(rec_size), NULL);

        persisted_ram_x_frame_t x_frame;

        osMutexAcquire(fp_lock_id, osWaitForever);

        while (fp_iter_next(&iter, &x_frame))
        {
            (void) SdMngr_f_write(&dump_file_hnd, (void *) &x_frame, sizeof(persisted_ram_x_frame_t), NULL);
        }

        osMutexRelease(fp_lock_id);

        (void) SdMngr_f_close(&dump_file_hnd);
    }
}

void fault_persistor_clear(void)
{
    fault_index_t fault_idx = { .free_slots = MAX_FAULT_BLOCKS_CNT, .next_free_slot_index = 0U };

    osMutexAcquire(fp_lock_id, osWaitForever);

    // reset only the index
    Nvm_SetBlockById(NVM_BLOCK_FAULT_INDEX, (void *) &fault_idx, NVMSETBLOCK_STORE_IMMEDIATELY);

    fault_block_t zeroed_out_block;
    (void) memset((void *) &zeroed_out_block, 0U, sizeof(zeroed_out_block));

    for (uint8_t slot_id = 0; slot_id < MAX_FAULT_BLOCKS_CNT; slot_id++)
    {
        Nvm_SetBlockById(slot_fb_map[slot_id], &zeroed_out_block, NVMSETBLOCK_STORE_IMMEDIATELY);
    }

    osMutexRelease(fp_lock_id);
}

static void fp_iter_init(fp_iter_ctx_t * const p_iter)
{
    CRIT_ASSERT(NULL != p_iter);

    p_iter->fault_idx.free_slots = MAX_FAULT_BLOCKS_CNT;
    p_iter->fault_idx.next_free_slot_index = 0U;
    p_iter->slot_id = 0U;

    Nvm_GetBlockById(NVM_BLOCK_FAULT_INDEX, &(p_iter->fault_idx));

}

static bool fp_iter_next(fp_iter_ctx_t * const p_iter, persisted_ram_x_frame_t * const p_frame)
{
    CRIT_ASSERT(NULL != p_iter);
    CRIT_ASSERT(NULL != p_frame);

    bool res = false;

    while (p_iter->slot_id < (MAX_FAULT_BLOCKS_CNT - p_iter->fault_idx.free_slots))
    {
        // invalid slots are not transferred
        if (!fault_persistor_read_single(p_iter->slot_id++, p_frame))
        {
            continue;
        }

        res = true;
        break;
    }

    return res;
}

static bool fp_iter_has_records(fp_iter_ctx_t * const p_iter)
{
    CRIT_ASSERT(NULL != p_iter);

    return (p_iter->fault_idx.free_slots < MAX_FAULT_BLOCKS_CNT);
}
