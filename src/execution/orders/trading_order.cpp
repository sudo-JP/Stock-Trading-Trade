#include "trading_order.h"


TradingOrder TradingOrder::MarketOrder(const std::string& action, double quantity,
        const std::string& timeInForce) {

   TradingOrder to;  
   to.order.orderType = "MKT";
   to.order.action = action; 
   to.order.totalQuantity = quantity;
   to.order.tif = timeInForce; 
   return to; 
}
