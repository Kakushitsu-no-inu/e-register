set(INC ${CMAKE_SOURCE_DIR}/include)
set(SRC ${CMAKE_SOURCE_DIR}/src)

set(SOURCES
        ${INC}/config.h
        ${INC}/Person.h         ${SRC}/Person.cpp
        ${INC}/Student.h        ${SRC}/Student.cpp
        ${INC}/Teacher.h        ${SRC}/Teacher.cpp
        ${INC}/Group.h        ${SRC}/Group.cpp
        ${INC}/Stuff.h        ${SRC}/Stuff.cpp
        ${INC}/Mark.h
)

add_library(e-lib ${SOURCES})
target_include_directories(e-lib PRIVATE ${INC})
target_link_libraries(e-lib PUBLIC OpenXLSX-static)
target_compile_definitions(e-lib PRIVATE OPENXLSX_STATIC_DEFINE)