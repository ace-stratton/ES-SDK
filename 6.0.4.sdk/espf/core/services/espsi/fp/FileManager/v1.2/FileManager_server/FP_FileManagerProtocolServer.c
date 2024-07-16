/*!
********************************************************************************************
* @file FP_FileManagerProtocolServer.c
* @brief ESSA Stack server-side implementation
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
#include "FP_common/FP_ProtocolServerCommon.h"

#define FileManager_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define FileManager_PROTOCOL_VERSION_MINOR   ((uint8_t) 2)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileOpenRequestData_t data;
} PACKED_STRUCT FileManagerfileOpenProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileOpenResponseData_t data;
} PACKED_STRUCT FileManagerfileOpenProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileCloseRequestData_t data;
} PACKED_STRUCT FileManagerfileCloseProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileCloseResponseData_t data;
} PACKED_STRUCT FileManagerfileCloseProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileReadRequestData_t data;
} PACKED_STRUCT FileManagerfileReadProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileReadResponseData_t data;
} PACKED_STRUCT FileManagerfileReadProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileWriteRequestData_t data;
} PACKED_STRUCT FileManagerfileWriteProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileWriteResponseData_t data;
} PACKED_STRUCT FileManagerfileWriteProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerRenameRequestData_t data;
} PACKED_STRUCT FileManagerRenameProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerRenameResponseData_t data;
} PACKED_STRUCT FileManagerRenameProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerDeleteRequestData_t data;
} PACKED_STRUCT FileManagerDeleteProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerDeleteResponseData_t data;
} PACKED_STRUCT FileManagerDeleteProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileGetSizeRequestData_t data;
} PACKED_STRUCT FileManagerfileGetSizeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileGetSizeResponseData_t data;
} PACKED_STRUCT FileManagerfileGetSizeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileGetCheckSumRequestData_t data;
} PACKED_STRUCT FileManagerfileGetCheckSumProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileGetCheckSumResponseData_t data;
} PACKED_STRUCT FileManagerfileGetCheckSumProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT FileManagerfileGetOpenedHandlesCountProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileGetOpenedHandlesCountResponseData_t data;
} PACKED_STRUCT FileManagerfileGetOpenedHandlesCountProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerformatPartitionRequestData_t data;
} PACKED_STRUCT FileManagerformatPartitionProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerformatPartitionResponseData_t data;
} PACKED_STRUCT FileManagerformatPartitionProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileDumpDirListToFileRequestData_t data;
} PACKED_STRUCT FileManagerfileDumpDirListToFileProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerfileDumpDirListToFileResponseData_t data;
} PACKED_STRUCT FileManagerfileDumpDirListToFileProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT FileManagergetStatisticsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagergetStatisticsResponseData_t data;
} PACKED_STRUCT FileManagergetStatisticsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT FileManagerclearStatisticsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT FileManagerclearStatisticsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagersdReinitRequestData_t data;
} PACKED_STRUCT FileManagersdReinitProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagersdReinitResponseData_t data;
} PACKED_STRUCT FileManagersdReinitProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerdirMakeRequestData_t data;
} PACKED_STRUCT FileManagerdirMakeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerdirMakeResponseData_t data;
} PACKED_STRUCT FileManagerdirMakeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT FileManagerget_sd_card_statusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    FileManagerget_sd_card_statusResponseData_t data;
} PACKED_STRUCT FileManagerget_sd_card_statusProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileOpenReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileCloseReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileReadReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileWriteReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_RenameReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_DeleteReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileGetSizeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileGetCheckSumReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileGetOpenedHandlesCountReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_formatPartitionReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_fileDumpDirListToFileReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_getStatisticsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_clearStatisticsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_sdReinitReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_dirMakeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_get_sd_card_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_FileManagerProtocolServerInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static FileManager_ServerApi_t *pSrvApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { FILEMANAGER_FILEOPEN_FUNC_ID, fs_fileOpenReq },
    { FILEMANAGER_FILECLOSE_FUNC_ID, fs_fileCloseReq },
    { FILEMANAGER_FILEREAD_FUNC_ID, fs_fileReadReq },
    { FILEMANAGER_FILEWRITE_FUNC_ID, fs_fileWriteReq },
    { FILEMANAGER_RENAME_FUNC_ID, fs_RenameReq },
    { FILEMANAGER_DELETE_FUNC_ID, fs_DeleteReq },
    { FILEMANAGER_FILEGETSIZE_FUNC_ID, fs_fileGetSizeReq },
    { FILEMANAGER_FILEGETCHECKSUM_FUNC_ID, fs_fileGetCheckSumReq },
    { FILEMANAGER_FILEGETOPENEDHANDLESCOUNT_FUNC_ID, fs_fileGetOpenedHandlesCountReq },
    { FILEMANAGER_FORMATPARTITION_FUNC_ID, fs_formatPartitionReq },
    { FILEMANAGER_FILEDUMPDIRLISTTOFILE_FUNC_ID, fs_fileDumpDirListToFileReq },
    { FILEMANAGER_GETSTATISTICS_FUNC_ID, fs_getStatisticsReq },
    { FILEMANAGER_CLEARSTATISTICS_FUNC_ID, fs_clearStatisticsReq },
    { FILEMANAGER_SDREINIT_FUNC_ID, fs_sdReinitReq },
    { FILEMANAGER_DIRMAKE_FUNC_ID, fs_dirMakeReq },
    { FILEMANAGER_GET_SD_CARD_STATUS_FUNC_ID, fs_get_sd_card_statusReq }
};

/**********************************************************************
 *
 *  Static methods implementation
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    ESSA_Stack_FP_MsgHdr_t *pHdr = NULL;
    bool bIsFuncSupported = false;
    uint8_t i;

    // Basic header validity check
    if ((fp_DataInfo == NULL) ||
        (fp_DataInfo->u16DataSize < sizeof(ESSA_Stack_FP_MsgHdr_t)) ||
        (fp_DataInfo->pu8Data == NULL))
    {
        return false;
    }

    pHdr = (ESSA_Stack_FP_MsgHdr_t *) fp_DataInfo->pu8Data;

    if (IS_REQUEST(*pHdr))
    {
        for (i = 0; i < COUNT_OF(fs_aFuncArray); i++)
        {
            if (fs_aFuncArray[i].funcId == pHdr->funcId)
            {
                if (fs_aFuncArray[i].pfFunc != NULL)
                {
                    bIsFuncSupported = true;
                    fs_aFuncArray[i].pfFunc(fp_DataInfo);
                }

                break;
            }
        }

        if (!bIsFuncSupported)
            (void) ProtocolSendErrorResp(fp_DataInfo, (uint8_t) ESSA_FP_ERRCODE_FUNC_NOT_SUPPORTED);
    }

    return bIsFuncSupported;
}

static void fs_fileOpenReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileOpenProtocolRequestData_t *fullrequest = (FileManagerfileOpenProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerfileOpenRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileOpenProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerfileOpenRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileOpenRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileOpenRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fileCloseReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileCloseProtocolRequestData_t *fullrequest = (FileManagerfileCloseProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerfileCloseRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileCloseProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerfileCloseRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileCloseRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileCloseRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fileReadReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileReadProtocolRequestData_t *fullrequest = (FileManagerfileReadProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerfileReadRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileReadProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerfileReadRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileReadRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileReadRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fileWriteReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileWriteProtocolRequestData_t *fullrequest = (FileManagerfileWriteProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerfileWriteRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileWriteProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerfileWriteRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileWriteRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileWriteRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_RenameReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerRenameProtocolRequestData_t *fullrequest = (FileManagerRenameProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerRenameRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerRenameProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerRenameRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_RenameRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_RenameRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_DeleteReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerDeleteProtocolRequestData_t *fullrequest = (FileManagerDeleteProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerDeleteRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerDeleteProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerDeleteRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_DeleteRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_DeleteRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fileGetSizeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileGetSizeProtocolRequestData_t *fullrequest = (FileManagerfileGetSizeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerfileGetSizeRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileGetSizeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerfileGetSizeRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileGetSizeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileGetSizeRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fileGetCheckSumReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileGetCheckSumProtocolRequestData_t *fullrequest = (FileManagerfileGetCheckSumProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerfileGetCheckSumRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileGetCheckSumProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerfileGetCheckSumRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileGetCheckSumRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileGetCheckSumRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fileGetOpenedHandlesCountReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileGetOpenedHandlesCountProtocolRequestData_t *fullrequest = (FileManagerfileGetOpenedHandlesCountProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileGetOpenedHandlesCountProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileGetOpenedHandlesCountRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileGetOpenedHandlesCountRequestHandler(&requestCtx);
    }
}

static void fs_formatPartitionReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerformatPartitionProtocolRequestData_t *fullrequest = (FileManagerformatPartitionProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerformatPartitionRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerformatPartitionProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerformatPartitionRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_formatPartitionRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_formatPartitionRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_fileDumpDirListToFileReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerfileDumpDirListToFileProtocolRequestData_t *fullrequest = (FileManagerfileDumpDirListToFileProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerfileDumpDirListToFileRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileDumpDirListToFileProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerfileDumpDirListToFileRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_fileDumpDirListToFileRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_fileDumpDirListToFileRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_getStatisticsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagergetStatisticsProtocolRequestData_t *fullrequest = (FileManagergetStatisticsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagergetStatisticsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_getStatisticsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_getStatisticsRequestHandler(&requestCtx);
    }
}

static void fs_clearStatisticsReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerclearStatisticsProtocolRequestData_t *fullrequest = (FileManagerclearStatisticsProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerclearStatisticsProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_clearStatisticsRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_clearStatisticsRequestHandler(&requestCtx);
    }
}

static void fs_sdReinitReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagersdReinitProtocolRequestData_t *fullrequest = (FileManagersdReinitProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagersdReinitRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagersdReinitProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagersdReinitRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_sdReinitRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_sdReinitRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_dirMakeReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerdirMakeProtocolRequestData_t *fullrequest = (FileManagerdirMakeProtocolRequestData_t *) fp_DataInfo->pu8Data;
    FileManagerdirMakeRequestData_t *requestPayload = NULL;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerdirMakeProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    requestPayload = (FileManagerdirMakeRequestData_t *) &fullrequest->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_dirMakeRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_dirMakeRequestHandler(&requestCtx,
                                        requestPayload);
    }
}

static void fs_get_sd_card_statusReq(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    FileManagerget_sd_card_statusProtocolRequestData_t *fullrequest = (FileManagerget_sd_card_statusProtocolRequestData_t *) fp_DataInfo->pu8Data;
    ReqContext_t requestCtx;

    STATIC_ASSERT_SIZE_CHECK(FileManagerget_sd_card_statusProtocolRequestData_t);

    if ((fullrequest == NULL) || (pSrvApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullrequest)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pSrvApiHnd->FileManager_get_sd_card_statusRequestHandler != NULL)
    {
        requestCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        requestCtx.netType = fp_DataInfo->pMACContext->netType;
        requestCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        requestCtx.seqId = fullrequest->hdr.seqId;

        pSrvApiHnd->FileManager_get_sd_card_statusRequestHandler(&requestCtx);
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void FileManager_registerServerApi(FileManager_ServerApi_t *pSrvApiHandlers)
{
    pSrvApiHnd = pSrvApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t FileManager_getServerProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_FileManagerProtocolServerInfo;
}

ESSATMAC_ErrCodes FileManager_fileOpenResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManFileHandle_t tHandle,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileOpenProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileOpenProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileOpenProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILEOPEN_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.tHandle = tHandle;
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileOpenProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_fileCloseResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileCloseProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileCloseProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileCloseProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILECLOSE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileCloseProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_fileReadResp(
                RespContext_t* ctx,
                const uint8_t * const au8Data,
                const uint8_t u8DataSize,
                const uint32_t u32BytesRead,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileReadProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileReadProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileReadProtocolResponseData_t);

    if ((ctx != NULL) && (au8Data != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILEREAD_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (au8Data != NULL)
        {
            if (u8DataSize > 0U)
            {
                // zero-out complete message buffer before copying user data to avoid confusion if
                // buffer is only partially filled-in by user
                (void) memset((void *) responseParams.data.au8Data,
                              0U,
                              sizeof(responseParams.data.au8Data));
                (void) memcpy((void *) responseParams.data.au8Data,
                              (const void *) au8Data,
                              MIN(u8DataSize, sizeof(responseParams.data.au8Data)));
            
            
            }
            
            responseParams.data.u8DataSize = MIN(u8DataSize, sizeof(responseParams.data.au8Data));
        }
        else
        {
            (void) memset((void *) responseParams.data.au8Data,
                          0U,
                          sizeof(responseParams.data.au8Data));
        }
        responseParams.data.u32BytesRead = u32BytesRead;
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileReadProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_fileWriteResp(
                RespContext_t* ctx,
                const uint32_t u32BytesWritten,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileWriteProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileWriteProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileWriteProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILEWRITE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32BytesWritten = u32BytesWritten;
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileWriteProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_RenameResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerRenameProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerRenameProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerRenameProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_RENAME_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerRenameProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_DeleteResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerDeleteProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerDeleteProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerDeleteProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_DELETE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerDeleteProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_fileGetSizeResp(
                RespContext_t* ctx,
                const uint32_t u32FSize,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileGetSizeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileGetSizeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileGetSizeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILEGETSIZE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32FSize = u32FSize;
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileGetSizeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_fileGetCheckSumResp(
                RespContext_t* ctx,
                const uint32_t u32Cs,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileGetCheckSumProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileGetCheckSumProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileGetCheckSumProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILEGETCHECKSUM_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32Cs = u32Cs;
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileGetCheckSumProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_fileGetOpenedHandlesCountResp(
                RespContext_t* ctx,
                const uint32_t u32HandlesCount
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileGetOpenedHandlesCountProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileGetOpenedHandlesCountProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileGetOpenedHandlesCountProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILEGETOPENEDHANDLESCOUNT_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.u32HandlesCount = u32HandlesCount;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileGetOpenedHandlesCountProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_formatPartitionResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerformatPartitionProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerformatPartitionProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerformatPartitionProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FORMATPARTITION_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerformatPartitionProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_fileDumpDirListToFileResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerfileDumpDirListToFileProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerfileDumpDirListToFileProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerfileDumpDirListToFileProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_FILEDUMPDIRLISTTOFILE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerfileDumpDirListToFileProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_getStatisticsResp(
                RespContext_t* ctx,
                const FILEMANAGER_Statistics_t * const sStats
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagergetStatisticsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagergetStatisticsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagergetStatisticsProtocolResponseData_t);

    if ((ctx != NULL) && (sStats != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_GETSTATISTICS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        if (sStats != NULL)
        {
            responseParams.data.sStats = *(sStats);
        }
        else
        {
            (void) memset((void *) &responseParams.data.sStats,
                          0U,
                          sizeof(responseParams.data.sStats));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagergetStatisticsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_clearStatisticsResp(
                RespContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerclearStatisticsProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerclearStatisticsProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerclearStatisticsProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_CLEARSTATISTICS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerclearStatisticsProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_sdReinitResp(
                RespContext_t* ctx,
                const bool bStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagersdReinitProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagersdReinitProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagersdReinitProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_SDREINIT_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.bStatus = bStatus;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagersdReinitProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_dirMakeResp(
                RespContext_t* ctx,
                const FILEMANAGER_FManOpResult_t eRes
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerdirMakeProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerdirMakeProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerdirMakeProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_DIRMAKE_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eRes = eRes;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerdirMakeProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes FileManager_get_sd_card_statusResp(
                RespContext_t* ctx,
                const FILEMANAGER_SDCardStatus_t eStatus
)
{
#ifndef BIG_ENDIAN_PLATFORM
    FileManagerget_sd_card_statusProtocolResponseData_t responseParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t responseParams[sizeof(FileManagerget_sd_card_statusProtocolResponseData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(FileManagerget_sd_card_statusProtocolResponseData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        responseParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_FILEMANAGER;
        responseParams.hdr.funcId  = FILEMANAGER_GET_SD_CARD_STATUS_FUNCRESP_ID;
        responseParams.hdr.seqId   = ctx->seqId;
        responseParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_RESPONSE(responseParams.hdr);

        // fill message data
        responseParams.data.eStatus = eStatus;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &responseParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) responseParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(FileManagerget_sd_card_statusProtocolResponseData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


