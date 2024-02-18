cmake_minimum_required(VERSION 3.22)

project(
    ft
    VERSION 0.1
    LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT BUILD_TESTING STREQUAL OFF)
    add_subdirectory(unit_tests)
else()
    find_package(CLI11 CONFIG REQUIRED)

    add_executable(ft
        src/main.cpp
        src/ft/file_thing.cpp
        src/cli/commands.cpp
    )

    target_link_libraries(ft PRIVATE CLI11::CLI11)
    set_property(TARGET ft PROPERTY CXX_STANDARD 17)
endif()


