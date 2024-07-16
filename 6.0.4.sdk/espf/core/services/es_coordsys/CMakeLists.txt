project(es_coordsys C)
set(make_target "es_coordsys")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")
cmake_path(SET obc_es_coordsys_fdepl_path "${PROJECT_SOURCE_DIR}/config/OBC_ES_COORDSYS.fdepl")
cmake_path(SET obc_es_coordsys_fidl_path "${FIDL_ROOT_OBC}/OBC_ES_COORDSYS.fidl")

list(APPEND fp_obc_es_coordsys_src_list
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_COORDSYS/v3.0/OBC_ES_COORDSYS_server/FP_OBC_ES_COORDSYSProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_COORDSYS/v3.0/OBC_ES_COORDSYS_server/FP_OBC_ES_COORDSYSProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_COORDSYS/v3.0/OBC_ES_COORDSYS_server/FP_OBC_ES_COORDSYSProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_COORDSYS/v3.0/OBC_ES_COORDSYS_server/FP_OBC_ES_COORDSYSServerApp.c
	${PROJECT_SOURCE_DIR}/fp/OBC_ES_COORDSYS/v3.0/OBC_ES_COORDSYS_server/FP_OBC_ES_COORDSYSServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
	"#include \"fp/OBC_ES_COORDSYS/v3.0/OBC_ES_COORDSYS_server/FP_OBC_ES_COORDSYSProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
	"&FP_OBC_ES_COORDSYSProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
	"#include \"fp/OBC_ES_COORDSYS/v3.0/OBC_ES_COORDSYS_server/FP_OBC_ES_COORDSYSServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
	"OBC_ES_COORDSYSServerAppInit()\;"
)

list(APPEND es_coordsys_sources
	${fp_obc_es_coordsys_src_list}
)

FP_GEN_AT_PATH(fp_obc_es_coordsys_src_list ${obc_es_coordsys_fdepl_path} obc_es_coordsys_fidl_path ${fp_gen_path})

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}"
    )
    
list (APPEND es_coordsys_sources
    "src/es_coordsys.c"
    )

add_library(${make_target} STATIC
    ${es_coordsys_sources}
)

list(APPEND es_coordsys_libs
    nvm
    assertions
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} ${es_coordsys_libs})