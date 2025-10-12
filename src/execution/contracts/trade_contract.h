#include "Contract.h"
#include <string>

class TradingContract {
    public: 
        TradingContract(const std::string& symbol, const std::string& secType,
                const std::string& exchange, const std::string& currency);
        
        const Contract &getContract() const { return contract; }

        // Create a stock contract 
        static TradingContract Stock(const std::string& symbol, const std::string& exchange, const std::string& currency);

        /* @brief Create an option contract
        * @param symbol 
        * @param expiry in format of YYYYMMDD
        * @param strike The strike price 
        * @param exchange The exchange type 
        * */
        static TradingContract Option(const std::string& symbol, const std::string& expiry, double strike, const std::string& right, const std::string& exchange);

        /*
         * @brief check if contract is valid
         * @return True if contract is valud
         * */
        bool isValid() const; 

    private: 
        Contract contract; 
};
