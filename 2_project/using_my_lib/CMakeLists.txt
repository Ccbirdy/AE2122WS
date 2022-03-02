cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(pi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF) # disable compiler specific extensions
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# embed library picomp in project pi
add_subdirectory(my_lib)

# create executable with name pi
add_executable(proj main.cpp)

# picomp already uses OpenMP, so no need to link OpenMP again to pi
target_link_libraries(proj PUBLIC enhccomp)
