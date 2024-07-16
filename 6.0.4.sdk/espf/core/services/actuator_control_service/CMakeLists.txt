project(actuator_control_service C)
set(make_target "actuator_control_service")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")
cmake_path(SET obc_actuator_control_service_fdepl_path "${PROJECT_SOURCE_DIR}/config/OBC_ACTUATOR_CONTROL_SERVICE.fdepl")
cmake_path(SET obc_actuator_control_service_fidl_path "${FIDL_ROOT_OBC}/OBC_ACTUATOR_CONTROL_SERVICE.fidl")

list(APPEND fp_obc_actuator_control_service_src_list
	${PROJECT_SOURCE_DIR}/fp/OBC_ACTUATOR_CONTROL_SERVICE/v3.0/OBC_ACTUATOR_CONTROL_SERVICE_server/FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/OBC_ACTUATOR_CONTROL_SERVICE/v3.0/OBC_ACTUATOR_CONTROL_SERVICE_server/FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/OBC_ACTUATOR_CONTROL_SERVICE/v3.0/OBC_ACTUATOR_CONTROL_SERVICE_server/FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/OBC_ACTUATOR_CONTROL_SERVICE/v3.0/OBC_ACTUATOR_CONTROL_SERVICE_server/FP_OBC_ACTUATOR_CONTROL_SERVICEServerApp.c
	${PROJECT_SOURCE_DIR}/fp/OBC_ACTUATOR_CONTROL_SERVICE/v3.0/OBC_ACTUATOR_CONTROL_SERVICE_server/FP_OBC_ACTUATOR_CONTROL_SERVICEServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
	"#include \"fp/OBC_ACTUATOR_CONTROL_SERVICE/v3.0/OBC_ACTUATOR_CONTROL_SERVICE_server/FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
	"&FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
	"#include \"fp/OBC_ACTUATOR_CONTROL_SERVICE/v3.0/OBC_ACTUATOR_CONTROL_SERVICE_server/FP_OBC_ACTUATOR_CONTROL_SERVICEServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
	"OBC_ACTUATOR_CONTROL_SERVICEServerAppInit()\;"
)

list(APPEND actuator_control_service_sources
	${fp_obc_actuator_control_service_src_list}
)

FP_GEN_AT_PATH(fp_obc_actuator_control_service_src_list ${obc_actuator_control_service_fdepl_path} obc_actuator_control_service_fidl_path ${fp_gen_path})

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}"
    )
    
list (APPEND actuator_control_service_sources
    "src/actuator_control_service.c"
    )

add_library(${make_target} STATIC
    ${actuator_control_service_sources}
)

list(APPEND actuator_control_service_libs
    nvm
    assertions
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} ${actuator_control_service_libs})