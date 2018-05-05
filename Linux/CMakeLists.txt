# Minimum CMake version
cmake_minimum_required(VERSION 3.0)

# Project name
project(ticTacLinux)

# Set build type
set(CMAKE_BUILD_TYPE Release)

# Set output folder
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

# Use C++11 standard
set(CMAKE_CXX_STANDARD 11)

set(APP_COMPILER_FLAGS
    "-fPIC"
)

# Include directories
set(APP_INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}/../common"
    "${PROJECT_SOURCE_DIR}/src"
)

# Source directories
set(APP_SOURCES
    "${PROJECT_SOURCE_DIR}/src/TicTacLinux.cpp"
    "${PROJECT_SOURCE_DIR}/../common/TurnLog.cpp"
    "${PROJECT_SOURCE_DIR}/../common/CTicTacToe.cpp"
)

# Build a shared library
add_executable(tic-tac-toe ${APP_SOURCES})

# Target compiler info.
target_include_directories(tic-tac-toe PUBLIC "${APP_INCLUDE_DIRS}")
target_compile_options(tic-tac-toe PUBLIC "${APP_COMPILER_FLAGS}")

# Install location for "sudo make install"
install(TARGETS tic-tac-toe DESTINATION /usr/local/bin)

