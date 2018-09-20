# Bobnet 

## Description
Simplest HTTP request. I am always duplicating the Curl code in my pet projects so I wanted something easier for
simpler use cases. The API is inspired (copied? :D) from python's request.

My motivations to write this code:
- Have access to an Requests-like librairie for my projects
- Practice new c++ features
 
 This is not a curl wrapper by design so some features will be missing. Feel free to 
 suggest improvements.
 
WIP. Contributions are welcomed.

## Build

Requirement is libcurl and jsonformoderncpp (TODO: give choice of JSON Lib).
 
 Using conan to manage the dependencies. You can install conan easily with python pip
 in a virtual env
 ```shell
 virtualenv venv
 source venv/bin/activate
 pip install conan
```

## Examples

Examples are located in examples folder.

## Basic usage

Using the convenience function in bobnet.h. The API is synchronous so the HTTP request
will be finished once the function returns.
```cpp
#include <iostream>
#include "bobnet.h"

int main() {
    bobnet::Context context;
    
    // Do a get request to get the body of a page
    auto resp = bobnet::get("www.google.com");
    std::cout << resp.text() << std::endl;
    
    // post json to some REST API.
    auto resp2 = bobnet::post(bobnet::post("https://jsonplaceholder.typicode.com/posts",
        R"(
        {
            "title": "foo",
            "body": "bar",
            "userId": 1    
        }
        )"_json
    );
    std::cout << resp.json() << std::endl;
}
```