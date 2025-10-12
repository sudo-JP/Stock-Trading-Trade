#include "ib_wrapper.h"

void TradingApp::error(int id, time_t errorTime, int errorCode, const std::string &errorMsg, const std::string &advancedOrderRejectJson) {
    if (errorCode == 502 || errorCode == 504 || errorCode == 1100) {
        std::cout << "Connection issue: " << errorMsg;
        std::cout << "Exiting with code: " << errorCode;
        std::cout << "Details: " << advancedOrderRejectJson;

        this->thread_shutdown = true; 
        return; 
    }
    std::cout << "Code error: " << errorCode; 
    std::cout << "Error Message: " << errorMsg; 
    std::cout << "Details: " << advancedOrderRejectJson;
}

void TradingApp::connectionClosed() {
    this->thread_shutdown = true;
}
