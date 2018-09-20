//
// Created by benoit on 18/09/21.
//

#include "options.h"

namespace bobnet {
    nlohmann::json Options::json() const {
        return json_;
    }

    Headers Options::headers() const {
        return headers_;
    }

    Options& Options::set_headers(const bobnet::Headers &headers) {
        headers_ = headers;
        return *this;
    }

    Options& Options::set_json(const nlohmann::json &json) {
        json_ = json;
        return *this;
    }
}