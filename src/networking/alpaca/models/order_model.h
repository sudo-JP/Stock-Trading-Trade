#include <string>
#include "core/status.h"
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
    char client_order_id[64];
    int64_t created_at;
    int64_t updated_at;
    int64_t submitted_at;
    int64_t filled_at;
    
    char symbol[16];
    char side[8];
    char type[16];
    int64_t time_in_force;

    uint32_t qty;
    uint32_t filled_qty;
    float filled_avg_price;
};
#pragma pack()


#endif 
