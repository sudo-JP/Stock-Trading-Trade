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

    private: 
        AccountBinaryPayload getAccountSync(bool refreshed = false); 
        AccountBinaryPayload account; 
        const ENV env; 
        const std::string route = "/v2/account"; 
};

#endif
