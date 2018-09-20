//
// Created by benoit on 18/09/21.
//

#include <bobnet/exception.h>
#include "gtest/gtest.h"
#include "bobnet/bobnet.h"

using namespace bobnet;

TEST(get_request, wrong_protocol) {
    Connection conn;
    auto req = make_builder(http_request_type::GET, "hjgv://someurl.com").request();
    try {
        conn.perform(req);
        FAIL();
    } catch (BobnetException& e) {
        ASSERT_STREQ("curl_easy_perform() failed - CURL error: wrong protocol", e.what());
    }
}