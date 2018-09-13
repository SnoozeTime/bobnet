include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(simpleget simpleget.cpp)
target_link_libraries(simpleget bobnet)