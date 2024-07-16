--8<-- "includes/abbreviations.md"

# Libraries

The MAC drivers rely on the implementation of the CRC calculation library and on the ESPS I library.

## CRC Calculation

There is a CRC field at the beggining and at the end of a MAC Frame. This library contains some helper funtions to calculate the CRC and to verify the received messages.

### Files

| Files                     | Path                     | Description |
|---------------------------|--------------------------|-------------|
| `crc16-ccitt.c`           | `esps_drv/lib/crc16/src` | CRC32 CIITT calculation |
| `crc16-ccitt.h`           | `esps_drv/lib/crc16/inc` | Public interface declarations |
| `MACCRC32_Classic_Impl.c` | `esps_drv/lib/crc16/src` | CRC32 classic calculation |
| `MACCRC32_Classic_Impl.h` | `esps_drv/lib/crc16/inc` | Public interface declarations |

## ESPS I

We mentioned the stack in the Configuration section since there are some definitions needed for the right performance of the drivers. But typically, the ESPS I is added to the project as a static library and built together. See how in the [Integration](../guide/int_esps_i_stack.md) section.

For more information about how to setup the ESPS I Stack go to the  [Integration](../guide/int_esps_i_stack.md) section.

If you are interested only in Inter-Module communication, you will also need to check the [Inter-Module Only](../im_only/im_introduction.md) section.