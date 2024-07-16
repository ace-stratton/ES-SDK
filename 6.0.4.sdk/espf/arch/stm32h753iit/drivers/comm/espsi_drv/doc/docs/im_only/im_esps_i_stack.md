--8<-- "includes/abbreviations.md"

# ESPS I (Inter-Module Only)

!!! Important
    There are some references in the code refering to **ESSA Stack**. This is the **old nomenclature for the ESPS I**. ESSA and ESPS are equivalent.

It is possible to integrate the drivers and only use the ESPS I Stack for Inter-Module communication. This is, send and receive messages between two modules via the RS-485 bus. You can see the specific differences in the [Inter-Module Only](../im_only/im_introduction.md) section.

## Structure

From all the layers in the ESPS I Stack, we will just configure the Function Protocol to interact with the Drivers without the overhead of having the whole ESPS I Stack library.

### Files

We will have less files to take care off but the main files that are the connection between the MAC Drivers and the rest of the stack must be present. Some of the files have differences compared to the full ESPS I Initialization described in the [Integration](../guide/int_esps_i_stack.md#configuration) section. These files are:

| Files                 | Path                          | Modifications |
|-----------------------|-------------------------------|---------------|
| `ESPS_Stack.c`        | `Core/esps_stack_im_only/src` | :white_check_mark: |
| `ESPS_Stack.h`        | `Core/esps_stack_im_only/inc` | :white_check_mark: |
| `ESPS_CommonUtils.c`  | `Core/esps_stack_im_only/src` | No changes |
| `ESPS_CommonUtils.h`  | `Core/esps_stack_im_only/inc` | No changes |
| `ESPS_Stack_Facade.c` | `Core/esps_stack_im_only/src` | No changes |
| `ESPS_Stack_Facade.h` | `Core/esps_stack_im_only/inc` | No changes |
| `ESPS_StackConfig.h`  | `Core/esps_stack_im_only/inc` | No changes |

:white_check_mark:

From all the headers of the ESPS I Stack binary, we will only need the ones that define the MAC Drivers types and public functions:

| Files                     | Path                          | Description        |
|---------------------------|-------------------------------|--------------------|
| `ES_SAT_MAC`              | `Core/esps_stack_im_only/inc` | :white_check_mark: |

The rest of the files are not present in the folder since they are not needed.

### ESPS I Configuration

It is very important to understand that the link for the different Function Protocols and the MAC Drivers is defined in `ESPS_StackConfig.h`. There are three macros that are populating the arrays with the callback functions:

- `FS_PROTOCOL_HANDLERS_LIST`: This macro is not defined for the Inter-Module Only configuration. The only FS_PROCOTOL is going to be the Function Protocol.
- `FUNCTION_PROTOCOL_HANDLERS_LIST`: Here we should add all the FP descriptors that will be called from our application.
- `NETTYPE_HANDLER_ENTRIES_LIST`: Depending on the network type we use, we should call one or another function to send the messages. In our example, we only have defined the Internal network to send messages with the MAC Driver's function `MAC_DrvEnqMessage`.

This is how it looks in the example project:

```c
#define FUNCTION_PROTOCOL_HANDLERS_LIST  \
    (ESSA_pfStack_FunctionProtocolInfoCbk) PingPong_getServerProtocolDescriptor, \
    (ESSA_pfStack_FunctionProtocolInfoCbk) PingPong_getClientProtocolDescriptor


#define NETTYPE_HANDLER_ENTRIES_LIST    \
        NETTYPE_HANDLER_ENTRY(ESSASNETT_INTERNAL, MAC_DrvEnqMessage)
```

### Message Priority

The priority levels are defined in `ESPS_Stack.h` and are used for the MAC drivers to set the delays to send the different mesasges.

```c
// Keep those in TQ and at least 2 between them
// And not below 1, since inter byte delay may fool some node to start transmitting in middle of message
#define ESSASMP_PRIORITY_TQ_SPAN    6

typedef enum {
    ESSASMP_CRITICAL = 1,       // Reserved only for operational modes ! - one needed to ensure at least 1 TQ is passed after last transmission
    ESSASMP_HIGH = 3,           // Overlap half critical, half normal. Used for entering bootloader, service, discovery etc.
    ESSASMP_NORMAL = ESSASMP_CRITICAL + ESSASMP_PRIORITY_TQ_SPAN,   // Usual application level
    ESSASMP_LOW = ESSASMP_NORMAL + ESSASMP_PRIORITY_TQ_SPAN,    // Big not time critical packets like pictures etc
} ESSATMAC_MsgPriority;
```
TQ, stands for Time Quantum and it is used as a minimum time unit for the MAC Drivers, it is set in `esps_drv_def.h`. It takes a value of [360 micro seconds by default](../mac_layer/mac_configuration.md#parameters-of-the-mac-drivers).

## Initialization

In order to initialize our application properly we only need to call the function that we have defined in the `ESPS_Stack_Facade.c`. Here we are calling the initialization for the ESPS I [^1] and for the PingPong function protocol that we are using as an example.

[^1]: The function is called `ESSA_Stack_Init()`. This is because the ESPS I library still has the old naming convention.

```c
void ESPS_Stack_Facade_Init()
{
    // initialize ESPS I
    ESSA_Stack_Init();

    // initialize Function Protocol interfaces
    PingPongClientAppInit();
    PingPongServerAppInit();
}
```

!!! Note
    If you add additional Function Protocols to your application, you will need to add the initialisation here.

The ESPS I initialization function is in charge of linking all the defined Function Protocols with the callbacks for requests and responses.
