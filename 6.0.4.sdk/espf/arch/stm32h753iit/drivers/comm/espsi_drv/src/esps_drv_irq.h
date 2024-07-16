/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_IRQ_H
#define ESPS_DRV_IRQ_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_irq.h
 * @brief    Transmit/Receive Interrupt function declarations
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "esps_drv_ct.h"

/******************************************************************************
 * Private Preprocessor Definitions
 *****************************************************************************/
/// Set as a default value before the priority calculation
#define MAC_PRIORITY_INVALID  (0U)
/// To help verify the received or sent Address
#define MAC_ADDRESS_MASK      (0x100U)

/******************************************************************************
 * Private Types
 *****************************************************************************/

/******************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

/**
 * Indication function when a new byte has been received on a interface.
 * Called from interrupt.
 *
 * @param fp_psState - state that has a new byte received.
 */
    void MAC_IRQ_vRXIndication(sMACInterfaceState_t * fp_psState);

/**
 * Reception start indication function to be called when reception is started.
 *
 * @param fp_psState - state to start the reception for.
 */
    void MAC_IRQ_vRXStartIndication(sMACInterfaceState_t * fp_psState);

/**
 * When we are transmitting and there is an RX ISR, then
 * this is assumed to be an echo of what we just transmitted
 *
 * @param fp_psState - state where the echo is detected
 */
    void MAC_IRQ_vTxEchoIndication(sMACInterfaceState_t * fp_psState);

/**
 * Called when new data has been received on UART/USART.
 *
 * @param fp_psState - the MAC interface state that received a byte.
 */
    void MAC_IRQ_vTXIndication(sMACInterfaceState_t * fp_psState);

/**
 * Transmission finished indication, called when sending a byte is completed.
 *
 * @param fp_psState - the MAC interface state.
 */
    void MAC_IRQ_vTXFinishedIndication(sMACInterfaceState_t * fp_psState);

/**
 * Request the transmission to move out from idle. This function should
 * be called when transmission is desired.
 *
 * @param fp_psState - the MAC interface state.
 */
    void MAC_IRQ_vTXRequestIndication(sMACInterfaceState_t * fp_psState);

/**
 * Request the transmitter to process an event.
 *
 * @param fp_psState - the MAC interface state.
 * @param fp_eEvent  - the event to process.
 */
    void MAC_IRQ_vTXProcessEvent(sMACInterfaceState_t * fp_psState, eTXEvent_t fp_eEvent);

    void MAC_IRQ_vRXProcessEvent(sMACInterfaceState_t * fp_psState, eRXEvent_t evt);

#ifdef __cplusplus
}
#endif

#endif //ESPS_DRV_IRQ_H
