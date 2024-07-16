# C/C++test test project 'cpptest_espsi_drv'
# Project will be located in the current directory (./)
# Test cases will be generated into ./tests

# In order to build the espsi_drv we need to set the ROOT_* variables
ROOT_INCLUDES
ROOT_COMPILE_DEFS
ROOT_COMPILE_OPTIONS
ROOT_LINK_OPTIONS

# Add espsi_drv target to the cpptest_modules
cpptest_add_executable(
    cpptest_espsi_drv
    CPPTEST_PROJECT_FOLDERS
        espsi_drv=${CMAKE_SOURCE_DIR}/..
    TARGETS espsi_drv
)

file(GLOB modules_INCLUDES "${CMAKE_SOURCE_DIR}/modules/**/include")
target_include_directories(cpptest_espsi_drv PRIVATE ${modules_INCLUDES})
target_link_libraries(cpptest_espsi_drv PRIVATE espsi_drv)

