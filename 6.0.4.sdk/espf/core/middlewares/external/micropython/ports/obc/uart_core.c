#include <unistd.h>
#include <stdio.h>
#include "py/mpconfig.h"
#include "trace.h"
#include "string.h"
#include "sys_time.h"
#include "ff.h"

#define MAX_LINE_CHARACHERS \
    (512U) // there is no real limit, this value can be bigger if needed
#define TIME_STRING_LENGTH  (13U) // no null termination included in the length
#define NULL_CHARACHTER_LEN (1U)

static char line[MAX_LINE_CHARACHERS];

/*
 * Core UART functions to implement for a port
 */

// Receive single character
// Currently with OBC there is no input method
int
mp_hal_stdin_rx_chr(void)
{
    return 0;
}

FRESULT
upy_write_line_to_file(const char *const line);

// Send string of given length
// This interface is called from micropython implementation and could be
// invoked even for just one symbol. As we don't want to have too frequent
// writings into the file here the symbols are combined into a line and
// the line is sent to the file.
void
mp_hal_stdout_tx_strn(const char *str, mp_uint_t len)
{
    // make sure we have 0 at the end of the string
    char pstr[len + 1];
    memcpy(pstr, str, len);
    pstr[len] = '\0';

    if ('\0' == line[0])
    {
        sys_time_t sTimeStamp;
        char       time_str[TIME_STRING_LENGTH +
                      NULL_CHARACHTER_LEN]; // take into account the null
                                                  // termination
        sys_time_get(&sTimeStamp);

        snprintf(time_str, TIME_STRING_LENGTH + NULL_CHARACHTER_LEN,
                 "%02d:%02d:%02d: ", sTimeStamp.hour, sTimeStamp.min,
                 sTimeStamp.sec);

        (void)strncpy(line, time_str,
                      MAX_LINE_CHARACHERS - NULL_CHARACHTER_LEN);
    }

    if (MAX_LINE_CHARACHERS < strlen(line) + strlen(pstr))
    {
    	ES_TRACE_DEBUG(
            "Python output line truncated!!! Possible memory "
            "corruption or trying to write more characters on the line then "
            "the limit(MAX_LINE_CHARACHERS=%d)!\n",
            MAX_LINE_CHARACHERS);
    }

    (void)strncat(line, pstr,
                  MAX_LINE_CHARACHERS - strlen(line) - NULL_CHARACHTER_LEN);

    if (NULL != strchr(pstr, '\n'))
    {
    	ES_TRACE_DEBUG("%s", line);
        (void)upy_write_line_to_file(line);
        line[0] = '\0';
    }
}
