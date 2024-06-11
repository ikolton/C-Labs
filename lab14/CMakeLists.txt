cmake_minimum_required(VERSION 3.20)
project(VectorModuleExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the VectorModule library
add_library(VectorModule MODULE VectorModule.ixx)
target_compile_options(VectorModule PRIVATE /std:c++latest /experimental:module /module:export)
target_include_directories(VectorModule PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Define the VectorModuleInstantiations library
add_library(VectorModuleInstantiations OBJECT VectorModuleInstantiate.ixx)
target_compile_options(VectorModuleInstantiations PRIVATE /std:c++latest /experimental:module)
target_include_directories(VectorModuleInstantiations PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Main application
add_executable(Main main.cpp)
target_compile_options(Main PRIVATE /std:c++latest /experimental:module)
target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link the VectorModule and VectorModuleInstantiations libraries to the Main executable
target_link_libraries(Main PRIVATE VectorModule VectorModuleInstantiations)
