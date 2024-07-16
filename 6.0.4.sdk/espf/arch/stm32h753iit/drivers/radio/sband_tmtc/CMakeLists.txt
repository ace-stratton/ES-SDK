project(sband_tmtc C)
set(make_target "sband_tmtc")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fdepl_path "${PROJECT_SOURCE_DIR}/fp/config/deployment.fdepl")
cmake_path(SET fidl_path   "${FIDL_ROOT}/sband_tmtc/fp/S_Band_TMTC.fidl")

list(APPEND fidl_dependencies_list 
    ${fdepl_path}
    ${fidl_path}
)

list(APPEND fp_list
    ${PROJECT_SOURCE_DIR}/fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCProtocolClient.c
    ${PROJECT_SOURCE_DIR}/fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCClientApp.c
    ${PROJECT_SOURCE_DIR}/fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCProtocolClient.h
    ${PROJECT_SOURCE_DIR}/fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCClientApp.h
)

list(APPEND sband_tmtc_sources
        "src/sband_tmtc.c"
        ${fp_list}
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCProtocolClient.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_SBAND_TMTCProtocolClientInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/SBAND_TMTC/v1.1/SBAND_TMTC_client/FP_SBAND_TMTCClientApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "SBAND_TMTCClientAppInit()\;"
)

add_library(${make_target} STATIC 
    ${sband_tmtc_sources}
)

list(APPEND module_includes
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/inc"
)

FP_GEN_AT_PATH(fp_list ${fdepl_path} fidl_dependencies_list "${PROJECT_SOURCE_DIR}/fp")

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} assertions)