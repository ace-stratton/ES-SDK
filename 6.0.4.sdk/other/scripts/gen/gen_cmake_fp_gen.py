from jinja2 import Template

template = """
{%      for fidl_name, fidl_config_entry in config.items() %}
#
# Global declarations for "{{fidl_name}}"
#
cmake_path(SET {{ fidl_name.lower() }}_fdepl_path "${PROJECT_SOURCE_DIR}/config/{{ fidl_name }}.fdepl")
cmake_path(SET {{ fidl_name.lower() }}_fidl_path "{{ fidl_config_entry['path'] }}{{ fidl_name }}.fidl")

list(APPEND fp_{{ fidl_name.lower() }}_src_list
	${PROJECT_SOURCE_DIR}/fp/{{ fidl_name }}/v{{ fidl_config_entry['version'] }}/{{fidl_name}}_{{ fidl_config_entry['type'].lower() }}/FP_{{ fidl_name }}Protocol{{ fidl_config_entry['type'] }}.c
	${PROJECT_SOURCE_DIR}/fp/{{ fidl_name }}/v{{ fidl_config_entry['version'] }}/{{fidl_name}}_{{ fidl_config_entry['type'].lower() }}/FP_{{ fidl_name }}Protocol{{ fidl_config_entry['type'] }}.h
	${PROJECT_SOURCE_DIR}/fp/{{ fidl_name }}/v{{ fidl_config_entry['version'] }}/{{fidl_name}}_{{ fidl_config_entry['type'].lower() }}/FP_{{ fidl_name }}ProtocolTypes.h
	${PROJECT_SOURCE_DIR}/fp/{{ fidl_name }}/v{{ fidl_config_entry['version'] }}/{{fidl_name}}_{{ fidl_config_entry['type'].lower() }}/FP_{{ fidl_name }}{{ fidl_config_entry['type'] }}App.c
	${PROJECT_SOURCE_DIR}/fp/{{ fidl_name }}/v{{ fidl_config_entry['version'] }}/{{fidl_name}}_{{ fidl_config_entry['type'].lower() }}/FP_{{ fidl_name }}{{ fidl_config_entry['type'] }}App.h
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_INCLUDE_LIST
    "#include \\"fp/{{fidl_name}}/v{{ fidl_config_entry['version'] }}/{{fidl_name}}_{{ fidl_config_entry['type'].lower() }}/FP_{{fidl_name}}Protocol{{ fidl_config_entry['type'] }}.h\\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_HANDLERS_LIST
    "&FP_{{fidl_name}}Protocol{{ fidl_config_entry['type'] }}Info"
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INCLUDE_LIST
    "#include \\"fp/{{fidl_name}}/v{{ fidl_config_entry['version'] }}/{{fidl_name}}_{{ fidl_config_entry['type'].lower() }}/FP_{{fidl_name}}{{ fidl_config_entry['type'] }}App.h\\""
)

set_property(GLOBAL APPEND PROPERTY FUNCTION_PROTOCOL_APP_INIT_LIST
    "{{fidl_name}}{{ fidl_config_entry['type'] }}AppInit()\;"
)
{%     endfor %}

list(APPEND espsi_fp_sources
{%-      for fidl_name, fidl_config_entry in config.items() %}
    ${fp_{{ fidl_name.lower() }}_src_list}
{%-     endfor %}
)

{%      for fidl_name, fidl_config_entry in config.items() %}
FP_GEN_AT_PATH(fp_{{ fidl_name.lower() }}_src_list {{'${'}}{{ fidl_name.lower() }}_fdepl_path} {{ fidl_name.lower() }}_fidl_path {{'${'}}fp_gen_path})
{%-     endfor %}
"""

data = {
    "config": {
        "OBC_ES_ADCS":  {"path": "${FIDL_ROOT_OBC}/", "version": "3.0", "type": "Server"}
    }
}

j2_template = Template(template)

print(j2_template.render(data))
