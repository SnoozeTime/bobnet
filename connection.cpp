//
// Created by benoit on 18/09/13.
//

#include "connection.h"
#include "response.h"
#include <iostream>

using namespace bobnet;

static size_t memory_cb(char *content, size_t size, size_t nmeb, void *userp) {
    size_t real_size = size * nmeb;
    auto resp = static_cast<Response *>(userp);

    resp->add_data(content, real_size);

    return real_size;
}

Response Connection::get(std::string url) {
    Response resp;
    curl_easy_setopt(handle_.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEFUNCTION, memory_cb);
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEDATA, static_cast<void *>(&resp));
    curl_easy_setopt(handle_.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0");

    auto res = curl_easy_perform(handle_.get());
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    return resp;
}
