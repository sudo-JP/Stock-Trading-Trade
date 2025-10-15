#include <string> 
#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct env_t {
    const std::string ALPACA_KEY; 
    const std::string ALPACA_SECRET_KEY; 
    const std::string URL;
} ENV; 

ENV get_env();

#endif
