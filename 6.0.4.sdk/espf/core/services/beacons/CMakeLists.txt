project(beacons C)
set(make_target "beacons")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")

list(APPEND beacons_sources
    "src/beacons.c"
    "src/beacons_sm_config_user.c"
    "src/beacons_sm_config.c"
)

if (UHF_BEACONS_SINK_ENABLED)
    list(APPEND beacons_sources
         "src/beacons_sink_uhf.c"
    )
endif (UHF_BEACONS_SINK_ENABLED)

if (COMM_ESPS_ENABLED)
    #
    # Global declarations for "Beacons"
    #
    cmake_path(SET beacons_fdepl_path "${PROJECT_SOURCE_DIR}/config/Beacons.fdepl")
    cmake_path(SET beacons_fidl_path "${FIDL_ROOT_OBC}/Beacons.fidl")
    
    list(APPEND fp_beacons_src_list
        ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsProtocolServer.c
        ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsProtocolServer.h
        ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsProtocolTypes.h
        ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsServerApp.c
        ${PROJECT_SOURCE_DIR}/fp/Beacons/v0.1/Beacons_server/FP_BeaconsServerApp.h
    )
    
    set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
        "#include \"fp/Beacons/v0.1/Beacons_server/FP_BeaconsProtocolServer.h\""
    )
    
    set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
        "&FP_BeaconsProtocolServerInfo"
    )
    
    set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
        "#include \"fp/Beacons/v0.1/Beacons_server/FP_BeaconsServerApp.h\""
    )
    
    set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
        "BeaconsServerAppInit()\;"
    )

    FP_GEN_AT_PATH(fp_beacons_src_list ${beacons_fdepl_path} beacons_fidl_path ${fp_gen_path})

    list(APPEND beacons_sources
        ${fp_beacons_src_list}
    )
endif (COMM_ESPS_ENABLED)

add_library(${make_target} STATIC
    ${beacons_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} timer hsm datacache nvm assertions)
