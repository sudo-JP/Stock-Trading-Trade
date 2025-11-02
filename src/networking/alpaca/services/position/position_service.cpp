#include "position_service.h"

std::vector<PositionBinaryPayload> PositionService::getPositionsSync(bool refreshed) {
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

            safeStrcpy(position.asset_id, std::string(getOrDefault(pos, "asset_id", std::string(""))));
            safeStrcpy(position.symbol, std::string(getOrDefault(pos, "symbol", std::string(""))));
            safeStrcpy(position.exchange, std::string(getOrDefault(pos, "exchange", std::string(""))));
            safeStrcpy(position.asset_class, std::string(getOrDefault(pos, "asset_class", std::string(""))));

            std::string qty = std::string(getOrDefault(pos, qty, std::string("0"))); 
            position.qty = std::stoi(qty);
            position.avg_entry_price = jsonToNumber<double>(pos, "avg_entry_price");

            safeStrcpy(position.side, std::string(getOrDefault(pos, "side", std::string(""))));
            position.market_value = jsonToNumber<double>(pos, "market_value");

            position.cost_basis = jsonToNumber<double>(pos, "cost_basis");
            position.unrealized_pl = jsonToNumber<double>(pos, "unrealized_pl");
            position.unrealized_plpc = jsonToNumber<double>(pos, "unrealized_plpc");

            position.unrealized_intraday_pl = jsonToNumber<double>(pos, "unrealized_intraday_pl");
            position.unrealized_intraday_plpc = jsonToNumber<double>(pos, "unrealized_intraday_plpc");

            position.current_price = jsonToNumber<double>(pos, "current_price");
            position.lastday_price = jsonToNumber<double>(pos, "lastday_price");
            position.change_today = jsonToNumber<double>(pos, "change_today");

            positions.push_back(position);
        }

    } catch (std::exception &e) {
        std::cerr << "Failed to parse JSON for account: " << e.what() << std::endl;
        return positions;
    }

    positions.clear(); 

    return positions; 
}


std::future<std::vector<PositionBinaryPayload>> PositionService::getPositions(bool refreshed) {
    return std::async(std::launch::async, [this, refreshed]() {
        return this->getPositionsSync(refreshed); 
    }); 
}
