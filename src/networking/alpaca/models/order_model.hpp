#include <string>
#include "core/status.hpp"
#ifndef _ORDER_MODEL_H_
#define _ORDER_MODEL_H_

struct OrderPayload {
    std::string symbol; 
    int qty; 
    std::string side; // Either "buy" or "sell"
    std::string type; // Market orer 
    std::string time_in_force; 
}; 

// Times are represented in nanoseconds 
#pragma pack(1)
struct OrderBinaryPayload {
    char id[64];              

    // Timestamps (nanoseconds)
    int64_t created_at;
    int64_t updated_at;
    int64_t submitted_at;
    int64_t filled_at;        
    char status[16]; 

    // Core order info
    char asset_id[64]; 
    char symbol[16];           
    char side[8];               
    char type[16];               
    char time_in_force[8];        

    double qty;            
    double filled_qty;      
    double filled_avg_price;    

    char asset_class[16];       
    char position_intent[16];    
    double notional;               
    double limit_price;          
    double stop_price;            
    char extended_hours;          
};
#pragma pack()


#endif 
