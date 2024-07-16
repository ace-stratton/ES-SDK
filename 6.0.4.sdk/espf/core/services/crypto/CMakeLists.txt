project(crypto C)
set(make_target "crypto")

include(${ROOT_BUILD_PATH}/espf.cmake)
cmake_path(SET fp_gen_path "${PROJECT_SOURCE_DIR}/fp")

cmake_path(SET crypto_fdepl_path "${PROJECT_SOURCE_DIR}/fp/config/crypto.fdepl")
cmake_path(SET crypto_fidl_path "${FIDL_ROOT_OBC}/crypto.fidl")

list(APPEND fp_crypto_src_list
        ${PROJECT_SOURCE_DIR}/fp/crypto/v0.1/crypto_server/FP_cryptoProtocolServer.c
        ${PROJECT_SOURCE_DIR}/fp/crypto/v0.1/crypto_server/FP_cryptoProtocolServer.h
        ${PROJECT_SOURCE_DIR}/fp/crypto/v0.1/crypto_server/FP_cryptoProtocolTypes.h
        ${PROJECT_SOURCE_DIR}/fp/crypto/v0.1/crypto_server/FP_cryptoServerApp.c
        ${PROJECT_SOURCE_DIR}/fp/crypto/v0.1/crypto_server/FP_cryptoServerApp.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \"fp/crypto/v0.1/crypto_server/FP_cryptoProtocolServer.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_cryptoProtocolServerInfo"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \"fp/crypto/v0.1/crypto_server/FP_cryptoServerApp.h\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "cryptoServerAppInit()\;"
)


list(APPEND espsi_fp_sources
    ${fp_crypto_src_list}
)

FP_GEN_AT_PATH(fp_crypto_src_list ${crypto_fdepl_path} crypto_fidl_path ${fp_gen_path})

list(APPEND crypto_sources
    "src/crypto.c"
    ${fp_crypto_src_list}
)

add_library(${make_target} STATIC
    ${crypto_sources}
)

list(
    APPEND module_includes
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

target_include_directories(${make_target} PUBLIC ${module_includes} PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} fatfs libcsq_algo stm32_crypto rng timer nvm assertions)
