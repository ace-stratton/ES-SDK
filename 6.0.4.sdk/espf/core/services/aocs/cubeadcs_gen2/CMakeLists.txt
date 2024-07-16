project(cubeadcs_gen2_service C)
set(make_target "cubeadcs_gen2_service")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")
cmake_path(SET obc_cubeadcs_gen2_fdepl_path "${PROJECT_SOURCE_DIR}/config/OBC_CUBEADCS_GEN2.fdepl")
cmake_path(SET obc_cubeadcs_gen2_fidl_path "${FIDL_ROOT_OBC}/OBC_CUBEADCS_GEN2.fidl")
list(APPEND fp_obc_cubeadcs_gen2_src_list
    ${PROJECT_SOURCE_DIR}/fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ProtocolServer.c
    ${PROJECT_SOURCE_DIR}/fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ProtocolServer.h
    ${PROJECT_SOURCE_DIR}/fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ServerApp.c
    ${PROJECT_SOURCE_DIR}/fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ServerApp.h
)


set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_OBC_CUBEADCS_GEN2ProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/OBC_CUBEADCS_GEN2/v1.0/OBC_CUBEADCS_GEN2_server/FP_OBC_CUBEADCS_GEN2ServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "OBC_CUBEADCS_GEN2ServerAppInit()\;"
)

list(APPEND cubeadcs_gen2_service_sources
    ${fp_obc_cubeadcs_gen2_src_list}
)

FP_GEN_AT_PATH(fp_obc_cubeadcs_gen2_src_list ${obc_cubeadcs_gen2_fdepl_path} obc_cubeadcs_gen2_fidl_path ${fp_gen_path})


list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/gen"
    "${PROJECT_SOURCE_DIR}/cfg"
    "${PROJECT_ROOT}/core/middlewares/external/libcubeobc/api/src"
    "${PROJECT_ROOT}/core/middlewares/external/libcubeobc/include"
)

list (APPEND cubeadcs_gen2_service_sources
	"src/cubeadcs_gen2.c"
    "src/cubeadcs_gen2_gw.c"
	"src/cubeadcs_gen2_events.c"
	"gen/cubeadcs_gen2_sm_config_user.c"
	"gen/cubeadcs_gen2_sm_config.c"
	"src/cubeadcs_gen2_fdir.c"
    "src/cubeadcs_gen2_sys_states.c"
    "src/cubeadcs_gen2_transfer.c"
    "src/cubeadcs_gen2_tlm.c"
)

add_library(${make_target} STATIC
    ${cubeadcs_gen2_service_sources}
)

list(APPEND cubeadcs_gen2_libs
    cubeobc
    fatfs
    nvm
    assertions
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} ${cubeadcs_gen2_libs})
