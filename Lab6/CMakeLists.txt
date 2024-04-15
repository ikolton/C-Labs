cmake_minimum_required(VERSION 3.27)
project(Lab6)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab6 ex1variadicFunctions.cpp
        /ex2_proxy.cpp
        ex4_MultiVector.cpp
        ex1variadicFunctions.cpp
        ex2_proxy.cpp)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})