add_library(ui STATIC 
    ui/include/menu.h       ui/src/menu.cpp 
    ui/include/option.h     ui/src/option.cpp 
    ui/include/ui.h         ui/src/ui.cpp
)
target_include_directories(ui PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ui/include>
)

add_library(utils STATIC 
    utils/include/utils.hpp utils/src/utils.cpp
)
target_include_directories(utils PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utils/include>
)

add_library(core STATIC
    core/include/config.h
    core/include/Person.h       core/src/Person.cpp
    core/include/Student.h      core/src/Student.cpp
    core/include/Teacher.h      core/src/Teacher.cpp
    core/include/Group.h        core/src/Group.cpp
    core/include/Stuff.h        core/src/Stuff.cpp
    core/include/Mark.h
    core/include/application.h  core/src/application.cpp
)
target_include_directories(core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include>
    ${OPENXLSX_PATH}/include
)

target_compile_definitions(core PRIVATE
    OPENXLSX_STATIC_DEFINE
)
target_link_libraries(core PUBLIC
    OpenXLSX-static utils ui
)
