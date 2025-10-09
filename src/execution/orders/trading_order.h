#include <string>
#include "Order.h"

class TradingOrder {
    public: 
        static TradingOrder MarketOrder(const std::string& action, double quantity);

        static TradingOrder LimitOrder(const std::string& action, double quantity, double limitPrice);

        const Order& getOrder() const { return order; }

    private: 
        Order order;
};
