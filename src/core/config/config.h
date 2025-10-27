#include <string> 
#include "http/httplib.h"
#include "json/json.hpp"
#ifndef _CONFIG_H_
#define _CONFIG_H_


/*template <typename T, size_t N>
inline constexpr size_t length_c_arr(T (&)[N]) {
    return N;
}*/


template<typename T>
inline T get_or_default(const nlohmann::json& data, const std::string& key, T default_value) {
    if (!data.contains(key) || data[key].is_null()) 
        return default_value; 
    try {
        return data[key].get<T>();
    } catch (...) {
        return default_value; 
    }
}

template <size_t N>
inline void safe_str_copy(char (&dest)[N], const nlohmann::json &j) {
    std::string s;
    if (j.is_string()) {
        s = j.get<std::string>();
    } else if (j.is_number()) {
        s = std::to_string(j.get<double>()); // converts numeric types to string
    } else {
        s = ""; // fallback
    }

    std::strncpy(dest, s.c_str(), N - 1);
    dest[N - 1] = '\0';
}

inline double json_to_double(const nlohmann::json &j, const std::string &key, double fallback = 0.0) {
    try {
        if (j[key].is_null()) return fallback;
        if (j[key].is_number()) return j[key].get<double>();
        if (j[key].is_string()) return std::stod(j[key].get<std::string>());
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
