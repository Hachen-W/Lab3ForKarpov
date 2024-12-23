cmake_minimum_required(VERSION 3.2)

project(VECTOR VERSION 1.0 LANGUAGES CXX)

add_compile_options(-fprofile-arcs -ftest-coverage)
link_libraries(gcov)

add_executable(bin test.cpp)

#add_library(libsygnal STATIC sygnal.cpp)
#target_link_libraries(bin PRIVATE libsygnal)

# Catch2
add_subdirectory(Catch2)
# These tests can use the Catch2-provided main
target_link_libraries(bin PRIVATE Catch2::Catch2WithMain)