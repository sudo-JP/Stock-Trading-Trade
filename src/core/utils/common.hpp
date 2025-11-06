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

#endif 
