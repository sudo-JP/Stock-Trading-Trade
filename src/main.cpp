#include <iostream> 
#include "EWrapper.h"
#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"
#include "EClientSocket.h"
#include <string>



class EClientSocket; 

class TradingApp : public EWrapper {
    private: 
        EReaderOSSignal m_osSignal;
        EClientSocket * client;
        bool auth; 

    public: 
        TradingApp() {
            client = new EClientSocket(this, &m_osSignal);
            auth = false; 
        };

        bool connect(const char *host = "127.0.0.1", int port = 7497, int clientId = 1) {
            int e = client->eConnect(host, port, clientId); 
            return e; 
        }
}; 



int main() {
    std::cout << "Hello World\n";   

    return 0; 
}
