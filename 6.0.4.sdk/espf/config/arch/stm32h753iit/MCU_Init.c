/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*!
 ********************************************************************************************
 * @file MCU_Init.c
 * @brief All initialization routines needed after Power up
 ********************************************************************************************
 * @author            Vassil Milev
 * @version           1.0.0
 * @date              2019.01.10
 *
 * @copyright         (C) Copyright Endurosat
 *
 *                    Contents and presentations are protected world-wide.
 *                    Any kind of using, copying etc. is prohibited without prior permission.
 *                    All rights - incl. industrial property rights - are reserved.
 *
 * @history
 * @revision{         1.0.0  , 2019.01.10, author Vassil Milev, Initial revision }
 * @endhistory
 ********************************************************************************************
 */

/*
 *********************************************************************************************
 * INCLUDES
 *********************************************************************************************
 */
#include "MCU_Init.h"
#include "cmsis_os.h"
#include "SdMngr.h"
#include "string.h"

#include "DAT_Inputs.h"
#include "panels.h"
#include "cubeadcs.h"
#include "stm32h7xx_ll_rcc.h"
#include "es_exeh.h"                /* Include DTC error handling */
#include "MX_I2C.h"
#include "S_X_Band_Trnsm.h"
#include "trace.h"
#include "if_sys_conf.h"
#include "nvm/inc/nvm.h"

/*
 *********************************************************************************************
 * INTERNAL DEFINES
 *********************************************************************************************
 */
/* No Internal defines */

/*
 *********************************************************************************************
 * INTERNAL TYPES DEFINITION
 *********************************************************************************************
 */
/* No Internal types definition */

/*
 *********************************************************************************************
 * EXTERNAL VARIABLES DEFINITION
 *********************************************************************************************
 */

/**
 * @brief Peripheral HAL interfaces in use
 */
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

SD_HandleTypeDef hsd1;

SPI_HandleTypeDef hspi5;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim5;

extern Disk_drvTypeDef  disk;

///////////////////////////////


/*
 *********************************************************************************************
 * INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
 *********************************************************************************************
 */
volatile static uint8_t I2C2_Used = 0;
volatile static uint8_t PANEL_SPI_Used = 0;/* No Internal routines declaration */

/*
 *********************************************************************************************
 * INTERNAL (STATIC) ROUTINES DECLARATION
 *********************************************************************************************
 */
/* No Internal routines declaration */

/*
 *********************************************************************************************
 * EXTERNAL (NONE STATIC) ROUTINES DEFINITION
 *********************************************************************************************
 */
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
static void RCC_SDIO1_RESET(void);

/*!
 *********************************************************************************************
 * @brief System Clock Configuration - configure to 216Mhz core frequency
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void SystemClock_IdleConfig(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Supply configuration update enable
     */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
    /** Configure the main internal regulator output voltage
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
    /** Configure LSE Drive Capability
     */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_HIGH);
    /** Macro to configure the PLL clock source
     */
    __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

    /* Enable D2 domain SRAM3 Clock (0x30040000 AXI)*/
    __HAL_RCC_D2SRAM3_CLK_ENABLE();

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        //Ignore the error - that oscillator is not used (only for RNG and USB).
    }

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    RCC_OscInitStruct.PLL.PLLR = 4;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_0;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)    //If not able to work on external oscillator use to the internal one
    {
        //Internal clock will be used on Fail of the external

    	__HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
        RCC_OscInitStruct.LSEState = RCC_LSE_ON;
        RCC_OscInitStruct.HSIState = RCC_HSI_DIV2;
        RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
        RCC_OscInitStruct.LSIState = RCC_LSI_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
        RCC_OscInitStruct.PLL.PLLM = 32;
        RCC_OscInitStruct.PLL.PLLN = 432;
        RCC_OscInitStruct.PLL.PLLP = 2;
        RCC_OscInitStruct.PLL.PLLQ = 9;
        RCC_OscInitStruct.PLL.PLLR = 4;
        RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
        RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
        RCC_OscInitStruct.PLL.PLLFRACN = 0;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        {
            Error_Handler();
        }else{
            // Success to init the Internal high speed clock

            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_FDCAN;
            PeriphClkInitStruct.PLL2.PLL2M = 32;
            PeriphClkInitStruct.PLL2.PLL2N = 240;
            PeriphClkInitStruct.PLL2.PLL2P = 25;
            PeriphClkInitStruct.PLL2.PLL2Q = 4;
            PeriphClkInitStruct.PLL2.PLL2R = 4;
            PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_0;
            PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
            PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
            PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL2;
            PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
        }
    }
    else{
        // Success to init the External high speed clock

    	HAL_RCC_EnableCSS();

        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_FDCAN;
        PeriphClkInitStruct.PLL2.PLL2M = 25;
        PeriphClkInitStruct.PLL2.PLL2N = 240;
        PeriphClkInitStruct.PLL2.PLL2P = 25;
        PeriphClkInitStruct.PLL2.PLL2Q = 4;
        PeriphClkInitStruct.PLL2.PLL2R = 4;
        PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
        PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
        PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
        PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL2;
        PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    }

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_OFF;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        RCC_OscInitStruct.LSIState = RCC_LSI_ON;
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;

        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        {
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
            |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }

    ////////////////////////////////////////////////////////////////////////////////////

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}

/*!
 *********************************************************************************************
 * @brief Deinit all General purpose I/O lines
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MX_AllPeripheryAndGpio_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    Panels_ChipSelect2_DeInit();

    MCU_AccelerometersDeInit();
    MCU_MagnetometersDeInit();
    MCU_MagnetorqersDeInit();
    MCU_GyrosDeInit();
    MCU_TemprDeInit();
    MCU_SunSensDeInit();

    //  MX_SENSORS_I2C_DeInit(); // already done in the actual deinit of the sensors
    //  MX_SYSTEM_I2C_DeInit(); //Never deinit System I2C
    MX_I2C_BusDeInit(MX_I2C_BUS_PAYLOAD);

    /////////////// UART 1 RS485 disable transmit ///////////////////////
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);  //USART1_RTS_RS485_HS1_DE_SYS1_Pin
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /////////////// RS 422 pins ///////////////////////
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5 | GPIO_PIN_12, GPIO_PIN_RESET);   // leave it with Rx enable so it can wake up the MCU

    GPIO_InitStruct.Pin = RS422_HS1_nRE_UART1_SYS1_Pin  //RS422_HS1_nRE
            |RS422_HS2_nRE_UART6_PAY1_Pin; //RS422_HS2_nRE
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    //DE1 -> PF10 RS422_HS1_DE
    //DE2 -> PE10 RS422_HS2_DE
    HAL_GPIO_WritePin(RS422_HS1_DE_UART1_SYS1_GPIO_Port, RS422_HS1_DE_UART1_SYS1_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = RS422_HS1_DE_UART1_SYS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(RS422_HS1_DE_UART1_SYS1_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(RS422_HS2_DE_UART6_PAY1_GPIO_Port, RS422_HS2_DE_UART6_PAY1_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = RS422_HS2_DE_UART6_PAY1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(RS422_HS2_DE_UART6_PAY1_GPIO_Port, &GPIO_InitStruct);
    /////////////   Ethernet pins ////////////////////

    GPIO_InitStruct.Pin = GPIO_PIN_1   //ETH_MDC
            |GPIO_PIN_2   //ETH_TXD2
            |GPIO_PIN_3   //ETH_TX_CLK
            |GPIO_PIN_4   //ETH_RXD0
            |GPIO_PIN_5;  //ETH_RXD1
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;     //ETH_RX_ER
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /*Configure GPIO pins : PA1 PA2
                           PA5 PA6 PA7 PA9
                           PA11
                           USART1_RTS_RS485_HS1_DE_SYS1_Pin */
    GPIO_InitStruct.Pin = GPIO_PIN_1  //ETH_RX_CLK
            |GPIO_PIN_2   //ETH_MDIO
            |GPIO_PIN_7;  //ETH_RX_DV
    /*|USART1_RTS_RS485_HS1_DE_SYS1_Pin;*/
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins :  PB1 PB10 PB11
                           PB12 PB13 PB5 PB6
                           PB7 PB8 */
    GPIO_InitStruct.Pin = GPIO_PIN_1  //ETH_RXD3
            |GPIO_PIN_11  //ETH0TX_EN
            |GPIO_PIN_12  //ETH_TXD0
            |GPIO_PIN_13; //ETH_TXD1
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);   //*******

    /*Configure GPIO pins : PE2 */
    GPIO_InitStruct.Pin = GPIO_PIN_2; //ETH_TXD3
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);


    /*Configure GPIO pins : PH2 PH6 PH14 */
    GPIO_InitStruct.Pin = ETH_RSTn_Pin
            |GPIO_PIN_6   //ETH_RXD2
            |ETH_EN_Pin; //CAN1_RX
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    ////////////////////////////// CAN Pins ////////////////////////////

    HAL_GPIO_WritePin(GPIOA, CAN_RS_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = GPIO_PIN_14; //CAN1_RX
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /*Configure GPIO pins : CAN_RS_Pin  */
    GPIO_InitStruct.Pin = CAN_RS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1;   //CAN1_TX
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/*!
 *********************************************************************************************
 * @brief ADC1 (Analog-to-Digital Converter Module #1) initialization
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MX_ADC1_Init(void)
{
    ADC_MultiModeTypeDef multimode = {0};
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.LowPowerAutoWait = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
    hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
    hadc1.Init.OversamplingMode = DISABLE;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure the ADC multi-mode
     */
    multimode.Mode = ADC_MODE_INDEPENDENT;
    if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_9;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    sConfig.OffsetSignedSaturation = DISABLE;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/*!
 *********************************************************************************************
 * @brief SDIO (Secure Digital Input Output Module) initialisation
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
static void MX_SDMMC1_SD_Init(void)
{
    // Enable GPIO and SPI Clocks
    __HAL_RCC_GPIOG_CLK_ENABLE();

    /* USER CODE BEGIN SDMMC1_Init 0 */
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = SD_DET_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SD_DET_GPIO_Port, &GPIO_InitStruct);//ADD exti13 for SD2 -> PC13

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0); //ADD exti13 for SD2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* USER CODE END SDMMC1_Init 0 */

    /* USER CODE BEGIN SDMMC1_Init 1 */

    /* USER CODE END SDMMC1_Init 1 */
    hsd1.Instance = SDMMC1;
    hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
    hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
    hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
    hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd1.Init.ClockDiv = 0;
    /* USER CODE BEGIN SDMMC1_Init 2 */

    /* SDMMC1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SDMMC1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);

    /* USER CODE END SDMMC1_Init 2 */
}

/**
 * @brief SPI5 Initialization Function
 * @param None
 * @retval None
 */
void MX_SPI5_Init(void)
{
    /* SPI5 parameter configuration*/
    hspi5.Instance = SPI5;
    hspi5.Init.Mode = SPI_MODE_MASTER;
    hspi5.Init.Direction = SPI_DIRECTION_2LINES;
    hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi5.Init.NSS = SPI_NSS_SOFT;
    hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi5.Init.CRCPolynomial = 10;
    hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi5.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    if (HAL_SPI_Init(&hspi5) != HAL_OK)
    {
        Error_Handler();
    }

}

void MX_SPI5_DeInit(void)
{
    HAL_SPI_DeInit(&hspi5);

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = SPI5_SCK_Pin|SPI5_MISO_Pin|SPI5_MOSI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

/*!
 *********************************************************************************************
 * @brief SPI2 (Serial Peripheral Interface Module #2) initialisation
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MX_PANEL_SPI_Init(SPI_HandleTypeDef *hspi)
{
    /* SPI2 parameter configuration*/
    hspi->Instance = PANEL_SPI;
    hspi->Init.Mode = SPI_MODE_MASTER;
    hspi->Init.Direction = SPI_DIRECTION_2LINES;
    hspi->Init.DataSize = SPI_DATASIZE_16BIT;
    hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi->Init.NSS = SPI_NSS_SOFT;
    hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi->Init.TIMode = SPI_TIMODE_DISABLE;
    hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi->Init.CRCPolynomial = 7;
    hspi->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    hspi->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;
    if (HAL_SPI_Init(hspi) != HAL_OK)
    {
        Error_Handler();
    }
}

/*!
 *********************************************************************************************
 * @brief TIM5 (Timer Module #5) initialisation
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MX_TIM5_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 0;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = MAGTORQ_PWM_PERIOD;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM5_Init 2 */

    /* USER CODE END TIM5_Init 2 */
    HAL_TIM_MspPostInit(&htim5);
}

/*!
*********************************************************************************************
 * @brief Controls power of all 1U panel sensors
 *           Power to temp and gyro sensors is controlled in combination to make sure
 *           pin levels are always held in a stable state while using any of the sensors.
*********************************************************************************************
 * @param[input]      isOn -> true: turns on power to sensors; false: turns off power to sensors
 * @param[output]     none
 * @return            none
 * @note              none
*********************************************************************************************
 */
static void pansense_pwr_control(const bool isOn)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    if (isOn)
    {
        // Temp sensors power
        HAL_GPIO_WritePin(PAN_Temp_PS_GPIO_Port, PAN_Temp_PS_Pin, GPIO_PIN_RESET);

        GPIO_InitStruct.Pin = PAN_Temp_PS_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(PAN5_CS2_GPIO_Port, &GPIO_InitStruct);

        // Gyro power
        HAL_GPIO_WritePin(GPIOB, PAN3_6_VGY_Pin|PAN1_4_VGY_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(PAN2_5_VGY_GPIO_Port, PAN2_5_VGY_Pin, GPIO_PIN_SET);

        /*Configure GPIO pin : PtPin */
        GPIO_InitStruct.Pin = PAN3_6_VGY_Pin|PAN1_4_VGY_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = PAN2_5_VGY_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(PAN2_5_VGY_GPIO_Port, &GPIO_InitStruct);
    }
    else
    {
        HAL_GPIO_WritePin(PAN_Temp_PS_GPIO_Port, PAN_Temp_PS_Pin, GPIO_PIN_SET);

        GPIO_InitStruct.Pin = PAN_Temp_PS_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(PAN5_CS2_GPIO_Port, &GPIO_InitStruct);

        HAL_GPIO_WritePin(GPIOB, PAN3_6_VGY_Pin|PAN1_4_VGY_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(PAN2_5_VGY_GPIO_Port, PAN2_5_VGY_Pin, GPIO_PIN_RESET);

        GPIO_InitStruct.Pin = PAN3_6_VGY_Pin|PAN1_4_VGY_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = PAN2_5_VGY_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(PAN2_5_VGY_GPIO_Port, &GPIO_InitStruct);
    }
}

/*
 * @brief Initialize all periphery needed for the accelerometers
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_AccelerometersInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(ACC_EN_GPIO_Port, ACC_EN_Pin, GPIO_PIN_RESET); //Enable Power supply of the accelerometers

    GPIO_InitStruct.Pin = ACC_EN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ACC_EN_GPIO_Port, &GPIO_InitStruct);

    //Init SPI2
    I2C2_Used |= SENSORS_I2C_USE_ACCEL;

    //Inizialize ACC Sensor 1
    if (AIS328DQ_Init(AIS328DQ_1_MEMS_I2C_ADDRESS) != SEN_SUCCESS)
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_MCU_INIT, eEXEH_MCU_INIT_EXCEPTION_ID_ACCEL_INIT, __LINE__);
    }

    //Inizialize ACC Sensor 2
    if (AIS328DQ_Init(AIS328DQ_2_MEMS_I2C_ADDRESS) != SEN_SUCCESS)
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_MCU_INIT, eEXEH_MCU_INIT_EXCEPTION_ID_ACCEL_INIT, __LINE__);
    }
}

/*!
 *********************************************************************************************
 * @brief DeInitialize all periphery needed for the accelerometers
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_AccelerometersDeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(ACC_EN_GPIO_Port, ACC_EN_Pin, GPIO_PIN_SET); //Disable Power supply of the accelerometers

    GPIO_InitStruct.Pin = ACC_EN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ACC_EN_GPIO_Port, &GPIO_InitStruct);

    I2C2_Used &= ~SENSORS_I2C_USE_ACCEL;
    if( I2C2_Used == 0 )
    {
        //DeInit SPI2
        HAL_I2C_DeInit(&SENSORS_I2C_HANDLER);

        GPIO_InitStruct.Pin = I2C2_SEN_SCL_Pin|I2C2_SEN_SDA_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(I2C2_SEN_SDA_GPIO_Port, &GPIO_InitStruct);
    }
}

/*!
 *********************************************************************************************
 * @brief Initialize all periphery needed for the magnitometers
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_MagnetometersInit(void)
{
    //Init SPI2
    I2C2_Used |= SENSORS_I2C_USE_COMPAS;

    if (Magnitometers_LIS3MDL_Init(LIS3MDL_MAG_I2C_ADDRESS_LOW) != E_OK)
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_MCU_INIT, eEXEH_MCU_INIT_EXCEPTION_ID_MANITO_INIT, __LINE__);
    }

    if (Magnitometers_LIS3MDL_Init(LIS3MDL_MAG_I2C_ADDRESS_HIGH) != E_OK)
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_MCU_INIT, eEXEH_MCU_INIT_EXCEPTION_ID_MANITO_INIT, __LINE__);
    }
}

/*!
 *********************************************************************************************
 * @brief DeInitialize all periphery needed for the magnitometers
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_MagnetometersDeInit(void)
{
    //todo VVS: add low-power mode for the magnetometers

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    I2C2_Used &= ~SENSORS_I2C_USE_COMPAS;
    if( I2C2_Used == 0 )
    {
        //DeInit I2C
        HAL_I2C_DeInit(&SENSORS_I2C_HANDLER);

        //Deinit GPIOs
        GPIO_InitStruct.Pin = I2C2_SEN_SCL_Pin|I2C2_SEN_SDA_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(I2C2_SEN_SDA_GPIO_Port, &GPIO_InitStruct);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 *********************************************************************************************
 * @brief Initialize all periphery needed for the magnetorquers
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_MagnetorqersInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO and SPI Clocks
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    // Init GPIOs

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(PAN4_DIR1_GPIO_Port, PAN4_DIR1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PAN5_DIR1_GPIO_Port, PAN5_DIR1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PAN_PS_GPIO_Port, PAN_PS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(PAN6_DIR1_GPIO_Port, PAN6_DIR1_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = PAN6_DIR1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN6_DIR1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN5_DIR1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN5_DIR1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PAN4_DIR1_Pin*/
    GPIO_InitStruct.Pin = PAN4_DIR1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN4_DIR1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PAN_PS_Pin*/
    GPIO_InitStruct.Pin = PAN_PS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN_PS_GPIO_Port, &GPIO_InitStruct);

    //Init TIM5
    MX_TIM5_Init();

    /* Set PWM of the magnetorquer to 0% (i.e. OFF) */
    if (SetMagnetorque(PAN_X_M, 0, 1) == SEN_SUCCESS)
        ES_TRACE_DEBUG("TRQ1_INIT_OK 0%%\r");

    /* Set PWM of the magnetorquer to 0% (i.e. OFF) */
    if (SetMagnetorque(PAN_Y_M, 0, 1) == SEN_SUCCESS)
        ES_TRACE_DEBUG("TRQ2_INIT_OK 0%%\r");

    /* Set PWM of the magnetorquer to 0% (i.e. OFF) */
    if (SetMagnetorque(PAN_Z_M, 0, 1) == SEN_SUCCESS)
        ES_TRACE_DEBUG("TRQ3_INIT_OK 0%%\r");
}

/*!
 *********************************************************************************************
 * @brief DeInitialize all periphery needed for the magnetorquers
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_MagnetorqersDeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    //DeInit TIM5
    HAL_TIM_PWM_DeInit(&htim5);

    //Enalbe power safe mode of the H-Bridge Driver
    HAL_GPIO_WritePin(PAN_PS_GPIO_Port, PAN_PS_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : PAN_PS_Pin*/
    GPIO_InitStruct.Pin = PAN_PS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN_PS_GPIO_Port, &GPIO_InitStruct);  //PE

    // DeInit GPIOs
    GPIO_InitStruct.Pin = PAN6_DIR1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PAN6_DIR1_GPIO_Port, &GPIO_InitStruct);


    GPIO_InitStruct.Pin = PAN5_DIR1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PAN5_DIR1_GPIO_Port, &GPIO_InitStruct);   //PF

    GPIO_InitStruct.Pin = PAN4_DIR1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PAN4_DIR1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN4_PWM_Pin|PAN5_PWM_Pin|PAN6_PWM_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
}

////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 *********************************************************************************************
 * @brief Initialize all periphery needed for the gyroscopes
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_GyrosInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    uint8_t res;

    pansense_pwr_control(true);
    //Init SPI2
    PANEL_SPI_Used |= PANEL_SPI_USE_GPS;
    if(( PANEL_SPI_Used & PANEL_SPI_USE_TEMPR ) == 0)   // If temerature sensor is not initialised
    {
        Panels_ChipSelect2_Init();

        //Init SPI if not done already
        MX_PANEL_SPI_Init(&PANEL_SPI_HANDLER);
    }

    // Enable GPIO and SPI Clocks
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();


    // Init GPIOs
    HAL_GPIO_WritePin(GPIOI, PAN6_CS1_Pin|PAN3_CS1_Pin|PAN4_CS1_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(PAN5_CS1_GPIO_Port, PAN5_CS1_Pin, GPIO_PIN_SET);  //PE

    HAL_GPIO_WritePin(GPIOG, PAN2_CS1_Pin |PAN1_CS1_Pin , GPIO_PIN_SET);

    GPIO_InitStruct.Pin = PAN6_CS1_Pin|PAN3_CS1_Pin|PAN4_CS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN5_CS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN5_CS1_GPIO_Port, &GPIO_InitStruct);    //PE

    GPIO_InitStruct.Pin = PAN2_CS1_Pin|PAN1_CS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* This delay compensates for gyroscope initial start-up time, 165ms as per datasheet, page 4, for ADIS16265 gyro */
    sysDelay(200);

    //Inizialize GYR Sensor X
    res = 0;
    if ( ADIS16265_Init(PAN_X_P, ADIS16265_INIT_TIME_NREQ) == GYRO_SUCCESS) { res += 1; } /* Attempt to initialize gyroscope on X positive axis */
    if ( ADIS16265_Init(PAN_X_M, ADIS16265_INIT_TIME_NREQ) == GYRO_SUCCESS) { res += 1; } /* Attempt to initialize gyroscope on X negative axis */
    /* If either no gyroscope was found on X axis or TWO gyroscopes were found on positive and negative X axis */
    if ((ADIS16265_AXIS_NOT_FOUND_IN_INIT == res) || (ADIS16265_REPEATING_AXIS_IN_INIT == res))
	{
    	EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_MCU_INIT, eEXEH_MCU_INIT_EXCEPTION_ID_GYRO_INIT, __LINE__);
    }

    //Inizialize GYR Sensor Y
    res = 0;
    if (ADIS16265_Init(PAN_Y_P, ADIS16265_INIT_TIME_NREQ) == GYRO_SUCCESS) { res += 1; } /* Attempt to initialize gyroscope on Y positive axis */
    if (ADIS16265_Init(PAN_Y_M, ADIS16265_INIT_TIME_NREQ) == GYRO_SUCCESS) { res += 1; } /* Attempt to initialize gyroscope on Y negative axis */
    /* If either no gyroscope was found on Y axis or TWO gyroscopes were found on positive and negative Y axis */
    if ((ADIS16265_AXIS_NOT_FOUND_IN_INIT == res) || (ADIS16265_REPEATING_AXIS_IN_INIT == res))
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_MCU_INIT, eEXEH_MCU_INIT_EXCEPTION_ID_GYRO_INIT, __LINE__);
    }

    //Inizialize GYR Sensor Z
    res = 0;
    if (ADIS16265_Init(PAN_Z_P, ADIS16265_INIT_TIME_NREQ) == GYRO_SUCCESS) { res += 1; } /* Attempt to initialize gyroscope on Z positive axis */
    if (ADIS16265_Init(PAN_Z_M, ADIS16265_INIT_TIME_NREQ) == GYRO_SUCCESS) { res += 1; } /* Attempt to initialize gyroscope on Z negative axis */
    /* If either no gyroscope was found on Z axis or TWO gyroscopes were found on positive and negative Z axis */
    if ((ADIS16265_AXIS_NOT_FOUND_IN_INIT == res) || (ADIS16265_REPEATING_AXIS_IN_INIT == res))
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_MCU_INIT, eEXEH_MCU_INIT_EXCEPTION_ID_GYRO_INIT, __LINE__);
    }
}

/*!
 *********************************************************************************************
 * @brief DeInitialize all periphery needed for the gyroscopes
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_GyrosDeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    ADIS16265_DeInit(PAN_X_P);
    ADIS16265_DeInit(PAN_Y_P);
    ADIS16265_DeInit(PAN_Z_P);
    ADIS16265_DeInit(PAN_X_M);
    ADIS16265_DeInit(PAN_Y_M);
    ADIS16265_DeInit(PAN_Z_M);

    // Init GPIOs
    pansense_pwr_control(false);

    GPIO_InitStruct.Pin = PAN6_CS1_Pin|PAN3_CS1_Pin|PAN4_CS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN5_CS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PAN5_CS1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN1_CS1_Pin|PAN2_CS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    PANEL_SPI_Used &= ~PANEL_SPI_USE_GPS;
    if( PANEL_SPI_Used == 0)
    {
        //DeInit SPI2
        HAL_SPI_DeInit(&PANEL_SPI_HANDLER);
        Panels_ChipSelect2_DeInit();

        //DeInit GPIOs
        GPIO_InitStruct.Pin = PAN_MOSI_Pin|PAN_MISO_Pin|PAN_SCK_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
    }
}

/*!
 *********************************************************************************************
 * @brief Initialize all periphery needed for the temperature sensors
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_TemprInit(void)
{
    uint16_t txdata = 0x0000;

    pansense_pwr_control(true);
    //Init all "chip select 2" pins (for all 6 panels)
    Panels_ChipSelect2_Init();

    //Init SPI2
    PANEL_SPI_Used |= PANEL_SPI_USE_TEMPR;
    MX_PANEL_SPI_Init(&PANEL_SPI_HANDLER);

    //Do one dummy SPI transfer (Otherwise the first temperature sensor reading is wrong)
    (void)HAL_SPI_Transmit(&PANEL_SPI_HANDLER, (uint8_t *) &txdata, 1, 10);
}

/*!
 *********************************************************************************************
 * @brief Initialize all periphery needed for the temperature sensors
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_TemprDeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    pansense_pwr_control(false);


    Panels_ChipSelect2_DeInit();

    PANEL_SPI_Used &= ~PANEL_SPI_USE_TEMPR;
    if( PANEL_SPI_Used == 0)
    {
        //DeInit SPI2
        HAL_SPI_DeInit(&PANEL_SPI_HANDLER);

        // DeInit GPIOs
        GPIO_InitStruct.Pin = PAN_SCK_Pin| PAN_MISO_Pin | PAN_MOSI_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
    }
}

/*!
 *********************************************************************************************
 * @brief Initialize all periphery needed for the sun sensors
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_SunSensInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO and SPI Clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOE, OpAmp_PS_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : OpAmp_PS_Pin*/
    GPIO_InitStruct.Pin = OpAmp_PS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    //Init ADC1
    MX_ADC1_Init();
}

/*!
 *********************************************************************************************
 * @brief DeInitialize all periphery needed for the sun sensors
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
void MCU_SunSensDeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // Enable GPIO and SPI Clocks

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOE, OpAmp_PS_Pin, GPIO_PIN_SET);

    /*Configure GPIO pins : OpAmp_PS_Pin*/
    GPIO_InitStruct.Pin = OpAmp_PS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // DeInit GPIOs
    GPIO_InitStruct.Pin = PAN1_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN5_IN_Pin|PAN2_IN_Pin|PAN3_IN_Pin|PAN4_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN6_IN_Pin|PAN6_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*!
 *********************************************************************************************
 * @brief Initialize all periphery needed for the SD cards
 *********************************************************************************************
 * @param[input]      cards:
 *                       + 1 - SD card 1
 *                       + 2 - SD card 2
 *                       + 3 - Both SD cards 1 and 2
 * @param[output]     none
 * @return            uint8_t:
 *                      + 1 - SD card 1 Successful
 *                      + 2 - SD card 2 Successful
 *                      + 3 - SD card 1 and 2 Successful
 *                      + dpFALSE- Fail
 * @note              none
 *********************************************************************************************
 */
static uint8_t MCU_SD_CardInit(uint8_t cards)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    FRESULT appl_fd_result = FR_INVALID_PARAMETER;
    uint8_t retStat = pdFALSE;

    // Enable GPIO and SPI Clocks
    __HAL_RCC_GPIOD_CLK_ENABLE();

    if( cards & 0x01 )
    {
        // Init GPIOs
        HAL_GPIO_WritePin(SD_EN_GPIO_Port, SD_EN_Pin, GPIO_PIN_RESET);

        /*Configure GPIO pins : PDPin PDPin */
        GPIO_InitStruct.Pin = SD_EN_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(SD_EN_GPIO_Port, &GPIO_InitStruct);
    }

    osDelay(1); //wait 1ms after enable of the Power supply


    if( cards & 0x01 )
    {
        MX_FATFS_Init();
        MX_SDMMC1_SD_Init();

        if (FR_OK == (appl_fd_result = f_mount(&SDFatFS)))
        {
            ES_TRACE_DEBUG("SD card mounted successfully.\r");

            retStat |= 0x01;
        }
        else{
            ES_TRACE_DEBUG("SD card fail err=%u.\r", appl_fd_result);

            //retStat = pdFALSE;  //Already set
        }
    }

    return retStat;
}

/*!
 *********************************************************************************************
 * @brief DeInitialize all periphery needed for the SD cards
 *********************************************************************************************
 * @param[input]      Sd_DetectDeInitEnable: 1 - deinitialize the detection pins, 0 - does not deinitialze it (used when the SD cards is just reset, this way some interrupts are skipped)
 * @param[input]      cards:
 *                       + 1 - SD card 1
 *                       + 2 - SD card 2
 *                       + 3 - Both SD cards 1 and 2
 * @param[input]      cardHwReset:
 *                       + 0 - reset only the SDIO and FAT file system on the MCU
 *                       + 1 - do a HW reset of the (power off, delay, power on) SD card 1
 *                       + 2 - do a HW reset of the (power off, delay, power on) SD card 2
 *                       + 3 - do a HW both SD cards 1 and 2
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
static void MCU_SD_CardDeInit(uint8_t Sd_DetectDeInitEnable, uint8_t cards, uint8_t cardHwReset)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if( cards & 0x01 )
    {
        // Enable GPIO and SPI Clocks
        if(cardHwReset & 0x01){
            HAL_GPIO_WritePin(SD_EN_GPIO_Port, SD_EN_Pin, GPIO_PIN_SET);
        }
        RCC_SDIO1_RESET();
        HAL_SD_MspDeInit(&hsd1); //__HAL_RCC_SDIO_CLK_DISABLE();
        memset( (uint8_t*)&hsd1, 0, sizeof( SD_HandleTypeDef ) );
        (void)f_umount(&SDFatFS);         //unmount SD1
        (void)FATFS_UnLinkDriver(&SDFatFS);
        memset( (uint8_t*)&SDFatFS, 0, sizeof( FATFS ) );
        // Init GPIOs for SD card 1
        GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    }

    if( Sd_DetectDeInitEnable > 0)
    {
        if( cards & 0x01 )
        {
            GPIO_InitStruct.Pin = SD_DET_Pin;
            GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            HAL_GPIO_Init(SD_DET_GPIO_Port, &GPIO_InitStruct);
        }
    }
}


/*!
 *********************************************************************************************
 * @brief Reset SD card and initialise all components needed to use it
 *********************************************************************************************
 * @param[input]      cards:
 *                       + 1 - SD card 1
 *                       + 2 - SD card 2
 *                       + 3 - Both SD cards 1 and 2
 * @param[input]      cardHwReset:
 *                       + pdTRUE - do a HW reset of the SD card (power off, delay, power on)
 *                       + pdFALSE - reset only the SDIO and FAT file system on the MCU
 * @param[output]     none
 * @return            uint8_t:
 *                      + 1 - SD card 1 Successful
 *                      + 2 - SD card 2 Successful
 *                      + 3 - SD card 1 and 2 Successful
 *                      + dpFALSE- Fail
 * @note              none
 *********************************************************************************************
 */
uint8_t MCU_InitSdCard(uint8_t cards, uint8_t cardHwReset)
{

    /////////////////////// RESET ALL PERIPHERY AND STRUCTURES /////////////////////////
    MCU_SD_CardDeInit(DISABLE, cards, cardHwReset);

    /////////////////////// INITIALISE ALL PERIPHERY AND STRUCTURES /////////////////////////
    if(cardHwReset == pdTRUE){
        sysDelay(250);   /* Wait until the capacitors discharge to 0V - Minimum time 80 ms */
    }

    return MCU_SD_CardInit(cards);
}

void MCU_Init_I2cPullUps_Nvm(void)
{
    i2c_config_t i2c_config;

    // read NVM I2C pull-up configuration...
    Nvm_GetBlockById(NVM_BLOCK_I2C_CONFIG, &i2c_config);

    I2CPullUpsState_t tmp_config;

    tmp_config.pins.sys_bus_4K7 = i2c_config.i2c_pull_up_config[I2C_BUS_SYSTEM].pull_up_4k7;
    tmp_config.pins.sys_bus_10K = i2c_config.i2c_pull_up_config[I2C_BUS_SYSTEM].pull_up_10k;
    tmp_config.pins.pay_bus_4K7 = i2c_config.i2c_pull_up_config[I2C_BUS_PAYLOAD].pull_up_4k7;
    tmp_config.pins.pay_bus_10K = i2c_config.i2c_pull_up_config[I2C_BUS_PAYLOAD].pull_up_10k;

    MCU_Init_I2cPullUps_Set(tmp_config);
}

void MCU_Init_I2cPullUps_Set(const I2CPullUpsState_t i2c_io_setting)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    /*Configure GPIO pins : SYS_I2C_4K7_Pin */
    GPIO_InitStruct.Pin = SYS_I2C_4K7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SYS_I2C_4K7_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : SYS_I2C_10K_Pin PAY_I2C_4K7_Pin PAY_I2C_10K_Pin */
    GPIO_InitStruct.Pin = SYS_I2C_10K_Pin|PAY_I2C_4K7_Pin|PAY_I2C_10K_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAY_I2C_4K7_GPIO_Port, &GPIO_InitStruct);

    // set GPIO pin output levels according to NVM configuration...
    // note: inverse logic is used for OBC pull-up control (these outputs control p-channel MOSFETs)
    HAL_GPIO_WritePin(SYS_I2C_4K7_GPIO_Port, SYS_I2C_4K7_Pin,
            (i2c_io_setting.pins.sys_bus_4K7) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET));
    HAL_GPIO_WritePin(SYS_I2C_10K_GPIO_Port, SYS_I2C_10K_Pin,
            (i2c_io_setting.pins.sys_bus_10K) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET));
    HAL_GPIO_WritePin(PAY_I2C_4K7_GPIO_Port, PAY_I2C_4K7_Pin,
            (i2c_io_setting.pins.pay_bus_4K7) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET));
    HAL_GPIO_WritePin(PAY_I2C_10K_GPIO_Port, PAY_I2C_10K_Pin,
            (i2c_io_setting.pins.pay_bus_10K) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET));
}

I2CPullUpsState_t MCU_Init_I2cPullUps_Get(void)
{
    I2CPullUpsState_t i2c_io_setting;

    i2c_io_setting.pins.sys_bus_4K7 =
            (GPIO_PIN_RESET == HAL_GPIO_ReadPin(SYS_I2C_4K7_GPIO_Port, SYS_I2C_4K7_Pin)) ? (true) : (false);

    i2c_io_setting.pins.sys_bus_10K =
            (GPIO_PIN_RESET == HAL_GPIO_ReadPin(SYS_I2C_10K_GPIO_Port, SYS_I2C_10K_Pin)) ? (true) : (false);

    i2c_io_setting.pins.pay_bus_4K7 =
            (GPIO_PIN_RESET == HAL_GPIO_ReadPin(PAY_I2C_4K7_GPIO_Port, PAY_I2C_4K7_Pin)) ? (true) : (false);

    i2c_io_setting.pins.pay_bus_10K =
            (GPIO_PIN_RESET == HAL_GPIO_ReadPin(PAY_I2C_10K_GPIO_Port, PAY_I2C_10K_Pin)) ? (true) : (false);

    return i2c_io_setting;
}

/*
 *********************************************************************************************
 * INTERNAL (STATIC) ROUTINES DEFINITION
 *********************************************************************************************
 */
/*!
 *********************************************************************************************
 * @brief Reset the SDIO controller
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
static void RCC_SDIO1_RESET(void)
{
    __HAL_RCC_SDMMC1_FORCE_RESET(); //RCC->APB2RSTR |= RCC_APB2RSTR_SDIORST;
    while( ( RCC->AHB3RSTR & RCC_AHB3RSTR_SDMMC1RST ) != RCC_AHB3RSTR_SDMMC1RST );
    osDelay(1);
    __HAL_RCC_SDMMC1_RELEASE_RESET(); //RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST);
    while( ( RCC->AHB3RSTR & RCC_AHB3RSTR_SDMMC1RST ) == RCC_AHB3RSTR_SDMMC1RST );
}

//////////////
// Programmable voltage detector (PVD) stuff
void PVD_BrownoutReset_Init()
{
    //__HAL_RCC_PWR_CLK_ENABLE();   // Enable Power Clock //??? Commented because of H7xx
    //Configure the NVIC for PVD
    HAL_NVIC_SetPriority(PVD_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(PVD_IRQn);
    // Configure the PVD Level to 7 (3.03V-3.14V)
    PWR_PVDTypeDef sConfigPVD;
    sConfigPVD.PVDLevel = PWR_PVDLEVEL_6;
    sConfigPVD.Mode = PWR_MODE_IT_RISING_FALLING;
    HAL_PWR_PVDConfig(&sConfigPVD);
    // Enable the PVD Output
    HAL_PWR_EnablePVD();

    // Brownout reset enable
    FLASH_OBProgramInitTypeDef sOBProgramInitTypeDef;
    HAL_FLASHEx_OBGetConfig(&sOBProgramInitTypeDef); // Get BOR Option Bytes
    if((sOBProgramInitTypeDef.BORLevel & 0x0F) != OB_BOR_LEVEL3)
    {
        HAL_FLASH_OB_Unlock(); // Unlocks the option bytes block access
        //??? Changed because of H7xx
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_OPERR|FLASH_FLAG_WRPERR|FLASH_FLAG_PGSERR|FLASH_FLAG_BSY); // Clears the FLASH pending flags
        memset(&sOBProgramInitTypeDef, 0, sizeof(FLASH_OBProgramInitTypeDef));
        sOBProgramInitTypeDef.OptionType = OPTIONBYTE_BOR;
        sOBProgramInitTypeDef.BORLevel = OB_BOR_LEVEL3; // Select the desired V(BOR) Level
        HAL_FLASHEx_OBProgram(&sOBProgramInitTypeDef);
        HAL_FLASH_OB_Launch(); // Launch the option byte loading
    }
}

//When the voltage rail powering the MCU goes below 2.9V, the PVD interrupt is triggered causing it to call the IRQ handler below:
void HAL_PWR_PVDCallback(void)
{
    //Write_EEPROM();
    if (READ_BIT(PWR->CSR1, PWR_CSR1_PVDO))
    {
        // VDD is lower than the PVD threshold selected with the PLS[2:0] bits
        ES_TRACE_DEBUG("\r\n --- VDD is low ---\r\n");
    } else
    {
        //  VDD is higher than the PVD threshold selected with the PLS[2:0] bits
        ES_TRACE_DEBUG("\r\n--- VDD is normal ---\r\n");
    }
    // Note: The PVD is stopped by Standby mode. For this reason, this bit is equal to 0 after
    // Standby or reset until the PVDE bit is set.
}
