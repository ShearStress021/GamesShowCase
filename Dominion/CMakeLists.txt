
cmake_minimum_required(VERSION 3.24)
project(DonDominion VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG 5.5
	GIT_SHALLOW TRUE
	)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_MakeAvailable(raylib)

#include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp )

add_executable(res ${SOURCES})
#set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

target_link_libraries(res PRIVATE raylib)

