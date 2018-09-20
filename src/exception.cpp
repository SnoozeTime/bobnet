//
// Created by benoit on 18/09/21.
//

#include "exception.h"
#include <sstream>
#include <iostream>

namespace bobnet {
    BobnetException::BobnetException(const char *message, CURLcode underlying_error_code):
        message_(message),
        underlying_error_(underlying_error_code){
    }

    const char* BobnetException::what() const noexcept {
        std::stringstream ss;
        std::cout << "BIM\n";
        ss << message_;
        if (underlying_error_ != 0) {
            ss << " - Curl error: " << curl_easy_strerror(underlying_error_);
        }

        return ss.str().c_str();
    }
}