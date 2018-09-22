//
// Binance API. Use the public REST api to get data from Binance exchange
// Without error handling :)
//

#include "bobnet/bobnet.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;
class Binance {

public:
    json get_exchange_info() {
        return get("exchangeInfo");
    }

    json get_ticker(const std::string& symbol) {
        std::stringstream ss;
        ss << "ticker/24hr?symbol=" << symbol;
        return get(ss.str().c_str());
    }

private:
    // Will reuse the handle! If the connection is not closed by the server, it will
    // reuse the same TCP connection.
    bobnet::Connection conn{};

    constexpr static const char* url = "https://www.binance.com/api/v1/";

    json get(const char* endpoint) {
        std::stringstream ss;
        ss << url << endpoint;
        auto req = bobnet::make_builder(bobnet::http_request_type::GET, ss.str()).request();
        auto resp = conn.perform(req);
        return resp.json();
    }

};

int main() {
    bobnet::Context cleanup;

    Binance binance;

    std::cout << "Exchange info:\n" << binance.get_exchange_info() << std::endl;
    std::cout << "Ticker ETH-BTC:\n" << binance.get_ticker("ETHBTC") << std::endl;
}