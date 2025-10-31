#include "order_service.h"
#include <future>
#include <chrono> 
#include <iomanip>


OrderBinaryPayload OrderService::processOrderSync(OrderPayload order_payload) {
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


    try {

        json data = json::parse(res->body);
        order.created_at = parseTime(data, "created_at");
        order.filled_at = parseTime(data, "filled_at");
        order.submitted_at = parseTime(data, "submitted_at");
        order.updated_at = parseTime(data, "updated_at");

        safeStrcpy(order.id, getOrDefault(data, "id", ""));
        safeStrcpy(order.client_order_id, getOrDefault(data, "client_order_id", ""));
        safeStrcpy(order.symbol, getOrDefault(data, "symbol", ""));
        safeStrcpy(order.side, getOrDefault(data, "side", ""));
        safeStrcpy(order.type, getOrDefault(data, "type", ""));


        std::string qty_str = getOrDefault<std::string>(data, "qty", "0");
        order.qty = std::stoi(qty_str);

        std::string filled_qty_str = getOrDefault(data, "filled_qty", "0"); 

        order.filled_qty = std::stoi(filled_qty_str);
        // filled avg price 
        safeStrcpy(order.time_in_force, getOrDefault(data, "time_in_force", "utc"));

    } catch (const std::exception &e){
        std::cerr << "Failed to parse JSON for order: " << e.what() << std::endl;
    }

    return order; 
}


std::future<OrderBinaryPayload> OrderService::processOrder(OrderPayload order_payload) {
    return std::async(std::launch::async, [this, order_payload]() {
        return this->processOrderSync(order_payload);
    }); 
}


std::vector<std::future<OrderBinaryPayload>> OrderService::massProcess(std::vector<OrderPayload> order_payloads) {
    std::vector<std::future<OrderBinaryPayload>> futures; 
    int n = order_payloads.size();

    for (OrderPayload &payload : order_payloads) {
        futures.push_back(processOrder(payload)); 
    }

    return futures; 
}

