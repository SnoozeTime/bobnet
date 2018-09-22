//
// Created by benoit on 18/09/21.
//

#include "exception.h"
#include <sstream>
#include <iostream>

namespace bobnet {
    BobnetException::BobnetException(const char *message, CURLcode underlying_error_code):
        message_(),
        underlying_error_(underlying_error_code){
        std::stringstream ss;
        ss << message;
        if (underlying_error_ != CURLE_OK) {
            ss << " - CURL error: " << curl_easy_strerror(underlying_error_);
        }
        message_ = ss.str();
    }

    const char* BobnetException::what() const noexcept {
        return message_.c_str();
    }
}