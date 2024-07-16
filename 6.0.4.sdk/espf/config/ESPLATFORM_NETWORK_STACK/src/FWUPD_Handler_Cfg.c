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
 * @file    FWUPD_Handler_Cfg.c
 * @brief   FWUPD handler configuration definitions
 *
 * @}
 */

#include <string.h>
#include "FWUPD_Handler_Cfg.h"
#include "FWUPD_Persistor.h"
#include "es_exeh.h"
#include "CommandsApi.h"
#include "es_lz77.h"
#include "TleUpdate.h"
#include "payload_scheduler.h"
#include "crc16-ccitt.h"
#include "SdMngr.h"
#include "trace.h"
#include "assertions.h"
#include <stdio.h>

#define EXEH_CURRENT_MODULE_ID            (eEXEHModuleID_FWUPD_HANDLER_CFG)
#define EXT_MAX_SIZE					  (3U)		/**< maximum size of the file extension supported by this module */
#define EXT_MAP_ENTRIES_CNT				  (3U)		/**< number of entries in the file handlers map */

// Exception IDs
#define EXC_FWUPD_INVALID_ARGS             ((int32_t) 0)
#define EXC_FWUPD_UNSUPPORTED_IMAGE_TYPE   ((int32_t) 1)
#define EXC_FWUPD_COULD_NOT_PREPARE_IMAGE  ((int32_t) 2)
#define EXC_FWUPD_COULD_NOT_FINALIZE_IMAGE ((int32_t) 3)

/** @brief A function pointer to
 *
 */
typedef void (*p_file_handler_t)(const char * const p_file_name);

static uint32_t process_file_footer(const char * const pFileName, sTransferInfo_t * const pTransferInfo);
static void default_file_handler(const char * const p_file_name);
static void tle_handler(const char * const p_file_name);
static void lz7_handler(const char * const p_file_name);
static void bin_handler(const char * const p_file_name);
static void handle_file_ext(const char * const p_file_name);

/**
 * @brief The function attempts to process the optionally appended file footer which contains additional information
 *           about the uploaded file.
 *
 * @param[in] pFileName name of the received file
 * @param[in/out] pTransferInfo    a pointer to the last transfer context
 * @return size of the footer which must be truncated at the end of the file before user processing of the uploaded data
 */
static uint32_t process_file_footer(const char * const pFileName, sTransferInfo_t * const pTransferInfo)
{
    CRIT_ASSERT(NULL != pTransferInfo);

    FRESULT fres = FR_INT_ERR;
    FIL fHnd;
    uint32_t footer_size = 0U;

    fres = SdMngr_f_open(&fHnd, pFileName, FA_READ | FA_OPEN_EXISTING);

    if (FR_OK == fres)
    {
        if (SdMngr_f_size(&fHnd) >= sizeof(pTransferInfo->footer_ex))
        {
            fres = SdMngr_f_lseek(&fHnd, SdMngr_f_size(&fHnd) - sizeof(pTransferInfo->footer_ex));

            if (FR_OK == fres)
            {
                UINT bytes_read = 0U;

                fres = SdMngr_f_read(&fHnd, &pTransferInfo->footer_ex, sizeof(pTransferInfo->footer_ex), &bytes_read);

                if ((FR_OK == fres) && (bytes_read == sizeof(pTransferInfo->footer_ex)))
                {
                    bool ext_footer_sig_valid = (0 == memcmp(&pTransferInfo->footer_ex.ext_bun_sig[0], EXT_BUN_FOOTER_SIG, sizeof(pTransferInfo->footer_ex.ext_bun_sig)));

                    pTransferInfo->has_valid_footer = false;

                    if (ext_footer_sig_valid)
                    {
                        uint16_t ext_hdr_crc = crc16_ccitt_table((const uint8_t *) &pTransferInfo->footer_ex, sizeof(pTransferInfo->footer_ex) - sizeof(pTransferInfo->footer_ex.ext_bun_crc));

                        if (ext_hdr_crc == pTransferInfo->footer_ex.ext_bun_crc)
                        {
                            pTransferInfo->has_valid_footer = ('\0' != pTransferInfo->footer_ex.file_name[0]);
                            footer_size = sizeof(pTransferInfo->footer_ex);
                        }
                    }
                }
            }
        }
    }

    (void) SdMngr_f_close(&fHnd);

    return footer_size;
}

/**
 * @brief The structure describes the registered file handlers in the OBC
 */
typedef struct
{
	const char * const uppercase_ext;		/**< a string specifying the file extension in uppercase (without the dot symbol '.') */
	const char * const lowercase_ext;		/**< a string specifying the file extension in lowercase (without the dot symbol '.') */
	p_file_handler_t p_file_ext_handler;	/**< a pointer to the file handler function to call if the file name extension matches the entry in this table */
} file_ext_map_t;

/**
 * @brief Defines the list of file extension handlers in the OBC
 */
static const file_ext_map_t file_ext_map[EXT_MAP_ENTRIES_CNT] =
{
	{ .uppercase_ext = "TLE", .lowercase_ext = "tle", .p_file_ext_handler = &tle_handler },
	{ .uppercase_ext = "LZ7", .lowercase_ext = "lz7", .p_file_ext_handler = &lz7_handler },
	{ .uppercase_ext = "BIN", .lowercase_ext = "bin", .p_file_ext_handler = &bin_handler },
};

/**
 * @brief The function parses the received file extension and calls its corresponding handler (if registered).
 *
 * @param[in] p_file_name Name of the received file via the FWUPD protocol
 */
static void handle_file_ext(const char * const p_file_name)
{
	bool ext_handler_found = false;

	if (NULL != p_file_name)
	{
		const char *p_dot_pos = strchr(p_file_name, '.');
		const char *p_str_end = strchr(p_file_name, '\0');

		if ((NULL != p_dot_pos) && (NULL != p_str_end) && (p_str_end > p_dot_pos) &&
			(((uint32_t) p_str_end - (uint32_t) p_dot_pos - 1U) <= EXT_MAX_SIZE))
		{
			for (uint8_t file_ext_idx = 0; file_ext_idx < CDEF_ELEMENT_COUNT(file_ext_map); file_ext_idx++)
			{
				if ((0 == strcmp(p_dot_pos + 1, file_ext_map[file_ext_idx].uppercase_ext)) ||
					(0 == strcmp(p_dot_pos + 1, file_ext_map[file_ext_idx].lowercase_ext)))
				{
					p_file_handler_t fhnd = file_ext_map[file_ext_idx].p_file_ext_handler;

					if (NULL != fhnd)
					{
						(*fhnd)(p_file_name);
					}

					ext_handler_found = true;

					break;
				}
			}
		}

		if (!ext_handler_found)
		{
			default_file_handler(p_file_name);
		}
	}
}

/**
 * @brief This is the default file handler called when the file name extension was not
 *        recognized as a supported extension
 *
 * @param[in] p_file_name name of the received file on the SD card
 */
static void default_file_handler(const char * const p_file_name)
{
	ES_TRACE_DEBUG("No handler registered for received file: `%s`\r\n", p_file_name);
}

/**
 * @brief This is a Two-line-element file (.TLE) handler
 *
 * @param[in] p_file_name name of the received file on the SD card
 */
static void tle_handler(const char * const p_file_name)
{
	TleUpdateFromFile(p_file_name);
}

/**
 * @brief This is an LZ7 archive file handler which decompresses the file after it has
 *        been received.
 *
 * @param[in] p_file_name name of the received file on the SD card
 */
static void lz7_handler(const char * const p_file_name)
{
    LZ77_Init();
    LZ77_Decompress((char *) aTempImageFileName, p_file_name, 60000);

    // the LZ77 decompression will create the actual fileName, the following call performs only
    // cleanup of temporary files when argument is set to NULL
    (void) FWUPD_Persistor_PrepareImage(NULL);
}

/**
 * @brief This is a payload scheduler binary file handler which trigger reloading of the
 *        schedule if a new file has been uploaded to the SD card.
 *
 * @param[in] p_file_name name of the received file on the SD card
 */
static void bin_handler(const char * const p_file_name)
{
	PayloadScheduler_Reload(p_file_name);
}

/**
 * @brief This function is called whenever a new FWUPD bundle file is received by the OBC and is ready to be processed
 *
 * @param[in] pTransferInfo Transfer information context structure filled-in during file reception
 * @param[in] u64ActiveTransferId ID of the current transfer provided by the Ground Station
 * @param[in] pFileName name of the temporary file stored on the SD card
 *
 * @return true: the received bundle is valid and handled correctly; false - otherwise
 */
bool FWUPD_Handler_Cfg_HandleTransferComplete(sTransferInfo_t * const pTransferInfo,
                                              const uint64_t u64ActiveTransferId,
                                              const char * const pFileName)
{
    bool bTransferHandled = false;
    eFwUpdPersistorResult finalizeTransferRes;

    (void) u64ActiveTransferId;

    if ((pTransferInfo != NULL) && (pFileName != NULL))
    {
        const SESSoftwareUPD_Bundle * const psHeader = &pTransferInfo->header;
        uint32_t num_bytes_to_strip = 4U;    // uint32_t FWUPD bundle CRC size at the end of the bundle file

        // process and skip file footer if it exists
        num_bytes_to_strip += process_file_footer(pFileName, pTransferInfo);

        // remove any extra bytes added by GS in the update bundle
        finalizeTransferRes = FWUPD_Persistor_FinalizeTransfer(num_bytes_to_strip);

        if (finalizeTransferRes == EFWUPDPERSISTORRESULT_OK)
        {
            if ((psHeader->nModuleType == FW_OBC_MODULE_TYPE1) ||
                (psHeader->nModuleType == FW_OBC_MODULE_TYPE2))
            {
                switch (psHeader->nSubModule)
                {
                    // regular OBC update bundle received
                    case FW_OBC_SUBMODULE_SELF:
                    {
                        if (FWUPD_Persistor_PrepareImage(BOOTLDR_AUTOFLASH_FILE_PATH) == EFWUPDPERSISTORRESULT_OK)
                        {
                            // Switch to Bootloader mode to perform the actual flashing...
                            WriteHandler_ResetInBootOrAppMode(APPMODE_AUTO_FW_UPDATE);

                            bTransferHandled = true;
                        }
                        else
                        {
                            EXEH_HANDLE(eEXEHSeverity_Warning, EXC_FWUPD_COULD_NOT_PREPARE_IMAGE);
                        }

                        break;
                    }

                    // Specific files received
                    case FW_OBC_SUBMODULE_FILE:
                    {
                        char fileName[FWUPD_MAX_FILE_NAME_SIZE] = { '\0' };

                        if (true == pTransferInfo->has_valid_footer)
                        {
                            uint16_t hdr_ex_fname_sz = (uint16_t) strlen((const char *) pTransferInfo->footer_ex.file_name);

                            if (hdr_ex_fname_sz <= sizeof(fileName))
                            {
                                (void) memcpy(fileName, pTransferInfo->footer_ex.file_name, hdr_ex_fname_sz);
                                fileName[hdr_ex_fname_sz] = '\0';
                            }
                            else
                            {
                                (void) memcpy(fileName, pTransferInfo->footer_ex.file_name, sizeof(fileName));
                                fileName[sizeof(fileName) - 1] = '\0';
                            }
                        }

                        if (SESUL_FL_ARCHIVED == (psHeader->nFlags & SESUL_FL_ARCHIVED))
                        {
                            if (false == pTransferInfo->has_valid_footer)
                            {
                                snprintf(fileName, sizeof(fileName), "%sup_%05d.lz7", FWUPD_Persistor_GetStorageDir(), psHeader->nFWVerMaj);
                            }

                            LZ77_Init();
                            LZ77_Decompress((char *) aTempImageFileName, fileName, 60000);

                            // the LZ77 decompression will create the actual fileName, the following call performs only
                            // cleanup of temporary files when argument is set to NULL
                            (void) FWUPD_Persistor_PrepareImage(NULL);
                        } else if (SESUL_FL_FILE_TLE == (psHeader->nFlags & SESUL_FL_FILE_TLE))
                        {
                            if (false == pTransferInfo->has_valid_footer)
                            {
                                snprintf(fileName, sizeof(fileName), "%ssat.tle", FWUPD_Persistor_GetStorageDir());
                            }

                            (void) FWUPD_Persistor_PrepareImage(fileName);
                            TleUpdateFromFile(fileName);
                        } else if (SESUL_FL_PAYLOAD_SCHEDULE == (psHeader->nFlags & SESUL_FL_PAYLOAD_SCHEDULE))
                        {
                            if (false == pTransferInfo->has_valid_footer)
                            {
                                snprintf(fileName, sizeof(fileName), "%s%s", FWUPD_Persistor_GetStorageDir(), "paysched.bin");
                            }

                            (void) FWUPD_Persistor_PrepareImage(fileName);
                            PayloadScheduler_Reload(fileName);
                        } else if (SESUL_FL_FILE_ZIP == (psHeader->nFlags & SESUL_FL_FILE_ZIP))
                        {
                            if (false == pTransferInfo->has_valid_footer)
                            {
                                snprintf(fileName, sizeof(fileName), "%sup_%05d.zip", FWUPD_Persistor_GetStorageDir(), psHeader->nFWVerMaj);
                            }

                            (void) FWUPD_Persistor_PrepareImage(fileName);
                        } else if (SESUL_FL_FILE_CMD == (psHeader->nFlags & SESUL_FL_FILE_CMD))
                        {
                            if (false == pTransferInfo->has_valid_footer)
                            {
                                snprintf(fileName, sizeof(fileName), "%sup_%05d.cmd", FWUPD_Persistor_GetStorageDir(), psHeader->nFWVerMaj);
                            }

                            (void) FWUPD_Persistor_PrepareImage(fileName);
                        } else
                        {
                            if (false == pTransferInfo->has_valid_footer)
                            {
                                snprintf(fileName, sizeof(fileName), "%sup_%05d.upl", FWUPD_Persistor_GetStorageDir(), psHeader->nFWVerMaj);
                            }

                            (void) FWUPD_Persistor_PrepareImage(fileName);

                            handle_file_ext(fileName);
                        }

                        bTransferHandled = true;
                        break;
                    }

                    default:
                        EXEH_HANDLE(eEXEHSeverity_Warning, EXC_FWUPD_UNSUPPORTED_IMAGE_TYPE);
                    break;
                }
            }
        }
        else
        {
            EXEH_HANDLE(eEXEHSeverity_Warning, EXC_FWUPD_COULD_NOT_FINALIZE_IMAGE);
        }
    }
    else
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, EXC_FWUPD_INVALID_ARGS);
    }

    return bTransferHandled;
}
