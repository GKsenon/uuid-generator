cmake_minimum_required(VERSION 3.7)
project(uuid-generator C)
set(CMAKE_C_STANDARD 11)

enable_testing()
add_subdirectory(src)
add_subdirectory(demo)
