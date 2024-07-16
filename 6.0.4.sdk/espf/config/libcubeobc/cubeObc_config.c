#include "cubeObc_config.h"
#include "cubeObc.h"
#include "cubeobc_uart.h"
#include "cubeobc_critical.h"
#include "cubeadcs_gen2.h"
#include "cubeadcs_gen2_transfer.h"
#include "TaskMonitor.h"
#include "trace.h"


if_sys_mod_t cube_adcs_g2_module_configuration = 
{
    .init   = cube_adcs_g2_init,
    .run    = cube_adcs_g2_run,
    .stop   = cube_adcs_g2_stop,
    .deinit = cube_adcs_g2_deinit
};


mod_op_status_id_t cube_adcs_g2_init(sys_init_level_id_t level)
{
    mod_op_status_id_t ret;
    CubeObc_Config obc_config;

    switch (level)
    {
        case INIT_MEM:
        case INIT_HW:

            ret = STATUS_OK;

            break;
        case INIT_OS:
            obc_config.hostAddress = 1;

            if ((false == cubeobc_critical_init()) ||
                (false == cubeobc_uart_init()) ||
                (CUBEOBC_ERROR_OK != cubeObc_init(&obc_config)) ||
                (CUBEOBC_ERROR_OK != cubeadcs_gen2_transfer_init()))
            {
                ES_TRACE_ERROR("init");
            }

            cubeadcs_gen2_os_init();
            
            ret = STATUS_OK;

            break;
        default:
            ret = STATUS_NOT_SUPPORTED;
            break;
    }

    return ret;
}


mod_op_status_id_t cube_adcs_g2_run(void)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}


mod_op_status_id_t cube_adcs_g2_stop(void)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}


mod_op_status_id_t cube_adcs_g2_deinit(sys_init_level_id_t level)
{
    mod_op_status_id_t ret;

    switch (level)
    {
        case INIT_MEM:
        case INIT_HW:
        case INIT_OS:

            task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_GEN2_COMM, TASK_MON_POLICY_DONT_CARE);
            task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_GEN2_TRANSFER, TASK_MON_POLICY_DONT_CARE);

            cubeadcs_gen2_os_deinit();

            ret = STATUS_OK;

            break;
        default:
            ret = STATUS_NOT_SUPPORTED;
            break;
    }

    return ret;
}
