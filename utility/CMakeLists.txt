add_library(utils STATIC utils.hpp utils.cpp)
target_include_directories(utils PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
