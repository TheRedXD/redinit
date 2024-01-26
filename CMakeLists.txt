cmake_minimum_required(VERSION 3.16)
project(redinit CXX)

# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)

add_executable(redinit
    src/main.cpp
    src/scripts/cppconancmake.cpp
    src/scripts/cppconan.cpp
)

target_link_libraries(redinit -static)
