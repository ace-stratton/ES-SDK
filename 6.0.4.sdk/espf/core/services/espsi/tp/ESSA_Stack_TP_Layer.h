/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESSA_STACK_TP_LAYER_H_
#define ESSA_STACK_TP_LAYER_H_

/**
 * @addtogroup Services
 * @{
 *
 * @addtogroup ESPS_I
 * @{
 *
 * @defgroup tp Transport Layer
 * @{
 *
 * Service to handle the Transport Layer from the ESPS I Stack
 *
 * @file ESSA_Stack_TP_Layer.h
 * @brief TP layer handler declarations
 *
 * @}
 * @}
 * @}
 *
 */

/** Return codes for the TP layer function to block the thread */
typedef enum
{
    THREADBlOCKEVT_WAITFINISHED, /**< Received the releasing event before timeout */
    THREADBLOCKEVT_WAITTIMEOUT, /**< Timeout before the event was received */
    THREADBLOCKEVT_ERROR, /**< An undefined error ocurred */
    THREADBLOCKEVT_MAX
} eThreadBlockEvt_t;

/**
 * @brief Initialization of the ESPS I stack transport layer
 */
void ESSA_Stack_TP_Layer_Init(void);

/**
 * @brief Reset the local flags to prepare the TP thread to wait for an event
 */
void ESSA_Stack_TP_Layer_PrepareThreadWait(void);

/**
 * @brief Block the TP thread until an event is triggered
 * @see ESSA_Stack_TP_Layer_ReleaseThreadWait
 * @param u32TimeoutMs: timeout in milliseconds to wait for the event
 */
eThreadBlockEvt_t ESSA_Stack_TP_Layer_ThreadWaitForEvent(uint32_t u32TimeoutMs);

/**
 * @brief Trigger the event that will release the TP thread
 * @see ESSA_Stack_TP_Layer_ThreadWaitForEvent
 */
void ESSA_Stack_TP_Layer_ReleaseThreadWait(void);

#endif // ESSA_STACK_TP_LAYER_H_
