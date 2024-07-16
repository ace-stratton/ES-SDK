/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef DRV_LED_H_
#define DRV_LED_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup drv_led Status LED Driver
 * @{
 *
 * Control of the status LED of the OBC
 *
 * @file     drv_led.h
 * @brief    Status LED Driver declarations
 *
 * @}
 * @}
 *
 */

/**
 * @brief Led Status enumeration definition
 */
typedef enum
{
    DRV_LED_STATUS_ERR = 0,   /**< error within driver           */
    DRV_LED_STATUS_ERR_PARAM, /**< user-supplied parameter error */
    DRV_LED_STATUS_OK,        /**< no errors                     */
} drv_led_status_t;


/**
 * @brief Led State enumeration definition
 */
typedef enum
{
    DRV_LED_STATE_OFF = 0,
    DRV_LED_STATE_ON,
    DRV_LED_STATE_MAX_COUNT
} drv_led_state_t;


/**
 * @brief Led ID enumeration definition
 */
typedef enum
{
    DRV_LED_ID_GREEN = 0,
    DRV_LED_ID_AMBER,
    DRV_LED_ID_MAX_COUNT
} drv_led_id_t;


/**
 * @brief  Initialize LEDs.
 *
 * @return @ref drv_led_status_t
 */
drv_led_status_t drv_led_init(void);


/**
 * @brief  DeInitialize LEDs.
 *
 * @return @ref drv_led_status_t
 */
drv_led_status_t drv_led_deinit(void);


/**
 * @brief  Turn on/off LED
 *
 * @param  id    LED id @ref drv_led_id_t
 * @param  state LED state @ref led_state_t
 *
 * @return @ref drv_led_status_t
 */
drv_led_status_t drv_led_set(drv_led_id_t id, drv_led_state_t state);


/**
 * @brief  Toggle LED
 *
 * @param  id LED id @ref drv_led_id_t
 *
 * @return @ref drv_led_status_t
 */
drv_led_status_t drv_led_toggle(drv_led_id_t id);


#endif /* DRV_LED_H_ */
