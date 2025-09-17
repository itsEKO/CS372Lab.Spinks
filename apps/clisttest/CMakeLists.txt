cmake_minimum_required(VERSION 3.10)
project(CircularListTests)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add executable for the test
add_executable(CircularListTest CircularListTest.cpp)

# Link Google Test libraries and pthread
target_link_libraries(CircularListTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# Enable testing
enable_testing()

# Add test
add_test(NAME CircularListTest COMMAND CircularListTest)