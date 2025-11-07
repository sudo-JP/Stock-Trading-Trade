#include <string>
#include "json/json.hpp"
#ifndef _COMMON_H_
#define _COMMON_H_

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



template<typename T>
inline constexpr int32_t statusTouint32(T status) {
    return static_cast<int32_t>(status);
}
#endif 
