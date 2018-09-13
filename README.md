# Bobnet 

## Description
Simplest HTTP request. I am always duplicating the Curl code in my pet projects so I wanted something easier for
simpler use cases. The API is inspired (copied? :D) from python's request.

Clearly WIP. Contributions are welcomed.

## Build

Requirement is libcurl. Then you can use CMake to build.

## Example

```cpp
#include <iostream>
#include "bobnet.h"


int main() {
    bobnet::Context context;
    auto resp = bobnet::get("www.google.com");
    std::cout << resp.text() << std::endl;
}
```