/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup sd_mng
 * @{
 *
 * @file FileManager.c
 *
 * @brief FileManager
 *
 * @}
 *
 */

#include "es_cdef.h"
#include "assertions.h"
#include "FileManager.h"
#include "FileManager_Cfg.h"
#include "es_exeh.h"
#include "SdMngr.h"
#include "libfile_stack.h"
#include "trace.h"
#include "fatfs.h"

#include <stdio.h>
#include <string.h>

/*
********************************************************************************************
* INTERNAL DEFINES
********************************************************************************************
*/
#define DEF_LOCAL_FILE_PATH_BUFFER \
    TCHAR localFilePathBuf[LOCAL_FILE_PATH_BUF_SIZE_BYTES]
#define GET_LOCAL_FILE_PATH_BUFFER localFilePathBuf

#define DIR_MARKER     ("d")
#define FILE_MARKER    ("f")
#define PATH_DELIMITER ("/")

/*
********************************************************************************************
* INTERNAL TYPES DEFINITION
********************************************************************************************
*/

/**
 * \brief User context used for dirlist callouts. Only the handler to dirlist
 * file is needed for dirlist file action callouts
 *
 */
typedef struct
{
    FIL *h_dirlist_file;
} dirlist_ctx_t;

/**
 * \brief prototype for file action handler used by the scan_files function
 * This handler will be invoked for each file found by scan_files function
 *
 * \param p_dinfo: pointer to directory info object
 * \param p_finfo: pointer to the file to handle
 * \param p_dir_path: pointer to string with the current path
 * \param p_user_ctx: context that is needed for this specific scan. This
 * is used for passing specific information needed for handling the files
 * scanned.
 */
typedef void (*p_file_action_handler_t)(FF_DIR const *const  p_dinfo,
                                        FILINFO const *const p_finfo,
                                        TCHAR const *const   p_dir_path,
                                        void const          *p_user_ctx);

/**
 * \brief struct used to keep context needed for scan_file function.
 * Everyone which is using the scan_file function need to pass such
 * variable to the function which will give information on how the
 * files found by scan_files will be processed.
 *
 */
typedef struct
{
    p_file_action_handler_t
        p_file_action_handler; // pointer to function with
                               // "p_file_action_handler_t" prototype to be
                               // called for each file found
    void *p_custom_info;       // this is place where the user can set information to
                               // be passed to the callout function
} scan_file_ctx_t;

/**
 * \brief Action handler used for making the dirlist. It is writing path and
 * name of the file properly formatted in DIRLIST file. The dirlist file handler
 * is passed by the user context data and is configured in before invoking of
 * scan_files function.
 *
 * \param p_dinfo
 * \param p_finfo
 * \param p_dir_path: this is parameter used internally by the scan_files
 * function. It shall be initialized by zero before scan_files function is
 * invoked. \param p_user_ctx
 */
static void
dirlist_file_action_handler(FF_DIR const *const  p_dinfo,
                            FILINFO const *const p_finfo,
                            TCHAR const *const   p_dir_path,
                            void const          *p_user_ctx);
/*
********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
********************************************************************************************
*/
/* No External variables definition */

/**
 * @brief Variable description
 */

/*
********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
********************************************************************************************
*/
static osMutexId_t aFileMngMutex;
static FIL         aFileHandles[FILEMANAGER_MAX_FILE_HANDLE_COUNT] = { 0 };
static inline void filemng_lock_acquire(osMutexId_t lock);
static inline void filemng_lock_release(osMutexId_t lock);

const uint32_t eFileManagerFileModeId_MASK =      eFileManagerFileModeId_READ
                                                | eFileManagerFileModeId_WRITE
                                                | eFileManagerFileModeId_OPEN_EXISTING
                                                | eFileManagerFileModeId_CREATE_NEW
                                                | eFileManagerFileModeId_CREATE_ALWAYS
                                                | eFileManagerFileModeId_OPEN_ALWAYS
                                                | eFileManagerFileModeId_OPEN_APPEND;

/**
 * \brief The function is meant to go through set of files in a folder filtered by a pattern.
 * It will scan all the folders in the input path recursively and will invoke a callout for
 * each found file and also for each empty folder.
 *
 * \param file_path : path to be scanned
 * \param pattern : pattern to be used for filtering the files
 * \param p_scan_file_ctx : context needed by scan_files function. For more infor check the
 * type scan_file_ctx_t
 * \return
 */
static FRESULT scan_files(const TCHAR *const file_path, const TCHAR *const pattern, const scan_file_ctx_t *const p_scan_file_ctx);

/*
********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
********************************************************************************************
*/
static inline bool fs_isHandleFree(const FileManagerFHnd fhnd)
{
    CRIT_ASSERT(fhnd < FILEMANAGER_MAX_FILE_HANDLE_COUNT);

    filemng_lock_acquire(aFileMngMutex);
    bool ret = (bool)(aFileHandles[fhnd].obj.fs == (FATFS *)NULL);
    filemng_lock_release(aFileMngMutex);

    return ret;
}

static bool fs_getFreeHandle(FileManagerFHnd *const pHnd)
{
    bool ret = false;

    CRIT_ASSERT(pHnd != (FileManagerFHnd *)NULL);

    filemng_lock_acquire(aFileMngMutex);

    *pHnd = FILEMANAGER_INVALID_FILE_HANDLE;

    for (uint8_t i = 0; i < CDEF_ELEMENT_COUNT(aFileHandles); i++)
    {
        if (fs_isHandleFree(i))
        {
            *pHnd = i;
            ret   = true;
            break;
        }
    }

    filemng_lock_release(aFileMngMutex);

    return ret;
}

static inline FIL *fs_getPhysHandle(const FileManagerFHnd fhnd)
{
    CRIT_ASSERT(fhnd < FILEMANAGER_MAX_FILE_HANDLE_COUNT);

    return (fhnd < FILEMANAGER_MAX_FILE_HANDLE_COUNT) ? &aFileHandles[fhnd] : NULL;
}

static uint32_t fs_calcBufChecksum(const uint8_t *const pBuf, const uint32_t u32BufSize, const uint32_t u32StartCs)
{
    uint32_t u32Res = u32StartCs;

    CRIT_ASSERT((pBuf != NULL) && (u32BufSize > (uint32_t)0));

    for (uint32_t i = 0; i < u32BufSize; i++)
    {
        u32Res += pBuf[i];
    }

    return u32Res;
}

static void fs_release_all_handles(void)
{
    filemng_lock_acquire(aFileMngMutex);

    for (uint32_t i = 0; i < CDEF_ELEMENT_COUNT(aFileHandles); i++)
    {
        fileManager_FClose(i);
    }

    memset(aFileHandles, 0, sizeof(aFileHandles));

    filemng_lock_release(aFileMngMutex);
}

static void fs_release_partition_handles(eSdMngr_partition_t partition_id)
{
    filemng_lock_acquire(aFileMngMutex);

    for (uint32_t i = 0; i < CDEF_ELEMENT_COUNT(aFileHandles); i++)
    {
        if ((NULL != aFileHandles[i].obj.fs)
            && (SdMngr_get_partition_id(&aFileHandles[i]) == partition_id))
        {
            fileManager_FClose(i);

            memset(&aFileHandles[i], 0, sizeof(aFileHandles[i]));
        }
    }

    filemng_lock_release(aFileMngMutex);
}


static inline bool fs_isHandleValid(const FileManagerFHnd fhnd)
{
    CRIT_ASSERT(fhnd < FILEMANAGER_MAX_FILE_HANDLE_COUNT);

    return (bool)(fhnd < FILEMANAGER_MAX_FILE_HANDLE_COUNT);
}

static bool fs_formatFullFilePath(const TCHAR *const pFilePath, TCHAR *const pPathBuf, const size_t pathBufSize)
{
    int32_t charsWritten = 0;

    CRIT_ASSERT(pFilePath != NULL);
    CRIT_ASSERT(pPathBuf != NULL);

    charsWritten = snprintf(pPathBuf, pathBufSize, "%s", pFilePath);

    return (charsWritten > 0) && (((size_t)charsWritten) < pathBufSize);
}

static inline void filemng_lock_acquire(osMutexId_t lock)
{
    osMutexAcquire((lock), osWaitForever);
}

static inline void filemng_lock_release(osMutexId_t lock)
{
    osMutexRelease(lock);
}

static FRESULT scan_files(const TCHAR *const file_path, const TCHAR *const pattern, const scan_file_ctx_t *const p_scan_file_ctx)
{
    static const TCHAR stack_fname[]                   = "___fstack.tmp";
    TCHAR              current_folder_path[FF_LFN_BUF] = { '\0' };
    TCHAR              tmp_stack_full_path[FF_LFN_BUF] = { '\0' };
    file_stack_ctx_t   fstack_hnd;
    FF_DIR             dinfo;
    FILINFO            finfo;
    FRESULT            res = FR_INVALID_PARAMETER;

    CRIT_ASSERT(NULL != file_path);
    CRIT_ASSERT(NULL != p_scan_file_ctx);
    CRIT_ASSERT(NULL != p_scan_file_ctx->p_file_action_handler);

    res = file_stack_open(&fstack_hnd, stack_fname, FF_LFN_BUF * sizeof(TCHAR));

    if (FR_OK != res)
    {
        return res;
    }

    res = file_stack_push(&fstack_hnd, file_path);

    while ((file_stack_get_elem_cnt(&fstack_hnd) > 0U) && (FR_OK == res))
    {
        res = file_stack_pop(&fstack_hnd, current_folder_path);

        if (FR_OK != res)
        {
            break;
        }

        current_folder_path[FF_LFN_BUF - 1] = '\0';

        // find all dirs with any name first and add them to the stack
        res = SdMngr_f_findfirst(&dinfo, &finfo, current_folder_path, "*");

        if ((FR_OK == res) && ('\0' != finfo.fname[0]))
        {
            do
            {
                bool is_path_len_valid;

                (void)strncpy(tmp_stack_full_path, current_folder_path, FF_LFN_BUF);
                tmp_stack_full_path[FF_LFN_BUF - 1] = '\0';

                size_t fname_sz   = strlen(finfo.fname);
                is_path_len_valid = (strlen(tmp_stack_full_path) + strlen(PATH_DELIMITER) + fname_sz) < FF_LFN_BUF;

                if (true == is_path_len_valid)
                {
                    if (finfo.fattrib == (finfo.fattrib & AM_DIR))
                    {
                        (void)strcat(tmp_stack_full_path, PATH_DELIMITER);
                        (void)strncat(tmp_stack_full_path, finfo.fname, fname_sz);
                        tmp_stack_full_path[FF_LFN_BUF - 1] = '\0';

                        res = file_stack_push(&fstack_hnd, tmp_stack_full_path);

                        if (FR_OK != res)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    ES_TRACE_WARN("file '%s' in folder '%s' hit the name limit size of %d bytes\n", finfo.fname, current_folder_path, FF_LFN_BUF);
                }

                res = SdMngr_f_findnext(&dinfo, &finfo);
            } while ((FR_OK == res) && ('\0' != finfo.fname[0]));
        }

        SdMngr_f_closedir(&dinfo);

        // list all files/dirs matching the pattern and add them to the dump list
        res = SdMngr_f_findfirst(&dinfo, &finfo, current_folder_path, pattern);

        if ((FR_OK == res) && ('\0' != finfo.fname[0]))
        {
            do
            {
                bool is_path_len_valid;

                (void)strncpy(tmp_stack_full_path, current_folder_path, FF_LFN_BUF);
                tmp_stack_full_path[FF_LFN_BUF - 1] = '\0';

                size_t fname_sz   = strlen(finfo.fname);
                is_path_len_valid = (strlen(tmp_stack_full_path) + strlen(PATH_DELIMITER) + fname_sz) < FF_LFN_BUF;

                // do not call the user handler for the temporary stack file because
                // it will be deleted once it is used and the file will be reported as
                // part of the FATFS iteration but will be inexistent after the function finishes
                if ((true == is_path_len_valid)
                    && (0U != strcmp(stack_fname, finfo.fname)))
                {
                    // call user action
                    (p_scan_file_ctx->p_file_action_handler)
                        ( &dinfo
                        , &finfo
                        , current_folder_path
                        , p_scan_file_ctx->p_custom_info);
                }

                res = SdMngr_f_findnext(&dinfo, &finfo);
            } while ((FR_OK == res) && ('\0' != finfo.fname[0]));
        }

        res = SdMngr_f_closedir(&dinfo);
    }

    res = file_stack_close(&fstack_hnd, true);

    return res;
}

static void dirlist_file_action_handler(FF_DIR const *const  p_dinfo,
                                        FILINFO const *const p_finfo,
                                        TCHAR const *const   p_dir_path,
                                        void const          *p_user_ctx)
{
    CRIT_ASSERT(NULL != p_dinfo);
    CRIT_ASSERT(NULL != p_finfo);
    CRIT_ASSERT(NULL != p_user_ctx);
    CRIT_ASSERT(NULL != p_dir_path);

    dirlist_ctx_t const *p_dirlist_ctx = (dirlist_ctx_t const *)p_user_ctx;

    f_printf(p_dirlist_ctx->h_dirlist_file, "%s/%s,%lu,%s,%lu\r\n",
             p_dir_path,
             p_finfo->fname,
             p_finfo->fsize,
             (p_finfo->fattrib == (p_finfo->fattrib & AM_DIR)) ? DIR_MARKER : FILE_MARKER,
             fattime_to_unix(p_finfo->fdate, p_finfo->ftime));
}
/*
********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
********************************************************************************************
*/

void fileManager_Init(void)
{
    (void)memset((void *)aFileHandles, 0x00, sizeof(aFileHandles));

    osMutexAttr_t filemng_id_attr = { "FileMngMutex", osMutexRecursive | osMutexPrioInherit, NULL, 0U };
    aFileMngMutex                 = osMutexNew(&filemng_id_attr);

    CRIT_ASSERT(aFileMngMutex);
}

eFileManagerOpResult_t fileManager_FormatPartition(const eSdMngr_partition_t partition_id)
{
    FRESULT res = FR_INVALID_PARAMETER;

    if (partition_id < SD_MNGR_PARTITIONS_CNT)
    {
        if (SDMNGR_CARD_STATE_READY != SdMngr_GetCardState())
        {
            res = FR_DISK_ERR;
        }
        else
        {
            const bool b_blocking = false;

            fs_release_partition_handles(partition_id);

            res = SdMngr_RequestPartitionFormat(partition_id, b_blocking);
        }
    }

    return res;
}

eFileManagerOpResult_t fileManager_FClose(const FileManagerFHnd fileHandle)
{
    FRESULT res = FR_INVALID_PARAMETER;

    if ((true == fs_isHandleValid(fileHandle))
        && (false == fs_isHandleFree(fileHandle)))
    {
        res = SdMngr_f_close(&aFileHandles[fileHandle]);
        if (FR_INVALID_OBJECT == res)
        {
            aFileHandles[fileHandle].obj.fs = NULL;
        }
    }

    return res;
}

eFileManagerOpResult_t fileManager_FGetCheckSum(const TCHAR *const filePath, uint32_t *const pu32Checksum)
{
    eFileManagerOpResult_t res                                       = FR_INVALID_PARAMETER;
    FileManagerFHnd        fHnd                                      = FILEMANAGER_INVALID_FILE_HANDLE;
    FIL                   *physHnd                                   = (FIL *)NULL;
    uint8_t                au8ReadBuf[FILEMANAGER_CS_BUF_SIZE_BYTES] = { 0 };
    UINT                   bytesRead                                 = (UINT)0;
    UINT                   remainingBytes                            = (UINT)0;
    DEF_LOCAL_FILE_PATH_BUFFER;

    // Validate the parameters
    if ((NULL == filePath) || (NULL == pu32Checksum))
    {
        return FR_INVALID_PARAMETER;
    }

    if (false == fs_formatFullFilePath(filePath, GET_LOCAL_FILE_PATH_BUFFER,
                                       sizeof(GET_LOCAL_FILE_PATH_BUFFER)))
    {
        return FR_INVALID_PARAMETER;
    }

    if (!fs_getFreeHandle(&fHnd))
    {
        return FR_TOO_MANY_OPEN_FILES;
    }

    // Open the file
    physHnd = fs_getPhysHandle(fHnd);
    res     = SdMngr_f_open(physHnd,
                            (const TCHAR *)GET_LOCAL_FILE_PATH_BUFFER,
                            FA_READ | FA_OPEN_EXISTING);
    if (res != FR_OK)
    {
        return res;
    }

    // Get the Checksum
    *pu32Checksum  = (uint32_t)0;
    remainingBytes = SdMngr_f_size(physHnd);
    // a non-zero value is needed to enable entering the loop
    // condition below...
    bytesRead = remainingBytes;

    while ((remainingBytes > 0) && (FR_OK == res) &&
           (bytesRead > 0))
    {
        // try to read data in chunks...
        res = SdMngr_f_read(physHnd, au8ReadBuf,
                            sizeof(au8ReadBuf), &bytesRead);

        if (FR_OK == res)
        {
            *pu32Checksum = fs_calcBufChecksum(
                au8ReadBuf, bytesRead, *pu32Checksum);

            if (remainingBytes >= bytesRead)
            {
                remainingBytes -= bytesRead;
            }
            else
            {
                // this should not happen!
                res = FR_INT_ERR;
                break;
            }
        }
    }

    SdMngr_f_close(physHnd);

    return res;
}

eFileManagerOpResult_t fileManager_FOpen(const TCHAR *const             filePath,
                                         const uint8_t mode,
                                         FileManagerFHnd *const         pFileHandle)
{
    FRESULT res = FR_INVALID_PARAMETER;
    DEF_LOCAL_FILE_PATH_BUFFER;

    if ((NULL == filePath)
        || (NULL == pFileHandle)
        || (0 != (mode & ((uint8_t)(~eFileManagerFileModeId_MASK))))
        || (false == fs_formatFullFilePath(filePath, GET_LOCAL_FILE_PATH_BUFFER, sizeof(GET_LOCAL_FILE_PATH_BUFFER))))
    {
        return FR_INVALID_PARAMETER;
    }

    if (true == fs_getFreeHandle(pFileHandle))
    {
        res = SdMngr_f_open(fs_getPhysHandle(*pFileHandle), GET_LOCAL_FILE_PATH_BUFFER, mode);
    }
    else
    {
        res = FR_TOO_MANY_OPEN_FILES;
    }

    return res;
}

eFileManagerOpResult_t fileManager_FRead(const FileManagerFHnd fileHandle,
                                         const uint32_t        u32Pos,
                                         uint8_t *const        pu8Buf,
                                         const uint32_t        u32BufSize,
                                         uint32_t *const       pu32BytesRead)
{
    FRESULT res     = FR_INVALID_PARAMETER;
    FIL    *physHnd = (FIL *)NULL;

    // Validate the parameters
    if ((NULL == pu8Buf) ||
        (NULL == pu32BytesRead) ||
        (false == fs_isHandleValid(fileHandle)) ||
        (u32BufSize == (uint32_t)0))
    {
        return FR_INVALID_PARAMETER;
    }

    // handle needs to have been opened before using this function
    if (true == fs_isHandleFree(fileHandle))
    {
        return FR_INVALID_OBJECT;
    }

    // Read the file
    *pu32BytesRead = 0U;
    physHnd        = fs_getPhysHandle(fileHandle);
    if (u32Pos <= SdMngr_f_size(physHnd))
    {
        res = SdMngr_f_lseek(physHnd, u32Pos);

        if (FR_OK == res)
        {
            res = SdMngr_f_read(physHnd, (void *)pu8Buf, (UINT)u32BufSize, (UINT *)pu32BytesRead);
        }
    }

    return res;
}

eFileManagerOpResult_t fileManager_FWrite(const FileManagerFHnd fileHandle,
                                          const uint32_t        u32Pos,
                                          const uint8_t *const  pu8Buf,
                                          const uint32_t        u32BufSize,
                                          uint32_t *const       pu32BytesWritten)
{
    FRESULT res     = FR_INVALID_PARAMETER;
    FIL    *physHnd = (FIL *)NULL;

    // Validate input parameters
    if ((NULL == pu8Buf) ||
        (NULL == pu32BytesWritten) ||
        (false == fs_isHandleValid(fileHandle)) ||
        (u32BufSize == (uint32_t)0))
    {
        return FR_INVALID_PARAMETER;
    }
    // handle needs to have been opened before using this function
    if (fs_isHandleFree(fileHandle))
    {
        return FR_INVALID_OBJECT;
    }

    // Write the file
    physHnd = fs_getPhysHandle(fileHandle);
    if (u32Pos <= SdMngr_f_size(physHnd))
    {
        res = SdMngr_f_lseek(physHnd, u32Pos);

        if (FR_OK == res)
        {
            res = SdMngr_f_write(physHnd, (const void *)pu8Buf, (UINT)u32BufSize, (UINT *)pu32BytesWritten);

            if (FR_OK == res)
            {
                res = SdMngr_f_sync(physHnd);
            }
        }
    }

    return res;
}

eFileManagerOpResult_t fileManager_FAppend(const FileManagerFHnd fileHandle,
                                           const uint8_t *const  pu8Buf,
                                           const uint32_t        u32BufSize,
                                           uint32_t *const       pu32BytesWritten)
{
    FRESULT res     = FR_INVALID_PARAMETER;
    FIL    *physHnd = (FIL *)NULL;

    if ((NULL == pu8Buf) ||
        (NULL == pu32BytesWritten) ||
        (false == fs_isHandleValid(fileHandle)) ||
        (u32BufSize == (uint32_t)0))
    {
        return FR_INVALID_PARAMETER;
    }

    // handle needs to have been opened before using this function
    if (true == fs_isHandleFree(fileHandle))
    {
        return FR_INVALID_OBJECT;
    }
    // Write the file
    physHnd = fs_getPhysHandle(fileHandle);
    res     = SdMngr_f_write(physHnd, (const void *)pu8Buf, (UINT)u32BufSize, (UINT *)pu32BytesWritten);

    if (res == FR_OK)
    {
        res = SdMngr_f_sync(physHnd);
    }

    return res;
}

eFileManagerOpResult_t fileManager_Rename(const TCHAR *const oldPath, const TCHAR *const newPath)
{
    FRESULT res = FR_INVALID_PARAMETER;
    DEF_LOCAL_FILE_PATH_BUFFER;
    TCHAR newFilePathBuf[LOCAL_FILE_PATH_BUF_SIZE_BYTES];

    if ((NULL == oldPath) || (NULL == newPath))
    {
        return FR_INVALID_PARAMETER;
    }

    if ((true == fs_formatFullFilePath(oldPath, GET_LOCAL_FILE_PATH_BUFFER, sizeof(GET_LOCAL_FILE_PATH_BUFFER)))
        && (true == fs_formatFullFilePath(newPath, newFilePathBuf, sizeof(newFilePathBuf))))
    {
        res = SdMngr_f_rename(GET_LOCAL_FILE_PATH_BUFFER, newFilePathBuf);
    }

    return res;
}

eFileManagerOpResult_t fileManager_Delete(const TCHAR *const filePath)
{
    FRESULT res = FR_INVALID_PARAMETER;
    DEF_LOCAL_FILE_PATH_BUFFER;

    if (NULL == filePath)
    {
        return FR_INVALID_PARAMETER;
    }
    if (true == fs_formatFullFilePath(filePath, GET_LOCAL_FILE_PATH_BUFFER,
                                      sizeof(GET_LOCAL_FILE_PATH_BUFFER)))
    {
        res = SdMngr_f_unlink(GET_LOCAL_FILE_PATH_BUFFER);
    }

    return res;
}

eFileManagerOpResult_t fileManager_FDumpDirListToFile(const TCHAR *const filePath,
                                                      const TCHAR *const pattern)
{

    FRESULT res = FR_INVALID_PARAMETER;
    FIL     physHnd;
    DEF_LOCAL_FILE_PATH_BUFFER;

    // Validate parameters
    if ((NULL == filePath)
        || (NULL == pattern)
        || (false == fs_formatFullFilePath(filePath, GET_LOCAL_FILE_PATH_BUFFER, sizeof(GET_LOCAL_FILE_PATH_BUFFER))))
    {
        return FR_INVALID_PARAMETER;
    }

    // Open the dump file
    res = SdMngr_f_open(&physHnd, GET_LOCAL_FILE_PATH_BUFFER, FA_WRITE | FA_CREATE_ALWAYS);

    // Start dump directory list
    if (FR_OK == res)
    {
        f_printf(&physHnd, "file_name,size(in bytes),attributes,timestamp\r\n");

        for (uint8_t p_id = 0; p_id < (uint8_t)SD_MNGR_PARTITIONS_CNT; p_id++)
        {
            char const *p_mnt_name = SdMngr_get_mnt_point_name(p_id);

            dirlist_ctx_t dirlist_ctx = { .h_dirlist_file = &physHnd };

            scan_file_ctx_t scan_file_ctx = { .p_custom_info = (void *)&dirlist_ctx,
                                              .p_file_action_handler = &dirlist_file_action_handler };

            if (NULL != p_mnt_name)
            {
                res = scan_files(p_mnt_name, pattern, &scan_file_ctx);
            }
        }

        (void)SdMngr_f_close(&physHnd);
    }

    return res;
}

uint32_t fileManager_getOpenHandlesCount(void)
{
    uint32_t openCntr = 0;

    for (uint32_t i = 0; i < CDEF_ELEMENT_COUNT(aFileHandles); i++)
    {
        if (false == fs_isHandleFree(i))
        {
            ++openCntr;
        }
    }

    return openCntr;
}

eFileManagerOpResult_t fileManager_FGetSize(const TCHAR *const filePath, uint32_t *const pu32Size)
{
    FRESULT res = FR_INVALID_PARAMETER;
    FILINFO fi;
    DEF_LOCAL_FILE_PATH_BUFFER;

    if ((NULL == filePath) || (NULL == pu32Size))
    {
        return FR_INVALID_PARAMETER;
    }
    if (true == fs_formatFullFilePath(filePath, GET_LOCAL_FILE_PATH_BUFFER,
                                      sizeof(GET_LOCAL_FILE_PATH_BUFFER)))
    {
        res = SdMngr_f_stat(GET_LOCAL_FILE_PATH_BUFFER, &fi);

        if (FR_OK == res)
        {
            *pu32Size = fi.fsize;
        }
    }

    return res;
}

eFileManagerOpResult_t fileManager_FMakeDir(const TCHAR *const directoryPath)
{
    FRESULT res = FR_INVALID_PARAMETER;
    DEF_LOCAL_FILE_PATH_BUFFER;

    if (NULL == directoryPath)
    {
        return FR_INVALID_PARAMETER;
    }
    if (true == fs_formatFullFilePath(directoryPath,
                                      GET_LOCAL_FILE_PATH_BUFFER,
                                      sizeof(GET_LOCAL_FILE_PATH_BUFFER)))
    {
        res = SdMngr_f_mkdir(GET_LOCAL_FILE_PATH_BUFFER);
    }

    return res;
}

bool fileManager_sd_reinit(const bool blocking)
{
    fs_release_all_handles();

    return SdMngr_RequestSdCardInit(blocking);
}
