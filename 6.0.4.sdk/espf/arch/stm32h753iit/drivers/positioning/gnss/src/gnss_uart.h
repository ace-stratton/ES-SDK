/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GNSS_UART_H_
#define GNSS_UART_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_uart.h
 *
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


/** @brief Single RX buffer data field maximum size */
#define GNSS_UART_BUFFER_DATA_SZ (512)


/** @brief Defines the structure of the UART RX message */
typedef struct
{
    uint8_t  data[GNSS_UART_BUFFER_DATA_SZ]; /**< received data */
    uint32_t data_sz;                        /**< received data size */
} gnss_uart_resp_t;


/** @brief */
typedef void(*gnss_uart_rx_callback)(void);


/**
 * @brief Registers user callback which is called on every RX event.
 *
 * @note The function will be called for IRQ context.
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_uart_reg(gnss_uart_rx_callback callback);

/**
 * @brief Initialise UART peripheral with specific baudrate
 *
 * @param[in] baudrate UART baudrate
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_uart_init(const uint32_t baudrate);

/**
 * @brief De-Initialise UART peripheral
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_uart_deinit(void);

/**
 * @brief Receive raw ASCII response
 *
 * @param[out] resp On success will contain GNSS response
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_uart_rx(gnss_uart_resp_t* resp);

/**
 * @brief Transmit ASCII data to GNSS
 *
 * @note The driver adds the termination symbols (\r\n) internally.
 *
 * @param[in] data    Data to be transmitted
 * @param[in] data_sz Size of the data in bytes
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_uart_tx(const uint8_t* data, const uint16_t data_sz);


#ifdef __cplusplus
}
#endif

#endif /* GNSS_UART_H_ */
