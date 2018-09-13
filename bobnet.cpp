//
// Created by benoit on 18/09/13.
//

#include "bobnet.h"
#include "connection.h"

namespace bobnet {

    Response get(std::string url) {
        Connection conn;
        return conn.get(std::move(url));
    }
}