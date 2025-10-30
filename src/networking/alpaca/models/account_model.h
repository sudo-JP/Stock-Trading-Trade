#include "core/status.h"
#ifndef _ACCOUNT_MODEL_H_
#define _ACCOUNT_MODEL_H_


#pragma pack(1)
struct AccountBinaryPayload {
    char account_id[64];     
    char currency[4];         

    double cash;            
    double buying_power;   
    double equity;        
    double portfolio_value;   

    double effective_buying_power;   
    double daytrading_buying_power; 
    double regt_buying_power;      
    double non_marginable_buying_power; 
    double last_equity;              
    double sma;                     
    double position_market_value;    
    double long_market_value;       
    double short_market_value;     

    // Metadata
    uint32_t status;                 // ACTIVE, CLOSED, etc.
    int64_t balance_asof;             // timestamp of last update
    int32_t daytrade_count;          // optional, tracks pattern day trades
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
