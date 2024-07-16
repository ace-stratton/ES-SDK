--8<-- "includes/abbreviations.md"

# Configuration

Since the MAC Drivers rely on the HAL Layer from STMicroelectronics, it is necessary to provide the initialization of the necessary peripherals and an interface to them for the MAC Layer. Similarly, the MAC Layer needs information about the network, the ESPS I, in which is going to be integrated.

!!! important
    The configuration included in the drivers is only to indicate the dependencies with the MCU or with the application. The implementation of certain functions must be done for the drivers to work and it depends entirely on the MCU and project to be used. Learn more about it in the [Integration Guide](../guide/int_introduction.md)

## Configuration structure

When the MAC Drivers are initialized, they will call the callbacks provided in the struct `sMACInterfaceImmutableConfig_t` to initialize the hardware peripherals. The initialization of the peripherals depends on the specific device, that is why the MAC Drivers cannot know before hand. The struct mentioned before, contains another struct, `sMACConfig_t`, which must contain the information about other necessary parameters for the MAC Drivers. Both structs are defined in `esps_drv_ct.h.template`:

```c
/// Structure with configuration values for a MAC interface.
typedef struct {
    /// The UART register base
    USART_TypeDef *const psUART;
    /// UART Baudrate for the interface
    const uint32_t u32Baudrate;
    /// NVIC interrupt mask to enable/disable the UART global interrupt
    const uint32_t u32NVICMask;
    /// The RCC clock mask to enable/disable the peripherial
    const uint32_t u32RCCMask;
    /// The RCC clock source of the UART peripheral
    const eRCCPeripheralClock_t eClockSource;
    /// The TIM ID to use for transmission timing related tasks.
    const eTIMTimerID_t eTXTIMID;
    /// The TIM ID to use for reception timing related tasks.
    const eTIMTimerID_t eRXTIMID;
    /// Time quantum value in microseconds.
    const uint16_t u16TQVal;
} sMACConfig_t;

/// This structure contains parameters that will not be modifiable at runtime, it shall be placed in a FLASH section
typedef struct {
    /// Enable transmission callback
    const pfSetResetCb_t pfEnableTX;
    /// Disable transmission callback
    const pfSetResetCb_t pfDisableTX;
    /// Enable reception callback
    const pfSetResetCb_t pfEnableRX;
    /// Disable reception callback
    const pfSetResetCb_t pfDisableRX;
    /// The static configuration of the UART/MAC
    const sMACConfig_t sHwConfig;
    /// UART init callback
    const pfUartInitDeinitCb_t pfUartInit;
    /// UART deinit callback
    const pfUartInitDeinitCb_t pfUartDeinit;
} sMACInterfaceImmutableConfig_t;
```

To see more specific information about the configuration, see the [Integration](../guide/int_configuration.md) section.

## Parameters of the MAC Drivers

Some of the behaviour of the MAC Drivers can be defined with some of the definitions from `esps_drv_def.h.template`.

Default values for the MAC Drivers:

 - `MAC_DEFAULT_BAUDRATE`: Baudrate for the UART in Hz. Default 50000.
 - `MAC_DEFAULT_TQ`: Time Quantum for the priority calculations of the bus in micro seconds. Default 360 micro seconds.
 - `MAC_DEFAULT_BASEPRIO`: Base priority level for the MAC interface of the device in time quantum (TQ) units. Default 0.
 - `MAC_DEFAULT_ADDRESS`: MAC address for the interface of the device. This should be defined by the user.

The drives have a retry mechanism. In case the bus is not free after a given time, it will reduce the **dynamic priority** of the interface to try to send the message. The dynamic priority will keep its value until there it a successful message sent.

 - `RS485_MAX_TX_WAIT_TIMEOUT`: Time to wait before increasing the Dynamic Prority and retry to send the message.
 - `RS485_MAX_TX_RETRY_COUNT`: The number of retries to be attempted before giving up the message and notifying the sender.
 - `RS485_MINIMUM_PRIORITY`: The minimum **value** of the dynamic priority would reach.
 - `RS485_INITIAL_PRIORITY`: The initial **value** of the dynamic priority.

### Files

| Files                                 | Path           | Description |
|---------------------------------------|----------------|-------------|
| `esps_drv_config.h.template`          | `esps_drv/cfg` | Main configuration definitions |
| `esps_drv_debug_config.h.template`    | `esps_drv/cfg` | Interface with the debug macros between the application and the drivers |
| `esps_drv_def.h.template`             | `esps_drv/cfg` | Basic definitions for the drivers |
| `esps_drv_esps_stack.h.template`      | `esps_drv/cfg` | Interface with the ESPS I |
| `esps_drv_exeh_config.h.template`     | `esps_drv/cfg` | Interface with the Exception Handling module (if there is any in the application) |
| `esps_drv_rng_config.h.template`      | `esps_drv/cfg` | Definitions for the initialization of the RNG Hardware peripheral |
| `esps_drv_stm32.h.template`           | `esps_drv/cfg` | Interface with the necessary STM32 Drivers |
| `esps_drv_tim_config.h.template`      | `esps_drv/cfg` | Definitions of the timer peripheral |

## Hardware peripherals

The MAC layer uses two timers, the UART, the RNG and three GPIO for the control of the signals needed for the RS-485.

You can find more information about how to integrate the drivers with an application in the [Integration](../guide/int_configuration.md) section.

### UART and GPIO

The UART and GPIO initialization depends on the microcontroller used. Anyhow, the MAC Drivers require the callbacks for initialization and deinitialization to be provided as part of the `sMACInterfaceImmutableConfig_t` struct. This way it can be reset in case of fatal error.

For the UART, the fields `const pfUartInitDeinitCb_t pfUartInit;` and `const pfUartInitDeinitCb_t pfUartDeinit;` must be provided.

For the GPIO, we have a bit different setup. We need to define three GPIO.

- **Driver Enable (DE)**: Controlled by the software, whether to enable or disable the transmition of messages.
- **Clear to Send (CTS)**: Also called Receiver Enable (**nRE**), it must be enable to receive from the bus. It will be disable during transmissions.
- **Termination Enable (TE)**: Depending on the chip of the transceiver, you might be able to set a termination resistor. Both end devices in the bus should have one.

By controlling the **DE** signal, we can stop the drivers from sending messages. This signal must be OFF when the device is not sending to avoid keeping the bus busy. Therefor, two callbacks for enable and disable the signal **must be defined and provided** to the configuration struct, `const pfSetResetCb_t pfEnableTX;` and `const pfSetResetCb_t pfDisableTX;`.

Similarly, we can control the **nRE** (or **CTS**) signal to stop receiving from the RS-485 bus. The signals is always enabled (set to 0) unless the device starts a transmission. Again, two callbacks for enable and disable the signal **must be defined and provided** to the configuration struct, `const pfSetResetCb_t pfEnableRX;` and `const pfSetResetCb_t pfDisableRX;`.

Finally, there is an option to set or to read the state of the **TE** pin using the following two functions declared in `esps_drv_config.h`:

```c
// Get and Set Termination Enable bit for the UART interface.
bool MacCfg_bGetBusTerminationState (const eMACInterface_t eMacIf);
void MacCfg_vSetBusTerminationState (const eMACInterface_t eMacIf, const bool bNewState);
```

These two functions are called from the MacServices[^1] function protocol.

!!! note
    Not every RS-485 transceiver has the possibility of setting the Termination resistor by driving a GPIO. If this option is not available, the functions mentioned above will be pointless.

[^1]: FP Layer is defined at the application level. It uses the ESPS I, and the MAC Layer, to send messages between devices.

### Timers

There are two timers related to the UART, transmission and reception timer. The timers are necessary for setting the priority delay before sending a message or to set timeouts to avoid blocking the communication. The structure that contains the configuration information of a timer is `sTIMTimerEntry_t`, and it is defined in `esps_drv_ct.h`:

```c
/// TIM pool entry.
typedef struct sTIMTimerEntry_t {
    // Pointer to the TIM register base
    TIM_TypeDef *psTIM;
    // The clock source for the TIM instance.
    eRCCPeripheralClock_t eClockSrc;
    // APB(1/2) clock enable/disable mask.
    uint32_t u32ClockMask;
    // Prescaler value for the Timer.
    uint32_t u16Prescaler;
    // NVIC Interrupt
    uint32_t u32NVICInterrupt;
    // Event flags to set on expiration.
    pfTIMCallback_t pfCallback;
    // Data to deliver to the callback upon expiration or timeout
    void *pvData;
    // Running or not flag
    bool bRunning;
    // Used or not flag
    bool bUsed;
} sTIMTimerEntry_t;
```

This structure must be defined for each timer in the configuration and it depends on the microcontroller used for the project. The drivers are expecting `TIM_CFG_asTimerEntries` to be filled up with the information as declared in `esps_drv_tim_config.h`.

The enumeration type `eTIMTimerID_t` must have a number per timer in the application.

Also, the function `uint16_t MacCfg_TIM_u16CalculatePrescaler(sTIMTimerEntry_t * fp_psTIM);` must also be implemented for the drivers. This function, must return a value that will set the timer to run with 1 micro second per tick. So it depends on the base frequency that the timer has assigned from the microcontroller.

!!! important
    If the timers are not set to 1 micro second per tick, the device will disturb the proper performance of the network.

### RNG

Another peripheral that drivers use is the random number generator. It creates an array with random numbers. The configuration must define the following functions, which should call the initialization and deinitialization functions for the specific microcontroller:


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

!!! important
    The driver will call the HAL Drivers function `HAL_RNG_GenerateRandomNumber` from `stm32xxxx_hal_rng.h` (from STM32 HAL Drivers).

!!! Tip
    In the current implementation, the drivers are using the hardware RNG of the microcontroller but this is not mandatory. In case the MCU doesn't have RNG peripheral, an interface to the software random generation can be programmed and to pass to the drivers as if it were the RNG from hardware.

After generating the random numbers array, the drivers will deinitialize the RNG peripheral.

### Microncontroller headers

The MAC Drivers are using functions from the HAL Drivers defined by ST. They access this functions by adding the header file `esps_drv_stm32.h`. This file must be modified to have the calls to the right microcontroller drivers used in the application. Keep in mind that some drivers are using the HAL version but some others are using the LL version. For more information see the table in the [Integration](../guide/int_configuration.md) section.

!!! Warning
    It is possible that some calls vary between different versions or that some microcontrollers are not compatible. In case you find any compatibility issues, contact our [support team](https://endurosat.com/contact).

## ESPS I

!!! Important
    There are some references in the code refering to **ESSA Stack**. This is the **old nomenclature for the ESPS I**. They are equivalent.

To use the MAC driver in your application, you need to setup the ESPS I.

You can find in the configuration folder, a header called `esps_drv_esps_stack.h`. This header contains the following includes:

```c
#include "ES_SAT_MAC/ES_SAT_MAC.h"
#include "ESPS_Stack.h"
```

These two headers contain the types and definitions that the MAC Drivers need in order to cover the network configuration requisites. But in the end, this will need to be modified to point to the headers in the project. See the [Integration](../guide/int_configuration.md) section.

Some of the necessary definitions from the stack are:

- `ESSATMAC_MsgPriority`: Priority values for the transmitted messages.
- `ESSATMAC_ErrCodes`: Error codes on sending a message.
- `ESSATMAC_Message`: The message structure
- `ESSATMAC_Context`: The context for sending or receiving the messages.
- `ESSA_Stack_DataDispatch`: The call to the dispatcher function that takes care of the received messages.
- `ESSATMAC_ADDR_BROADCAST`: Broadcast address for thw whole ESPS I network.
- `ESSATMAC_ADDR_GATEWAY_DEV`: Broadcast address for a group of devices.

!!! Important
    The values for this parameters are set in the ESPS I, for the drivers to work correctly, the includes in `esps_drv_esps_stack.h` must be the ones that the application is using to setup the ESPS I network.
