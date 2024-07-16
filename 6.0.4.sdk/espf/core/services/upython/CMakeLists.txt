project(upython C)


list( 
    APPEND module_sources
    ${PROJECT_SOURCE_DIR}/src/upy.c
    ${PROJECT_SOURCE_DIR}/src/upy_fp_gw.c  
    ${PROJECT_SOURCE_DIR}/src/upy_scr_mgr.c
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/fp/obc_micropython/v1.1/obc_micropython_server"
)

#remove -pedantic compiler option for micropython, there are too many warnings from the implementation of micropython itself.
list(APPEND module_compile_options ${ROOT_COMPILE_OPTIONS})
list(REMOVE_ITEM module_compile_options "-pedantic")

#
# Global declarations for "obc_micropython"
#
cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")
cmake_path(SET obc_micropython_fdepl_path "${PROJECT_SOURCE_DIR}/config/obc_micropython.fdepl")
cmake_path(SET obc_micropython_fidl_path "${FIDL_ROOT_OBC}/obc_micropython.fidl")


list(APPEND fp_obc_es_micropython_list
    ${PROJECT_SOURCE_DIR}/fp/obc_micropython/v1.1/obc_micropython_server/FP_obc_micropythonProtocolServer.c
    ${PROJECT_SOURCE_DIR}/fp/obc_micropython/v1.1/obc_micropython_server/FP_obc_micropythonProtocolServer.h
    ${PROJECT_SOURCE_DIR}/fp/obc_micropython/v1.1/obc_micropython_server/FP_obc_micropythonProtocolTypes.h
    ${PROJECT_SOURCE_DIR}/fp/obc_micropython/v1.1/obc_micropython_server/FP_obc_micropythonServerApp.c
    ${PROJECT_SOURCE_DIR}/fp/obc_micropython/v1.1/obc_micropython_server/FP_obc_micropythonServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/obc_micropython/v1.1/obc_micropython_server/FP_obc_micropythonProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_obc_micropythonProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/obc_micropython/v1.1/obc_micropython_server/FP_obc_micropythonServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "obc_micropythonServerAppInit()\;"
)

FP_GEN_AT_PATH(fp_obc_es_micropython_list ${obc_micropython_fdepl_path} obc_micropython_fidl_path ${fp_gen_path})



add_library(upython STATIC 
                 ${module_sources}
                 ${fp_obc_es_micropython_list}
)
set_property(TARGET upython PROPERTY COMPILE_OPTIONS ${module_compile_options})

target_include_directories(upython PRIVATE ${ROOT_INCLUDES} PUBLIC ${module_includes})
target_compile_definitions(upython PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(upython PRIVATE ${module_compile_options})
target_link_options(upython PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(upython ESPSI fatfs micropython sys_time timer)
