--8<-- "includes/abbreviations.md"

# Debug and trace

There are two modules that depend completely on the configuration given from the application. Debug and Exception Handling.

## Debug configuration

As mentioned in the [MAC Layer](../mac_layer/mac_modules.md#debug-and-exception-handling), there are several macros used in the drivers to add some debug messages and to trace the program execution. This macros are defined by default to nothing.

In this project we can find an example of how to redirect the debug trace in the drivers to an application. We define `TRACE_DBG` as the call to the function `MacCfg_DBG_printf` which would print out or send the debug message. And then we redifine the drivers debug macro `MACDRV_DBG_PRINT` as the one we just defined, `TRACE_DBG`.

```c
/// Print out information in the debug console
void MacCfg_DBG_printf(const char *formatStr, ...);

// Traces made with this macro appear in the debug console only
#define TRACE_DBG(formatStr, ...)   MacCfg_DBG_printf(formatStr, formatStr OPT_VA_ARGS(__VA_ARGS__));

// Setup the Debug print of the ESPS driver as TRACE_DBG
#ifdef ESPS_CONFIG_DEBUG_TRACE_ENABLE
#define MACDRV_DBG_PRINT(formatStr, ...)   TRACE_DBG(formatStr OPT_VA_ARGS(__VA_ARGS__));
#endif

```

Inside the drivers code, we also can find the macro `MACDRV_DBG_ASSERT`. In this example we have redefined it to call the function `Error_Handler()`, which is provided by the HAL Drivers.

```c
// Typically, Error_Handler() will restart the MCU
#define MACDRV_DBG_ASSERT(condition)       { if (!((bool) (condition))) Error_Handler(); }
```

| Files                      | Path              | Description |
|----------------------------|-------------------|-------------|
| `esps_drv_debug_config.c`  | `Core/config/src` | Debug definitions |
| `esps_drv_debug_config.h`  | `Core/config/inc` | Debug macros definitions |

## Exception Handling

There are in the MAC Driver's code also defined several safety checks that will throw an exception. By default, the macros are defined to do nothing. In the example project you can find defined the different functions that would be called on an exception with the different severities.

The functions that will be called on an exception are defined in  `Core/config/src/esps_drv_exeh_config.c`. And the macros that redefine the macros in the drivers are defined in `Core/config/src/esps_drv_exeh_config.h`. These macros are `EXEH_HANDLE_EX` and `EXEH_HANDLE`.

```c
/**
 * @brief Handler for the exceptions of the ESPS driver with level and ID.
 * @param fp_eLevel         - level
 * @param fp_eModuleID      - the ID of the module reporting the exception.
 * @param fp_s32ExceptionID - the user defined exception ID.
 * @param fp_u32FileLineNo  - line in the file where the exception occurred.
 */
void MacCfg_EXEH_vException(eEXEHSeverityLevel_t fp_eLevel,
                            eEXEHModuleID_t      fp_eModuleID,
                            eMACException_t      fp_s32ExceptionID,
                            uint32_t             fp_u32FileLineNo);

// This macro allows specifying the logical module (M parameter) to which the exception relates
#define EXEH_HANDLE_EX(LEVEL, MOD, EXC)     MacCfg_EXEH_vException(LEVEL, MOD, EXC, __LINE__);

// This is a simpler-to-use version of the EXEH_HANDLE_EX(...) macro where the module ID is not explicitly
// specified and is assumed to be defined in the same module under the name of EXEH_CURRENT_MODULE_ID
#define EXEH_HANDLE(LEVEL, EXC)             EXEH_HANDLE_EX(LEVEL, EXEH_CURRENT_MODULE_ID, EXC);
```

You can see in the implementation of `MacCfg_EXEH_vException()` that we call three different functions depending if we are handling an error, a warning or a fatal error.

| Files                     | Path              | Description |
|---------------------------|-------------------|-------------|
| `esps_drv_exeh_config.c`  | `Core/config/src` | Exception handling definitions |
| `esps_drv_exeh_config.h`  | `Core/config/inc` | Exception handling macros definitions |
