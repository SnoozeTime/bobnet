//
// Created by benoit on 18/09/13.
//

#include "bobnet.h"
#include "connection.h"
#include "response.h"
namespace bobnet {

    Response get(std::string url) {
        Connection conn;

        auto req = RequestBuilder(http_request_type::GET, std::move(url)).request();
        return conn.process(req);
    }
}