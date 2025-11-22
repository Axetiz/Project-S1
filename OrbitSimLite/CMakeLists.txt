cmake_minimum_required(VERSION 3.15)
project(OrbitSimLite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ORBITSIMLITE_BUILD_DEMO "Build the demo application" ON)

# Library sources
set(ORBITSIMLITE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ORBITSIMLITE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(orbitsimlite STATIC
    ${ORBITSIMLITE_SRC_DIR}/vec2.cpp
    ${ORBITSIMLITE_SRC_DIR}/body.cpp
    ${ORBITSIMLITE_SRC_DIR}/physics.cpp
    ${ORBITSIMLITE_SRC_DIR}/simulator.cpp
    ${ORBITSIMLITE_SRC_DIR}/renderer.cpp
)

target_include_directories(orbitsimlite PUBLIC ${ORBITSIMLITE_INCLUDE_DIR})

# Find SFML for the renderer and demo
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics)

target_link_libraries(orbitsimlite PUBLIC sfml-system sfml-window sfml-graphics)

if (MSVC)
    target_compile_options(orbitsimlite PRIVATE /W4 /permissive-)
else()
    target_compile_options(orbitsimlite PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (ORBITSIMLITE_BUILD_DEMO)
    add_executable(demo examples/demo.cpp)
    target_link_libraries(demo PRIVATE orbitsimlite)
    target_include_directories(demo PRIVATE ${ORBITSIMLITE_INCLUDE_DIR})
endif()