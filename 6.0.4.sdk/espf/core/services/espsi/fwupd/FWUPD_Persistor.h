/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TPLAYER_FWUPD_PERSISTOR_H_
#define TPLAYER_FWUPD_PERSISTOR_H_

/**
 * @addtogroup fwupd
 * @{
 *
 * @file    FWUPD_Persistor.h
 * @brief   FWUPD persistor configuration
 *
 * @}
 */

#include "es_cdef.h"
#include "ff.h"
#include "core/middlewares/ESPLATFORM_NETWORK_STACK/ES_FW_UPD/ESFWUPD_ModDrv.h"
#include "FileManager.h"
#include "trace.h"

#define EXT_BUN_FOOTER_SIG                "EXT_BUN"        /**< extended footer signature string */
#define FWUPD_MAX_FILE_NAME_SIZE          FF_LFN_BUF       /**< maximum file name size allowed for uploaded files via FWUPD protocol */

#if defined(DEBUG_TRACE_FWUPD_ENABLED)
#define FWUPD_DBG_PRINT(formatStr, ...)   ES_TRACE_DEBUG(formatStr OPT_VA_ARGS(__VA_ARGS__))
#else
#define FWUPD_DBG_PRINT(fmtString, ...)   asm("nop")
#endif

typedef enum
{
    EFWUPDPERSISTORRESULT_OK,
    EFWUPDPERSISTORRESULT_ERROR,
    EFWUPDPERSISTORRESULT_MAX
} eFwUpdPersistorResult;

/** @brief Optional extended bundle footer which contains information about the file name to use for the uploaded buffer
 *
 *  The structure extends the current FWUPD protocol handling to support regular file uploads with a file name specified by the
 *  user. At the same time, the protocol remains compatible to the existing tooling because the additional footer is actually
 *  part of the payload data and will only be used if formatted as expected and its CRC is calculated correctly.
*/
typedef struct
{
    uint8_t ext_bun_sig[sizeof(EXT_BUN_FOOTER_SIG) - 1U];   /**< extended bundle footer signature in ASCII fixed to 'EXT_BUN' (no terminating null) */
    uint8_t file_name[FWUPD_MAX_FILE_NAME_SIZE];            /**< ASCIIZ file name to use for storing this buffer on the SD card */
    uint16_t ext_bun_crc;                                   /**< CRC16-CCITT of all extended bundle header fields */
} PACKED SESSoftwareUPD_Bundle_ex_t;

typedef struct
{
    uint64_t u64TransferId;
    bool has_valid_footer;                               /**< true: set on bundle footer validation if the footer_ex field was verified successfully, false: otherwise */
    SESSoftwareUPD_Bundle header;                        /**< mandatory FWUPD header */
    SESSoftwareUPD_Bundle_ex_t footer_ex;                /**< this fiels is optional and may not actually be present in the provided data (will be searched for at the end of a fully received file */
} PACKED sTransferInfo_t;

extern const TCHAR aTempImageFileName[];

eFwUpdPersistorResult FWUPD_Persistor_StartNewTransfer(sTransferInfo_t * const pTransferInfo,
                                                       uint32_t * const pu32StartPos);

eFwUpdPersistorResult FWUPD_Persistor_CommitBuffer(const uint32_t u32Pos,
                                                   const uint8_t * const pu8Buf,
                                                   const uint32_t u32BufSize,
                                                   uint32_t * const pu32BytesWritten);

eFwUpdPersistorResult FWUPD_Persistor_GetPartialTransferInfo(sTransferInfo_t * const pTransferInfo,
                                                             uint32_t * const pu32StartPos);

eFwUpdPersistorResult FWUPD_Persistor_VerifyImage(void);

eFwUpdPersistorResult FWUPD_Persistor_PrepareImage(char * const pRequestedImageName);

eFwUpdPersistorResult FWUPD_Persistor_FinalizeTransfer(const uint32_t num_bytes_to_strip);

const TCHAR * const FWUPD_Persistor_GetDownloadedImageFileName(void);

eFwUpdPersistorResult FWUPD_Persistor_DiscardPendingUpdate(void);

const char * FWUPD_Persistor_GetStorageDir(void);

#endif /* TPLAYER_FWUPD_PERSISTOR_H_ */
