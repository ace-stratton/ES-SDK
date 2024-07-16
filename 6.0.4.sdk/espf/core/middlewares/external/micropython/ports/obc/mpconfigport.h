#include <stdint.h>

// options to control how MicroPython is built

#define MICROPYTHON_HEAP_SIZE (128 * 1024)
// Use the minimal starting configuration (disables all optional features).
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_BASIC_FEATURES)

#define MICROPY_PY_SYS_EXECUTABLE    (1)
#define MICROPY_PERSISTENT_CODE_LOAD (1)
#define MICROPY_PY_UOS               (1)
#define MICROPY_HELPER_REPL          (1)
#define MICROPY_PY_BUILTINS_HELP     (1)
#define MICROPY_GCREGS_SETJMP        (1)
#define MICROPY_PY_TIME              (1)
#define MICROPY_PY_TIME_GMTIME_LOCALTIME_MKTIME (1)
#define MICROPY_PY_TIME_TIME_TIME_NS (1)
// #define MICROPY_PY_UASYNCIO (1)
//  You can disable the built-in MicroPython compiler by setting the following
//  config option to 0.  If you do this then you won't get a REPL prompt, but
//  you will still be able to execute pre-compiled scripts, compiled with
//  mpy-cross.
#ifndef WINDOWS_BUILD
#define MICROPY_ENABLE_COMPILER (0)
#else
#define MICROPY_ENABLE_COMPILER (1)
#endif

// Float is needed by python scripts implementing some fiddle logic.
#define MICROPY_FLOAT_IMPL        (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_PY_BUILTINS_FLOAT (1)
#define MICROPY_PY_MATH           (1)

#define MICROPY_LONGINT_IMPL (MICROPY_LONGINT_IMPL_MPZ)

// RE is needed by some scripts implementing fiddle logic.
#define MICROPY_PY_URE (1)
// BINASCII is needed by some scripts implementing fiddle logic.
#define MICROPY_PY_UBINASCII (1)

#define MICROPY_QSTR_EXTRA_POOL        mp_qstr_frozen_const_pool
#define MICROPY_ENABLE_GC              (1)
#define MICROPY_HELPER_REPL            (1)
#define MICROPY_MODULE_FROZEN_STR      (0)
#define MICROPY_MODULE_FROZEN_MPY      (1)
#define MICROPY_ENABLE_EXTERNAL_IMPORT (1)

// important because a lot of existing python files are using aliases for
// modules
#define MICROPY_MODULE_WEAK_LINKS (1)

#define MICROPY_ALLOC_PATH_MAX         (256)
#define MICROPY_ALLOC_PARSE_CHUNK_INIT (16)

// type definitions for the specific machine

typedef intptr_t  mp_int_t;  // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long      mp_off_t;

// We need to provide a declaration/definition of alloca()
#include <alloca.h>

#define MICROPY_HW_BOARD_NAME "minimal"
#define MICROPY_HW_MCU_NAME   "unknown-cpu"

#ifdef __linux__
#define MICROPY_MIN_USE_STDOUT (1)
#endif

#ifdef __thumb__
#define MICROPY_MIN_USE_CORTEX_CPU (0)
#define MICROPY_MIN_USE_STM32_MCU  (1)
#endif

#define MP_STATE_PORT MP_STATE_VM
// Enable the VFS, and enable the posix "filesystem".
#define MICROPY_ENABLE_FINALISER (1)
#ifndef WINDOWS_BUILD
#define MICROPY_VFS_FAT    (1)
#define MICROPY_VFS        (1)
#define MICROPY_READER_VFS (MICROPY_VFS)
#endif

#define MICROPY_HELPER_LEXER_UNIX     (1)
#define MICROPY_FATFS_ENABLE_LFN      (1)
#define MICROPY_FATFS_LFN_CODE_PAGE   437 /* 1=SFN/ANSI 437=LFN/U.S.(OEM) */
#define MICROPY_FATFS_USE_LABEL       (1)
#define MICROPY_FATFS_MULTI_PARTITION (0)

#ifndef WINDOWS_BUILD
#define MICROPY_HW_SDCARD_MOUNT_AT_BOOT (1)
#define MICROPY_HW_ENABLE_SDCARD        (1)
#define MICROPY_ENABLE_VM_ABORT         (1)
#endif
