# Integration tests for the ESPS I MAC Drivers

In order to run the tests, you will need to get the proper hardware and software. This is a MAC Dongle tuned for the readings (ask around for one) and the tool to execute the tests. There is usually the last version of the tool in the shared folder, in: `\\192.168.1.36\Department\Software\Releases\MAC_DONGLE`. 

If not, it is from the repository [ESPLATFORM_RS485_MAC_DONGLES](https://gitlab.endurosatlab.com/sw-platform-es/cots/msp430fr/ESPLATFORM_RS485_MAC_DONGLES). 

# Run the tests

To run the tests, you have 2 options:

- use the .bat file or .sh script from the release in the shared folder
- run the python script (which is similar to the .bat file, but more complete)

You can find more information on the test cases run from [Confluence](https://endurosat.atlassian.net/wiki/spaces/SPE/pages/819101761/MAC+Test+dongle+based+on+MSP430FR5994+development+kit).

## Executing run_tests_win.bat

If you are in windows, open the file `run_tests_win.bat` and change from the first lines:

```bat
SET COM_DEV=12
SET MAC_ADDR=11
```

- `COM_DEV` is the COM port of the MAC dongle that you are using. It is called **MSP Application UART1 (COMxx)**.
- `MAC_ADDR` is the Address of the device you want to test in hexadecimal.

Once you have done that, you can open a comand window and execute the bat file.

**Both scripts for linux or windows, will stop when a test fails.** It is advisable if you run, manually, once every test case to make sure the device passes and then run the scripts to loop until error through all the test cases.

## Executing run_tests_lin.sh

IF you are running in linux, you should do a similar setup and execute the script run_tests_lin.sh.

**Both scripts for linux or windows, will stop when a test fails.** It is advisable if you run, manually, once every test case to make sure the device passes and then run the scripts to loop until error through all the test cases.


## Executing with python

The approach with the python script is very simialar, it calls randomly a test case. The main difference is that it doesn't stop after an error, it keeps running for a period of time.

You can setup the script by changing the values:

```python
COM_DEV=6
MAC_ADDR=34
# Time to execute in seconds
TEST_TIME = 600
```
COM_DEV and MAC_ADDR are the same as for the other scripts.

- `COM_DEV` is the COM port of the MAC dongle that you are using. It is called **MSP Application UART1 (COMxx)**.
- `MAC_ADDR` is the Address of the device you want to test in hexadecimal.
- `TEST_TIME` is the time in seconds you want the test to be running.

You can find the output in 'test_output_clean.log' as well as a summary of all the run tests:

```
Elapsed time: 600.44 s
TC3: 0/55 errors
TC4: 0/48 errors
TC6: 0/46 errors
TC7: 0/46 errors
TC8: 0/55 errors
TC9: 0/71 errors
TC10: 0/53 errors
TC11: 0/40 errors
TC12: 0/44 errors
TC13: 0/44 errors
TC14: 55/55 errors
TC16: 0/60 errors
TC17: 49/49 errors
```

The file 'test_output.log' takes the output from the command as it comes and it has lots of extra lines. The '_clean' output is the same without those extra lines. Which makes it much easier to read. 
