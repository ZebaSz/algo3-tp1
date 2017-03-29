cmake_minimum_required(VERSION 2.8)
project(algo3_tp1)

set(SOURCE_FILES
        src/Backtrack.cpp src/Backtrack.h
        src/ImprovedBacktrack.cpp src/ImprovedBacktrack.h
        src/Solver.h src/Utils.h)

set(MAIN_FILE main.cpp)

set(TEST_FILES test/BacktrackTest.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03 -Wall -Wno-long-long -pedantic -Wno-variadic-macros")

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(correrTests ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(correrTests gtest gtest_main)

add_executable(algo3_tp1 ${SOURCE_FILES} ${MAIN_FILE})
