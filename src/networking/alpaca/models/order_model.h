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

    // Timestamps (nanoseconds)
    int64_t created_at;
    int64_t updated_at;
    int64_t submitted_at;
    int64_t filled_at;            // 0 if not filled yet
    char status[16]; 

    // Core order info
    char asset_id[64]; 
    char symbol[16];              // e.g., "NVDA"
    char side[8];                 // "buy" or "sell"
    char type[16];                // "market", "limit", etc.
    char time_in_force[8];        // "day", "gtc"

    uint32_t qty;                 // total order quantity
    uint32_t filled_qty;          // filled quantity
    float filled_avg_price;       // avg fill price, 0 if not filled

    char asset_class[16];         // "us_equity", "crypto", etc.
    char position_intent[16];     // buy_to_open, sell_to_close, etc.
    float notional;               // total value of order, if provided
    float limit_price;            // if limit order
    float stop_price;             // if stop order
    char extended_hours;          // executed in extended hours or not
};
#pragma pack()


#endif 
