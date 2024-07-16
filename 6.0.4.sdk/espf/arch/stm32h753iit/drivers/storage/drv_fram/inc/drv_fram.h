/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef DRV_FRAM_H
#define DRV_FRAM_H

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup drv_fram ExtFram Driver
 * @{
 * This is a basic driver for the OBC PCB-mounted CY15B102Q FRAM chip from Cypress.
 * It provides all standard functions (identification, read, write, sleep, wakeup, etc.)
 * and its primary purpose is to give you a quick start with the FRAM while keeping the
 * driver simple and easy to use.
 *
 * @attention Please, make sure that the module is initialized by calling `ExtFram_Init`
 *      before using it.
 *
 * @note The maximum size of read/write operations is limited to the size of the internal
 *      read buffer (`EXT_FRAM_RX_BUFF_SIZE`) which is also used during write operations to
 *      perform data verification. The interface of the driver also limits the size to a
 *      1-byte-value for that reason. However, there is no physical limitation on the amount
 *      of bytes transferred to/from the FRAM chip, hence you can modify the driver to use bigger
 *      buffer sizes if you need so.
 *
 * @file drv_fram.h
 *
 * @brief Header of drv_fram.c
 *
 * @}
 * @}
 *
*/

#include <stdbool.h>
#include <stdint.h>


#define FRAM_RX_BUFF_SIZE (512) // maximum size which can be accommodated for a single read or write
#define FRAM_DEV_ID_LENTH (9)


/**
 * @brief Init routine for the FRAM component
 *
 * @return            true if all initialized
 */
bool FRAM_Init(void);


/**
 * @brief Deinit routine for the FRAM component
 *
 * @return            true if everything deinitiallized
 */
bool FRAM_DeInit(void);


/**
 * @brief Enabled writing latch (disable the write protection)
 */
void FRAM_WriteEnable(void);


/**
 * @brief Disabled writing latch (Enable the write protection)
 */
void FRAM_WriteDisable(void);


/**
 * @brief Write the status register
 *
 * @param[input]      status: register value
 */
void FRAM_WriteStatusReg(uint8_t status);


/**
 * @brief Read the status register of the FRAM
 *
 * @return            uint8_t - returns the value of the status register
 */
uint8_t FRAM_ReadStatusReg(void);


/**
 * @brief Read data
 *
 * @param[input]      address: starting byte to start reading from
 * @param[input]      size: number of bytes to be read
 * @param[output]     dataBuff: buffer to retrun the read bytes
 * @return            true on successful read
 */
bool FRAM_ReadData(uint32_t address,uint16_t size, uint8_t * dataBuff);


/**
 * @brief Fast Read data
 *
 * @param[input]      size: number of bytes to read
 * @param[output]     dataBuff: buffer to return the read bytes
 */
void FRAM_FastReadData(uint16_t size, uint8_t * dataBuff);


/**
 * @brief Write data
 *
 * @param[input]      address: byte where to start writing
 * @param[input]      size: number of bytes to be written
 * @param[inpt]       dataBuff: bytes to be written
 * @return            true if successful writing
 */
bool FRAM_WriteData(uint32_t address, uint16_t size, uint8_t * dataBuff);


/**
 * @brief Enter Sleep Mode
 */
void FRAM_EnSleep(void);


/**
 * @brief Wake up (send dummy read and wait 450 us)
 */
void FRAM_Wake(void);


/**
 * @brief Read the Device ID of the FRAM
 *
 * @param[output]     buffer: read the ID into the buffer
 * @param[output]     buffer_sz: amounts of bytes read
 */
void FRAM_Read_DevID(uint8_t* buffer, uint8_t buffer_sz);

#endif /* DRV_FRAM_H */
