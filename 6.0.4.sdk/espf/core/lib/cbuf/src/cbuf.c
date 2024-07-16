/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "cbuf.h"
#include "cbuf_config.h"
#include <string.h>


void cbuf_init(cbuf_t* const cbuf, uint8_t* const buf, const uint32_t buf_sz)
{
    CBUF_ASSERT(NULL != cbuf);
    CBUF_ASSERT(NULL != buf);
    CBUF_ASSERT(0 < buf_sz);

    cbuf->buf    = buf;
    cbuf->buf_sz = buf_sz;

    cbuf_clearq(cbuf);
}


void cbuf_clearq(cbuf_t* const cbuf)
{
    CBUF_ASSERT(NULL != cbuf);

    cbuf->head  = 0;
    cbuf->tail  = 0;
    cbuf->space = cbuf_capacity(cbuf);
}


void cbuf_clear(cbuf_t* const cbuf)
{
    CBUF_ASSERT(NULL != cbuf);
    CBUF_ASSERT(NULL != cbuf->buf);

    cbuf_clearq(cbuf);

    memset(cbuf->buf, 0, cbuf_capacity(cbuf));
}


uint32_t cbuf_push(cbuf_t* const cbuf, const uint8_t* data, const uint32_t data_sz, const bool overwrite)
{
    CBUF_ASSERT(NULL != cbuf);
    CBUF_ASSERT(NULL != cbuf->buf);
    CBUF_ASSERT(NULL != data);
    CBUF_ASSERT(data_sz <= cbuf_capacity(cbuf));

    uint32_t bytes_written = 0;

    if (overwrite || (cbuf_space(cbuf) >= data_sz))
    {
        for (uint32_t i = 0; i < data_sz; i++)
        {
            if (overwrite && (cbuf->head == cbuf->tail))
            {
                cbuf->tail++;
                cbuf->space++;
                cbuf->tail %= cbuf_capacity(cbuf);
            }

            cbuf->buf[cbuf->head++] = data[i];
            cbuf->head %= cbuf_capacity(cbuf);
            bytes_written++;
            cbuf->space--;
        }
    }

    return bytes_written;
}


uint32_t cbuf_pop(cbuf_t* const cbuf, uint8_t* const data, const uint32_t data_sz)
{
    return cbuf_free(cbuf, cbuf_peek(cbuf, data, data_sz));
}


uint32_t cbuf_peek(const cbuf_t* cbuf, uint8_t* const data, const uint32_t data_sz)
{
    CBUF_ASSERT(NULL != cbuf);
    CBUF_ASSERT(NULL != cbuf->buf);

    uint32_t read_sz        = 0;
    uint32_t tail           = cbuf->tail;
    uint32_t occupied_bytes = cbuf_size(cbuf);
    uint32_t bytes_to_read  = (data_sz > occupied_bytes) ? occupied_bytes : data_sz;

    for (uint32_t i = 0; i < bytes_to_read; i++)
    {
        data[i] = cbuf->buf[tail++];
        tail %= cbuf_capacity(cbuf);
        read_sz++;
    }

    return read_sz;
}


uint32_t cbuf_free(cbuf_t* const cbuf, const uint32_t sz)
{
    CBUF_ASSERT(NULL != cbuf);
    CBUF_ASSERT(NULL != cbuf->buf);
    CBUF_ASSERT(sz <= cbuf_capacity(cbuf));

    uint32_t advance_tail;
    uint32_t removed = 0;

    if (sz <= cbuf_size(cbuf))
    {
        cbuf->space += sz;
        advance_tail = sz;
    }
    else
    {
        cbuf->space = cbuf_size(cbuf);
        advance_tail = cbuf->space;
    }

    for (uint32_t i = 0; i < advance_tail; i++)
    {
        cbuf->tail++;
        cbuf->tail %= cbuf_capacity(cbuf);
        removed++;
    }

    return removed;
}


uint32_t cbuf_capacity(const cbuf_t* cbuf)
{
    CBUF_ASSERT(NULL != cbuf);

    return cbuf->buf_sz;
}


uint32_t cbuf_space(const cbuf_t* cbuf)
{
    CBUF_ASSERT(NULL != cbuf);

    return cbuf->space;
}


uint32_t cbuf_size(const cbuf_t* cbuf)
{
    CBUF_ASSERT(cbuf_capacity(cbuf) >= cbuf_space(cbuf));

    return (cbuf_capacity(cbuf) - cbuf_space(cbuf));
}


bool cbuf_full(const cbuf_t* cbuf)
{
    return (cbuf_size(cbuf) == cbuf_capacity(cbuf));
}


bool cbuf_empty(const cbuf_t* cbuf)
{
    return (cbuf_size(cbuf) == 0);
}

