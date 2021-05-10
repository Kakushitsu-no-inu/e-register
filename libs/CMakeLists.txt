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
    core/include/person.h       core/src/person.cpp
    core/include/student.h      core/src/student.cpp
    core/include/teacher.h      core/src/teacher.cpp
    core/include/group.h        core/src/group.cpp
    core/include/stuff.h        core/src/stuff.cpp
    core/include/mark.h         core/src/mark.cpp
    core/include/application.h  core/src/application.cpp
)
target_include_directories(core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include>
    ${OPENXLSX_PATH}/include
    ${FMT_PATH}/include
)

target_compile_definitions(core PRIVATE
    OPENXLSX_STATIC_DEFINE
)
target_link_libraries(core PUBLIC
    OpenXLSX-static utils ui fmt::fmt-header-only
)


find_program(
    clang_tidy
    NAMES clang-tidy
    PATHS /usr/local/opt/llvm/bin/
)

if (clang_tidy)
set_target_properties(
        utils ui core
        PROPERTIES CXX_CLANG_TIDY ${clang_tidy}
)
endif (clang_tidy)
