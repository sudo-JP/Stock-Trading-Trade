#include "json/json.hpp"
#include <chrono>
#ifndef _TIME_H_
#define _TIME_ 

int64_t parseTime(const nlohmann::json &data, const std::string &key);
int64_t timeToi64(std::chrono::system_clock::time_point t);

#endif 
