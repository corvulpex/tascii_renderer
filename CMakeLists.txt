cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

project(tascii_renderer)


find_package (Eigen3 3.3 REQUIRED NO_MODULE)


set(SOURCES
    src/main.cpp
    src/terminal.cpp
	src/wf_obj.cpp
	src/vertex_transformer.cpp
	src/math_helper.cpp
	src/object.cpp
	src/rasterizer.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries (${CMAKE_PROJECT_NAME} Eigen3::Eigen)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
