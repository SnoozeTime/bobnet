cmake_minimum_required(VERSION 3.12)
project(simplehttp)

set(CMAKE_CXX_STANDARD 14)

add_executable(simplehttp main.cpp connection.cpp connection.h bobnet.cpp bobnet.h response.cpp response.h)
target_link_libraries(simplehttp curl)