#ifndef _IB_WRAPPER_H_
#define _IB_WRAPPER_H_
#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"
#include "EClientSocket.h"
#include <thread>

/*
 * Trading Application that handles IB API communication 
 *
 * Inherits EWrapper to receive callbacks and send requests via ECLientSocket
 * */


namespace ib_wrapper {
    enum tick_name {
        // Highest big price on the contact
        // handler: tickPrice
        BID_PRICE = 1,         

        // Lowest price offer on the contact
        // handler: tickPrice
        ASK_PRICE = 2,

        // Last price at which contract traded
        // handler: tickPrice
        LAST_PRICE = 4,

        // High price of the day
        // handler: tickPrice
        HIGH_PRICE = 6, 

        // Low price of the day 
        // handler: tickPrice
        LOW_PRICE = 7, 

        // The prev day's adjusted closing price 
        // handler: tickPrice
        CLOSE_PRICE = 9,

        // Curr session's opening price
        // handler: tickPrice
        OPEN_TICK = 14, 

        // Number of lots offered at the bid price 
        // handler: tickSize
        BID_SIZE = 0, 

        // Number of lots traded at the last price 
        // handler: tickSize
        ASK_SIZE = 3, 

        // Number of lots traded at the last price 
        // handler: tickSize
        LAST_SIZE = 5, 

        // Trading volume for the day (US Stocks: mult 100)
        // handler: tickSize
        VOLUME = 8
    }; 
}


class EClientSocket; 

class TradingApp : public EWrapper {
    private: 
        EReaderOSSignal m_osSignal;
        EClientSocket * const client;
        bool auth; 
        std::unique_ptr<EReader> ereader;

        bool thread_shutdown; 
        std::thread readerThread; 

        OrderId first_ord;

        double currentBid; 
        double currentAsk;

    public: 
        TradingApp();

        ~TradingApp();

        bool connect(const char *host = "127.0.0.1", int port = 7497, int clientId = 1); 

        void disconnect(); 

        void processMessage(); 

        void error(int id, time_t errorTime, int errorCode, const std::string &errorMsg, const std::string &advancedOrderRejectJson) override; // Handling error codes

        void nextValidId(OrderId orderId) override;  // Save order id to satisfy IB Requirements
                                                     
        void connectionClosed() override;

        // Receives real-time price updates for subscribed symbols 
        void tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib &attrib) override;

        void orderStatus(OrderId orderId, const std::string &status, Decimal filled, Decimal remaining, double avgFillPrice, long long permId, int parentId, double lastFillPrice, int clientId, const std::string &whyHeld, double mktCapPrice) override;

        void execDetails(int reqId, const Contract &contract, const Execution &execution) override;
}; 

#endif 
