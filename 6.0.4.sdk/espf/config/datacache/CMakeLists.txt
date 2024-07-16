project(datacache C)
set(make_target "datacache")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fdepl_path "${PROJECT_SOURCE_DIR}/deploy_dc.fdepl")
cmake_path(SET fdepl_io_path "${PROJECT_SOURCE_DIR}/deploy_dc_io.fdepl")
cmake_path(SET dc_fidl_path "${PROJECT_SOURCE_DIR}/DataCache.fidl")
cmake_path(SET dc_types_fidl_path "${PROJECT_SOURCE_DIR}/DataCacheTypes.fidl")
cmake_path(SET fidl_io_path "${PROJECT_SOURCE_DIR}/datacache_io.fidl")

list(APPEND dc_fidls_list
    ${fdepl_path}
    ${dc_fidl_path}
    ${dc_types_fidl_path}
)

list(APPEND dc_files_list
    ${PROJECT_SOURCE_DIR}/datacache.c
    ${PROJECT_SOURCE_DIR}/datacache.h
)

list(APPEND fp_dc_io_list
    ${PROJECT_SOURCE_DIR}/fp/data_cache/v0.1/data_cache_server/FP_data_cacheProtocolServer.c
    ${PROJECT_SOURCE_DIR}/fp/data_cache/v0.1/data_cache_server/FP_data_cacheProtocolServer.h
    ${PROJECT_SOURCE_DIR}/fp/data_cache/v0.1/data_cache_server/FP_data_cacheProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/data_cache/v0.1/data_cache_server/FP_data_cacheServerApp.c
    ${PROJECT_SOURCE_DIR}/fp/data_cache/v0.1/data_cache_server/FP_data_cacheServerApp.h
)

list(APPEND datacache_sources
    ${dc_files_list}
)

add_library(${make_target} STATIC
    ${datacache_sources}
    ${fp_dc_io_list}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/fp"
)

# the following custom command is responsible to build the datacache sources and datacache_io.fidl;
# this is the first stage code generation
add_custom_command(
        OUTPUT ${dc_files_list} ${fidl_io_path}
        COMMAND ${DC_GEN_CMD} -dc ${fdepl_path} VERBATIM
        DEPENDS ${dc_fidls_list}
        COMMENT "DataCache generation..."
)

# the following custom command is responsible to build the source code for the datacache_io.fidl generated
# in the previous step
add_custom_command(
        OUTPUT ${fp_dc_io_list}
        COMMAND ${FP_GEN_CMD} -dc ${fdepl_io_path} -fmr ${PROJECT_SOURCE_DIR}/fp VERBATIM
        DEPENDS ${fidl_io_path} VERBATIM
        COMMENT "DataCache io generation..."
)

# Create a custom target that will always depend on the custom command
add_custom_target(
    run_datacache_gen
    DEPENDS ${dc_fidls_list}
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/data_cache/v0.1/data_cache_server/FP_data_cacheProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_data_cacheProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/data_cache/v0.1/data_cache_server/FP_data_cacheServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "data_cacheServerAppInit()\;"
)

add_dependencies(${make_target} run_datacache_gen)
add_dependencies(run_datacache_gen gen_bp_instance)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} timer)
