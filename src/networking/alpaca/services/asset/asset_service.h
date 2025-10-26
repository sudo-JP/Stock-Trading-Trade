#include "networking/alpaca/models/asset_model.h"
#include "core/config/config.h"
#include <vector>
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
        AssetBinaryPayload get_asset(const std::string &symbol);

        /*
         * @brief Get all assets 
         * @return Vector containing all assets
         * */
        std::vector<AssetBinaryPayload> get_assets(); 

    private: 
        const ENV env; 
        const std::string route = "/v2/assets/";
};

#endif 
