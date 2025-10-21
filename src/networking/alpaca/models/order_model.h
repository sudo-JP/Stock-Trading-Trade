#include <string>
#include "core/status.h"
#include <chrono>
#ifndef _ORDER_MODEL_H_
#define _ORDER_MODEL_H_

struct OrderPayload {
    std::string symbol; 
    int qty; 
    std::string side; // Either "buy" or "sell"
    std::string type; // Market orer 
    std::string time_in_force; 
}; 

struct Order {
    std::string id; 
    std::string client_order_id; 
    std::chrono::system_clock::time_point created_at; 
    std::chrono::system_clock::time_point updated_at; 
    std::chrono::system_clock::time_point submitted_at; 
    std::chrono::system_clock::time_point filled_at; 
    Status status;    

    // Should match with payload
    std::string symbol;
    std::string side; 
    std::string type; 
    int qty; 
    std::string time_in_force;

    int filled_qty; 
    float filled_avg_price; 
}; 


#endif 
