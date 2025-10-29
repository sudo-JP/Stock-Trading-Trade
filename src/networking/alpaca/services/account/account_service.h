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
        bool can_trade(double required_amount = 0.0);

        /**
        * @brief Gets current buying power with safety margin
        * @param safety_margin Percentage buffer to reserve (e.g., 0.1 for 10%)
        * @return Available buying power after safety margin
        * @warning Does not consider pending orders - check order manager for accuracy
        */
        double get_available_buying_power(double safety_margin = 0.05);

        /**
        * @brief Calculates daily profit/loss performance
        * @return PnLData containing absolute and percentage change
        * @note Uses last_equity vs current_equity from account data
        */
        PnLData get_daily_performance();   // need to wait for TCP connections for getting data from rust back end 

        /**
        * @brief Quick health check of account connectivity and basic status
        * @return true if API is reachable and account is accessible
        * @throws AlpacaAPIException if authentication fails or account not found
        */
        bool health_check();


    private: 
        AccountBinaryPayload getAccountSync(bool refreshed = false); 
        AccountBinaryPayload account; 
        const ENV env; 
        const std::string route = "/v2/account"; 
};

#endif
