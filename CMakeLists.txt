cmake_minimum_required(VERSION 3.15..3.20 FATAL_ERROR)
project(E-Register VERSION 0.0.1 DESCRIPTION "Term Paper" LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/deps.cmake)

add_subdirectory(libs)

add_executable(e-register apps/main.cpp)
target_link_libraries(e-register PRIVATE core)
