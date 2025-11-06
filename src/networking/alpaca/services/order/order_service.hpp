#include "networking/alpaca/models/order_model.hpp"
#include "core/utils/common.hpp"
#include <future>
#include <vector>
#include "core/config/config.hpp"
#include "core/utils/time/time.hpp"
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
        std::future<OrderBinaryPayload> processOrder(OrderPayload order_payload);

        /*
         * @brief process multiple orders with populated data 
         * @param order_payloads The vector of payload 
         * @return Orders vector of promised order from async 
         * */
        std::vector<std::future<OrderBinaryPayload>> massProcess(std::vector<OrderPayload> order_payloads);

    private:
        OrderBinaryPayload processOrderSync(OrderPayload order_payload);
        const ENV env;
        const std::string route = "/v2/orders"; 
};

#endif 
