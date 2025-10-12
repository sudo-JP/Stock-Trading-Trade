#include <string>
#include "Order.h"

class TradingOrder {
    public: 

        TradingOrder(const std::string& action, double quantity, const std::string& timeInForce = "DAY"); 

        /**
        * @brief Creates a market order for immediate execution
        * @param action "BUY" or "SELL"
        * @param quantity Number of shares/contracts (must be positive)
        * @param timeInForce Order duration ("DAY", "GTC", "IOC", etc.)
        * @return TradingOrder configured as a market order
        */
        static TradingOrder MarketOrder(const std::string& action, double quantity,
                const std::string& timeInForce = "DAY");

        /**
        * @brief Creates a limit order for price-controlled execution
        * @param action "BUY" or "SELL" 
        * @param quantity Number of shares/contracts (must be positive)
        * @param limitPrice The maximum/minimum execution price
        * @param timeInForce Order duration ("DAY", "GTC", "IOC", etc.)
        * @return TradingOrder configured as a limit order
        */
        static TradingOrder LimitOrder(const std::string& action, double quantity, 
                double limitPrice, const std::string& timeInForce);

        /*
         * @brief gets the order object 
         * @return the order object
         * */
        const Order& getOrder() const { return order; }

        /*
         * @brief check if the trading order is valid 
         * @return bool true if valid 
         * */
        bool isValid() const; 

    private: 
        Order order;
};
