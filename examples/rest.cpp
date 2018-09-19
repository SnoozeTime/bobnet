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
       // std::cout << "SUCCESS -> " << resp.text() << std::endl;
    } else {
        std::cout << "Nope. " << resp.status_code() << std::endl;
    }

    //title: 'foo',
    //      body: 'bar',
    //      userId: 1
    auto post_json = R"(
    {
        "title": "foo",
        "body": "bar",
        "userId": 1
    }
    )"_json;
    auto req = bobnet::make_builder(bobnet::http_request_type::POST,
                                            "https://jsonplaceholder.typicode.com/posts")
                                                    .json(post_json).request();
    //auto resp2 = bobnet::get("http://localhost:9080/value/blasw/");
    bobnet::Connection conn;
    auto resp2 = conn.perform(req);
    std::cout << resp2.status_code() << std::endl;

    auto resp2_json = resp2.json();
    std::cout << "Created a new post with ID: " << resp2_json["id"]<< std::endl;

    std::stringstream new_post_url;
    new_post_url << "https://jsonplaceholder.typicode.com/posts/" << resp2_json["id"];
    auto resp3 = bobnet::get(new_post_url.str());
    std::cout << resp3.text() << std::endl;
//    if (resp2.status_code() == 200) {
//        std::cout << "SUCCESS -> " << resp2.text() << std::endl;
//    } else {
//        std::cout << "Nope. " << resp2.status_code() << std::endl;
//    }
}
