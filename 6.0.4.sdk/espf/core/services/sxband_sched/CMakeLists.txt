project(sxband_sched C)
set(make_target "sxband_sched")

include(${ROOT_BUILD_PATH}/espf.cmake)

list(APPEND module_sources 
    "src/sxband_sched.c"
    "src/sxband_sched_sm_config_user.c"
    "src/sxband_sched_sm_config.c"
    "src/sxband_cmd_iter_file.c"
    "src/sxband_cmd_iter_cmn.c"
    "src/sxband_sched_report.c"
)

add_library(${make_target} STATIC
    ${module_sources}
)

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PUBLIC datetime crc hsm timer assertions)
