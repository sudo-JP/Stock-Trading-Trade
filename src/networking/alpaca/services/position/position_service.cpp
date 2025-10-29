#include "position_service.h"

std::vector<PositionBinaryPayload> PositionService::getPositions(bool refreshed) {
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
        if (!data.is_array()) return positions;
        for (const auto &pos : data) {
            PositionBinaryPayload position;     

            safeStrcpy(position.asset_id, getOrDefault(pos, "asset_id", ""));
            safeStrcpy(position.symbol, getOrDefault(pos, "symbol", ""));
            safeStrcpy(position.exchange, getOrDefault(pos, "exchange", ""));
            safeStrcpy(position.asset_class, getOrDefault(pos, "asset_class", ""));

            std::string qty = getOrDefault(pos, qty, "0"); 
            position.qty = std::stoi(qty);
            position.avg_entry_price = jsonToDouble(pos, "avg_entry_price");

            safeStrcpy(position.side, getOrDefault(pos, "side", ""));
            position.market_value = jsonToDouble(pos, "market_value");

            position.cost_basis = jsonToDouble(pos, "cost_basis");
            position.unrealized_pl = jsonToDouble(pos, "unrealized_pl");
            position.unrealized_plpc = jsonToDouble(pos, "unrealized_plpc");

            position.unrealized_intraday_pl = jsonToDouble(pos, "unrealized_intraday_pl");
            position.unrealized_intraday_plpc = jsonToDouble(pos, "unrealized_intraday_plpc");

            position.current_price = jsonToDouble(pos, "current_price");
            position.lastday_price = jsonToDouble(pos, "lastday_price");
            position.change_today = jsonToDouble(pos, "change_today");

            positions.push_back(position);
        }

    } catch (std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return positions;
    }

    positions.clear(); 

    return positions; 
}
