#include "config.h"
#include "http/httplib.h"
#include <cstdlib>

ENV get_env() {
    const char *api_key = std::getenv("ALPACA_KEY");
    const char *secret_key = std::getenv("ALPACA_SECRET_KEY");
    const char *url = std::getenv("ALPACA_URL");
    const char *tcp_host = std::getenv("TCP_HOST");
    const char *tcp_port = std::getenv("TCP_PORT");
    
    return ENV {
        std::string(api_key ? api_key : ""),
        std::string(secret_key ? secret_key : ""),
        std::string(url ? url : ""),
        std::string(tcp_host ? tcp_host : ""),
        std::string(tcp_port ? tcp_port : ""),
    };
}
