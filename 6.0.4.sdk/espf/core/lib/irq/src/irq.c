/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "irq.h"

#ifdef STM32H753xx
#include "stm32h7xx_hal.h"

static volatile uint32_t fs_interrupt_disabled_count = 0;


bool irq_active(void)
{
    return (0U != __get_IPSR());
}


void irq_disable_all(void)
{
    __disable_irq();

    // Increase number of disable interrupt function calls
    fs_interrupt_disabled_count++;
}


void irq_enable_all(void)
{
    // Decrease number of disable interrupt function calls
    if (0 < fs_interrupt_disabled_count)
    {
        fs_interrupt_disabled_count--;
    }

    // Check if we are ready to enable interrupts
    if (0 >= fs_interrupt_disabled_count)
    {
        __enable_irq();
    }
}
#else
#error "missing implementation"
#endif






