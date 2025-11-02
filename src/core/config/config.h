#include <string> 
#include "http/httplib.h"
#include "json/json.hpp"
#ifndef _CONFIG_H_
#define _CONFIG_H_


/*template <typename T, size_t N>
inline constexpr size_t length_c_arr(T (&)[N]) {
    return N;
}*/



inline std::string getOrDefault(const nlohmann::json &data, const std::string &key, const std::string &def = "") {
    if (data.contains(key) && data[key].is_string())
        return data[key].get<std::string>();
    return def;
}

inline bool getOrDefault(const nlohmann::json &data, const std::string &key, bool def) {
    if (data.contains(key) && data[key].is_boolean())
        return data[key].get<bool>();
    return def;
}
template <size_t N>
inline void safeStrcpy(char (&dest)[N], const std::string &s) {
    std::strncpy(dest, s.c_str(), N - 1);
    dest[N - 1] = '\0';
}


template <typename T>
inline T jsonToNumber(const nlohmann::json &j, const std::string &key, T fallback = T{}) {
    try {
        if (j[key].is_null()) return fallback;
        if (j[key].is_number()) return j[key].get<T>();
        if (j[key].is_string()) return static_cast<T>(std::stod(j[key].get<std::string>()));
    } catch (...) {}
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
