project(telemetry C)
set(make_target "telemetry")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fdepl_path "${PROJECT_SOURCE_DIR}/fp/config/deployment.fdepl")
cmake_path(SET fidl_path "${FIDL_ROOT_OBC}/Telemetry.fidl")

list(APPEND fidl_dependencies_list
    ${fidl_path}
)

list(APPEND fp_list
        ${PROJECT_SOURCE_DIR}/fp/Telemetry/v0.1/Telemetry_server/FP_TelemetryProtocolServer.c
        ${PROJECT_SOURCE_DIR}/fp/Telemetry/v0.1/Telemetry_server/FP_TelemetryServerApp.c
        ${PROJECT_SOURCE_DIR}/fp/Telemetry/v0.1/Telemetry_server/FP_TelemetryProtocolTypes.h
        ${PROJECT_SOURCE_DIR}/fp/Telemetry/v0.1/Telemetry_server/FP_TelemetryProtocolServer.h
        ${PROJECT_SOURCE_DIR}/fp/Telemetry/v0.1/Telemetry_server/FP_TelemetryServerApp.h
)

FP_GEN_AT_PATH(fp_list ${fdepl_path} fidl_dependencies_list "${PROJECT_SOURCE_DIR}/fp")

list(APPEND telemetry_sources
    "src/telemetry.c"
    "src/telemetry_sm_config_user.c"
    "src/telemetry_sm_config.c"
    "src/telemetry_file_sink_sm_config_user.c"
    "src/telemetry_file_sink_sm_config.c"
    "src/telemetry_queue.c"
    "src/telemetry_file_sink.c"
    ${fp_list}
)

add_library(${make_target} STATIC
    ${telemetry_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/src"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/Telemetry/v0.1/Telemetry_server/FP_TelemetryProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_TelemetryProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/Telemetry/v0.1/Telemetry_server/FP_TelemetryServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "TelemetryServerAppInit()\;"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} timer hsm datetime COBS datacache nvm crc fatfs assertions)
