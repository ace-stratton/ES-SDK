/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup sys_printf
 * @{
 *
 * Based on the 3rd party [printf](https://github.com/mpaland/printf) library
 * extending the interface to enable easier configuration for the users.
 * With this service you can use a `printf`-like interface for sending formatted
 * strings to a system-defined output for tracing purposes.
 *
 * @file sys_printf.c
 *
 * @file sys_printf.h
 * @brief `sys_printf` library public interface based on [printf](https://github.com/mpaland/printf).
 *
 * @}
 * @}
 */
#ifndef SYS_PRINTF_H_
#define SYS_PRINTF_H_

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>


/**
 * @brief  A pointer to a function which implements printing a single character to an output sink.
 *
 * @param  ch The ASCII code of the character to print
 *
 * @note   The function is provided by the user.
 *         Different implementations can be used to print to different
 *         output sinks (e.g. UART, file, ARM trace port, etc.).
 *         The function returns control when the data has been printed.
 */
typedef void(*sys_printf_char_func_t)(char ch);

/**
 * @brief  A pointer to a function which implements printing a single character to an output sink.
 *
 * @param  ch The ASCII code of the character to print
 * @param  arg A pointer to a user-defined structure to pass additional arguments to the print function
 */
typedef void(*sys_printf_custom_func_t)(char ch, void* arg);


/**
 * @brief  Initializes the printf module
 *
 * @param  func User-defined function to output single character
 */
void sys_printf_init(sys_printf_char_func_t func);


/**
 * @brief  Same as printf()
 *
 * @param  fmt Format string
 *
 * @return Number of processed characters
 */
int sys_printf(const char* fmt, ...);


/**
 * @brief  Same as vprintf()
 *
 * @param  fmt Format string
 *
 * @return Number of processed characters
 */
int sys_vprintf(const char* fmt, va_list va);


/**
 * @brief  Same as snprintf()
 */
int sys_snprintf(char* buffer, uint32_t count, const char* format, ...);


/**
 * @brief  Same as vsnprintf()
 */
int sys_vsnprintf(char* buf, const size_t maxlen, const char* fmt, va_list va);


/**
 * @brief  Same as printf() and passes it to user-defined function
 *
 * @param  func User-defined function to process the
 * @param  arg User data
 * @param  fmt Format string
 *
 * @return Number of processed characters
 */
int sys_printf_fct(sys_printf_custom_func_t func, void* arg, const char* fmt, ...);


#endif /* SYS_PRINTF_H_ */
