/*!
********************************************************************************************
* @file FP_FileManagerProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface FileManager v1.2
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __FP_FILEMANAGERPROTOCOLTYPES_H__
#define __FP_FILEMANAGERPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER ((uint16_t) (0x0000000F))

#define FILEMANAGER_FILEOPEN_FUNC_ID ((funcIdType_t) 0x00000000)
#define FILEMANAGER_FILECLOSE_FUNC_ID ((funcIdType_t) 0x00000001)
#define FILEMANAGER_FILEREAD_FUNC_ID ((funcIdType_t) 0x00000002)
#define FILEMANAGER_FILEWRITE_FUNC_ID ((funcIdType_t) 0x00000003)
#define FILEMANAGER_RENAME_FUNC_ID ((funcIdType_t) 0x0000000F)
#define FILEMANAGER_DELETE_FUNC_ID ((funcIdType_t) 0x00000004)
#define FILEMANAGER_FILEGETSIZE_FUNC_ID ((funcIdType_t) 0x00000005)
#define FILEMANAGER_FILEGETCHECKSUM_FUNC_ID ((funcIdType_t) 0x00000006)
#define FILEMANAGER_FILEGETOPENEDHANDLESCOUNT_FUNC_ID ((funcIdType_t) 0x00000007)
#define FILEMANAGER_FORMATPARTITION_FUNC_ID ((funcIdType_t) 0x00000008)
#define FILEMANAGER_FILEDUMPDIRLISTTOFILE_FUNC_ID ((funcIdType_t) 0x00000009)
#define FILEMANAGER_GETSTATISTICS_FUNC_ID ((funcIdType_t) 0x0000000A)
#define FILEMANAGER_CLEARSTATISTICS_FUNC_ID ((funcIdType_t) 0x0000000B)
#define FILEMANAGER_SDREINIT_FUNC_ID ((funcIdType_t) 0x0000000C)
#define FILEMANAGER_DIRMAKE_FUNC_ID ((funcIdType_t) 0x0000000D)
#define FILEMANAGER_GET_SD_CARD_STATUS_FUNC_ID ((funcIdType_t) 0x0000000E)
#define FILEMANAGER_FILEOPEN_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define FILEMANAGER_FILECLOSE_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define FILEMANAGER_FILEREAD_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define FILEMANAGER_FILEWRITE_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define FILEMANAGER_RENAME_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define FILEMANAGER_DELETE_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define FILEMANAGER_FILEGETSIZE_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define FILEMANAGER_FILEGETCHECKSUM_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define FILEMANAGER_FILEGETOPENEDHANDLESCOUNT_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define FILEMANAGER_FORMATPARTITION_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define FILEMANAGER_FILEDUMPDIRLISTTOFILE_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define FILEMANAGER_GETSTATISTICS_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define FILEMANAGER_CLEARSTATISTICS_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define FILEMANAGER_SDREINIT_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define FILEMANAGER_DIRMAKE_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define FILEMANAGER_GET_SD_CARD_STATUS_FUNCRESP_ID ((funcIdType_t) 0x0000000E)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    The error codes here are mapped to the FATFS implementation (http://elm-chan.org/fsw/ff/doc/rc.html)
*/
#define FILEMANAGER_FMANOPRESULT_OK ((uint8_t) 0)
#define FILEMANAGER_FMANOPRESULT_DISK_ERR ((uint8_t) 1)
#define FILEMANAGER_FMANOPRESULT_INT_ERR ((uint8_t) 2)
#define FILEMANAGER_FMANOPRESULT_NOT_READY ((uint8_t) 3)
#define FILEMANAGER_FMANOPRESULT_NO_FILE ((uint8_t) 4)
#define FILEMANAGER_FMANOPRESULT_NO_PATH ((uint8_t) 5)
#define FILEMANAGER_FMANOPRESULT_INVALID_NAME ((uint8_t) 6)
#define FILEMANAGER_FMANOPRESULT_DENIED ((uint8_t) 7)
#define FILEMANAGER_FMANOPRESULT_EXIST ((uint8_t) 8)
#define FILEMANAGER_FMANOPRESULT_INVALID_OBJECT ((uint8_t) 9)
#define FILEMANAGER_FMANOPRESULT_WRITE_PROTECTED ((uint8_t) 10)
#define FILEMANAGER_FMANOPRESULT_INVALID_DRIVE ((uint8_t) 11)
#define FILEMANAGER_FMANOPRESULT_NOT_ENABLED ((uint8_t) 12)
#define FILEMANAGER_FMANOPRESULT_NO_FILESYSTEM ((uint8_t) 13)
#define FILEMANAGER_FMANOPRESULT_MKFS_ABORTED ((uint8_t) 14)
#define FILEMANAGER_FMANOPRESULT_TIMEOUT ((uint8_t) 15)
#define FILEMANAGER_FMANOPRESULT_LOCKED ((uint8_t) 16)
#define FILEMANAGER_FMANOPRESULT_NOT_ENOUGH_CORE ((uint8_t) 17)
#define FILEMANAGER_FMANOPRESULT_TOO_MANY_OPEN_FILES ((uint8_t) 18)
#define FILEMANAGER_FMANOPRESULT_INVALID_PARAMETER ((uint8_t) 19)
#define FILEMANAGER_FMANOPRESULT_MAX_CNT  ((uint8_t) 20)
typedef uint8_t FILEMANAGER_FManOpResult_t;

/*
    The enumeration provides all possible partitions supported in the OBC
*/
#define FILEMANAGER_FMANPARTITIONS_SD_PARTITION ((uint8_t) 0)
#define FILEMANAGER_FMANPARTITIONS_MAX_CNT  ((uint8_t) 1)
typedef uint8_t FILEMANAGER_FManPartitions_t;

/*
    The enumeration provides the different flags which can be used with the fileOpen method. Please note that
                          those are bit-mask values which implies that they can be combined by a logical OR operation, e.g.
                          READ | WRITE => "r+" (POSIX)
*/
#define FILEMANAGER_FMANFILEMODEID_OPEN_EXISTING ((uint8_t) 0)
#define FILEMANAGER_FMANFILEMODEID_READ ((uint8_t) 1)
#define FILEMANAGER_FMANFILEMODEID_WRITE ((uint8_t) 2)
#define FILEMANAGER_FMANFILEMODEID_CREATE_NEW ((uint8_t) 4)
#define FILEMANAGER_FMANFILEMODEID_CREATE_ALWAYS ((uint8_t) 8)
#define FILEMANAGER_FMANFILEMODEID_OPEN_ALWAYS ((uint8_t) 16)
#define FILEMANAGER_FMANFILEMODEID_OPEN_APPEND ((uint8_t) 48)
#define FILEMANAGER_FMANFILEMODEID_MAX_CNT  ((uint8_t) 49)
typedef uint8_t FILEMANAGER_FManFileModeId_t;

/*
    This type represents a unique identifier of an opened file returned by the fileOpen operation. Later this identifier is used with
                          the rest of the file APIs and it gets invalidated when the fileClose operation is executed with this handle.
*/
typedef uint32_t FILEMANAGER_FManFileHandle_t;

/*
    This type describes all internally tracked error counters related to file operations.
*/
typedef struct {
    uint16_t u16DISK_ERR;
    uint16_t u16INT_ERR;
    uint16_t u16NOT_READY;
    uint16_t u16NO_FILE;
    uint16_t u16NO_PATH;
    uint16_t u16INVALID_NAME;
    uint16_t u16DENIED;
    uint16_t u16EXIST;
    uint16_t u16INVALID_OBJECT;
    uint16_t u16WRITE_PROTECTED;
    uint16_t u16INVALID_DRIVE;
    uint16_t u16NOT_ENABLED;
    uint16_t u16NO_FILESYSTEM;
    uint16_t u16MKFS_ABORTED;
    uint16_t u16TIMEOUT;
    uint16_t u16LOCKED;
    uint16_t u16NOT_ENOUGH_CORE;
    uint16_t u16TOO_MANY_OPEN_FILES;
    uint16_t u16INVALID_PARAMETER;
} PACKED_STRUCT FILEMANAGER_ErrorCounters_t;

/*
    This structure contains statistical information about the operation of the file subsystem of the device. Its main
                          purpose is to ease debugging and finding faults with file operations.
*/
typedef struct {
    FILEMANAGER_ErrorCounters_t sErrCounters;
    int16_t i16NestCount;
    int16_t i16MaxNestCount;
} PACKED_STRUCT FILEMANAGER_Statistics_t;

/*
    Return the status of the SD card in the OBC.
*/
#define FILEMANAGER_SDCARDSTATUS_READY ((uint8_t) 0)
#define FILEMANAGER_SDCARDSTATUS_NOT_INIT ((uint8_t) 1)
#define FILEMANAGER_SDCARDSTATUS_EJECTED ((uint8_t) 2)
#define FILEMANAGER_SDCARDSTATUS_ERROR ((uint8_t) 3)
#define FILEMANAGER_SDCARDSTATUS_MAX_CNT  ((uint8_t) 4)
typedef uint8_t FILEMANAGER_SDCardStatus_t;


typedef struct {
    uint8_t u8FilePathSize;
    char strFilePath[47];
    uint8_t u8Mode;
} PACKED_STRUCT FileManagerfileOpenRequestData_t;

typedef struct {
    FILEMANAGER_FManFileHandle_t tHandle;
} PACKED_STRUCT FileManagerfileCloseRequestData_t;

typedef struct {
    FILEMANAGER_FManFileHandle_t tHandle;
    uint32_t u32Pos;
    uint32_t u32BytesToRead;
} PACKED_STRUCT FileManagerfileReadRequestData_t;

typedef struct {
    FILEMANAGER_FManFileHandle_t tHandle;
    uint32_t u32Pos;
    uint8_t u8DataSize;
    uint8_t au8Data[230];
} PACKED_STRUCT FileManagerfileWriteRequestData_t;

typedef struct {
    uint8_t u8OldPathSize;
    char strOldPath[47];
    uint8_t u8NewPathSize;
    char strNewPath[47];
} PACKED_STRUCT FileManagerRenameRequestData_t;

typedef struct {
    uint8_t u8PathSize;
    char strPath[47];
} PACKED_STRUCT FileManagerDeleteRequestData_t;

typedef struct {
    uint8_t u8FilePathSize;
    char strFilePath[47];
} PACKED_STRUCT FileManagerfileGetSizeRequestData_t;

typedef struct {
    uint8_t u8FilePathSize;
    char strFilePath[47];
} PACKED_STRUCT FileManagerfileGetCheckSumRequestData_t;

typedef struct {
    FILEMANAGER_FManPartitions_t ePartitionId;
} PACKED_STRUCT FileManagerformatPartitionRequestData_t;

typedef struct {
    uint8_t u8FilePathSize;
    char strFilePath[47];
    uint8_t u8PatternSize;
    char strPattern[47];
} PACKED_STRUCT FileManagerfileDumpDirListToFileRequestData_t;

typedef struct {
    bool bSynchronousCall;
} PACKED_STRUCT FileManagersdReinitRequestData_t;

typedef struct {
    uint8_t u8DirNameSize;
    char strDirName[47];
} PACKED_STRUCT FileManagerdirMakeRequestData_t;


typedef struct {
    FILEMANAGER_FManFileHandle_t tHandle;
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerfileOpenResponseData_t;

typedef struct {
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerfileCloseResponseData_t;

typedef struct {
    uint8_t u8DataSize;
    uint8_t au8Data[230];
    uint32_t u32BytesRead;
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerfileReadResponseData_t;

typedef struct {
    uint32_t u32BytesWritten;
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerfileWriteResponseData_t;

typedef struct {
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerRenameResponseData_t;

typedef struct {
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerDeleteResponseData_t;

typedef struct {
    uint32_t u32FSize;
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerfileGetSizeResponseData_t;

typedef struct {
    uint32_t u32Cs;
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerfileGetCheckSumResponseData_t;

typedef struct {
    uint32_t u32HandlesCount;
} PACKED_STRUCT FileManagerfileGetOpenedHandlesCountResponseData_t;

typedef struct {
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerformatPartitionResponseData_t;

typedef struct {
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerfileDumpDirListToFileResponseData_t;

typedef struct {
    FILEMANAGER_Statistics_t sStats;
} PACKED_STRUCT FileManagergetStatisticsResponseData_t;

typedef struct {
    bool bStatus;
} PACKED_STRUCT FileManagersdReinitResponseData_t;

typedef struct {
    FILEMANAGER_FManOpResult_t eRes;
} PACKED_STRUCT FileManagerdirMakeResponseData_t;

typedef struct {
    FILEMANAGER_SDCardStatus_t eStatus;
} PACKED_STRUCT FileManagerget_sd_card_statusResponseData_t;


#endif  // #ifndef __FP_FILEMANAGERPROTOCOLTYPES_H__

