#include "asset_service.h"
#include <boost/algorithm/string.hpp>
#include <future>


AssetBinaryPayload AssetService::getAssetSync(const std::string &symbol) {
    AssetBinaryPayload asset; 
    
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 
    auto res = client.Get(route + symbol, headers); 
    asset.tradeable = false; 
    asset.status = statusTouint32(BinaryStatus::UNKNOWN);

    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return asset;
    }

    try {
        json data = json::parse(res->body); 
        safeStrcpy(asset.id, getOrDefault(data, "id", ""));
        safeStrcpy(asset.asset_class, getOrDefault(data, "class", "")); 
        safeStrcpy(asset.exchange, getOrDefault(data, "exchange", ""));
        safeStrcpy(asset.symbol, getOrDefault(data, "symbol", ""));
        safeStrcpy(asset.name, getOrDefault(data, "name", ""));
        asset.status = boost::iequals(getOrDefault(data, "status", "active"), "active") 
            ? statusTouint32(BinaryStatus::ACTIVE)
            : statusTouint32(BinaryStatus::INACTIVE);
        asset.tradeable = getOrDefault(data, "tradable", false) ? 1 : 0;
        asset.marginable = getOrDefault(data, "marginable", false) ? 1 : 0;
        asset.shortable = getOrDefault(data, "shortable", false) ? 1 : 0; 
        asset.easy_to_borrow = getOrDefault(data, "easy_to_borrow", false) ? 1 : 0;
        asset.fractionable = getOrDefault(data, "fractionable", false) ? 1 : 0;
        
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON for asset: " << e.what() << std::endl;
        return asset; 
    }


    return asset; 
} 

std::future<AssetBinaryPayload> AssetService::getAsset(const std::string &symbol) {
    return std::async(std::launch::async, [this, symbol]() {
        return this->getAssetSync(symbol); 
    }); 
}
