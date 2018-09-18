//
// Show how to reuse the same connection to execute multiple HTTP request if the server allows it.
//
#include "bobnet/bobnet.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace bobnet;

int main() {

    Context context;
    RequestBuilder builder(http_request_type::GET, "https://jsonplaceholder.typicode.com/todos/1");
    auto req = builder.request();

    Connection conn;
    auto resp = conn.perform(req);
    std::cout << resp.text() << std::endl;

    auto j = json::parse(resp.text());

    if (j.is_object()) {
        std::cout << "JSON doc is an object\n";
    }

    // range-based for
    for (auto it = j.begin(), it2 = j.end(); it != it2; ++it) {
        std::cout << it.key() << " -> " << it.value() << '\n';
    }
}

