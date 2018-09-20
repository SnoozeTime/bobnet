//
// Created by benoit on 18/09/13.
//

#ifndef SIMPLEHTTP_BOBNET_H
#define SIMPLEHTTP_BOBNET_H

#include <string>
#include <curl/curl.h>
#include "response.h"
#include "connection.h"
#include "options.h"

namespace bobnet {

    // Curl needs to initialize the global state. This object should be created at the beginning of the program
    // and destroyed when no more HTTP requests will be done.
    class Context {
    public:
        Context() { curl_global_init(CURL_GLOBAL_ALL); }
        ~Context() { curl_global_cleanup(); }
    };

    RequestBuilder make_builder(http_request_type type, std::string uri);

    /// Perform a get request
    /// \param url
    /// \param options
    /// \return
    Response get(std::string url, Options options = Options());

    /// Perform a post request for the given URL and the given options
    /// \param url
    /// \param options (optional) additional options for the post request
    /// \return
    Response post(std::string url, Options options = Options());


    /// Overload of bobnet::post which add json as function parameter.
    /// \param url
    /// \param json
    /// \param options
    /// \return
    Response post(std::string url, nlohmann::json json, Options options = Options());

}


#endif //SIMPLEHTTP_BOBNET_H
