/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup drv_led
 * @{
 *
 * @file     drv_led.c
 * @brief    Status LED Driver definitions
 *
 * @}
 *
 */

#include "../inc/drv_led.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"
#include <stdint.h>


#define LED_GREEN_GPIO_PORT    GPIOB
#define LED_GREEN_PIN          GPIO_PIN_2

#define LED_AMBER_GPIO_PORT    GPIOF
#define LED_AMBER_PIN          GPIO_PIN_4

#define LED_GREEN_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED_AMBER_CLK_ENABLE() __HAL_RCC_GPIOF_CLK_ENABLE()


typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} fs_led_t;


fs_led_t fs_led[DRV_LED_ID_MAX_COUNT] =
{
    [DRV_LED_ID_GREEN] =
    {
        .port = LED_GREEN_GPIO_PORT,
        .pin  = LED_GREEN_PIN
    },
    [DRV_LED_ID_AMBER] =
    {
        .port = LED_AMBER_GPIO_PORT,
        .pin  = LED_AMBER_PIN
    },
};


drv_led_status_t drv_led_init(void)
{
	LED_GREEN_CLK_ENABLE();
	LED_AMBER_CLK_ENABLE();

    GPIO_InitTypeDef init_struct;

    init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    init_struct.Pull  = GPIO_NOPULL;
    init_struct.Speed = GPIO_SPEED_FREQ_LOW;

    for (uint8_t id = 0; id < DRV_LED_ID_MAX_COUNT; id++)
    {
        init_struct.Pin = fs_led[id].pin;
        HAL_GPIO_Init(fs_led[id].port, &init_struct);
        drv_led_set(id, DRV_LED_STATE_OFF);
    }

    return DRV_LED_STATUS_OK;
}


drv_led_status_t drv_led_deinit(void)
{
    for (uint8_t id = 0; id < DRV_LED_ID_MAX_COUNT; id++)
    {
    	drv_led_set(id, DRV_LED_STATE_OFF);
        HAL_GPIO_DeInit(fs_led[id].port, fs_led[id].pin);
    }

    return DRV_LED_STATUS_OK;
}


drv_led_status_t drv_led_set(drv_led_id_t id, drv_led_state_t state)
{
    if (DRV_LED_ID_MAX_COUNT <= (uint8_t)id)
    {
        return DRV_LED_STATUS_ERR_PARAM;
    }

    if (DRV_LED_STATE_MAX_COUNT <= (uint8_t)state)
    {
        return DRV_LED_STATUS_ERR_PARAM;
    }

    if (DRV_LED_STATE_OFF == state)
    {
        HAL_GPIO_WritePin(fs_led[id].port, fs_led[id].pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(fs_led[id].port, fs_led[id].pin, GPIO_PIN_SET);
    }

    return DRV_LED_STATUS_OK;
}


drv_led_status_t drv_led_toggle(drv_led_id_t id)
{
    if (DRV_LED_ID_MAX_COUNT <= (uint8_t)id)
    {
        return DRV_LED_STATUS_ERR_PARAM;
    }

    HAL_GPIO_TogglePin(fs_led[id].port, fs_led[id].pin);

    return DRV_LED_STATUS_OK;
}
