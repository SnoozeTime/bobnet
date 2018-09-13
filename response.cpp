//
// Created by benoit on 18/09/13.
//

#include "response.h"
#include <string>

namespace bobnet {
    void Response::add_data(char *data, const size_t size) {
        buffer_ << std::string(data, size);
    }
}