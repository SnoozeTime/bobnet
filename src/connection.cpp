//
// Created by benoit on 18/09/13.
//

#include "connection.h"
#include "response.h"
#include <iostream>
#include <cassert>
using namespace bobnet;

static size_t write_body_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    resp->add_data(content, real_size);
    return real_size;
}

// Get header and status code...
static size_t write_header_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    std::string http_header_str(content, real_size);


    if (http_header_str.substr(0, 4) == "HTTP") {
        // status code is 3 digits from first space
        auto status_index = http_header_str.find(' ');
        std::stringstream status_ss(http_header_str.substr(status_index+1, 3));
        int status;
        status_ss >> status;
        resp->set_status_code(status);
    } else {
        // Status line :)
        resp->headers().parse_header(content, real_size);
    }
    return real_size;
}

Response Connection::process(const bobnet::Request& request) {

    Response resp;
    curl_easy_setopt(handle_.get(), CURLOPT_URL, request.uri().c_str());
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEFUNCTION, write_body_cb);
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEDATA, &resp);
    curl_easy_setopt(handle_.get(), CURLOPT_HEADERFUNCTION, write_header_cb);
    curl_easy_setopt(handle_.get(), CURLOPT_HEADERDATA, &resp);
    curl_easy_setopt(handle_.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0");

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


    auto res = curl_easy_perform(handle_.get());
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }
    return resp;
}

void Connection::get(const bobnet::Request& /*request*/, Response& /*resp*/) {
    curl_easy_setopt(handle_.get(), CURLOPT_HTTPGET, 1L);
}

void Connection::post(const bobnet::Request& /*request*/, Response& /*resp*/) {
    curl_easy_setopt(handle_.get(), CURLOPT_POST, 1L);
}
