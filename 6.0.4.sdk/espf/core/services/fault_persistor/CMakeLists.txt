project(fault_persistor C)
set(make_target "fault_persistor")

include(${ROOT_BUILD_PATH}/espf.cmake)
cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")

cmake_path(SET fault_ops_fdepl_path "${PROJECT_SOURCE_DIR}/fp/config/fault_ops.fdepl")
cmake_path(SET fault_ops_fidl_path "${FIDL_ROOT_OBC}/fault_ops.fidl")

list(APPEND fp_fault_ops_src_list
        ${PROJECT_SOURCE_DIR}/fp/fault_ops/v0.1/fault_ops_server/FP_fault_opsProtocolServer.c
        ${PROJECT_SOURCE_DIR}/fp/fault_ops/v0.1/fault_ops_server/FP_fault_opsProtocolServer.h
        ${PROJECT_SOURCE_DIR}/fp/fault_ops/v0.1/fault_ops_server/FP_fault_opsProtocolTypes.h
        ${PROJECT_SOURCE_DIR}/fp/fault_ops/v0.1/fault_ops_server/FP_fault_opsServerApp.c
        ${PROJECT_SOURCE_DIR}/fp/fault_ops/v0.1/fault_ops_server/FP_fault_opsServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/fault_ops/v0.1/fault_ops_server/FP_fault_opsProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_fault_opsProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/fault_ops/v0.1/fault_ops_server/FP_fault_opsServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "fault_opsServerAppInit()\;"
)

FP_GEN_AT_PATH(fp_fault_ops_src_list ${fault_ops_fdepl_path} fault_ops_fidl_path ${fp_gen_path})

list(APPEND module_sources
    "src/fault_persistor.c"
    "inc/fault_persistor.h"
    ${fp_fault_ops_src_list}
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
target_link_libraries(${make_target} arm_fault_handler nvm assertions)
