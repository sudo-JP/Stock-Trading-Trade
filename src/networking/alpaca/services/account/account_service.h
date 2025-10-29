#include "networking/alpaca/models/account_model.h"
#include <future>
#include <string>
#include "core/config/config.h"
#ifndef _ACCOUNT_SERVICE_H_
#define _ACCOUNT_SERVICE_H_
class AccountService {
    public: 
        AccountService(const ENV t_env) : env(t_env) {}

        /**
        * @brief Fetches complete account information from Alpaca API
        * @return Account struct populated with current account data
        * @note Rate limited by Alpaca, avoid frequent calls
        */

        std::future<AccountBinaryPayload> getAccount(bool refreshed); 

        /**
        * @brief Checks if account is active and has sufficient buying power
        * @param required_amount Minimum buying power needed for intended trade
        * @return true if account can execute trades
        */
        bool canTrade(double required_amount = 0.0);



    private: 
        AccountBinaryPayload getAccountSync(bool refreshed = false); 
        AccountBinaryPayload account; 
        const ENV env; 
        const std::string route = "/v2/account"; 
};

#endif
