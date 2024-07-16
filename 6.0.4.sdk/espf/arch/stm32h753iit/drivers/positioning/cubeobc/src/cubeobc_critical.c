#include "cubeobc_critical.h"
#include "cmsis_os2.h"
#include "debug.h"
#include "cubeObc/arch/cubeObc_critical.h"


static osMutexId_t fs_critical_section = NULL;

#if CUBEOBC_CRITICAL_WAIT_FOREVER != osWaitForever
#error "Mismatched critical section timeout value between OS and Gen2 CubeADCS driver!"
#endif

bool cubeobc_critical_init(void)
{
    bool res = false;

    if (NULL == fs_critical_section)
    {
        osMutexAttr_t attr =
        {
            .name      = NULL,
            .attr_bits = osMutexRecursive | osMutexPrioInherit,
            .cb_mem    = NULL,
            .cb_size   = 0U
        };

        fs_critical_section = osMutexNew(&attr);

        if (NULL != fs_critical_section)
        {
            res = true;
        }
    }
    else
    {
        res = true;
    }

    return res;
}


bool cubeObc_critical_enter(const uint32_t timeout)
{
    bool op_res = false;

    if (osOK == osMutexAcquire(fs_critical_section, timeout))
    {
        op_res = true;
    }

    return op_res;
}


void cubeObc_critical_exit(void)
{
    (void)osMutexRelease(fs_critical_section);
}
