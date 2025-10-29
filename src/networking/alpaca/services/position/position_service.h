#include "networking/alpaca/models/position_model.h"
#include <vector>
#include "core/config/config.h"
#include <future>
#ifndef _POSITION_SERVICE_H_
#define _POSITION_SERVICE_H_

class PositionService {
    public: 
        PositionService(ENV t_env) : env(t_env) {}; 

        /*
         * @brief get the current position
         * @param refreshed Set true refreshed to get new info  
         * @return vector of positions  
         * */
        std::future<std::vector<PositionBinaryPayload>> getPositions(bool refreshed = false);
    

    private: 
        std::vector<PositionBinaryPayload> getPositionsSync(bool refreshed = false);
        const ENV env;
        const std::string route = "/v2/positions";
        std::vector<PositionBinaryPayload> positions; 
}; 

#endif 
