/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/** @addtogroup service_adcs_tlm
  * @{
  *
  * @file     adcs_tlm.c
  * @brief    The ADCS telemetry service core logic
  *
  * @}
  */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/

#include "AppTasks.h"
#include "TaskMonitor.h"

#include "adcs_tlm.h"
#include "adcs_tlm_cfg.h"

#include "cubeadcs.h"
#include "if_sys_conf.h"

#include <string.h>

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

#ifndef COUNT_OF
/** @brief Macro to return the size of an array of maximum element count 255 */
#define COUNT_OF(x) ((uint8_t) (sizeof(x) / sizeof(x[0])))
#endif  // #ifndef COUNT_OF
/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/
/* No External variables definition */

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
/** @brief The ADCS telemetry task handle */
static       osThreadId_t   ADCS_TLM_Task_TaskHandle;
/** @brief The ADCS telemetry task attributes */
static const osThreadAttr_t ADCS_TLM_Task_attributes = {
  .name = "fs_ADCS_TLM_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048
};

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

static void fs_adcs_tlm_task(void *arg);

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
void ADCS_TLM_TaskInit(void)
{
    ADCS_TLM_Task_TaskHandle = osThreadNew(fs_adcs_tlm_task, NULL, &ADCS_TLM_Task_attributes);
    CRIT_ASSERT( ADCS_TLM_Task_TaskHandle );

    TaskMonitor_TaskInitialized(TASK_ADCS_TLM);
    task_mon_set_task_policy(TASK_ADCS_TLM, TASK_MON_POLICY_MONITOR);
}

void ADCS_TLM_TaskDeInit(void)
{
    task_mon_set_task_policy(TASK_ADCS_TLM, TASK_MON_POLICY_DONT_CARE);
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief The ADCS Telemetry Task
 *
 *  @param[in] arg pointer to task arguments
 */
static void fs_adcs_tlm_task(void *arg)
{
    for(;;)
    {
        const uint8_t data_buff_size = sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS) ? 100 : 50;
        uint8_t u8Data[data_buff_size];
        uint8_t *pu8Data;

        uint16_t u16CmdRspLen;

        CubeADCS_CmdCfg_t sCmdStruct;

        if ( (eCUBEADCS_STATE_IDLE == CubeADCS_GetState() ) &&
                (eCUBEADCS_FTRANSF_STATE_IDLE == CubeADCS_FTransfer_GetTaskState() ) )
        {
            uint8_t u8TLMIndx;

            for (uint8_t u8Indx= 0; u8Indx < ( (uint8_t)(sizeof(au8CubeADCS_TLM)/sizeof(au8CubeADCS_TLM[0])) ); u8Indx++)
            {
                pu8Data = &u8Data[0];
                for (u8TLMIndx = 0; u8TLMIndx < au8CubeADCS_TLM[u8Indx].u8CmdListSize; u8TLMIndx++)
                {
                    CubeADCS_PREPCmd(
                            &sCmdStruct,
                            au8CubeADCS_TLM[u8Indx].pu8CmdList[u8TLMIndx].u8ID,
                            NULL,
                            0,
                            (void *)pu8Data,
                            au8CubeADCS_TLM[u8Indx].pu8CmdList[u8TLMIndx].u8Size,
                            &u16CmdRspLen);

                    if ( eCUBEADCS_COMM_OK != CubeADCS_SendCmd(&sCmdStruct, eCUBEADCS_COMMREQTYPE_FETCH) )
                    {
                        break;
                    }
                    else
                    {
                        /* Each telemetry is received prefixed with the telemetry ID from the ADCS.
                         * It has to be removed as it is not part of the data cache relevant data */
                        for ( uint8_t u8BIndx = 0; u8BIndx < au8CubeADCS_TLM[u8Indx].pu8CmdList[u8TLMIndx].u8Size - 1; u8BIndx++ )
                        {
                            *pu8Data = *(pu8Data + 1);
                            pu8Data++;
                        }
                    }
                }

                if ( u8TLMIndx == au8CubeADCS_TLM[u8Indx].u8CmdListSize )
                {

                    ADCS_TLM_CFG_Update_DCache(au8CubeADCS_TLM[u8Indx].eDCacheType, &u8Data[0]);
                }
            }
        }

        osDelay(ADCS_TLM_TASK_PERIOD_MS);

        TaskMonitor_IamAlive(TASK_ADCS_TLM);
        vApplicationLowStackCheck(TASK_ADCS_TLM);
    }
}

/* ******************************************************************************************* */
