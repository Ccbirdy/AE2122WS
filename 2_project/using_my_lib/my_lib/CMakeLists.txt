cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(proj LANGUAGES CXX)

# search for OpenMP, REQUIRED -> fatal error if not found
find_package(OpenMP REQUIRED)

# add a library to the project using the specified source files
add_library(enhccomp STATIC include/enhance.h src/enhance.cpp)

# PUBLIC -> targets that link to this target get that include directory
target_include_directories(enhccomp PUBLIC include PRIVATE src)

# link to the imported target provided by the FindOpenMP module
target_link_libraries(enhccomp PUBLIC OpenMP::OpenMP_CXX)
