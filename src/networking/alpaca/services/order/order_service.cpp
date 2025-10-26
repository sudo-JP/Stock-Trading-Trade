#include "order_service.h"
#include <future>

OrderBinaryPayload OrderService::process_order(OrderPayload order_payload) {
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 

    OrderBinaryPayload order; 
    json payload = {
        { "symbol", order_payload.symbol }, 
        { "qty", order_payload.qty }, 
        { "side", order_payload.side }, 
        { "type", order_payload.type },
        { "time_in_force", order_payload.time_in_force }
    }; 

    auto res = client.Post(route, headers, payload.dump(), "application/json"); 

    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return order;
    }

    //order.created_at = time_to_i64(std::chrono::system_clock::now());

    try {

        json data = json::parse(res->body);

        if (data["filled_at"].is_null()) {
            // Handle the case where the order hasn't been filled
        } else {
            // Convert the timestamp to your desired format
        }
        safe_str_copy(order.id, data["id"]);
        safe_str_copy(order.client_order_id, data["client_order_id"]);
        safe_str_copy(order.symbol, data["symbol"]);
        safe_str_copy(order.side, data["side"]);
        safe_str_copy(order.type, data["type"]);
        order.qty = std::stoi(data["qty"].get<std::string>());
        order.filled_qty = std::stoi(data["filled_qty"].get<std::string>());
        // filled avg price 
        //order.time_in_force = data["time_in_force"];

    } catch (const std::exception &e){
        std::cerr << "Failed to parse JSON for order: " << e.what() << std::endl;
    }

    return order; 
}


std::vector<std::future<OrderBinaryPayload>> OrderService::mass_process(std::vector<OrderPayload> order_payloads) {
    std::vector<std::future<OrderBinaryPayload>> futures; 
    int n = order_payloads.size();

    for (OrderPayload &payload : order_payloads) {
        futures.push_back(std::async(std::launch::async, [this, payload] {
            return this->process_order(payload);
        }));
    }

    return futures; 
}

