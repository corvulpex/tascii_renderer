cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(TRenderer)


find_package (Eigen3 3.3 REQUIRED NO_MODULE)


set(SOURCES
    src/main.cpp
    src/terminal.cpp
	src/wf_obj.cpp
	src/vertex_transformer.cpp
)

add_executable(TRenderer ${SOURCES})

target_link_libraries (TRenderer Eigen3::Eigen)

target_include_directories(TRenderer PRIVATE ${PROJECT_SOURCE_DIR}/include)
