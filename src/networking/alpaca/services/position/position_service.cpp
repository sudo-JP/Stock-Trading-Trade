#include "position_service.h"

std::vector<PositionBinaryPayload> PositionService::get_positions(bool refreshed) {
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
            PositionBinaryPayload position;     

            safe_str_copy(position.asset_id, pos["asset_id"]);
            safe_str_copy(position.symbol, pos["symbol"]);
            safe_str_copy(position.exchange, pos["exchange"]);
            safe_str_copy(position.asset_class, pos["asset_class"]);

            position.qty = std::stoi(pos["qty"].get<std::string>());
            position.avg_entry_price = json_to_double(pos["avg_entry_price"]);

            safe_str_copy(position.side, pos["side"]);
            position.market_value = json_to_double(pos["market_value"]);

            position.cost_basis = json_to_double(pos["cost_basis"]);
            position.unrealized_pl = json_to_double(pos["unrealized_pl"]);
            position.unrealized_plpc = json_to_double(pos["unrealized_plpc"]);

            position.unrealized_intraday_pl = json_to_double(pos["unrealized_intraday_pl"]);
            position.unrealized_intraday_plpc = json_to_double(pos["unrealized_intraday_plpc"]);

            position.current_price = json_to_double(pos["current_price"]);
            position.lastday_price = json_to_double(pos["lastday_price"]);
            position.change_today = json_to_double(pos["change_today"]);

            positions.push_back(position);
        }

    } catch (std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return positions;
    }

    positions.clear(); 

    return positions; 
}
