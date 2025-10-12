#include <iostream>
#include "ib_wrapper.h"
#include <thread>


TradingApp::TradingApp(): 
    m_osSignal(2000), client(new EClientSocket(this, &m_osSignal)), auth(false), thread_shutdown(false), first_ord(-1), currentAsk(0.0), currentBid(0.0)  {}






