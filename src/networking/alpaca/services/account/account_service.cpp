#include "account_service.h"

Account AccountService::getAccount(bool refreshed) {
    if (!refreshed) return account; 
    httplib::Client client(env.URL); 
    auto data = client.Get("/account"); 
    account.account_id = data["user_id"]; 
    account.cash = data["cash"]; 
    account.currency = data["currency"]; 
    account.last_update = std::chrono::system_clock::now();
    account.status = ACTIVE;

    return account; 
}

bool AccountService::can_trade(double required_amount) {
   return account.status == ACTIVE && account.buying_power >= required_amount; 
}
