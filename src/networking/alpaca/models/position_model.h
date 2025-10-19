#include <string>
#ifndef _POSITION_MODEL_H_
#define _POSITION_MODEL_H_

struct Position {
    std::string asset_id;
    std::string symbol; 
    std::string exchange;
    std::string asset_class;

    int qty; 
    double avg_entry_price; 

    std::string side; 
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

#endif 
