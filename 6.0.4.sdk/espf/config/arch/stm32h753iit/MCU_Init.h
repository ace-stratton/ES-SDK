/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*!
********************************************************************************************
* @file MCU_Init.h
* @brief Header of MCU_Init.c
********************************************************************************************
* @author            Vassil Milev
* @version           1.0.0
* @date              2019.01.10
*
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
* @history
* @revision{         1.0.0  , 2019.01.10, author Vassil Milev, Initial revision }
* @endhistory
********************************************************************************************
*/
#ifndef MCU_INIT_H
#define MCU_INIT_H

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include <stdbool.h>
#include "stm32h7xx_hal.h"
#include <GlobalConfig.h>
#include "es_cdef.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/
//UART1 is defined in the espsi_drv @see esps_drv_config.c
//UART1 Init definitions -> PAY1 ES MAC RS485
// This definitions are used in MX_AllPeripheryAndGpio_DeInit.
#define RS422_HS1_DE_UART1_SYS1_Pin             GPIO_PIN_10
#define RS422_HS1_DE_UART1_SYS1_GPIO_Port       GPIOE
#define RS422_HS1_nRE_UART1_SYS1_Pin            GPIO_PIN_5
#define RS422_HS1_nRE_UART1_SYS1_GPIO_Port      GPIOF

//UART2 is unused

//UART3 Init definitions -> SYS1 ES MAC RS485 or  S/X-Band
#define U3_RS485_S1_nRE_Pin         GPIO_PIN_6
#define U3_RS485_S1_nRE_GPIO_Port   GPIOE
#define U3_RS485_S1_DE_Pin          GPIO_PIN_10
#define U3_RS485_S1_DE_GPIO_Port    GPIOD
#define U3_RS485_S1_TE_Pin          GPIO_PIN_8
#define U3_RS485_S1_TE_GPIO_Port    GPIOI

#define U3_RS485_S1_RX_Pin          GPIO_PIN_9
#define U3_RS485_S1_RX_GPIO_Port    GPIOD
#define U3_RS485_S1_TX_Pin          GPIO_PIN_10
#define U3_RS485_S1_TX_GPIO_Port    GPIOB

//UART4 Init definitions -> PAY2 ES MAC RS485 / ESTTC uart / CubeADCS
#define U4_RS485_S2_DE_Pin          GPIO_PIN_13
#define U4_RS485_S2_DE_GPIO_Port    GPIOF
#define U4_RS485_S2_nRE_Pin         GPIO_PIN_14
#define U4_RS485_S2_nRE_GPIO_Port   GPIOF
#define U4_RS485_S2_RX_Pin          GPIO_PIN_9
#define U4_RS485_S2_RX_GPIO_Port    GPIOI
#define U4_RS485_S2_TX_Pin          GPIO_PIN_13
#define U4_RS485_S2_TX_GPIO_Port    GPIOH
#define U4_RS485_S2_TE_Pin          GPIO_PIN_3
#define U4_RS485_S2_TE_GPIO_Port    GPIOE
//End of UART4 Init definitions

//UART5 Init definitions -> SYS UART / USB
#define U5_PROTO_USB_SYSTEM_RX_Pin GPIO_PIN_5
#define U5_PROTO_USB_SYSTEM_RX_GPIO_Port GPIOB
#define U5_PROTO_USB_SYSTEM_TX_Pin GPIO_PIN_6
#define U5_PROTO_USB_SYSTEM_TX_GPIO_Port GPIOB

//UART6 Init definitions -> PAY1 ES MAC RS485
#define RS422_HS2_DE_UART6_PAY1_Pin         GPIO_PIN_10
#define RS422_HS2_DE_UART6_PAY1_GPIO_Port   GPIOF
#define RS422_HS2_nRE_UART6_PAY1_Pin        GPIO_PIN_12
#define RS422_HS2_nRE_UART6_PAY1_GPIO_Port  GPIOF
//End of UART6 Init definitions

//UART7 Init definitions -> Payload ESTTC uart / EPS M / SPI5
#define U7_PAY_RX_SPI5_NSS_Pin          GPIO_PIN_6
#define U7_PAY_RX_SPI5_NSS_GPIO_Port    GPIOF
#define U7_PAY_TX_SPI5_SCK_Pin          GPIO_PIN_7
#define U7_PAY_TX_SPI5_SCK_GPIO_Port    GPIOF
#define U7_PAY_RTS_SPI5_MISO_Pin        GPIO_PIN_8
#define U7_PAY_RTS_SPI5_MISO_GPIO_Port  GPIOF
#define U7_PAY_CTS_SPI5_MOSI_Pin        GPIO_PIN_9
#define U7_PAY_CTS_SPI5_MOSI_GPIO_Port  GPIOF
//End of UART7 Init definitions

//UART8 Init definitions -> COMM UART / Ext EPS
#define U8_COMM_TX_Pin GPIO_PIN_1
#define U8_COMM_TX_GPIO_Port GPIOE
#define U8_COMM_RX_Pin GPIO_PIN_0
#define U8_COMM_RX_GPIO_Port GPIOE

#define U8_COMM_CTS_Pin GPIO_PIN_14
#define U8_COMM_CTS_GPIO_Port GPIOD
#define U8_COMM_RTS_Pin GPIO_PIN_15
#define U8_COMM_RTS_GPIO_Port GPIOD
//End of UART8 Init definitions

//I2C1 Init definitions -> SYS I2C
#define I2C1_SYS_SDA_Pin GPIO_PIN_7
#define I2C1_SYS_SDA_GPIO_Port GPIOB
#define I2C1_SYS_SCL_Pin GPIO_PIN_8
#define I2C1_SYS_SCL_GPIO_Port GPIOB
//End of I2C1 Init definitions

//I2C2 Init definitions -> Sesors I2C
#define I2C2_SEN_SCL_Pin GPIO_PIN_1
#define I2C2_SEN_SCL_GPIO_Port GPIOF
#define I2C2_SEN_SDA_Pin GPIO_PIN_0
#define I2C2_SEN_SDA_GPIO_Port GPIOF
//End of I2C2 Init definitions

//I2C3 Init definitions -> PAY I2C
#define I2C3_PAY_SCL_Pin GPIO_PIN_7
#define I2C3_PAY_SCL_GPIO_Port GPIOH
#define I2C3_PAY_SDA_Pin GPIO_PIN_8
#define I2C3_PAY_SDA_GPIO_Port GPIOH
//End of I2C3 Init definitions

//SPI5 Init definitions
#define SPI5_SCK_Pin U7_PAY_TX_SPI5_SCK_Pin
#define SPI5_SCK_GPIO_Port U7_PAY_TX_SPI5_SCK_GPIO_Port
#define SPI5_MISO_Pin U7_PAY_RTS_SPI5_MISO_Pin
#define SPI5_MISO_GPIO_Port U7_PAY_RTS_SPI5_MISO_GPIO_Port
#define SPI5_MOSI_Pin U7_PAY_CTS_SPI5_MOSI_Pin
#define SPI5_MOSI_GPIO_Port U7_PAY_CTS_SPI5_MOSI_GPIO_Port
#define SPI5_IRQ_Pin RS422_HS2_DE_UART6_PAY1_Pin
#define SPI5_IRQ_GPIO_Port RS422_HS2_DE_UART6_PAY1_GPIO_Port

#define ARDU_CAM_CS_Pin U7_PAY_RX_SPI5_NSS_Pin
#define ARDU_CAM_CS_GPIO_Port U7_PAY_RX_SPI5_NSS_GPIO_Port
//End of SPI5 Init definitions

//Accelerometers Init definitions
#define ACC_EN_Pin GPIO_PIN_15
#define ACC_EN_GPIO_Port GPIOE
#define SENSORS_I2C_USE_ACCEL   (uint8_t)(1<<0)
#define SENSORS_I2C_USE_COMPAS  (uint8_t)(1<<1)
//End of Accelerometers Init definitions

//Magnetorqers Init definitions
#define PAN_PS_Pin GPIO_PIN_7
#define PAN_PS_GPIO_Port GPIOE

#define PAN4_DIR1_Pin GPIO_PIN_11
#define PAN4_DIR1_GPIO_Port GPIOD
#define PAN5_DIR1_Pin GPIO_PIN_3
#define PAN5_DIR1_GPIO_Port GPIOF
#define PAN6_DIR1_Pin GPIO_PIN_4
#define PAN6_DIR1_GPIO_Port GPIOH

#define PAN4_PWM_Pin GPIO_PIN_10
#define PAN4_PWM_GPIO_Port GPIOH
#define PAN5_PWM_Pin GPIO_PIN_11
#define PAN5_PWM_GPIO_Port GPIOH
#define PAN6_PWM_Pin GPIO_PIN_12
#define PAN6_PWM_GPIO_Port GPIOH

#define PAN4_PWM_Pin GPIO_PIN_10
#define PAN4_PWM_GPIO_Port GPIOH
#define PAN5_PWM_Pin GPIO_PIN_11
#define PAN5_PWM_GPIO_Port GPIOH
#define PAN6_PWM_Pin GPIO_PIN_12
#define PAN6_PWM_GPIO_Port GPIOH

//End of Magnetorqers Init definitions

//Gyroscopes Init definitions
#define PANLES_SPI      SPI2

#define PAN1_CS1_Pin GPIO_PIN_3
#define PAN1_CS1_GPIO_Port GPIOG
#define PAN2_CS1_Pin GPIO_PIN_5
#define PAN2_CS1_GPIO_Port GPIOG
#define PAN3_CS1_Pin GPIO_PIN_5
#define PAN3_CS1_GPIO_Port GPIOI
#define PAN4_CS1_Pin GPIO_PIN_7
#define PAN4_CS1_GPIO_Port GPIOI
#define PAN5_CS1_Pin GPIO_PIN_5
#define PAN5_CS1_GPIO_Port GPIOE
#define PAN6_CS1_Pin GPIO_PIN_11
#define PAN6_CS1_GPIO_Port GPIOI

#define PAN1_4_VGY_Pin GPIO_PIN_14
#define PAN1_4_VGY_GPIO_Port GPIOB
#define PAN2_5_VGY_Pin GPIO_PIN_14
#define PAN2_5_VGY_GPIO_Port GPIOG
#define PAN3_6_VGY_Pin GPIO_PIN_9
#define PAN3_6_VGY_GPIO_Port GPIOB

//SPI2 pins
#define PAN_SCK_Pin GPIO_PIN_1
#define PAN_SCK_GPIO_Port GPIOI
#define PAN_MISO_Pin GPIO_PIN_2
#define PAN_MISO_GPIO_Port GPIOI
#define PAN_MOSI_Pin GPIO_PIN_3
#define PAN_MOSI_GPIO_Port GPIOI

#define PANEL_SPI_USE_GPS   (uint8_t)(1<<0)
#define PANEL_SPI_USE_TEMPR  (uint8_t)(1<<1)
//End of Gyroscopes Init definitions

//Temperature sensors Init definitions
#define PAN_Temp_PS_Pin GPIO_PIN_8
#define PAN_Temp_PS_GPIO_Port GPIOE

#define PAN1_CS2_Pin GPIO_PIN_0
#define PAN1_CS2_GPIO_Port GPIOI
#define PAN2_CS2_Pin GPIO_PIN_4
#define PAN2_CS2_GPIO_Port GPIOG
#define PAN3_CS2_Pin GPIO_PIN_4
#define PAN3_CS2_GPIO_Port GPIOI
#define PAN4_CS2_Pin GPIO_PIN_6
#define PAN4_CS2_GPIO_Port GPIOI
#define PAN5_CS2_Pin GPIO_PIN_4
#define PAN5_CS2_GPIO_Port GPIOE
#define PAN6_CS2_Pin GPIO_PIN_2
#define PAN6_CS2_GPIO_Port GPIOF
//End of Temperature sensors Init definitions

//Sun sensors Init definitions
#define PAN1_IN_Pin GPIO_PIN_0
#define PAN1_IN_GPIO_Port GPIOC
#define PAN2_IN_Pin GPIO_PIN_3
#define PAN2_IN_GPIO_Port GPIOA
#define PAN3_IN_Pin GPIO_PIN_4
#define PAN3_IN_GPIO_Port GPIOA
#define PAN4_IN_Pin GPIO_PIN_5
#define PAN4_IN_GPIO_Port GPIOA
#define PAN5_IN_Pin GPIO_PIN_6
#define PAN5_IN_GPIO_Port GPIOA
#define PAN6_IN_Pin GPIO_PIN_0
#define PAN6_IN_GPIO_Port GPIOB
//End of Sun sensors Init definitions

#define OpAmp_PS_Pin GPIO_PIN_9
#define OpAmp_PS_GPIO_Port GPIOE

//SD card Init definitions
#define SD_REINIT_MAX_RETRIES 6

#define SD_EN_Pin GPIO_PIN_3
#define SD_EN_GPIO_Port GPIOD
#define SD2_EN_Pin GPIO_PIN_8
#define SD2_EN_GPIO_Port GPIOD
#define SD_DET_Pin GPIO_PIN_15
#define SD_DET_GPIO_Port GPIOG
#define SD2_DET_Pin GPIO_PIN_13
#define SD2_DET_GPIO_Port GPIOC
//End of SD card Init definitions

#define ETH_RSTn_Pin GPIO_PIN_2
#define ETH_RSTn_GPIO_Port GPIOH
#define ETH_EN_Pin GPIO_PIN_3
#define ETH_EN_GPIO_Port GPIOH

#define SYS_I2C_4K7_Pin GPIO_PIN_15
#define SYS_I2C_4K7_GPIO_Port GPIOF
#define SYS_I2C_10K_Pin GPIO_PIN_0
#define SYS_I2C_10K_GPIO_Port GPIOG
#define PAY_I2C_4K7_Pin GPIO_PIN_1
#define PAY_I2C_4K7_GPIO_Port GPIOG
#define PAY_I2C_10K_Pin GPIO_PIN_2
#define PAY_I2C_10K_GPIO_Port GPIOG

#define CAN_RS_Pin GPIO_PIN_8
#define CAN_RS_GPIO_Port GPIOA

#define SYS_WAKE1_Pin GPIO_PIN_0
#define SYS_WAKE1_GPIO_Port GPIOA

#define MCU_WWDG_MAX_RESET_TIME     (82)                            /*  112 = 21ms min time ;  127 = 83ms max time */
#define MCU_WWDG_MAX_CYCLING_TIME   (MCU_WWDG_MAX_RESET_TIME/2)     // Maximum time to wait in a while() loop

//////////////////////////////////////////////////////////////////////////////////////////
////  New define /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define SYSTEM_I2C_HANDLER      (hi2c1)
#define SYSTEM_I2C              (I2C1)

#define SENSORS_I2C_HANDLER      (hi2c2)
#define SENSORS_I2C              (I2C2)

#define PAYLOAD_I2C_HANDLER      (hi2c3)
#define PAYLOAD_I2C              (I2C3)

#define PANEL_SPI_HANDLER       (hspi2)
#define PANEL_SPI               (SPI2)

typedef struct {
    uint8_t        OutToChange;    //Allowed outputs to be changed: bit-field
    uint8_t        OutState;       //States into which to be changed: bit-field
}MCU_Init_OutStates_struct;

typedef enum {
    MCU_INIT_OUT1,    // S/X-band
    MCU_INIT_OUT2,    // S/X-band
    MCU_INIT_OUT3,    // VHF
    MCU_INIT_OUT5,    // UHF
    MCU_INIT_OUT4_6,  // OBC
    MCU_INIT_OUT7,    //
    MCU_INIT_OUT8     //
}MCU_Init_OutputsOrder_enum;

typedef union
{
    uint8_t i2c_pull_up_states;

    struct
    {
        uint8_t sys_bus_4K7:1;
        uint8_t sys_bus_10K:1;
        uint8_t pay_bus_4K7:1;
        uint8_t pay_bus_10K:1;
    } pins;
} I2CPullUpsState_t;

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/
/* No External types declarations */

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/
extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;

extern SD_HandleTypeDef  hsd1;

extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi5;
extern TIM_HandleTypeDef htim5;

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/
void SystemClock_IdleConfig(void);

void MX_AllPeripheryAndGpio_DeInit(void);

void MX_ADC1_Init(void);

// Arduino Camera
void MX_SPI5_Init(void);
void MX_SPI5_DeInit(void);

// Panels
void MX_PANEL_SPI_Init(SPI_HandleTypeDef *hspi);
void MX_SPI6_Init(void);
void MX_TIM5_Init(void);

// Telemetry
void MCU_AccelerometersInit(void);
void MCU_AccelerometersDeInit(void);
void MCU_MagnetometersInit(void);
void MCU_MagnetometersDeInit(void);
void MCU_MagnetorqersInit(void);
void MCU_MagnetorqersDeInit(void);
void MCU_GyrosInit(void);
void MCU_GyrosDeInit(void);
void MCU_TemprInit(void);
void MCU_TemprDeInit(void);
void MCU_SunSensInit(void);
void MCU_SunSensDeInit(void);

uint8_t MCU_InitSdCard(uint8_t cards, uint8_t cardHwReset);

void MCU_Init_I2cPullUps_Nvm(void);
void MCU_Init_I2cPullUps_Set(const I2CPullUpsState_t i2c_io_setting);
I2CPullUpsState_t MCU_Init_I2cPullUps_Get(void);

void PVD_BrownoutReset_Init();

#endif    /* MCU_INIT_H */
/* **************************************************************************************** */
