/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GNSS_IRQ_H_
#define GNSS_IRQ_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_irq.h
 *
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Process an interrupt in the UART peripheral
 */
void gnss_irq_uart_handler(void);

/**
 * @brief Process an interrupt in the DMA peripheral
 */
void gnss_irq_dma_handler(void);


#ifdef __cplusplus
}
#endif

#endif /* GNSS_IRQ_H_ */
