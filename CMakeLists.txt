cmake_minimum_required(VERSION 3.30)
project(adventofcode2024)

set(CMAKE_CXX_STANDARD 26)

file(GLOB CPP_FILES "day*.cpp")
foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE} utils.cpp utils.h)
    target_compile_definitions(${EXECUTABLE_NAME} PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
endforeach()
