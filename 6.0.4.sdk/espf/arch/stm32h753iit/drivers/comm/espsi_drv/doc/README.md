# Introduction

This guide aims to provide all the information regarding to the integration and use of the MAC layer driver that is part of the ESPS I network stack.

## ESPS I

ESPS I is a network stack protocol developed by Endurosat. It is designed to provide message exchanges between the ground station and the satellite modules. The lowest layer, before the HAL, is the MAC layer.

## MAC layer
This layer is responsible for the final encapsulation of higher-level messages into frames, that are sent over the network to other devices using the RS-485 protocol. It is the lowest layer, from the ESPS I, that is concerned with addressing. It contains information about the sender and the destination. Each device in an ESPS I network has an unique number called MAC Address. On this layer errors that occur are handled, for example, using a CRC field.

### HW Requirements

The MAC layer is implemented on a ST Microelectronics microcontroller and it needs to have access at least to an UART port, three GPIO, two timers and a random number generator module. For more details, go to the [MAC Configuration](mac_layer/mac_configuration.md) section.

### Integration

For more information about the MAC layer, go to [MAC layer](mac_layer/mac_hl_design.md). If you prefer to start with the integration guide, go to [Integration Guide](guide/int_configuration.md).