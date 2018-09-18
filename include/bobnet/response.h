//
// Created by benoit on 18/09/13.
//

#ifndef SIMPLEHTTP_RESPONSE_H
#define SIMPLEHTTP_RESPONSE_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <experimental/optional>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

namespace bobnet {

    // Curl object to store the pointer data. Wrap it in a smart pointer to not worry about resource cleanup
    using HeaderPtr = std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)>;

    class Headers {
    public:
        Headers(): headers_() {}

        // add a header to the existing headers. Will overwrite if already exists
        void add(std::string header, std::string value);

        // Get view-only headers map
        const std::unordered_map<std::string, std::string>& headers() const;

        // get header value if exist
        std::experimental::optional<std::string> header(const std::string& name) const;

        // Complete header line should be given to this function.
        // It will parse the header and add it to the headers_ map
        void parse_header(char* data, size_t size);

        // Will dump the header as curl objects. Or nothing is no header.
        HeaderPtr dump() const;
    private:
        std::unordered_map<std::string, std::string> headers_;
    };

    enum class http_request_type {
        GET,
        POST,
    };

    // Input of an HTTP request.
    class Request {
    public:
        Request(http_request_type type, std::string uri):
            type_(type),
            uri_(std::move(uri)),
            headers_(),
            content_() {}

        void set_headers(Headers headers) { headers_ = std::move(headers); }
        void set_content(std::string content) { content_ = std::move(content); }
        void add_header(std::string key, std::string value) { headers_.add(std::move(key), std::move(value));}

        http_request_type type() const { return type_; }
        const std::string& uri() const { return uri_; }
        const std::string& content() const { return content_; }
        const Headers& headers() const { return headers_; }
    private:
        http_request_type type_;
        std::string uri_;
        Headers headers_;

        // In case of POST request, this is the body ;)
        std::string content_;
    };


    // Create easily a request
    class RequestBuilder {
    public:

        RequestBuilder(http_request_type type, std::string uri);

        // set the headers of the request and return a reference of this object.
        RequestBuilder& setHeaders(Headers headers);

        // Set content as json file, and add the correct header
        RequestBuilder& json(const nlohmann::json& json);

        // Return a copy of the request. This can be reused later.
        Request request() const { return request_; }
    private:
        Request request_;
    };

    class Response {
    public:
        Response(): buffer_(), headers_(), status_code_() {}

        std::string text() const { return buffer_.str(); }

        // This is called to add data at the end of our buffer.
        void add_data(char* data, size_t size);

        const Headers& headers() const {return headers_;};
        Headers& headers() {return headers_;};

        void set_status_code(long status_code) {status_code_ = status_code;}
        long status_code() { return status_code_;}
    private:
        std::stringstream buffer_;
        Headers headers_;
        long status_code_;

    };
}

#endif //SIMPLEHTTP_RESPONSE_H
