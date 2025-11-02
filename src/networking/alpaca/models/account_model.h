#include "core/status.h"
#ifndef _ACCOUNT_MODEL_H_
#define _ACCOUNT_MODEL_H_



#pragma pack(1)
struct AccountBinaryPayload {
    char id[64];     
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
    char status[16];
    char crypto_status[16];
    int64_t balance_asof;
    double daytrade_count;
};

#pragma pack()
#endif 
