#include <string> 
#include "http/httplib.h"
#include "json/json.hpp"
#ifndef _CONFIG_H_
#define _CONFIG_H_


/*template <typename T, size_t N>
inline constexpr size_t length_c_arr(T (&)[N]) {
    return N;
}*/

template <size_t N>
inline void safe_str_copy(char (&dest)[N], const std::string &src) {
    std::strncpy(dest, src.c_str(), N - 1);
    dest[N - 1] = '\0';
}

inline double json_to_double(const nlohmann::json &j, double fallback = 0.0) {
    try {
        if (j.is_number()) return j.get<double>();
        if (j.is_string()) return std::stod(j.get<std::string>());
    } catch (...) {
    }
    return fallback;
}

int64_t time_to_i64(std::chrono::system_clock::time_point t);

typedef struct env_t {
    const std::string ALPACA_KEY; 
    const std::string ALPACA_SECRET_KEY; 
    const std::string URL;
    const std::string TCP_HOST;
    const std::string TCP_PORT;
} ENV; 

ENV get_env();

using json = nlohmann::json;

#endif
