#include "account_service.h"
#include <cstring>
#include <boost/algorithm/string.hpp>

/*
 *
struct AccountBinaryPayload {
    char account_id[64];     
    char currency[4];         

    double cash;            
    double buying_power;   
    double equity;        
    double portfolio_value;   

    double effective_buying_power;   
    double daytrading_buying_power; 
    double regt_buying_power;      
    double non_marginable_buying_power; 
    double last_equity;              
    double sma;                     
    double position_market_value;    
    double long_market_value;       
    double short_market_value;     

    // Metadata
    uint32_t status;
    int64_t balance_asof;
    int32_t daytrade_count;
};
 * */

AccountStatus getStatus(std::string &status) {
    if (status == "ACTIVE") return AccountStatus::ACTIVE; 
    else if (status == "REJECTED") return AccountStatus::REJECTED; 
    else if (status == "APPROVAL_PENDING") return AccountStatus::APPROVAL_PENDING; 
    else if (status == "ACCOUNT_UPDATED") return AccountStatus::ACCOUNT_UPDATED;
    else if (status == "SUBMITTED") return AccountStatus::SUBMITTED; 
    else if (status == "SUBMISSION_FAILED") return AccountStatus::SUBMISSION_FAILED;
    else if (status == "ONBOARDING") return AccountStatus::ONBOARDING;
    else return AccountStatus::UNKNOWN;
}

AccountBinaryPayload AccountService::getAccountSync(bool refreshed) {
    if (!refreshed) return account; 
    
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 

    auto res = client.Get(route, headers); 

    // Error respond 
    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return account;
    }

    // Parse to json 
    try {
        json data = json::parse(res->body); 

        // id and currency
        safeStrcpy(account.account_id, getOrDefault(data, "id", "id")); 
        safeStrcpy(account.currency, getOrDefault(data, "currency", "USD"));

        // Estimate numeric 
        account.effective_buying_power = jsonToDouble(data, "effective_buying_power"); 
        account.daytrading_buying_power = jsonToDouble(data, "daytrading_buying_power"); 
        account.regt_buying_power = jsonToDouble(data, "regt_buying_power"); 
        account.non_marginable_buying_power = jsonToDouble(data, "non_marginable_buying_power"); 

        // Futures
        account.last_equity = jsonToDouble(data, "last_equity"); 
        account.sma = jsonToDouble(data, "sma"); 
        account.position_market_value = jsonToDouble(data, "position_market_value"); 
        account.long_market_value = jsonToDouble(data, "long_market_value"); 
        account.short_market_value = jsonToDouble(data, "short_market_value"); 

        // Owned numeric 
        account.cash = jsonToDouble(data, "cash");
        account.buying_power = jsonToDouble(data, "buying_power");
        account.equity = jsonToDouble(data, "equity");
        account.portfolio_value = jsonToDouble(data, "portfolio_value");

        // Metadata 
        std::string status = getOrDefault(data, "status", ""); 
        account.status = statusTouint32(getStatus(status));
        std::string crypto_status = getOrDefault(data, "crypto_status", ""); 
        account.crypto_status = statusTouint32(getStatus(crypto_status));
        account.balance_asof = timeToi64(std::chrono::system_clock::now());
        account.daytrade_count = jsonToDouble(data, "daytrade_count"); 

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
