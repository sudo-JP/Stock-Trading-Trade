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

            position.asset_id = pos["asset_id"];
            position.symbol = pos["symbol"];
            position.exchange = pos["exchange"];
            position.asset_class = pos["asset_class"];

            position.qty = std::stoi(pos["qty"].get<std::string>());
            position.avg_entry_price = std::stod(pos["avg_entry_price"].get<std::string>());

            position.side = pos["side"];
            position.market_value = std::stod(pos["market_value"].get<std::string>());

            position.cost_basis = std::stod(pos["cost_basis"].get<std::string>());
            position.unrealized_pl = std::stod(pos["unrealized_pl"].get<std::string>());
            position.unrealized_plpc = std::stod(pos["unrealized_plpc"].get<std::string>());

            position.unrealized_intraday_pl = std::stod(pos["unrealized_intraday_pl"].get<std::string>());
            position.unrealized_intraday_plpc = std::stod(pos["unrealized_intraday_plpc"].get<std::string>());

            position.current_price = std::stod(pos["current_price"].get<std::string>());
            position.lastday_price = std::stod(pos["lastday_price"].get<std::string>());
            position.change_today = std::stod(pos["change_today"].get<std::string>());

            positions.push_back(position);
        }

    } catch (std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return positions;
    }

    positions.clear(); 

    return positions; 
}
