/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef SDMNGR_H
#define SDMNGR_H
/**
 * @addtogroup Services
 * @{
 *
 * @defgroup sd_mng SD Manager
 * @{
 *
 * Service to perform read and write operations in the SD Card.
 * In order to use, just call SdMngr_InitTask() which starts the SD manager RTOS task
 *  as soon as the RTOS kernel is running. The task is then responsible to make SD I/O
 *  initialization and file system mounting making all public **SDMngr** APIsavailable for use.
 *
 * Most FATFS APIs are wrapped directly so if you need to use `f_open()` FATFS call, you shall only
 *  put a prefix **SDMngr_** and use the same arguments as you would with FATFS, e.g.
 *
 * ```c
 * fileOperationsResult = f_open(&dest_file, binPath, FA_READ | FA_OPEN_EXISTING);
 *  ```
 *
 * becomes:
 *
 * ```c
 * fileOperationsResult = SdMngr_f_open(&dest_file, binPath, FA_READ | FA_OPEN_EXISTING);
 * ```
 *
 * The path size is limited to 47 characters where 46 are the path, including the mount point,
 *  and the last is always a null character.
 *
 * To specify the mounting point, '/' must be used (i.e. /sd/my_file.txt or /mnt/my_file.txt).
 *  If no mount point is specified, the OBC is going to assign the default mount point, currently "/sd".
 *
 * @note
 *     Some specific FATFS APIs are not wrapped and you may have to use them directly or extend the
 *     **SDMngr** implementation if you should need them.
 *
 *
 * @file SdMngr.h
 *
 * @brief Header of SdMngr.c
 *
 * @}
 * @}
 *
 */

#include "main.h"
#include <fatfs.h>

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/
#define SdMngr_f_size(a)       f_size(a)
#define SdMngr_f_tell(a)       f_tell(a)

#define SD_MNGR_CARD_0         (0x01U)

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/
typedef enum{
    SDMNGR_CARD_STATE_READY,
    SDMNGR_CARD_STATE_NOT_INIT,
    SDMNGR_CARD_STATE_EJECTED,
    SDMNGR_CARD_STATE_ERROR,

    SDMNGR_CARD_STATE_NUMBER
}SdMngr_cardStatus_enum;

typedef struct
{
    int16_t ff_call_use_count;
    int16_t ff_call_use_max_value;
} sRamStats_t;

typedef enum{
    FS_TYPE_FATFS,
    FS_TYPE_LITTLEFS
}fs_type_t;

typedef struct
{
    bool b_is_format_requested;
    FRESULT format_status;
}sSdMngr_partiton_dyn_data;

typedef struct
{
    void *psFileSystem; //partition
    fs_type_t fs_type;
    sSdMngr_partiton_dyn_data * p_dyn_data;
}sSdMngr_partition_info_t;

typedef enum{
    RLF_OK,
    RLF_FAIL,
    RLF_WRONG_PARAM,
    RLF_WRONG_CFG,
    RLF_SDMNGR_PROBLEM,
    RLF_NOT_INIT,
    RLF_COUNT
}eSdMngr_rlf_result_t;

/**
 * @brief Rolling file configuration
 */
typedef struct
{
    uint32_t u32MaxSizeInBytes;         /**< maximum size of python output files in bytes */
    char     acNamePattern[FF_MAX_LFN]; /**< name used for template for the rolling file name */
    uint8_t  u8MarkerPos;               /**< defines the position of the marker character in the file name */
    uint8_t  u8IndexPos;                /**< defines the position of the marker character in the file name */
    uint8_t  u8FilesCount;              /**< maximum number of preserved files before starting to erase old content */
    char     cActiveMarker;             /**< a file name ending with this character is the currently active file */
    char     cInactiveMarker;           /**< file names ending with this character indicate older reports */
} sSdMngr_rlf_cfg_t;

typedef struct {
    const sSdMngr_rlf_cfg_t * psCfg;
    FIL sFileHnd;
    char acFileName[FF_MAX_LFN];
    uint8_t u8CurrentIdx;
    bool bIsFileOpened;
}sSdMngr_rlf_ctx_t;

typedef enum
{
    SD_MNGR_FATFS_SDCARD_PARTITION,
    SD_MNGR_PARTITIONS_CNT
}eSdMngr_partition_t;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/
/* No External variables declarations */

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/
/**
 * @brief Init routine for the SdMngr component
 */
void SdMngr_InitTask(void);

/**
 * @brief Get the current state of the SD card
 */
SdMngr_cardStatus_enum SdMngr_GetCardState(void);

/**
 * @brief Set flag to rquest the SD card to be reinitialise
 * @param             blocking:
 *                       + pdTRUE  - block the task until the Initialisation is complete
 *                       + pdFALSE - set a request that will be done later ( during next execution of "SdMngr_Task()" )
 * @return            uint8_t:
 *                       + pdTRUE - Successful
 *                       + dpFALSE- Fail
 * @note              Do not call from ISR
 */
bool SdMngr_RequestSdCardInit(bool blocking);

/**
 * @brief Set flag to request the SD card to be formatted
 * @param   eSdMngr_partition_t Id of the partition to be formatted.
 * @param   bool          blocking:
 *                       + pdTRUE  - block the task until the Initialisation is complete
 *                       + pdFALSE - set a request that will be done later ( during next execution of "SdMngr_Task()" )
 * @return Returns status of the partition based on file system status.
 * @note              Do not call from ISR
 */
FRESULT SdMngr_RequestPartitionFormat(eSdMngr_partition_t partition_id, bool blocking);

/**
 * @brief Set flag for detected ejecting or insertion of the SD card of the slot
 */
void SD_Card_Eject_Detected(void);

/**
 * @brief Request immediate wake up of the task (only call from ISR)
 */
void SdMngr_NotifyTaskFromISR(void);

/**
 * @brief Request immediate wake up of the task (Do not call from ISR)
 */
void SdMngr_NotifyTask(void);

/**
 * @brief Get the counter for a type of `FRESULT`
 * @param id: type of result
 *
 * @return the counter for the specific `FRESULT` ID
 */
uint16_t SdMngr_GetStatisticCounterById(FRESULT id);

/**
 * @brief Return the RAM statistics counters
 * @param pStats: pointer to the statistics counters list
 */
void SdMngr_GetRamStatisticCounters(sRamStats_t * const pStats);

/**
 * @brief Clear all the statistics counters, set them to 0
 */
void SdMngr_ClearStatisticCounters(void);

/**
 * @brief Get the volume name of a partition id.
 * @param partition_id: Id of the partition for which we need the mount point path
 * @return Returns a pointer to constant string representing the mount point
 */
const char* SdMngr_get_mnt_point_name(eSdMngr_partition_t partition_id);

/**
 * @brief Get which partition an opened file handle belongs to.
 * @param fp pointer to an opened fatfs FIL object.
 * @return Returns an enum representing the partition
 */
eSdMngr_partition_t SdMngr_get_partition_id(const FIL* fp);

FRESULT SdMngr_f_open (FIL* fp, const TCHAR* path, const BYTE mode);                           /** Open or create a file */
FRESULT SdMngr_f_close (FIL* fp);                                                              /** Close an open file object */
FRESULT SdMngr_f_read (FIL* fp, void* buff, UINT btr, UINT* br);                               /** Read data from the file */
FRESULT SdMngr_f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);                        /** Write data to the file */
FRESULT SdMngr_f_lseek (FIL* fp, FSIZE_t ofs);                                                 /** Move file pointer of the file object */
FRESULT SdMngr_f_truncate (FIL* fp);                                                           /** Truncate the file */
FRESULT SdMngr_f_sync (FIL* fp);                                                               /** Flush cached data of the writing file */
FRESULT SdMngr_f_opendir (FF_DIR* dp, const TCHAR* path);                                      /** Open a directory */
FRESULT SdMngr_f_closedir (FF_DIR* dp);                                                        /** Close an open directory */
FRESULT SdMngr_f_readdir (FF_DIR* dp, FILINFO* fno);                                           /** Read a directory item */
FRESULT SdMngr_f_findfirst (FF_DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);/** Find first file */
FRESULT SdMngr_f_findnext (FF_DIR* dp, FILINFO* fno);                                          /** Find next file */
FRESULT SdMngr_f_mkdir (const TCHAR* path);                                                    /** Create a sub directory */
FRESULT SdMngr_f_unlink (const TCHAR* path);                                                   /** Delete an existing file or directory */
FRESULT SdMngr_f_rename (const TCHAR* path_old, const TCHAR* path_new);                        /** Rename/Move a file or directory */
FRESULT SdMngr_f_stat (const TCHAR* path, FILINFO* fno);                                       /** Get file status */
FRESULT SdMngr_f_chmod (const TCHAR* path, BYTE attr, BYTE mask);                              /** Change attribute of a file/dir */
FRESULT SdMngr_f_utime (const TCHAR* path, const FILINFO* fno);                                /** Change timestamp of a file/dir */
FRESULT SdMngr_f_chdir (const TCHAR* path);                                                    /** Change current directory */
FRESULT SdMngr_f_chdrive (const TCHAR* path);                                                  /** Change current drive */
FRESULT SdMngr_f_getcwd (TCHAR* buff, UINT len);                                               /** Get current directory */
FRESULT SdMngr_f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);                     /** Get number of free clusters on the drive */
FRESULT SdMngr_f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);                       /** Get volume label */
FRESULT SdMngr_f_setlabel (const TCHAR* label);                                                /** Set volume label */
FRESULT SdMngr_f_expand (FIL* fp, FSIZE_t szf, BYTE opt);                                      /** Allocate a contiguous block to the file */
FRESULT SdMngr_f_mount (FATFS* fs, const TCHAR* path, BYTE opt);                               /** Mount/Unmount a logical drive */
FRESULT SdMngr_f_mkfs (const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);           /** Create a FAT volume */
FRESULT SdMngr_f_fdisk (BYTE pdrv, const DWORD* szt, void* work);                              /** Divide a physical drive into some partitions */
int SdMngr_f_putc (TCHAR c, FIL* fp);                                                          /** Put a character to the file */
int SdMngr_f_puts (const TCHAR* str, FIL* cp);                                                 /** Put a string to the file */
TCHAR* SdMngr_f_gets (TCHAR* buff, int len, FIL* fp);                                          /** Get a string from the file */

/** @brief Open rolling file. The context already needs to be filled in the configuration field of the context.
 *  The function is searching in existing files and opens the correct one and makes it ready for writing.
 *  @param fp_psCtx : context of the rolling file
 *  @return status of the operation
 */
FRESULT SdMngr_rlf_open(sSdMngr_rlf_ctx_t * const fp_psCtx);

/** @brief Close a rolling file
 *  @param fp_psCtx : context of the rolling file
 *  @return status of the operation
 */
FRESULT SdMngr_rlf_close(sSdMngr_rlf_ctx_t * const fp_psCtx);

/** @brief Writing a buffer to a rolling file.
 *  @param fp_psCtx : context of a rolling file
 *  @param pBuff : pointer to a buffer which has to be written in the file
 *  @param btw : Bytes to be written in the file
 *  @param bw : Written bytes after the operation
 *  @return status of the operation
 */
FRESULT SdMngr_rlf_write(sSdMngr_rlf_ctx_t * const fp_psCtx, const void* pBuff, UINT btw, UINT* bw);

#endif    /* SDMNGR_H */
