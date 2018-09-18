//
// Created by benoit on 18/09/15.
//
#include "gtest/gtest.h"
#include "bobnet/response.h"

TEST(parse_headers, with_crlf_non_nullterminated) {

    bobnet::Headers headers;
    char hi[] = {'N', 'a', 'm', 'e', ':', ' ', 'V', 'a', 'l', 'u', 'e', '\r', '\n'};
    headers.parse_header(hi, 13);

    ASSERT_EQ(1, headers.headers().size());
    auto maybe_value = headers.header("Name");
    if (maybe_value) {
        ASSERT_STREQ("Value", maybe_value.value().c_str());
    } else {
        FAIL();
    }
}

TEST(parse_headers, with_crlf_nullterminated) {

    bobnet::Headers headers;
    char hi[] = {'N', 'a', 'm', 'e', ':', ' ', 'V', 'a', 'l', 'u', 'e', '\r', '\n', '\0'};
    headers.parse_header(hi, 14);

    ASSERT_EQ(1, headers.headers().size());
    auto maybe_value = headers.header("Name");
    if (maybe_value) {
        ASSERT_STREQ("Value", maybe_value.value().c_str());
    } else {
        FAIL();
    }
}

TEST(dump_headers, normal_case) {
    bobnet::Headers headers;
    headers.add("Content-Type", "application/json");
    headers.add("X-Custom", "key");
    auto curl_list = headers.dump();

    if (curl_list) {
        ASSERT_STREQ("X-Custom: key", curl_list->data);

        auto next = curl_list->next;
        ASSERT_STREQ("Content-Type: application/json", next->data);
        ASSERT_TRUE(next->next == nullptr);
    } else {
        FAIL();
    }
}

TEST(dump_headers, no_headers) {
    bobnet::Headers headers;
    auto curl_list = headers.dump();

    if (curl_list) {
        FAIL();
    }
}