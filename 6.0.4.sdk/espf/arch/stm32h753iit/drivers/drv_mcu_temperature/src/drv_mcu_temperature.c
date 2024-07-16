/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup drv_mcu_temperature
 * @{
 *
 * @file     drv_mcu_temperature.c
 * @brief    MCU Temperature sensor driver
 *
 * @}
 *
 */
#include "../inc/drv_mcu_temperature.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_adc.h"
#include <stdint.h>


static ADC_HandleTypeDef fs_hadc;


static void fs_msp_init  (ADC_HandleTypeDef* hadc);
static void fs_msp_deinit(ADC_HandleTypeDef* hadc);


drv_mcu_temp_status_t drv_mcu_temp_init(void)
{
    if (HAL_OK != HAL_ADC_RegisterCallback(&fs_hadc, HAL_ADC_MSPINIT_CB_ID, fs_msp_init))
    {
        return DRV_MCU_TEMP_STATUS_ERR;
    }

    fs_hadc.Instance                      = ADC3;
    fs_hadc.Init.ClockPrescaler           = ADC_CLOCK_ASYNC_DIV1;
    fs_hadc.Init.Resolution               = ADC_RESOLUTION_16B;
    fs_hadc.Init.ScanConvMode             = ADC_SCAN_DISABLE;
    fs_hadc.Init.EOCSelection             = ADC_EOC_SINGLE_CONV;
    fs_hadc.Init.LowPowerAutoWait         = DISABLE;
    fs_hadc.Init.ContinuousConvMode       = ENABLE;
    fs_hadc.Init.NbrOfConversion          = 1;
    fs_hadc.Init.DiscontinuousConvMode    = DISABLE;
    fs_hadc.Init.ExternalTrigConv         = ADC_SOFTWARE_START;
    fs_hadc.Init.ExternalTrigConvEdge     = ADC_EXTERNALTRIGCONVEDGE_NONE;
    fs_hadc.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
    fs_hadc.Init.Overrun                  = ADC_OVR_DATA_PRESERVED;
    fs_hadc.Init.LeftBitShift             = ADC_LEFTBITSHIFT_NONE;
    fs_hadc.Init.OversamplingMode         = DISABLE;

    if (HAL_OK != HAL_ADC_Init(&fs_hadc))
    {
        return DRV_MCU_TEMP_STATUS_ERR;
    }

    ADC_ChannelConfTypeDef config = {0};

    config.Channel                = ADC_CHANNEL_TEMPSENSOR;
    config.Rank                   = ADC_REGULAR_RANK_1;
    config.SamplingTime           = ADC_SAMPLETIME_387CYCLES_5;
    config.SingleDiff             = ADC_SINGLE_ENDED;
    config.OffsetNumber           = ADC_OFFSET_NONE;
    config.Offset                 = 0;
    config.OffsetSignedSaturation = DISABLE;

    if (HAL_OK != HAL_ADC_ConfigChannel(&fs_hadc, &config))
    {
        return DRV_MCU_TEMP_STATUS_ERR;
    }

    return DRV_MCU_TEMP_STATUS_OK;
}


drv_mcu_temp_status_t drv_mcu_temp_deinit(void)
{
    if (HAL_OK != HAL_ADC_RegisterCallback(&fs_hadc, HAL_ADC_MSPDEINIT_CB_ID, fs_msp_deinit))
    {
        return DRV_MCU_TEMP_STATUS_ERR;
    }

    if (HAL_OK != HAL_ADC_DeInit(&fs_hadc))
    {
        return DRV_MCU_TEMP_STATUS_ERR;
    }

    return DRV_MCU_TEMP_STATUS_OK;
}


drv_mcu_temp_status_t drv_mcu_temp_get(float* temperature)
{
    if (NULL == temperature)
    {
        return DRV_MCU_TEMP_STATUS_ERR_PARAM;
    }

    HAL_StatusTypeDef status;

    status = HAL_ADCEx_Calibration_Start(&fs_hadc, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);

    if (HAL_OK != status)
    {
        return DRV_MCU_TEMP_STATUS_ERR;
    }

    status = HAL_ADC_Start(&fs_hadc);

    if (HAL_OK != status)
    {
        return DRV_MCU_TEMP_STATUS_ERR;
    }

    status = HAL_ADC_PollForConversion(&fs_hadc, 10);
    drv_mcu_temp_status_t drv_status;

    if (HAL_OK == status)
    {
        float TS_DATA = HAL_ADC_GetValue(&fs_hadc);
        float TS_CAL1 = *((int16_t*)0x1FF1E820); // 0x1FF1E820 Calibration ADC value at 30 degrees C
        float TS_CAL2 = *((int16_t*)0x1FF1E840); // 0x1FF1E840 Calibration ADC value at 110 degrees C
        *temperature  = ((110.f - 30.f) / (TS_CAL2 - TS_CAL1)) * (TS_DATA - TS_CAL1) + 30.f;

        drv_status = DRV_MCU_TEMP_STATUS_OK;
    }
    else
    {
    	drv_status = DRV_MCU_TEMP_STATUS_ERR;
    }

    HAL_ADC_Stop(&fs_hadc);

    return drv_status;
}


static void fs_msp_init(ADC_HandleTypeDef* hadc)
{
    if (ADC3 == hadc->Instance)
    {
        __HAL_RCC_ADC3_CLK_ENABLE();
    }
}


static void fs_msp_deinit(ADC_HandleTypeDef* hadc)
{
    if (ADC3 == hadc->Instance)
    {
        __HAL_RCC_ADC3_CLK_DISABLE();
    }
}

