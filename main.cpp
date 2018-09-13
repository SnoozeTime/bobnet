#include <iostream>
#include "bobnet.h"


int main() {

    bobnet::Context context;
    auto resp = bobnet::get("www.google.com");

    std::cout << resp.text() << std::endl;

    return 0;
}