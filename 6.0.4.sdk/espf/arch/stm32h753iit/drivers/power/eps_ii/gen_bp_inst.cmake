cmake_path(SET EPS_BP_INSTANCE_GEN_PY "${PROJECT_SOURCE_DIR}/gen_bp_instances.py")
cmake_path(SET EPS_II_TELEMETRY_CFG_HDR_FILE "${PROJECT_SOURCE_DIR}/inc/eps_ii_telemetry_cfg.h")
cmake_path(SET NVM_BP_FIDL_FILE "${PROJECT_ROOT}/config/nvm/fp/config/nvm_bp.fidl")
cmake_path(SET EPS_CONFIG_HDR_FILE "${PROJECT_ROOT}/config/eps_ii/eps_ii_config.h")

# Extract the source directory of the datacache library target
get_target_property(DATACACHE_DIR datacache SOURCE_DIR)

list(APPEND generated_files_src_list
    ${EPS_II_TELEMETRY_CFG_HDR_FILE}
    ${NVM_BP_FIDL_FILE}
    ${EPS_CONFIG_HDR_FILE}
)

# This variable is used where we need to execute the eps bp instance generation tool
set(EPS_BP_INSTANCE_GENERATOR_CMD ${PY} ${EPS_BP_INSTANCE_GEN_PY} ${EPS_BP_COUNT} ${DATACACHE_DIR} ${EPS_II_TELEMETRY_CFG_HDR_FILE} ${NVM_BP_FIDL_FILE} )

# Custom command to run the eps battery pack instance generator if there are changes
add_custom_command(
    OUTPUT ${generated_files_src_list}
    COMMAND ${EPS_BP_INSTANCE_GENERATOR_CMD}           # Execute the generation script
    DEPENDS ${EPS_BP_INSTANCE_GEN_PY}                  # Depend on the python script itself
    COMMENT "EPS Battery Pack configuration changed. Running script for generation..."
)

# Create a custom target that will always depend on the custom command
add_custom_target(
    gen_bp_instance
    DEPENDS ${generated_files_src_list}
)
