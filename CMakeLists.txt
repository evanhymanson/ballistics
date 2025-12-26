cmake_minimum_required(VERSION 3.26)

project(ballistics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(prop)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE prop)