/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef FAULT_PERSISTOR_H
#define FAULT_PERSISTOR_H

#include "arm_fault_handler.h"

/** @brief Fault memory info type */
typedef struct
{
    uint8_t slots_occupied;     /**< number of currently occupied slots */
    uint8_t slots_available;    /**< number of available slots */
} fault_info_t;

/** @brief Call this function to prepare the module for use */
void fault_persistor_init(void);

/** @brief Provides basic fault memory information to users
 *  @param[out] p_fault_info buffer to receive the fault memory information
 * */
void fault_persistor_get_info(fault_info_t * const p_fault_info);

/** @brief Checks for any pending exceptions in RAM since last reset and persists them. */
void fault_persistor_store(void);

/** @brief Reads all stored faults from NVM to a user-provided buffer
 *  @param[out] p_buf user buffer to hold the fault data
 *  @param[in] buf_max_size size in bytes of the buffer pointed to by p_buf
 *  @param[out] p_bytes_read number of bytes written in p_buf
 *
 *  @warning In case the fault data size is bigger than buf_max_size, a partial read up to buf_max_size bytes will be performed.
 */
void fault_persistor_read_all(uint8_t * const p_buf, const uint32_t buf_max_size, uint32_t * const p_bytes_written);

/** @brief Reads a single exception frame located in the given slot
 *  @param[in] slot_id persisted frame slot id to read from
 *  @param[out] p_buf user buffer to receive the frame data
 *
 *  @retval true: the frame data is valid and successfully copied to the user buffer
 *  @retval false: the frame data is empty or invalid (p_buf may change content but it will be invalid eventually)
 */
bool fault_persistor_read_single(const uint8_t slot_id, persisted_ram_x_frame_t * const p_buf);

/** @brief Writes all persisted fault data to a file on the SD card
 *  @param[in] p_file_name name of the fault dump file to create on the SD card
 *
 *  @warning If the file already exists, it will be overwritten!
 */
void fault_persistor_dump_to_file(const char *p_file_name);

/** @brief Clear out the persistent fault storage */
void fault_persistor_clear(void);

#endif /* FAULT_PERSISTOR_H */
