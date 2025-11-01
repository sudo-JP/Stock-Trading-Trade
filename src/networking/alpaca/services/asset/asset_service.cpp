#include "asset_service.h"
#include <boost/algorithm/string.hpp>
#include <future>


std::vector<AssetBinaryPayload> AssetService::getAssetsSync() {
    
    httplib::SSLClient client(env.URL); 
    httplib::Headers headers = {
        {"APCA-API-KEY-ID", env.ALPACA_KEY},
        {"APCA-API-SECRET-KEY", env.ALPACA_SECRET_KEY}
    }; 
    auto res = client.Get(route, headers); 

    std::vector<AssetBinaryPayload> assets; 
    if (!res || res->status != 200) {
        std::cerr << "HTTP Error: " << (res ? res->status : -1) << std::endl;
        return assets;
    }

    try {
        json arr = json::parse(res->body); 
        if (!arr.is_array()) return assets;
            for (const auto &data: arr) {
            AssetBinaryPayload asset; 

            // String identification 
            safeStrcpy(asset.id, getOrDefault(data, "id", ""));
            safeStrcpy(asset.symbol, getOrDefault(data, "symbol", ""));
            safeStrcpy(asset.name, getOrDefault(data, "name", ""));
            safeStrcpy(asset.asset_class, getOrDefault(data, "class", "")); 
            safeStrcpy(asset.exchange, getOrDefault(data, "exchange", ""));
            safeStrcpy(asset.status, getOrDefault(data, "status", "inactive"));


            // Boolean 
            asset.tradable = getOrDefault(data, "tradable", false) ? 1 : 0;
            asset.marginable = getOrDefault(data, "marginable", false) ? 1 : 0;
            asset.shortable = getOrDefault(data, "shortable", false) ? 1 : 0; 
            asset.fractionable = getOrDefault(data, "fractionable", false) ? 1 : 0;
            asset.easy_to_borrow = getOrDefault(data, "easy_to_borrow", false) ? 1 : 0;

            // Margins 
            asset.maintenance_margin_requirement = jsonToNumber<float>(data, "maintenance_margin_requirement");
            asset.margin_requirement_long = jsonToNumber<float>(data, "margin_requirement_long");
            asset.margin_requirement_short = jsonToNumber<float>(data, "margin_requirement_short"); 

            assets.push_back(asset);
        }
        
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse JSON for asset: " << e.what() << std::endl;
        return assets; 
    }

    return assets; 
} 

std::future<std::vector<AssetBinaryPayload>> AssetService::getAssets() {
    return std::async(std::launch::async, [this]() {
        return this->getAssetsSync(); 
    }); 
}
