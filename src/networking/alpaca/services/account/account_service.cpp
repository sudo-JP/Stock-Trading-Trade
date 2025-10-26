#include "account_service.h"
#include <cstring>
#include <boost/algorithm/string.hpp>

AccountBinaryPayload AccountService::getAccount(bool refreshed) {
    if (!refreshed) return account; 
    account.last_update = time_to_i64(std::chrono::system_clock::now());
    
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 

    auto res = client.Get(route, headers); 
    account.status = status_to_uint32(BinaryStatus::INACTIVE);

    // Error respond 
    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return account;
    }

    // Parse to json 
    try {
        json data = json::parse(res->body); 

        safe_str_copy(account.account_id, data["id"]); 

        account.status = boost::iequals(data["status"], "ACTIVE") 
            ? status_to_uint32(BinaryStatus::ACTIVE)
            : status_to_uint32(BinaryStatus::INACTIVE);
    
        safe_str_copy(account.currency, data["currency"]);

        account.cash = json_to_double(data["cash"]);
        account.buying_power = json_to_double(data["buying_power"]);
        account.portfolio_value = json_to_double(data["portfolio_value"]);
        
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return account;
    }

    return account; 
}

bool AccountService::can_trade(double required_amount) {
   return account.status == status_to_uint32(BinaryStatus::ACTIVE) && account.buying_power >= required_amount; 
}
