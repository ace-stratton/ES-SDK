project(sys_time C)
set(make_target "sys_time")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fdepl_path "${PROJECT_SOURCE_DIR}/fp/config/deployment.fdepl")
cmake_path(SET fidl_path "${FIDL_ROOT_OBC}/time.fidl")

list(APPEND fidl_dependencies_list
    ${fidl_path}
)

list(APPEND fp_list
    ${PROJECT_SOURCE_DIR}/fp/time/v0.1/time_server/FP_timeProtocolServer.c
    ${PROJECT_SOURCE_DIR}/fp/time/v0.1/time_server/FP_timeServerApp.c
    ${PROJECT_SOURCE_DIR}/fp/time/v0.1/time_server/FP_timeProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/time/v0.1/time_server/FP_timeProtocolServer.h
    ${PROJECT_SOURCE_DIR}/fp/time/v0.1/time_server/FP_timeServerApp.h
)

FP_GEN_AT_PATH(fp_list ${fdepl_path} fidl_dependencies_list "${PROJECT_SOURCE_DIR}/fp")

list(APPEND module_sources 
	"src/sys_time.c"
    ${fp_list}
)

add_library(${make_target} STATIC
    ${module_sources}
)

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/time/v0.1/time_server/FP_timeProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_timeProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/time/v0.1/time_server/FP_timeServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "timeServerAppInit()\;"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} nvm datetime assertions)
