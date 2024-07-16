/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_DEF_H
#define ESPS_DRV_DEF_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_def.h
 * @brief    Basic configuration for the supported MAC RS485 interfaces
 *
 * @}
 */

/**
 * Enumeration with all possible MAC interfaces.
 * By default only the primary interface is defined.
 */
typedef enum {
	/// Primary MAC/RS485 physical interface.
	eMAC_Interface_Primary = 0U,
	/// Count of avilable MAC/RS485 interfaces.
	eMAC_Interface_Count
} eMACInterface_t;

// The following symbolic names shall be used with the fp_bFullInit parameter of
// MAC_bStartAllIfs() and MAC_bStart()
typedef enum {
	MACIF_INITTYPE_FULL = 0,
	MACIF_INITTYPE_UART_ONLY = 1,
	MACIF_INITTYPE_MAX
} eMAC_Interface_InitType_t;

/**
 ******************************************************************************
 * Configuration options for the ESPS Driver
 ******************************************************************************
 */

/// Comment this if you don't need to report the Exceptions.
#define ESPS_CONFIG_EXEH_ENABLE

/// Debug trace, ESPS_CONFIG_DEBUG_ENABLE must also be defined for some of the traces inside the driver
//#define ESPS_CONFIG_DEBUG_ENABLE
//#define ESPS_CONFIG_DEBUG_TRACE_ENABLE

/// MAC UART Interface configuration definitions
#define MAC_UART_ISR_PRIO                       (6U)
#define MAC_TX_ECHO_MONITOR_GUARD_TIMEOUT_US    (10000U)

/// Count of reception memory pool entries (set to number of threads that can send MAC messages).
#define MAC_TXMEMORYPOOL_COUNT     (30U)
/// Count of transmission memory pool entries.
#define MAC_RXMEMORYPOOL_COUNT     (30U)
/// Max number of bytes to be transmitted at once with the UART
#define MAC_TRANSMIT_MAX_CMD_COUNT (3U)

/// Timeout in ms for one Tx attempt before increasing priority (time for Tx of 400 bytes + margin)
#define RS485_MAX_TX_WAIT_TIMEOUT  ((uint32_t) 88)

/// Timeout for retrying to allocate a new message when the allocation failed.
#define MAC_WAIT_POOLMEMORY_TIME   (2000U)

/// Default Configuration for the MAC interface
#define MAC_DEFAULT_BAUDRATE         (50000U)
#define MAC_DEFAULT_TQ               (360U)
#define MAC_DEFAULT_BASEPRIO         (0U)
#define MAC_DEFAULT_ADDRESS_PRI      (0x33U)

// For compatibility with the OBC build
#define MAC_SYS1_ADDRESS_PRI      MAC_DEFAULT_ADDRESS_PRI

/**
 ******************************************************************************
 * Parameters taken from the ESSA Network Stack configuration:
 ******************************************************************************
 */
/// Time span value in TQ for random constituent of the wait priority phase
#define RS485_MAX_RND_TIME_VALUE   (ESSASMP_PRIORITY_TQ_SPAN)
/// Maximum retries before increasing the dynamic priority of the interface by 1TQ
#define RS485_MAX_TX_RETRY_COUNT   (ESSASMP_PRIORITY_TQ_SPAN)
/// The minimum priority a message can have. When reaching this priority the retry will not be attempted.
#define RS485_MINIMUM_PRIORITY     (ESSASMP_HIGH)
/// Initial value for the Dynamic priority of the MAC Device
#define RS485_INITIAL_PRIORITY     (ESSASMP_LOW)

#ifdef __cplusplus
}
#endif

#endif // ESPS_DRV_DEF_H
