/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef IRQ_H_
#define IRQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


/**
 * @brief Checks if current execution is from ISR context
 *
 * @retval true  In ISR context
 * @retval false Not in ISR context
 */
bool irq_active(void);

/**
 * @brief Disable all interrupts
 */
void irq_disable_all(void);

/**
 * @brief Enable all interrupts
 */
void irq_enable_all(void);


#ifdef __cplusplus
}
#endif

#endif /* IRQ_H_ */
