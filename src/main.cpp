#include <iostream> 
#include "account_service.h"
#include "config.h"


int main() {
    AccountService as(get_env());  
    Account acc = as.getAccount(true);
    std::cout << acc.cash;
    return 0; 
}
