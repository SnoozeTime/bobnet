//
// Created by benoit on 18/09/21.
//

#ifndef SIMPLEHTTP_OPTIONS_H
#define SIMPLEHTTP_OPTIONS_H

#include "response.h"
#include <nlohmann/json.hpp>

namespace bobnet {

    /// Option to give to the get and post method of the main API.
    /// Options can be chained to specify more options.
    class Options {

    public:
        Options() = default;

        Options& set_json(const nlohmann::json& json);
        Options& set_headers(const Headers& headers);
        nlohmann::json json() const;
        Headers headers() const;
    private:
        nlohmann::json json_{nlohmann::json()};
        Headers headers_{Headers()};
    };
}

#endif //SIMPLEHTTP_OPTIONS_H
