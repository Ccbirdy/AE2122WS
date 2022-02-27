cmake_minimum_required(VERSION 3.8)
project(scanenhancer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_executable(proj proj.cpp)

target_link_libraries(proj PUBLIC OpenMP::OpenMP_CXX)
