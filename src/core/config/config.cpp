#include "config.h"
#include "http/httplib.h"
#include <cstdlib>

ENV get_env() {
    const char* api_key = std::getenv("ALPACA_KEY");
    const char* secret_key = std::getenv("ALPACA_SECRET_KEY");
    const char* url = std::getenv("ALPACA_URL");
    
    return ENV {
        std::string(api_key ? api_key : ""),
        std::string(secret_key ? secret_key : ""),
        std::string(url ? url : ""),
    };
}
