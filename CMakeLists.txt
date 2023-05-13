cmake_minimum_required(VERSION 3.13)    # CMake version check
project(CompEM)                         # Create project "simple_example"
set(CMAKE_CXX_STANDARD 23)              # Enable c++23standard

add_executable(MoM src/main_MoM.cpp)
add_executable(FEM src/main_FEM.cpp)
add_executable(FDTD src/main_FDTD.cpp)

target_include_directories (MoM PUBLIC libraries/Eigen)
target_include_directories (FEM PUBLIC libraries/Eigen)