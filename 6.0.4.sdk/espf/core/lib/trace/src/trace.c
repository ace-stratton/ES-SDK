/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libtrace
 * @{
 *
 * @file trace.c
 * @brief Implementation of tracing functionality for software events.
 *
 * @}
 */
#include "trace.h"
#include "trace_defs.h"
#include "trace_config.h"
#include "cobs_inplace.h"
#include "irq.h"
#include "datetime.h"
#include "crc16-ccitt.h"
#include "sys_printf.h"
#include <stddef.h>
#include <string.h>


#define TRACE_HDR_FMT            "%.*s,%d,%.*s,%0*d,"

#define TRACE_HDR_FILENAME_SZ   (50)// Maximum number of characters for a file name.  Value chosen based on latest measured longest source file name - 47 characters
#define TRACE_HDR_LINE_SZ       (6) // Maximum number of characters for a line number. Assumption is that files with traces are unlikely to be > 999 999 lines
#define TRACE_HDR_LVL_SZ        (5)
#define TRACE_HDR_TSTAMP_SZ     (10)
#define TRACE_HDR_FMT_SZ        (TRACE_HDR_FILENAME_SZ + TRACE_HDR_LINE_SZ + TRACE_HDR_LVL_SZ + TRACE_HDR_TSTAMP_SZ + 4) // +4 because of ',' symbol

#define TRACE_FTR_FMT           ",%0*d"
#define TRACE_FTR_CRC_SZ        (5)
#define TRACE_FTR_FMT_SZ        (TRACE_FTR_CRC_SZ + 2) // +2 because of ',' and null symbols

#define TRACE_COBS_OVERHEAD     (2)
#define TRACE_COBS_FIRST_IDX    (0) // Index of the first COBS sentinel value in the bytes of a trace entry

#define TRACE_OVERHEAD_SZ       (TRACE_HDR_FMT_SZ + TRACE_FTR_FMT_SZ + TRACE_COBS_OVERHEAD)
#define TRACE_USER_SZ           (128)
#define TRACE_BUF_SZ            (TRACE_OVERHEAD_SZ + TRACE_USER_SZ)


static trace_channel_t* fs_chan_list = NULL;
static uint32_t         fs_chan_list_sz = 0;
static bool             fs_init_done = false;


void trace_init(void)
{
    trace_channel_t* chan_list = NULL;
    uint32_t chan_list_sz = 0;
    trace_config_init(&chan_list, &chan_list_sz);

    if ((NULL != chan_list) && (0 < chan_list_sz) && (true != fs_init_done))
    {
        fs_chan_list = chan_list;
        fs_chan_list_sz = chan_list_sz;

        for (uint32_t i = 0; i < chan_list_sz; i++)
        {
            trace_assert(NULL != chan_list[i].name);
            trace_assert(NULL != chan_list[i].data_send);
            trace_assert(NULL != chan_list[i].buf);
            trace_assert(0     < chan_list[i].buf_sz);

            chan_list[i].lock = trace_lock_new();

            trace_assert(NULL != chan_list[i].lock);

            cbuf_init(&chan_list[i].cbuf, chan_list[i].buf, chan_list[i].buf_sz);
        }

        fs_init_done = true;
    }
    else
    {
        trace_assert(false);
    }
}


static void fs_send_data_to_channels(const uint8_t* data, const uint32_t data_sz, const trace_level_t level, bool encoded)
{
    for (uint32_t i = 0; i < fs_chan_list_sz; i++)
    {
        if ((false != trace_get_chan_active(i)) && (encoded == fs_chan_list[i].encoded))
        {
            trace_lock_acquire(fs_chan_list[i].lock);

            // Check if the severity level of the entry is allowed on this channel
            if (TRACE_LVL_ENABLED(fs_chan_list[i].levels, level))
            {
                (void)cbuf_push(&fs_chan_list[i].cbuf, data, data_sz, false);
            }

            trace_lock_release(fs_chan_list[i].lock);
        }
    }
}

void trace(const char* const filename, const int32_t line, trace_level_t lvl, const char* fmt, ...)
{
    static const char* lvl_str[TRACE_LVL_COUNT] =
    { "INFO", "WARN", "ERROR", "FATAL", "DEBUG" };

    if ((false == irq_active()) &&
        (NULL != filename) &&
        (TRACE_LVL_COUNT > lvl) &&
        (NULL != fmt) &&
        (false != fs_init_done))
    {
        // local buffer to format user data
        uint8_t trc_buf[TRACE_BUF_SZ];
        uint32_t trc_sz = 0;

        // 1st byte set as required by COBS implementation
        trc_buf[trc_sz++] = COBS_INPLACE_SENTINEL_VALUE;

        // add header in readable format
        int ret = sys_snprintf(
            (char*)&trc_buf[trc_sz], TRACE_HDR_FMT_SZ,
            TRACE_HDR_FMT,
            TRACE_HDR_FILENAME_SZ, filename,
            line,
            TRACE_HDR_LVL_SZ, lvl_str[lvl],
            TRACE_HDR_TSTAMP_SZ, datetime_to_unix_now());

        ret = (ret > 0) ? ret : 0;
        trc_sz += ret;

        // add user data in readable format
        va_list va;
        va_start(va, fmt);

        ret = sys_vsnprintf((char*)&trc_buf[trc_sz], TRACE_USER_SZ, fmt, va);
        ret = (ret > 0) ? ret : 0;
        trc_sz += (ret > TRACE_USER_SZ) ? TRACE_USER_SZ : ret;

        va_end(va);

        // send data to the active channels without encoding
        fs_send_data_to_channels(
                &trc_buf[TRACE_COBS_FIRST_IDX + 1], trc_sz - 1, lvl, false);

        // calculate data crc, format and append it
        uint16_t trc_crc = crc16_ccitt_calc(
                &trc_buf[TRACE_COBS_FIRST_IDX + 1], trc_sz - 1);

        ret = sys_snprintf(
            (char*)&trc_buf[trc_sz], TRACE_FTR_FMT_SZ,
            TRACE_FTR_FMT, TRACE_FTR_CRC_SZ, trc_crc);

        ret = (ret > 0) ? ret : 0;
        trc_sz += ret;

        // last byte set as required by COBS implementation
        trc_buf[trc_sz++] = COBS_INPLACE_SENTINEL_VALUE;

        trace_assert(COBS_INPLACE_SAFE_BUFFER_SIZE >= trc_sz);

        // send data to the active channels with encoding
        if (cobs_inplace_encode(trc_buf, trc_sz))
        {
            fs_send_data_to_channels(trc_buf, trc_sz, lvl, true);
        }
        else
        {
            trace_assert(false);
        }
    }
}


void trace_serve_chan(const uint32_t channel, uint8_t* buf, const uint32_t buf_sz)
{
    trace_assert(fs_init_done);
    trace_assert(NULL != buf);
    trace_assert(fs_chan_list_sz > channel);

    trace_channel_t* chan = &fs_chan_list[channel];

    trace_lock_acquire(chan->lock);

    uint32_t read_sz = cbuf_peek(&chan->cbuf, buf, buf_sz);

    trace_lock_release(chan->lock);

    uint32_t sent_sz = 0;

    if ((0 < read_sz) && (buf_sz >= read_sz))
    {
        sent_sz = chan->data_send(buf, read_sz);
    }

    if (0 < sent_sz)
    {
        trace_lock_acquire(chan->lock);

        (void)cbuf_free(&chan->cbuf, sent_sz);

        trace_lock_release(chan->lock);
    }
}


bool trace_get_chan_active(const uint32_t channel)
{
    trace_assert(fs_init_done);
    trace_assert(fs_chan_list_sz > channel);

    bool active;

    trace_lock_acquire(fs_chan_list[channel].lock);

    active = fs_chan_list[channel].active;

    trace_lock_release(fs_chan_list[channel].lock);

    return active;
}


const char* trace_get_chan_name(const uint32_t channel)
{
    trace_assert(fs_init_done);
    trace_assert(fs_chan_list_sz > channel);

    return fs_chan_list[channel].name;
}
