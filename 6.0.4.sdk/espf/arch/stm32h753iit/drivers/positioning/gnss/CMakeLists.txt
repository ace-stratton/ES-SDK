project(gnss C)
set(make_target "gnss")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")
cmake_path(SET fdepl_path "${PROJECT_SOURCE_DIR}/fp/config/deployment.fdepl")
cmake_path(SET fidl_path "${FIDL_ROOT_OBC}/gnss.fidl")

list(APPEND fidl_dependencies_list
    ${fdepl_path}
    ${fidl_path}
)

list(APPEND fp_list
    ${PROJECT_SOURCE_DIR}/fp/gnss/v1.0/gnss_server/FP_gnssProtocolServer.c
    ${PROJECT_SOURCE_DIR}/fp/gnss/v1.0/gnss_server/FP_gnssServerApp.c
    ${PROJECT_SOURCE_DIR}/fp/gnss/v1.0/gnss_server/FP_gnssProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/gnss/v1.0/gnss_server/FP_gnssProtocolServer.h
    ${PROJECT_SOURCE_DIR}/fp/gnss/v1.0/gnss_server/FP_gnssServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/gnss/v1.0/gnss_server/FP_gnssProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_gnssProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/gnss/v1.0/gnss_server/FP_gnssServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "gnssServerAppInit()\;"
)

FP_GEN_AT_PATH(fp_list ${fdepl_path} fidl_dependencies_list ${fp_gen_path})

add_library(${make_target} STATIC
	"src/gnss.c"
    "src/gnss_resp.c"
    "src/gnss_uart.c"
    "src/gnss_power.c"
    ${fp_list}
)

list(APPEND module_includes
    "${PROJECT_SOURCE_DIR}/"
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PRIVATE ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PRIVATE libtrace assertions)
