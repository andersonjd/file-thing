cmake_minimum_required(VERSION 3.22)
project(FtTest CXX)

find_package(GTest REQUIRED CONFIG)

add_executable(test_ft
    main.cpp
    ../src/ft/file_thing.cpp)

target_link_libraries(test_ft GTest::gtest GTest::gtest_main)
set_property(TARGET test_ft PROPERTY CXX_STANDARD 17)