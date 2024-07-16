/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_MAC_H
#define ESPS_DRV_MAC_H

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup espsi_drv ESPS I MAC Driver
 * @{
 *
 * Driver for the MAC Layer of the ESPS I over RS-485.
 *
 * Usage:
 *
 *  - Populate the configuration <tt>fs_MacConfig</tt> in <tt>esps_drv_config.c</tt>
 *  - Pass it to the interface state <tt>fs_asMACStates</tt> in <tt>esps_drv_config.c</tt>
 *  - Send messages to the network by calling <tt>MAC_DrvEnqMessage</tt>, configured
 *   in in <tt>ESSA_StackConfig.c</tt>
 *  - The received messages will be dispatched when <tt>MAC_DISP_vDispatchMessages</tt>
 *   is called in <tt>esps_drv_dispatcher_thread.c</tt>
 *
 * @file     esps_drv.h
 *
 * @brief    ESPS I MAC Driver interface
 *
 * @}
 * @}
 *
 */

// External imports
#include "esps_drv_esps_stack.h"

#include "esps_drv_ct.h"
#include "esps_drv_cdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Public Types
 *****************************************************************************/

/******************************************************************************
 * Public Functions Declarations
 *****************************************************************************/

/**
 * Performs the core initialization of the related peripherals used by all MAC interfaces.
 *
 * @retval true: initialization successful
 * @retval false: error occurred
 */
bool MAC_bCoreInit(void);

/**
 * Performs the core deinitialization of the related peripherals used by all MAC interfaces.
 *
 * @retval true: deinitialization successful
 * @retval false: error occurred
 */
bool MAC_bCoreDeinit(void);

/**
 * Start all configured MAC interfaces.
 * @param fp_eInitType: type of init to be performed;
 *
 * @retval true: all interfaces are running
 * @retval false: an error occurred
 */
bool MAC_bStartAllIfs(const eMAC_Interface_InitType_t fp_eInitType);

/**
 * Function to stop all configured MAC interfaces.
 * @retval true: all interfaces are stop
 * @retval false: an error occurred
 */
bool MAC_bStopAllIfs(void);

/**
 * Function to start a MAC interface. Initializes the USART/UART peripheral,
 * state values and starts the dispatcher thread for the messages received.
 *
 * @param fp_eInterface: the interface to start
 * @param fp_eInitType: type of init to be performed
 *
 * @retval true: interface running
 * @retval false: an error occurred
 */
bool MAC_bStart(eMACInterface_t fp_eInterface, const eMAC_Interface_InitType_t fp_eInitType);

/**
 * Function to stop a MAC interface. Deinitializes the USART/UART peripheral and
 * stops the dispatcher thread.
 * All messages still pending to be transmitted will be released and all blocked
 * threads for transmission will be unblocked, any pending send operations will
 * return failure.
 *
 * @param fp_eInterface
 * @retval true: interface stopped successfully
 * @retval false: an error occurred
 */
bool MAC_bStop(eMACInterface_t fp_eInterface);

/**
 * This function will be the control of a loop that reads and processes the RX messages.
 * Messages should be processed with the function MAC_bProtocolProcessMessage.
 *
 * @retval true: there are messages in the RX pool
 * @retval false: the RX pool is empty
 */
bool MAC_bMessageInQueue(const eMACInterface_t fp_eMacInterfaceId);

/**
 * Declaration of the dispatch function. This function should be defined and
 * it should dispatch the messages to the corresponding protocol.
 *
 * @param fp_eMACId: MAC interface ID
 * @param fp_psMsg: reference to the message
 * @retval true: the message was sent to the corresponding protocol
 * @retval false: ESPS stack failed to dispatch the message
 */
bool MAC_bProtocolProcessMessage(eMACInterface_t fp_eMACId, ESSATMAC_Message * fp_psMsg);

/**
 * Add a message to the driver RX queue to be sent when possible.
 *
 * @param fp_pMACContext: ESSA Stack Context for the Message
 * @param fp_pMsgData: message
 * @param fp_nMsgDataSize: size
 * @return <tt>ESSATMAC_ErrCodes</tt>: result of the processed message
 */
ESSATMAC_ErrCodes MAC_DrvEnqMessage(ESSATMAC_Context * fp_pMACContext, uint8_t * fp_pMsgData,
                                    uint8_t fp_nMsgDataSize);

/**
 * Treat UART interrupt events
 *
 * @param fp_psState: MAC interface state structure
 */
void MAC_vDispatchUARTEvent(sMACInterfaceState_t * fp_psState);

/**
 * Start the MAC-interface-related interrupts to avoid race conditions
 *
 * @param fp_psIntf: MAC interface state structure
 */
void MAC_vEnterCriticalSection(sMACInterfaceState_t * const fp_psIntf);
/**
 * Stop the MAC-interface-related interrupts to avoid race conditions
 *
 * @param fp_psIntf: MAC interface state structure
 */
void MAC_vLeaveCriticalSection(sMACInterfaceState_t * const fp_psIntf);

#ifdef __cplusplus
}
#endif

#endif //ESPS_DRV_MAC_H
