cmake_minimum_required(VERSION 3.5)
project(allocatorExample)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES ../allocate_fixed.cpp ../../../src/Allocator.cpp)
add_executable(allocateExample ${SOURCE_FILES})