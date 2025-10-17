#include "order_model.h"
#include <vector>
#include "config.h"
#ifndef _ORDER_SERVICE_H
#define _ORDER_SERVICE_H

class OrderService {
    public: 
        OrderService(const ENV env_t) : env(env_t) {};

        Order process_order(OrderPayload payload);

        std::vector<Order> mass_process(std::vector<Order> payloads);

    private:
        const ENV env;
        const std::string route = "/v2/orders"; 
};

#endif 
