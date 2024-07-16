/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_tim.c
 * @brief    Timer helper module for MAC layer
 *
 * @}
 */

// External imports
#include "esps_drv_tim_config.h"

#include "esps_drv_tim.h"
#include "esps_drv_ct.h"
#include "esps_drv_cdef.h"
#include "esps_drv_exeh.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_MAC_TIM)

/// Callback for the timers
static void fs_vProcessExpiration(eTIMTimerID_t fp_eTIMID);

/// Interrupt handler for the MAC Driver RX and TX timers
void MAC_TIM_IRQ_Handler_Generic(TIM_TypeDef * fp_sTimBase, eTIMTimerID_t fp_eTimId)
{
    if(LL_TIM_IsActiveFlag_UPDATE(fp_sTimBase) && LL_TIM_IsEnabledIT_UPDATE(fp_sTimBase))
    {
        fs_vProcessExpiration(fp_eTimId);

        LL_TIM_ClearFlag_UPDATE(fp_sTimBase);
    }
}

/// initialize hardware timers
bool MAC_TIM_bInit(void)
{
    uint32_t u32TIMIdx;

    for(u32TIMIdx = 0U; u32TIMIdx < CDEF_ELEMENT_COUNT(TIM_CFG_asTimerEntries); u32TIMIdx++)
    {
        NVIC_EnableIRQ(TIM_CFG_asTimerEntries[u32TIMIdx].u32NVICInterrupt);

        HAL_NVIC_SetPriority(TIM_CFG_asTimerEntries[u32TIMIdx].u32NVICInterrupt, TIMER_ISR_PRIO, u32TIMIdx);

        MAC_RCC_vPeripheralClockEnable(TIM_CFG_asTimerEntries[u32TIMIdx].eClockSrc,
                                       TIM_CFG_asTimerEntries[u32TIMIdx].u32ClockMask);

        LL_TIM_SetPrescaler(TIM_CFG_asTimerEntries[u32TIMIdx].psTIM,
                            MacCfg_TIM_u16CalculatePrescaler(&TIM_CFG_asTimerEntries[u32TIMIdx]));

        LL_TIM_DisableCounter(TIM_CFG_asTimerEntries[u32TIMIdx].psTIM);

        LL_TIM_DisableIT_UPDATE(TIM_CFG_asTimerEntries[u32TIMIdx].psTIM);

    }

    return true;
}

/// Deinitialize timers
bool MAC_TIM_bDeinit(void)
{
    uint32_t u32TIMIdx;

    for(u32TIMIdx = 0U; u32TIMIdx < CDEF_ELEMENT_COUNT(TIM_CFG_asTimerEntries); u32TIMIdx++)
    {
        NVIC_DisableIRQ(TIM_CFG_asTimerEntries[u32TIMIdx].u32NVICInterrupt);
        MAC_RCC_vPeripheralClockDisable(TIM_CFG_asTimerEntries[u32TIMIdx].eClockSrc,
                                        TIM_CFG_asTimerEntries[u32TIMIdx].u32ClockMask);

        LL_TIM_DisableIT_UPDATE(TIM_CFG_asTimerEntries[u32TIMIdx].psTIM);
    }

    return true;
}

/// Start a timer in micro seconds
void MAC_TIM_vMicroTimerStart(eTIMTimerID_t fp_eTIM, uint32_t fp_u32Timeout, pfTIMCallback_t fp_pfCallback,
                              void *fp_pvData)
{
    sTIMTimerEntry_t *psTIM;

    if((fp_pfCallback == NULL) || (fp_u32Timeout == 0U) || (fp_eTIM >= eTIM_TIM_ID_Count))
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        psTIM = &TIM_CFG_asTimerEntries[fp_eTIM];

        if(psTIM->bRunning)
        {
            EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_TIMUsed);
        }
        else
        {
            psTIM->bRunning = true;

            psTIM->pfCallback = fp_pfCallback;
            psTIM->pvData = fp_pvData;
            LL_TIM_SetAutoReload(psTIM->psTIM,
                                 (fp_u32Timeout <=
                                  MAX_TIMER_RANGE_US) ? ((uint16_t) fp_u32Timeout) : ((uint16_t) MAX_TIMER_RANGE_US));
            LL_TIM_SetCounter(psTIM->psTIM, 0U);
            LL_TIM_EnableCounter(psTIM->psTIM);
            LL_TIM_ClearFlag_UPDATE(psTIM->psTIM);
            LL_TIM_EnableIT_UPDATE(psTIM->psTIM);
        }
    }
}

/// Get the elapsed time for a given timer
uint32_t MAC_TIM_vMicroTimerGetElapsed(eTIMTimerID_t fp_eTIM)
{
    return (fp_eTIM < eTIM_TIM_ID_Count) ? (LL_TIM_GetCounter(TIM_CFG_asTimerEntries[fp_eTIM].psTIM)) : ((uint32_t) 0);
}

/// Cancel a timer
void MAC_TIM_vMicroTimerCancel(eTIMTimerID_t fp_eTIM, bool fp_bSuppressCancelCbk)
{
    pfTIMCallback_t pfCallback = (pfTIMCallback_t) NULL;

    void *pvData = (void *)NULL;

    if(fp_eTIM >= eTIM_TIM_ID_Count)
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        if(TIM_CFG_asTimerEntries[fp_eTIM].bRunning)
        {
            pfCallback = TIM_CFG_asTimerEntries[fp_eTIM].pfCallback;
            pvData = TIM_CFG_asTimerEntries[fp_eTIM].pvData;

            LL_TIM_DisableCounter(TIM_CFG_asTimerEntries[fp_eTIM].psTIM);

            TIM_CFG_asTimerEntries[fp_eTIM].bRunning = false;
            TIM_CFG_asTimerEntries[fp_eTIM].pfCallback = NULL;
            TIM_CFG_asTimerEntries[fp_eTIM].pvData = NULL;

            if((pfCallback) && (!fp_bSuppressCancelCbk))
            {
                pfCallback(eTIMTimer_Canceled, pvData);
            }
        }
    }
}

bool MAC_TIM_vGetTimerIsrStateById(eTIMTimerID_t fp_eTIM)
{
    if(fp_eTIM >= eTIM_TIM_ID_Count)
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        return NVIC_GetEnableIRQ(TIM_CFG_asTimerEntries[fp_eTIM].u32NVICInterrupt);
    }

    return false;
}

/// Set the timers ISR
void MAC_TIM_vSetTimerIsrStateById(eTIMTimerID_t fp_eTIM, bool fp_bEnabled)
{
    if(fp_eTIM >= eTIM_TIM_ID_Count)
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        if(fp_bEnabled)
            NVIC_EnableIRQ(TIM_CFG_asTimerEntries[fp_eTIM].u32NVICInterrupt);
        else
            NVIC_DisableIRQ(TIM_CFG_asTimerEntries[fp_eTIM].u32NVICInterrupt);
    }
}

/// Callback for the timers
static void fs_vProcessExpiration(eTIMTimerID_t fp_eTIMID)
{
    pfTIMCallback_t pfCallback = TIM_CFG_asTimerEntries[fp_eTIMID].pfCallback;

    void *pvData = TIM_CFG_asTimerEntries[fp_eTIMID].pvData;

    LL_TIM_DisableCounter(TIM_CFG_asTimerEntries[fp_eTIMID].psTIM);
    LL_TIM_SetCounter(TIM_CFG_asTimerEntries[fp_eTIMID].psTIM, 0U);
    LL_TIM_DisableIT_UPDATE(TIM_CFG_asTimerEntries[fp_eTIMID].psTIM);

    if((TIM_CFG_asTimerEntries[fp_eTIMID].bRunning) && (TIM_CFG_asTimerEntries[fp_eTIMID].pfCallback))
    {
        TIM_CFG_asTimerEntries[fp_eTIMID].pfCallback = NULL;
        TIM_CFG_asTimerEntries[fp_eTIMID].pvData = NULL;
        TIM_CFG_asTimerEntries[fp_eTIMID].bRunning = false;

        pfCallback(eTIMTimer_Expired, pvData);
    }
}
