#include "position_model.h"
#include <vector>
#include "config.h"
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
        std::vector<Position> get_positions(bool refreshed = false);
    

    private: 
        const ENV env;
        const std::string route = "/v2/positions";
        std::vector<Position> positions; 
}; 

#endif 
