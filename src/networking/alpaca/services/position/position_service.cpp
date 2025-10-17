#include "position_service.h"

std::vector<Position> PositionService::get_positions(bool refreshed) {
    if (!refreshed) return positions;


    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 

    auto res = client.Get(route, headers); 

    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return positions; 
    }

    try {
        json data = json::parse(res->body); 
        for (const auto &pos : data) {
            Position position;     
            position.symbol = pos["symbol"];
            position.qty = std::stoi(pos["avg_entry_price"].get<std::string>());
            position.market_value = std::stod(pos["current_price"].get<std::string>());
            position.avg_entry_price = std::stod(pos["avg_entry_price"].get<std::string>());
            position.side = pos["side"]; 

            positions.push_back(position);
        }

    } catch (std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return positions;
    }

    positions.clear(); 

    return positions; 
}
