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
inline T getOrDefault(const nlohmann::json& data, const std::string& key, T default_value) {
    if (!data.contains(key) || data[key].is_null()) 
        return default_value; 
    try {
        return data[key].get<T>();
    } catch (...) {
        return default_value; 
    }
}

template <size_t N>
inline void safeStrcpy(char (&dest)[N], const nlohmann::json &j) {
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

inline double jsonToDouble(const nlohmann::json &j, const std::string &key, double fallback = 0.0) {
    try {
        if (j[key].is_null()) return fallback;
        if (j[key].is_number()) return j[key].get<double>();
        if (j[key].is_string()) return std::stod(j[key].get<std::string>());
    } catch (...) {
    }
    return fallback;
}

inline int64_t parseTime(const nlohmann::json &data, const std::string &key) {
    if (data[key].is_null()) {
        return 0; 
    } 
    std::string time = data[key]; 
    time.erase(std::remove(time.begin(), time.end(), 'Z'), time.end()); 
    std::istringstream iss(time); 
    std::tm t = {};

    if (!(iss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))) {
        return 0; 
    }
    time_t epoch = timegm(&t); 
    auto tp = std::chrono::system_clock::from_time_t(epoch);
    auto ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(tp)
              .time_since_epoch()
              .count();

    return ns; 
}
int64_t timeToi64(std::chrono::system_clock::time_point t);


template<typename T>
inline constexpr int32_t statusTouint32(T status) {
    return static_cast<int32_t>(status);
}

typedef struct env_t {
    const std::string ALPACA_KEY; 
    const std::string ALPACA_SECRET_KEY; 
    const std::string URL;
    const std::string TCP_HOST;
    const std::string TCP_PORT;
} ENV; 

ENV getEnv();

using json = nlohmann::json;

#endif
