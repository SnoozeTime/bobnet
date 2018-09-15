cmake_minimum_required(VERSION 3.12)
project(simplehttp)

# FOR TESTING
add_subdirectory (googletest-release-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)


add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
