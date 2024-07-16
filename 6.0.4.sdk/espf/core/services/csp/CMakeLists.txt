project(csp_service C)

add_library(csp_service STATIC
    "src/csp_service.c"
)

target_include_directories(csp_service PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(csp_service PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(csp_service PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(csp_service PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(csp_service PRIVATE csp)