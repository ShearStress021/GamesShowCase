cmake_minimum_required(VERSION 3.24) # FetchContent with integrated find_package() is available in 3.24+
project(ArmagaddonClash)


# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 4.0.0)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

set(RAYGUI_VERSION 3.2)
FetchContent_Declare(
    raygui
    URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYGUI_VERSION} EXACT
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raygui)

# 1. Create a "dummy" target for raygui
add_library(raygui INTERFACE)

# 2. Tell CMake where the raygui.h file is located
target_include_directories(raygui INTERFACE ${raygui_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(res ${SOURCES})

target_link_libraries(res raylib)
target_link_libraries(res raygui)


