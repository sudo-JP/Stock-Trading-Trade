#include "config.h"
#include "http/httplib.h"
#include <cstdlib>
#include <chrono>

ENV getEnv() {
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

int64_t timeToi64(std::chrono::system_clock::time_point t) {
    using namespace std::chrono; 
    auto ns = time_point_cast<nanoseconds>(t).time_since_epoch();
    return ns.count(); 
}
