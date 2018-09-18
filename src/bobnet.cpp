//
// Created by benoit on 18/09/13.
//

#include "bobnet.h"
#include "connection.h"
#include "response.h"
namespace bobnet {
    RequestBuilder make_builder(http_request_type type, std::string uri) {
        return RequestBuilder(type, std::move(uri));
    }

    Response get(std::string url) {
        Connection conn;

        auto req = RequestBuilder(http_request_type::GET, std::move(url)).request();
        return conn.perform(req);
    }

    Response post(std::string url) {
        Connection conn;

        auto req = RequestBuilder(http_request_type::POST, std::move(url)).request();
        return conn.perform(req);
    }
}