project(eps_ii C)
set(make_target "eps_ii")

include(${ROOT_BUILD_PATH}/espf.cmake)
include(${PROJECT_SOURCE_DIR}/gen_bp_inst.cmake)



cmake_path(SET fdepl_path  "${PROJECT_SOURCE_DIR}/fp/config/deployment.fdepl")
cmake_path(SET fidl_path   "${FIDL_ROOT}/eps_ii/fp/EPSII_BP_v1.fidl")
cmake_path(SET fidl_path_1 "${FIDL_ROOT}/eps_ii/fp/EPSII_PDM_v1.fidl")

list(APPEND fidl_dependencies_list
    ${fdepl_path}
    ${fidl_path}
    ${fidl_path_1}
)

list(APPEND fp_list
        ${PROJECT_SOURCE_DIR}/fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolClient.c
        ${PROJECT_SOURCE_DIR}/fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ClientApp.c
        ${PROJECT_SOURCE_DIR}/fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolTypes.h
        ${PROJECT_SOURCE_DIR}/fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolClient.h
        ${PROJECT_SOURCE_DIR}/fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ClientApp.h
        ${PROJECT_SOURCE_DIR}/fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolClient.c
        ${PROJECT_SOURCE_DIR}/fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ClientApp.c
        ${PROJECT_SOURCE_DIR}/fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolTypes.h
        ${PROJECT_SOURCE_DIR}/fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolClient.h
        ${PROJECT_SOURCE_DIR}/fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ClientApp.h
)

list(APPEND eps_ii_sources
        "src/eps_ii.c"
        "src/eps_ii_telemetry.c"
        "fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolClient.c"
        "fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ClientApp.c"
        "fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolClient.c"
        "fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ClientApp.c"       
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolClient.h\""
    "#include \"fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolClient.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_EPSII_BP_1ProtocolClientInfo"
    "&FP_EPSII_PDM_1ProtocolClientInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ClientApp.h\""
    "#include \"fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ClientApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "EPSII_BP_1ClientAppInit()\;"
    "EPSII_PDM_1ClientAppInit()\;"
)

add_library(${make_target} STATIC
        ${eps_ii_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

FP_GEN_AT_PATH(fp_list ${fdepl_path} fidl_dependencies_list "${PROJECT_SOURCE_DIR}/fp")

add_dependencies(${make_target} gen_bp_instance)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} datacache assertions)