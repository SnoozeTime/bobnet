//
// Created by benoit on 18/09/13.
//

#include "connection.h"
#include "response.h"
#include <iostream>
#include <cassert>
#include <exception.h>

using namespace bobnet;

/// Verify CURL code is OK. If not, will throw an exception. This is triggered by recoverable user
/// error. Code bug should not be using this one (for example, setting the write function should never
/// fail...)
/// \param code
/// \param details
inline void throw_if_err(CURLcode code, const char* details) {
    if (code != CURLE_OK) {
        throw BobnetException(details, code);
    }
}

/// Same as above but for non-recoverable errors
/// \param code
inline void assert_ok(CURLcode code) {
    assert(code == CURLE_OK);
}
static size_t write_body_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    resp->add_data(content, real_size);
    return real_size;
}

// Get header and status code...
static size_t write_header_cb(char *content, size_t size, size_t nmeb, Response *resp) {
    size_t real_size = size * nmeb;
    std::string http_header_str(content, real_size);
    resp->headers().parse_header(content, real_size);

    return real_size;
}

// for external sockets

static int closecb(void *clientp, curl_socket_t item)
{
    (void)clientp;
    printf("libcurl wants to close %d now\n", (int)item);
    return 0;
}

static curl_socket_t opensocket(void *clientp,
                                curlsocktype purpose,
                                struct curl_sockaddr *address)
{
    curl_socket_t sockfd;
    (void)purpose;
    (void)address;
    sockfd = *(curl_socket_t *)clientp;
    /* the actual externally set socket is passed in via the OPENSOCKETDATA
       option */
    return sockfd;
}

static int sockopt_callback(void *clientp, curl_socket_t curlfd,
                            curlsocktype purpose)
{
    (void)clientp;
    (void)curlfd;
    (void)purpose;
    /* This return code was added in libcurl 7.21.5 */
    return CURL_SOCKOPT_ALREADY_CONNECTED;
}

Response Connection::perform(const bobnet::Request& request) const {

    Response resp;
    long status_code;

    // This should never fail...
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_NOPROGRESS, 1L));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_WRITEFUNCTION, write_body_cb));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_WRITEDATA, &resp));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_HEADERFUNCTION, write_header_cb));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_HEADERDATA, &resp));
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0"));

    if (request.external_socket() != nullptr && *request.external_socket() != 1) {

        /* call this function to get a socket */
        assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_OPENSOCKETFUNCTION, opensocket));
        assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_OPENSOCKETDATA, request.external_socket()));

        /* call this function to close sockets */
        assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_CLOSESOCKETFUNCTION, closecb));
        assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_CLOSESOCKETDATA, request.external_socket()));

        /* call this function to set options for the socket */
        assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_SOCKOPTFUNCTION, sockopt_callback));
    }

    // Set by user
    throw_if_err(curl_easy_setopt(handle_.get(), CURLOPT_URL, request.uri().c_str()), "Set URL");
    auto header_data = request.headers().dump();
    if (header_data) {
        throw_if_err(curl_easy_setopt(handle_.get(), CURLOPT_HTTPHEADER, header_data.get()), "Set headers");
    }

    switch (request.type()) {
        case http_request_type::GET:
            get(request, resp);
            break;
        case http_request_type::POST:
            post(request, resp);
            break;
        default:
            assert(false);
    }

    throw_if_err(curl_easy_perform(handle_.get()), "curl_easy_perform() failed");

    curl_easy_getinfo(handle_.get(), CURLINFO_RESPONSE_CODE, &status_code);
    resp.set_status_code(status_code);
    return resp;
}

void Connection::get(const bobnet::Request& /*request*/, Response& /*resp*/) const {
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_HTTPGET, 1L));
}

void Connection::post(const bobnet::Request& request, Response& /*resp*/) const {
    assert_ok(curl_easy_setopt(handle_.get(), CURLOPT_POST, 1L));

    if (!request.content().empty()) {
        throw_if_err(curl_easy_setopt(handle_.get(), CURLOPT_POSTFIELDS, request.content().c_str()), "Set body");
    }
}
