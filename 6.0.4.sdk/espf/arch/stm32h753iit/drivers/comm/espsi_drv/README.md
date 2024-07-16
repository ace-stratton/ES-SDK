# ESPS I MAC Drivers

ESPS I driver for RS-485 UART communication

### Documentation

There is a documentation for the drivers as well as the integration documentaiton in a project using ESPS I network stack in the `doc` folder.

**To generate the mkdocs documentation**, you must have python and the mkdocs library installed. Then you can run the command `mkdocs build` from the `doc` folder.

**To generate the doxygen documentation**, you must have doxygen installed in your pc. Then generate the doxygen by running `doxygen` from the folder `doc/doxygen` (where the `Doxyfile` is located). This will generate an html output.

## Parasoft Tests

How to run and update the Parasoft Tests

## MAC Donlge Tests

The drivers should pass all the [test cases](https://endurosat.atlassian.net/wiki/spaces/SPE/pages/819101761/MAC+Test+dongle+based+on+MSP430FR5994+development+kit) indicated (except the ones for MAC 2).

### Run the tests

**Hardware:**
- 'Tuned' MAC Dongle with capacity to measure different parameters.
- Connections between the device under test (DUT) and the MAC Dongle (RS-485 A and RS-485 B).

**Software:**
- MAC Dongle the latest software: `\\192.168.1.36\Department\Software\Releases\MAC_DONGLE`.
  - There should be a file `ES_SAT_MACGW_Impl.hex`. That should be flashed on the MAC Dongle.
- From the MAC Dongle release folder, you can call the `ES_SAT_MACGW_CMD` as follows:
`ES_SAT_MACGW_CMD TC=X COM_PORT=X DEST_MAC_ADDR=XX`

The parameters `COM_PORT` and `DEST_MAC_ADDR` should match the port for the MAC Dongle in your PC and the MAC Address of the DUT.

Alternative:
- Use the es-mac-tester tool developed for this purpose. It is installed as a python package and it can be downloaded from [here](https://gitlab.endurosatlab.com/sw-platform-es/experimental/scripts/-/tree/main/es_mac_tester). 

*You can flash the dongle by installing [UNIFLASH from TI](https://www.ti.com/tool/UNIFLASH).*

**Test:**

I recommend to run the tests at least once by hand before leaving the DUT to run randomly for a long time.

I also recommend to use the es-mac-tester tool. You can run it like this:

```
> es-mac-tester set-port <COM_PORT>
> es-mac-tester set-target <TARGET_MAC_ADDRESS>

> es-mac-tester run tc3 --verbose
Elapsed time: 251.49 s
TC3: 0/1 errors
TC4: 0/0 errors
TC6: 0/0 errors
TC7: 0/0 errors
TC8: 0/0 errors
TC9: 0/0 errors
TC10: 0/0 errors
TC11: 0/0 errors
TC12: 0/0 errors
TC13: 0/0 errors
TC14: 0/0 errors
TC16: 0/0 errors
TC17: 0/0 errors

> es-mac-tester run random -t250 --verbose

Elapsed time: 251.49 s
TC3: 8/26 errors
TC4: 0/22 errors
TC6: 0/12 errors
TC7: 0/22 errors
TC8: 0/15 errors
TC9: 0/23 errors
TC10: 1/22 errors
TC11: 0/22 errors
TC12: 2/26 errors
TC13: 0/20 errors
TC14: 0/15 errors
TC16: 0/25 errors
TC17: 0/13 errors

```

The script will run for the amount of time set in `-t` or `--timeout` and it will generate an output file with the logs of the tests and a final summary, `es_mac_tester.log`. You can also run the test cases 1 one by one by setting the argument to `tc3`, `tc4` or `tcx` instead of to `random`.
