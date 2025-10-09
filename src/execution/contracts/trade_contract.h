#include "Contract.h"
#include <string>

class TradingContract {
    public: 
        TradingContract(const std::string& symbol, const std:: string &secType,
                const std::string& exchange, const std::string& currency);
        
        const Contract &getContract() const { return contract; }

    private: 
        Contract contract; 
};
