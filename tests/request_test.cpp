//
// Created by benoit on 18/09/18.
//
#include "gtest/gtest.h"
#include "bobnet/bobnet.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace bobnet;

TEST(create_request, simple_get_request) {
    RequestBuilder builder(http_request_type::GET, "127.0.0.1");
    auto req = builder.request();

    ASSERT_EQ(http_request_type::GET, req.type());
    ASSERT_STREQ("127.0.0.1", req.uri().c_str());
}

TEST(create_request, post_json) {

    auto j = R"(
                {
                    "happy": true,
                    "id": 450
                }
             )"_json;
    auto builder = make_builder(http_request_type::GET, "127.0.0.1").json(j);
    auto req = builder.request();
    auto maybe_header = req.headers().header("Content-Type");

    ASSERT_STREQ("{\"happy\":true,\"id\":450}", req.content().c_str());
    if (maybe_header) {
        ASSERT_STREQ("application/json", maybe_header.value().c_str());
    } else {
        FAIL();
    }
}