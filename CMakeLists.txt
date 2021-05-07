cmake_minimum_required(VERSION 3.17..3.20 FATAL_ERROR)
project(E-Register VERSION 0.0.1 
        DESCRIPTION "Term Paper"
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

include(scripts/excel.cmake)

add_subdirectory(src)
add_subdirectory(ui)
add_subdirectory(utils)

set(EXT_LIBS ui e-lib)

add_executable(e-register apps/main.cpp)
# target_include_directories(e-register PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(e-register PRIVATE ${EXT_LIBS})