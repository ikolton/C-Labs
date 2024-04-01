cmake_minimum_required(VERSION 3.27)
project(Lab5)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab5 ex1_Pair.cpp
        staticVector.h
        /ex2_staticVector.cpp
        /ex3_dynamicVector.cpp
        ex4_conversion.cpp
        /ex3_dynamicVector.cpp
        ex2_staticVector.cpp
        dynamicVector.h)
