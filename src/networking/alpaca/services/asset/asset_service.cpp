#include "asset_service.h"
#include <boost/algorithm/string.hpp>


AssetBinaryPayload AssetService::get_asset(const std::string &symbol) {
    AssetBinaryPayload asset; 
    
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 
    auto res = client.Get(route + symbol, headers); 
    asset.tradeable = false; 
    asset.status = status_to_uint32(BinaryStatus::UNKNOWN);

    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return asset;
    }

    try {
        json data = json::parse(res->body); 
        safe_str_copy(asset.id, data["id"]);
        safe_str_copy(asset.asset_class, data["class"]); 
        safe_str_copy(asset.exchange, data["exchange"]);
        safe_str_copy(asset.symbol, data["symbol"]);
        safe_str_copy(asset.name, data["name"]);
        asset.status = boost::iequals(data["status"], "active") 
            ? status_to_uint32(BinaryStatus::ACTIVE)
            : status_to_uint32(BinaryStatus::INACTIVE);
        asset.tradeable = data["tradable"] ? 1 : 0;
        asset.marginable = data["marginable"] ? 1 : 0;
        asset.shortable = data["shortable"] ? 1 : 0; 
        asset.easy_to_borrow = data["easy_to_borrow"] ? 1 : 0;
        asset.fractionable = data["fractionable"] ? 1 : 0;
        
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON for asset: " << e.what() << std::endl;
        return asset; 
    }


    return asset; 
} 
