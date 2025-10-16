#include <chrono>
#include <string>
#include "status.h"
#ifndef _ACCOUNT_MODEL_H
#define _ACCOUNT_MODEL_H

enum AccountStatus {
    ACTIVE,
    INACTIVE
}; 

struct Account {
    // Basic info 
    std::string account_id; 
    std::string currency; 
    double buying_power; 
    double cash;
    double portfolio_value; 
    double equity; 

    // Performance
    double unrealized_pl; 
    double realized_pl;

    // Status
    Status status; 
    std::chrono::system_clock::time_point last_update;
}; 

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
