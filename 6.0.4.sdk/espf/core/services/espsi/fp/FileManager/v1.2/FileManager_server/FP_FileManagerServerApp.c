/*!
********************************************************************************************
* @file FP_FileManagerServerApp.c
* @brief ServerApp implementation template generator
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

#include "FP_FileManagerProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "FileManager.h"
#include "SdMngr.h"
#include "debug.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void FileManager_fileOpenRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerfileOpenRequestData_t* pRequestData);

static void FileManager_fileCloseRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerfileCloseRequestData_t* pRequestData);

static void FileManager_fileReadRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerfileReadRequestData_t* pRequestData);

static void FileManager_fileWriteRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerfileWriteRequestData_t* pRequestData);

static void FileManager_RenameRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerRenameRequestData_t* pRequestData);

static void FileManager_DeleteRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerDeleteRequestData_t* pRequestData);

static void FileManager_fileGetSizeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerfileGetSizeRequestData_t* pRequestData);

static void FileManager_fileGetCheckSumRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerfileGetCheckSumRequestData_t* pRequestData);

static void FileManager_fileGetOpenedHandlesCountRequestHandlerImpl(ReqContext_t* pReqCtx);

static void FileManager_formatPartitionRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerformatPartitionRequestData_t* pRequestData);

static void FileManager_fileDumpDirListToFileRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerfileDumpDirListToFileRequestData_t* pRequestData);

static void FileManager_getStatisticsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void FileManager_clearStatisticsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void FileManager_sdReinitRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagersdReinitRequestData_t* pRequestData);

static void FileManager_dirMakeRequestHandlerImpl(ReqContext_t* pReqCtx,
            const FileManagerdirMakeRequestData_t* pRequestData);

static void FileManager_get_sd_card_statusRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static FileManager_ServerApi_t FileManagerServerApiCtx =
{
  .FileManager_fileOpenRequestHandler = (pfFileManager_fileOpenRequestHandler_t) FileManager_fileOpenRequestHandlerImpl,
  .FileManager_fileCloseRequestHandler = (pfFileManager_fileCloseRequestHandler_t) FileManager_fileCloseRequestHandlerImpl,
  .FileManager_fileReadRequestHandler = (pfFileManager_fileReadRequestHandler_t) FileManager_fileReadRequestHandlerImpl,
  .FileManager_fileWriteRequestHandler = (pfFileManager_fileWriteRequestHandler_t) FileManager_fileWriteRequestHandlerImpl,
  .FileManager_RenameRequestHandler = (pfFileManager_RenameRequestHandler_t) FileManager_RenameRequestHandlerImpl,
  .FileManager_DeleteRequestHandler = (pfFileManager_DeleteRequestHandler_t) FileManager_DeleteRequestHandlerImpl,
  .FileManager_fileGetSizeRequestHandler = (pfFileManager_fileGetSizeRequestHandler_t) FileManager_fileGetSizeRequestHandlerImpl,
  .FileManager_fileGetCheckSumRequestHandler = (pfFileManager_fileGetCheckSumRequestHandler_t) FileManager_fileGetCheckSumRequestHandlerImpl,
  .FileManager_fileGetOpenedHandlesCountRequestHandler = (pfFileManager_fileGetOpenedHandlesCountRequestHandler_t) FileManager_fileGetOpenedHandlesCountRequestHandlerImpl,
  .FileManager_formatPartitionRequestHandler = (pfFileManager_formatPartitionRequestHandler_t) FileManager_formatPartitionRequestHandlerImpl,
  .FileManager_fileDumpDirListToFileRequestHandler = (pfFileManager_fileDumpDirListToFileRequestHandler_t) FileManager_fileDumpDirListToFileRequestHandlerImpl,
  .FileManager_getStatisticsRequestHandler = (pfFileManager_getStatisticsRequestHandler_t) FileManager_getStatisticsRequestHandlerImpl,
  .FileManager_clearStatisticsRequestHandler = (pfFileManager_clearStatisticsRequestHandler_t) FileManager_clearStatisticsRequestHandlerImpl,
  .FileManager_sdReinitRequestHandler = (pfFileManager_sdReinitRequestHandler_t) FileManager_sdReinitRequestHandlerImpl,
  .FileManager_dirMakeRequestHandler = (pfFileManager_dirMakeRequestHandler_t) FileManager_dirMakeRequestHandlerImpl,
  .FileManager_get_sd_card_statusRequestHandler = (pfFileManager_get_sd_card_statusRequestHandler_t) FileManager_get_sd_card_statusRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
static FILEMANAGER_FManOpResult_t getFManOpResultForFileManagerOpResult(eFileManagerOpResult_t opRes)
{
    FILEMANAGER_FManOpResult_t result;

    switch (opRes)
    {
        case FR_OK:
            result = FILEMANAGER_FMANOPRESULT_OK;
        break;

        case FR_DISK_ERR:
            result = FILEMANAGER_FMANOPRESULT_DISK_ERR;
        break;

        case FR_INT_ERR:
            result = FILEMANAGER_FMANOPRESULT_INT_ERR;
        break;

        case FR_NOT_READY:
            result = FILEMANAGER_FMANOPRESULT_NOT_READY;
        break;

        case FR_NO_FILE:
            result = FILEMANAGER_FMANOPRESULT_NO_FILE;
        break;

        case FR_NO_PATH:
            result = FILEMANAGER_FMANOPRESULT_NO_PATH;
        break;

        case FR_INVALID_NAME:
            result = FILEMANAGER_FMANOPRESULT_INVALID_NAME;
        break;

        case FR_DENIED:
            result = FILEMANAGER_FMANOPRESULT_DENIED;
        break;

        case FR_EXIST:
            result = FILEMANAGER_FMANOPRESULT_EXIST;
        break;

        case FR_INVALID_OBJECT:
            result = FILEMANAGER_FMANOPRESULT_INVALID_OBJECT;
        break;

        case FR_WRITE_PROTECTED:
            result = FILEMANAGER_FMANOPRESULT_WRITE_PROTECTED;
        break;

        case FR_INVALID_DRIVE:
            result = FILEMANAGER_FMANOPRESULT_INVALID_DRIVE;
        break;

        case FR_NOT_ENABLED:
            result = FILEMANAGER_FMANOPRESULT_NOT_ENABLED;
        break;

        case FR_NO_FILESYSTEM:
            result = FILEMANAGER_FMANOPRESULT_NO_FILESYSTEM;
        break;

        case FR_MKFS_ABORTED:
            result = FILEMANAGER_FMANOPRESULT_MKFS_ABORTED;
        break;

        case FR_TIMEOUT:
            result = FILEMANAGER_FMANOPRESULT_TIMEOUT;
        break;

        case FR_LOCKED:
            result = FILEMANAGER_FMANOPRESULT_LOCKED;
        break;

        case FR_NOT_ENOUGH_CORE:
            result = FILEMANAGER_FMANOPRESULT_NOT_ENOUGH_CORE;
        break;

        case FR_TOO_MANY_OPEN_FILES:
            result = FILEMANAGER_FMANOPRESULT_TOO_MANY_OPEN_FILES;
        break;

        case FR_INVALID_PARAMETER:
            result = FILEMANAGER_FMANOPRESULT_INVALID_PARAMETER;
        break;

        default:
            result = FILEMANAGER_FMANOPRESULT_INVALID_PARAMETER;
        break;
    }

    return result;
}

// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method FileManager::fileOpen (ID = 0x00000000)
static void FileManager_fileOpenRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerfileOpenRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_FManFileHandle_t tHandle;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::fileOpen@
    // Put your local variables in this section to preserve during merge!
    eFileManagerOpResult_t fmRes;
    FileManagerFHnd fHandle;
    // @USER_VAR_SECTION_END@FileManager::fileOpen@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileOpen@

        fmRes = fileManager_FOpen(pRequestData->strFilePath, pRequestData->u8Mode, &fHandle);

        static_assert(sizeof(tHandle) == sizeof(fHandle));
        tHandle = (FR_OK == fmRes) ? fHandle : (FileManagerFHnd)-1;

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::fileOpen@

        respResult = FileManager_fileOpenResp(
                        &respCtx,
                        tHandle,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILEOPEN_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileOpen (ID = 0x00000000)

// @START@ Request handler for method FileManager::fileClose (ID = 0x00000001)
static void FileManager_fileCloseRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerfileCloseRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::fileClose@
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::fileClose@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileClose@

        fmRes = fileManager_FClose(pRequestData->tHandle);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::fileClose@

        respResult = FileManager_fileCloseResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILECLOSE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileClose (ID = 0x00000001)

// @START@ Request handler for method FileManager::fileRead (ID = 0x00000002)
static void FileManager_fileReadRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerfileReadRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t au8Data[230];
    uint8_t u8DataSize;
    uint32_t u32BytesRead;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::fileRead@
    eFileManagerOpResult_t fmRes;
    size_t bytesToRead;
    // @USER_VAR_SECTION_END@FileManager::fileRead@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileRead@

        u32BytesRead = 0;
        (void) memset(au8Data, 0U, sizeof(au8Data));

        bytesToRead = pRequestData->u32BytesToRead;
        if (sizeof(au8Data) < bytesToRead)
        {
            bytesToRead = sizeof(au8Data);
        }
        fmRes = fileManager_FRead(pRequestData->tHandle,
                                pRequestData->u32Pos,
                                au8Data,
                                bytesToRead,
                                &u32BytesRead);

        // Maximum bytes read would be 230, limited by the FP frame size.
        u8DataSize = (fmRes == FR_OK) ? (uint8_t)u32BytesRead : 0;

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::fileRead@

        respResult = FileManager_fileReadResp(
                        &respCtx,
                        au8Data,
                        u8DataSize,
                        u32BytesRead,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILEREAD_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileRead (ID = 0x00000002)

// @START@ Request handler for method FileManager::fileWrite (ID = 0x00000003)
static void FileManager_fileWriteRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerfileWriteRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32BytesWritten;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::fileWrite@
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::fileWrite@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileWrite@

        u32BytesWritten = 0U;

        fmRes = fileManager_FWrite(pRequestData->tHandle,
                                   pRequestData->u32Pos,
                                   pRequestData->au8Data,
                                   (pRequestData->u8DataSize <= sizeof(pRequestData->au8Data)) ?
                                   (pRequestData->u8DataSize) :
                                   (sizeof(pRequestData->au8Data)),
                                   &u32BytesWritten);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::fileWrite@

        respResult = FileManager_fileWriteResp(
                        &respCtx,
                        u32BytesWritten,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILEWRITE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileWrite (ID = 0x00000003)

// @START@ Request handler for method FileManager::Rename (ID = 0x0000000F)
static void FileManager_RenameRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerRenameRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::Rename@
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::Rename@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::Rename@

        fmRes = fileManager_Rename(pRequestData->strOldPath, pRequestData->strNewPath);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::Rename@

        respResult = FileManager_RenameResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_RENAME_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::Rename (ID = 0x0000000F)

// @START@ Request handler for method FileManager::Delete (ID = 0x00000004)
static void FileManager_DeleteRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerDeleteRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::Delete@
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::Delete@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::Delete@

        fmRes = fileManager_Delete(pRequestData->strPath);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::Delete@

        respResult = FileManager_DeleteResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_DELETE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::Delete (ID = 0x00000004)

// @START@ Request handler for method FileManager::fileGetSize (ID = 0x00000005)
static void FileManager_fileGetSizeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerfileGetSizeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32FSize;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::fileGetSize@
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::fileGetSize@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileGetSize@

        u32FSize = 0; // Init the size variable
        
        fmRes = fileManager_FGetSize(pRequestData->strFilePath, &u32FSize);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::fileGetSize@

        respResult = FileManager_fileGetSizeResp(
                        &respCtx,
                        u32FSize,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILEGETSIZE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileGetSize (ID = 0x00000005)

// @START@ Request handler for method FileManager::fileGetCheckSum (ID = 0x00000006)
static void FileManager_fileGetCheckSumRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerfileGetCheckSumRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32Cs;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::fileGetCheckSum@
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::fileGetCheckSum@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileGetCheckSum@

        fmRes = fileManager_FGetCheckSum(pRequestData->strFilePath, &u32Cs);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::fileGetCheckSum@

        respResult = FileManager_fileGetCheckSumResp(
                        &respCtx,
                        u32Cs,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILEGETCHECKSUM_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileGetCheckSum (ID = 0x00000006)

// @START@ Request handler for method FileManager::fileGetOpenedHandlesCount (ID = 0x00000007)
static void FileManager_fileGetOpenedHandlesCountRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32HandlesCount;

    // @USER_VAR_SECTION_START@FileManager::fileGetOpenedHandlesCount@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@FileManager::fileGetOpenedHandlesCount@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileGetOpenedHandlesCount@

        u32HandlesCount = fileManager_getOpenHandlesCount();

        // @USER_CODE_SECTION_END@FileManager::fileGetOpenedHandlesCount@

        respResult = FileManager_fileGetOpenedHandlesCountResp(
                        &respCtx,
                        u32HandlesCount
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILEGETOPENEDHANDLESCOUNT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileGetOpenedHandlesCount (ID = 0x00000007)

// @START@ Request handler for method FileManager::formatPartition (ID = 0x00000008)
static void FileManager_formatPartitionRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerformatPartitionRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::formatPartition@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@FileManager::formatPartition@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::formatPartition@
        
        eFileManagerOpResult_t fmRes = fileManager_FormatPartition(pRequestData->ePartitionId);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);
        
        // @USER_CODE_SECTION_END@FileManager::formatPartition@

        respResult = FileManager_formatPartitionResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FORMATPARTITION_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::formatPartition (ID = 0x00000008)

// @START@ Request handler for method FileManager::fileDumpDirListToFile (ID = 0x00000009)
static void FileManager_fileDumpDirListToFileRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerfileDumpDirListToFileRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::fileDumpDirListToFile@
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::fileDumpDirListToFile@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::fileDumpDirListToFile@

        fmRes = fileManager_FDumpDirListToFile(pRequestData->strFilePath, pRequestData->strPattern);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::fileDumpDirListToFile@

        respResult = FileManager_fileDumpDirListToFileResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_FILEDUMPDIRLISTTOFILE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::fileDumpDirListToFile (ID = 0x00000009)

// @START@ Request handler for method FileManager::getStatistics (ID = 0x0000000A)
static void FileManager_getStatisticsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_Statistics_t sStats;

    // @USER_VAR_SECTION_START@FileManager::getStatistics@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@FileManager::getStatistics@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::getStatistics@

        memset(&sStats, 0, sizeof(sStats));

        sStats.sErrCounters.u16DISK_ERR = SdMngr_GetStatisticCounterById(FR_DISK_ERR);
        sStats.sErrCounters.u16INT_ERR = SdMngr_GetStatisticCounterById(FR_INT_ERR);
        sStats.sErrCounters.u16NOT_READY = SdMngr_GetStatisticCounterById(FR_NOT_READY);
        sStats.sErrCounters.u16NO_FILE = SdMngr_GetStatisticCounterById(FR_NO_FILE);
        sStats.sErrCounters.u16NO_PATH = SdMngr_GetStatisticCounterById(FR_NO_PATH);
        sStats.sErrCounters.u16INVALID_NAME = SdMngr_GetStatisticCounterById(FR_INVALID_NAME);
        sStats.sErrCounters.u16DENIED = SdMngr_GetStatisticCounterById(FR_DENIED);
        sStats.sErrCounters.u16EXIST = SdMngr_GetStatisticCounterById(FR_EXIST);
        sStats.sErrCounters.u16INVALID_OBJECT = SdMngr_GetStatisticCounterById(FR_INVALID_OBJECT);
        sStats.sErrCounters.u16WRITE_PROTECTED = SdMngr_GetStatisticCounterById(FR_WRITE_PROTECTED);
        sStats.sErrCounters.u16INVALID_DRIVE = SdMngr_GetStatisticCounterById(FR_INVALID_DRIVE);
        sStats.sErrCounters.u16NOT_ENABLED = SdMngr_GetStatisticCounterById(FR_NOT_ENABLED);
        sStats.sErrCounters.u16NO_FILESYSTEM = SdMngr_GetStatisticCounterById(FR_NO_FILESYSTEM);
        sStats.sErrCounters.u16MKFS_ABORTED = SdMngr_GetStatisticCounterById(FR_MKFS_ABORTED);
        sStats.sErrCounters.u16TIMEOUT = SdMngr_GetStatisticCounterById(FR_TIMEOUT);
        sStats.sErrCounters.u16LOCKED = SdMngr_GetStatisticCounterById(FR_LOCKED);
        sStats.sErrCounters.u16NOT_ENOUGH_CORE = SdMngr_GetStatisticCounterById(FR_NOT_ENOUGH_CORE);
        sStats.sErrCounters.u16TOO_MANY_OPEN_FILES = SdMngr_GetStatisticCounterById(FR_TOO_MANY_OPEN_FILES);
        sStats.sErrCounters.u16INVALID_PARAMETER = SdMngr_GetStatisticCounterById(FR_INVALID_PARAMETER);

        sRamStats_t stats =
        {
                .ff_call_use_count = 0U,
                .ff_call_use_max_value = 0U
        };

        SdMngr_GetRamStatisticCounters(&stats);
        sStats.i16MaxNestCount = stats.ff_call_use_max_value;
        sStats.i16NestCount = stats.ff_call_use_count;

        // @USER_CODE_SECTION_END@FileManager::getStatistics@

        respResult = FileManager_getStatisticsResp(
                        &respCtx,
                        &sStats
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_GETSTATISTICS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::getStatistics (ID = 0x0000000A)

// @START@ Request handler for method FileManager::clearStatistics (ID = 0x0000000B)
static void FileManager_clearStatisticsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;

    // @USER_VAR_SECTION_START@FileManager::clearStatistics@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@FileManager::clearStatistics@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::clearStatistics@

        SdMngr_ClearStatisticCounters();

        // @USER_CODE_SECTION_END@FileManager::clearStatistics@

        respResult = FileManager_clearStatisticsResp(
                        &respCtx
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_CLEARSTATISTICS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::clearStatistics (ID = 0x0000000B)

// @START@ Request handler for method FileManager::sdReinit (ID = 0x0000000C)
static void FileManager_sdReinitRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagersdReinitRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    bool bStatus;

    // @USER_VAR_SECTION_START@FileManager::sdReinit@
    // @USER_VAR_SECTION_END@FileManager::sdReinit@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::sdReinit@

        bStatus = fileManager_sd_reinit(pRequestData->bSynchronousCall);

        // @USER_CODE_SECTION_END@FileManager::sdReinit@

        respResult = FileManager_sdReinitResp(
                        &respCtx,
                        bStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_SDREINIT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::sdReinit (ID = 0x0000000C)

// @START@ Request handler for method FileManager::dirMake (ID = 0x0000000D)
static void FileManager_dirMakeRequestHandlerImpl(ReqContext_t *pReqCtx,
            const FileManagerdirMakeRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_FManOpResult_t eRes;

    // @USER_VAR_SECTION_START@FileManager::dirMake@
    // Put your local variables in this section to preserve during merge!
    eFileManagerOpResult_t fmRes;
    // @USER_VAR_SECTION_END@FileManager::dirMake@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::dirMake@

        fmRes = fileManager_FMakeDir(pRequestData->strDirName);

        eRes = getFManOpResultForFileManagerOpResult(fmRes);

        // @USER_CODE_SECTION_END@FileManager::dirMake@

        respResult = FileManager_dirMakeResp(
                        &respCtx,
                        eRes
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_DIRMAKE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::dirMake (ID = 0x0000000D)

// @START@ Request handler for method FileManager::get_sd_card_status (ID = 0x0000000E)
static void FileManager_get_sd_card_statusRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    FILEMANAGER_SDCardStatus_t eStatus;

    // @USER_VAR_SECTION_START@FileManager::get_sd_card_status@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@FileManager::get_sd_card_status@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@FileManager::get_sd_card_status@

        eStatus = (FILEMANAGER_SDCardStatus_t)SdMngr_GetCardState();

        // @USER_CODE_SECTION_END@FileManager::get_sd_card_status@

        respResult = FileManager_get_sd_card_statusResp(
                        &respCtx,
                        eStatus
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER, FILEMANAGER_GET_SD_CARD_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method FileManager::get_sd_card_status (ID = 0x0000000E)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void FileManagerServerAppInit(void)
{
    FileManager_registerServerApi(&FileManagerServerApiCtx);
}
