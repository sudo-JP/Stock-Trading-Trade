#ifndef _IB_WRAPPER_H_
#define _IB_WRAPPER_H_
#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"
#include "EClientSocket.h"
#include <string>

/*
 * Trading Application that handles IB API communication 
 *
 * Inherits EWrapper to receive callbacks and send requests via ECLientSocket
 * */
//class EClientSocket; 

//class TradingApp : public EWrapper {
//private: 
//std::string host; 
//int port; 
//int id; 
//EReaderOSSignal m_osSignal;
//ECLientSocket * const client;
//bool auth; 
//
//public: 
//TradingApp(const std::string& host = "127.0.0.1", int port = 7497, int clientId = 1);
//
//~TradingApp();
//bool connect(); 
//void disconnect(); 
//}; 
//#endif 
