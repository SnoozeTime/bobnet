include_directories(${PROJECT_SOURCE_DIR}/include/bobnet)

add_library(bobnet bobnet.cpp connection.cpp response.cpp)
target_link_libraries(bobnet curl)