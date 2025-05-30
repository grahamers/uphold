cmake_minimum_required(VERSION 3.16)
project(MyApp LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Global compile options
add_compile_options(-g -O0 -Wall)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main application executable
add_executable(main
    src/main.cxx
    src/utils.cxx
)

# Test executable
add_executable(tests
    tests/main.cxx
    src/utils.cxx
)

