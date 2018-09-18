//
// Created by benoit on 18/09/13.
//

#ifndef SIMPLEHTTP_BOBNET_H
#define SIMPLEHTTP_BOBNET_H

#include <string>
#include <curl/curl.h>
#include "response.h"
#include "connection.h"

namespace bobnet {

    // Curl needs to initialize the global state. This object should be created at the beginning of the program
    // and destroyed when no more HTTP requests will be done.
    class Context {
    public:
        Context() { curl_global_init(CURL_GLOBAL_ALL); }
        ~Context() { curl_global_cleanup(); }
    };

    RequestBuilder make_builder(http_request_type type, std::string uri);

    Response get(std::string url);
    Response post(std::string url);

}


#endif //SIMPLEHTTP_BOBNET_H
