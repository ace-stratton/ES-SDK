--8<-- "includes/abbreviations.md"

# ESPS I

!!! Important
    There are some references in the code refering to **ESSA Stack**. This is the **old nomenclature for the ESPS I**. ESSA and ESPS are equivalent.

It is possible to integrate the drivers and only use the ESPS I Stack for Inter-Module communication. This is, send and receive messages between two modules via the RS-485 bus. You can see the specific differences in the [Inter-Module Only](../im_only/im_introduction.md) section.

## Structure

The ESPS I has different layers that must be taken in account when initializing it:

- Transport Layer (TL)
- Command Protocol (CP)
- MAC Test Protocol

The interface with the library is defined in `Core/esps_stack/inc/ESPS_Stack.h`. But in our case, we will use the Function Protocol generated code to send messages with the library. We don't need to interact directly with the calls in the ESPS I.

!!! Note
    There are more protocols included in the ESPS I Stack (FWUPD, ESTL, CCP) but they are not included in this example project. The whole ESPS I Stack it is usually packaged with the OBC Starter Kit from EnduroSat. It is out of the scope of this document to get into details about it. Our [support team]((https://endurosat.com/contact)) is always available to give more information.

## Configuration

Similarly to the MAC Driver, there is a configurable part of the ESPS I that depends on the application. These are some of the public headers of the ESPS I library.

| Files                     | Path                  | Description |
|---------------------------|-----------------------|-------------|
| `ESTL_LayersLocalConf.h`  | `Core/esps_stack/inc` | Parameters for the Transport layer configuration |
| `ESTL_UserDeclarations.h` | `Core/esps_stack/inc` | Additional parameters that affect the application |
| `ESSA_BridgeDrv.h`        | `Core/esps_stack/inc` | Bridge between TL and the Stack |
| `ESSA_MACTest.h`          | `Core/esps_stack/inc` | Protocol to test the MAC Drivers performance |
| `ES_SAT_AIRMAC`           | `Core/esps_stack/inc` | AIRMAC Protocol headers |
| `ES_SAT_API`              | `Core/esps_stack/inc` | Public interface of the ESPS I Stack |
| `ES_SAT_MAC`              | `Core/esps_stack/inc` | Definitions particular to the MAC Drivers |

The ESPS I works together with the Function Protocol. This is why, we need to specify what protocols we are going to use in our project. We created several files to take care of this part of the configuration. As well as some helper functions that are necessary to provide for the Stack.

| Files                 | Path                  | Description |
|-----------------------|-----------------------|-------------|
| `ESPS_Stack.c`        | `Core/esps_stack/src` | ESPS I main functions |
| `ESPS_Stack.h`        | `Core/esps_stack/inc` | Public interface and types declarations |
| `ESPS_CommonUtils.c`  | `Core/esps_stack/src` | Helper functions for the ESPS I |
| `ESPS_CommonUtils.h`  | `Core/esps_stack/inc` | Public interface declarations |
| `ESPS_Stack_Facade.c` | `Core/esps_stack/src` | Initialisation call of the ESPS I, including the Function Protocols we use in our application |
| `ESPS_Stack_Facade.h` | `Core/esps_stack/inc` | Public interface declarations |
| `ESPS_StackConfig.h`  | `Core/esps_stack/inc` | Configuration declarations, including the callbacks for the Function Protocol |

### ESPS I params

It is very important to understand that the link for the different Function Protocols and the MAC Drivers is defined in `ESPS_StackConfig.h`. There are three macros that are populating the arrays with the callback functions:

- `FS_PROTOCOL_HANDLERS_LIST`: Protocols that use the payload in a MAC Frame[^1]. We will define here the Function Protocol and the MAC Test Protocol. The latter, is a protocol used to test the performance of the MAC Driver.
- `FUNCTION_PROTOCOL_HANDLERS_LIST`: Here we should add all the FP descriptors that will be called from our application.
- `NETTYPE_HANDLER_ENTRIES_LIST`: Depending on the network type we use, we should call one or another function to send the messages. In our example, we only have defined the Internal network to send messages with the MAC Driver's function `MAC_DrvEnqMessage`.

This is how it looks in the example project:

```c
// Handlers for MAC payload protocols, defined in ES_SAT_MAC_Protocols.h
#define FS_PROTOCOL_HANDLERS_LIST               ESSA_TL_BridgeDriverProtocol, \
                                                ESSA_MACTEST_Protocol

#define FUNCTION_PROTOCOL_HANDLERS_LIST  \
    (ESSA_pfStack_FunctionProtocolInfoCbk) PingPong_getServerProtocolDescriptor, \
    (ESSA_pfStack_FunctionProtocolInfoCbk) PingPong_getClientProtocolDescriptor


#define NETTYPE_HANDLER_ENTRIES_LIST    \
        NETTYPE_HANDLER_ENTRY(ESSASNETT_INTERNAL, MAC_DrvEnqMessage),  \
        NETTYPE_HANDLER_ENTRY(ESSASNETT_AIR,      NULL)
```

[^1]: This macro doesn't include the Function Protocol. This is hardcoded in `ESSA_Stack.c` since it always must be there.

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

In order to initialize our application properly we only need to call the function that we have defined in the `ESPS_Stack_Facade.c`. Here we are calling the initialization for the ESPS I [^2] and for the PingPong function protocol that we are using as an example.

[^2]: The function is called `ESSA_Stack_Init()`. This is because the ESPS I library still has the old naming convention.

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
