include(FetchContent)

FetchContent_Declare(
    OpenXLSX
    GIT_REPOSITORY https://github.com/troldal/OpenXLSX.git
    GIT_TAG master
)
FetchContent_MakeAvailable(OpenXLSX)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
    GIT_TAG 0889856d6160775462e9e0722d121aab0e75e873
)
FetchContent_MakeAvailable(fmt)
