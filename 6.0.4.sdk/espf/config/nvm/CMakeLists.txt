project(nvm_cfg C)
set(make_target "nvm_cfg")

cmake_path(SET fdepl_nvm_bp_path "${PROJECT_SOURCE_DIR}/fp/config/nvm_bp.fdepl")
cmake_path(SET nvm_bp_fidl_path "${PROJECT_SOURCE_DIR}/fp/config/nvm_bp.fidl")

list(APPEND fidl_dependencies_list
    ${nvm_bp_fidl_path}
)

list(APPEND fp_nvm_bp_list
    ${PROJECT_SOURCE_DIR}/fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpProtocolServer.c
    ${PROJECT_SOURCE_DIR}/fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpProtocolServer.h
    ${PROJECT_SOURCE_DIR}/fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpServerApp.c
    ${PROJECT_SOURCE_DIR}/fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpServerApp.h
)

FP_GEN_AT_PATH(fp_nvm_bp_list ${fdepl_nvm_bp_path} fidl_dependencies_list "${PROJECT_SOURCE_DIR}/fp")

add_library(${make_target} STATIC
    "${PROJECT_SOURCE_DIR}/src/nvm_cfg.c"
    ${fp_nvm_bp_list}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/../nvm_appcfg/inc"
    "${PROJECT_SOURCE_DIR}/../nvm_bootcfg/inc"
    "${PROJECT_ROOT}/core/services/nvm/inc"
    "${PROJECT_SOURCE_DIR}/fp"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_nvm_bpProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "nvm_bpServerAppInit()\;"
)


target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PUBLIC sys_time cubeobc)
