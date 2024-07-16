# Top-level cmake file for building MicroPython on EnduroSat OBC.

cmake_minimum_required(VERSION 3.12)

project(micropython C)

add_library(micropython STATIC
)

# Set the location of this port's directory.
set(MICROPY_PORT_DIR    ${CMAKE_CURRENT_SOURCE_DIR})

# set environment variable for mpy-cross compiler tool
if(CMAKE_HOST_WIN32)
    set(SED_TOOL "${PROJECT_TOOLS_ROOT}/sed.exe ")
    set(MICROPY_MPYCROSS "${PROJECT_TOOLS_ROOT}/mpy_cross_compiler/win/mpy-cross.exe")
elseif(CMAKE_HOST_UNIX AND NOT CMAKE_HOST_APPLE)
    set(MICROPY_MPYCROSS "${PROJECT_TOOLS_ROOT}/mpy_cross_compiler/linux/mpy-cross")
endif()


# set MICROPY_DIR to be grandparent of MICROPY_PORT_DIR
cmake_path(GET MICROPY_PORT_DIR PARENT_PATH PARENT_DIR)
cmake_path(GET PARENT_DIR PARENT_PATH MICROPY_DIR)

set(MICROPY_TARGET micropython)
set(USER_C_MODULES      ${MICROPY_DIR}/esmodules/cmodules/micropython.cmake)

include(${MICROPY_DIR}/py/py.cmake)
include(${MICROPY_DIR}/py/usermod.cmake)
include(${MICROPY_DIR}/extmod/extmod.cmake)

list(
    APPEND module_includes
    ${MICROPY_DIR}
    ${MICROPY_PORT_DIR}
    ${CMAKE_BINARY_DIR}
)

list(APPEND MICROPY_CPP_INC_EXTRA
    ${MICROPY_DIR}
    ${MICROPY_PORT_DIR}
    ${CMAKE_BINARY_DIR}
)

# message(FATAL_ERROR "MICROPY_CPP_INC: ${MICROPY_CPP_INC}")

set(MICROPY_SOURCE_PORT
    main.c
    uart_core.c
    modtime.c
    sdcard.c
    freertos_mphal.c
)
list(TRANSFORM MICROPY_SOURCE_PORT PREPEND ${MICROPY_PORT_DIR}/)

set(MICROPY_SOURCE_SHARED
    libc/printf.c
    readline/readline.c
    runtime/pyexec.c
    runtime/stdout_helpers.c
    runtime/sys_stdio_mphal.c
    runtime/gchelper_generic.c
    timeutils/timeutils.c
)
list(TRANSFORM MICROPY_SOURCE_SHARED PREPEND ${MICROPY_DIR}/shared/)


set(MICROPY_SOURCE_LIB
)
list(TRANSFORM MICROPY_SOURCE_LIB PREPEND ${MICROPY_DIR}/lib/)

# this must be after including py.cmake
set(MICROPY_SOURCE_QSTR
    ${MICROPY_SOURCE_USERMOD}
    ${MICROPY_SOURCE_PY}
    ${MICROPY_SOURCE_EXTMOD}
    ${MICROPY_SOURCE_SHARED}
    ${MICROPY_SOURCE_LIB}
    ${MICROPY_SOURCE_PORT}
)

list(
    APPEND module_sources
    ${MICROPY_SOURCE_PY}
    ${MICROPY_SOURCE_EXTMOD}
    ${MICROPY_SOURCE_SHARED}
    ${MICROPY_SOURCE_PORT}
    ${MICROPY_SOURCE_LIB}
)

# Save the manifest file set from the cmake command line.
set(MICROPY_USER_FROZEN_MANIFEST ${MICROPY_FROZEN_MANIFEST})

# Define mpy-cross flags, for use with frozen code.
set(MICROPY_CROSS_FLAGS -march=armv7emsp)

#  The mpz is used as configuration, becaue in such way we can compile all
#  python files generated for fidles. The reason "none" cannot be used
#  is because in the generated files there are already variables which are
#  using 32 bits.
set(MPY_TOOL_FLAGS -mlongint-impl=mpz)


# Set the frozen manifest file. Note if MICROPY_FROZEN_MANIFEST is set from the cmake
# command line, then it will override the default and any manifest set by the board.
if (MICROPY_USER_FROZEN_MANIFEST)
    set(MICROPY_FROZEN_MANIFEST ${MICROPY_USER_FROZEN_MANIFEST})
elseif (NOT MICROPY_FROZEN_MANIFEST)
    set(MICROPY_FROZEN_MANIFEST ${MICROPY_PORT_DIR}/manifest.py)
endif()

#remove -pedantic compiler option for micropython, there are too many warnings from the implementation of micropython itself.
list(APPEND module_compile_options ${ROOT_COMPILE_OPTIONS})
list(REMOVE_ITEM module_compile_options "-pedantic")


# foreach(_arg ${module_compile_options})
#     message(STATUS "aaaaaaaaa ${_arg}")
# endforeach()

# # set_target_properties(micropython PROPERTIES COMPILE_OPTIONS "${module_compile_options}")
#
# get_target_property(EXTLIB_COMPILE_FLAGS micropython COMPILE_OPTIONS )


add_custom_command(
    OUTPUT always_build_micropy_modules
    COMMENT "Building external MPY modules"
    COMMAND ${Python3_EXECUTABLE} ${MICROPY_DIR}/tools/mpy_cross_all.py -o ${MICROPY_DIR}/esmodules/mpy_output ${MICROPY_DIR}/esmodules/pymodules
)



target_sources(micropython PRIVATE ${module_sources})
target_include_directories(micropython PRIVATE ${ROOT_INCLUDES} PUBLIC ${module_includes})
target_compile_definitions(micropython PUBLIC ${ROOT_COMPILE_DEFS} PRIVATE FFCONF_H="ffconf.h")
target_compile_options(micropython PRIVATE ${module_compile_options})
target_link_options(micropython PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(micropython PRIVATE fatfs usermod sys_time ESPSI)

#
# function GET_TARGET_INCLUDES:
# The function Gather specific includes for additional modules
#
# Example:
#   GET_TARGET_INCLUDES( fatfs
#                    MICROPY_CPP_INC_EXTRA)
#
#    This call adds to the MICROPY_CPP_INC_EXTRA all specific includes for the fatfs target.
#
function(GET_TARGET_INCLUDES TARGET_NAME TARGET_SPECIFIC_INCLUDES)
    set(target_inc_dirs "")
    set(target_source_dir "")
    get_target_property (target_inc_dirs ${TARGET_NAME} INCLUDE_DIRECTORIES)
    get_target_property (target_source_dir ${TARGET_NAME} SOURCE_DIR)

    foreach(_arg ${target_inc_dirs})
        string(COMPARE LESS_EQUAL ${target_source_dir} ${_arg} result)
        if(${result})
            list(APPEND "${TARGET_SPECIFIC_INCLUDES}" ${_arg} )
        endif()
    endforeach()

    set(${TARGET_SPECIFIC_INCLUDES} ${${TARGET_SPECIFIC_INCLUDES}} PARENT_SCOPE)
endfunction()

#   In many cases it is needed for compilation of MPY_CROSS modules to have
#   access to include paths from the TOP Level project. As
#   "target_link_libraries" does not work for MPY_CROSS build step we need
#   to add the needed Include folders manually to MICROPY_CPP_INC_EXTRA variable.
GET_TARGET_INCLUDES( fatfs
                    MICROPY_CPP_INC_EXTRA)

GET_TARGET_INCLUDES( sd_diskio
                    MICROPY_CPP_INC_EXTRA)

GET_TARGET_INCLUDES( sys_time
                    MICROPY_CPP_INC_EXTRA)

GET_TARGET_INCLUDES( ESPSI
                     MICROPY_CPP_INC_EXTRA)


include(${MICROPY_DIR}/py/mkrules.cmake)

target_include_directories(micropython PRIVATE ${MICROPY_GENHDR_DIR} ${MICROPY_DIR}/mpy-cross/build/genhdr)
