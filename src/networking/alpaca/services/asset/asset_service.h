#include "asset.h"
#include <vector>
#ifndef _ASSET_SERVICE_H_
#define _ASSET_SERVICE_H_

class AssetService {
    public:
        /*
         * @brief Fetches the asset from Alpaca API 
         * @param symbol The symbol of the asset 
         * @return Asset populated with the symbol
         * */
        Asset get_asset(const std::string &symbol);

        /*
         * @brief Get all assets 
         * @return Vector containing all assets
         * */
        std::vector<Asset> get_assets(); 

        /*
         * @brief Check if given symbol is tradable 
         * @param symbol The symbol to be checked 
         * @return true if tradable 
         * */
        bool is_tradable(const std::string &symbol); 

        /*
         * @brief Check if symbol is valid, should be used before 
         * @brief attempting to get an asset 
         * @param symbol The symbol to be checked 
         * @return true if symbol exists 
         * */
        bool is_valid_symbol(const std::string &symbol);
};

#endif 
