#include "account_service.h"
#include <cstring>
#include <boost/algorithm/string.hpp>

AccountBinaryPayload AccountService::getAccountSync(bool refreshed) {
    if (!refreshed) return account; 
    account.last_update = timeToi64(std::chrono::system_clock::now());
    
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 

    auto res = client.Get(route, headers); 
    account.status = statusTouint32(BinaryStatus::INACTIVE);

    // Error respond 
    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return account;
    }

    // Parse to json 
    try {
        json data = json::parse(res->body); 

        safeStrcpy(account.account_id, getOrDefault(data, "id", "id")); 

        account.status = boost::iequals(getOrDefault(data, "status", "ACTIVE"), "ACTIVE") 
            ? statusTouint32(BinaryStatus::ACTIVE)
            : statusTouint32(BinaryStatus::INACTIVE);
    
        safeStrcpy(account.currency, getOrDefault(data, "currency", "USD"));

        account.cash = jsonToDouble(data, "cash");
        account.buying_power = jsonToDouble(data, "buying_power");
        account.portfolio_value = jsonToDouble(data, "portfolio_value");
        
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return account;
    }

    return account; 
}

std::future<AccountBinaryPayload> AccountService::getAccount(bool refreshed) {
    return std::async(std::launch::async, [this, refreshed]() {
        return this->getAccountSync(refreshed);
    });
}

bool AccountService::canTrade(double required_amount) {
   return account.status == statusTouint32(BinaryStatus::ACTIVE) && account.buying_power >= required_amount; 
}
