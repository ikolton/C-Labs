cmake_minimum_required(VERSION 3.00)
project(lab7)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(Range ex_7_1_Range.cpp Range.h)

add_executable(MatrixModifiers ex_7_2_MatrixModifiers.cpp Matrix.h )

add_executable(MatrixIterator ex_7_3_MatrixIterator.cpp Matrix.h )

add_executable(Filter ex_7_4_Filter.cpp Filter.h)

