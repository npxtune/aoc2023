cmake_minimum_required(VERSION 3.27)
project(aoc2023 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_COMPILER clang)

# Define an option to specify the day
option(DAY "Select the day directory for compilation" "")

#   Select day directory to be used for compilation
set(DAY day4)

# Check if DAY option is provided
if(NOT DAY)
    message(FATAL_ERROR "Please specify a day directory using --DAY=<day>")
endif()

# Set the source directory based on the provided day
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/${DAY})

# Check if the specified directory exists
if(NOT EXISTS ${SOURCE_DIR})
    message(FATAL_ERROR "Directory ${SOURCE_DIR} does not exist.")
endif()

# Add the main.c file from the specified directory
add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.c)