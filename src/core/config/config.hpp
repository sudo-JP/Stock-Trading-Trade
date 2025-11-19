#include <string> 
#include "http/httplib.h"
#include "json/json.hpp"
#ifndef _CONFIG_H_
#define _CONFIG_H_



class ENV {
    public:
        const std::string ALPACA_KEY; 
        const std::string ALPACA_SECRET_KEY; 
        const std::string URL;
        const std::string TCP_HOST;
        const std::string TCP_PORT;

        static ENV& getInstance() {
            static ENV instance; 
            return instance;
        }

    private: 

        ENV() : ALPACA_KEY(std::getenv("ALPACA_KEY") ? std::getenv("ALPACA_KEY") : ""),
        ALPACA_SECRET_KEY(std::getenv("ALPACA_SECRET_KEY") ? std::getenv("ALPACA_SECRET_KEY") : ""),
        URL(std::getenv("ALPACA_URL") ? std::getenv("ALPACA_URL") : ""),
        TCP_HOST(std::getenv("TCP_HOST") ? std::getenv("TCP_HOST") : ""),
        TCP_PORT(std::getenv("TCP_PORT") ? std::getenv("TCP_PORT") : "") 
        {}

        ENV(const ENV&) = delete;
        ENV& operator=(const ENV&) = delete;
}; 

ENV getEnv();

using json = nlohmann::json;

#endif
