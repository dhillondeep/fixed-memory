cmake_minimum_required(VERSION 3.8)
project(fixed_memory)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/Allocator.cpp examples/allocator/allocate_fixed.cpp)
add_executable(fixed_memory ${SOURCE_FILES})