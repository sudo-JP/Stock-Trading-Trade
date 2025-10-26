#include <cstdint>
#ifndef _POSITION_MODEL_H_
#define _POSITION_MODEL_H_

#pragma pack(1)
struct PositionBinaryPayload {
    char asset_id[64];
    char symbol[16];
    char exchange[16];
    char asset_class[16];

    uint32_t qty; 
    double avg_entry_price;
    
    char side[8];
    double market_value; 
    double cost_basis; 

    
    double unrealized_pl;
    double unrealized_plpc;
    double unrealized_intraday_pl;
    double unrealized_intraday_plpc;

    double current_price;
    double lastday_price;
    double change_today;
};
#pragma pack()

#endif 
