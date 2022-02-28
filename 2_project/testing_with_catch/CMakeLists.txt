cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(proj LANGUAGES CXX)

# embed library proj in project test_pi
add_subdirectory(my_lib)

# catch is a header only library for testing
# embed library catch in project test_pi
add_subdirectory(catch)

# create executable with all tests
add_executable(proj_tests catch_main.cpp catch_tests_proj.cpp)

# link libraries proj and catch to executable
target_link_libraries(proj_tests PRIVATE proj PRIVATE catch)
