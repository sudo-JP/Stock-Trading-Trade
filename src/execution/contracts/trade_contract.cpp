#include "trade_contract.h"

TradingContract::TradingContract(const std::string& symbol, const std::string& secType,
                const std::string& exchange, const std::string& currency) {
    contract.symbol = symbol;
    contract.secType = secType; 
    contract.exchange = exchange;
    contract.currency = currency;
}

TradingContract TradingContract::Stock(const std::string& symbol, const std::string& exchange, const std::string& currency) {
    return TradingContract(symbol, "STK", exchange, currency); 

}

TradingContract TradingContract::Option(const std::string& symbol, const std::string& expiry, double strike, const std::string& right, const std::string& exchange) {

    TradingContract contract = TradingContract(symbol, "OPT", exchange, "USD");
    contract.contract.multiplier = "100";
    contract.contract.strike = strike; 
    contract.contract.right = right; 
    contract.contract.lastTradeDateOrContractMonth = expiry; 
    return contract;
}
