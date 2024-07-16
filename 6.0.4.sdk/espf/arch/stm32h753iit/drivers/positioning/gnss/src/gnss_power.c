/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_power.c
 *
 *
 * @}
 * @}
 */

#include "gnss_power.h"
#include "stm32h7xx_hal.h"


void gnss_power_on(void)
{
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init_struct = { 0 };

    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET);
    gpio_init_struct.Pin   = GPIO_PIN_11;
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);
}


void gnss_power_off(void)
{
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init_struct = { 0 };

    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET);
    gpio_init_struct.Pin   = GPIO_PIN_11;
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);
}


bool gnss_power_is_on(void)
{
    return (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_11)) ? true : false;
}


