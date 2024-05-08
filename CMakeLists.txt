cmake_minimum_required(VERSION 3.20)
project(i8080 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(i8080 STATIC)
target_sources(i8080 PRIVATE src/processor.cpp src/register.cpp)

add_executable(tests)
target_sources(tests PRIVATE tests/test.cpp)
target_include_directories(tests PRIVATE src/)
target_link_libraries(tests PRIVATE i8080)