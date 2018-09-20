include_directories(${PROJECT_SOURCE_DIR}/include)

function (add_bobnet_test test_class)
    add_executable(${test_class} ${test_class}.cpp)
    target_link_libraries(${test_class} bobnet gtest gtest_main)
endfunction()

add_bobnet_test(headers_test)
add_bobnet_test(request_test)
add_bobnet_test(connection_test)