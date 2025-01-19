cmake_minimum_required(VERSION 3.30)
project(adventofcode2024)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DAY_SOURCES
        day1.cpp
        day2.cpp
        day14.cpp
        # Add more day*.cpp files here
)

foreach(SRC ${DAY_SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SRC} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SRC})
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
    target_compile_definitions(${EXECUTABLE_NAME} PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
endforeach()
