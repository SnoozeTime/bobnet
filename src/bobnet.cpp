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

    Response get(std::string url, Options options) {
        Connection conn;

        auto req = RequestBuilder(http_request_type::GET, std::move(url))
                .setHeaders(options.headers())
                .request();
        return conn.perform(req);
    }

    Response post(std::string url, Options options) {
        Connection conn;

        auto req_builder = RequestBuilder(http_request_type::POST, std::move(url)).setHeaders(options.headers());
        auto json = options.json();
        if (!json.empty()) {
            req_builder.json(json);
        }
        auto req = req_builder.request();
        return conn.perform(req);
    }

    Response post(std::string url, nlohmann::json json, Options options) {
        options.set_json(json);
        return post(std::move(url), options);
    }
}