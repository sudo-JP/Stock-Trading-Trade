#include <string>
#ifndef _POSITION_MODEL_H_
#define _POSITION_MODEL_H_

struct Position {
    std::string symbol; 
    int qty; 
    float market_value; 
    float avg_entry_price; 
    std::string side;
};

#endif 
