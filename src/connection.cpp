//
// Created by benoit on 18/09/13.
//

#include "connection.h"
#include "response.h"
#include <iostream>
#include <cassert>
#include <exception.h>

using namespace bobnet;

/// Verify CURL code is OK. If not, will throw an exception. This is triggered by recoverable user
/// error. Code bug should not be using this one (for example, setting the write function should never
/// fail...)
/// \param code
/// \param details
inline void throw_if_err(CURLcode code, const char* details) {
    if (code != CURLE_OK) {
        throw BobnetException(details, code);
    }
}

/// Same as above but for non-recoverable errors
/// \param code
inline void assert_ok(CURLcode code) {
    assert(code == CURLE_OK);
}
static size_t write_body_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    resp->add_data(content, real_size);
    return real_size;
}

// Get header and status code...
static size_t write_header_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    std::string http_header_str(content, real_size);
    resp->headers().parse_header(content, real_size);

    return real_size;
}

Response Connection::perform(const bobnet::Request& request) {

    Response resp;
    long status_code;

    // This should never fail...
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_WRITEFUNCTION, write_body_cb));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_WRITEDATA, &resp));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_HEADERFUNCTION, write_header_cb));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_HEADERDATA, &resp));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0"));

    // Set by user
    throw_if_err(curl_easy_setopt(handle_.get(), CURLOPT_URL, request.uri().c_str()), "Set URL");
    auto header_data = request.headers().dump();
    if (header_data) {
        throw_if_err(curl_easy_setopt(handle_.get(), CURLOPT_HTTPHEADER, header_data.get()), "Set headers");
    }

    switch (request.type()) {
        case http_request_type::GET:
            get(request, resp);
            break;
        case http_request_type::POST:
            post(request, resp);
            break;
        default:
            assert(false);
    }

    throw_if_err(curl_easy_perform(handle_.get()), "curl_easy_perform() failed");

    curl_easy_getinfo(handle_.get(), CURLINFO_RESPONSE_CODE, &status_code);
    resp.set_status_code(status_code);
    return resp;
}

void Connection::get(const bobnet::Request& /*request*/, Response& /*resp*/) {
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_HTTPGET, 1L));
}

void Connection::post(const bobnet::Request& request, Response& /*resp*/) {
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_POST, 1L));

    if (!request.content().empty()) {
        throw_if_err(curl_easy_setopt(handle_.get(), CURLOPT_POSTFIELDS, request.content().c_str()), "Set body");
    }
}
