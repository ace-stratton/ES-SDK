project(eps_i C)
set(make_target "eps_i")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fdepl_path  "${PROJECT_SOURCE_DIR}/fp/config/deployment.fdepl")
cmake_path(SET fidl_path   "${FIDL_ROOT}/eps_i/fp/EPS1.fidl")

list(APPEND fidl_dependencies_list
    ${fdepl_path}
    ${fidl_path}
)

list(APPEND fp_list
        ${PROJECT_SOURCE_DIR}/fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolClient.c
        ${PROJECT_SOURCE_DIR}/fp/EPS1/v0.1/EPS1_client/FP_EPS1ClientApp.c
        ${PROJECT_SOURCE_DIR}/fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolTypes.h
        ${PROJECT_SOURCE_DIR}/fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolClient.h
        ${PROJECT_SOURCE_DIR}/fp/EPS1/v0.1/EPS1_client/FP_EPS1ClientApp.h
)

list(APPEND eps_i_sources
        "src/eps_i.c"
        ${fp_list}
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolClient.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_EPS1ProtocolClientInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/EPS1/v0.1/EPS1_client/FP_EPS1ClientApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "EPS1ClientAppInit()\;"
)

add_library(${make_target} STATIC
        ${eps_i_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

FP_GEN_AT_PATH(fp_list ${fdepl_path} fidl_dependencies_list "${PROJECT_SOURCE_DIR}/fp")

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} espsi_common assertions)
