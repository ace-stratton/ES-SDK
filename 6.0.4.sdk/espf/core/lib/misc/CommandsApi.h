/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef COMMANDSAPI_H
#define COMMANDSAPI_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup misc Miscellaneous
 * @{
 *
 * Different libraries or utilities.
 *
 * - Commands API
 *
 * @file CommandsApi.h
 * @brief Public interface of the Commands API
 *
 * @}
 * @}
 */

#include "User_types.h"
#include "DAT_Inputs.h"
#include "nvm/inc/nvm.h"


#pragma pack(push)
#pragma pack(1)

typedef enum {
    HWRES_SUCCESS,
    HWRES_ERROR,
    HWRES_DISABLED
} HwRes_t;

typedef enum {
    STDRESULT_SUCCESS,
    STDRESULT_ERROR,
    STDRESULT_INVALID_ARGS
} StdResult_t;

typedef struct {
    uint8_t gpioStatusBitField;
} GpioStat_t;

typedef enum
{
    APPMODE_APPLICATION,
    APPMODE_BOOTLOADER,
    APPMODE_AUTO_FW_UPDATE,
    APPMODE_MAX
} AppMode_t;

#pragma pack(pop)


void CommandsApi_GPIO_Init(void);
void CommandsApi_Gpo_Set(const MCU_Init_OutStates_struct * const states);
GpioStat_t ReadHandler_GpOutputState(void);
HwRes_t WriteHandler_GpOutputState(uint8_t pin, uint8_t value);
StdResult_t WriteHandler_ResetInBootOrAppMode(const AppMode_t appMode);

#endif    /* COMMANDSAPI_H */

