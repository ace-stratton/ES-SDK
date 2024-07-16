project(arm_fault_handler C)
set(make_target "arm_fault_handler")

list(APPEND module_sources
    "src/arm_fault_handler.c"
    "inc/arm_fault_handler.h"
)

add_library(${make_target} STATIC
    ${module_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} crc)
