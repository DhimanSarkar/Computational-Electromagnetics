cmake_minimum_required(VERSION 3.13)    # CMake version check
project(CompEM)                         # Create project "simple_example"
set(CMAKE_CXX_STANDARD 23)              # Enable c++23standard

add_executable(CompEM src/main.cpp)

target_include_directories (CompEM PUBLIC libraries/Eigen)