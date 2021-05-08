include(FetchContent)

FetchContent_Declare(
        OpenXLSX
        GIT_REPOSITORY https://github.com/troldal/OpenXLSX.git
        GIT_TAG master
)

FetchContent_GetProperties(OpenXLSX)
if(NOT OpenXLSX_POPULATED)
        FetchContent_Populate(OpenXLSX)
        add_subdirectory(${OpenXLSX_SOURCE_DIR} ${OpenXLSX_BINARY_DIR})
endif()
set(OPENXLSX_PATH ${OpenXLSX_SOURCE_DIR})

FetchContent_Declare(
        fmt
        GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
        GIT_TAG 0889856d6160775462e9e0722d121aab0e75e873
)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
        FetchContent_Populate(fmt)
        add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
endif()
set(FMT_PATH ${fmt_SOURCE_DIR})