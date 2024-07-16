/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CAN_PIN_DEFS_H_
#define CAN_PIN_DEFS_H_

#include "stm32h7xx_hal.h"


#define CANDEF_RX_PORT  GPIOH
#define CANDEF_RX_PIN   GPIO_PIN_14
#define CANDEF_TX_PORT  GPIOD
#define CANDEF_TX_PIN   GPIO_PIN_1
#define CANDEF_EN_PORT  GPIOA
#define CANDEF_EN_PIN   GPIO_PIN_8


static inline void CANDEF_RX_PORT_CLK_EN(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();
}

static inline void CANDEF_TX_PORT_CLK_EN(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
}

static inline void CANDEF_EN_PORT_CLK_EN(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
}


#endif /* CAN_PIN_DEFS_H_ */
