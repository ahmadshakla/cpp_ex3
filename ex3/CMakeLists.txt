cmake_minimum_required(VERSION 3.12)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS"$CMAKE_CXX_FLAGS -Wall -Wextra -Wvla")

add_executable(ex3 HashMapTester1.3.cpp HashMap.hpp)