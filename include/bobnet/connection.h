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
    class Request;

    // Connection will have one CURL handle that can be reused for
    // multiple requests.
    class Connection {
    public:
        Connection(): handle_(curl_easy_init(), &curl_easy_cleanup) {}

        // Process an HTTP request. Build the request with RequestBuilder.
        Response process(const Request& request);
    private:
        using HandlePtr = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>;
        HandlePtr handle_;


        Response get(const Request& request);
        Response post(const Request& request);
    };
}

#endif //SIMPLEHTTP_CONNECTION_H
