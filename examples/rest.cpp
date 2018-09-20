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
    auto resp = bobnet::get("https://jsonplaceholder.typicode.com/posts/1");

    if (resp.status_code() == 200) {
       std::cout << "SUCCESS -> " << resp.json() << std::endl;
    } else {
        std::cout << "Nope. " << resp.status_code() << std::endl;
    }

    auto post_json = R"(
    {
        "title": "foo",
        "body": "bar",
        "userId": 1
    }
    )"_json;

    auto resp2 = bobnet::post("https://jsonplaceholder.typicode.com/posts", post_json);
    std::cout << resp2.status_code() << std::endl;

    auto resp2_json = resp2.json();
    std::cout << "Created a new post with ID: " << resp2_json["id"]<< std::endl;
}
