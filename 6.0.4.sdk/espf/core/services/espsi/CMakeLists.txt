project(espsi_fp C)
set(make_target "espsi_fp")

include(${ROOT_BUILD_PATH}/espf.cmake)

cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")

#
# Global declarations for "MacServices"
#
cmake_path(SET macservices_fdepl_path "${PROJECT_SOURCE_DIR}/config/MacServices.fdepl")
cmake_path(SET macservices_fidl_path "${FIDL_ROOT}/common/fp/MacServices.fidl")

list(APPEND fp_macservices_src_list
	${PROJECT_SOURCE_DIR}/fp/MacServices/v0.1/MacServices_server/FP_MacServicesProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/MacServices/v0.1/MacServices_server/FP_MacServicesProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/MacServices/v0.1/MacServices_server/FP_MacServicesProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/MacServices/v0.1/MacServices_server/FP_MacServicesServerApp.c
	${PROJECT_SOURCE_DIR}/fp/MacServices/v0.1/MacServices_server/FP_MacServicesServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/MacServices/v0.1/MacServices_server/FP_MacServicesProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_MacServicesProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/MacServices/v0.1/MacServices_server/FP_MacServicesServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "MacServicesServerAppInit()\;"
)

#
# Global declarations for "ModuleId"
#
cmake_path(SET moduleid_fdepl_path "${PROJECT_SOURCE_DIR}/config/ModuleId.fdepl")
cmake_path(SET moduleid_fidl_path "${FIDL_ROOT}/common/fp/ModuleId.fidl")

list(APPEND fp_moduleid_src_list
	${PROJECT_SOURCE_DIR}/fp/ModuleId/v0.1/ModuleId_server/FP_ModuleIdProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/ModuleId/v0.1/ModuleId_server/FP_ModuleIdProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/ModuleId/v0.1/ModuleId_server/FP_ModuleIdProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/ModuleId/v0.1/ModuleId_server/FP_ModuleIdServerApp.c
	${PROJECT_SOURCE_DIR}/fp/ModuleId/v0.1/ModuleId_server/FP_ModuleIdServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/ModuleId/v0.1/ModuleId_server/FP_ModuleIdProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_ModuleIdProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/ModuleId/v0.1/ModuleId_server/FP_ModuleIdServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "ModuleIdServerAppInit()\;"
)

#
# Global declarations for "ConOps"
#
cmake_path(SET conops_fdepl_path "${PROJECT_SOURCE_DIR}/config/ConOps.fdepl")
cmake_path(SET conops_fidl_path "${FIDL_ROOT_OBC}/ConOps.fidl")

list(APPEND fp_conops_src_list
	${PROJECT_SOURCE_DIR}/fp/ConOps/v0.2/ConOps_server/FP_ConOpsProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/ConOps/v0.2/ConOps_server/FP_ConOpsProtocolServer.h
	# ${PROJECT_SOURCE_DIR}/fp/ConOps/v0.2/ConOps_server/FP_ConOpsProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/ConOps/v0.2/ConOps_server/FP_ConOpsServerApp.c
	${PROJECT_SOURCE_DIR}/fp/ConOps/v0.2/ConOps_server/FP_ConOpsServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/ConOps/v0.2/ConOps_server/FP_ConOpsProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_ConOpsProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/ConOps/v0.2/ConOps_server/FP_ConOpsServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "ConOpsServerAppInit()\;"
)

#
# Global declarations for "FileManager"
#
cmake_path(SET filemanager_fdepl_path "${PROJECT_SOURCE_DIR}/config/FileManager.fdepl")
cmake_path(SET filemanager_fidl_path "${FIDL_ROOT_OBC}/FileManager.fidl")

list(APPEND fp_filemanager_src_list
	${PROJECT_SOURCE_DIR}/fp/FileManager/v1.2/FileManager_server/FP_FileManagerProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/FileManager/v1.2/FileManager_server/FP_FileManagerProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/FileManager/v1.2/FileManager_server/FP_FileManagerProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/FileManager/v1.2/FileManager_server/FP_FileManagerServerApp.c
	${PROJECT_SOURCE_DIR}/fp/FileManager/v1.2/FileManager_server/FP_FileManagerServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/FileManager/v1.2/FileManager_server/FP_FileManagerProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_FileManagerProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/FileManager/v1.2/FileManager_server/FP_FileManagerServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "FileManagerServerAppInit()\;"
)

#
# Global declarations for "nvm"
#
cmake_path(SET nvm_fdepl_path "${PROJECT_SOURCE_DIR}/config/nvm.fdepl")
cmake_path(SET nvm_fidl_path "${FIDL_ROOT_OBC}/nvm.fidl")

list(APPEND fp_nvm_src_list
	${PROJECT_SOURCE_DIR}/fp/nvm/v0.1/nvm_server/FP_nvmProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/nvm/v0.1/nvm_server/FP_nvmProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/nvm/v0.1/nvm_server/FP_nvmProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/nvm/v0.1/nvm_server/FP_nvmServerApp.c
	${PROJECT_SOURCE_DIR}/fp/nvm/v0.1/nvm_server/FP_nvmServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/nvm/v0.1/nvm_server/FP_nvmProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_nvmProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/nvm/v0.1/nvm_server/FP_nvmServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "nvmServerAppInit()\;"
)

#
# Global declarations for "OBC"
#
cmake_path(SET obc_fdepl_path "${PROJECT_SOURCE_DIR}/config/OBC.fdepl")
cmake_path(SET obc_fidl_path "${FIDL_ROOT_OBC}/OBC.fidl")

list(APPEND fp_obc_src_list
	${PROJECT_SOURCE_DIR}/fp/OBC/v3.4/OBC_server/FP_OBCProtocolServer.c
	${PROJECT_SOURCE_DIR}/fp/OBC/v3.4/OBC_server/FP_OBCProtocolServer.h
	${PROJECT_SOURCE_DIR}/fp/OBC/v3.4/OBC_server/FP_OBCProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/OBC/v3.4/OBC_server/FP_OBCServerApp.c
	${PROJECT_SOURCE_DIR}/fp/OBC/v3.4/OBC_server/FP_OBCServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/OBC/v3.4/OBC_server/FP_OBCProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_OBCProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/OBC/v3.4/OBC_server/FP_OBCServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "OBCServerAppInit()\;"
)

#
# Global declarations for "UHF"
#
cmake_path(SET uhf_fdepl_path "${PROJECT_SOURCE_DIR}/config/UHF.fdepl")
cmake_path(SET uhf_fidl_path "${FIDL_ROOT}/uhf/fp/UHF2.fidl")

list(APPEND fp_uhf_src_list
	${PROJECT_SOURCE_DIR}/fp/UHF/v0.4/UHF_client/FP_UHFProtocolClient.c
	${PROJECT_SOURCE_DIR}/fp/UHF/v0.4/UHF_client/FP_UHFProtocolClient.h
	${PROJECT_SOURCE_DIR}/fp/UHF/v0.4/UHF_client/FP_UHFProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/UHF/v0.4/UHF_client/FP_UHFClientApp.c
	${PROJECT_SOURCE_DIR}/fp/UHF/v0.4/UHF_client/FP_UHFClientApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/UHF/v0.4/UHF_client/FP_UHFProtocolClient.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_UHFProtocolClientInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/UHF/v0.4/UHF_client/FP_UHFClientApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "UHFClientAppInit()\;"
)

list(APPEND espsi_fp_sources
    ${fp_macservices_src_list}
    ${fp_moduleid_src_list}
    ${fp_conops_src_list}
    ${fp_filemanager_src_list}
    ${fp_nvm_src_list}
    ${fp_obc_src_list}
    ${fp_uhf_src_list}
)

FP_GEN_AT_PATH(fp_macservices_src_list ${macservices_fdepl_path} macservices_fidl_path ${fp_gen_path})
FP_GEN_AT_PATH(fp_moduleid_src_list ${moduleid_fdepl_path} moduleid_fidl_path ${fp_gen_path})
FP_GEN_AT_PATH(fp_conops_src_list ${conops_fdepl_path} conops_fidl_path ${fp_gen_path})
FP_GEN_AT_PATH(fp_filemanager_src_list ${filemanager_fdepl_path} filemanager_fidl_path ${fp_gen_path})
FP_GEN_AT_PATH(fp_nvm_src_list ${nvm_fdepl_path} nvm_fidl_path ${fp_gen_path})
FP_GEN_AT_PATH(fp_obc_src_list ${obc_fdepl_path} obc_fidl_path ${fp_gen_path})
FP_GEN_AT_PATH(fp_uhf_src_list ${uhf_fdepl_path} uhf_fidl_path ${fp_gen_path})

add_library(${make_target} STATIC
    ${espsi_fp_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} eps_i nvm fatfs)
