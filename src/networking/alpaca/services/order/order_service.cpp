#include "order_service.h"
#include <future>

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
        // Identity 
        safeStrcpy(order.id, std::string(getOrDefault(data, "id", std::string(""))));

        // Timestamps 
        order.created_at = parseTime(data, "created_at");
        order.filled_at = parseTime(data, "filled_at");
        order.submitted_at = parseTime(data, "submitted_at");
        order.updated_at = parseTime(data, "updated_at");

        // Status 
        safeStrcpy(order.status, std::string(getOrDefault(data, "status", std::string("UNKNOWN"))));

        
        // IDs 
        safeStrcpy(order.asset_id, std::string(getOrDefault(data, "asset_id", std::string(""))));
        safeStrcpy(order.symbol, std::string(getOrDefault(data, "symbol", std::string(""))));
        safeStrcpy(order.side, std::string(getOrDefault(data, "side", std::string(""))));
        safeStrcpy(order.type, std::string(getOrDefault(data, "type", std::string(""))));
        safeStrcpy(order.time_in_force, std::string(getOrDefault(data, "time_in_force", std::string(""))));


        // Numbering 
        order.qty = jsonToNumber<uint32_t>(data, "qty"); 
        order.filled_qty = jsonToNumber<uint32_t>(data, "filled_qty"); 
        order.filled_avg_price = jsonToNumber<float>(data, "filled_avg_price"); 
        
        // Asset and Position 
        safeStrcpy(order.asset_class, std::string(getOrDefault(data, "asset_class", std::string(""))));
        safeStrcpy(order.position_intent, std::string(getOrDefault(data, "position_intent", std::string(""))));

        order.notional = jsonToNumber<float>(data, "notional"); 
        order.limit_price = jsonToNumber<float>(data, "limit_price"); 
        order.stop_price = jsonToNumber<float>(data, "stop_price"); 
        order.extended_hours = getOrDefault(data, "extended_hours", false) ? 1 : 0; 
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

