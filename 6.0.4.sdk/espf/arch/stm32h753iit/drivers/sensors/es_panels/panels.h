#ifndef PANELS_H
#define PANELS_H

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup es_panels Solar Panels
 * @{
 *
 * Driver for the Endurosat solar panels
 *
 * @file     panels.h
 * @brief    Public interface for the solar panels driver
 *
 * @}
 * @}
 *
 */

#include "MCU_Init.h"
#include "User_types.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/
#define MTQ_DIP_MOM_TO_PWM_CONV_MULT ((float)833.34) /* Magnetorquer ADCS requested dipole moment conv to PWM percentage multiplier */

typedef enum tag_ePinState_t
{
    ePINSTATE_OFF         = 0,
    ePINSTATE_ON          = 1,
    ePINSTATE_INV_STATE   = 2,
} ePinStates_t;

typedef struct tag_BD_GPIO_Cntrl{
    GPIO_TypeDef * port;
    uint16_t       pin;
    ePinStates_t   state;
} tag_BD_GPIO_Cntrl;

typedef struct tag_PWM_Cntrl {
    uint32_t          TIM_CHANNEL;
    tag_BD_GPIO_Cntrl INA;
} PWM_Cntrl_t;

typedef enum
{
    PAN_X_P,    // Panel X Plus
    PAN_Y_P,    // Panel Y Plus
    PAN_Z_P,    // Panel Z Plus
    PAN_X_M,    // Panel X Minus
    PAN_Y_M,    // Panel Y Minus
    PAN_Z_M,    // Panel Z Minus
    MAX_PAN
} PanId_t;

/* To be used in gyroscope panel-sensor configurations, most likely in the future other sensors will move to this enumeration */
typedef enum
{
    PANEL_1 = 1, // Panel connected to output connector designated PAN_1
    PANEL_2,     // Panel connected to output connector designated PAN_2
    PANEL_3,     // Panel connected to output connector designated PAN_3
    PANEL_4,     // Panel connected to output connector designated PAN_4
    PANEL_5,     // Panel connected to output connector designated PAN_5
    PANEL_6,     // Panel connected to output connector designated PAN_6
    MAX_PANEL
} Panel_Number_t;

#define TRQ_1           1       /* Magnetorquer 1 */
#define TRQ_2           2       /* Magnetorquer 2 */
#define TRQ_3           3       /* Magnetorquer 3 */

#define TEMP_CS 0x80

#define CS_ON   0x00
#define CS_OFF  0x60
   
#define MAGTORQ_PWM_PERIOD 899

#define TMP122_CONVERSION_TIME  (265)   // Minimum measured time for temperature conversion is 235 ms, according to datasheet is 250ms

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/
/* Values of all commands */
typedef enum{
    PANLE_GYROS_AXIS_X,
    PANLE_GYROS_AXIS_Y,
    PANLE_GYROS_AXIS_Z,
    PANLE_GYROS_AXIS_ALL,
    PANLE_GYROS_AXIS_NUMBER
}PANLE_GYROS_AXIS;

typedef struct{
    uint8_t power;
    uint8_t dir;
}PANLE_TRQ_str;

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/
extern uint16_t PanelLight[MAX_PAN];
extern uint16_t PanelTemp[MAX_PAN];

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS 
*********************************************************************************************
*/
void Panels_ChipSelect2_Init(void);
void Panels_ChipSelect2_DeInit(void);
void SPI_SlaveSelect(uint8_t Mode);
status_t Pan_PD_ADC_Measure(uint8_t Panel, uint16_t *val);
void Panel_GetPhotodiodesLum(void);
status_t GetMagnetorque(uint8_t Panel, PANLE_TRQ_str* data);
status_t SetMagnetorque(uint8_t Panel, uint8_t perc, uint8_t dir);
void Magnetorquers_Update (Magnetorquer_Axis_t MT_level);
void Boost_Magnetorquers (uint8_t Arrow);
void Stop_Magnetorquers (void);
bool Panels_IsAttached(const PanId_t panelId);
status_t TMP122_ReadReg16(uint16_t *data, uint8_t Panel);
status_t TMP122_GetTemperatureP(Temperature_t* tmp);
int16_t TMP122_getTemperatureInDegC(int16_t rawTempValue);
status_t TMP122_GetTemperatureM(Temperature_t* tmp);
status_t TMP122_GetTemperatureFromPanel(PanId_t panelNumber, int16_t * tmp);

#endif    /* PANELS_H */
