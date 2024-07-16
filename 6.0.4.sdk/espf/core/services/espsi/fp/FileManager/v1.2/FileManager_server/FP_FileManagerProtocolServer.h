/*!
********************************************************************************************
* @file FP_FileManagerProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_FILEMANAGERPROTOCOLSERVER_H__
#define __FP_FILEMANAGERPROTOCOLSERVER_H__

#include "FP_FileManagerProtocolTypes.h"

typedef void (*pfFileManager_fileOpenRequestHandler_t)(ReqContext_t *ctx, FileManagerfileOpenRequestData_t *pRequestData);
typedef void (*pfFileManager_fileCloseRequestHandler_t)(ReqContext_t *ctx, FileManagerfileCloseRequestData_t *pRequestData);
typedef void (*pfFileManager_fileReadRequestHandler_t)(ReqContext_t *ctx, FileManagerfileReadRequestData_t *pRequestData);
typedef void (*pfFileManager_fileWriteRequestHandler_t)(ReqContext_t *ctx, FileManagerfileWriteRequestData_t *pRequestData);
typedef void (*pfFileManager_RenameRequestHandler_t)(ReqContext_t *ctx, FileManagerRenameRequestData_t *pRequestData);
typedef void (*pfFileManager_DeleteRequestHandler_t)(ReqContext_t *ctx, FileManagerDeleteRequestData_t *pRequestData);
typedef void (*pfFileManager_fileGetSizeRequestHandler_t)(ReqContext_t *ctx, FileManagerfileGetSizeRequestData_t *pRequestData);
typedef void (*pfFileManager_fileGetCheckSumRequestHandler_t)(ReqContext_t *ctx, FileManagerfileGetCheckSumRequestData_t *pRequestData);
typedef void (*pfFileManager_fileGetOpenedHandlesCountRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfFileManager_formatPartitionRequestHandler_t)(ReqContext_t *ctx, FileManagerformatPartitionRequestData_t *pRequestData);
typedef void (*pfFileManager_fileDumpDirListToFileRequestHandler_t)(ReqContext_t *ctx, FileManagerfileDumpDirListToFileRequestData_t *pRequestData);
typedef void (*pfFileManager_getStatisticsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfFileManager_clearStatisticsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfFileManager_sdReinitRequestHandler_t)(ReqContext_t *ctx, FileManagersdReinitRequestData_t *pRequestData);
typedef void (*pfFileManager_dirMakeRequestHandler_t)(ReqContext_t *ctx, FileManagerdirMakeRequestData_t *pRequestData);
typedef void (*pfFileManager_get_sd_card_statusRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfFileManager_fileOpenRequestHandler_t FileManager_fileOpenRequestHandler;
    pfFileManager_fileCloseRequestHandler_t FileManager_fileCloseRequestHandler;
    pfFileManager_fileReadRequestHandler_t FileManager_fileReadRequestHandler;
    pfFileManager_fileWriteRequestHandler_t FileManager_fileWriteRequestHandler;
    pfFileManager_RenameRequestHandler_t FileManager_RenameRequestHandler;
    pfFileManager_DeleteRequestHandler_t FileManager_DeleteRequestHandler;
    pfFileManager_fileGetSizeRequestHandler_t FileManager_fileGetSizeRequestHandler;
    pfFileManager_fileGetCheckSumRequestHandler_t FileManager_fileGetCheckSumRequestHandler;
    pfFileManager_fileGetOpenedHandlesCountRequestHandler_t FileManager_fileGetOpenedHandlesCountRequestHandler;
    pfFileManager_formatPartitionRequestHandler_t FileManager_formatPartitionRequestHandler;
    pfFileManager_fileDumpDirListToFileRequestHandler_t FileManager_fileDumpDirListToFileRequestHandler;
    pfFileManager_getStatisticsRequestHandler_t FileManager_getStatisticsRequestHandler;
    pfFileManager_clearStatisticsRequestHandler_t FileManager_clearStatisticsRequestHandler;
    pfFileManager_sdReinitRequestHandler_t FileManager_sdReinitRequestHandler;
    pfFileManager_dirMakeRequestHandler_t FileManager_dirMakeRequestHandler;
    pfFileManager_get_sd_card_statusRequestHandler_t FileManager_get_sd_card_statusRequestHandler;
} FileManager_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_FileManagerProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void FileManager_registerServerApi(FileManager_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_FileManagerProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t FileManager_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes FileManager_fileOpenResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManFileHandle_t tHandle,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_fileCloseResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_fileReadResp(
                RespContext_t* ctx,
                const uint8_t * const au8Data,
                const uint8_t u8DataSize,
                const uint32_t u32BytesRead,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_fileWriteResp(
                RespContext_t* ctx,
                const uint32_t u32BytesWritten,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_RenameResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_DeleteResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_fileGetSizeResp(
                RespContext_t* ctx,
                const uint32_t u32FSize,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_fileGetCheckSumResp(
                RespContext_t* ctx,
                const uint32_t u32Cs,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_fileGetOpenedHandlesCountResp(
                RespContext_t* ctx,
                const uint32_t u32HandlesCount
);

ESSATMAC_ErrCodes FileManager_formatPartitionResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_fileDumpDirListToFileResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_getStatisticsResp(
                RespContext_t* ctx,
                const FILEMANAGER_Statistics_t * const sStats
);

ESSATMAC_ErrCodes FileManager_clearStatisticsResp(
                RespContext_t* ctx);

ESSATMAC_ErrCodes FileManager_sdReinitResp(
                RespContext_t* ctx,
                const bool bStatus
);

ESSATMAC_ErrCodes FileManager_dirMakeResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
);

ESSATMAC_ErrCodes FileManager_get_sd_card_statusResp(
                RespContext_t* ctx,
                const FILEMANAGER_SDCardStatus_t eStatus
);


#endif  // #ifndef __FP_FILEMANAGERPROTOCOLSERVER_H__
