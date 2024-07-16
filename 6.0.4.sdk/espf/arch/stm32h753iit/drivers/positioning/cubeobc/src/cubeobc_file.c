/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "SdMngr.h"
#include "cmsis_os2.h"
#include "cubeadcs_gen2_types.h"
#include <cubeObc/cubeObc_bulkDataTransfer.h>


ErrorCode cubeObc_bulkDataTransfer_getFrameBuffer(void* userData, U8** frame, U16 size)
{
    ErrorCode result = CUBEOBC_ERROR_FRAME;
    cubeadcs_gen2_file_context_t* h = (cubeadcs_gen2_file_context_t*)userData;
    UINT br = 0;

    switch (h->context)
    {
        case CUBEADCS_GEN2_BDT_CTX_FTP_BL:
        case CUBEADCS_GEN2_BDT_CTX_FTP_AP:
        {
            if (CUBEADCS_GEN2_FILE_SZ_LIMIT > h->file_seek_index)
            {
                if (FR_OK == SdMngr_f_open(&h->file_handle, h->file_name, FA_OPEN_EXISTING | FA_READ))
                {
                    if ((FR_OK == SdMngr_f_lseek(&h->file_handle, h->file_seek_index)) &&
                        (FR_OK == SdMngr_f_read(&h->file_handle, h->frame_buffer, size, &br)))
                    {
                        if (br != size)
                        {
                            result = CUBEOBC_ERROR_SIZE;
                        }
                        else
                        {
                            result = CUBEOBC_ERROR_OK;
                        }

                        *frame = h->frame_buffer;

                        h->last_frame_size = size;
                    }

                    (void)SdMngr_f_close(&h->file_handle);
                }
            }
            else
            {
                result = CUBEOBC_ERROR_SIZE;
            }
        } break;

        case CUBEADCS_GEN2_BDT_CTX_IMG_CC:
        case CUBEADCS_GEN2_BDT_CTX_EVT_CC:
        case CUBEADCS_GEN2_BDT_CTX_TLM_CC:
        {
            *frame = h->frame_buffer;

            h->last_frame_size = size;

            result = CUBEOBC_ERROR_OK;
        } break;

        default:
        {
            result = CUBEOBC_ERROR_USER_DATA;
        } break;
    }

    return result;
}


ErrorCode cubeObc_bulkDataTransfer_commitFrameBuffer(void* userData, U8* frame, U16 size)
{
    ErrorCode result = CUBEOBC_ERROR_COMMIT;
    cubeadcs_gen2_file_context_t* h = (cubeadcs_gen2_file_context_t*)userData;
    UINT bw = 0;

    if ((NULL != frame) &&
        (0 < size) &&
        (frame == h->frame_buffer) &&
        (size == h->last_frame_size))
    {
        switch (h->context)
        {
            case CUBEADCS_GEN2_BDT_CTX_FTP_BL:
            case CUBEADCS_GEN2_BDT_CTX_FTP_AP:
            {
                h->file_seek_index += size;
                result = CUBEOBC_ERROR_OK;
            } break;

            case CUBEADCS_GEN2_BDT_CTX_IMG_CC:
            case CUBEADCS_GEN2_BDT_CTX_EVT_CC:
            case CUBEADCS_GEN2_BDT_CTX_TLM_CC:
            {
                if (CUBEADCS_GEN2_FILE_SZ_LIMIT > h->file_seek_index)
                {
                    // Opens the file, if it is existing, in writing mode. If not, a new file will be created.
                    if (FR_OK == SdMngr_f_open(&h->file_handle, h->file_name, FA_OPEN_EXISTING | FA_WRITE))
                    {
                        // set the write pointer to the EOF and attempt to write the data
                        if ((FR_OK == SdMngr_f_lseek(&h->file_handle, h->file_seek_index)) &&
                            (FR_OK == SdMngr_f_write(&h->file_handle, h->frame_buffer, size, &bw)))
                        {
                            if (bw != size)
                            {
                                result = CUBEOBC_ERROR_SIZE;
                            }
                            else
                            {
                                h->file_seek_index += size;
                                result = CUBEOBC_ERROR_OK;
                            }
                        }

                        (void)SdMngr_f_close(&h->file_handle);
                    }
                }
                else
                {
                    result = CUBEOBC_ERROR_SIZE;
                }
            } break;

            default:
            {
                result = CUBEOBC_ERROR_USER_DATA;
            } break;
        }
    }

    return result;
}

