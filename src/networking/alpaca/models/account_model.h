#include <chrono>
#include <string>
#include "core/status.h"
#ifndef _ACCOUNT_MODEL_H_
#define _ACCOUNT_MODEL_H_

#pragma pack(1)
struct AccountBinaryPayload {
    char account_id[64];
    char currency[4];
    
    double buying_power; 
    double cash;
    double portfolio_value; 
    double equity; 

    // Performance
    double unrealized_pl; 
    double realized_pl;

    uint32_t status; 
    int64_t last_update;
}; 
#pragma pack()


enum TimeFrame {
    HOURLY, 
    DAILY, 
    WEEKLY, 
    MONTHLY
};

struct PnLData {
    double absolute_change;    // Dollar amount gained/lost
    double percentage_change;  // Percentage gained/lost
    TimeFrame time; 
};

#endif 
