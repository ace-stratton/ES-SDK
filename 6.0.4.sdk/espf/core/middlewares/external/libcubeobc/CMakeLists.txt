project(cubeobc C)
set(make_target "cubeobc")

# Read the file contents into a variable
file(READ "version" VERSION_CONTENTS)
file(READ "systemversion" SYSTEMVERSION_CONTENTS)

# Extract the version numbers using regular expressions
string(REGEX MATCH "VERSION := ([0-9]+)\\.([0-9]+)\\.([0-9]+)" MATCHED_VERSION "${VERSION_CONTENTS}")

# Extract the major, minor, and patch versions from the matched string
set(VERSION_MAJOR ${CMAKE_MATCH_1})
set(VERSION_MINOR ${CMAKE_MATCH_2})
set(VERSION_PATCH ${CMAKE_MATCH_3})

string(REGEX MATCH "SYSTEM_VERSION := ([0-9]+)\\.([0-9]+)\\.([0-9]+)" MATCHED_VERSION "${SYSTEMVERSION_CONTENTS}")

# Extract the major, minor, and patch versions from the matched string
set(SYSTEM_VERSION_MAJOR ${CMAKE_MATCH_1})
set(SYSTEM_VERSION_MINOR ${CMAKE_MATCH_2})
set(SYSTEM_VERSION_PATCH ${CMAKE_MATCH_3})

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/api/src"
    "${PROJECT_SOURCE_DIR}/include"
)

list(APPEND module_sources
    "api/src/tctlmCommonFramework1.c"
    "api/src/tctlmCommonTransfer1.c"
    "api/src/tctlmCubeCommonBaseBootloader5.c"
    "api/src/tctlmCubeComputerCommon3.c"
    "api/src/tctlmCubeComputerControlProgram8.c"
    "api/src/tctlmCubeIrControlProgram1.c"
    "api/src/tctlmCubeMagCommon1.c"
    "api/src/tctlmCubeMagControlProgramCommon1.c"
    "api/src/tctlmCubeMagControlProgramCompact1.c"
    "api/src/tctlmCubeMagControlProgramDeploy1.c"
    "api/src/tctlmCubeNodeCommon1.c"
    "api/src/tctlmCubeNodeControlProgramNssrwl1.c"
    "api/src/tctlmCubeNodeControlProgramPst3s1.c"
    "api/src/tctlmCubeSenseCommon1.c"
    "api/src/tctlmCubeSenseControlProgram5.c"
    "api/src/tctlmCubeWheelControlProgram3.c"
    "src/cubeObc_bootloader.c"
    "src/cubeObc_bulkDataTransfer.c"
    "src/cubeObc_common.c"
    "src/cubeObc_cubeComputer.c"
    "src/cubeObc_init.c"
    "src/cubeObc_tctlmCommsMasterSvc.c"
)

add_library(${make_target} STATIC ${module_sources})

target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS} PRIVATE
    VERSION_MAJOR=${VERSION_MAJOR}
    VERSION_MINOR=${VERSION_MINOR}
    VERSION_PATCH=${VERSION_PATCH}
    SYSTEM_VERSION_MAJOR=${SYSTEM_VERSION_MAJOR}
    SYSTEM_VERSION_MINOR=${SYSTEM_VERSION_MINOR}
    SYSTEM_VERSION_PATCH=${SYSTEM_VERSION_PATCH}
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})