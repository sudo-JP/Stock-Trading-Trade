#include "account_service.h"
#include <boost/algorithm/string.hpp>

Account AccountService::getAccount(bool refreshed) {
    if (!refreshed) return account; 
    account.last_update = std::chrono::system_clock::now();
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 

    auto res = client.Get(route, headers); 
    account.status = Status::INACTIVE; 

    // Error respond 
    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return account;
    }

    // Parse to json 
    try {
        json data = json::parse(res->body); 

        account.account_id = data["id"]; 
        boost::iequals(data["status"], "ACTIVE") ? account.status = Status::ACTIVE : account.status = Status::INACTIVE;
    
        account.currency = data["currency"]; 
        account.cash = std::stod(data["cash"].get<std::string>());
        account.buying_power = std::stod(data["buying_power"].get<std::string>());
        account.portfolio_value = std::stod(data["portfolio_value"].get<std::string>());
        
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return account;
    }

    return account; 
}

bool AccountService::can_trade(double required_amount) {
   return account.status == Status::ACTIVE && account.buying_power >= required_amount; 
}
