//
// Created by benoit on 18/09/13.
//

#ifndef SIMPLEHTTP_CONNECTION_H
#define SIMPLEHTTP_CONNECTION_H

#include <curl/curl.h>
#include <memory>
#include <string>

namespace bobnet {

    class Response;

    // Connection will have one CURL handle that can be reused for
    // multiple requests.
    class Connection {
    public:
        Connection(): handle_(curl_easy_init(), &curl_easy_cleanup) {}

        Response get(std::string url);
    private:
        using HandlePtr = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>;

        HandlePtr handle_;
    };
}

#endif //SIMPLEHTTP_CONNECTION_H
