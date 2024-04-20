cmake_minimum_required(VERSION 3.00)
project(lab8)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex1_type_traits ex_8_1_type_traits.cpp
        ex_8_1_type_traits.cpp)
add_executable(ex2_traits ex_8_2_Vector_traits.cpp
        ex_8_1_type_traits.cpp)
add_executable(ex3_policies ex_8_3_Vector_policies.cpp
        ex_8_1_type_traits.cpp)
add_executable(ex4_operators ex_8_4_Vector_operators.cpp
        ex_8_1_type_traits.cpp)