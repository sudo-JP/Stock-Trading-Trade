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
         * @brief Fetches all assets from Alpaca API 
         * @return Asset populated with the symbol
         * */
        std::future<std::vector<AssetBinaryPayload>> getAssets();

    private: 
        const ENV env; 
        std::vector<AssetBinaryPayload> getAssetsSync();
        const std::string route = "/v2/assets";
};

#endif 
