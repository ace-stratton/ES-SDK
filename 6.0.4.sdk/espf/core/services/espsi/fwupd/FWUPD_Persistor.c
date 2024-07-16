/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup fwupd
 * @{
 *
 * @file    FWUPD_Persistor.h
 * @brief   FWUPD persistor configuration definitions
 *
 * @}
 */

#include <stdbool.h>
#include <stdint.h>
#include "FWUPD_Persistor.h"
#include "assertions.h"
#include "cmsis_os2.h"
#include "MACCRC32_Classic_Impl.h"

#define APP_BUNDLE_CRC_SIZE     (4U)

#define FWUPD_PERSISTOR_STORAGE_DIR ""

static const TCHAR aActiveTidFileName[] = "fwu.tid";
const TCHAR aTempImageFileName[] = "fwu.tmp";

// verification is disabled in this version of the protocol
#if 0
static uint8_t au8VerifyBuffer[256];
#endif

typedef struct
{
    // file handle for the current transfer
    FIL fHnd;
    // overall maximum time for writing a single block to file system for
    // the current transfer
    uint32_t u32MaxWriteTime;
} sPersistorContext_t;

static sPersistorContext_t persistCtx;

static void fs_vInit(sPersistorContext_t * const pCtx);
static bool fs_bGetPendingTransferInfo(sTransferInfo_t * const pTransferInfo);

static void fs_vInit(sPersistorContext_t * const pCtx)
{
    CRIT_ASSERT(pCtx != NULL);

    pCtx->u32MaxWriteTime = 0U;
}

static bool fs_bGetPendingTransferInfo(sTransferInfo_t * const pTransferInfo)
{
    FIL tempHandle;
    FRESULT fres;
    bool bPendingTransferExists = false;
    UINT uintBytesRead = (UINT) 0;

    CRIT_ASSERT(pTransferInfo != NULL);

    fres = SdMngr_f_open(&tempHandle, (const TCHAR *) aActiveTidFileName, FA_OPEN_EXISTING | FA_READ);

    if (fres == FR_OK)
    {
        fres = SdMngr_f_read(&tempHandle,
                      (void *) pTransferInfo,
                      sizeof(sTransferInfo_t),
                      &uintBytesRead);

        (void) fres;
        (void) SdMngr_f_close(&tempHandle);

        if (uintBytesRead == sizeof(sTransferInfo_t))
        {
            bPendingTransferExists = true;
        }
    }
    else
    {
        (void) memset(pTransferInfo, 0U, sizeof(sTransferInfo_t));
    }

    return bPendingTransferExists;
}

static bool fs_u32GetStartingPosForTransfer(const uint64_t u64TransferId, uint32_t * pu32StartPos)
{
    FRESULT fres;
    uint32_t u32StartPos = 0U;
    sTransferInfo_t tinfo;
    bool bPendingTransferExists = fs_bGetPendingTransferInfo(&tinfo);

    if (bPendingTransferExists)
    {
        if (u64TransferId == tinfo.u64TransferId)
        {
            // TID file exists and TID matches the new transfer ID -->
            // try to obtain the size of the downloaded image to
            // attempt resuming of the active transfer (probably an OBC restart occurred)
            fres = SdMngr_f_open(&persistCtx.fHnd, (const TCHAR *) aTempImageFileName, FA_OPEN_EXISTING | FA_READ);

            if (fres == FR_OK)
            {
                u32StartPos = SdMngr_f_size(&persistCtx.fHnd);
                (void) SdMngr_f_close(&persistCtx.fHnd);
            }
        }
    }

    // if the starting pos is more than zero, then the transfer size shall also include the size of the update header
    // which is not written as part of the downloaded file but GS assumes the start of transfer from the beginning of this header;
    // providing a value 0 here, means that we also want to receive the header again
    if (pu32StartPos != NULL)
    {
        *pu32StartPos = bPendingTransferExists ? u32StartPos + sizeof(SESSoftwareUPD_Bundle) : u32StartPos;
    }

    return bPendingTransferExists;
}

eFwUpdPersistorResult FWUPD_Persistor_GetPartialTransferInfo(sTransferInfo_t * const pTransferInfo,
                                                             uint32_t * const pu32StartPos)
{
    eFwUpdPersistorResult res = EFWUPDPERSISTORRESULT_ERROR;

    if ((pTransferInfo != NULL) &&
        (pu32StartPos != NULL))
    {
        if (fs_bGetPendingTransferInfo(pTransferInfo))
        {
            (void) fs_u32GetStartingPosForTransfer(pTransferInfo->u64TransferId, pu32StartPos);
            res = EFWUPDPERSISTORRESULT_OK;
        }
        else
        {
            *pu32StartPos = 0U;
        }
    }

    return res;
}

eFwUpdPersistorResult FWUPD_Persistor_StartNewTransfer(sTransferInfo_t * const pTransferInfo, uint32_t * const pu32StartPos)
{
    FRESULT fres = FR_INT_ERR;
    FIL tempHandle;
    uint32_t u32BytesWritten = 0U;
    bool bPendingTransferExists = false;

    fs_vInit(&persistCtx);

    if (pTransferInfo != NULL)
    {
        bPendingTransferExists = fs_u32GetStartingPosForTransfer(pTransferInfo->u64TransferId, pu32StartPos);

        if (pu32StartPos != NULL)
        {
            if (*pu32StartPos >= sizeof(SESSoftwareUPD_Bundle))
            {
                *pu32StartPos -= sizeof(SESSoftwareUPD_Bundle);
            }
        }

        if (!bPendingTransferExists)
        {
            // create the file which contains the ID of the currently active transfer
            fres = SdMngr_f_open(&tempHandle, (const TCHAR *) aActiveTidFileName, FA_WRITE | FA_CREATE_ALWAYS);
            if (fres == FR_OK)
            {
                fres = SdMngr_f_write(&tempHandle, (const void *) pTransferInfo, sizeof(sTransferInfo_t), (UINT *) &u32BytesWritten);
                (void) SdMngr_f_close(&tempHandle);

                if ((fres == FR_OK) && (u32BytesWritten == sizeof(sTransferInfo_t)))
                {
                    // attempt to create a zero-length file
                    fres = SdMngr_f_open(&persistCtx.fHnd, (const TCHAR *) aTempImageFileName, FA_WRITE | FA_CREATE_ALWAYS);
                    (void) fres;
                    fres = SdMngr_f_close(&persistCtx.fHnd);
                }
                else
                {
                    FWUPD_DBG_PRINT("fres = %d\r\n", fres);
                    fres = FR_INT_ERR;
                }
            }
            else
                FWUPD_DBG_PRINT("SdMngr_f_open(%d)\r\n", fres);
        }
        else
        {
            fres = FR_OK;
        }
    }

    return (fres == FR_OK) ? EFWUPDPERSISTORRESULT_OK : EFWUPDPERSISTORRESULT_ERROR;
}

eFwUpdPersistorResult FWUPD_Persistor_CommitBuffer(const uint32_t u32Pos,
                                                   const uint8_t * const pu8Buf,
                                                   const uint32_t u32BufSize,
                                                   uint32_t * const pu32BytesWritten)
{
    FRESULT fres;
    UINT bytesWritten = 0U;
    eFwUpdPersistorResult retRes = EFWUPDPERSISTORRESULT_ERROR;
    uint32_t u32WriteTime;
    uint32_t u32StartTime;

    u32StartTime = osKernelGetTickCount();

    fres = SdMngr_f_open(&persistCtx.fHnd, (const TCHAR *) aTempImageFileName, FA_WRITE | FA_OPEN_APPEND);

    if (fres == FR_OK)
    {
        fres = SdMngr_f_lseek(&persistCtx.fHnd, u32Pos);

        if (fres == FR_OK)
        {
            fres = SdMngr_f_write(&persistCtx.fHnd, pu8Buf, u32BufSize, &bytesWritten);

            if (fres == FR_OK)
            {
                if (pu32BytesWritten != NULL)
                {
                    *pu32BytesWritten = bytesWritten;
                }

                if (fres == FR_OK)
                {
                    retRes = EFWUPDPERSISTORRESULT_OK;
                }
            }
            else
                FWUPD_DBG_PRINT("SdMngr_f_write(%d)\r\n", fres);

        }
        else
            FWUPD_DBG_PRINT("SdMngr_f_lseek(%d)\r\n", fres);
    }
    else
        FWUPD_DBG_PRINT("SdMngr_f_open(%d)\r\n", fres);

    u32WriteTime = osKernelGetTickCount() - u32StartTime;

    if (persistCtx.u32MaxWriteTime < u32WriteTime)
    {
        persistCtx.u32MaxWriteTime = u32WriteTime;
    }

    (void) SdMngr_f_close(&persistCtx.fHnd);

    return retRes;
}

eFwUpdPersistorResult FWUPD_Persistor_FinalizeTransfer(const uint32_t num_bytes_to_strip)
{
    FRESULT fres = FR_INT_ERR;
    FIL fHnd;

    fres = SdMngr_f_open(&fHnd, aTempImageFileName, FA_WRITE | FA_OPEN_APPEND);

    if (fres == FR_OK)
    {
        // strip the specified number of bytes at the end of the file
        if (SdMngr_f_size(&fHnd) >= num_bytes_to_strip)
        {
            fres = SdMngr_f_lseek(&fHnd, SdMngr_f_size(&fHnd) - num_bytes_to_strip);

            if (fres == FR_OK)
            {
                fres = SdMngr_f_truncate(&fHnd);
                (void) SdMngr_f_close(&fHnd);
            }
        }
    }
    else
        FWUPD_DBG_PRINT("SdMngr_f_open(%d)\r\n", fres);

    return (fres == FR_OK) ? EFWUPDPERSISTORRESULT_OK : EFWUPDPERSISTORRESULT_ERROR;
}

eFwUpdPersistorResult FWUPD_Persistor_PrepareImage(char * const pRequestedImageName)
{
    FRESULT fres = FR_INVALID_PARAMETER;

    if (pRequestedImageName != NULL)
    {
        // delete any previous update image if it exists
        (void) SdMngr_f_unlink(pRequestedImageName);

        // rename temporary image to the name requested by the user
        fres = SdMngr_f_rename(aTempImageFileName, pRequestedImageName);
    }
    else
    {
    	// make sure all temporary files get deleted
    	(void) SdMngr_f_unlink((const TCHAR *) aTempImageFileName);
    }

    // delete active transfer ID file
    (void) SdMngr_f_unlink((const TCHAR *) aActiveTidFileName);

    return (fres == FR_OK) ? EFWUPDPERSISTORRESULT_OK : EFWUPDPERSISTORRESULT_ERROR;
}

eFwUpdPersistorResult FWUPD_Persistor_VerifyImage(void)
{
// verification example (currently not enabled due to custom extensions on top of the FWUPD protocol
#if 0
    FIL fHnd;
    FRESULT fres;
    UINT bytesRead = 0U;
    eFwUpdPersistorResult res = EFWUPDPERSISTORRESULT_ERROR;
    uint32_t u32Crc = 0xFFFFFFFFU;
    uint32_t u32ExpectedCrc = 0U;
    uint32_t u32FSize = 0U;

    fres = SdMngr_f_open(&fHnd, aTempImageFileName, FA_READ | FA_OPEN_EXISTING);

    if (fres == FR_OK)
    {
        u32FSize = SdMngr_f_size(&fHnd);

        if (u32FSize > APP_BUNDLE_CRC_SIZE)
        {
            fres = SdMngr_f_lseek(&fHnd, SdMngr_f_size(&fHnd) - APP_BUNDLE_CRC_SIZE);

            if (fres == FR_OK)
            {
                fres = SdMngr_f_read(&fHnd, &u32ExpectedCrc, APP_BUNDLE_CRC_SIZE, &bytesRead);

                fres = SdMngr_f_lseek(&fHnd, 0);

                if ((fres == FR_OK) && (bytesRead == APP_BUNDLE_CRC_SIZE))
                {
                    do
                    {
                        fres = SdMngr_f_read(&fHnd, au8VerifyBuffer, sizeof(au8VerifyBuffer), &bytesRead);

                        if (fres == FR_OK)
                        {
                            u32Crc = MACCRC32_Calc32(au8VerifyBuffer, bytesRead, u32Crc);
                        }
                        else
                        {
                            break;
                        }
                    } while (bytesRead > 0);

                    if (u32Crc == u32ExpectedCrc)
                    {
                        res = EFWUPDPERSISTORRESULT_OK;
                    }
                }
            }
        }
    }

    (void) SdMngr_f_close(&fHnd);

    return res;
#else
    return EFWUPDPERSISTORRESULT_OK;
#endif
}

eFwUpdPersistorResult FWUPD_Persistor_DiscardPendingUpdate(void)
{
    (void) SdMngr_f_unlink(aActiveTidFileName);
    (void) SdMngr_f_unlink(aTempImageFileName);

    return EFWUPDPERSISTORRESULT_OK;
}

const TCHAR * const FWUPD_Persistor_GetDownloadedImageFileName(void)
{
    return aTempImageFileName;
}

const char * FWUPD_Persistor_GetStorageDir(void)
{
    return FWUPD_PERSISTOR_STORAGE_DIR;
}
