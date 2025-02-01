cmake_minimum_required(VERSION 3.10)
project(Maguic)

file(GLOB SOURCES "src/*.cc")
file(GLOB EXAMPLES "examples/*.cc")
add_executable(${PROJECT_NAME} ${SOURCES} ${EXAMPLES})

# add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# add compiler errors/warnings flags depending on compiler
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)

# Create an option to switch between a system sdl library and a vendored SDL library
option(MAGUIC_VENDORED "Use vendored libraries" OFF)

if(MAGUIC_VENDORED)
    # us SDL as a submodule in include/SDL
    message( FATAL_ERROR "FIXME: NOT READY YET, CMake will exit." )
    add_subdirectory(include/SDL EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL3 package,
    # 2. look for the SDL3-shared component, and
    # 3. fail if the shared component cannot be found.
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)