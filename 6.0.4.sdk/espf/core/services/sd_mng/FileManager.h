/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

/**
 * @addtogroup sd_mng
 * @{
 *
 * @file FileManager.h
 *
 * @brief Main header for the FileManager implementation
 *
 * @}
 *
 */
#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "es_cdef.h"
#include "SdMngr.h"
#include "FileManager_Cfg.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/
#define FILEMANAGER_INVALID_FILE_HANDLE (FILEMANAGER_MAX_FILE_HANDLE_COUNT)

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/
typedef enum
{
    eFileManagerFileModeId_READ          = FA_READ,
    eFileManagerFileModeId_WRITE         = FA_WRITE,
    eFileManagerFileModeId_OPEN_EXISTING = FA_OPEN_EXISTING,
    eFileManagerFileModeId_CREATE_NEW    = FA_CREATE_NEW,
    eFileManagerFileModeId_CREATE_ALWAYS = FA_CREATE_ALWAYS,
    eFileManagerFileModeId_OPEN_ALWAYS   = FA_OPEN_ALWAYS,
    eFileManagerFileModeId_OPEN_APPEND   = FA_OPEN_APPEND,
} eFileManagerFileModeId_t;

typedef FRESULT eFileManagerOpResult_t;

typedef uint32_t FileManagerFHnd;

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
 * @brief File Manager initialisation routine
 */
void fileManager_Init(void);

/**
 * @brief Open a file
 * @param filePath: pointer to the filepath string
 * @param mode: OR'd combination of operating mode eFileManagerFileModeId_t
 * @param pFileHandle: handler to the open file (if successful)
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FOpen(const TCHAR *const filePath,
                                            const uint8_t mode,
                                            FileManagerFHnd *const pFileHandle);

/**
 * @brief Closes an opened file and invalidates its handle
 * @param      fileHandle: valid file handle acquired via `fileManager_FOpen`
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FClose(const FileManagerFHnd fileHandle);

/**
 * @brief Read from a file a certain number of bytes
 * @param fileHandle: valid file handle acquired via `fileManager_FOpen`
 * @param u32Pos: where to start reading the bytes
 * @param pu8Buf: buffer to store the read information
 * @param u32BufSize: size of the buffer and number of bytes to read
 * @param pu32BytesRead: pointer to contain the number of bytes that are actually read
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FRead(const FileManagerFHnd fileHandle,
                                            const uint32_t        u32Pos,
                                            uint8_t *const        pu8Buf,
                                            const uint32_t        u32BufSize,
                                            uint32_t *const       pu32BytesRead);

/**
 * @brief Write to a file a certain number of bytes
 * @param fileHandle: valid file handle acquired via `fileManager_FOpen`
 * @param u32Pos: where to start writing the bytes
 * @param pu8Buf: buffer with the information to write
 * @param u32BufSize: size of the buffer and number of bytes to write
 * @param pu32BytesWritten: pointer to contain the number of bytes that are actually written
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FWrite(const FileManagerFHnd fileHandle,
                                            const uint32_t        u32Pos,
                                            const uint8_t *const  pu8Buf,
                                            const uint32_t        u32BufSize,
                                            uint32_t *const       pu32BytesWritten);

/**
 * @brief Append to a file a certain number of bytes
 * @param fileHandle: valid file handle acquired via `fileManager_FOpen`
 * @param pu8Buf: buffer with the information to write
 * @param u32BufSize: size of the buffer and number of bytes to write
 * @param pu32BytesWritten: pointer to contain the number of bytes that are actually written
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FAppend(const FileManagerFHnd fileHandle,
                                            const uint8_t *const  pu8Buf,
                                            const uint32_t        u32BufSize,
                                            uint32_t *const       pu32BytesWritten);

/**
 * @brief Rename a file or directory in file system. Old and new name must be in same partition.
 * @param oldPath Full path to the current name of the file. It must exist.
 * @param filePath: Full path to the new name of the file. Intermediate directories must exist.
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_Rename(const TCHAR *const oldPath, const TCHAR *const newPath);

/**
 * @brief Delete a file or directory from file system
 * @param filePath: path to the file or the directory
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_Delete(const TCHAR *const filePath);

/**
 * @brief Get the size of a file from a volume
 * @param volId: volume that contains the file
 * @param filePath: path to the file
 * @param pu32Size: pointer to contain the returned size value
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FGetSize(const TCHAR *const filePath,
                                            uint32_t *const    pu32Size);

/**
 * @brief Get the list of files from a directory that follow certain pattern and copy it in a file
 * @param volId: volume containing the directory
 * @param filePath: path to the directory
 * @param pattern: name matching pattern
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FDumpDirListToFile(const TCHAR *const filePath,
                                                        const TCHAR *const pattern);

/**
 * @brief Calculate the checksum of a file
 * @param volId: volume containing the directory
 * @param filePath: path to the file
 * @param pu32Checksum: pointer to contain the returned checksum value
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FGetCheckSum(const TCHAR *const filePath,
                                                uint32_t *const    pu32Checksum);

/**
 * @brief The operation is used to format a storage volume given its unique identifier in the
 *        system. For a list of identifiers valid for a particular device, refer to the device
 *        specification.
 *        If the partition_id is valid and the SD card is ready, then the reserved file handles
 *        for the partition are reset (ie the open files are closed) before the format operation starts.
 * @param partition_id: ID of the partition to be formated
 *
 * @return     See eFileManagerOpResult_t return type for details on error code values
 */
eFileManagerOpResult_t fileManager_FormatPartition(const eSdMngr_partition_t partition_id);

/**
 * @brief Retrieve the number of open handles
 *
 * @return number of open handles from the handles pool
 */
uint32_t fileManager_getOpenHandlesCount(void);

/**
 * @fn eFileManagerOpResult_t fileManager_FMakeDir(const TCHAR* const)
 * @brief Creates a new folder with the name provided.
 *
 * @param directoryPath name of the directory to be created. It shall be full name including the partition. Ex: "/sd/NewFolderName"
 * @return result of the operation
 */
eFileManagerOpResult_t fileManager_FMakeDir(const TCHAR *const directoryPath);

/**
 * @brief           Force a reinitialization of the SD Card.
 *                  Resets the reserved file handles regardless if reinit is successfull or not.
 * @param blocking  If `true` wait for the reinitialization to finish.
 * @retval false    reinit has failed, else reinit either failed or did not complete within timeout.
 * @retval true     reinit started, but may not have completed, init is completed and card is ready to use.
 */
bool fileManager_sd_reinit(const bool blocking);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif /* FILE_MANAGER_H */
