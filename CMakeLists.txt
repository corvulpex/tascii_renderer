cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(TRenderer)

set(SOURCES
    src/main.cpp
    src/terminal.cpp
	src/obj.cpp
)

add_executable(TRenderer ${SOURCES})

target_include_directories(TRenderer PRIVATE ${PROJECT_SOURCE_DIR}/include)
