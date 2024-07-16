project(es_adcs C)
set(make_target "es_adcs")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")
cmake_path(SET obc_es_adcs_fdepl_path "${PROJECT_SOURCE_DIR}/config/OBC_ES_ADCS.fdepl")
cmake_path(SET obc_es_adcs_fidl_path "${FIDL_ROOT_OBC}/OBC_ES_ADCS.fidl")

list(APPEND fp_obc_es_adcs_src_list
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_ADCS/v3.0/OBC_ES_ADCS_server/FP_OBC_ES_ADCSProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_ADCS/v3.0/OBC_ES_ADCS_server/FP_OBC_ES_ADCSProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_ADCS/v3.0/OBC_ES_ADCS_server/FP_OBC_ES_ADCSProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_ADCS/v3.0/OBC_ES_ADCS_server/FP_OBC_ES_ADCSServerApp.c
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_ADCS/v3.0/OBC_ES_ADCS_server/FP_OBC_ES_ADCSServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
	"#include \"fp/OBC_ES_ADCS/v3.0/OBC_ES_ADCS_server/FP_OBC_ES_ADCSProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
	"&FP_OBC_ES_ADCSProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
	"#include \"fp/OBC_ES_ADCS/v3.0/OBC_ES_ADCS_server/FP_OBC_ES_ADCSServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
	"OBC_ES_ADCSServerAppInit()\;"
)

list(APPEND es_adcs_sources
	${fp_obc_es_adcs_src_list}
)

FP_GEN_AT_PATH(fp_obc_es_adcs_src_list ${obc_es_adcs_fdepl_path} obc_es_adcs_fidl_path ${fp_gen_path})

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/gen_sm"
	"${PROJECT_SOURCE_DIR}/fp"
	"${PROJECT_SOURCE_DIR}"
)

list(APPEND es_adcs_sources
			"src/es_adcs.c"
			"src/es_adcs_math.c"
			"src/es_adcs_estimators.c"
			"src/es_adcs_controllers.c"
			"gen_sm/es_adcs_op_modes_sm_config_user.c"
			"gen_sm/es_adcs_op_modes_sm_config.c"
)

add_library(${make_target} STATIC
        ${es_adcs_sources}
)

list(APPEND es_adcs_libs
    SGP4
    datacache
    nvm
    assertions
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} ${es_adcs_libs})