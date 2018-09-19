//
// Will send request to a REST API that is receiving and sending back JSON formatted data
// Created by benoit on 18/09/15.
//
#include <bobnet/bobnet.h>
#include <iostream>

//https://jsonplaceholder.typicode.com/todos/1
int main() {
    bobnet::Context context;

    // First will query the GET endpoint
    auto resp = bobnet::get("https://jsonplaceholder.typicode.com/posts");

    if (resp.status_code() == 200) {
        std::cout << "SUCCESS -> " << resp.text() << std::endl;
    } else {
        std::cout << "Nope. " << resp.status_code() << std::endl;
    }

    //auto resp2 = bobnet::get("http://localhost:9080/value/blasw/");

//    if (resp2.status_code() == 200) {
//        std::cout << "SUCCESS -> " << resp2.text() << std::endl;
//    } else {
//        std::cout << "Nope. " << resp2.status_code() << std::endl;
//    }
}
