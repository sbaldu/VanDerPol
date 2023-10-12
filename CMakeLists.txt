cmake_minimum_required(VERSION 3.16.0)
project(VanDerPol LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

# include pybind11 extern subfolder
add_subdirectory(./extern/pybind11)

include_directories(./src)
pybind11_add_module(vdp SHARED src/binding.cc)
