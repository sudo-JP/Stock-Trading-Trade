#include <string>
#ifndef _ORDER_H_
#define _ORDER_H_

struct OrderPayload {
    std::string symbol; 
    int qty; 
    std::string side; // Either "buy" or "sell"
    std::string type; // Market orer 
    std::string time_in_force; 
}; 

struct Order {
    std::string id; 

}; 


#endif 
