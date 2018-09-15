//
// Will send request to a REST API that is receiving and sending back JSON formatted data
// Created by benoit on 18/09/15.
//
#include <bobnet/bobnet.h>
#include <iostream>

//https://jsonplaceholder.typicode.com/todos/1
int main() {
    // First will query the GET endpoint
    auto resp = bobnet::get("https://jsonplaceholder.typicode.com/todos/1");

    std::cout << resp.text() << std::endl;
}
