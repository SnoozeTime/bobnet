#include <iostream>
#include "bobnet/bobnet.h"


int main() {

    bobnet::Context context;
    auto resp = bobnet::get("www.google.com");

    std::cout << "HEADERS\n";
    for (const auto& h: resp.headers().headers()) {
        std::cout << h.first << " -> " << h.second << std::endl;
    }

    std::cout << "BODY\n" << resp.text() << std::endl;

    return 0;
}