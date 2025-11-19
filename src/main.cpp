#include "networking/alpaca/services/account/account_service.hpp"
#include "core/config/config.hpp"
#include "networking/tcp/client/tcp_client.hpp"
#include <iostream>
#include "execution/engine.hpp"
#define PORT_RANGE 100
#define THREADS 100

int main() {
    // Handshake 
    ENV env = ENV::getInstance();
    TCPClient client(env); 
    TCPServer server(env); 
    TaskPool tp; 

    Engine eng(tp, server, client);
    
    BinaryMessage msg; 
    // Filler value 
    msg.sql_command = SQLCommand::INSERT;
    msg.table = SQLTable::ACCOUNT;
    msg.type = MessageType::HANDSHAKE;

    Handshake hs = { THREADS, PORT_RANGE }; 
    if (!client.send_data(msg, &hs, sizeof(Handshake))) {
        std::cerr << "Failed to handshake with other repos" << std::endl;
        return -1; 
    }

    eng.start(THREADS); 

    // Closing handshake 
    msg.type = MessageType::SHUTDOWN; 
    Shutdown sd = { 0, 0 }; 
    if (!client.send_data(msg, &sd, sizeof(Shutdown))) {
        std::cerr << "Failed to close connection with other repos" << std::endl;
        return -1; 
    }
    eng.stop(); 
    client.disconnect();
    return 0;
}
