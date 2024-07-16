#ifndef SX_BAND_PL_CTRL_H
#define SX_BAND_PL_CTRL_H

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup es_sxband S/X Band Transmitter
 * @{
 *
 * Declaration of the SXBand file iterator interface
 *
 * @file     sxband_cmd_iter_file.h
 * @brief    S/X Band file iterator interface
 *
 * @}
 * @}
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "if_sxband_cmd_iter.h"
#include "SdMngr.h"

/**
 * @brief Specifies the different kinds of alloc operation statuses
 */
typedef enum
{
    SXB_INIT_STATUS_OK = 0U,
    SXB_INIT_STATUS_FS_ERROR,
    SXB_INIT_STATUS_INVALID_FILE_FORMAT,
    SXB_INIT_STATUS_MAX
} sxband_cmd_iter_init_status_t;

/**
 * @brief File iterator context structure
 */
typedef struct
{
    char cmd_file_name[30U];            /**< Name of the file containing the commands */
    FIL f_hnd;                          /**< File system file handle */
    FRESULT fs_last_res;                /**< Last file system operation status */
    FRESULT find_iter_res;              /**< Last file iterator operation status (f_findfirst(), f_findnext() */
    uint32_t cmd_idx;                   /**< Command index in the command file */
    cmd_list_hdr_t cmd_list_hdr;        /**< List header data as loaded by the iterator */
    cmd_list_command_t iter_cmd_entry;  /**< Current command data as read by the iterator */
    FF_DIR dir_obj;                        /**< FATFS directory object used to perform wildcard file name scanning */
    FILINFO fno;                        /**< FATFS file information entry obtained during wildcard file name scanning */
    char file_pattern[30U];             /**< Used to keep a copy of the requested user file pattern until file iteration is finished */
    bool has_more_files;                /**< Indicates whether there are more files to be listed by the SdMngr_f_findnext() function */
} sxband_cmd_file_iter_ctx_t;

/**
 * @brief Prepares an iterator interface context for a given file with commands
 *
 * @param[in] cmd_file_name   Name of the file containing the commands
 * @param[in] cmd_file_name_size Size in bytes of the cmd_file_name parameter
 * @param[out] p_file_ctx     Provides a buffer to receive the initialized iteration context
 * @return status of the operation
 */
sxband_cmd_iter_init_status_t sxband_cmd_iter_file_init_ctx(const char * const cmd_file_name, const uint8_t cmd_file_name_size, sxband_cmd_file_iter_ctx_t * const p_file_ctx);

extern const if_sxband_cmd_iter_t sxband_cmd_iter_file;

#ifdef __cplusplus
}
#endif

#endif    /* SX_BAND_PL_CTRL_H */
