#include "order_service.h"
#include <future>
#include <chrono> 
#include <iomanip>

int64_t parse_time(const nlohmann::json &data, const std::string &key) {
    if (data[key].is_null()) {
        return 0; 
    } 
    std::string time = data[key]; 
    time.erase(std::remove(time.begin(), time.end(), 'Z'), time.end()); 
    std::istringstream iss(time); 
    std::tm t = {};

    if (!(iss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))) {
        return 0; 
    }
    time_t epoch = timegm(&t); 
    auto tp = std::chrono::system_clock::from_time_t(epoch);
    auto ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(tp)
              .time_since_epoch()
              .count();

    return ns; 
}

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


    try {

        json data = json::parse(res->body);
        order.created_at = parse_time(data, "created_at");
        order.filled_at = parse_time(data, "filled_at");
        order.submitted_at = parse_time(data, "submitted_at");
        order.updated_at = parse_time(data, "updated_at");

        safe_str_copy(order.id, get_or_default(data, "id", ""));
        safe_str_copy(order.client_order_id, get_or_default(data, "client_order_id", ""));
        safe_str_copy(order.symbol, get_or_default(data, "symbol", ""));
        safe_str_copy(order.side, get_or_default(data, "side", ""));
        safe_str_copy(order.type, get_or_default(data, "type", ""));


        std::string qty_str = get_or_default<std::string>(data, "qty", "0");
        order.qty = std::stoi(qty_str);

        std::string filled_qty_str = get_or_default(data, "filled_qty", "0"); 

        order.filled_qty = std::stoi(filled_qty_str);
        // filled avg price 
        safe_str_copy(order.time_in_force, get_or_default(data, "time_in_force", "utc"));

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

