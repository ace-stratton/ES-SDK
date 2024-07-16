project(irq C)

add_library(irq STATIC
    "src/irq.c"
)

target_include_directories(irq PRIVATE ${ROOT_INCLUDES} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_compile_definitions(irq PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(irq PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(irq PRIVATE ${ROOT_LINK_OPTIONS})