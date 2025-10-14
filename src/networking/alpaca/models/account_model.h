#include <string>
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
    double daily_change;
    double daily_change_percentage; 

    // Status
    AccountStatus status; 

}; 

#endif 
