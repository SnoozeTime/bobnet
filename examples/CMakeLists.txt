include_directories(${PROJECT_SOURCE_DIR}/include)

function(add_example example_name sources)
    add_executable(${example_name} ${sources})
    target_link_libraries(${example_name} bobnet)
endfunction()

add_example(simpleget simpleget.cpp)
add_example(rest rest.cpp)
add_example(reuse_connection reuse_connection.cpp)
