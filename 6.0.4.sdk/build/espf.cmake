# This is the absolute path to the macaron build wrapper script.
cmake_path(SET MACARON_PY "${CMAKE_SOURCE_DIR}/macaron.py")

# If your Python executable is not on the global path, please set the PYTHON 
# environment variable to the full path of your Python executable. 
if(DEFINED ENV{PYTHON})
    set(PY $ENV{PYTHON})
else()
    set(PY python)
endif()

# This variable is used in all CMakeLists.txt files which include this file and
# need to execute the macaron build wrapper directly. Only command options need
# to be provided by the users.
set(MACARON_CMD ${PY} ${MACARON_PY})

# This is a short-cut definition for the FIDL code generation command of the macaron
# build wrapper. Modules which include this file and would like to execute FIDL
# generation with specific options, can use this variable directly.
set(FP_GEN_CMD ${MACARON_CMD} -fp)

# This is a short-cut definition for the DataCache code generation command of the macaron
# build wrapper. Modules which include this file and would like to execute DC
# generation with specific options, can use this variable directly.
set(DC_GEN_CMD ${MACARON_CMD} -datacache)

# 
# function FP_GEN:
# The function performs generation of C source code from a macchiato deployment schema file.
# Parameters:
#     <OUTPUT_SRC_LIST>: a list of all generated C source files to be used as dependencies of the
#                       custom command added to the module in order to re-trigger a build if the
#                       code generation modifies those sources
#     <FDEPL_FILE_NAME>: full path to the macchiato deployment schema file used for the code generation
#       <FIDL_DEP_LIST>: list of all FIDL files referred to by <FDEPL_FILE_NAME> to be used as dependencies
#                       for the custom command added to the module. This way, if a FIDL file gets modified,
#                       the code generation will be triggered automatically by CMake. 
# 
# Example:
#      You can use code similar to the following in your own CMakeLists.txt file:
#
#      include(${ROOT_BUILD_PATH}/espf.cmake)
#
#     cmake_path(SET beacons_fdepl_path "${PROJECT_SOURCE_DIR}/config/Beacons.fdepl")
#     cmake_path(SET beacons_fidl_path "${FIDL_ROOT_OBC}/Beacons.fidl")
#    
#     list(APPEND fp_beacons_src_list
#         ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsProtocolServer.c
#         ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsProtocolServer.h
#         ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsProtocolTypes.h
#         ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsServerApp.c
#         ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsServerApp.h
#     )
# 
#     FP_GEN(fp_beacons_src_list ${beacons_fdepl_path} beacons_fidl_path)
#
#     The code above will trigger FIDL code generation for file Beacons.fidl if:
#       - Beacons.fidl file gets modified.
#         - Beacons.fdepl file gets modified.
#      In addition to that, when the code generation command producing the files listed in ${fp_beacons_src_list}
#      executes, any CMake targets listing those files as part of their source list will get rebuilt through the
#     CMake dependency tree. 

function(FP_GEN OUTPUT_SRC_LIST FDEPL_FILE_NAME FIDL_DEP_LIST)
    add_custom_command(OUTPUT ${${OUTPUT_SRC_LIST}}
        COMMAND ${FP_GEN_CMD} -dc ${FDEPL_FILE_NAME} VERBATIM
        DEPENDS ${${FIDL_DEP_LIST}} VERBATIM)
endfunction(FP_GEN)

# function FP_GEN_AT_PATH:
# The function performs exactly the same action as FP_GEN but can be given an additional parameter
# <GEN_PATH> which specifies in which folder the macchiato-generated files will be placed.
#
function(FP_GEN_AT_PATH OUTPUT_SRC_LIST FDEPL_FILE_NAME FIDL_DEP_LIST GEN_PATH)
    add_custom_command(OUTPUT ${${OUTPUT_SRC_LIST}}
        COMMAND ${FP_GEN_CMD} -dc ${FDEPL_FILE_NAME} -fmr ${GEN_PATH} VERBATIM
        DEPENDS ${${FIDL_DEP_LIST}} VERBATIM)
endfunction(FP_GEN_AT_PATH)

# Get the project version from the version file. It is expecting a format of major.minor.patch.
# This function will set the variables that can be used added as compilation defines:
#   - {project}_VERSION_MAJOR
#   - {project}_VERSION_MINOR
#   - {project}_VERSION_PATCH
#   - {project}_VERSION_LABEL
function(define_version_from_file file_path)
    # Read the file contents into a variable
    file(READ ${file_path} VERSION_CONTENTS)

    # Extract the version numbers using regular expressions
    string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)[-]?([a-zA-Z0-9_-]*)" MATCHED_VERSION "${VERSION_CONTENTS}")

    # Extract the major, minor, and patch versions from the matched string
    if(NOT ${CMAKE_MATCH_1} STREQUAL "")
        set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR ${CMAKE_MATCH_1} PARENT_SCOPE)
    else()
        # Set 0 if the version file contains an invalid format
        set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 99 PARENT_SCOPE)
    endif()
    
    if(NOT ${CMAKE_MATCH_2} STREQUAL "")
        set(${CMAKE_PROJECT_NAME}_VERSION_MINOR ${CMAKE_MATCH_2} PARENT_SCOPE)
    else()
        set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 99 PARENT_SCOPE)
    endif()
    
    if(NOT ${CMAKE_MATCH_3} STREQUAL "")
        set(${CMAKE_PROJECT_NAME}_VERSION_PATCH ${CMAKE_MATCH_3} PARENT_SCOPE)
    else()
        set(${CMAKE_PROJECT_NAME}_VERSION_PATCH 99 PARENT_SCOPE)
    endif()
    
    if(NOT ${CMAKE_MATCH_4} STREQUAL "")
        set(${CMAKE_PROJECT_NAME}_VERSION_LABEL ${CMAKE_MATCH_4} PARENT_SCOPE)
    # If the version file doesn't match the regex, set the label to its contents
    elseif("${CMAKE_MATCH_1}" STREQUAL "" OR "${CMAKE_MATCH_2}" STREQUAL "" OR "${CMAKE_MATCH_3}" STREQUAL "")
        string(STRIP "${VERSION_CONTENTS}" STRIP_VERSION)
        set(${CMAKE_PROJECT_NAME}_VERSION_LABEL ${STRIP_VERSION} PARENT_SCOPE)
    endif()

endfunction(define_version_from_file)
