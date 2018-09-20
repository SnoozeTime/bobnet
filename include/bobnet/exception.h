//
// Created by benoit on 18/09/21.
//

#ifndef SIMPLEHTTP_EXCEPTION_H
#define SIMPLEHTTP_EXCEPTION_H

#include <exception>
#include <string>
#include <curl/curl.h>

namespace bobnet {
    class BobnetException : public std::exception {
    public:
        explicit BobnetException(const char *message, CURLcode underlying_error_code = CURLE_OK);

        const char* what() const noexcept override;

    private:
        std::string message_;

        // This is the curl error. If 0, it will not be shown
        CURLcode underlying_error_;
    };
}

#endif //SIMPLEHTTP_EXCEPTION_H
