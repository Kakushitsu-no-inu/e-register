add_library(ui STATIC menu.h menu.cpp option.h option.cpp ui.h ui.cpp)
target_include_directories(ui PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
