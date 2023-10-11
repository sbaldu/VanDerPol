cmake_minimum_required(VERSION 3.16.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the C++ flags
string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -g")

# Set the folder for the executable
set(EXECUTABLE_OUTPUT_PATH ../)

include(FetchContent)
# Get doctest
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG 7b9885133108ae301ddd16e2651320f54cafeba7
)
FetchContent_GetProperties(doctest)
if(NOT doctest_POPULATED)
  FetchContent_Populate(doctest)
endif()

# Set base directory for serial code
include_directories(../src/)

# Compile
add_executable(test_solution.out ./test_solution.cc)
target_include_directories(test_solution.out SYSTEM PRIVATE ${doctest_SOURCE_DIR}/doctest)
add_test(NAME test_solution.out COMMAND test_solution.out)
add_executable(test_eulerSolver.out ./test_eulerSolver.cc)
target_include_directories(test_eulerSolver.out SYSTEM PRIVATE ${doctest_SOURCE_DIR}/doctest)
add_test(NAME test_eulerSolver.out COMMAND test_eulerSolver.out)
# To be added
# add_executable(test_rk2Solver.out ./test_rk2Solver.cc)
# target_include_directories(test_rk2Solver.out SYSTEM PRIVATE ${doctest_SOURCE_DIR}/doctest)
# add_test(NAME test_rk2Solver.out COMMAND test_rk2Solver.out)
