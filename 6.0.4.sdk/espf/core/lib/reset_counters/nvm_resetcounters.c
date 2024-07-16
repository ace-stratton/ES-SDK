/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup reset_counters
 * @{
 *
 * @file nvm_resetcounters.c
 * @brief Main implementation
 *
 * @}
 */

#include "nvm_resetcounters.h"
#include "nvm/inc/nvm.h"
#include "stm32h7xx_hal.h"
#include "trace.h"

bool NvmResetCounters_ClearCounter(RstCounterId_t cntrId)
{
    bool res = true;
    boot_struct BootData;

    Nvm_GetBlockById(NVM_BLOCK_BOOTDATA, &BootData);

    switch(cntrId)
    {
        case RSTCOUNTERID_WWD:
            BootData.RST_WWD = 0;
        break;

        case RSTCOUNTERID_IWD:
            BootData.RST_IWD = 0;
        break;

        case RSTCOUNTERID_LPR:
            BootData.RST_LPR = 0;
        break;

        case RSTCOUNTERID_POR:
            BootData.RST_POR = 0;
        break;

        case RSTCOUNTERID_RSTPIN:
            BootData.RST_RstPin = 0;
        break;

        case RSTCOUNTERID_BOR:
            BootData.RST_BOR = 0;
        break;

        case RSTCOUNTERID_HARDFAULT:
            BootData.RST_HardFault  = 0;
        break;

        case RSTCOUNTERID_MEMFAULT:
            BootData.RST_MemFault   = 0;
        break;

        case RSTCOUNTERID_BUSFAULT:
            BootData.RST_BusFault   = 0;
        break;

        case RSTCOUNTERID_USAGEFAULT:
            BootData.RST_UsageFault = 0;
        break;

        case RSTCOUNTERID_ALL:
            BootData.RST_WWD = 0;
            BootData.RST_IWD = 0;
            BootData.RST_LPR = 0;
            BootData.RST_POR = 0;
            BootData.RST_RstPin = 0;
            BootData.RST_BOR = 0;

            BootData.RST_HardFault  = 0;    /* HardFault_Handler()  */
            BootData.RST_MemFault   = 0;    /* MemManage_Handler()  */
            BootData.RST_BusFault   = 0;    /* BusFault_Handler()   */
            BootData.RST_UsageFault = 0;    /* UsageFault_Handler() */
        break;

        default:
            res = false;
        break;
    }

    Nvm_SetBlockById(NVM_BLOCK_BOOTDATA, &BootData, NVMSETBLOCK_STORE_IMMEDIATELY);

    return res;
}

void NvmResetCounters_ClearResetReason(void)
{
    // Clear all the reset flags or else they will remain set during future resets until system power is fully removed.
    __HAL_RCC_CLEAR_RESET_FLAGS();
}

void NvmResetCounters_Update(const bool bClearResetReason)
{
    boot_struct BootData;

    Nvm_GetBlockById(NVM_BLOCK_BOOTDATA, &BootData);

	//??? Changed because of H7xx

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDG1RST)) /* WINDOW_WATCHDOG_RESET */
        BootData.RST_WWD++;

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDG1RST))   /* INDEPENDENT_WATCHDOG_RESET */
        BootData.RST_IWD++;

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWR1RST)) /* LOW_POWER_RESET */
        BootData.RST_LPR++;

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))  /* POWER-ON_RESET (POR) / POWER-DOWN_RESET (PDR) */
        BootData.RST_POR++;

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))  /* EXTERNAL_RESET_PIN_RESET */
        BootData.RST_RstPin++;

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST))  /* BROWNOUT_RESET (BOR) */
        BootData.RST_BOR++;

    Nvm_SetBlockById(NVM_BLOCK_BOOTDATA, &BootData, NVMSETBLOCK_STORE_IMMEDIATELY);

    if (bClearResetReason)
        __HAL_RCC_CLEAR_RESET_FLAGS();
}

void NvmResetCounters_HardFault(void)
{
    boot_struct BootData;

    Nvm_GetBlockById(NVM_BLOCK_BOOTDATA, &BootData);

    if ((uint8_t) SCB->CFSR)
      BootData.RST_MemFault++;
    else if ((uint8_t) (SCB->CFSR >> 8))
      BootData.RST_BusFault++;
    else if ((uint16_t) (SCB->CFSR >> 16))
      BootData.RST_UsageFault++;
    else
        BootData.RST_HardFault++;

    Nvm_SetBlockById(NVM_BLOCK_BOOTDATA, &BootData, NVMSETBLOCK_STORE_IMMEDIATELY);
}

uint32_t NvmResetCounters_GetTotalCount(uint16_t * const rst_reason_bits)
{
    boot_struct BootData;
    uint32_t total_reset_count;

    Nvm_GetBlockById(NVM_BLOCK_BOOTDATA, &BootData);

    total_reset_count = BootData.RST_WWD +
				  BootData.RST_IWD +
				  BootData.RST_LPR +
				  BootData.RST_POR +
				  BootData.RST_RstPin +
				  BootData.RST_BOR +
				  BootData.RST_HardFault +
				  BootData.RST_MemFault +
				  BootData.RST_BusFault +
				  BootData.RST_UsageFault;

    if (NULL != rst_reason_bits)
    {
		//		LS bit 0: WWD reset occurred at least once
		//		LS bit 1: IWD reset occurred at least once
		//		LS bit 2: LPR reset occurred at least once
		//		LS bit 3: POR reset occurred at least once
		//		LS bit 4: RSTPIN reset occurred at least once
		//		LS bit 5: BOR reset occurred at least once
		//		LS bit 6: HARDFAULT reset occurred at least once
		//		LS bit 7: MEMFAULT reset occurred at least once
		//		LS bit 8: BUSFAULT reset occurred at least once
		//		LS bit 9: USAGEFAULT reset occurred at least once

    	*rst_reason_bits =
    			((BootData.RST_WWD > 0U) ? (RST_REASON_WWD) : (0U)) |
    			((BootData.RST_IWD > 0U) ? (RST_REASON_IWD) : (0U)) |
    			((BootData.RST_LPR > 0U) ? (RST_REASON_LPR) : (0U)) |
    			((BootData.RST_POR > 0U) ? (RST_REASON_POR) : (0U)) |
    			((BootData.RST_RstPin > 0U) ? (RST_REASON_RSTPIN) : (0U)) |
    			((BootData.RST_BOR > 0U) ? (RST_REASON_BOR) : (0U)) |
    			((BootData.RST_HardFault > 0U) ? (RST_REASON_HARDFAULT) : (0U)) |
    			((BootData.RST_MemFault > 0U) ? (RST_REASON_MEMFAULT) : (0U)) |
    			((BootData.RST_BusFault > 0U) ? (RST_REASON_BUSFAULT) : (0U)) |
    			((BootData.RST_UsageFault > 0U) ? (RST_REASON_USAGEFAULT) : (0U));
    }

    return total_reset_count;
}
