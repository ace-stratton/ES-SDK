#include <sys/stat.h>
#include "cmsis_gcc.h"

//
// The following are syscall stubs required by the linker even if we don't use newlib C library in the project.
//

int _fstat(int file, struct stat *st)    // NOSONAR
{
    (void) file;

    st->st_mode = S_IFCHR;
    return 0;
}

int _lseek(int file, int offset, int whence)    // NOSONAR
{
    (void) file;
    (void) offset;
    (void) whence;

    return 0;
}

int _close(int fd)    // NOSONAR
{
    (void) fd;

    return -1;
}

int _write(int fd, char *buf, int count)    // NOSONAR
{
    (void) fd;
    (void) buf;
    (void) count;

    return 0;
}

int _read(int fd, char *buf, int count)        // NOSONAR
{
    (void) fd;
    (void) buf;
    (void) count;

    return 0;
}

void *_sbrk(int incr)    // NOSONAR
{
    (void) incr;

    return NULL;
}

int _isatty(int file)    // NOSONAR
{
    return 1;
}

void _exit(int status)    // NOSONAR
{
    (void) status;

    __BKPT(0);

    while (1)
    {
        __NOP();
    }
}

void _kill(int pid, int sig)    // NOSONAR
{
    (void) pid;
    (void) sig;
}

int _getpid(void)    // NOSONAR
{
    return -1;
}
