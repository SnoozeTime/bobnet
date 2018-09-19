//
// Created by benoit on 18/09/13.
//

#include "response.h"

#include <string>
#include <algorithm>

namespace bobnet {

    void Headers::add(std::string header, std::string value) {
        headers_.emplace(header, std::move(value));
    }

    std::experimental::optional<std::string> Headers::header(const std::string& name) const {
        if (headers_.find(name) != headers_.end()) {
            return std::experimental::optional<std::string>{headers_.at(name)};
        }
        return std::experimental::nullopt;
    }

    HeaderPtr Headers::dump() const {
        curl_slist *chunk = nullptr;

        for (const auto& pair: headers_) {
            std::stringstream chunk_data_ss;
            chunk_data_ss << pair.first << ": " << pair.second;
            auto data = chunk_data_ss.str();
            chunk = curl_slist_append(chunk, data.c_str());
        }
        return HeaderPtr(chunk, &curl_slist_free_all);
    }

    const std::unordered_map<std::string, std::string>& Headers::headers() const { return headers_; }

    void Headers::parse_header(char *data, size_t size) {
        std::string header_str(data, size);
        size_t colon_idx = header_str.find(':');

        if (colon_idx < size-2) {
            // Need to remove extra \r\n.. TODO do it more cleanly.

            auto value = header_str.substr(colon_idx+1, size);
            value.erase(0, value.find_first_not_of(' '));
            value.erase(value.find_last_of('\n'), size);
            value.erase(value.find_last_of('\r'), size);
            add(header_str.substr(0, colon_idx), std::move(value));
        }
    }

    void Response::add_data(char *data, const size_t size) {
        buffer_ << std::string(data, size);
    }

    nlohmann::json Response::json() const {
        return nlohmann::json::parse(buffer_.str());
    }

    RequestBuilder::RequestBuilder(bobnet::http_request_type type, std::string uri): request_(type, std::move(uri)) {}
    RequestBuilder& RequestBuilder::setHeaders(bobnet::Headers headers) {
        request_.set_headers(std::move(headers));
        return *this;
    }

    RequestBuilder& RequestBuilder::json(const nlohmann::json &json) {
        // TODO replace magic strings
        request_.add_header("Content-Type", "application/json; charset=UTF-8");
        request_.set_content(json.dump());

        return *this;
    }
}