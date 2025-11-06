#include "time.hpp"

int64_t timeToi64(std::chrono::system_clock::time_point t) {
    using namespace std::chrono; 
    auto ns = time_point_cast<nanoseconds>(t).time_since_epoch();
    return ns.count(); 
}

int64_t parseTime(const nlohmann::json &data, const std::string &key) {
    if (!data.contains(key) || data[key].is_null()) return 0;

    std::string time = data[key].get<std::string>();
    // Trim Z at the end 
    time.erase(std::remove(time.begin(), time.end(), 'Z'), time.end());

    // Converting to whole seconds and fractional_seconds 
    size_t dot = time.find('.'); 
    std::string fractional_seconds;

    // If no dots, then we consider everything else to be whole seconds 
    if (dot == std::string::npos) {
        fractional_seconds = "0";
        dot = 0; 
    }
    else {
        fractional_seconds = time.substr(dot + 1);
    }
    std::string whole_seconds = time.substr(0, dot);

    // Parse whole seconds to tm struct 
    // convert it to seconds since epoch
    std::tm t = {}; 
    std::istringstream iss(whole_seconds); 
    if (!(iss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))) {
        return 0; 
    }

    // THIS FUNCTION WORKS ONLY ON LINUX (timegm)
    // we have to use another function for MacOS or Windows 
    // but I don't want to implement it because this runs 
    // strictly on linux 
    time_t epoch_seconds = timegm(&t); 
    while (fractional_seconds.size() < 9) {
        fractional_seconds += "0"; 
    }
    int64_t fractional_ns = std::stoll(fractional_seconds);

    int64_t ns = static_cast<int64_t>(epoch_seconds) * 1e9 + fractional_ns;
    return ns;
}
