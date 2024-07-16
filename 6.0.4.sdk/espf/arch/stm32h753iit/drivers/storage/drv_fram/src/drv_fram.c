/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup drv_fram
 * @{
 *
 * @file     drv_fram.c
 * @brief    Driver for external 2-Mbit (256 K × 8) FRAM CY15B102Q
 *
 * @}
 */

#include "../inc/drv_fram.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_spi.h"
#include <string.h>


#define EXT_FRAM_MAX_RETRY               (3)
#define EXT_FRAM_TIMEOUT_MS              (50)

#define SPI4_FRAM_CHIP_SELECT_Pin        GPIO_PIN_11
#define SPI4_FRAM_CHIP_SELECT_GPIO_Port  GPIOE
#define FRAM_CS_GPIO_PORT_CLOCK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE();
#define SPI4_FRAM_SCK_Pin                GPIO_PIN_12
#define SPI4_FRAM_SCK_GPIO_Port          GPIOE
#define SPI4_FRAM_MISO_Pin               GPIO_PIN_13
#define SPI4_FRAM_MISO_GPIO_Port         GPIOE
#define SPI4_FRAM_MOSI_Pin               GPIO_PIN_14
#define SPI4_FRAM_MOSI_GPIO_Port         GPIOE


static uint8_t ExtFram_RxBuffer[2][FRAM_RX_BUFF_SIZE];
static uint8_t ExtFram_TxBuffer[FRAM_RX_BUFF_SIZE + 4];
static SPI_HandleTypeDef hspi4;


static bool ExtFram_Transfer(uint8_t* txBuffer, uint16_t txSize, uint8_t* rxBuffer, uint16_t rxSize);
static uint8_t ExtFram_SafeRead(uint8_t* txBuffer, uint16_t txSize, uint8_t* rxBuffer, uint16_t rxSize);
static void FRAM_MspInit(SPI_HandleTypeDef* hspi);
static void FRAM_MspDeInit(SPI_HandleTypeDef* hspi);


bool FRAM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    FRAM_CS_GPIO_PORT_CLOCK_ENABLE();

    GPIO_InitStruct.Pin   = SPI4_FRAM_CHIP_SELECT_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SPI4_FRAM_CHIP_SELECT_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(SPI4_FRAM_CHIP_SELECT_GPIO_Port, SPI4_FRAM_CHIP_SELECT_Pin, GPIO_PIN_SET);

	hspi4.Instance               = SPI4;
	hspi4.Init.Mode              = SPI_MODE_MASTER;
	hspi4.Init.Direction         = SPI_DIRECTION_2LINES;
	hspi4.Init.DataSize          = SPI_DATASIZE_8BIT;
	hspi4.Init.CLKPolarity       = SPI_POLARITY_LOW;
	hspi4.Init.CLKPhase          = SPI_PHASE_1EDGE;
	hspi4.Init.NSS               = SPI_NSS_SOFT;
	hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi4.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	hspi4.Init.TIMode            = SPI_TIMODE_DISABLE;
	hspi4.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	hspi4.Init.CRCPolynomial     = 7;
	hspi4.Init.CRCLength         = SPI_CRC_LENGTH_DATASIZE;
	hspi4.Init.NSSPMode          = SPI_NSS_PULSE_ENABLE;

	if (HAL_OK != HAL_SPI_RegisterCallback(&hspi4, HAL_SPI_MSPINIT_CB_ID, FRAM_MspInit))
	{
		return false;
	}

	if (HAL_OK != HAL_SPI_Init(&hspi4))
	{
		return false;
	}

	return true;
}


bool FRAM_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    HAL_GPIO_WritePin(SPI4_FRAM_CHIP_SELECT_GPIO_Port, SPI4_FRAM_CHIP_SELECT_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin   = SPI4_FRAM_CHIP_SELECT_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SPI4_FRAM_CHIP_SELECT_GPIO_Port, &GPIO_InitStruct);

	if (HAL_OK != HAL_SPI_RegisterCallback(&hspi4, HAL_SPI_MSPDEINIT_CB_ID, FRAM_MspDeInit))
	{
		return false;
	}

    if (HAL_OK != HAL_SPI_DeInit(&hspi4))
	{
		return false;
	}

	return true;
}


void FRAM_WriteEnable(void)
{
    uint8_t TxData = 0x06; //Opcode RDSR (Read status register)
    uint8_t RxData;

    (void)ExtFram_Transfer(&TxData, 1, &RxData, 0);
}


void FRAM_WriteDisable(void)
{
    uint8_t TxData = 0x04; //Opcode RDSR (Read status register)
    uint8_t RxData;

    (void)ExtFram_Transfer(&TxData, 1, &RxData, 0);
}


void FRAM_WriteStatusReg(uint8_t status)
{
    uint8_t TxData[2] = {0x01, status}; //Opcode RDSR (Read status register)
    uint8_t RxData;

    (void)ExtFram_Transfer(TxData, 2, &RxData, 0); //VMI_TODO_EXT_FRAM Use safe write
}


uint8_t FRAM_ReadStatusReg(void)
{
    uint8_t TxData = 0x05; //Opcode RDSR (Read status register)
    uint8_t RxData = 0;

    (void)ExtFram_SafeRead(&TxData, 1, &RxData, 1);

    return RxData;
}


bool FRAM_ReadData(uint32_t address, uint16_t size, uint8_t* dataBuff)
{
    uint8_t TxData[4] = {0x03, (uint8_t)(address >> 16), (uint8_t)(address >> 8), (uint8_t)(address)}; //Opcode READ (Read memory data)

    return ExtFram_Transfer(TxData, 4, dataBuff, size);
}


void FRAM_FastReadData(uint16_t size, uint8_t* dataBuff)
{
    // TODO: FRAM fast read not needed for now
}


bool FRAM_WriteData(uint32_t address, uint16_t size, uint8_t * dataBuff)
{
    uint8_t TxData[4] = {0x02, (uint8_t)(address >> 16), (uint8_t)(address >> 8), (uint8_t)(address)}; //Opcode READ (Read memory data)
    bool bWriteSuccessful = false;

    memcpy(ExtFram_TxBuffer,TxData, 4);
    memcpy(&ExtFram_TxBuffer[4],dataBuff, size);

    FRAM_WriteEnable();

    for (uint8_t i = 0; i < EXT_FRAM_MAX_RETRY; i++)
    {
        (void)ExtFram_Transfer(ExtFram_TxBuffer, 4+size, dataBuff, 0);

        bWriteSuccessful = FRAM_ReadData(address,size, ExtFram_RxBuffer[1]);

        if (memcmp(&ExtFram_TxBuffer[4], ExtFram_RxBuffer[1], size) == 0)
        {
            break;
        }
    }

    FRAM_WriteDisable();

    return bWriteSuccessful;
}


void FRAM_EnSleep(void)
{
    uint8_t TxData = 0xB9; //Opcode SLEEP (Enter sleep mode)
    uint8_t RxData = 0;

    (void)ExtFram_Transfer(&TxData, 1, &RxData, 0);
}


void FRAM_Wake(void)
{
    (void)FRAM_ReadStatusReg();
}


void FRAM_Read_DevID(uint8_t* buffer, uint8_t buffer_sz)
{
	if (buffer_sz < FRAM_DEV_ID_LENTH)
	{
		return;
	}

    uint8_t TxData = 0x9F; //Opcode RDSR (Read status register)

    (void)ExtFram_Transfer(&TxData, 1, buffer, FRAM_DEV_ID_LENTH);
}


/*!
********************************************************************************************
* @brief Read the Device ID of the FRAM
********************************************************************************************
* @param[input]      txBuffer - write data
* @param[input]      txSize - number of bytes to send
* @param[input]      rxSize - number of bytes to receive
* @param[output]     rxBuffer - read data
* @return            uint8_t:
*                       + 1 - OK
*                       - 0 - Failed
* @note              none
********************************************************************************************
*/
static bool ExtFram_Transfer(uint8_t* txBuffer, uint16_t txSize, uint8_t* rxBuffer, uint16_t rxSize)
{
    HAL_StatusTypeDef statusTx = HAL_OK;
    HAL_StatusTypeDef statusRx = HAL_OK;

    HAL_GPIO_WritePin(SPI4_FRAM_CHIP_SELECT_GPIO_Port, SPI4_FRAM_CHIP_SELECT_Pin, GPIO_PIN_RESET);

    if (txSize > 0U)
    {
        statusTx = HAL_SPI_Transmit(&hspi4, txBuffer, txSize, EXT_FRAM_TIMEOUT_MS);
    }

    if (rxSize > 0U)
    {
    	statusRx = HAL_SPI_Receive(&hspi4, rxBuffer, rxSize, EXT_FRAM_TIMEOUT_MS);
    }

    HAL_GPIO_WritePin(SPI4_FRAM_CHIP_SELECT_GPIO_Port, SPI4_FRAM_CHIP_SELECT_Pin, GPIO_PIN_SET);

    return ((statusTx == HAL_OK) && (statusRx == HAL_OK)) ? (true) : (false);
}


/*!
********************************************************************************************
* @brief Read the Device ID of the FRAM
********************************************************************************************
* @param[input]      txBuffer - write data
* @param[input]      txSize - number of bytes to send
* @param[input]      rxSize - number of bytes to receive
* @param[output]     rxBuffer - read data
* @return            uint8_t:
*                       + 1 - OK
*                       - 0 - Failed
* @note              none
********************************************************************************************
*/
static uint8_t ExtFram_SafeRead(uint8_t* txBuffer, uint16_t txSize, uint8_t* rxBuffer, uint16_t rxSize)
{
    int readStatus;
    uint8_t retStat = 0;

    if (rxSize <= FRAM_RX_BUFF_SIZE)
    {
        for (uint8_t i = 0; i < EXT_FRAM_MAX_RETRY; i++)
        {
            ExtFram_Transfer(txBuffer, txSize, ExtFram_RxBuffer[0], rxSize);

            if (rxSize <= 0)
            {
                // if no bytes are going to be read, there is nothing to compare
                break;
            }

            ExtFram_Transfer(txBuffer, txSize, ExtFram_RxBuffer[1], rxSize);

            readStatus = memcmp(ExtFram_RxBuffer[0], ExtFram_RxBuffer[1], rxSize);

            if (readStatus == 0)
            {
                memcpy(rxBuffer, ExtFram_RxBuffer[0], rxSize);
                retStat = 1;
                break;
            }
        }
    }

    return retStat;
}


static void FRAM_MspInit(SPI_HandleTypeDef* hspi)
{
	if (hspi->Instance == SPI4)
	{
	    GPIO_InitTypeDef GPIO_InitStruct = {0};

		__HAL_RCC_SPI4_CLK_ENABLE();
		__HAL_RCC_GPIOE_CLK_ENABLE();

		GPIO_InitStruct.Pin       = SPI4_FRAM_SCK_Pin | SPI4_FRAM_MISO_Pin | SPI4_FRAM_MOSI_Pin;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_NOPULL;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	}
}


static void FRAM_MspDeInit(SPI_HandleTypeDef* hspi)
{
	if (hspi->Instance == SPI4)
	{
		__HAL_RCC_SPI4_CLK_DISABLE();

		HAL_GPIO_DeInit(GPIOE, SPI4_FRAM_SCK_Pin | SPI4_FRAM_MISO_Pin | SPI4_FRAM_MOSI_Pin);

		HAL_NVIC_DisableIRQ(SPI4_IRQn);
	}
}
