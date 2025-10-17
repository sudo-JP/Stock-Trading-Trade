#include "asset_service.h"
#include <boost/algorithm/string.hpp>


Asset AssetService::get_asset(const std::string &symbol) {
    Asset asset; 
    
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 

    auto res = client.Get(route + symbol, headers); 
    asset.tradeable = false; 
    asset.status = Status::UNKNOWN; 

    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return asset;
    }

    try {
        json data = json::parse(res->body); 
        asset.id = data["id"];
        asset.asset_class = data["class"]; 
        asset.exchange = data["exchange"]; 
        asset.symbol = data["symbol"]; 
        asset.name = data["name"]; 
        boost::iequals(data["status"], "active") ? asset.status = Status::ACTIVE : asset.status = Status::INACTIVE;
        asset.tradeable = data["tradable"];
        asset.marginable = data["marginable"];
        asset.shortable = data["shortable"]; 
        asset.easy_to_borrow = data["easy_to_borrow"];
        asset.fractionable = data["fractionable"];
        
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON for asset: " << e.what() << std::endl;
        return asset; 
    }


    return asset; 
} 
