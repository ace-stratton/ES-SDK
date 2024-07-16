cmake_minimum_required(VERSION 3.10)

project(cpptest-unittest-cmake)

# Set the compiler to be used by cpptest
set(CPPTEST_COMPILER_ID gcc)

# Include the cpptest functions from the installation folder
set(CPPTEST_INSTALL C:/cpptest)

include(${CPPTEST_INSTALL}/integration/cmake/cpptest-project.cmake)

# Add the project subdirectories
add_subdirectory(cpptest)
