//
// Created by benoit on 18/09/13.
//

#include "connection.h"
#include "response.h"
#include <iostream>

using namespace bobnet;

static size_t write_body_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    resp->add_data(content, real_size);
    return real_size;
}

// Get header and status code...
static size_t write_header_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    resp->headers().parse_header(content, real_size);
    return real_size;
}


Response Connection::get(std::string url) {
    Response resp;
    curl_easy_setopt(handle_.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEFUNCTION, write_body_cb);
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEDATA, &resp);
    curl_easy_setopt(handle_.get(), CURLOPT_HEADERFUNCTION, write_header_cb);
    curl_easy_setopt(handle_.get(), CURLOPT_HEADERDATA, &resp);
    curl_easy_setopt(handle_.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0");

    auto res = curl_easy_perform(handle_.get());
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    return resp;
}
