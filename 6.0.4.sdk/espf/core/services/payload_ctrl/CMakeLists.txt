project(payload_ctrl C)
set(make_target "payload_ctrl")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")

#
# Global declarations for "Payload_Control"
#
cmake_path(SET payload_control_fdepl_path "${PROJECT_SOURCE_DIR}/config/Payload_Control.fdepl")
cmake_path(SET payload_control_fidl_path "${FIDL_ROOT_OBC}/Payload_Control.fidl")

list(APPEND fp_payload_control_src_list
    ${PROJECT_SOURCE_DIR}/fp/Payload_Control/v0.1/Payload_Control_server/FP_Payload_ControlProtocolServer.c
    ${PROJECT_SOURCE_DIR}/fp/Payload_Control/v0.1/Payload_Control_server/FP_Payload_ControlProtocolServer.h
    ${PROJECT_SOURCE_DIR}/fp/Payload_Control/v0.1/Payload_Control_server/FP_Payload_ControlProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/Payload_Control/v0.1/Payload_Control_server/FP_Payload_ControlServerApp.c
    ${PROJECT_SOURCE_DIR}/fp/Payload_Control/v0.1/Payload_Control_server/FP_Payload_ControlServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/Payload_Control/v0.1/Payload_Control_server/FP_Payload_ControlProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_Payload_ControlProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/Payload_Control/v0.1/Payload_Control_server/FP_Payload_ControlServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "Payload_ControlServerAppInit()\;"
)

FP_GEN_AT_PATH(fp_payload_control_src_list ${payload_control_fdepl_path} payload_control_fidl_path ${fp_gen_path})

add_library(${make_target} STATIC
    "src/payload_cfg.c"
    "src/payload_ctrl_sm_config_user.c"
    "src/payload_ctrl_sm_config.c"
    "src/payload_ctrl.c"
    "src/payload_dummy.c"
    ${fp_payload_control_src_list}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/src"
)

list(APPEND pl_ctrl_libs
    timer
    hsm
    assertions
)

list(APPEND pl_ctrl_libs
    aocs_cntrl_service
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} ${pl_ctrl_libs})
