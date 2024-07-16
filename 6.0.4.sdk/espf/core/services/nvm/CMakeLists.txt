project(nvm C)
set(make_target "nvm")

add_library(${make_target} STATIC
    "src/nvm.c"
    "src/nvm_task.c"
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PUBLIC nvm_cfg assertions)
