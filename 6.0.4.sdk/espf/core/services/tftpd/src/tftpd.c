/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#include <stdio.h>

#include "lwip/apps/tftp_client.h"
#include "lwip/apps/tftp_server.h"
#include <string.h>
#include "../inc/tftpd.h"
#include "SdMngr.h"
#include "trace.h"

#if LWIP_UDP

#define MAX_OPENED_HANDLES  (1)

/* Define a base directory for TFTP access
 * ATTENTION: This code does NOT check for sandboxing,
 * i.e. '..' in paths is not checked! */
#ifndef LWIP_TFTP_EXAMPLE_BASE_DIR
#define LWIP_TFTP_EXAMPLE_BASE_DIR ""
#endif

/* Define this to a file to get via tftp client */
#ifndef LWIP_TFTP_EXAMPLE_CLIENT_FILENAME
#define LWIP_TFTP_EXAMPLE_CLIENT_FILENAME "test.bin"
#endif

/* Define this to a server IP string */
#ifndef LWIP_TFTP_EXAMPLE_CLIENT_REMOTEIP
#define LWIP_TFTP_EXAMPLE_CLIENT_REMOTEIP "192.168.0.1"
#endif

static char full_filename[FF_LFN_BUF];
static FIL fhnd_pool[MAX_OPENED_HANDLES];

static FIL *get_free_file_hnd(void)
{
    FIL *p_hnd = NULL;

    for (uint8_t i = 0; i < CDEF_ELEMENT_COUNT(fhnd_pool); i++)
    {
        if (NULL == fhnd_pool[i].obj.fs)
        {
            p_hnd = &fhnd_pool[i];
            break;
        }
    }

    return p_hnd;
}

static void *tftp_open_file(const char* fname, u8_t is_write)
{
    FIL *p_fhnd = NULL;
    FRESULT fres;

    p_fhnd = get_free_file_hnd();

    if (NULL != p_fhnd)
    {
    	(void) memset(full_filename, 0U, sizeof(full_filename));
        snprintf(full_filename, sizeof(full_filename), "%s%s", LWIP_TFTP_EXAMPLE_BASE_DIR, fname);
        full_filename[sizeof(full_filename) - 1] = 0;

        if (is_write)
        {
            fres = SdMngr_f_open(p_fhnd, full_filename, FA_WRITE | FA_CREATE_ALWAYS);
        }
        else
        {
            fres = SdMngr_f_open(p_fhnd, full_filename, FA_READ | FA_OPEN_EXISTING);
        }

        if (FR_OK != fres)
        {
            ES_TRACE_ERROR("could not open file with error: %d\r\n", fres);
            p_fhnd = NULL;
        }
        else
        {
        	ES_TRACE_INFO("'%s' file successfully opened!\r\n", full_filename);
        }
    }

    return p_fhnd;
}

static uint32_t max_size = 0;

static void* tftp_open(const char* fname, const char* mode, u8_t is_write)
{
  LWIP_UNUSED_ARG(mode);
  max_size = 0;
  return tftp_open_file(fname, is_write);
}

static void tftp_close(void* handle)
{
    (void) SdMngr_f_close((FIL *) handle);

    // invalidate handle (just in case)
    ((FIL *) handle)->obj.fs = NULL;
}

static int tftp_read(void* handle, void* buf, int bytes)
{
    UINT bytes_read = -1;
    FRESULT fres;

    fres = SdMngr_f_read((FIL *) handle, buf, bytes, &bytes_read);

	if (FR_OK != fres)
	{
		bytes_read = -1;
	}

    return (int) bytes_read;
}

static int tftp_write(void* handle, struct pbuf* p)
{
    UINT bytes_written = -1;
    FRESULT fres;

    while (p != NULL)
    {
        fres = SdMngr_f_write((FIL *) handle, p->payload, p->len, &bytes_written);

        if (FR_OK != fres)
        {
            bytes_written = -1;
            break;
        }

        p = p->next;
    }

    return (int) bytes_written;
}

/* For TFTP client only */
static void tftp_error(void* handle, int err, const char* msg, int size)
{
    char message[100];

    LWIP_UNUSED_ARG(handle);

    memset(message, 0, sizeof(message));
    MEMCPY(message, msg, LWIP_MIN(sizeof(message)-1, (size_t)size));

    printf("TFTP error: %d (%s)", err, message);
}

static const struct tftp_context tftp = {
    tftp_open,
    tftp_close,
    tftp_read,
    tftp_write,
    tftp_error
};

void tftpd_init_server(void)
{
    for (uint8_t i = 0; i < CDEF_ELEMENT_COUNT(fhnd_pool); i++)
    {
        fhnd_pool[i].obj.fs = NULL;
    }

    tftp_init_server(&tftp);
}

void tftpd_init_client(void)
{
    void *f;
    err_t err;
    ip_addr_t srv;
    int ret = ipaddr_aton(LWIP_TFTP_EXAMPLE_CLIENT_REMOTEIP, &srv);
    LWIP_ASSERT("ipaddr_aton failed", ret == 1);

    err = tftp_init_client(&tftp);
    LWIP_ASSERT("tftp_init_client failed", err == ERR_OK);

    f = tftp_open_file(LWIP_TFTP_EXAMPLE_CLIENT_FILENAME, 1);
    LWIP_ASSERT("failed to create file", f != NULL);

    err = tftp_get(f, &srv, TFTP_PORT, LWIP_TFTP_EXAMPLE_CLIENT_FILENAME, TFTP_MODE_OCTET);
    LWIP_ASSERT("tftp_get failed", err == ERR_OK);
}

#endif /* LWIP_UDP */
