/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "cobs_inplace.h"


typedef unsigned char cobs_byte_t;


bool cobs_inplace_encode(void* buf, cobs_inplace_sz_t len)
{
    if ((!buf) || (len < 2))
    {
        return false;
    }

    cobs_byte_t* const src = (cobs_byte_t*)buf;

    if ((src[0] != COBS_INPLACE_SENTINEL_VALUE) ||
        (src[len - 1] != COBS_INPLACE_SENTINEL_VALUE))
    {
        return false;
    }

    cobs_inplace_sz_t patch = 0;
    cobs_inplace_sz_t cur = 1;
    cobs_inplace_sz_t ofs;

    while (cur < len - 1)
    {
        if (src[cur] == COBS_INPLACE_FRAME_DELIMITER)
        {
            ofs = cur - patch;

            if (ofs >= COBS_INPLACE_SAFE_BUFFER_SIZE)
            {
                return false;
            }

            src[patch] = (cobs_byte_t)ofs;
            patch = cur;
        }

        ++cur;
    }

    ofs = cur - patch;

    if (ofs >= COBS_INPLACE_SAFE_BUFFER_SIZE)
    {
        return false;
    }

    src[patch] = (cobs_byte_t)ofs;
    src[cur] = 0;

    return true;
}


bool cobs_inplace_decode(void* buf, const cobs_inplace_sz_t len)
{
    if ((!buf) || (len < 2))
    {
        return false;
    }

    cobs_byte_t* const src = (cobs_byte_t*) buf;
    cobs_inplace_sz_t ofs;
    cobs_inplace_sz_t cur = 0;

    while ((cur < len) && ((ofs = src[cur]) != COBS_INPLACE_FRAME_DELIMITER))
    {
        src[cur] = 0;

        for (cobs_inplace_sz_t i = 1; i < ofs; ++i)
        {
            if (src[cur + i] == 0)
            {
                return false;
            }
        }

        cur += ofs;
    }

    if (cur != len - 1)
    {
        return false;
    }

    src[0] = COBS_INPLACE_SENTINEL_VALUE;
    src[len - 1] = COBS_INPLACE_SENTINEL_VALUE;

    return true;
}




