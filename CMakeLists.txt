cmake_minimum_required(VERSION 2.6)
project(algo3_tp1)

set(SOURCE_FILES
        src/Backtrack.cpp src/Backtrack.h
        src/ImprovedBacktrack.cpp src/ImprovedBacktrack.h
        src/Solver.h src/Utils.h src/Dynamic.cpp src/Dynamic.h src/Utils.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_library(algo3-tp1-base ${SOURCE_FILES})

add_executable(ej1 src/ej1.cpp)
target_link_libraries (ej1 algo3-tp1-base)
add_executable(ej2 src/ej2.cpp)
target_link_libraries (ej2 algo3-tp1-base)
add_executable(ej3 src/ej3.cpp)
target_link_libraries (ej3 algo3-tp1-base)

add_subdirectory(test)

add_subdirectory(data)