#include "trade_contract.h"

TradingContract TradingContract::Stock(const std::string& symbol, const std::string& exchange, const std::string& currency) {

    return TradingContract(symbol, "STK", exchange, currency); 

}
