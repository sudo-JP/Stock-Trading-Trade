#include "order_model.h"
#include <future>
#include <vector>
#include "config.h"
#ifndef _ORDER_SERVICE_H
#define _ORDER_SERVICE_H

class OrderService {
    public: 
        OrderService(const ENV env_t) : env(env_t) {};

        /*
         * @brief process an order given a populated payload 
         * @param order_payload The payload to be sent 
         * @return Order populated with info
         * */
        Order process_order(OrderPayload order_payload);

        /*
         * @brief process multiple orders with populated data 
         * @param order_payloads The vector of payload 
         * @return Orders vector of promised order from async 
         * */
        std::vector<std::future<Order>> mass_process(std::vector<OrderPayload> order_payloads);

    private:
        const ENV env;
        const std::string route = "/v2/orders"; 
};

#endif 
