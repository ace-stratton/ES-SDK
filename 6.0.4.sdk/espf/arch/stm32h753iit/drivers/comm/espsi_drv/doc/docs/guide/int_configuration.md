--8<-- "includes/abbreviations.md"

# Configuration

## HAL Drivers
The MAC layer uses two timers, the UART, the RNG and a GPIO for the control of the signals needed for the RS-485. The hardware peripherals are defined in the file `esps_drv_stm32g.ioc` but the code is not generated from the IDE. In case you change the hardware, you might want to generate the code for the initialization to verify that everythin is done the same way as in the example project.

Generation of the code from the CubeIDE:

| Peripheral | HAL driver         | LL driver          | Generated Code |
|------------|--------------------|--------------------|----------------|
| USART 1    | :white_check_mark: | :white_check_mark: | :x:            |
| TIM 16     | :x:                | :white_check_mark: | :x:            |
| TIM 17     | :x:                | :white_check_mark: | :x:            |
| GPIOs      | :white_check_mark: | :x:                | :x:            |
| RNG        | :white_check_mark: | :x:                | :x:            |

!!! Note
    The CubeIDE will not let you select LL and HAL for the same peripheral, you will need to select one of them and get the header for the other one from their [repository](https://github.com/STMicroelectronics/stm32g4xx_hal_driver) (make sure you get a compatible version).

    Alternatively, if there is another UART in use, you can select this additional UART to use the HAL Drivers and the first one to use the LL drivers. This way, you will have both headers available from the CubeIDE generation.

Please note that the pins used have the labels defined in the configuration file (.ioc), and the definitions are generated in `Core/Inc/main.h`:

```c
// USART1 pins:
//      PB0  --> CTS (Clear To Send)   -- RS485_nRE (Receiver Enable)
//      PA9  --> TX                    -- RS485_TX
//      PA10 --> RX                    -- RS485_RX
//      PA12 --> RTS (Request To Send) -- RS485_DE (Driver Enable)
//      PB7  --> TE                    -- RS485_TE (Termination Enable)

#define RS485_nRE_Pin       GPIO_PIN_0
#define RS485_nRE_GPIO_Port GPIOB
#define RS485_TX_Pin        GPIO_PIN_9
#define RS485_TX_GPIO_Port  GPIOA
#define RS485_RX_Pin        GPIO_PIN_10
#define RS485_RX_GPIO_Port  GPIOA
#define RS485_DE_Pin        GPIO_PIN_12
#define RS485_DE_GPIO_Port  GPIOA
#define RS485_TE_Pin        GPIO_PIN_7
#define RS485_TE_GPIO_Port  GPIOB
```

All the configuration is accessible to the drivers by using the struct `sMACInterfaceImmutableConfig_t fs_MacConfig[]`, in `Core/config/src/esps_drv_conf.c`, by populating the fields with the necessary callbacks. Each MAC interface, has a configuration structure defined to keep the timers, the UART callbacks, the parameters of the serial communication, etc.

### UART and GPIO

The UART and GPIO initialization is defined in the file `Core/config/src/esps_drv_conf.c`. The following functions:

```c
static void fs_Uart1Init (struct sMACConfig_t *cfg);
static void fs_Uart1Deinit (struct sMACConfig_t *cfg);
static void fs_vDriverEnable (void);
static void fs_vDriverDisable (void);
static void fs_vRS485ReceptionEnable (void);
static void fs_vRS485ReceptionDisable (void);
```

!!! Tip
    If you are not sure how to initialize any of the peripherals you can generate the code with the CubeIDE by modifying the settings in the .ioc file and take it as an example of what you should write in the functions mentioned above.

UART is using two GPIO, Tx and Rx, and there are three additional GPIO to control the RS-485 transceiver.

- Driver Enable signal (`RS485_DE_Pin`): Controlled by the software, whether to enable or disable the transmition of messages.
- Receiver Enable (`RS485_nRE_Pin`): It must be enable to receive from the bus. It will be disable during transmissions.
- Termination Enable (`RS485_TE_Pin`): Depending on the chip of the transceiver, you might be able to set a termination resistor. Both end devices in the bus should have one.

The `RS485_TE_Pin` has an option to be set or to read the state using the following two functions defined in `Core/config/src/esps_drv_config.c`:

```c
// Get and Set Termination Enable bit for the UART interface.
bool MacCfg_bGetBusTerminationState (const eMACInterface_t eMacIf);
void MacCfg_vSetBusTerminationState (const eMACInterface_t eMacIf, const bool bNewState);
```

Just for information, the function protocol MacServices is using these two functions.

!!! Tip
    The DE signal can be set as part of the UART configuration (if you are using the .ioc file to generate the code).

### Timers

There is a timer for the transmission and another for the reception. The timers are necessary for setting the priority delay before sending a message or to set timeouts to avoid blocking the communication. The configuration of the timers is done in `Core/config/src/esps_drv_tim_config.c`.

`TIM_CFG_asTimerEntries` is defined with the necessary information for the initalization for each timer. For this project, both timers are in the 'APB2' clock domain but the functions in the drivers, and in the configuration, are defined for a generic domain in case other timers were necessary to be used. Thanks to the definitions from `esps_drv_rcc.h`.

Both timers must tick with a frequency of 1 micro second. In order to achieve that, the function `MacCfg_TIM_u16CalculatePrescaler` must be defined accordingly. In our example, we have both timers with a base frequency of 16 MHz and we will obtain a prescaler value of 16, in order to get a Timer frequency of 1 MHz.

### RNG

The configuration must define the following functions:

```c
/**
 * @brief initializer for the RNG Hardware peripheral
 * @param fp_pHrng RNG Handler
 */
void MacCfg_RNG_Init(RNG_HandleTypeDef * fp_pHrng);

/**
 * @brief Deinitializer for the RNG Hardware peripherial
 * @param fp_pHrng RNG Handler
 */
void MacCfg_RNG_DeInit(RNG_HandleTypeDef * fp_pHrng);
```

Which should call the initialization and deinitialization functions generated by the CubeIDE. In the example project, these functions are defined in `Core/config/src/esps_drv_rng_conf.c`.

!!! Note
    Take in account that it was neccessary also to define the functions `HAL_RNG_MspInit` and `HAL_RNG_MspDeInit`, which are used by the STM32 drivers.

!!! Tip
    You can also generate the code for the RNG peripheral without generating the call in `main.c`. And add the calls to the generated functions in the functions defined in the configuration.

### Hardware Interrupts

The hardware interrupts are set for both timers and for the UART. The MAC Driver have also a generic callback defined for the [UART](../mac_layer/mac_modules.md#uart-interrupt-processing) and for the [timers](../mac_layer/mac_modules.md#timers). At the same time, you have to call these callbacks from the interrupt callback defined in the microcontroller drivers. In the example project, we have defined the functions in `Core/config/src/esps_drv_config.c`:

```c
// Interrupt callbacks for the timers and USART1
void MacCfg_USART1_IRQHandler(void);
void MacCfg_TIM1_UP_TIM16_IRQHandler(void);
void MacCfg_TIM1_TRG_COM_TIM17_IRQHandler(void);
```

And finally, call those callbacks from the default callback generated by the CubeIDE in `Core/Src/stm32gxx_it.c`:

```c
void TIM1_UP_TIM16_IRQHandler(void);
void TIM1_TRG_COM_TIM17_IRQHandler(void);
void USART1_IRQHandler(void);
```
