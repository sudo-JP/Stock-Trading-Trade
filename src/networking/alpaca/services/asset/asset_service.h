#include "networking/alpaca/models/asset_model.h"
#include "core/config/config.h"
#include <vector>
#include <future>
#ifndef _ASSET_SERVICE_H_
#define _ASSET_SERVICE_H_

class AssetService {
    public:
        AssetService(const ENV t_env) : env(t_env) {};
        /*
         * @brief Fetches the asset from Alpaca API 
         * @param symbol The symbol of the asset 
         * @return Asset populated with the symbol
         * */
        std::future<AssetBinaryPayload> getAsset(const std::string &symbol);

        /*
         * @brief Get all assets 
         * @return Vector containing all assets
         * */
        std::vector<AssetBinaryPayload> getAssets(); 

    private: 
        const ENV env; 
        AssetBinaryPayload getAssetSync(const std::string &symbol);
        const std::string route = "/v2/assets/";
};

#endif 
