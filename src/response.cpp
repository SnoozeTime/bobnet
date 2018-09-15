//
// Created by benoit on 18/09/13.
//

#include "response.h"
#include <string>

namespace bobnet {

    void Headers::add(std::string header, std::string value) {
        headers_.emplace(header, std::move(value));
    }

    const std::unordered_map<std::string, std::string>& Headers::headers() const { return headers_; }

    void Headers::parse_header(char *data, size_t size) {
        std::string header_str(data, size);
        size_t colon_idx = header_str.find(':');

        if (colon_idx < size-2) {
            // Need to remove extra \r\n.. TODO do it more cleanly.
            add(header_str.substr(0, colon_idx), header_str.substr(colon_idx, size-2));
        }
    }

    void Response::add_data(char *data, const size_t size) {
        buffer_ << std::string(data, size);
    }

    RequestBuilder::RequestBuilder(bobnet::http_request_type type, std::string uri): request_(type, std::move(uri)) {}
    RequestBuilder& RequestBuilder::setHeaders(bobnet::Headers headers) {
        request_.set_headers(std::move(headers));
        return *this;
    }
}