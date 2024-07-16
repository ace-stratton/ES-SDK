project(eps_ctrl C)
set(make_target "eps_ctrl")

list(APPEND eps_ctrl_sources
    "src/eps_ctrl.c"
    "src/eps_ctrl_sm_config_user.c"
    "src/eps_ctrl_sm_config.c"
    "src/eps_ctrl_queue.c"
)

add_library(${make_target} STATIC
    ${eps_ctrl_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} timer hsm)
