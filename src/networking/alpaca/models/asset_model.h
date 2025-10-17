#include <string>
#include "status.h"
#ifndef _ASSET_MODEL_H_
#define _ASSET_MODEL_H_ 

struct Asset {
    std::string id;
    std::string asset_class;
    std::string exchange;
    std::string symbol; 
    std::string name; 
    Status status; 
    bool tradeable;
    bool marginable;
    bool shortable;
    bool easy_to_borrow; 
    bool fractionable;
};


#endif
