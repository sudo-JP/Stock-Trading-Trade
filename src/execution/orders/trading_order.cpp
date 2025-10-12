#include "trading_order.h"

TradingOrder::TradingOrder(const std::string& action, double quantity, const std::string& timeInForce) {
   order.action = action; 
   order.totalQuantity = quantity; 
   order.tif = timeInForce; 
}


TradingOrder TradingOrder::MarketOrder(const std::string& action, double quantity,
        const std::string& timeInForce) {

   TradingOrder to = TradingOrder(action, quantity, timeInForce);  
   to.order.orderType = "MKT";
   return to; 
}

TradingOrder TradingOrder::LimitOrder(const std::string& action, double quantity, 
                double limitPrice, const std::string& timeInForce) {

   TradingOrder to = TradingOrder(action, quantity, timeInForce); 
   to.order.orderType = "LMT";
   to.order.lmtPrice = limitPrice; 
   return to;
}
