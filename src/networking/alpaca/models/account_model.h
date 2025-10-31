#include "core/status.h"
#ifndef _ACCOUNT_MODEL_H_
#define _ACCOUNT_MODEL_H_



#pragma pack(1)
enum class AccountStatus : int32_t {
    UNKNOWN = 0,
    ACTIVE = 1,
    REJECTED = 2, 
    APPROVAL_PENDING = 3, 
    ACCOUNT_UPDATED = 4, 
    SUBMITTED = 5, 
    SUBMISSION_FAILED = 6, 
    ONBOARDING = 7 
};

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
    int32_t status;
    int32_t crypto_status;
    int64_t balance_asof;
    double daytrade_count;
};

#pragma pack()
#endif 
