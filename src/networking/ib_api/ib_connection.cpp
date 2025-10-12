#include "ib_wrapper.h"

bool TradingApp::connect(const char *host, int port, int clientId) {
    bool error; 
    if ((error = this->client->eConnect(host, port, clientId, auth))) {
        std::cout << "Connected to server on host" << this->client->host() << " on port " << this->client->port();    
        this->ereader = std::unique_ptr<EReader>(new EReader(this->client, &this->m_osSignal)); 
        this->ereader->start(); 
        this->readerThread = std::thread([this] {
            this->processMessage();
        });
    }
    else {
        std::cout << "Can't connect to TWS"; 
    }
    return error;
}

TradingApp::~TradingApp() {
}


void TradingApp::disconnect() {
    this->client->eDisconnect(); 
    this->thread_shutdown = true; 
    this->m_osSignal.issueSignal();
    if (this->readerThread.joinable()) {
        this->readerThread.join();
    }
    std::cout << "Disconnected"; 
}

void TradingApp::processMessage() {
    while (!this->thread_shutdown && this->client->isConnected()) {
        this->m_osSignal.waitForSignal();
        if (!this->thread_shutdown) {
            this->ereader->processMsgs();
        }
    }
}

