#include "account_service.hpp"
#include <boost/algorithm/string.hpp>

AccountBinaryPayload AccountService::getAccountSync(bool refreshed) {
    if (!refreshed) return account; 
    
    httplib::SSLClient client(env.URL, 443); 
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
        safeStrcpy(account.id, std::string(getOrDefault(data, "id", std::string("")))); 
        safeStrcpy(account.currency, std::string(getOrDefault(data, "currency", std::string("USD"))));

        // Estimate numeric 
        account.effective_buying_power = jsonToNumber<double>(data, "effective_buying_power"); 
        account.daytrading_buying_power = jsonToNumber<double>(data, "daytrading_buying_power"); 
        account.regt_buying_power = jsonToNumber<double>(data, "regt_buying_power"); 
        account.non_marginable_buying_power = jsonToNumber<double>(data, "non_marginable_buying_power"); 

        // Futures
        account.last_equity = jsonToNumber<double>(data, "last_equity"); 
        account.sma = jsonToNumber<double>(data, "sma"); 
        account.position_market_value = jsonToNumber<double>(data, "position_market_value"); 
        account.long_market_value = jsonToNumber<double>(data, "long_market_value"); 
        account.short_market_value = jsonToNumber<double>(data, "short_market_value"); 

        // Owned numeric 
        account.cash = jsonToNumber<double>(data, "cash");
        account.buying_power = jsonToNumber<double>(data, "buying_power");
        account.equity = jsonToNumber<double>(data, "equity");
        account.portfolio_value = jsonToNumber<double>(data, "portfolio_value");

        // Metadata 
        safeStrcpy(account.status, std::string(getOrDefault(data, "status", std::string("UNKNOWN")))); 
        std::string crypto_status = std::string(getOrDefault(data, "crypto_status", std::string(""))); 
        safeStrcpy(account.crypto_status, std::string(getOrDefault(data, "status", std::string("UNKNOWN")))); 
        account.balance_asof = timeToi64(std::chrono::system_clock::now());
        account.daytrade_count = jsonToNumber<double>(data, "daytrade_count"); 

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

