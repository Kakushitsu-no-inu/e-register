set(INC ${CMAKE_SOURCE_DIR}/include)
set(SRC ${CMAKE_SOURCE_DIR}/src)

set(SOURCES
        ${INC}/Person.h         ${SRC}/Person.cpp
        ${INC}/Student.h        ${SRC}/Student.cpp
        ${INC}/Teacher.h        ${SRC}/Teacher.cpp
        ${INC}/Group.h        ${SRC}/Group.cpp
)

add_library(e-lib ${SOURCES})
target_include_directories(e-lib PRIVATE ${INC})