/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup es_panels
 * @{
 *
 * @file     panels.c
 * @brief    Manage the panels with all the sensors ( magnetorquer, gyroscope, temeperature sensor, sun sensor )
 *
 * @}
 *
 */

#include "FreeRTOS.h"
#include "task.h"

#include "stm32h7xx_hal.h"
#include "main.h"
#include "MCU_Init.h"
#include "cmsis_os.h"
#include "panels.h"
#include <stdio.h>
#include "math.h"

#include <stdint.h>
#include <string.h>

/*
*********************************************************************************************
 * INTERNAL DEFINES
*********************************************************************************************
 */
#define    __no_operation()            __asm volatile("nop");

static uint8_t Panel_Magnetorqer_Power[3] = { 0, 0, 0 };
static uint8_t Panel_Magnetorqer_Direction[3] = { 0, 0, 0 };

static PWM_Cntrl_t sPWMCntrl[3] = {
    {
     .TIM_CHANNEL = TIM_CHANNEL_1,
     {
      .port = PAN4_DIR1_GPIO_Port,
      .pin = PAN4_DIR1_Pin,
      }
     },
    {
     .TIM_CHANNEL = TIM_CHANNEL_2,
     {
      .port = PAN5_DIR1_GPIO_Port,
      .pin = PAN5_DIR1_Pin,
      }
     },
    {
     .TIM_CHANNEL = TIM_CHANNEL_3,
     {
      .port = PAN6_DIR1_GPIO_Port,
      .pin = PAN6_DIR1_Pin,
      }
     },
};

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
 * @brief Array of MAX_PAN (6) elements, representing panels' photometric sensor data input
 */
uint16_t PanelLight[MAX_PAN] = { 0, 0, 0, 0, 0, 0 };

/**
 * @brief Array of MAX_PAN (6) elements, representing panels' thermoelectric sensor data input
 */
uint16_t PanelTemp[MAX_PAN] = { 0, 0, 0, 0, 0, 0 };

/*
*********************************************************************************************
 * INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
 */
/**
 * @brief Bitmask, defining mounted and active panels to gather data from (luminescence and temperature)
 */
static volatile uint8_t PanelStat = 0;


static const uint32_t AdcChannel[MAX_PAN] = { ADC_CHANNEL_10, ADC_CHANNEL_15, ADC_CHANNEL_18, ADC_CHANNEL_19, ADC_CHANNEL_3, ADC_CHANNEL_9 }; //??? Changed because of H7xx

/*
*********************************************************************************************
 * EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*********************************************************************************************
 */
/*!
*********************************************************************************************
 * @brief Panels initialisation routine
*********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              Temp sensor power shall have been enabled before calling this function
 * 					  otherwise panel detection won't work correctly.
*********************************************************************************************
 */
void Panels_ChipSelect2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    // Enable GPIO and SPI Clocks
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    PanelStat = 0;

    /*Configure GPIO pin Output Level */
    // Configure all panel temperature sensors CS as inputs with pull-down
    GPIO_InitStruct.Pin = PAN5_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN5_CS2_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN1_CS2_Pin | PAN3_CS2_Pin | PAN4_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN6_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN6_CS2_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN2_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN2_CS2_GPIO_Port, &GPIO_InitStruct);

    sysDelay(2);

    if (HAL_GPIO_ReadPin(PAN1_CS2_GPIO_Port, PAN1_CS2_Pin))
        PanelStat |= (1 << PAN_X_P);
    if (HAL_GPIO_ReadPin(PAN2_CS2_GPIO_Port, PAN2_CS2_Pin))
        PanelStat |= (1 << PAN_Y_P);
    if (HAL_GPIO_ReadPin(PAN3_CS2_GPIO_Port, PAN3_CS2_Pin))
        PanelStat |= (1 << PAN_Z_P);
    if (HAL_GPIO_ReadPin(PAN4_CS2_GPIO_Port, PAN4_CS2_Pin))
        PanelStat |= (1 << PAN_X_M);
    if (HAL_GPIO_ReadPin(PAN5_CS2_GPIO_Port, PAN5_CS2_Pin))
        PanelStat |= (1 << PAN_Y_M);
    if (HAL_GPIO_ReadPin(PAN6_CS2_GPIO_Port, PAN6_CS2_Pin))
        PanelStat |= (1 << PAN_Z_M);

    // Configure all panel temperature sensors CS as push-pull outputs
    HAL_GPIO_WritePin(PAN5_CS2_GPIO_Port, PAN5_CS2_Pin, GPIO_PIN_SET);    //Chip selects is OFF
    HAL_GPIO_WritePin(GPIOI, PAN1_CS2_Pin | PAN3_CS2_Pin | PAN4_CS2_Pin,
              GPIO_PIN_SET);
    HAL_GPIO_WritePin(PAN6_CS2_GPIO_Port, PAN6_CS2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(PAN2_CS2_GPIO_Port, PAN2_CS2_Pin, GPIO_PIN_SET);

    GPIO_InitStruct.Pin = PAN5_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN5_CS2_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN1_CS2_Pin | PAN3_CS2_Pin | PAN4_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN6_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN6_CS2_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN2_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN2_CS2_GPIO_Port, &GPIO_InitStruct);
}

/*!
*********************************************************************************************
 * @brief Panels initialisation routine
*********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
*********************************************************************************************
 */
void Panels_ChipSelect2_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStruct.Pin = PAN5_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN5_CS2_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN1_CS2_Pin | PAN3_CS2_Pin | PAN4_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN6_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN6_CS2_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PAN2_CS2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PAN2_CS2_GPIO_Port, &GPIO_InitStruct);
}


/*!
*********************************************************************************************
 * @brief Selects SPI slave (e.g. CS/SS pin for the proper SPI slave)
*********************************************************************************************
 * @param[input]      uint8_t Mode - identification bitmask, consisting of the device selector, operational mode (ON/OFF) and panel identifier
 * @param[output]     none
 * @return            none
 * @note              !!! Partially optimized by Georgi Georgiev on 06-06-19 !!!
*********************************************************************************************
 */
void SPI_SlaveSelect(uint8_t Mode)
{
    GPIO_PinState GPIO_pstate;

    if (Mode & CS_OFF) {
        GPIO_pstate = GPIO_PIN_SET;
    } else {
        GPIO_pstate = GPIO_PIN_RESET;
    }

    switch (Mode & (MAX_PAN + 1)) {
    case 0:
        if (Mode & TEMP_CS) {
            HAL_GPIO_WritePin(PAN1_CS2_GPIO_Port, PAN1_CS2_Pin,
                      GPIO_pstate);
        } else {
            HAL_GPIO_WritePin(PAN1_CS1_GPIO_Port, PAN1_CS1_Pin,
                      GPIO_pstate);
        }
        break;
    case 1:
        if (Mode & TEMP_CS) {
            HAL_GPIO_WritePin(PAN2_CS2_GPIO_Port, PAN2_CS2_Pin,
                      GPIO_pstate);
        } else {
            HAL_GPIO_WritePin(PAN2_CS1_GPIO_Port, PAN2_CS1_Pin,
                      GPIO_pstate);
        }
        break;
    case 2:
        if (Mode & TEMP_CS) {
            HAL_GPIO_WritePin(PAN3_CS2_GPIO_Port, PAN3_CS2_Pin,
                      GPIO_pstate);
        } else {
            HAL_GPIO_WritePin(PAN3_CS1_GPIO_Port, PAN3_CS1_Pin,
                      GPIO_pstate);
        }
        break;
    case 3:
        if (Mode & TEMP_CS) {
            HAL_GPIO_WritePin(PAN4_CS2_GPIO_Port, PAN4_CS2_Pin,
                      GPIO_pstate);
        } else {
            HAL_GPIO_WritePin(PAN4_CS1_GPIO_Port, PAN4_CS1_Pin,
                      GPIO_pstate);
        }
        break;
    case 4:
        if (Mode & TEMP_CS) {
            HAL_GPIO_WritePin(PAN5_CS2_GPIO_Port, PAN5_CS2_Pin,
                      GPIO_pstate);
        } else {
            HAL_GPIO_WritePin(PAN5_CS1_GPIO_Port, PAN5_CS1_Pin,
                      GPIO_pstate);
        }
        break;
    case 5:
        if (Mode & TEMP_CS) {
            HAL_GPIO_WritePin(PAN6_CS2_GPIO_Port, PAN6_CS2_Pin,
                      GPIO_pstate);
        } else {
            HAL_GPIO_WritePin(PAN6_CS1_GPIO_Port, PAN6_CS1_Pin,
                      GPIO_pstate);
        }
        break;
    default:
        break;
    }
}

/*!
*********************************************************************************************
 * @brief Checks if a given panel is attached or not.
*********************************************************************************************
 * @param[input]      panelId - panel identifier;
 * @return            True - panel attached;
 *                    False - panel missing
 * @note              none
*********************************************************************************************
 */
bool Panels_IsAttached(const PanId_t panelId)
{
    return (panelId < MAX_PAN) ?
        (bool) (PanelStat & (1 << panelId)) : (false);
}

/*!
*********************************************************************************************
 * @brief Returns last magnetic torque power (in %) and direction (cartesian axis direction) to a specific panel
*********************************************************************************************
 * @param[input]      uint8_t Panel - panel identifier;
 * @param[output]     uint8_t perc - applied power in %; uint8_t dir - cartesian axis direction
 * @return            SEN_SUCCESS or SEN_ERROR
 * @note              none
*********************************************************************************************
 */
status_t GetMagnetorque(uint8_t Panel, PANLE_TRQ_str * data)
{

    if (Panel == PAN_X_M) {
        data->power = Panel_Magnetorqer_Power[PAN_X_P];
        data->dir = Panel_Magnetorqer_Direction[PAN_X_P];
    } else if (Panel == PAN_Y_M) {
        data->power = Panel_Magnetorqer_Power[PAN_Y_P];
        data->dir = Panel_Magnetorqer_Direction[PAN_Y_P];
    } else if (Panel == PAN_Z_M) {
        data->power = Panel_Magnetorqer_Power[PAN_Z_P];
        data->dir = Panel_Magnetorqer_Direction[PAN_Z_P];
    } else
        return SEN_ERROR;

    return SEN_SUCCESS;
}

/*!
*********************************************************************************************
 * @brief Applies or stops magnetic torque power (in %) and direction (cartesian axis direction) to a specific panel
*********************************************************************************************
 * @param[input]      uint8_t Panel - panel identifier; uint8_t perc - applied power in %; uint8_t dir - cartesian axis direction
 * @param[output]     none
 * @return            SEN_SUCCESS or SEN_ERROR
 * @note              none
*********************************************************************************************
 */
status_t SetMagnetorque(uint8_t Panel, uint8_t perc, uint8_t dir)
{
    uint8_t u8PwrSettingPercentage = (perc > 100U) ? (100U) : (perc);
    uint32_t tmp = (uint32_t) u8PwrSettingPercentage;

    TIM_OC_InitTypeDef sConfigOC;

    if ((Panel < PAN_X_M) || (Panel > PAN_Z_M))
        return SEN_ERROR;
    else
        Panel -= (uint8_t) PAN_X_M;    /* PAN_X_M is the base panel *///todo VVS: This depends on the enum value ...not good

    if (dir > 1)
        dir = 1;

    HAL_TIM_PWM_Stop(&htim5, sPWMCntrl[Panel].TIM_CHANNEL);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = (tmp * (MAGTORQ_PWM_PERIOD + 1) + 50) / 100;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC,
                  sPWMCntrl[Panel].TIM_CHANNEL);

    HAL_TIM_PWM_Start(&htim5, sPWMCntrl[Panel].TIM_CHANNEL);

    Panel_Magnetorqer_Power[Panel] = u8PwrSettingPercentage;
    Panel_Magnetorqer_Direction[Panel] = dir;

    if (dir) {
    	/* Current in the coil flows from PWM_A to PWM_B (check magnetorquer schematic) */
        HAL_GPIO_WritePin(sPWMCntrl[Panel].INA.port,
                  sPWMCntrl[Panel].INA.pin, GPIO_PIN_SET);
    } else {
    	/* Current in the coil flows from PWM_B to PWM_A (check magnetorquer schematic) */
        HAL_GPIO_WritePin(sPWMCntrl[Panel].INA.port,
                  sPWMCntrl[Panel].INA.pin, GPIO_PIN_RESET);
    }

    return SEN_SUCCESS;
}

/*!
*********************************************************************************************
 * @brief Calculates all panels magnetorquer value, related to the dipole moment parameter (represented hereby Magnetorquer_Axis_t vector); checks direction and updates power.
*********************************************************************************************
 * @param[input]      Magnetorquer_Axis_t MT_level - dipole moment vector -> double {X, Y, Z}
 * @param[output]     none
 * @return            none
 * @note              Connection matrix - Relates mangetometer axis with mangetorquer axis
 *                          magnetometer Y-  <-> magnetorquer X+
 *                          magnetometer X-  <-> magnetorquer Y-
 *                          magnetometer Z-  <-> magnetorquer Z-
*********************************************************************************************
 */
void Magnetorquers_Update(Magnetorquer_Axis_t MT_level)
{
    static uint8_t LevX = 0, LevY = 0, LevZ = 0;    /* PWM value in percentage */
    static uint8_t DirX = 1, DirY = 1, DirZ = 1;    /* PWM direction           */

    /* Set direction */
    if (MT_level.AXIS_X >= 0)
        DirX = 1;
    else
        DirX = 0;
    if (MT_level.AXIS_Y >= 0)
        DirY = 1;
    else
        DirY = 0;
    if (MT_level.AXIS_Z >= 0)
        DirZ = 1;
    else
        DirZ = 0;

    LevX = (uint8_t) (fabs(MT_level.AXIS_X * MTQ_DIP_MOM_TO_PWM_CONV_MULT));
    if (LevX > 100)
        LevX = 100;
    LevY = (uint8_t) (fabs(MT_level.AXIS_Y * MTQ_DIP_MOM_TO_PWM_CONV_MULT));
    if (LevY > 100)
        LevY = 100;
    LevZ = (uint8_t) (fabs(MT_level.AXIS_Z * MTQ_DIP_MOM_TO_PWM_CONV_MULT));
    if (LevZ > 100)
        LevZ = 100;

    SetMagnetorque(PAN_X_M, LevZ, DirZ);    /* PAN4 */
    SetMagnetorque(PAN_Y_M, LevX, DirX);    /* PAN5 */
    SetMagnetorque(PAN_Z_M, LevY, DirY);    /* PAN6 */

}

/*!
*********************************************************************************************
 * @brief Forces all magnetorquers on all panels to maximum power and given input direction
*********************************************************************************************
 * @param[input]      uint8_t Arrow - cartesian axis direction
 * @param[output]     none
 * @return            none
 * @note              none
*********************************************************************************************
 */
void Boost_Magnetorquers(uint8_t Arrow)
{
    SetMagnetorque(PAN_X_M, 100, Arrow);
    SetMagnetorque(PAN_Y_M, 100, Arrow);
    SetMagnetorque(PAN_Z_M, 100, Arrow);
}

/*!
*********************************************************************************************
 * @brief Turns off (0% power) all magnetorquers on all panels
*********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
*********************************************************************************************
 */
void Stop_Magnetorquers(void)
{
    SetMagnetorque(PAN_X_M, 0, 1);
    SetMagnetorque(PAN_Y_M, 0, 1);
    SetMagnetorque(PAN_Z_M, 0, 1);
}

/*!
*********************************************************************************************
 * @brief Makes ADC measurement on the specific channel, attached to each photo sensor
*********************************************************************************************
 * @param[input]      uint8_t Panel - panel identifier
 * @param[output]     uint16_t *val - the ADC output value
 * @return            SEN_SUCCESS or SEN_ERROR
 * @note              none
*********************************************************************************************
 */
status_t Pan_PD_ADC_Measure(uint8_t Panel, uint16_t * val)
{
    ADC_ChannelConfTypeDef sConfig;

    //Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.

    //??? Changed because of H7xx
    sConfig.Channel = AdcChannel[Panel];
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_64CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    sConfig.OffsetSignedSaturation = DISABLE;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
      return SEN_ERROR;

    if (HAL_ADC_Start(&hadc1) != HAL_OK)
        return SEN_ERROR;
    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
        return SEN_ERROR;
    *val = (uint16_t) HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return SEN_SUCCESS;
}

/*!
*********************************************************************************************
 * @brief Gets the ADC measurement of all the photo sensors, attached to the panels, and updates the global photometric data sensor array (that is - PanelLight) accordingly
*********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
*********************************************************************************************
 */
void Panel_GetPhotodiodesLum(void)
{
    for (uint8_t i = 0; i < MAX_PAN; i++) {
        if (Pan_PD_ADC_Measure(i, (uint16_t *) & PanelLight[i]) !=
            SEN_SUCCESS)
            PanelLight[i] = 0xFFFF;
    }
}

/*!
*********************************************************************************************
 * @brief Calculates the current positive temperature 3D gradient value of the TMP122 temperature sensor (SPI slave)
*********************************************************************************************
 * @param[input]      none
 * @param[output]     Temperature_t* tmp - positive temperature 3D gradient value output - int16_t {Temp_X, Temp_Y, Temp_Z}
 * @return            SEN_SUCCESS or SEN_ERROR
 * @note              none
*********************************************************************************************
 */
status_t TMP122_GetTemperatureP(Temperature_t * tmp)
{
    uint16_t txdata = 0;
    HAL_StatusTypeDef res = HAL_OK;

    if (tmp == NULL)
        return SEN_ERROR;

    tmp->Temp_X = tmp->Temp_Y = tmp->Temp_Z = (int16_t) 0xFFFF;

    SPI_SlaveSelect(TEMP_CS | CS_ON | PAN_X_P);
    res =
        HAL_SPI_TransmitReceive(&PANEL_SPI_HANDLER, (uint8_t *) & txdata,
                    (uint8_t *) (&tmp->Temp_X), 1, 10);
    SPI_SlaveSelect(TEMP_CS | CS_OFF | PAN_X_P);
    if (res != HAL_OK)
        return SEN_ERROR;

    SPI_SlaveSelect(TEMP_CS | CS_ON | PAN_Y_P);
    res =
        HAL_SPI_TransmitReceive(&PANEL_SPI_HANDLER, (uint8_t *) & txdata,
                    (uint8_t *) (&tmp->Temp_Y), 1, 10);
    SPI_SlaveSelect(TEMP_CS | CS_OFF | PAN_Y_P);
    if (res != HAL_OK)
        return SEN_ERROR;

    SPI_SlaveSelect(TEMP_CS | CS_ON | PAN_Z_P);
    res =
        HAL_SPI_TransmitReceive(&PANEL_SPI_HANDLER, (uint8_t *) & txdata,
                    (uint8_t *) (&tmp->Temp_Z), 1, 10);
    SPI_SlaveSelect(TEMP_CS | CS_OFF | PAN_Z_P);
    if (res != HAL_OK)
        return SEN_ERROR;

    return SEN_SUCCESS;
}

/*!
*********************************************************************************************
 * @brief Converts the raw temperature result provided by TMP122_GetTemperatureX() operation
 *        to degrees Celsius
*********************************************************************************************
 * @param[input]      rawTempValue
 * @param[output]     n/a
 * @return            convTempValue - rawTempValue converted to degrees Celsius
 * @note              none
*********************************************************************************************
 */
inline int16_t TMP122_getTemperatureInDegC(int16_t rawTempValue)
{
    return (int16_t) ((rawTempValue >> 3) * 10) >> 4;
}

/*!
*********************************************************************************************
 * @brief Calculates the current negative temperature 3D gradient value of the TMP122 temperature sensor (SPI slave)
*********************************************************************************************
 * @param[input]      none
 * @param[output]     Temperature_t* tmp - negative temperature 3D gradient value output - int16_t {Temp_X, Temp_Y, Temp_Z}
 * @return            SEN_SUCCESS or SEN_ERROR
 * @note              none
*********************************************************************************************
 */
status_t TMP122_GetTemperatureM(Temperature_t * tmp)
{
    uint16_t txdata = 0;
    HAL_StatusTypeDef res = HAL_OK;

    if (tmp == NULL)
        return SEN_ERROR;

    tmp->Temp_X = tmp->Temp_Y = tmp->Temp_Z = (int16_t) 0xFFFF;

    SPI_SlaveSelect(TEMP_CS | CS_ON | PAN_X_M);
    res = HAL_SPI_TransmitReceive(&PANEL_SPI_HANDLER, (uint8_t *) & txdata,
                      (uint8_t *) (&tmp->Temp_X), 1, 10);
    SPI_SlaveSelect(TEMP_CS | CS_OFF | PAN_X_M);
    if (res != HAL_OK)
        return SEN_ERROR;

    SPI_SlaveSelect(TEMP_CS | CS_ON | PAN_Y_M);
    res = HAL_SPI_TransmitReceive(&PANEL_SPI_HANDLER, (uint8_t *) & txdata,
                      (uint8_t *) (&tmp->Temp_Y), 1, 10);
    SPI_SlaveSelect(TEMP_CS | CS_OFF | PAN_Y_M);
    if (res != HAL_OK)
        return SEN_ERROR;

    SPI_SlaveSelect(TEMP_CS | CS_ON | PAN_Z_M);
    res = HAL_SPI_TransmitReceive(&PANEL_SPI_HANDLER, (uint8_t *) & txdata,
                      (uint8_t *) (&tmp->Temp_Z), 1, 10);
    SPI_SlaveSelect(TEMP_CS | CS_OFF | PAN_Z_M);
    if (res != HAL_OK)
        return SEN_ERROR;

    return SEN_SUCCESS;
}

/*!
*********************************************************************************************
 * @brief Read a temperature sensor
*********************************************************************************************
 * @param[input]      panelNumber - number of panel
 * @param[output]     int16_t * tmp - temperature from a panel
 * @return            SEN_SUCCESS or SEN_ERROR
 * @note              none
*********************************************************************************************
 */
status_t TMP122_GetTemperatureFromPanel(PanId_t panelNumber, int16_t * tmp)
{
    uint16_t txdata = 0;
    HAL_StatusTypeDef res = HAL_OK;

    if ((tmp == NULL) || (panelNumber >= MAX_PAN))
        return SEN_ERROR;

    *tmp = (int16_t) 0xFFFF;

    SPI_SlaveSelect(TEMP_CS | CS_ON | panelNumber);
    res =
        HAL_SPI_TransmitReceive(&PANEL_SPI_HANDLER, (uint8_t *) & txdata,
                    (uint8_t *) (tmp), 1, 10);
    SPI_SlaveSelect(TEMP_CS | CS_OFF | panelNumber);

    if (res != HAL_OK)
        return SEN_ERROR;

    return SEN_SUCCESS;
}
