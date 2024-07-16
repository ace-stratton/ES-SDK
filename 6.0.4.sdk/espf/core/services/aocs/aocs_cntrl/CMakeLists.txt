project(aocs_cntrl_service C)
set(make_target "aocs_cntrl_service")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")
cmake_path(SET obc_aocs_cntrl_fdepl_path "${PROJECT_SOURCE_DIR}/config/OBC_AOCS_CNTRL.fdepl")
cmake_path(SET obc_aocs_cntrl_fidl_path "${FIDL_ROOT_OBC}/OBC_AOCS_CNTRL.fidl")

list(APPEND fp_obc_aocs_cntrl_src_list
	${PROJECT_SOURCE_DIR}/fp/OBC_AOCS_CNTRL/v1.0/OBC_AOCS_CNTRL_server/FP_OBC_AOCS_CNTRLProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/OBC_AOCS_CNTRL/v1.0/OBC_AOCS_CNTRL_server/FP_OBC_AOCS_CNTRLSProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/OBC_AOCS_CNTRL/v1.0/OBC_AOCS_CNTRL_server/FP_OBC_AOCS_CNTRLProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/OBC_AOCS_CNTRL/v1.0/OBC_AOCS_CNTRL_server/FP_OBC_AOCS_CNTRLServerApp.c
	${PROJECT_SOURCE_DIR}/fp/OBC_AOCS_CNTRL/v1.0/OBC_AOCS_CNTRL_server/FP_OBC_AOCS_CNTRLServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
	"#include \"fp/OBC_AOCS_CNTRL/v1.0/OBC_AOCS_CNTRL_server/FP_OBC_AOCS_CNTRLProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
	"&FP_OBC_AOCS_CNTRLProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
	"#include \"fp/OBC_AOCS_CNTRL/v1.0/OBC_AOCS_CNTRL_server/FP_OBC_AOCS_CNTRLServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
	"OBC_AOCS_CNTRLServerAppInit()\;"
)

list(APPEND aocs_cntrl_sources
	${fp_obc_aocs_cntrl_src_list}
)

FP_GEN_AT_PATH(fp_obc_aocs_cntrl_src_list ${obc_aocs_cntrl_fdepl_path} obc_aocs_cntrl_fidl_path ${fp_gen_path})

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/fp"
)

list (APPEND aocs_cntrl_sources
	"src/aocs_cntrl.c"
	"src/aocs_pm.c"
	"src/aocs_cntrl_feedback.c"
)

add_library(${make_target} STATIC
    ${aocs_cntrl_sources}
)

list(APPEND aocs_libs
	fatfs
    cubeadcs
    es_adcs
    assertions
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} ${aocs_libs})
