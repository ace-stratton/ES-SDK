/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef DRV_MCU_TEMPERATURE_H_
#define DRV_MCU_TEMPERATURE_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup drv_mcu_temperature MCU Temperature
 * @{
 *
 * Get the measurement of the temperature of the MCU.
 *
 * @file     drv_mcu_temperature.h
 * @brief    Public interface for the MCU temperature driver
 *
 * @}
 * @}
 *
 */

/**
 * @brief MCU Temperature Status enumeration definition
 */
typedef enum
{
    DRV_MCU_TEMP_STATUS_ERR,       /*!< error within driver           */
    DRV_MCU_TEMP_STATUS_ERR_PARAM, /*!< user-supplied parameter error */
    DRV_MCU_TEMP_STATUS_OK         /*!< no errors                     */
} drv_mcu_temp_status_t;


/**
 * @brief  Initialize the ADC peripheral used for measuring the MCU temperature
 *
 * @return @ref drv_mcu_temp_status_t
 */
drv_mcu_temp_status_t drv_mcu_temp_init(void);


/**
 * @brief  DeInitialize the ADC peripheral used for measuring the MCU temperature.
 *
 * @return @ref drv_mcu_temp_status_t
 */
drv_mcu_temp_status_t drv_mcu_temp_deinit(void);


/**
 * @brief  Get the MCU temperature in degrees C.
 *
 * @param  temperature Valid pointer. Contains the MCU temperature (in degrees C) on success.
 *
 * @return @ref drv_mcu_temp_status_t
 */
drv_mcu_temp_status_t drv_mcu_temp_get(float* temperature);


#endif /* DRV_MCU_TEMPERATURE_H_ */
